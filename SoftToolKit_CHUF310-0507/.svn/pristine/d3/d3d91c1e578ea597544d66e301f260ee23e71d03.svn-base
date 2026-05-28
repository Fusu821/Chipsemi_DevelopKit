#ifndef __HAL_USB_LAYER_SERVICE__
#define __HAL_USB_LAYER_SERVICE__
/**************************************************************************************/
#include "Wait.h"
#include "RefBase.h"
#include "BaseService.h"
//////////////////////////////////////////////////////////////////////////
typedef BOOL (*FunAsycCallBack)( unsigned char (&buffer)[MAX_HAL_WR_LEN], LPVOID handler );

#pragma warning( disable:4311 )
#pragma warning( disable:4312 )
class IComplexHalListener;
class CHalUSBLayerService : public CBSPRService
{
private:
	CHalUSBLayerService( const CHalUSBLayerService& );
public:
	CHalUSBLayerService(  );
	virtual ~CHalUSBLayerService();

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	void StartService( int nPriority = 0  );

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	void StopService();

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	virtual void BackGoundProcessing();

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	void HalSrvWrite( RMHDR* pHDR );

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	void HalSrvRead( RMHDR* pHDR );

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	void HalSrvIoCtrl( RMHDR* pHDR );

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	void HalConnected( RMHDR* pHDR );

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	void HalSrvSetBackGoundRequied( RMHDR* pHDR );

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	void HalSrvRegistAnalyzer( RMHDR* pHDR );

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	void HalSetDeviceManuly( RMHDR* pHDR );

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	BOOL HasReceiveDataInQueue( UINT32 queryTimeout );

 	DECLEAR_SERVICE( CHalUSBLayerService )

private:
	//void WakeUpDispatcher( UINT32 hostRequest );
private:
	HANDLE m_hDevice;
 	HANDLE m_hEventIoCtrl;
	HANDLE m_hEventDevice;
 	//HANDLE m_hEventRead;
	OVERLAPPED m_oRead;

	IComplexHalListener* m_pComplexListener;
};

#pragma warning( default:4311 )
#pragma warning( default:4312 )
/**************************************************************************************/
#endif