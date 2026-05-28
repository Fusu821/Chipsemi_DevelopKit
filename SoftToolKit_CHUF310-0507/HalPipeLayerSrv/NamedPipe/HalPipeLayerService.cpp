#include "HalPipeLayerService.h"
#include "HalPipeServiceParam.h"
#include "IComplexHalListener.h"
#define MAX_PILE_READ_BUFFER  1024 * 2
#define MAX_PILE_WRITE_BUFFER 1024 * 2

BEGIN_SERVICE_BIND( CHalPipeLayerService )
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

const unsigned int  DEFAULT_PIPE_SERVICE_BUFFER_SIZE          = 4096;
CHalPipeLayerService::CHalPipeLayerService( )
:m_hDevice( NULL )
,m_hEventWrite( NULL )
,m_hEventRead( NULL )
,m_evWakeUp( NULL )
,m_evRcBuffer( NULL )
,m_bWaitDataComming(FALSE)
,m_flagClearDataQueue(FALSE)
,m_pComplexListener(NULL)
,m_lsRecv( m_itPool )
,m_dwPipeBufferSize(DEFAULT_PIPE_SERVICE_BUFFER_SIZE)
{
// 	m_curReaded.flag = 0;
// 	m_curReaded.root = 0;
// #ifdef _DEBUG
// 	m_curReaded.packetNum = 0;
// #endif
}
CHalPipeLayerService::~CHalPipeLayerService()
{
}
void CHalPipeLayerService::StartService( int nPriority /*= 0*/  )
{
	CBSPRService::StartService( nPriority );

	TCHAR chName[50] = {0};
	transformat( chName, 50, _T("%s-%d"), _T("Write"), GetServiceFackID() );
	m_hEventWrite = ::CreateEvent( NULL, TRUE, FALSE, chName );
	transformat( chName, 50, _T("%s-%d"), _T("Read"), GetServiceFackID() );
	m_hEventRead = ::CreateEvent( NULL, TRUE, FALSE, chName );
	transformat( chName, 50, _T("%s-%d"), _T("WakeUp"), GetServiceFackID() );
	m_evWakeUp = ::CreateEvent( NULL, TRUE, FALSE, chName );
	transformat( chName, 50, _T("%s-%d"), _T("Queue"), GetServiceFackID() );
	m_evRcBuffer = ::CreateEvent( NULL, TRUE, FALSE, chName );
}
void CHalPipeLayerService::StopService()
{
	CBSPRService::StopService();

	FireStop( GetServiceFackID() );

	CloseHandle( m_evWakeUp );

	CloseHandle( m_hEventWrite );

	CloseHandle( m_hEventRead );

	CloseHandle( m_evRcBuffer );
}
void CHalPipeLayerService::WakeUpDispatcher( UINT hostRequest )
{
	if( m_flagClearDataQueue )
	{
		m_lsRecv.Clear();
		::ResetEvent( m_evRcBuffer );

		m_flagClearDataQueue = FALSE;
	}

	::SetEvent( m_evWakeUp );
}
BOOL CHalPipeLayerService::HasReceiveDataInQueue( UINT queryTimeout )
{
	return WAIT_OBJECT_0 == ::WaitForSingleObject( m_evRcBuffer, queryTimeout );
}
void CHalPipeLayerService::MakeReadInternal( )
{
	//OVERLAPPED oRead;
	memset( (char*)(&m_oRead), 0, sizeof(OVERLAPPED) );
	m_oRead.hEvent = m_hEventRead;
	ResetEvent( m_oRead.hEvent );

	if( ReadFile( m_hDevice, m_rcBuffer, MAX_PIPE_WR_LEN, NULL, &m_oRead ) )
	{
		m_bWaitDataComming = FALSE;

		if( m_pComplexListener && HR_IGNORE == FireReceive( GetServiceFackID(), m_rcBuffer, (unsigned int)m_oRead.InternalHigh ) ) 
		{
			m_lsRecv.Cat( m_rcBuffer, (int)m_oRead.InternalHigh );

			SetEvent( m_evRcBuffer );
		}
	}
	else
	{
		m_bWaitDataComming = TRUE;
	}
}
void CHalPipeLayerService::BackGoundProcessing()
{
	if( !m_bWaitDataComming )
	{
		MakeReadInternal();
	}

	if( m_bWaitDataComming )
	{
		HANDLE hEventArray[] = { m_oRead.hEvent, m_evWakeUp };

		DWORD dwRet = ::WaitForMultipleObjects( sizeof(hEventArray)/sizeof(HANDLE), hEventArray, FALSE, INFINITE );
		if( dwRet == WAIT_OBJECT_0 )
		{ 
			m_bWaitDataComming = FALSE;

			if( 0 == m_oRead.InternalHigh )
			{
                CloseHandle( m_hDevice );
				m_hDevice = NULL;
			}
			else if( m_pComplexListener && HR_IGNORE == FireReceive( GetServiceFackID(), m_rcBuffer, (unsigned int)m_oRead.InternalHigh ) ) 
			{
				m_lsRecv.Cat( m_rcBuffer, (int)m_oRead.InternalHigh );

				SetEvent( m_evRcBuffer );
			}
		}
		else if( dwRet == WAIT_OBJECT_0 + 1 )
		{
			::ResetEvent( m_evWakeUp );
			//::WaitMessage();
		}
		else
		{
			int index = 0;
		}
	}
}
void CHalPipeLayerService::HalSrvWrite( RMHDR* pHDR )
{
	if( !pHDR->IsKindOf( TYPENAME(HAL_SRV_WR_PARAM) ) )
	{
		//ASSERT(FALSE);
	}
	HAL_SRV_WR_PARAM* paramWR = reinterpret_cast<HAL_SRV_WR_PARAM*>( pHDR );

	paramWR->bResult = ERROR_CODE_OK;
	OVERLAPPED oWrite;
	memset( (char*)(&oWrite), 0, sizeof(OVERLAPPED) );
	oWrite.hEvent = m_hEventWrite;
	ResetEvent( oWrite.hEvent );
	//CancelIo( m_hDevice );

	if( WriteFile( m_hDevice, paramWR->un.WRITE.writeBuffer, paramWR->un.WRITE.writeLen, NULL, &oWrite ) )
	{
		paramWR->bResult = ERROR_CODE_OK;

		FireSend( GetServiceFackID(), paramWR->un.WRITE.writeBuffer, paramWR->un.WRITE.writeLen );
	}
	else
	{
		if( GetLastError() == ERROR_IO_PENDING )
		{
			DWORD dwResult = ::WaitForSingleObject( oWrite.hEvent, COM_RW_TIMEOUT );
			if( dwResult == WAIT_OBJECT_0 )
			{
				paramWR->bResult = ERROR_CODE_OK;

				FireSend( GetServiceFackID(), paramWR->un.WRITE.writeBuffer, paramWR->un.WRITE.writeLen );
			}
			else
			{
				paramWR->bResult = ERROR_CODE_WRITE_USB_ERROR;
				CancelIo( m_hDevice );
			}
		}
		else
		{
			paramWR->bResult = ERROR_CODE_WRITE_USB_ERROR;
			CancelIo( m_hDevice );
		}
	}
}
void CHalPipeLayerService::HalSrvRead( RMHDR* pHDR )
{
	if( !pHDR->IsKindOf( TYPENAME(HAL_SRV_WR_PARAM) ) )
	{
		//ASSERT(FALSE);
	}
	HAL_SRV_WR_PARAM* paramWR = reinterpret_cast<HAL_SRV_WR_PARAM*>( pHDR );

	if( m_hDevice == NULL )  
	{
		paramWR->bResult = ERROR_CODE_READ_USB_ERROR;
	}
	else
	{
		paramWR->bResult = ReadCatchData( paramWR->un.READ.readBuffer, paramWR->un.READ.readLen, paramWR->un.READ.readed );
		if( m_lsRecv.Size() <= 0 ) ::ResetEvent( m_evRcBuffer );
	}
}
void CHalPipeLayerService::HalSrvSetBackGoundRequied( RMHDR* pHDR )
{
	if( !pHDR->IsKindOf( TYPENAME(HAL_SRV_SYNC_PARAM) ) )
	{
	}
	HAL_SRV_SYNC_PARAM* paramSync = reinterpret_cast<HAL_SRV_SYNC_PARAM*>( pHDR );

	SetBackGroundProcessRequied( (BOOL)paramSync->un.BACKGROUND.bBackGroundRequied );
}
void CHalPipeLayerService::HalClearDataQueueData( RMHDR* pHDR )
{
	if( !pHDR->IsKindOf( TYPENAME(HAL_SRV_SYNC_PARAM) ) )
	{
		return;
	}

	HAL_SRV_SYNC_PARAM* paramSync = reinterpret_cast<HAL_SRV_SYNC_PARAM*>( pHDR );

	m_flagClearDataQueue = TRUE;

	paramSync->bResult = ERROR_CODE_OK;
}
void CHalPipeLayerService::HalConnected( RMHDR* pHDR )
{
	if( !pHDR->IsKindOf( TYPENAME(HAL_SRV_SYNC_PARAM) ) )
	{
		return;
	}

	HAL_SRV_SYNC_PARAM* paramSync = reinterpret_cast<HAL_SRV_SYNC_PARAM*>( pHDR );

	paramSync->un.DEVICESTATE.connected = (BOOL)(m_hDevice != NULL);

	paramSync->bResult = ERROR_CODE_OK;
}
void CHalPipeLayerService::HalTryAttachLink( RMHDR* pHDR )
{
	if( !pHDR->IsKindOf( TYPENAME(HAL_SRV_SYNC_PARAM) ) )
	{
		return;
	}

	HAL_SRV_SYNC_PARAM* paramSync = reinterpret_cast<HAL_SRV_SYNC_PARAM*>( pHDR );

	if( m_hDevice )
	{
		::CloseHandle( m_hDevice );
	}
	m_hDevice = INVALID_HANDLE_VALUE;

	BOOL waitResult = ::WaitNamedPipe( paramSync->un.OPENDEVICE.ptrName, 500 );

	if( waitResult )
	{
		m_rcBuffer.Malloc( m_dwPipeBufferSize );
		m_hDevice = ::CreateFile( paramSync->un.OPENDEVICE.ptrName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL );
		DWORD dwMode = PIPE_READMODE_MESSAGE;   
		::SetNamedPipeHandleState( m_hDevice, &dwMode, NULL, NULL );    
		SetBackGroundProcessRequied( TRUE );
	}

	if( INVALID_HANDLE_VALUE != m_hDevice )
	{
		FireConnect( GetServiceFackID() );
		paramSync->bResult = ERROR_CODE_OK;
	}
}
void CHalPipeLayerService::HalTryDetachLink( RMHDR* pHDR )
{
	if( !pHDR->IsKindOf( TYPENAME(HAL_SRV_SYNC_PARAM) ) )
	{
		return;
	}

	HAL_SRV_SYNC_PARAM* paramSync = reinterpret_cast<HAL_SRV_SYNC_PARAM*>( pHDR );

	CloseHandle( m_hDevice );

	m_hDevice = NULL;

	FireClose( GetServiceFackID() );
}
void CHalPipeLayerService::HalSrvRegistAnalyzer( RMHDR* pHDR )
{
	if( !pHDR->IsKindOf( TYPENAME(HAL_SRV_SYNC_PARAM) ) )
	{
		return;
	}

	HAL_SRV_SYNC_PARAM* paramSync = reinterpret_cast<HAL_SRV_SYNC_PARAM*>( pHDR );
	paramSync->bResult = ERROR_CODE_INVALID_PARAM;

	m_pComplexListener = (IComplexHalListener*)paramSync->un.SETANALYZER.pHandler;

	FireStart( GetServiceFackID() );

	paramSync->bResult = ERROR_CODE_OK;
}
void CHalPipeLayerService::HalSetDeviceManuly( RMHDR* pHDR )
{
	if( !pHDR->IsKindOf( TYPENAME(HAL_SRV_SYNC_PARAM) ) )
	{
		return;
	}

	HAL_SRV_SYNC_PARAM* paramSync = reinterpret_cast<HAL_SRV_SYNC_PARAM*>( pHDR );
	paramSync->bResult = ERROR_CODE_INVALID_PARAM;

	if( m_hDevice ) 
	{
		CloseHandle( m_hDevice );
	}

	m_hDevice = paramSync->un.SETDEVICE.hDevice;
	SetBackGroundProcessRequied( TRUE );

	paramSync->bResult = ERROR_CODE_OK;
}
TItem* CHalPipeLayerService::GetRecvBuffer()
{
	TItem* pItem = NULL;

	if( m_lsRecv.Size() > 0 )
		pItem = m_lsRecv.PopFront();

	return pItem;
}
int CHalPipeLayerService::ReadCatchData( const BYTE* bufferRead, unsigned int readLen, unsigned int& readedLen )
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