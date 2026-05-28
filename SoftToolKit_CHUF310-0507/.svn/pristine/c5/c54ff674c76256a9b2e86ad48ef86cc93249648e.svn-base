#include "HalTcpServerService.h"
#include "HalTcpServerServiceParam.h"
#include "IComplexHalListener.h"
#include <stdio.h>
BEGIN_SERVICE_BIND( CHalTcpServerLayerService )
	BIND_REQUEST( HAL_BSPR_READ, HalSrvRead )
	BIND_REQUEST( HAL_BSPR_WRITE, HalSrvWrite )
	BIND_REQUEST( HAL_BSPR_CONNECTED, HalConnected )
	BIND_REQUEST( HAL_BSPR_CLOSE_DEVICE, HalTryDetachLink )
	BIND_REQUEST( HAL_BSPR_OPENDEVICE, HalTryAttachLink )
	BIND_REQUEST( HAL_BSPR_SET_BACKGROUND, HalSrvSetBackGoundRequied )
	BIND_REQUEST( HAL_BSPR_REGIST_ANALYZER, HalSrvRegistAnalyzer )
	BIND_REQUEST( HAL_BSPR_SETDEVICEMANULY, HalSetDeviceManuly )
	BIND_REQUEST( HAL_BSPR_CLEAR_DATA_QUEUE, HalClearDataQueueData )
SERVICE_BIND_END()

const unsigned int	DEFAULT_TCP_SERVER_SOCKET_LISTEN_QUEUE	= 1000000;
const unsigned int  MAX_WORKER_THREAD_COUNT                 = 500;
const unsigned int  DEFAULT_TCP_SERVER_ACCEPT_SOCKET_COUNT  = 300;
const unsigned int	DEFAULT_WORKER_THREAD_COUNT				= min((::SysGetNumberOfProcessors() * 2 + 2), MAX_WORKER_THREAD_COUNT);
const unsigned int	DEFAULT_FREE_SOCKETOBJ_POOL				= 150;
const unsigned int	DEFAULT_FREE_SOCKETOBJ_HOLD				= 600;
const unsigned int	DEFAULT_FREE_BUFFEROBJ_POOL				= 300;
const unsigned int	DEFAULT_FREE_BUFFEROBJ_HOLD				= 1200;
const unsigned int	DEFALUT_TCP_KEEPALIVE_TIME				= 20 * 1000;
const unsigned int	DEFALUT_TCP_KEEPALIVE_INTERVAL			= 5 * 1000;
const unsigned int  DEFAULT_FREE_SOCKETOBJ_LOCK_TIME        = 10 * 1000;
const unsigned int  DEFAULT_TCP_SOCKET_BUFFER_SIZE          = 4096;

#define  DEFAULT_IPV4_BIND_ADDRESS				_T("0.0.0.0")
#define  MAX_LISTEN_QUENE_ITEM                  3
#define  soListen                               m_soArray[0]
#define  evtiter_to_socketid(x)                 ((int)x + 1 - EVENT_FIXD_COUNT)       

