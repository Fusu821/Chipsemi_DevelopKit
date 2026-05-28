#ifndef __HAL_HID_IIC_LAYER_PROXY__
#define __HAL_HID_IIC_LAYER_PROXY__
/**************************************************************************************/
#include "HalServiceInterface.h"
#include "HalHIDIICLayerService.h"
class CHalHIDIICServiceProxy : public IHalServiceInterface
{
public:
	CHalHIDIICServiceProxy();
	virtual ~CHalHIDIICServiceProxy();

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	//static IHalServiceInterface* GetHalSrvInterface();

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
	virtual UCHAR Read( unsigned char* buffer, unsigned int len = MAX_HAL_WR_LEN, unsigned int* readedLen = NULL );

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	virtual UCHAR IoCtrl( unsigned char* write, unsigned int writelen, unsigned char* read, unsigned int readlen, unsigned int* readedLen = NULL );

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

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	virtual DWORD GetServiceFackID();

private:
	CHalHIDIICLayerService m_HalSrvAddr;

#ifdef LOG_BSPR_SERVICE
    HMODULE m_LogHandle;
#endif
};

/**************************************************************************************/
#endif
