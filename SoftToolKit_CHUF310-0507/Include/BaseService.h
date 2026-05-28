#ifndef __IBASE_SERVICE__
#define __IBASE_SERVICE__
/**************************************************************************************/
#include "Macro.h"
#include "RBNode.h"
#include "RefBase.h"
#include <tchar.h>
/**************************************************************************************/
#define BSPRMSG  MSG*
//#define BSPRMSG  sp<MsgPacket>
// #define PostBSPRThreadMessage( id, code, w, l ) \
// sp<MsgPacket> newPacket = new MsgPacket( (id), (code), (w), (l) );\
// m_curMsgQueue.InsertMessagePacket( newPacket );
#define PostBSPRThreadMessage( id, code, w, l ) PostThreadMessage( (id), (code), (w), (l) )

struct RMHDR;
class CBSPRService;
class BSPR_SERVICE_API IRequestProcessMethod
{
public:
	virtual void Invoke( CBSPRService* pBase, RMHDR* pHDR ) = 0;
	virtual ~IRequestProcessMethod(){}
};

class BSPR_SERVICE_API CRequestProcessMethod : public IRequestProcessMethod
{
public:
	//CRequestProcessMethod( UINT32 method ):mMethodID(method){}
	virtual void Invoke( CBSPRService* pBase, RMHDR* pHDR ) = 0;
    static CRequestProcessMethod* SearchMethod( struct rb_root* root, UINT32 methodID );
    static int InsertMethod( struct rb_root* root, CRequestProcessMethod* newMethod );
private:
	struct rb_node mRBLink;
public:
	UINT32 mMethodID;
};

//////////////////////////////////////////////////////////////////////////
/* 服务绑定宏 */
#define DECLEAR_SERVICE(SERVICE)\
	static LPCTSTR Get##SERVICE()\
{\
	return _T(#SERVICE);\
}\
	LPCTSTR GetServiceName()\
{\
	return Get##SERVICE();\
}\
    typedef SERVICE classtype;\
	static CBSPRService* GetServiceBasePointer( void* pThis )\
{\
	unsigned long offset = 0;\
	unsigned long uBassAddr = 1;\
	offset = (unsigned long)&( ((classtype*)(&uBassAddr))->Real_Auto_Method ) - (unsigned long)(&uBassAddr);\
	return (CBSPRService*)( ( unsigned long )pThis - offset );\
}\
struct _AUTO_METHOD##SERVICE\
{\
	_AUTO_METHOD##SERVICE();\
}Real_Auto_Method;\



#define BEGIN_SERVICE_BIND( SERVICE )\
typedef SERVICE classtype;\
classtype::_AUTO_METHOD##SERVICE::_AUTO_METHOD##SERVICE()\
{\
	CBSPRService* pBase = classtype::GetServiceBasePointer( this );\

#define BIND_REQUEST(REQUEST,METHODNAME)\
	class _REQUEST_METHOD##METHODNAME : public CRequestProcessMethod\
	{\
		void Invoke( CBSPRService* pBase, RMHDR* pHDR )\
		{\
			((classtype*)pBase)->METHODNAME( pHDR );\
		}\
	};\
	static _REQUEST_METHOD##METHODNAME method##METHODNAME;\
	method##METHODNAME.mMethodID = REQUEST;\
	CRequestProcessMethod::InsertMethod( &pBase->m_rbRequestMethod, &method##METHODNAME );\


#define SERVICE_BIND_END() \
}

//////////////////////////////////////////////////////////////////////////
/* 参数绑定宏 */
#define DECLEAR_REQUEST_PARAM(PARAM)\
	typedef PARAM classtype;\
	RMHDR HDR;\
	static classtype* GetPointer( void* pThis )\
{\
	unsigned long offset = 0;\
	unsigned long uBassAddr = 1;\
	offset = (unsigned long)&( ((classtype*)(&uBassAddr))->auto_param ) - (unsigned long)(&uBassAddr);\
	return (classtype*)( ( unsigned long )pThis - offset );\
}\
struct _AUTO_PARAM\
{\
	_AUTO_PARAM()\
{\
	classtype* pClassType = GetPointer( this );\
	LPCTSTR strName = _T( #PARAM );\
	pClassType->HDR.m_iSize = sizeof( classtype );\
	if ( _tcslen( strName ) < (PARAM_NAME_LENTH-1) )\
{\
	_tcscpy_s( pClassType->HDR.m_paramName, strName );\
}\
}\
}auto_param;


struct BSPR_SERVICE_API RMHDR
{
	HANDLE m_eventFinish;
	TCHAR  m_paramName[PARAM_NAME_LENTH];
	UINT32   m_iSize;
	UINT32   m_iGateByte;
	friend class CBSPRService;
public:
	RMHDR();
	~RMHDR();

public:
	BOOL IsValidate();
	void ProcessFinish();
	BOOL IsKindOf( LPCTSTR pStrTypeName );
	void Release();
	RMHDR* Colne();
};

struct MsgPacket;
class BSPR_SERVICE_API CBSPRService 
{
private:
	CBSPRService( const CBSPRService& );
public:
    CBSPRService();
	virtual ~CBSPRService();

public:
	/**************************************************************************************
	*Summary: Sync Interface, make a request and wait for turnning back
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	virtual BOOL RequestAndWait( UINT32 RequestCode, RMHDR* pHDR );

	/**************************************************************************************
	*Summary: Sync Interface, make a request and wait for turnning back
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	virtual BOOL RequestAndWaitEx( UINT32 RequestCode, RMHDR* pHDR );

	/**************************************************************************************
	*Summary: Sync Interface, make a request and wait for turnning back
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	virtual BOOL Request( UINT32 RequestCode, RMHDR* pHDR );

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	virtual void StartService( int nPriority = 0  );

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	virtual void StopService();

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	virtual LPCTSTR GetServiceName();

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	DWORD GetServiceFackID();

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	BOOL IsExistSameRequestID( UINT32 uRequestID );

protected:
	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	void ServiceMain();

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	void TranslateBSPRMessage( const BSPRMSG msg  );

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	static DWORD WINAPI ThreadProc( LPVOID lpParameter );

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	void DisPatchBSPRMessage( const BSPRMSG msg );

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	RMHDR* ColounSyncParam( RMHDR* pHDR );

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	inline BOOL IsBackGroundProcessRequied() const;

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	inline void SetBackGroundProcessRequied( BOOL bRequied );

	/**************************************************************************************
	*Summary: Start Sevice
	*Parameters:
	*     param:common param pointer,such as user name ,pwd,etc.*    
	*Return : true is connect successfully.
	***************************************************************************************/
	virtual void BackGoundProcessing();

	virtual void WakeUpDispatcher( UINT32 hostRequest );

private:
	HANDLE m_hThreadHandle;
	BOOL   m_bBackGoundProcessRequied;
protected:
	DWORD  m_dwFackID;
public:
// 	struct MessageQueue
// 	{ 
// 		sp<MsgPacket> root;
// 		void InsertMessagePacket( sp<MsgPacket>& packet );
// 		sp<MsgPacket> PopMessagePacket(  );
// 		volatile LONG locked;
// 	};
    rb_root m_rbRequestMethod;
//    MessageQueue m_curMsgQueue;


	
};

/**************************************************************************************/
#endif
