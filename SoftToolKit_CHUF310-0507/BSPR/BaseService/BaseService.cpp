#include "BaseService.h"
#include <process.h>
#include <stdio.h>
/**************************************************************************************/
#pragma warning( disable:4311 )
/**************************************************************************************/


RMHDR::RMHDR()
{
	m_iGateByte   = VALIDATA_GATEBYTE;
	m_eventFinish = NULL;
	m_iSize       = 0;
	memset( m_paramName, 0, sizeof( TCHAR )*PARAM_NAME_LENTH );
}
RMHDR::~RMHDR()
{
	m_iGateByte   = VALIDATA_GATEBYTE;
	m_iSize       = 0;
	memset( m_paramName, 0, sizeof( TCHAR )*PARAM_NAME_LENTH );
	if( NULL != m_eventFinish ){
		CloseHandle( m_eventFinish );
		m_eventFinish = NULL;
	}
}
BOOL RMHDR::IsKindOf( LPCTSTR pStrTypeName )
{
	BOOL bRet = FALSE;
	if( 0 == icomparetext( pStrTypeName, m_paramName ) )
	{
		bRet = TRUE;
	}
	return bRet; 
}
BOOL RMHDR::IsValidate()
{
	BOOL bRet = FALSE;
	if ( m_iGateByte == VALIDATA_GATEBYTE )
	{
		bRet = TRUE;
	}
	return bRet;
}
void RMHDR::ProcessFinish()
{
	if ( NULL != m_eventFinish )
	{
		SetEvent( m_eventFinish );
	}
}
void RMHDR::Release()
{
	if ( IsValidate() )
	{
		BYTE* p = (BYTE*)this;
		delete[] p;
		p = NULL;
	}
}
RMHDR* RMHDR::Colne()
{
	RMHDR* pHDR = NULL;
	if ( IsValidate() )
	{
		pHDR = (RMHDR*)( new BYTE[ m_iSize ] );
		if ( NULL != pHDR )
		{
			memcpy( pHDR, this, m_iSize );
		}
	}
	return pHDR;
}

class CServiceManager
{
public:
	struct ServicePacket{
		DWORD dwServiceID;
		CBSPRService* pServicePoint;
	};
	CServiceManager()
	{
		memset( m_arrayService, 0, sizeof(m_arrayService) );
	}
	virtual ~CServiceManager()
	{

	}
	static CServiceManager& GetManagerInstance()
	{
		static CServiceManager inst;
		return inst;
	}
	BOOL RegistService( CBSPRService* pBaseService )
	{
		BOOL bRegisted = FALSE;
		DWORD dwFackID = -1;
		if ( NULL != pBaseService )
		{
			dwFackID = pBaseService->GetServiceFackID();
		}

		for ( int index = 0; index < MAX_SERVICE_NUM; ++index )
		{
			ServicePacket& packet = m_arrayService[index];
			if( NULL == packet.pServicePoint ){
				packet.dwServiceID = dwFackID;
				packet.pServicePoint = pBaseService;
				bRegisted = TRUE;
			}
		}

		return bRegisted;
	}
	void CServiceManager::UnRegistService( CBSPRService* pBaseService )
	{
		for ( int index = 0; index < MAX_SERVICE_NUM; ++index )
		{
			ServicePacket& packet = m_arrayService[index];
			if( NULL == packet.pServicePoint ) continue;
			if( pBaseService != packet.pServicePoint ) continue;

			packet.dwServiceID = 0;
			packet.pServicePoint = NULL;
		}
	}
	DWORD CServiceManager::GetFackIDByName( LPCTSTR strName )
	{
		DWORD dwReturn = -1;

		for ( int index = 0; index < MAX_SERVICE_NUM; ++index )
		{
			ServicePacket& packet = m_arrayService[index];
			if( NULL == packet.pServicePoint ) continue;
			if( 0 == icomparetext( packet.pServicePoint->GetServiceName(), strName ) )
			{
				dwReturn = packet.dwServiceID;
				break;
			}
		}
		return dwReturn;
	}
	CBSPRService* CServiceManager::GetServiceByName( LPCTSTR strName )
	{
		CBSPRService* pService = NULL;
		for ( int index = 0; index < MAX_SERVICE_NUM; ++index )
		{
			ServicePacket& packet = m_arrayService[index];
			if( NULL == packet.pServicePoint ) continue;
			if( 0 == icomparetext( packet.pServicePoint->GetServiceName(), strName ) )
			{
				pService = packet.pServicePoint;
				break;
			}
		}
		return pService;
	}

private:
	enum { MAX_SERVICE_NUM = 20 };
	ServicePacket m_arrayService[MAX_SERVICE_NUM];

};
#define  ServiceManager CServiceManager::GetManagerInstance()



