#ifndef __HAL_PIPE_SERVICE__
#define __HAL_PIPE_SERVICE__
#include "BaseService.h"
#include "Lock.h"
#include "Sodata.h"
#include "bufferpool.h"
/**************************************************************************************/
typedef BOOL (*FunAsycCallBack)( unsigned char *buffer, unsigned int len, LPVOID handler );
#pragma warning( disable:4311 )
#pragma warning( disable:4312 )
class IComplexHalListener;
class CHalPipeLayerService : public CBSPRService
{
private:
	CHalPipeLayerService( const CHalPipeLayerService& );
public:
	CHalPipeLayerService(  );
	virtual ~CHalPipeLayerService();

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
	void HalConnected( RMHDR* pHDR );

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	void HalTryAttachLink( RMHDR* pHDR );

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	void HalTryDetachLink( RMHDR* pHDR );

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
	void HalClearDataQueueData( RMHDR* pHDR );

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	BOOL HasReceiveDataInQueue( UINT queryTimeout );

	DECLEAR_SERVICE( CHalPipeLayerService )
private:
	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
    void WakeUpDispatcher( UINT hostRequest );

	void MakeReadInternal(  );

	TItem* GetRecvBuffer();

	int ReadCatchData( const BYTE* bufferRead, unsigned int readLen, unsigned int& readedLen );
private:
	HANDLE m_hDevice;
	HANDLE m_hEventWrite;
	HANDLE m_hEventRead;
	HANDLE m_evWakeUp;
	HANDLE m_evRcBuffer;
	DWORD  m_dwPipeBufferSize;
	BOOL m_bWaitDataComming;
	OVERLAPPED m_oRead;

	BOOL m_flagClearDataQueue;

	TItemList           m_lsRecv;
	CBufferPtr			m_rcBuffer;
	CItemPool			m_itPool;
	IComplexHalListener* m_pComplexListener;
};
#pragma warning( default:4311 )
#pragma warning( default:4312 )
/**************************************************************************************/
#endif