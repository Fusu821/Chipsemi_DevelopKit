#ifndef __HAL_TCPCIENT_SERVICE__
#define __HAL_TCPCIENT_SERVICE__
#include "BaseService.h"
#include <WinSock2.h>
#include "Lock.h"
#include "Sodata.h"
#include "Socket.h"
#include "bufferpool.h"
/**************************************************************************************/
class IComplexHalListener;
enum EnServiceState{ SS_STARTING = 0,SS_STARTED	= 1,SS_STOPPING	= 2, SS_STOPPED	= 3,};
#pragma warning( disable:4311 )
#pragma warning( disable:4312 )
 class CHalTcpClientLayerService : public CBSPRService
 {
 private:
 	CHalTcpClientLayerService( const CHalTcpClientLayerService& );
 public:
 	CHalTcpClientLayerService(  );
 	virtual ~CHalTcpClientLayerService();

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
	BOOL HasReceiveDataInQueue( UINT32 queryTimeout );

	DECLEAR_SERVICE( CHalTcpClientLayerService )
private:
	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
    void WakeUpDispatcher( UINT32 hostRequest );

	BOOL CheckParams() { return TRUE; }

	bool CheckStarting();

	bool CheckStoping();

	void Reset( bool bClear  = true  );

	bool CreateClientSocket();

	bool ConnectToServer( LPCTSTR pszRemoteAddress, unsigned short uPort, unsigned short uPortSource );

	int SendInternal( const BYTE* pWriteBuffer, int iLen );

	bool ProcessNetworkEvent();

	bool ReadData();

	bool SendData();

	TItem* GetSendBuffer();

	TItem* GetRecvBuffer();

	bool DoSendData( TItem* pItem );

	void Stop();

	int ReadCatchData( const BYTE* bufferRead, unsigned int readLen, unsigned int& readedLen );
private:
	SOCKET              m_soClient;
    unsigned char       m_bAsyncConnect;
	EnServiceState      m_enState;
	CSpinGuard          m_csState;
	unsigned long       m_dwKeepAliveTime;
	unsigned long       m_dwKeepAliveInterval;
	unsigned int        m_dwSocketBufferSize;

 	HANDLE              m_evWakeUp;
	HANDLE              m_evSocket;
	HANDLE              m_evSdBuffer;
	HANDLE              m_evRcBuffer;

	TItemList           m_lsRecv;
	TItemList			m_lsSend;
	CCriSec				m_csSend;

	CBufferPtr			m_rcBuffer;
	CItemPool			m_itPool;

	CInitSocket         m_initSocket;

 	BOOL                m_flagClearDataQueue;

	IComplexHalListener* m_pComplexListener;
 };
#pragma warning( default:4311 )
#pragma warning( default:4312 )
/**************************************************************************************/
#endif