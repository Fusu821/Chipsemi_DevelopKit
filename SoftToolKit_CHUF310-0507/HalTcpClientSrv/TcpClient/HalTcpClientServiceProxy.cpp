#include "HalTcpClientServiceProxy.h"
#include "HalTcpClientServiceParam.h"
IHalServiceInterface* AllocateHalSrvInterface()
{
	IHalServiceInterface* tempProxy = new CHalTcpClientServiceProxy();

	tempProxy->RegistSevice( THREAD_PRIORITY_NORMAL );

	return tempProxy;
}
void RestoreHalSrvInterface( IHalServiceInterface*& interfaceHal )
{
	if( NULL != interfaceHal )
	{
		interfaceHal->HalTryDetachLink( 0 );
		interfaceHal->UnRegistSevice();
		delete interfaceHal;
		interfaceHal = NULL;
	}
}
CHalTcpClientServiceProxy::CHalTcpClientServiceProxy()
{

}
CHalTcpClientServiceProxy::~CHalTcpClientServiceProxy()
{

}
UCHAR CHalTcpClientServiceProxy::RegistSevice( int iPriority /*= 0*/ )
{
	m_HalSrvAddr.StartService( iPriority );

	return ERROR_CODE_OK;
}
UCHAR CHalTcpClientServiceProxy::UnRegistSevice(  )
{
	m_HalSrvAddr.StopService();

	return ERROR_CODE_OK;
}
UCHAR CHalTcpClientServiceProxy::HalTryAttachLink( int type, ... )
{
	HAL_SRV_SYNC_PARAM syncParam;

	LPCTSTR pszAddress = NULL;
	unsigned short portNum = 0;
	unsigned char bAsyn = 0;
	unsigned short portSource = 5816;

	va_list vaptr;
	va_start( vaptr, type );

	pszAddress = va_arg( vaptr, LPCTSTR );
	portNum = va_arg( vaptr, unsigned short );
	bAsyn = va_arg( vaptr, unsigned char );
	portSource = va_arg( vaptr, unsigned short );

	va_end( vaptr );

	syncParam.un.OPENDEVICE.ptrIpAddress = pszAddress;
	syncParam.un.OPENDEVICE.port = portNum;
	syncParam.un.OPENDEVICE.aSync = bAsyn;
	syncParam.un.OPENDEVICE.source = portSource;
	m_HalSrvAddr.RequestAndWait( HAL_BSPR_OPENDEVICE, (RMHDR*)&syncParam );

	return syncParam.bResult;
}
UCHAR CHalTcpClientServiceProxy::HalTryDetachLink( int type, ... )
{
	HAL_SRV_SYNC_PARAM syncParam;
	//syncParam.un.CLOSEDEVICE.strName = txtName;
	m_HalSrvAddr.RequestAndWait( HAL_BSPR_CLOSE_DEVICE, (RMHDR*)&syncParam );

	return syncParam.bResult;
}
UCHAR CHalTcpClientServiceProxy::Write( const unsigned char* buffer, unsigned int len /*= MAX_HAL_WR_LEN*/ )
{
	HAL_SRV_WR_PARAM wrParam;
	wrParam.un.WRITE.writeBuffer = buffer;
	wrParam.un.WRITE.writeLen = len;
	m_HalSrvAddr.RequestAndWait( HAL_BSPR_WRITE, (RMHDR*)&wrParam );

	return wrParam.bResult;
}
UCHAR CHalTcpClientServiceProxy::Read( unsigned char* buffer, unsigned int len /*= MAX_HAL_WR_LEN*/, unsigned int* readedLen/* = NULL */)
{
	HAL_SRV_WR_PARAM wrParam;
	wrParam.un.READ.readed = 0;
	while( len > 0 )
	{
		if( !m_HalSrvAddr.HasReceiveDataInQueue( wrParam.un.READ.readed ? (TCP_WR_TIMEOUT >> 5) : TCP_WR_TIMEOUT ) )
			return ERROR_CODE_WAIT_RESPONSE_TIMEOUT;

		wrParam.un.READ.readBuffer = buffer;
		wrParam.un.READ.readLen = len;
		m_HalSrvAddr.RequestAndWait( HAL_BSPR_READ, (RMHDR*)&wrParam );

		buffer += wrParam.un.READ.readed;
		len -= wrParam.un.READ.readed;
		if(readedLen) *readedLen += wrParam.un.READ.readed;
	}

	return wrParam.bResult;
}
UCHAR CHalTcpClientServiceProxy::IoCtrl( unsigned char* write, unsigned int writelen, unsigned char* read, unsigned int readlen, unsigned int* readedLen/* = NULL*/ )
{
	//int iRetry = 10;
	HAL_SRV_WR_PARAM wrParam;
	wrParam.bResult = ERROR_CODE_INVALID_FILE;
	wrParam.un.WRITE.writeBuffer = write;
	wrParam.un.WRITE.writeLen = writelen;

	m_HalSrvAddr.RequestAndWait( HAL_BSPR_WRITE, (RMHDR*)&wrParam );
	if(ERROR_CODE_OK == wrParam.bResult)
	{
		if( !m_HalSrvAddr.HasReceiveDataInQueue( TCP_WR_TIMEOUT ) )
			return ERROR_CODE_WAIT_RESPONSE_TIMEOUT;

		wrParam.bResult = ERROR_CODE_INVALID_FILE;
		wrParam.un.READ.readBuffer = read;
		wrParam.un.READ.readLen = readlen;

		m_HalSrvAddr.RequestAndWait( HAL_BSPR_READ, (RMHDR*)&wrParam );
		if( NULL != readedLen )  *readedLen = wrParam.un.READ.readed;

		//if( ERROR_CODE_OK == wrParam.bResult )
		//{
		//	memcpy_s( (char*)read, wrParam.un.READ.readed, (const char*)wrParam.un.READ.readBuffer, wrParam.un.READ.readed );
		//	if( NULL != readedLen )  *readedLen = wrParam.un.READ.readed;
		//}
	}

	if(readlen != wrParam.un.READ.readed)
	{
		int indx = 0;
	}

	return wrParam.bResult;

// 	wrParam.un.IOCTRL.completed = 0;
// 	wrParam.un.IOCTRL.writeLen = writelen;
// 	wrParam.un.IOCTRL.readLen = readlen + 8;
// 	memcpy_s( (char*)wrParam.un.IOCTRL.writeBuffer, MAX_HAL_WR_LEN, (const char*)write, writelen );

// 	//do 
// 	//{
// 	m_HalSrvAddr.RequestAndWait( HAL_BSPR_IOCTRL, (RMHDR*)&wrParam );
// 	//} while ( wrParam.un.IOCTRL.completed != readlen && iRetry-- );
// 
// 	if( ERROR_CODE_OK == wrParam.bResult )
// 	{
// 		memcpy_s( (char*)read, wrParam.un.IOCTRL.completed, (const char*)wrParam.un.IOCTRL.readBuffer, wrParam.un.IOCTRL.completed );
// 		if( NULL != readedLen )  *readedLen = wrParam.un.IOCTRL.completed;
// 	}


	return wrParam.bResult;
}
UCHAR CHalTcpClientServiceProxy::SetBackGoundRequied( bool bRequied, bool* oldState /*= NULL*/ )
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
UCHAR CHalTcpClientServiceProxy::HalClearDataQueueData(  )
{
	HAL_SRV_SYNC_PARAM syncParam;
	m_HalSrvAddr.RequestAndWaitEx( HAL_BSPR_CLEAR_DATA_QUEUE, (RMHDR*)&syncParam );

	return syncParam.bResult;
}
BOOL CHalTcpClientServiceProxy::IsConnected(  )
{
	HAL_SRV_SYNC_PARAM syncParam;
	syncParam.un.DEVICESTATE.connected = FALSE;
	m_HalSrvAddr.RequestAndWait( HAL_BSPR_CONNECTED, (RMHDR*)&syncParam );

	return syncParam.un.DEVICESTATE.connected;
}
UCHAR CHalTcpClientServiceProxy::RegistAnalyzer( LPVOID handler )
{
	HAL_SRV_SYNC_PARAM syncParam;
	syncParam.un.SETANALYZER.pAnayzer = handler;
	m_HalSrvAddr.RequestAndWait( HAL_BSPR_REGIST_ANALYZER, (RMHDR*)&syncParam );

	return syncParam.bResult;
}
UCHAR CHalTcpClientServiceProxy::HalTrySetDeviceManuly(  HANDLE hDevice, int iDeviceIndex/* = 0*/ )
{
	HAL_SRV_SYNC_PARAM syncParam;
	m_HalSrvAddr.RequestAndWait( HAL_BSPR_SETDEVICEMANULY, (RMHDR*)&syncParam );

	return syncParam.bResult;
}
DWORD CHalTcpClientServiceProxy::GetServiceFackID()
{
	return m_HalSrvAddr.GetServiceFackID();
}