CHalTcpServerLayerService::CHalTcpServerLayerService( )
	:m_flagClearDataQueue( FALSE )
	,m_enState( SS_STOPPED )
	,m_pComplexListener( NULL )
	,m_iEventCount(0)
	,m_lsSend( m_itPool )
	,m_lsRecv( m_itPool )
	,m_dwSocketListenQueue(30)
	,m_dwWorkerThreadCount(1)
	,m_dwAcceptSocketCount(0)
	,m_dwSocketBufferSize(DEFAULT_TCP_SOCKET_BUFFER_SIZE)
{
	for(int index = 0; index < sizeof(m_soArray)/sizeof(SOCKET); index++)
	{
		m_soArray[index] = INVALID_SOCKET;
	}
}
CHalTcpServerLayerService::~CHalTcpServerLayerService()
{
}
void CHalTcpServerLayerService::StartService( int nPriority /*= 0*/  )
{
	CBSPRService::StartService( nPriority );

	m_iEventCount = 0;

	TCHAR chName[50] = {0};
	transformat( chName, _T("%s-%d"), _T("WakeUp"), GetServiceFackID() );
	HANDLE evWakeUp = ::CreateEvent( NULL, TRUE, FALSE, chName );
	m_eventQueues[EVENT_WAKE_UP] = evWakeUp;
	m_iEventCount++;

	transformat( chName, _T("%s-%d"), _T("Send"), GetServiceFackID() );
	HANDLE evSdBuffer = ::CreateEvent( NULL, TRUE, FALSE, chName );
	m_eventQueues[EVENT_SEND_DATA] = evSdBuffer;
	m_iEventCount++;

	transformat( chName, _T("%s-%d"), _T("Receive"), GetServiceFackID() );
	HANDLE evRcBuffer = ::CreateEvent( NULL, TRUE, FALSE, chName );
	m_eventQueues[EVENT_RECV_DATA] = evRcBuffer;
	m_iEventCount++;

	WSAEVENT evtSock = WSACreateEvent();
	m_eventQueues[EVENT_SOCK_LISTEN] = evtSock;
	m_iEventCount++;
}
void CHalTcpServerLayerService::StopService()
{
	CBSPRService::StopService();

	FireStop( GetServiceFackID() );

	Stop();

// 	CloseHandle( m_evWakeUp );
// 
// 	CloseHandle( m_evSdBuffer );
// 
// 	CloseHandle( m_evRcBuffer );

}
void CHalTcpServerLayerService::WakeUpDispatcher( UINT32 hostRequest )
{
	if( m_flagClearDataQueue )
	{
		//m_lsRecv.Clear();
		//ResetEvent( m_evRcBuffer );

		m_flagClearDataQueue = FALSE;
	}

	::SetEvent( m_eventQueues[EVENT_WAKE_UP] );
}
BOOL CHalTcpServerLayerService::HasReceiveDataInQueue( UINT32 queryTimeout )
{
	return WAIT_OBJECT_0 == ::WaitForSingleObject( m_eventQueues[EVENT_RECV_DATA], queryTimeout );
}
void CHalTcpServerLayerService::BackGoundProcessing()
{
	if( m_enState == SS_STARTED || m_enState == SS_STARTING )
	{
		DWORD dwRet = WSAWaitForMultipleEvents(m_iEventCount,m_eventQueues,FALSE,WSA_INFINITE,FALSE);

		if(WSA_WAIT_EVENT_0 == dwRet)
		{
			ResetEvent( m_eventQueues[EVENT_WAKE_UP] );
		}
		else if(WSA_WAIT_EVENT_0 + 1 == dwRet)  //send data
		{
			if( !SendData( m_soArray[1] ) )
				if( m_enState == SS_STARTED || m_enState == SS_STARTING )
					ResetClient();

			ResetEvent( m_eventQueues[EVENT_SEND_DATA] );
		}
		else if(WSA_WAIT_EVENT_0 + 2 == dwRet)  //recv data
		{

		}
		else
		{
			if( !ProcessNetworkEvent(dwRet) )
				if( m_enState == SS_STARTED || m_enState == SS_STARTING )
					ResetClient();
		}
	}
}
void CHalTcpServerLayerService::HalSrvWrite( RMHDR* pHDR )
{
	if( !pHDR->IsKindOf( TYPENAME(HAL_SRV_WR_PARAM) ) )
	{
		return;
	}

	HAL_SRV_WR_PARAM* paramSync = reinterpret_cast<HAL_SRV_WR_PARAM*>( pHDR );

	if( m_enState == SS_STARTED || m_enState == SS_STARTING )
	{
		m_lsRecv.Clear();
		ResetEvent( m_eventQueues[EVENT_RECV_DATA] );
		paramSync->bResult = SendInternal( paramSync->un.WRITE.writeBuffer, paramSync->un.WRITE.writeLen );
	}
	else
		paramSync->bResult = ERROR_CODE_WRITE_USB_ERROR; 
}
void CHalTcpServerLayerService::HalSrvRead( RMHDR* pHDR )
{
	if( !pHDR->IsKindOf( TYPENAME(HAL_SRV_WR_PARAM) ) )
	{
		return;
	}

	HAL_SRV_WR_PARAM* paramSync = reinterpret_cast<HAL_SRV_WR_PARAM*>( pHDR );

	if( m_enState == SS_STARTED || m_enState == SS_STARTING )
	{
		paramSync->bResult = ReadCatchData( paramSync->un.READ.readBuffer, paramSync->un.READ.readLen, paramSync->un.READ.readed );
		if( m_lsRecv.Size() <= 0 ) ::ResetEvent( m_eventQueues[EVENT_RECV_DATA] );
	}
	else
		paramSync->bResult = ERROR_CODE_READ_USB_ERROR; 
}
void CHalTcpServerLayerService::HalSrvSetBackGoundRequied( RMHDR* pHDR )
{
	if( !pHDR->IsKindOf( TYPENAME(HAL_SRV_SYNC_PARAM) ) )
	{
		return;
	}

	HAL_SRV_SYNC_PARAM* paramSync = reinterpret_cast<HAL_SRV_SYNC_PARAM*>( pHDR );

	SetBackGroundProcessRequied( (BOOL)paramSync->un.BACKGROUND.bBackGroundRequied );
}
void CHalTcpServerLayerService::HalClearDataQueueData( RMHDR* pHDR )
{
	if( !pHDR->IsKindOf( TYPENAME(HAL_SRV_SYNC_PARAM) ) )
	{
		return;
	}

	HAL_SRV_SYNC_PARAM* paramSync = reinterpret_cast<HAL_SRV_SYNC_PARAM*>( pHDR );

	m_flagClearDataQueue = TRUE;

	paramSync->bResult = ERROR_CODE_OK;
}
void CHalTcpServerLayerService::HalConnected( RMHDR* pHDR )
{
	if( !pHDR->IsKindOf( TYPENAME(HAL_SRV_SYNC_PARAM) ) )
	{
		return;
	}

	HAL_SRV_SYNC_PARAM* paramSync = reinterpret_cast<HAL_SRV_SYNC_PARAM*>( pHDR );

	paramSync->bResult = ERROR_CODE_OK;
}
void CHalTcpServerLayerService::HalTryAttachLink( RMHDR* pHDR )
{
	if( !pHDR->IsKindOf( TYPENAME(HAL_SRV_SYNC_PARAM) ) )
	{
		return;
	}

	HAL_SRV_SYNC_PARAM* paramSync = reinterpret_cast<HAL_SRV_SYNC_PARAM*>( pHDR );
	paramSync->bResult = ERROR_CODE_INVALID_PARAM;

	if( !CheckParams() || !CheckStarting() )   
		return;

	paramSync->bResult = ERROR_CODE_DEVICE_OPENED;

	if( CreateListenSocket(paramSync->un.OPENDEVICE.ptrIpAddress, paramSync->un.OPENDEVICE.port) )
	{
		m_rcBuffer.Malloc( m_dwSocketBufferSize );
		SetBackGroundProcessRequied( TRUE );
		paramSync->bResult = ERROR_CODE_OK;
		return;
	}	

	ResetClient();
}
void CHalTcpServerLayerService::HalTryDetachLink( RMHDR* pHDR )
{
	if( !pHDR->IsKindOf( TYPENAME(HAL_SRV_SYNC_PARAM) ) )
	{
		return;
	}

	HAL_SRV_SYNC_PARAM* paramSync = reinterpret_cast<HAL_SRV_SYNC_PARAM*>( pHDR );
	paramSync->bResult = ERROR_CODE_INVALID_PARAM;

	if( !CheckStoping() )    return;

	Stop();

	paramSync->bResult = ERROR_CODE_OK;
}
void CHalTcpServerLayerService::HalSrvRegistAnalyzer( RMHDR* pHDR )
{
	if( !pHDR->IsKindOf( TYPENAME(HAL_SRV_SYNC_PARAM) ) )
	{
		return;
	}

	HAL_SRV_SYNC_PARAM* paramSync = reinterpret_cast<HAL_SRV_SYNC_PARAM*>( pHDR );

	m_pComplexListener = (IComplexHalListener*)paramSync->un.PSETANALYZER.pAnayzer;

	FireStart( GetServiceFackID() );

	paramSync->bResult = ERROR_CODE_OK;
}
void CHalTcpServerLayerService::HalSetDeviceManuly( RMHDR* pHDR )
{
	if( !pHDR->IsKindOf( TYPENAME(HAL_SRV_SYNC_PARAM) ) )
	{
		return;
	}

	HAL_SRV_SYNC_PARAM* paramSync = reinterpret_cast<HAL_SRV_SYNC_PARAM*>( pHDR );
	paramSync->bResult = ERROR_CODE_INVALID_PARAM;
}
bool CHalTcpServerLayerService::CheckStarting()
{
	CSpinLock locallock( m_csState );

	if(m_enState == SS_STOPPED)
		m_enState = SS_STARTING;
	else
	{
		return false;
	}

	return true;
}