CRequestProcessMethod* CRequestProcessMethod::SearchMethod( struct rb_root* root, UINT32 methodID )
{
    struct rb_node* node = root->rb_node;

	while( node )
	{
         CRequestProcessMethod* method = container_of( node, CRequestProcessMethod, mRBLink );

		 int iResult = (int)method->mMethodID - (int)methodID;

		 if( iResult < 0 )      node = node->rb_left;
		 else if( iResult > 0 ) node = node->rb_right;
		 else return method;
	}

	return NULL;
}
int CRequestProcessMethod::InsertMethod( struct rb_root* root, CRequestProcessMethod* newMethod )
{
    struct rb_node **nodeAddr = &root->rb_node, *parent = NULL;

	while( *nodeAddr )
	{
		CRequestProcessMethod* method = container_of( *nodeAddr, CRequestProcessMethod, mRBLink );

		int iResult = (int)method->mMethodID - (int)newMethod->mMethodID;

        parent = *nodeAddr;

		if( iResult < 0 )      nodeAddr = &((*nodeAddr)->rb_left);
		else if( iResult > 0 ) nodeAddr = &((*nodeAddr)->rb_right);
		else return 0;
	}

    rb_link_node( &newMethod->mRBLink, parent, nodeAddr );

	rb_insert_color( &newMethod->mRBLink, root );

	return 1;
}


struct MsgPacket : public RefBase
{ 
	DWORD      dwTarThreadID;
	UINT32       message;
	WPARAM     wParam;
	LPARAM     lParam;
	sp<MsgPacket> next;
	sp<MsgPacket> last;
	MsgPacket( DWORD id, UINT32 code, WPARAM w, LPARAM l )
		:dwTarThreadID(id)
		,message(code)
		,wParam(w)
		,lParam(l)
		,next(0)
		,last(0)
	{}
};

struct THREADPARAM 
{
	LPVOID                 lpthreadParam;
	LPTHREAD_START_ROUTINE lpStartAddress;
	LPCTSTR                lpThreadName;
};
unsigned int CALLBACK BSPRThreadProc( LPVOID lpParameter )
{
	THREADPARAM* pParam = ( THREADPARAM* )lpParameter;
	if ( NULL != pParam )
	{
		pParam->lpStartAddress( pParam->lpthreadParam );
	}
	delete pParam;  //非常重要

	return THREAD_EXIT_SUCCESS;
}
HANDLE BSPRCreatThread( IN LPTHREAD_START_ROUTINE lpstartAddress,
					   IN LPVOID lpParameter,
					   IN LPCTSTR lpthreadName,
					   OUT LPDWORD lpthreadID,
					   IN  LPSECURITY_ATTRIBUTES lpthreadAttributes,
					   IN SIZE_T dwsdacksize,
					   IN int nPriority
					   )
{
	unsigned int dwThreadID = 0;
	THREADPARAM* pthreadparam = new THREADPARAM;
	pthreadparam->lpStartAddress = lpstartAddress;
	pthreadparam->lpthreadParam  = lpParameter;
	pthreadparam->lpThreadName  = lpthreadName;
	HANDLE hThread = (HANDLE)_beginthreadex( NULL,
		(unsigned int)dwsdacksize, 
		&BSPRThreadProc, 
		pthreadparam, 
		0, 
		&dwThreadID );

	SetThreadPriority( hThread, nPriority );

	if( lpthreadID ) *lpthreadID = dwThreadID;
	return hThread;
}




