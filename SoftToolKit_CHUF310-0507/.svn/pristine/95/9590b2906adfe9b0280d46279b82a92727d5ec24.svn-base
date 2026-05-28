#pragma once
#include "../../include/automaticInterface.h"
#include "../../include/HalServiceInterface.h"
#include "../../include/IComplexHalListener.h"
#include "../../Include/NativeTestInterface.h"
#include "Wait.h"
#include <iostream>
#include <string>
#include <tchar.h>
#include <map>
using namespace std;

class CProtocal;
class CAutomatic : public IAutomaticInterface, public virtual IComplexHalListener
{
public:
    CAutomatic();

	unsigned char OnLine( unsigned char option, LPCTSTR szLine );

	unsigned char AccountCheck( LPCTSTR szLine, LPCTSTR szAccount, LPCTSTR szPassword );

	unsigned char LogOnMessage( LPCTSTR szLine, LPCTSTR sn );

	unsigned char LogOffMessage( LPCTSTR szLine, LPCTSTR sn, int device, unsigned short result );

	unsigned char ActionToOnLineMessage(NativeTestInterface* appInterface, int msg, unsigned int wparam, unsigned int lparam);

	LPCTSTR GetOnLineMessageInfo( );

	unsigned char SendResultUpToServer( const TransInfo_Collection& trans );

	bool NotifyTestStatus( unsigned char ucDevice, unsigned int testCode, unsigned short status, unsigned char result = RESULT_NULL );

	unsigned char OnLineDoHandShake();

	void SetOperateComplexWnd( HWND hwnd );

	bool Initialize( unsigned int type, LinkParam& param );

	void GameOver( );

	//BOOL HandleRecvAndNotify( unsigned char* buffer, unsigned int len );

	void OnLinkDataArrived( unsigned char* recvBuffer, int len, bool bAnyTesting, char* szIni, char* szBin );

	unsigned char OnGetUserData( unsigned char ucDevice, unsigned short dataType, unsigned char* buffer, int len, int* readed );

	bool SendUserData( unsigned char ucDevice, unsigned short dataType, unsigned char* buffer, int len );

	bool SendAckPacket( unsigned char ucDevice, unsigned short packetType );

	bool ReceiveAckPacket( unsigned char ucDevice, unsigned short packetType );

    unsigned int ResetCommandEvent( unsigned char ucDevice, unsigned int iCommandEvent );

    unsigned int WaitCommandEvent( unsigned char ucDevice, unsigned int iCommandEvent, unsigned int iwaitTime = 500 );

	/*********************************************************************************************************
	*Proxy向用户提供的接口 有数据发送出去时调用此接口
	*参数定义
	**********************************************************************************************************/
	virtual EnHandleResult OnStart( LONG dwConnID );

	/*********************************************************************************************************
	*Proxy向用户提供的接口 有数据发送出去时调用此接口
	*参数定义
	**********************************************************************************************************/
	virtual EnHandleResult OnStop( LONG dwConnID );

	/*********************************************************************************************************
	*Proxy向用户提供的接口 有数据接收时调用此接口
	*参数定义
	**********************************************************************************************************/
	virtual EnHandleResult OnSend( LONG dwConnID, const BYTE* pData, int iLength );

	/*********************************************************************************************************
	*Proxy向用户提供的接口 有数据接收时调用此接口
	*参数定义
	**********************************************************************************************************/
	virtual EnHandleResult OnReceive( LONG dwConnID, const BYTE* pData, int iLength );

	/*********************************************************************************************************
	*Proxy向用户提供的接口 有数据接收时调用此接口
	*参数定义
	**********************************************************************************************************/
	virtual EnHandleResult OnReceive( LONG dwConnID, int iLength );

	/*********************************************************************************************************
	*Proxy向用户提供的接口 关闭设备时调用此接口
	*参数定义
	**********************************************************************************************************/
	virtual EnHandleResult OnConnect( LONG dwConnID );

	/*********************************************************************************************************
	*Proxy向用户提供的接口 关闭设备时调用此接口
	*参数定义
	**********************************************************************************************************/
	virtual EnHandleResult OnClose( LONG dwConnID );

	/*********************************************************************************************************
	*Proxy向用户提供的接口 关闭设备时调用此接口
	*参数定义
	**********************************************************************************************************/
	virtual EnHandleResult OnError( LONG dwConnID, int iErrorCode );

	/*********************************************************************************************************
	*Proxy向用户提供的接口 关闭设备时调用此接口
	*参数定义
	**********************************************************************************************************/
	virtual EnHandleResult OnShutdown( LONG dwConnID );

private:
    HWND m_ComplexWnd;
	SpinLock m_OpLock;
	CProtocal* m_curProtocal;
	unsigned int m_curOpType;
	//BOOL m_bHexCode;
    HMODULE m_LogSrvHandle;
	IHalServiceInterface* m_HalServiceInterface;
    HANDLE m_hCommndEvent[MAX_DEVICE_NUM];
};

enum ftp_task_type{ ftp_task_none = 0, ftp_task_upload = 2, };
class FtpClientProxy : public IFtpClientInterface
{
public:
	FtpClientProxy();

	virtual ~FtpClientProxy();

	virtual unsigned char UpFile(LPCTSTR localDir, LPCTSTR server, LPCTSTR user, LPCTSTR password, unsigned short nport );

protected:
	unsigned char FindFileAndUpdate();

	unsigned char IterLoopUpdate(CString szRelative);

// 	virtual unsigned char DownFile( LPCTSTR remoteFile, LPCTSTR localFile );
// 
// 	virtual unsigned char UpFile( );

	static unsigned int WINAPI FtpClientThreadEntry( LPVOID lp );

private:
	CInternetSession *m_pInetSession;
	CFtpConnection *m_pFtpConnection;
	unsigned int m_bFileUploader;
	ftp_task_type m_enType;

	CString m_szRootDir;
	CString m_szServer;
	CString m_szUser;
	CString m_szPassword;
	unsigned short m_port;
	map<CString, BOOL> m_mapDirExist;
};