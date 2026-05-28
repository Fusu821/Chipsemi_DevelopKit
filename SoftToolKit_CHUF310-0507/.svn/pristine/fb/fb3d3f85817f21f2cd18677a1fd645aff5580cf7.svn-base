#include "HalUSBLayerService.h"
#include "HalUSBServiceParam.h"
#include "IComplexHalListener.h"
#include <stdio.h>
#define LOCK_MUTEX_BEGIN()
/*do{*/

#define LOCK_MUTEX_END()
/*}while(0);\*/


BEGIN_SERVICE_BIND( CHalUSBLayerService )
	BIND_REQUEST( HAL_BSPR_READ, HalSrvRead )
	BIND_REQUEST( HAL_BSPR_WRITE, HalSrvWrite )
	BIND_REQUEST( HAL_BSPR_IOCTRL, HalSrvIoCtrl )
	BIND_REQUEST( HAL_BSPR_CONNECTED, HalConnected )
	BIND_REQUEST( HAL_BSPR_SET_BACKGROUND, HalSrvSetBackGoundRequied )
	BIND_REQUEST( HAL_BSPR_REGIST_ANALYZER, HalSrvRegistAnalyzer )
	BIND_REQUEST( HAL_BSPR_SETDEVICEMANULY, HalSetDeviceManuly )
SERVICE_BIND_END()

	CHalUSBLayerService::CHalUSBLayerService( )
	:m_hDevice( NULL )
	,m_hEventIoCtrl( NULL )
	,m_hEventDevice( NULL )
	,m_pComplexListener( NULL )
{

}
CHalUSBLayerService::~CHalUSBLayerService()
{
}
void CHalUSBLayerService::StartService( int nPriority /*= 0*/  )
{
	CBSPRService::StartService( nPriority );

	TCHAR chName[50] = {0};
	transformat( chName, _T("%s-%d"), _T("IoCtrl"), GetServiceFackID() );
	m_hEventIoCtrl = ::CreateEvent( NULL, TRUE, FALSE, chName );

	transformat( chName, _T("%s-%d"), _T("IoDevice"), GetServiceFackID() );
	m_hEventDevice = ::CreateEvent( NULL, TRUE, FALSE, chName );
}
void CHalUSBLayerService::StopService()
{
	CBSPRService::StopService();

	CloseHandle( m_hEventIoCtrl );

	CloseHandle( m_hEventDevice );
}
void CHalUSBLayerService::BackGoundProcessing()
{
	//feet dog
}

