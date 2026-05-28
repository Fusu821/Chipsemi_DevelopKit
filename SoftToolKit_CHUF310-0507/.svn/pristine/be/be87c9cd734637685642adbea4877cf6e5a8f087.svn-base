#ifndef __HAL_USB_SRV_INTERFACE__
#define __HAL_USB_SRV_INTERFACE__
/**************************************************************************************/
#define WIN32_LEAN_AND_MEAN	
#include "Macro.h"
//#include "RefBase.h"
#include <Windows.h>

class HAL_SERVICE_API IHalServiceInterface
{
public:
	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	virtual ~IHalServiceInterface(){}

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	virtual UCHAR _cdecl HalTryAttachLink( int type, ... ) = 0;

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	virtual UCHAR _cdecl HalTryDetachLink( int type, ... ) = 0;


	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	virtual UCHAR Write( const unsigned char* buffer, unsigned int len = MAX_HAL_WR_LEN ) = 0;

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	virtual UCHAR Read( unsigned char* buffer, unsigned int len = MAX_HAL_WR_LEN, unsigned int* readedLen = NULL ) = 0;

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	virtual UCHAR IoCtrl( unsigned char* write, unsigned int writelen, unsigned char* read, unsigned int readlen, unsigned int* readedLen = NULL ) = 0;

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	virtual UCHAR SetBackGoundRequied( bool bRequied, bool* oldState = NULL ) = 0;

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	virtual UCHAR RegistAnalyzer( LPVOID handler ) = 0;

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	virtual UCHAR RegistSevice( int iPriority = 0 ) = 0;

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	virtual UCHAR UnRegistSevice(  ) = 0;

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	virtual BOOL IsConnected(  ) = 0;

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	virtual UCHAR HalClearDataQueueData(  ) = 0;

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	virtual UCHAR HalTrySetDeviceManuly( HANDLE hDevice, int iDeviceIndex = 0 ) = 0;

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	virtual DWORD GetServiceFackID() = 0;
};

HAL_SERVICE_CSTYLE_API IHalServiceInterface* AllocateHalSrvInterface( );
HAL_SERVICE_CSTYLE_API void RestoreHalSrvInterface( IHalServiceInterface*& interfaceHal );


/**************************************************************************************/
#endif