LPCTSTR CHalTcpServerLayerService::GetHostIpAddress()
{
	static TCHAR szIpAddr[20];
	if (SOCKET_ERROR != gethostname(szIpAddr, sizeof(szIpAddr)))
	{
		struct hostent* hp;
		hp = gethostbyname(szIpAddr);
		if (hp != NULL && hp->h_addr_list[0] != NULL)
		{
			// IPv4: Address is four bytes (32-bit)
			if ( hp->h_length < 4)
				return false;

			szIpAddr[0] = 0;
			// IPv4: Create Address string
			sprintf_s(szIpAddr,sizeof(szIpAddr), "%u.%u.%u.%u",
				(UINT)(((PBYTE) hp->h_addr_list[0])[0]),
				(UINT)(((PBYTE) hp->h_addr_list[0])[1]),
				(UINT)(((PBYTE) hp->h_addr_list[0])[2]),
				(UINT)(((PBYTE) hp->h_addr_list[0])[3]));

			return szIpAddr;
		}

	}
	return NULL;
}

bool CHalTcpServerLayerService::CreateListenSocket( LPCTSTR lpszBindAddress, unsigned short uPort )
{
	bool bOk = false;

	if(NULL == lpszBindAddress || 0 == lengthof(lpszBindAddress))
		lpszBindAddress = GetHostIpAddress();
	if(NULL == lpszBindAddress || 0 == lengthof(lpszBindAddress))
		lpszBindAddress = DEFAULT_IPV4_BIND_ADDRESS;

	SOCKADDR_IN addr;

	if(::sockaddr_A_2_IN(AF_INET, lpszBindAddress, uPort, addr))
	{
		m_usFamily = addr.sin_family;
		soListen = socket(m_usFamily, SOCK_STREAM, IPPROTO_TCP);
		if(soListen != INVALID_SOCKET)
		{
			BOOL bOnOff	= (m_dwKeepAliveTime > 0 && m_dwKeepAliveInterval > 0);
			::SSO_KeepAliveVals(soListen, bOnOff, m_dwKeepAliveTime, m_dwKeepAliveInterval);
			::SSO_NoBlock(soListen);

			if(::bind(soListen, (SOCKADDR*)&addr, sizeof(SOCKADDR_IN)) != SOCKET_ERROR)
			{
				FirePrepareListen(soListen);
				if(::listen(soListen, MAX_LISTEN_QUENE_ITEM) != SOCKET_ERROR)
				{
					WSAEventSelect(soListen, m_eventQueues[EVENT_SOCK_LISTEN],FD_ACCEPT | FD_CLOSE);
					bOk = true;
				}
			}
			else
			{
				DWORD dwErr = ::GetLastError();
				bOk = false;
			}
		}
	}

	return bOk;
}
bool CHalTcpServerLayerService::CheckStoping()
{
	CSpinLock locallock(m_csState);

	if(m_enState == SS_STARTED || m_enState == SS_STARTING)
		m_enState = SS_STOPPING;
	else
	{
		return false;
	}

	return true;
}
void CHalTcpServerLayerService::ResetClient( bool bClear /* = true */ )
{
	if( bClear )
	{
		m_rcBuffer.Free();

		m_lsSend.Clear();
		m_lsRecv.Clear();
		m_itPool.Clear();

		for(int index = 0; index < (int)m_iEventCount; index++)
		{
			ResetEvent( m_eventQueues[index] );
		}
	}

	m_iEventCount = 4;
	for(int index = 1; index < MAX_ACCEPT_SOCKET_NUM + 1; index++)
	{
		if(INVALID_SOCKET != m_soArray[index])
		{
			closesocket(m_soArray[index]);
			m_soArray[index] = INVALID_SOCKET;
		}
	}
	for(int index = EVENT_FIXD_COUNT; index < MAX_WAIT_EVENT_QUEUE_LEN; index++)
	{
		if(NULL == m_eventQueues[index])
		{
			CloseHandle( m_eventQueues[index] );
			m_eventQueues[index] = NULL;
		}
	}

	m_enState = SS_STOPPED;
}
int CHalTcpServerLayerService::SendInternal( const BYTE* pWriteBuffer, int iLen )
{
	int iRet = ERROR_CODE_OK;

	assert( pWriteBuffer );

	if( iLen > 0 )
	{
		m_lsSend.Cat( pWriteBuffer, iLen );
	}
	else
		iRet = ERROR_CODE_INVALID_PARAM;

	::SetEvent( m_eventQueues[EVENT_SEND_DATA] );

	return iRet;
}
bool CHalTcpServerLayerService::ProcessNetworkEvent(DWORD eventID)
{
	bool bContinue = true;
	WSANETWORKEVENTS events;

	if(eventID >= MAX_WAIT_EVENT_QUEUE_LEN) return false;
	if(eventID < EVENT_SOCK_LISTEN) return false;

	int iRet = ::WSAEnumNetworkEvents( m_soArray[evtiter_to_socketid(eventID)], m_eventQueues[eventID], &events );

	if( iRet == SOCKET_ERROR )
	{
		int code = ::WSAGetLastError();
		::WSAResetEvent( m_eventQueues[eventID] );
		FireError( GetServiceFackID(), code );

		bContinue = false;
	}

	if( bContinue && events.lNetworkEvents & FD_ACCEPT)
	{
		int iCode = events.iErrorCode[FD_ACCEPT_BIT];

		if( iCode == 0 )
		{
			sockaddr_in    client;
			int sz = sizeof(sockaddr_in);
			SOCKET acp = accept(soListen,(sockaddr*)&client, &sz);
			if( INVALID_SOCKET != acp )
			{
				WSAEVENT evtClient = WSACreateEvent();
				WSAEventSelect(acp, evtClient, FD_READ|FD_WRITE|FD_CLOSE);
				if(m_iEventCount < MAX_WAIT_EVENT_QUEUE_LEN)
				{
					m_soArray[evtiter_to_socketid(m_iEventCount)] = acp;
					m_eventQueues[m_iEventCount++] = evtClient;
				}
			}
		}
		else
		{
			FireError( GetServiceFackID(), iCode );

			bContinue = true;
		}
	}

	if( bContinue && events.lNetworkEvents & FD_READ )
	{
		int iCode = events.iErrorCode[FD_READ_BIT];

		if( iCode == 0 )
			bContinue = ReadData( m_soArray[evtiter_to_socketid(eventID)] );
		else
		{
			FireError( GetServiceFackID(), iCode );

			bContinue = true;
		}
	}

	if( bContinue && events.lNetworkEvents & FD_WRITE )
	{
		int iCode = events.iErrorCode[FD_WRITE_BIT];

		if( iCode == 0 )
			bContinue = SendData( m_soArray[evtiter_to_socketid(eventID)] );
		else
		{
			FireError( GetServiceFackID(), iCode );

			bContinue = true;
		}
	}

	if( bContinue && events.lNetworkEvents & FD_CLOSE )
	{
		closesocket( m_soArray[evtiter_to_socketid(eventID)] );
		CloseHandle( m_eventQueues[eventID] );

		for(int index = 0; index < (int)(m_iEventCount - 1); index++)
		{
			if(index >= (int)eventID)
			{
				m_soArray[evtiter_to_socketid(index)] = m_soArray[evtiter_to_socketid(index + 1)];
				m_eventQueues[index] = m_eventQueues[index + 1];
			}
		}

		m_soArray[evtiter_to_socketid(m_iEventCount - 1)] = INVALID_SOCKET;
		m_eventQueues[m_iEventCount - 1] = NULL;
		m_iEventCount = m_iEventCount - 1;
		 
		bContinue = true;
	}

	return bContinue;	
}
bool CHalTcpServerLayerService::ReadData( SOCKET so )
{
 	while ( true )
 	{
 		int iReceive = recv( so, (char*)(BYTE*)m_rcBuffer, m_dwSocketBufferSize, 0 );
 		if( iReceive > 0 )
 		{
 			if( HR_IGNORE == FireReceive( GetServiceFackID(), m_rcBuffer, iReceive ) )
 			{
 				m_lsRecv.Cat( m_rcBuffer, iReceive );
 				SetEvent( m_eventQueues[EVENT_RECV_DATA] );
 			}
 		}
 		else if( iReceive == SOCKET_ERROR )
 		{
 			int iCode = ::WSAGetLastError();
 
 			if( iCode == WSAEWOULDBLOCK )
 				break;
 			else
 			{
 				FireError( GetServiceFackID(), iCode );
 				return false;
 			}
 		}
 		else if( iReceive == 0 )
 		{
 			FireClose( 0 );
 			return false;
 		}
 		else
 			assert( FALSE );
 	}

	return true;
}
bool CHalTcpServerLayerService::SendData( SOCKET so )
{
	bool bOK = true;
	if(INVALID_SOCKET == so) return false;
	
	while( true )
	{
		TItemPtr itPtr( m_itPool, GetSendBuffer() );
		if( !itPtr.IsValid() )  break;

		assert( !itPtr->IsEmpty() );
		bOK = DoSendData( so, itPtr );
		if( bOK )
		{
			if( !itPtr->IsEmpty() )
			{
				CCriSecLock localLock( m_csSend );
				m_lsSend.PushFront( itPtr.Detach() );

				break;
			}
		}
		else
			break;
	}

	return bOK;
}
TItem* CHalTcpServerLayerService::GetSendBuffer()
{
	TItem* pItem = NULL;

	if(m_lsSend.Size() > 0)
	{
		CCriSecLock locallock(m_csSend);

		if(m_lsSend.Size() > 0)
			pItem = m_lsSend.PopFront();
	}

	return pItem;
}
TItem* CHalTcpServerLayerService::GetRecvBuffer()
{
	TItem* pItem = NULL;

	if( m_lsRecv.Size() > 0 )
		pItem = m_lsRecv.PopFront();

	return pItem;
}
bool CHalTcpServerLayerService::DoSendData( SOCKET so, TItem* pItem )
{
	while( !pItem->IsEmpty() )
	{
		int rc = 0;

		{
			CCriSecLock locallock(m_csSend);

			rc = send( so, (char*)pItem->Ptr(), min(pItem->Size(), (int)m_dwSocketBufferSize), 0 );
		}

		if(rc > 0)
		{
			FireSend( GetServiceFackID(), pItem->Ptr(), rc );

			pItem->Reduce(rc);
		}
		else if(rc == SOCKET_ERROR)
		{
			int code = ::WSAGetLastError();

			if(code == WSAEWOULDBLOCK)
				break;
			else
			{
				FireError( GetServiceFackID(), code );

				return FALSE;
			}
		}
		else
			assert(FALSE);
	}

	return TRUE;
}
//bool CHalTcpServerLayerService::StartAccept()
//{
//	bool isOK = true;
//
//	if(::CreateIoCompletionPort((HANDLE)m_soListen, m_hCompletePort, m_soListen, 0))
//	{
//		//m_iRemainAcceptSockets = m_dwAcceptSocketCount;
//
//		for(DWORD i = 0; i < m_dwAcceptSocketCount; i++)
//			::PostIocpAccept(m_hCompletePort);
//	}
//	else
//	{
//		//SetLastError(SE_SOCKE_ATTACH_TO_CP, __FUNCTION__, ::GetLastError());
//		isOK = false;
//	}
//
//	return isOK;
//}
void CHalTcpServerLayerService::Stop()
{
	if( !CheckStoping() )    return;

	ResetClient(true);

	closesocket(soListen);
	soListen = INVALID_SOCKET;

	CloseHandle( m_eventQueues[EVENT_SOCK_LISTEN] );
	CloseHandle( m_eventQueues[EVENT_RECV_DATA] );
	CloseHandle( m_eventQueues[EVENT_SEND_DATA] );
	CloseHandle( m_eventQueues[EVENT_WAKE_UP] );

	m_iEventCount = 0;


	m_enState = SS_STOPPED;
}
int CHalTcpServerLayerService::ReadCatchData( const BYTE* bufferRead, unsigned int readLen, unsigned int& readedLen )
{
	int iRet = ERROR_CODE_OK;

	readedLen = 0;
	int iRemain = readLen;
	while( iRemain > 0 )
	{
		TItemPtr itPtr( m_itPool, GetRecvBuffer() );
		if( !itPtr ) break;

		assert( !itPtr->IsEmpty() );

		int size = min( itPtr->Size(), iRemain );
		memcpy_s( (void*)bufferRead, size, itPtr->Ptr(), size );

		if( size > 0 )
		{
			itPtr->Reduce( size );
			if( !itPtr->IsEmpty() ) 
				m_lsRecv.PushFront( itPtr.Detach() );
		}

		iRemain -= size;
		readedLen += size;
	}

	return iRet;
}