void CHalUSBLayerService::HalSrvWrite( RMHDR* pHDR )
{
	if( !pHDR->IsKindOf( TYPENAME(HAL_SRV_WR_PARAM) ) )
	{
		//ASSERT(FALSE);
	}
	HAL_SRV_WR_PARAM* paramWR = reinterpret_cast<HAL_SRV_WR_PARAM*>( pHDR );

	paramWR->bResult = ERROR_CODE_OK;
	OVERLAPPED oWrite;
	memset( (char*)(&oWrite), 0, sizeof(OVERLAPPED) );
	oWrite.hEvent = m_hEventIoCtrl;
	ResetEvent( oWrite.hEvent );

	//DWORD uWrited = 0;

	if( DeviceIoControl( m_hDevice, IOCTL_USBPRINT_VENDOR_SET_COMMAND, paramWR->un.WRITE.writeBuffer, paramWR->un.WRITE.writeLen, NULL, 0, NULL/*&uWrited*/, &oWrite ) )
	{
 		paramWR->bResult = ERROR_CODE_OK;
	}
	else
	{
		if( GetLastError() == ERROR_IO_PENDING )
		{
			DWORD dwResult = ::WaitForSingleObject( oWrite.hEvent, USB_RW_TIMEOUT );
			if( dwResult == WAIT_OBJECT_0 )
			{
				paramWR->bResult = ERROR_CODE_OK;
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
void CHalUSBLayerService::HalSrvRead( RMHDR* pHDR )
{
	if( !pHDR->IsKindOf( TYPENAME(HAL_SRV_WR_PARAM) ) )
	{
		//ASSERT(FALSE);
	}
	HAL_SRV_WR_PARAM* paramWR = reinterpret_cast<HAL_SRV_WR_PARAM*>( pHDR );

	paramWR->bResult = ERROR_CODE_OK;
	OVERLAPPED oRead;
	memset( (char*)(&oRead), 0, sizeof(OVERLAPPED) );
	oRead.hEvent = m_hEventIoCtrl;
	ResetEvent( oRead.hEvent );

	unsigned int uReaded = 0;
	if( DeviceIoControl( m_hDevice, IOCTL_USBPRINT_VENDOR_GET_COMMAND, NULL, 0, paramWR->un.READ.readBuffer, paramWR->un.READ.readLen, &paramWR->un.READ.completed, &oRead ) )
	{
		paramWR->bResult = ERROR_CODE_OK;
	}
	else
	{
		if( GetLastError() == ERROR_IO_PENDING )
		{
			DWORD dwResult = ::WaitForSingleObject( oRead.hEvent, USB_RW_TIMEOUT );
			if( dwResult == WAIT_OBJECT_0 )
			{
				paramWR->bResult = ERROR_CODE_OK;
			}
			else
			{
				paramWR->bResult = ERROR_CODE_READ_USB_ERROR;
				CancelIo( m_hDevice );
			}
		}
		else
		{
			paramWR->bResult = ERROR_CODE_READ_USB_ERROR;
			CancelIo( m_hDevice );
		}
	}
}
void CHalUSBLayerService::HalSrvIoCtrl( RMHDR* pHDR )
{
	if( !pHDR->IsKindOf( TYPENAME(HAL_SRV_WR_PARAM) ) )
	{
		//ASSERT(FALSE);
	}
	HAL_SRV_WR_PARAM* paramWR = reinterpret_cast<HAL_SRV_WR_PARAM*>( pHDR );

	paramWR->bResult = ERROR_CODE_OK;
	OVERLAPPED oIoCtrl;
	memset( (char*)(&oIoCtrl), 0, sizeof(OVERLAPPED) );
	oIoCtrl.hEvent = m_hEventIoCtrl;
	ResetEvent( oIoCtrl.hEvent );

	if( DeviceIoControl( m_hDevice, IOCTL_USBPRINT_VENDOR_GET_COMMAND, paramWR->un.IOCTRL.writeBuffer, paramWR->un.IOCTRL.writeLen, paramWR->un.IOCTRL.readBuffer, paramWR->un.IOCTRL.readLen, &paramWR->un.IOCTRL.completed, &oIoCtrl ) )
	{
		paramWR->bResult = ERROR_CODE_OK;
	}
	else
	{
		if( GetLastError() == ERROR_IO_PENDING )
		{
			DWORD dwResult = ::WaitForSingleObject( oIoCtrl.hEvent, USB_RW_TIMEOUT );
			if( dwResult == WAIT_OBJECT_0 )
			{
				paramWR->bResult = ERROR_CODE_OK;
			}
			else
			{
				paramWR->bResult = ERROR_CODE_READ_USB_ERROR;
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
void CHalUSBLayerService::HalSrvSetBackGoundRequied( RMHDR* pHDR )
{
	if( !pHDR->IsKindOf( TYPENAME(HAL_SRV_SYNC_PARAM) ) )
	{
	}
	HAL_SRV_SYNC_PARAM* paramSync = reinterpret_cast<HAL_SRV_SYNC_PARAM*>( pHDR );

	SetBackGroundProcessRequied( (BOOL)paramSync->un.BACKGROUND.bBackGroundRequied );
}
void CHalUSBLayerService::HalConnected( RMHDR* pHDR )
{
	if( !pHDR->IsKindOf( TYPENAME(HAL_SRV_SYNC_PARAM) ) )
	{
		return;
	}

	HAL_SRV_SYNC_PARAM* paramSync = reinterpret_cast<HAL_SRV_SYNC_PARAM*>( pHDR );

	paramSync->un.DEVICESTATE.connected = (BOOL)(m_hDevice != NULL);

	paramSync->bResult = ERROR_CODE_OK;
}
void CHalUSBLayerService::HalSrvRegistAnalyzer( RMHDR* pHDR )
{
	if( !pHDR->IsKindOf( TYPENAME(HAL_SRV_SYNC_PARAM) ) )
	{
		return;
	}

	HAL_SRV_SYNC_PARAM* paramSync = reinterpret_cast<HAL_SRV_SYNC_PARAM*>( pHDR );
	paramSync->bResult = ERROR_CODE_INVALID_PARAM;

	m_pComplexListener = (IComplexHalListener*)paramSync->un.SETANALYZER.pHandler;

	paramSync->bResult = ERROR_CODE_OK;
}
void CHalUSBLayerService::HalSetDeviceManuly( RMHDR* pHDR )
{
	if( !pHDR->IsKindOf( TYPENAME(HAL_SRV_SYNC_PARAM) ) )
	{
		return;
	}

	HAL_SRV_SYNC_PARAM* paramSync = reinterpret_cast<HAL_SRV_SYNC_PARAM*>( pHDR );
	paramSync->bResult = ERROR_CODE_INVALID_PARAM;

	if( m_hDevice ) 
	{
		SetEvent( m_hEventIoCtrl );
		CloseHandle( m_hDevice );
	}

	m_hDevice = paramSync->un.SETDEVICE.hDevice;
	//m_iAllocateIndex = paramSync->un.SETDEVICE.index;

	if( m_hDevice )
	{
		SetEvent( m_hEventDevice );
	}

	SetBackGroundProcessRequied( FALSE );

	paramSync->bResult = ERROR_CODE_OK;
}





