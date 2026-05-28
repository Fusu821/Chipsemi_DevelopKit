#include "HalPipeServiceProxy.h"
#include "HalPipeServiceParam.h"
IHalServiceInterface* AllocateHalSrvInterface()
{
	IHalServiceInterface* tempProxy = new CHalPipeServiceProxy();

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
CHalPipeServiceProxy::CHalPipeServiceProxy()
{

}
CHalPipeServiceProxy::~CHalPipeServiceProxy()
{

}
UCHAR CHalPipeServiceProxy::RegistSevice( int iPriority /*= 0*/ )
{
	m_HalSrvAddr.StartService( iPriority );

	return ERROR_CODE_OK;
}
UCHAR CHalPipeServiceProxy::UnRegistSevice(  )
{
	m_HalSrvAddr.StopService();

	return ERROR_CODE_OK;
}
UCHAR CHalPipeServiceProxy::HalTryAttachLink( int type, ... )
{
	HAL_SRV_SYNC_PARAM syncParam;

	LPCTSTR pszName = NULL;

	va_list vaptr;
	va_start( vaptr, type );

	pszName = va_arg( vaptr, LPCTSTR );

	va_end( vaptr );

	syncParam.un.OPENDEVICE.ptrName = pszName;
	m_HalSrvAddr.RequestAndWait( HAL_BSPR_OPENDEVICE, (RMHDR*)&syncParam );

	return syncParam.bResult;
}
UCHAR CHalPipeServiceProxy::HalTryDetachLink( int type, ... )
{
	HAL_SRV_SYNC_PARAM syncParam;
	//syncParam.un.CLOSEDEVICE.strName = txtName;
	m_HalSrvAddr.RequestAndWait( HAL_BSPR_CLOSE_DEVICE, (RMHDR*)&syncParam );

	return syncParam.bResult;
}
UCHAR CHalPipeServiceProxy::Write( const unsigned char* buffer, unsigned int len /*= MAX_HAL_WR_LEN*/ )
{
	HAL_SRV_WR_PARAM wrParam;
    wrParam.un.WRITE.writeBuffer = buffer;
	wrParam.un.WRITE.writeLen = len;
	//memcpy_s( (char*)wrParam.un.WRITE.writeBuffer, MAX_HAL_WR_LEN, (const char*)buffer, len );
	m_HalSrvAddr.RequestAndWait( HAL_BSPR_WRITE, (RMHDR*)&wrParam );

	return wrParam.bResult;
}
UCHAR CHalPipeServiceProxy::Read( unsigned char* buffer, unsigned int len /*= MAX_HAL_WR_LEN*/ )
{
	HAL_SRV_WR_PARAM wrParam;
	while( len > 0 )
	{
		if( !m_HalSrvAddr.HasReceiveDataInQueue( COM_RW_TIMEOUT ) )
			return ERROR_CODE_WAIT_RESPONSE_TIMEOUT;

		wrParam.un.READ.readBuffer = buffer;
		wrParam.un.READ.readLen = len;
		m_HalSrvAddr.RequestAndWait( HAL_BSPR_READ, (RMHDR*)&wrParam );

		buffer += wrParam.un.READ.readed;
		len -= wrParam.un.READ.readed;
	}

	return wrParam.bResult;
}
UCHAR CHalPipeServiceProxy::SetBackGoundRequied( bool bRequied, bool* oldState /*= NULL*/ )
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
UCHAR CHalPipeServiceProxy::HalClearDataQueueData(  )
{
	HAL_SRV_SYNC_PARAM syncParam;
	m_HalSrvAddr.RequestAndWaitEx( HAL_BSPR_CLEAR_DATA_QUEUE, (RMHDR*)&syncParam );

	return syncParam.bResult;
}
BOOL CHalPipeServiceProxy::IsConnected(  )
{
	HAL_SRV_SYNC_PARAM syncParam;
	syncParam.un.DEVICESTATE.connected = FALSE;
	m_HalSrvAddr.RequestAndWait( HAL_BSPR_CONNECTED, (RMHDR*)&syncParam );

	return syncParam.un.DEVICESTATE.connected;
}
UCHAR CHalPipeServiceProxy::RegistAnalyzer( LPVOID handler )
{
	HAL_SRV_SYNC_PARAM syncParam;
	syncParam.un.SETANALYZER.pHandler = handler;
	m_HalSrvAddr.RequestAndWait( HAL_BSPR_REGIST_ANALYZER, (RMHDR*)&syncParam );

	return syncParam.bResult;
}
UCHAR CHalPipeServiceProxy::HalTrySetDeviceManuly(  HANDLE hDevice, int iDeviceIndex/* = 0*/ )
{
	HAL_SRV_SYNC_PARAM syncParam;
	syncParam.un.SETDEVICE.hDevice = hDevice;
	syncParam.un.SETDEVICE.index = iDeviceIndex;
	m_HalSrvAddr.RequestAndWait( HAL_BSPR_SETDEVICEMANULY, (RMHDR*)&syncParam );

	return syncParam.bResult;
}