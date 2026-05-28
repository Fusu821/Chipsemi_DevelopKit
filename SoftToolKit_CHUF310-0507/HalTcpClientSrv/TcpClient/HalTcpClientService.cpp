#include "HalTcpClientService.h"
#include "HalTcpClientServiceParam.h"
#include "IComplexHalListener.h"
#include <stdio.h>
BEGIN_SERVICE_BIND( CHalTcpClientLayerService )
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
CHalTcpClientLayerService::CHalTcpClientLayerService( )
:m_evWakeUp( NULL )
,m_evSocket( NULL )
,m_evSdBuffer( NULL )
,m_evRcBuffer( NULL )
,m_soClient( INVALID_SOCKET )
,m_bAsyncConnect( 0 )
,m_flagClearDataQueue( FALSE )
,m_enState( SS_STOPPED )
,m_pComplexListener( NULL )
,m_lsSend( m_itPool )
,m_lsRecv( m_itPool )
,m_dwSocketBufferSize(DEFAULT_TCP_SOCKET_BUFFER_SIZE)
{
}
CHalTcpClientLayerService::~CHalTcpClientLayerService()
{
}
void CHalTcpClientLayerService::StartService( int nPriority /*= 0*/  )
{
	CBSPRService::StartService( nPriority );

	TCHAR chName[50] = {0};
	transformat( chName, _T("%s-%d"), _T("WakeUp"), GetServiceFackID() );
	m_evWakeUp = ::CreateEvent( NULL, TRUE, FALSE, chName );
	transformat( chName, _T("%s-%d"), _T("Send"), GetServiceFackID() );
	m_evSdBuffer = ::CreateEvent( NULL, TRUE, FALSE, chName );
	transformat( chName, _T("%s-%d"), _T("Receive"), GetServiceFackID() );
	m_evRcBuffer = ::CreateEvent( NULL, TRUE, FALSE, chName );
}
void CHalTcpClientLayerService::StopService()
{
	CBSPRService::StopService();

	FireStop( GetServiceFackID() );

	CloseHandle( m_evWakeUp );

	CloseHandle( m_evSdBuffer );
	
	CloseHandle( m_evRcBuffer );

}
void CHalTcpClientLayerService::WakeUpDispatcher( UINT32 hostRequest )
{
	if( m_flagClearDataQueue )
	{
		m_lsRecv.Clear();
		ResetEvent( m_evRcBuffer );

		m_flagClearDataQueue = FALSE;
	}

	::SetEvent( m_evWakeUp );
}
BOOL CHalTcpClientLayerService::HasReceiveDataInQueue( UINT32 queryTimeout )
{
	return WAIT_OBJECT_0 == ::WaitForSingleObject( m_evRcBuffer, queryTimeout );
}
void CHalTcpClientLayerService::BackGoundProcessing()
{
	if( m_enState == SS_STARTED || m_enState == SS_STARTING )
	{
        HANDLE hEventArray[] = { m_evSocket, m_evSdBuffer, m_evWakeUp };

		DWORD dwRet = ::WSAWaitForMultipleEvents( 3, hEventArray, FALSE, WSA_INFINITE, FALSE );

		if( dwRet == WSA_WAIT_EVENT_0 )
		{
			if( !ProcessNetworkEvent() )
				if( m_enState == SS_STARTED || m_enState == SS_STARTING )
					Stop();
		}
		else if( dwRet == WSA_WAIT_EVENT_0 + 1 )
		{
			if( !SendData() )
				if( m_enState == SS_STARTED || m_enState == SS_STARTING )
					Stop();

			ResetEvent( m_evSdBuffer );
		}
		else if( dwRet == WSA_WAIT_EVENT_0 + 2 )
		{
			//::WaitMessage();
			ResetEvent( m_evWakeUp );
		}
		else
		{
			assert( FALSE );
		}
	}
}
void CHalTcpClientLayerService::HalSrvWrite( RMHDR* pHDR )
{
	if( !pHDR->IsKindOf( TYPENAME(HAL_SRV_WR_PARAM) ) )
	{
		return;
	}

    HAL_SRV_WR_PARAM* paramSync = reinterpret_cast<HAL_SRV_WR_PARAM*>( pHDR );

	if( m_enState == SS_STARTED || m_enState == SS_STARTING )
	{
		m_lsRecv.Clear();
		ResetEvent( m_evRcBuffer );
		paramSync->bResult = SendInternal( paramSync->un.WRITE.writeBuffer, paramSync->un.WRITE.writeLen );
	}
	else
		paramSync->bResult = ERROR_CODE_WRITE_USB_ERROR; 
}
void CHalTcpClientLayerService::HalSrvRead( RMHDR* pHDR )
{
	if( !pHDR->IsKindOf( TYPENAME(HAL_SRV_WR_PARAM) ) )
	{
		return;
	}

	HAL_SRV_WR_PARAM* paramSync = reinterpret_cast<HAL_SRV_WR_PARAM*>( pHDR );

	if( m_enState == SS_STARTED || m_enState == SS_STARTING )
	{
		paramSync->bResult = ReadCatchData( paramSync->un.READ.readBuffer, paramSync->un.READ.readLen, paramSync->un.READ.readed );
		if( m_lsRecv.Size() <= 0 ) ::ResetEvent( m_evRcBuffer );
	}
	else
		paramSync->bResult = ERROR_CODE_READ_USB_ERROR; 
}
void CHalTcpClientLayerService::HalSrvSetBackGoundRequied( RMHDR* pHDR )
{
	if( !pHDR->IsKindOf( TYPENAME(HAL_SRV_SYNC_PARAM) ) )
	{
		return;
	}

	HAL_SRV_SYNC_PARAM* paramSync = reinterpret_cast<HAL_SRV_SYNC_PARAM*>( pHDR );

	SetBackGroundProcessRequied( (BOOL)paramSync->un.BACKGROUND.bBackGroundRequied );
}
void CHalTcpClientLayerService::HalClearDataQueueData( RMHDR* pHDR )
{
	if( !pHDR->IsKindOf( TYPENAME(HAL_SRV_SYNC_PARAM) ) )
	{
		return;
	}

	HAL_SRV_SYNC_PARAM* paramSync = reinterpret_cast<HAL_SRV_SYNC_PARAM*>( pHDR );

	m_flagClearDataQueue = TRUE;

	paramSync->bResult = ERROR_CODE_OK;
}
void CHalTcpClientLayerService::HalConnected( RMHDR* pHDR )
{
	if( !pHDR->IsKindOf( TYPENAME(HAL_SRV_SYNC_PARAM) ) )
	{
		return;
	}

	HAL_SRV_SYNC_PARAM* paramSync = reinterpret_cast<HAL_SRV_SYNC_PARAM*>( pHDR );

	paramSync->bResult = ERROR_CODE_OK;
}
void CHalTcpClientLayerService::HalTryAttachLink( RMHDR* pHDR )
{
	if( !pHDR->IsKindOf( TYPENAME(HAL_SRV_SYNC_PARAM) ) )
	{
		return;
	}

	HAL_SRV_SYNC_PARAM* paramSync = reinterpret_cast<HAL_SRV_SYNC_PARAM*>( pHDR );
	paramSync->bResult = ERROR_CODE_INVALID_PARAM;

	if( !CheckParams() || !CheckStarting() )   
		return;

	m_bAsyncConnect = paramSync->un.OPENDEVICE.aSync;

	if( CreateClientSocket () )
	{
		m_rcBuffer.Malloc( m_dwSocketBufferSize );

		if( ConnectToServer( paramSync->un.OPENDEVICE.ptrIpAddress, paramSync->un.OPENDEVICE.port, paramSync->un.OPENDEVICE.source) )
		{
			SetBackGroundProcessRequied( TRUE );
			paramSync->bResult = ERROR_CODE_OK;
		}
		else
			paramSync->bResult = ERROR_CODE_DEVICE_OPENED;
	}
	else
		paramSync->bResult = ERROR_CODE_DEVICE_OPENED;
}
void CHalTcpClientLayerService::HalTryDetachLink( RMHDR* pHDR )
{
	if( !pHDR->IsKindOf( TYPENAME(HAL_SRV_SYNC_PARAM) ) )
	{
		return;
	}

	HAL_SRV_SYNC_PARAM* paramSync = reinterpret_cast<HAL_SRV_SYNC_PARAM*>( pHDR );
	paramSync->bResult = ERROR_CODE_INVALID_PARAM;
	
	if( !CheckStoping() )    return;

	if( m_evSocket != NULL )
	{
		::WSACloseEvent( m_evSocket );
		m_evSocket = NULL;
	}

	if( m_soClient != INVALID_SOCKET )
	{
		shutdown( m_soClient, SD_SEND );
		closesocket( m_soClient );
		m_soClient = INVALID_SOCKET;
	}

	Reset();

	paramSync->bResult = ERROR_CODE_OK;
}
void CHalTcpClientLayerService::HalSrvRegistAnalyzer( RMHDR* pHDR )
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
void CHalTcpClientLayerService::HalSetDeviceManuly( RMHDR* pHDR )
{
	if( !pHDR->IsKindOf( TYPENAME(HAL_SRV_SYNC_PARAM) ) )
	{
		return;
	}

	HAL_SRV_SYNC_PARAM* paramSync = reinterpret_cast<HAL_SRV_SYNC_PARAM*>( pHDR );
	paramSync->bResult = ERROR_CODE_INVALID_PARAM;
}
bool CHalTcpClientLayerService::CheckStarting()
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
bool CHalTcpClientLayerService::CreateClientSocket()
{
	m_soClient = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
	if( INVALID_SOCKET != m_soClient )
	{
		BOOL bOnOff	= (m_dwKeepAliveTime > 0 && m_dwKeepAliveInterval > 0);
		::SSO_KeepAliveVals( m_soClient, bOnOff, m_dwKeepAliveTime, m_dwKeepAliveInterval );

		m_evSocket = ::WSACreateEvent();
		assert( m_evSocket != WSA_INVALID_EVENT );

		return true;
	}
	return false;
}
bool CHalTcpClientLayerService::ConnectToServer( LPCTSTR pszRemoteAddress, unsigned short uPort, unsigned short uPortSource )
{
	bool bOk = false;
	TCHAR szAddress[50] = {0};
	int iAddressLen = sizeof( szAddress ) / sizeof(TCHAR);

	if( !GetIPAddress( pszRemoteAddress, szAddress, iAddressLen ) )
	{
		::WSASetLastError( WSAEADDRNOTAVAIL );
		return false;
	}

	SOCKADDR_IN addr;
	if( !sockaddr_A_2_IN( AF_INET, szAddress, uPort, addr ) )
	{
		::WSASetLastError( WSAEADDRNOTAVAIL );
		return false;
	}

	//if((short)uPortSource > 0)
	//{
	//	SOCKADDR_IN mine;
	//	if( !sockaddr_A_2_IN( AF_INET, szAddress, uPortSource, mine ) )
	//	{
	//		::WSASetLastError( WSAEADDRNOTAVAIL );
	//		return false;
	//	}

	//	if(::bind(m_soClient, (SOCKADDR*)&mine, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	//	{
	//		::WSASetLastError( WSAEADDRNOTAVAIL );
	//		return false;
	//	}
	//}

	if( m_bAsyncConnect )
	{
		if( SOCKET_ERROR != WSAEventSelect( m_soClient, m_evSocket, FD_CONNECT | FD_CLOSE ) )
		{
			int iRet = ::connect( m_soClient, (SOCKADDR*)&addr, sizeof(SOCKADDR_IN) );
			bOk = ( (iRet == NOERROR) || (iRet == SOCKET_ERROR && WSAEWOULDBLOCK == WSAGetLastError()) );
		}
	}
	else
	{
		if( SOCKET_ERROR != ::connect( m_soClient, (SOCKADDR*)&addr, sizeof(SOCKADDR_IN) ) )
		{
			if( SOCKET_ERROR != WSAEventSelect( m_soClient, m_evSocket, FD_READ | FD_WRITE | FD_CLOSE ) )
			{
				FireConnect( GetServiceFackID() );

				m_enState = SS_STARTED;
				bOk = true;
			}
		}
		else
		{
			DWORD dwErr = ::GetLastError();
			bOk = false;
		}
	}

	return bOk;
}
bool CHalTcpClientLayerService::CheckStoping()
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
void CHalTcpClientLayerService::Reset( bool bClear /* = true */ )
{
	if( bClear )
	{
		m_rcBuffer.Free();

		ResetEvent( m_evRcBuffer );
		ResetEvent( m_evSdBuffer );

		//m_evBuffer.Reset();
		//m_evWakeUp.Reset();
		m_lsSend.Clear();
		m_lsRecv.Clear();
		m_itPool.Clear();
	}

	m_enState = SS_STOPPED;
}
int CHalTcpClientLayerService::SendInternal( const BYTE* pWriteBuffer, int iLen )
{
	int iRet = ERROR_CODE_OK;

	assert( pWriteBuffer );

	if( iLen > 0 )
	{
		m_lsSend.Cat( pWriteBuffer, iLen );
	}
	else
		iRet = ERROR_CODE_INVALID_PARAM;

	::SetEvent( m_evSdBuffer );

	return iRet;
}
bool CHalTcpClientLayerService::ProcessNetworkEvent()
{
	bool bContinue = true;
	WSANETWORKEVENTS events;

	int iRet = ::WSAEnumNetworkEvents( m_soClient, m_evSocket, &events );

	if( iRet == SOCKET_ERROR )
	{
		int code = ::WSAGetLastError();
		::WSAResetEvent( m_evSocket );
		FireError( GetServiceFackID(), code );

		bContinue = false;
	}

	if( bContinue && events.lNetworkEvents & FD_READ )
	{
		int iCode = events.iErrorCode[FD_READ_BIT];

		if( iCode == 0 )
			bContinue = ReadData(  );
		else
		{
			FireError( GetServiceFackID(), iCode );

			bContinue = false;
		}
	}

	if( bContinue && events.lNetworkEvents & FD_WRITE )
	{
		int iCode = events.iErrorCode[FD_WRITE_BIT];

		if( iCode == 0 )
			bContinue = SendData();
		else
		{
			FireError( GetServiceFackID(), iCode );

			bContinue = false;
		}
	}

	if( m_bAsyncConnect && bContinue && events.lNetworkEvents & FD_CONNECT )
	{
		int iCode = events.iErrorCode[FD_CONNECT_BIT];

		if( iCode == 0 )
		{
			if( SOCKET_ERROR != WSAEventSelect( m_soClient, m_evSocket, FD_READ | FD_WRITE | FD_CLOSE ) )
			{
				m_enState = SS_STARTED;
				FireConnect( 0 );
			}
			else
				iCode = ::WSAGetLastError();
		}

		if( iCode != 0 )
		{
			FireError( GetServiceFackID(), iCode );

			bContinue = false;
		}
	}

	if( bContinue && events.lNetworkEvents & FD_CLOSE )
	{
		int iCode = events.iErrorCode[FD_CLOSE_BIT];

		if( iCode == 0 )
			FireClose( 0 );
		else
		{
			EnSocketOperation enOperation = events.lNetworkEvents & FD_READ ? SO_RECEIVE :
				(
				   events.lNetworkEvents & FD_WRITE ? SO_SEND :
				  (events.lNetworkEvents & FD_CONNECT ? SO_CONNECT : SO_UNKNOWN)
				);
		    FireError( GetServiceFackID(), iCode );
		}

		bContinue = false;
	}

	return bContinue;	
}
bool CHalTcpClientLayerService::ReadData()
{
	while ( true )
	{
		int iReceive = recv( m_soClient, (char*)(BYTE*)m_rcBuffer, m_dwSocketBufferSize, 0 );
		if( iReceive > 0 )
		{
			if( HR_IGNORE == FireReceive( GetServiceFackID(), m_rcBuffer, iReceive ) )
			{
				m_lsRecv.Cat( m_rcBuffer, iReceive );
				SetEvent( m_evRcBuffer );
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
bool CHalTcpClientLayerService::SendData()
{
	bool bOK = true;

	while( true )
	{
		TItemPtr itPtr( m_itPool, GetSendBuffer() );
		if( !itPtr.IsValid() )  break;

		assert( !itPtr->IsEmpty() );
		bOK = DoSendData( itPtr );
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
TItem* CHalTcpClientLayerService::GetSendBuffer()
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
TItem* CHalTcpClientLayerService::GetRecvBuffer()
{
	TItem* pItem = NULL;

	if( m_lsRecv.Size() > 0 )
		pItem = m_lsRecv.PopFront();

	return pItem;
}
bool CHalTcpClientLayerService::DoSendData( TItem* pItem )
{
	while( !pItem->IsEmpty() )
	{
		int rc = 0;

		{
			CCriSecLock locallock(m_csSend);

			rc = send( m_soClient, (char*)pItem->Ptr(), min(pItem->Size(), (int)m_dwSocketBufferSize), 0 );
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
void CHalTcpClientLayerService::Stop()
{
	if( !CheckStoping() )    return;

	if( m_evSocket != NULL )
	{
		::WSACloseEvent( m_evSocket );
		m_evSocket = NULL;
	}

	if( m_soClient != INVALID_SOCKET )
	{
		shutdown( m_soClient, SD_SEND );
		closesocket( m_soClient );
		m_soClient = INVALID_SOCKET;
	}

	Reset();
}
int CHalTcpClientLayerService::ReadCatchData( const BYTE* bufferRead, unsigned int readLen, unsigned int& readedLen )
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