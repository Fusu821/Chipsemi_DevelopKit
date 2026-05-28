#include "HalUSBServiceProxy.h"
#include "HalUSBServiceParam.h"

IHalServiceInterface* AllocateHalSrvInterface()
{
	IHalServiceInterface* tempProxy = new CHalUSBServiceProxy();

	tempProxy->RegistSevice( THREAD_PRIORITY_NORMAL );

	return tempProxy;
}
void RestoreHalSrvInterface( IHalServiceInterface*& interfaceHal )
{
	if( NULL != interfaceHal )
	{
        interfaceHal->UnRegistSevice();
		delete interfaceHal;
		interfaceHal = NULL;
	}
}
CHalUSBServiceProxy::CHalUSBServiceProxy()
{
#ifdef LOG_BSPR_SERVICE
	m_LogHandle = NULL;
#endif
}
CHalUSBServiceProxy::~CHalUSBServiceProxy()
{

}
UCHAR CHalUSBServiceProxy::RegistSevice( int iPriority /*= 0*/ )
{
	m_HalSrvAddr.StartService( iPriority );

	return ERROR_CODE_OK;
}
UCHAR CHalUSBServiceProxy::UnRegistSevice(  )
{
    m_HalSrvAddr.StopService();

	return ERROR_CODE_OK;
}
UCHAR CHalUSBServiceProxy::HalTryAttachLink( int type, ... )
{
	HAL_SRV_SYNC_PARAM syncParam;
	//syncParam.un.OPENDEVICE.strName = txtName;
    m_HalSrvAddr.RequestAndWait( HAL_BSPR_OPENDEVICE, (RMHDR*)&syncParam );

    return syncParam.bResult;
}
UCHAR CHalUSBServiceProxy::HalTryDetachLink( int type, ... )
{
	HAL_SRV_SYNC_PARAM syncParam;
	//syncParam.un.CLOSEDEVICE.strName = txtName;
	m_HalSrvAddr.RequestAndWait( HAL_BSPR_CLOSE_DEVICE, (RMHDR*)&syncParam );

	return syncParam.bResult;
}
UCHAR CHalUSBServiceProxy::Write( const unsigned char* buffer, unsigned int len /*= MAX_HAL_WR_LEN*/ )
{
	//int iRetry = 100;
	HAL_SRV_WR_PARAM wrParam;
	wrParam.bResult = ERROR_CODE_INVALID_FILE;
	wrParam.un.WRITE.writeLen = len;
	wrParam.un.WRITE.writeBuffer = (unsigned char*)buffer;
	//memcpy_s( (char*)wrParam.un.WRITE.writeBuffer, MAX_HAL_WR_LEN, (const char*)buffer, len );

	m_HalSrvAddr.RequestAndWait( HAL_BSPR_WRITE, (RMHDR*)&wrParam );
	
	return wrParam.bResult;
}
UCHAR CHalUSBServiceProxy::Read( unsigned char* buffer, unsigned int len /*= MAX_HAL_WR_LEN*/, unsigned int* readedLen/* = NULL*/ )
{
	//int iRetry = 100;
 	HAL_SRV_WR_PARAM wrParam;
	wrParam.bResult = ERROR_CODE_INVALID_FILE;
	wrParam.un.READ.completed = 0;
	wrParam.un.READ.readLen = len;

	//do 
	//{
	    m_HalSrvAddr.RequestAndWait( HAL_BSPR_READ, (RMHDR*)&wrParam );
	//} while ( wrParam.un.READ.completed != len && iRetry-- );

	if( ERROR_CODE_OK == wrParam.bResult )
	{
		memcpy_s( (char*)buffer, len, (const char*)wrParam.un.READ.readBuffer, len );
		if( NULL != readedLen )  *readedLen = wrParam.un.READ.completed;
	}
 	
 
 	return wrParam.bResult;
}
UCHAR CHalUSBServiceProxy::IoCtrl( unsigned char* write, unsigned int writelen, unsigned char* read, unsigned int readlen, unsigned int* readedLen/* = NULL*/ )
{
	//int iRetry = 10;
	HAL_SRV_WR_PARAM wrParam;
	wrParam.bResult = ERROR_CODE_INVALID_FILE;
	wrParam.un.IOCTRL.completed = 0;
	wrParam.un.IOCTRL.writeLen = writelen;
	wrParam.un.IOCTRL.readLen = readlen + 8;
	wrParam.un.IOCTRL.writeBuffer = write;
	wrParam.un.IOCTRL.readBuffer = read;
	//memcpy_s( (char*)wrParam.un.IOCTRL.writeBuffer, MAX_HAL_WR_LEN, (const char*)write, writelen );

	//do 
	//{
		m_HalSrvAddr.RequestAndWait( HAL_BSPR_IOCTRL, (RMHDR*)&wrParam );
	//} while ( wrParam.un.IOCTRL.completed != readlen && iRetry-- );
	
	if( ERROR_CODE_OK == wrParam.bResult )
	{
		//memcpy_s( (char*)read, wrParam.un.IOCTRL.completed, (const char*)wrParam.un.IOCTRL.readBuffer, wrParam.un.IOCTRL.completed );
		if( NULL != readedLen )  *readedLen = wrParam.un.IOCTRL.completed;
	}
	

	return wrParam.bResult;
}
UCHAR CHalUSBServiceProxy::SetBackGoundRequied( bool bRequied, bool* oldState /*= NULL*/ )
{
	HAL_SRV_SYNC_PARAM syncParam;
	syncParam.un.BACKGROUND.bBackGroundRequied = bRequied;

	if( oldState ){
		m_HalSrvAddr.RequestAndWait( HAL_BSPR_SET_BACKGROUND, (RMHDR*)&syncParam );
		*oldState = syncParam.un.BACKGROUND.bOldRequiedState;
	}
	else
		m_HalSrvAddr.Request( HAL_BSPR_SET_BACKGROUND, (RMHDR*)&syncParam );

	return syncParam.bResult;
}
UCHAR CHalUSBServiceProxy::HalClearDataQueueData(  )
{
	HAL_SRV_SYNC_PARAM syncParam;
	m_HalSrvAddr.RequestAndWaitEx( HAL_BSPR_CLEAR_DATA_QUEUE, (RMHDR*)&syncParam );

	return syncParam.bResult;
}
BOOL CHalUSBServiceProxy::IsConnected(  )
{
	HAL_SRV_SYNC_PARAM syncParam;
	syncParam.un.DEVICESTATE.connected = FALSE;
	m_HalSrvAddr.RequestAndWait( HAL_BSPR_CONNECTED, (RMHDR*)&syncParam );

	return syncParam.un.DEVICESTATE.connected;
}
UCHAR CHalUSBServiceProxy::RegistAnalyzer( LPVOID handler )
{
	HAL_SRV_SYNC_PARAM syncParam;
	syncParam.un.SETANALYZER.pHandler = handler;
	m_HalSrvAddr.RequestAndWait( HAL_BSPR_REGIST_ANALYZER, (RMHDR*)&syncParam );

	return syncParam.bResult;
}
UCHAR CHalUSBServiceProxy::HalTrySetDeviceManuly(  HANDLE hDevice, int iDeviceIndex/* = 0*/ )
{
	HAL_SRV_SYNC_PARAM syncParam;
	syncParam.un.SETDEVICE.hDevice = hDevice;
	syncParam.un.SETDEVICE.index = iDeviceIndex;
	m_HalSrvAddr.RequestAndWait( HAL_BSPR_SETDEVICEMANULY, (RMHDR*)&syncParam );

	return syncParam.bResult;
}
DWORD CHalUSBServiceProxy::GetServiceFackID()
{
	return m_HalSrvAddr.GetServiceFackID();
}