CBSPRService::CBSPRService()
:m_dwFackID( -1 )
,m_hThreadHandle(NULL)
,m_bBackGoundProcessRequied( FALSE )
{
	//m_curMsgQueue.root = 0;
	//m_curMsgQueue.locked = FALSE;
	m_rbRequestMethod.rb_node = 0;
}
CBSPRService::~CBSPRService()
{
}
void CBSPRService::WakeUpDispatcher( UINT32 hostRequest )
{

}
BOOL CBSPRService::RequestAndWait( UINT32 RequestCode, RMHDR* pHDR )
{
	BOOL bRet = FALSE;

	TCHAR chName[50] = {0};
	transformat( chName, _T("%s-%d-%d"), pHDR->m_paramName, GetServiceFackID(), GetCurrentThreadId() );
	pHDR->m_eventFinish = ::CreateEvent( NULL, TRUE, FALSE, chName );

	PostBSPRThreadMessage( m_dwFackID, WM_SYNC_REQUEST,(WPARAM)RequestCode,(LPARAM)pHDR  );

	if( m_bBackGoundProcessRequied ) WakeUpDispatcher( RequestCode );

	::WaitForSingleObject( pHDR->m_eventFinish, INFINITE );

	::ResetEvent( pHDR->m_eventFinish );

	return bRet;
}

