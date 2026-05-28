#ifndef __HAL_PIPE_SRV_PROXY__
#define __HAL_PIPE_SRV_PROXY__
/**************************************************************************************/
#include "HalServiceInterface.h"
#include "HalPipeLayerService.h"
class CHalPipeServiceProxy : public IHalServiceInterface
{
public:
	CHalPipeServiceProxy();
	virtual ~CHalPipeServiceProxy();

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	virtual UCHAR _cdecl HalTryAttachLink( int type, ... );

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	virtual UCHAR _cdecl HalTryDetachLink( int type, ... );

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	virtual UCHAR Write( const unsigned char* buffer, unsigned int len = MAX_HAL_WR_LEN );

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	virtual UCHAR Read( unsigned char* buffer, unsigned int len = MAX_HAL_WR_LEN );

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	virtual UCHAR SetBackGoundRequied( bool bRequied, bool* oldState = NULL );

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	virtual UCHAR RegistAnalyzer( LPVOID handler );

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	virtual UCHAR RegistSevice( int iPriority = 0 );

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	virtual UCHAR UnRegistSevice(  );

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	virtual BOOL IsConnected(  );

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	virtual UCHAR HalClearDataQueueData(  );

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	virtual UCHAR HalTrySetDeviceManuly(  HANDLE hDevice, int iDeviceIndex = 0 );

private:
	CHalPipeLayerService m_HalSrvAddr;
};
/**************************************************************************************/
#endif