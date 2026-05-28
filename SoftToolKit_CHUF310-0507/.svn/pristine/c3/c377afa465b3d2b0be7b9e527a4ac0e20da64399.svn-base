#ifndef __HAL_COMPLEX_LISTENER__
#define __HAL_COMPLEX_LISTENER__
/*********************************************************************************************************

Copyright: Hal-Link Open Source (chaos_wu@163.com)

Author: Wasim

Date:2015-11-02

Description: Provide  a Interface of HalServiceProxy 
every one of them mush Inherit this interface and this interface is directly exposed to users

**********************************************************************************************************/
enum EnHandleResult
{
	HR_OK		= 0,	// 成功
	HR_IGNORE	= 1,	// 忽略
	HR_ERROR	= 2,	// 错误
	HR_CLOSED   = 0xFF,
};
#ifndef SOCKET
typedef UINT_PTR        SOCKET;
#endif

#define FireStart( id ) ( m_pComplexListener ? m_pComplexListener->OnStart( (id) ) : HR_IGNORE ) 
#define FireStop( id ) ( m_pComplexListener ? m_pComplexListener->OnStop( (id) ) : HR_IGNORE ) 
#define FireConnect( id ) ( m_pComplexListener ? m_pComplexListener->OnConnect( (id) ) : HR_IGNORE ) 
#define FireError( id, code )
#define FireClose( id ) ( m_pComplexListener ? m_pComplexListener->OnClose( (id) ) : HR_IGNORE ) 
#define FireReceive( id, op, code ) ( m_pComplexListener ? m_pComplexListener->OnReceive( (id), (op), (code) ) : HR_IGNORE ) 
#define FireSend( id, op, code )  ( m_pComplexListener ? m_pComplexListener->OnSend( (id), (op), (code) ) : HR_IGNORE ) 
#define FirePrepareListen( id )  ( m_pComplexListener ? m_pComplexListener->PrepareListen( (id) ) : HR_OK ) 

class IComplexHalListener
{
public:
	/*********************************************************************************************************
	*Proxy向用户提供的接口 有数据发送出去时调用此接口
	*参数定义
	**********************************************************************************************************/
	virtual EnHandleResult OnStart( LONG dwConnID )					                                    = 0;

	/*********************************************************************************************************
	*Proxy向用户提供的接口 有数据发送出去时调用此接口
	*参数定义
	**********************************************************************************************************/
	virtual EnHandleResult OnStop( LONG dwConnID )					                                    = 0;

	/*********************************************************************************************************
	*Proxy向用户提供的接口 有数据发送出去时调用此接口
	*参数定义
	**********************************************************************************************************/
	virtual EnHandleResult OnSend( LONG dwConnID, const BYTE* pData, int iLength )					    = 0;

	/*********************************************************************************************************
	*Proxy向用户提供的接口 有数据接收时调用此接口
	*参数定义
	**********************************************************************************************************/
	virtual EnHandleResult OnReceive( LONG dwConnID, const BYTE* pData, int iLength )					= 0;

	/*********************************************************************************************************
	*Proxy向用户提供的接口 有数据接收时调用此接口
	*参数定义
	**********************************************************************************************************/
	virtual EnHandleResult OnReceive( LONG dwConnID, int iLength )					                = 0;

	/*********************************************************************************************************
	*Proxy向用户提供的接口 关闭设备时调用此接口
	*参数定义
	**********************************************************************************************************/
	virtual EnHandleResult OnConnect( LONG dwConnID )													= 0;

	/*********************************************************************************************************
	*Proxy向用户提供的接口 关闭设备时调用此接口
	*参数定义
	**********************************************************************************************************/
	virtual EnHandleResult OnClose( LONG dwConnID )				    								= 0;

	/*********************************************************************************************************
	*Proxy向用户提供的接口 关闭设备时调用此接口
	*参数定义
	**********************************************************************************************************/
	virtual EnHandleResult OnError( LONG dwConnID, int iErrorCode )	    						    = 0;

	/*********************************************************************************************************
	*Proxy向用户提供的接口 关闭设备时调用此接口
	*参数定义
	**********************************************************************************************************/
	virtual EnHandleResult OnShutdown( LONG dwConnID )	    										    = 0;

	/*********************************************************************************************************
	*Proxy向用户提供的接口 关闭设备时调用此接口
	*参数定义
	**********************************************************************************************************/
	virtual EnHandleResult PrepareListen( LONG dwConnID )  { return HR_OK; };

public:
	virtual ~IComplexHalListener() {}
};



class ITcpServerListener : public IComplexHalListener
{
public:
	/*********************************************************************************************************
	*Proxy向用户提供的接口 监听端口前调用此接口
	*参数定义
	**********************************************************************************************************/
	virtual EnHandleResult OnPrepareListen( SOCKET soListen )	    									= 0;

	/*********************************************************************************************************
	*Proxy向用户提供的接口 有客户连接到来时调用此接口
	*参数定义
	**********************************************************************************************************/
	virtual EnHandleResult OnAccept( LONG dwConnID, SOCKET soClient )	    							= 0;
};


class CTcpServerListener : public ITcpServerListener
{
public:
	virtual EnHandleResult OnReceive(LONG dwConnID, int iLength)					{return HR_IGNORE;}
	virtual EnHandleResult OnSend(LONG dwConnID, const BYTE* pData, int iLength)	{return HR_IGNORE;}
	virtual EnHandleResult OnPrepareListen(SOCKET soListen)							{return HR_IGNORE;}
	virtual EnHandleResult OnAccept(LONG dwConnID, SOCKET soClient)				    {return HR_IGNORE;}
	virtual EnHandleResult OnShutdown( LONG dwConnID )					  		    {return HR_IGNORE;}
};

class CTcpPullServerListener : public CTcpServerListener
{
public:
	virtual EnHandleResult OnReceive(LONG dwConnID, int iLength)						                 = 0;
	virtual EnHandleResult OnReceive(LONG dwConnID, const BYTE* pData, int iLength)	{return HR_IGNORE;}
};

class CUsbLayerServiceListener : public IComplexHalListener
{
public:
	virtual EnHandleResult OnStart( LONG dwConnID )                                     {return HR_IGNORE;}
	virtual EnHandleResult OnStop( LONG dwConnID )                                      {return HR_IGNORE;}
	virtual EnHandleResult OnSend( LONG dwConnID, const BYTE* pData, int iLength )      {return HR_IGNORE;}
	virtual EnHandleResult OnReceive( LONG dwConnID, const BYTE* pData, int iLength )   = 0;
	virtual EnHandleResult OnReceive( LONG dwConnID, int iLength )                      {return HR_IGNORE;}
	virtual EnHandleResult OnConnect( LONG dwConnID )                                   {return HR_IGNORE;}
	virtual EnHandleResult OnClose( LONG dwConnID )                                     {return HR_IGNORE;}
	virtual EnHandleResult OnError( LONG dwConnID, int iErrorCode )                     {return HR_IGNORE;}
	virtual EnHandleResult OnShutdown( LONG dwConnID )                                  {return HR_IGNORE;}
};

/*********************************************************************************************************/
#endif