BOOL CBSPRService::RequestAndWaitEx( UINT32 RequestCode, RMHDR* pHDR )
{
	BOOL bRet = FALSE;

	CRequestProcessMethod* pMethod = CRequestProcessMethod::SearchMethod( &m_rbRequestMethod, RequestCode );
	if ( NULL != pMethod )
	{
		pMethod->Invoke( this, pHDR );
	}

	return bRet;
}
BOOL CBSPRService::Request( UINT32 RequestCode, RMHDR* pHDR )
{
	BOOL bRet = FALSE;

	RMHDR* pCopy = NULL;
	pCopy = pHDR->Colne();
	PostBSPRThreadMessage( m_dwFackID, WM_ASYN_REQUEST,(WPARAM)RequestCode,(LPARAM)pCopy );

	if( m_bBackGoundProcessRequied ) WakeUpDispatcher( RequestCode );

	return bRet;
}
void CBSPRService::StartService( int nPriority /*= 0*/ )
{
	LPCTSTR strWorkThreadName = GetServiceName();
    m_hThreadHandle = BSPRCreatThread(  (LPTHREAD_START_ROUTINE)CBSPRService::ThreadProc,
		this,
		strWorkThreadName,
		&m_dwFackID,
		NULL,
		0,
		nPriority
		);
	Sleep( 100 );
}
void CBSPRService::StopService()
{
	PostBSPRThreadMessage( m_dwFackID, WM_QUIT,(WPARAM)0,(LPARAM)0  );

	if( m_bBackGoundProcessRequied ) WakeUpDispatcher( -1 );

	::WaitForSingleObject( m_hThreadHandle, 500 );
}
LPCTSTR CBSPRService::GetServiceName()
{
	return _T("");
}
BOOL CBSPRService::IsExistSameRequestID( UINT32 uRequestID )
{
	CRequestProcessMethod* pMethod = CRequestProcessMethod::SearchMethod( &m_rbRequestMethod, uRequestID );

	return pMethod != NULL;
}
DWORD CBSPRService::GetServiceFackID()
{
	return m_dwFackID;
}
BOOL CBSPRService::IsBackGroundProcessRequied() const
{
	return m_bBackGoundProcessRequied;
}
void CBSPRService::SetBackGroundProcessRequied( BOOL bRequied )
{
    m_bBackGoundProcessRequied = bRequied;
}
void CBSPRService::BackGoundProcessing()
{

}
DWORD WINAPI CBSPRService::ThreadProc( LPVOID lpParameter )
{
	CBSPRService* pBaseService = (CBSPRService*)lpParameter;

	ServiceManager.RegistService( pBaseService );
	pBaseService->ServiceMain();
	ServiceManager.UnRegistService( pBaseService );

	return THREAD_EXIT_SUCCESS;
}
void CBSPRService::ServiceMain()
{
// 	sp<MsgPacket> msg = 0;
// 	for ( ; ; )
// 	{
// 		while ( (msg = m_curMsgQueue.PopMessagePacket()) != 0 )
// 		{
// 			if( msg->message == WM_QUIT )
// 			{
// 				HANDLE hEvent = (HANDLE)msg->lParam;
// 				::SetEvent( hEvent );
// 
// 				return;
// 			}
// 
// 			CBSPRService::TranslateBSPRMessage( msg );
// 
//             CBSPRService::DisPatchBSPRMessage( msg );
// 		}
// 	}

	MSG msg;
	BOOL bRet = FALSE;

	for ( ; ; )
	{
		__try
		{
			while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if( msg.message == WM_QUIT )
				{
					return;
				}
				CBSPRService::TranslateBSPRMessage( &msg );
				CBSPRService::DisPatchBSPRMessage( &msg );
			}
			if( IsBackGroundProcessRequied() )
			{
				BackGoundProcessing();
			}
			else 
			{
				WaitMessage();
			}

		}
		__finally
		{

		}
	}
}
void CBSPRService::TranslateBSPRMessage(  const BSPRMSG msg )
{
    
}
void CBSPRService::DisPatchBSPRMessage( const BSPRMSG msg  )
{
	UINT32 requestCode = (UINT32)msg->wParam;
	RMHDR* pHDR      = (RMHDR*)msg->lParam;
	UINT32 messageType =  msg->message;

	switch ( messageType )
	{
	case WM_SYNC_REQUEST:
		{
			CRequestProcessMethod* pMethod = CRequestProcessMethod::SearchMethod( &m_rbRequestMethod, requestCode );
			if ( NULL != pMethod )
			{
				pMethod->Invoke( this, pHDR );

				pHDR->ProcessFinish();
			}
		}
		break;
	case WM_ASYN_REQUEST:
		{
			CRequestProcessMethod* pMethod = CRequestProcessMethod::SearchMethod( &m_rbRequestMethod, requestCode );
			if ( NULL != pMethod )
			{
				pMethod->Invoke( this, pHDR );

				pHDR->Release();
			}
		}
		break;
	default:
		break;
	}
}

// void CBSPRService::MessageQueue::InsertMessagePacket( sp<MsgPacket>& packet )
// { 
// 	while( InterlockedCompareExchange( &locked, TRUE, FALSE ) == TRUE )
// 	{
// 
// 	}
// 
// 
// 	if( root == 0 ) 
// 	{
//         packet->last = packet->next = packet;
// 		root = packet;
// 	}
// 	else
// 	{
//        
// 		packet->last = root->last;
// 		packet->next = root;
// 		root = packet;
// 	}
// 
// 
// 
//     InterlockedCompareExchange( &locked, FALSE, TRUE );
// }
// 
// sp<MsgPacket> CBSPRService::MessageQueue::PopMessagePacket(  )
// {
// 	LONG localLock = InterlockedCompareExchange( &locked, TRUE, 2 );
// 	while( InterlockedCompareExchange( &locked, TRUE, FALSE ) == TRUE )
// 	{
// 
// 	}
// 
//     sp<MsgPacket> tail = 0;
// 	if( root != 0 && root != root->next )
// 	{
// 		tail = root->last;
// 		tail->last->next = root;
// 		root->last = tail->last;
// 	}
// 	else
// 	{
// 		tail = root;
// 		root = 0;
// 	}
// 
// 
// 	InterlockedCompareExchange( &locked, FALSE, TRUE );
// 
// 	return tail;
// 
// }

/**************************************************************************************/
#pragma warning( default:4311 )



