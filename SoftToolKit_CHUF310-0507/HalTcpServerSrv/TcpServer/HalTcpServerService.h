#ifndef __HAL_TCPSERVER_SERVICE__
#define __HAL_TCPSERVER_SERVICE__
#include "BaseService.h"
#include <WinSock2.h>
#include <vector>
#include "Lock.h"
#include "Sodata.h"
#include "Socket.h"
#include "bufferpool.h"
/**************************************************************************************/
class IComplexHalListener;
enum EnServiceState{ SS_STARTING = 0,SS_STARTED	= 1,SS_STOPPING	= 2, SS_STOPPED	= 3,};

#define EVENT_WAKE_UP                    0
#define EVENT_SEND_DATA                  1
#define EVENT_RECV_DATA                  2
#define EVENT_SOCK_LISTEN                3
#define EVENT_FIXD_COUNT                 4
#define MAX_ACCEPT_SOCKET_NUM            1
#define MAX_WAIT_EVENT_QUEUE_LEN         (MAX_ACCEPT_SOCKET_NUM) + EVENT_FIXD_COUNT
#pragma warning( disable:4311 )
#pragma warning( disable:4312 )
 class CHalTcpServerLayerService : public CBSPRService
 {
 private:
 	CHalTcpServerLayerService( const CHalTcpServerLayerService& );
 public:
 	CHalTcpServerLayerService(  );
 	virtual ~CHalTcpServerLayerService();

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

	DECLEAR_SERVICE( CHalTcpServerLayerService )
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

	void ResetClient( bool bClear  = true  );

	bool CreateListenSocket( LPCTSTR lpszBindAddress, unsigned short uPort );

	bool ConnectToServer( LPCTSTR pszRemoteAddress, unsigned short uPort );

	int SendInternal( const BYTE* pWriteBuffer, int iLen );

	bool ProcessNetworkEvent(DWORD eventID);

	bool ReadData( SOCKET so );

	bool SendData( SOCKET so );

	TItem* GetSendBuffer();

	TItem* GetRecvBuffer();

	bool DoSendData( SOCKET so, TItem* pItem );

	void Stop();

	//bool StartAccept();

	//bool CreateCompletePort();

	//bool CreateWorkerThreads();

	LPCTSTR GetHostIpAddress();

	int ReadCatchData( const BYTE* bufferRead, unsigned int readLen, unsigned int& readedLen );
private:
	//SOCKET              m_soListen;
    //unsigned char       m_bAsyncConnect;
	EnServiceState      m_enState;
	CSpinGuard          m_csState;
	unsigned long       m_dwKeepAliveTime;
	unsigned long       m_dwKeepAliveInterval;
	unsigned int        m_dwSocketBufferSize;
	unsigned int        m_dwSocketListenQueue;
	unsigned int        m_dwWorkerThreadCount;
	unsigned int        m_dwAcceptSocketCount;

//  	HANDLE              m_evWakeUp;
// 	HANDLE              m_evSocket;
// 	HANDLE              m_evSdBuffer;
// 	HANDLE              m_evRcBuffer;

	TItemList           m_lsRecv;
	TItemList			m_lsSend;
	CCriSec				m_csSend;

	CBufferPtr			m_rcBuffer;
	CItemPool			m_itPool;


	//PEERIO_OPERATION_DATA m_context;	
	CInitSocket         m_initSocket;

	ADDRESS_FAMILY		m_usFamily;

	//std::vector<HANDLE>	m_vtWorkerThreads;

// 	HANDLE				m_hCompletePort;
    BOOL                m_flagClearDataQueue;
// 	BOOL                m_bNoDelay;

	unsigned int        m_iEventCount;
	HANDLE              m_eventQueues[MAX_WAIT_EVENT_QUEUE_LEN];
	SOCKET              m_soArray[MAX_ACCEPT_SOCKET_NUM + 1];

// 	LPFN_ACCEPTEX				m_pfnAcceptEx;
// 	LPFN_GETACCEPTEXSOCKADDRS	m_pfnGetAcceptExSockaddrs;
// 	LPFN_DISCONNECTEX			m_pfnDisconnectEx;


// 	EnReuseAddressPolicy m_enReusePolicy;
// 	EnSendPolicy m_enSendPolicy;
// 	EnOnSendSyncPolicy m_enOnSendSyncPolicy;


	IComplexHalListener* m_pComplexListener;
 };
#pragma warning( default:4311 )
#pragma warning( default:4312 )
/**************************************************************************************/
#endif