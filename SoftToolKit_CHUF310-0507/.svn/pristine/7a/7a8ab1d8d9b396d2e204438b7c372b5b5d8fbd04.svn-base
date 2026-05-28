#include "stdafx.h"
#include <afxinet.h>
#include <process.h>
#include "Protocal.h"
#include "AutomaticEx.h"
IAutomaticInterface* GetAutomaticInterface( unsigned int type, HWND wind, LinkParam param )
{
	static CAutomatic proxy;

	proxy.SetOperateComplexWnd( wind );

	bool bOK = proxy.Initialize( type, param );

	if( !bOK ) proxy.GameOver(  );

	return bOK ? &proxy : NULL;
}

// BOOL HandleRecvAndNotifyAPI( unsigned char* buffer, unsigned int len, IAutomaticInterface* handler )
// {
// 	return handler->HandleRecvAndNotify( buffer, len );
// }

CAutomatic::CAutomatic()
:m_ComplexWnd( NULL )
,m_curProtocal( NULL )
,m_curOpType( OP_LIKE_DEFAULT )
,m_HalServiceInterface( NULL )
{  
	//m_bHexCode = TRUE;
}


bool CAutomatic::Initialize( unsigned int type, LinkParam& param )
{
	m_curOpType = type;
	typedef IHalServiceInterface* ( *funAllocInterface )(  );

	if( m_curOpType == OP_LIKE_DEFAULT ){
		HMODULE hDllLib = ::LoadLibrary( _T("HalComLayerSrv.dll") );
		funAllocInterface fun = (funAllocInterface)::GetProcAddress( hDllLib, "AllocateHalSrvInterface" );
		if( fun )  m_HalServiceInterface = (*fun)();

		if( m_HalServiceInterface )
		{
			m_curProtocal = GetProtocalLikeStandard();
			m_HalServiceInterface->RegistAnalyzer( dynamic_cast<IComplexHalListener*>(this) );
			return ERROR_CODE_OK == m_HalServiceInterface->HalTryAttachLink( PARAM_MARK_RESERVED, param.com.port, param.com.boartRate );
		}
	}
	else if( m_curOpType == OP_LIKE_EDO ){
		HMODULE hDllLib = ::LoadLibrary( _T("HalTcpClientSrv.dll") );
		funAllocInterface fun = (funAllocInterface)::GetProcAddress( hDllLib, "AllocateHalSrvInterface" );
		if( fun )  m_HalServiceInterface = (*fun)();

		if( m_HalServiceInterface )
		{
			m_curProtocal = GetProtocalEDO();//ÉÏº£EDO
			m_HalServiceInterface->RegistAnalyzer( dynamic_cast<IComplexHalListener*>(this) );

			if( m_curProtocal->Initalize(param) )
			{
				return ERROR_CODE_OK == m_HalServiceInterface->HalTryAttachLink( PARAM_MARK_RESERVED, param.tcp.pszIpAddress, param.tcp.port, param.tcp.async, param.tcp.nport - 1 );
				//return false;
			}
		}
	}
	else if( m_curOpType == OP_LIKE_HX ){
		HMODULE hDllLib = ::LoadLibrary( _T("HalTcpClientSrv.dll") );
		funAllocInterface fun = (funAllocInterface)::GetProcAddress( hDllLib, "AllocateHalSrvInterface" );
		if( fun )  m_HalServiceInterface = (*fun)();

		if( m_HalServiceInterface )
		{
			m_curProtocal = GetProtocalHXD();//»ªÐÇ
			m_HalServiceInterface->RegistAnalyzer( dynamic_cast<IComplexHalListener*>(this) );
			return ERROR_CODE_OK == m_HalServiceInterface->HalTryAttachLink( PARAM_MARK_RESERVED, param.tcp.pszIpAddress, param.tcp.port, param.tcp.async, param.tcp.nport - 1 );
		}
	}
	else{

	}

	return false;
}
//BOOL CAutomatic::HandleRecvAndNotify( unsigned char* buffer, unsigned int len )
//{
//	unsigned int mark = 0;
//	BOOL bWaitPull = m_curProtocal->AnalyzeRecvAndMark( buffer, len, mark );
//
//	if( PACKET_START_TEST == (mark >> 16) )
//	{
//		::PostMessage( m_ComplexWnd, WM_START_TEST, (mark & 0xff), 0 );
//	}
//	else
//	{
//	}
//
//	return bWaitPull;
//}
void CAutomatic::GameOver(  )
{
	typedef void ( *funRestoreInterface )( IHalServiceInterface*& ptr );

	if( m_HalServiceInterface ) m_HalServiceInterface->HalTryDetachLink( PARAM_MARK_RESERVED );

	if( m_curOpType == OP_LIKE_DEFAULT ){
		HMODULE hDllLib = ::LoadLibrary( _T("HalComLayerSrv.dll") );
		funRestoreInterface fun = (funRestoreInterface)::GetProcAddress( hDllLib, "RestoreHalSrvInterface" );
		if( fun ) (*fun)( m_HalServiceInterface );
	}
	if( m_curOpType == OP_LIKE_EDO ){
		m_curProtocal->UnInitalize();
		HMODULE hDllLib = ::LoadLibrary( _T("HalTcpClientSrv.dll") );
		funRestoreInterface fun = (funRestoreInterface)::GetProcAddress( hDllLib, "RestoreHalSrvInterface" );
		if( fun ) (*fun)( m_HalServiceInterface );
	}
	else{

	}

	m_HalServiceInterface = NULL;
}
void CAutomatic::SetOperateComplexWnd( HWND hwnd )
{
	m_ComplexWnd = hwnd;
}
unsigned char CAutomatic::SendResultUpToServer( const TransInfo_Collection& trans )
{
	OpParamEx op( m_HalServiceInterface, m_OpLock );
	op.SendResult.pCollection = &trans;

	return m_curProtocal->SendResultUpToServer( op );
}
unsigned char CAutomatic::OnLine( unsigned char option, LPCTSTR szLine )
{
	OpParamEx op( m_HalServiceInterface, m_OpLock );
	op.SwitchMode.option = option;
	op.SwitchMode.lineID = szLine;

	return m_curProtocal->OnLine( op );
}
unsigned char CAutomatic::AccountCheck( LPCTSTR szLine, LPCTSTR szAccount, LPCTSTR szPassword )
{
	OpParamEx op( m_HalServiceInterface, m_OpLock );
	op.AccountCheck.lineID = szLine;
	op.AccountCheck.account = szAccount;
	op.AccountCheck.password = szPassword;

	return m_curProtocal->AccountCheck( op );
}
unsigned char CAutomatic::LogOnMessage( LPCTSTR szLine, LPCTSTR sn )
{
	OpParamEx op( m_HalServiceInterface, m_OpLock );
	op.LogOn.pannelID = sn;
	op.LogOn.lineID = szLine;

	return m_curProtocal->LogOnMessage( op );
}
unsigned char CAutomatic::LogOffMessage( LPCTSTR szLine, LPCTSTR sn, int device, unsigned short result )
{
	OpParamEx op( m_HalServiceInterface, m_OpLock );
	op.LogOff.pannelID = sn;
	op.LogOff.result = result;
	op.LogOff.lineID = szLine;
	op.LogOff.nDevice = device;

	return m_curProtocal->LogOffMessage( op );
}
unsigned char CAutomatic::ActionToOnLineMessage(NativeTestInterface* appInterface, int msg, unsigned int wparam, unsigned int lparam)
{
	OpParamEx op( m_HalServiceInterface, m_OpLock );
	op.UserData.msg = msg;
	op.UserData.wparam = wparam;
	op.UserData.lparam = lparam;
	op.UserData.pcallBack = appInterface;

	return m_curProtocal->ActionToOnLineMessage(op);
}
LPCTSTR CAutomatic::GetOnLineMessageInfo( )
{
	return m_curProtocal->GetOnLineMessageInfo( );
}
bool CAutomatic::NotifyTestStatus( unsigned char ucDevice, unsigned int testCode, unsigned short status, unsigned char result/* = RESULT_NULL*/ )
{
	OpParamEx op( m_HalServiceInterface, m_OpLock );
	op.NotifyStatus.ucDevice = ucDevice;
	op.NotifyStatus.testCode = testCode;
	op.NotifyStatus.status = status;
	op.NotifyStatus.result = result;

	return m_curProtocal->NotifyTestStatus( op );
}
unsigned char CAutomatic::OnLineDoHandShake()
{
	OpParamEx op( m_HalServiceInterface, m_OpLock );

	return m_curProtocal->OnLineDoHandShake( op );
}
void CAutomatic::OnLinkDataArrived( unsigned char* recvBuffer, int len, bool bAnyTesting, char* szIni, char* szBin )
{
    OpParamEx op( m_HalServiceInterface, m_OpLock );
    op.Linkdata.szIni = (char*)szIni;
	op.Linkdata.szBin = (char*)szBin;

	return m_curProtocal->OnLinkDataArrived( op );
}
unsigned char CAutomatic::OnGetUserData( unsigned char ucDevice, unsigned short dataType, unsigned char* buffer, int len, int* readed )
{
	OpParamEx op( m_HalServiceInterface, m_OpLock );
	//op.UserData.device = ucDevice;
	//op.UserData.dataType = dataType;
	//op.UserData.buffer = buffer;
	//op.UserData.lenth = len;
	//op.UserData.readed = readed;

	return m_curProtocal->OnGetUserData( op );
}

bool CAutomatic::SendUserData( unsigned char ucDevice, unsigned short dataType, unsigned char* buffer, int len )
{
	OpParamEx op( m_HalServiceInterface, m_OpLock );
	//op.UserData.device = ucDevice;
	//op.UserData.dataType = dataType;
	//op.UserData.buffer = buffer;
	//op.UserData.lenth = len;

	return m_curProtocal->SendUserData( op );
}

bool  CAutomatic::SendAckPacket( unsigned char ucDevice, unsigned short packetType )
{
	OpParamEx op( m_HalServiceInterface, m_OpLock );
	op.Ack.ucDevice = ucDevice;
	op.Ack.packetType = packetType;

	return m_curProtocal->SendAckPacket( op );
}

bool CAutomatic::ReceiveAckPacket( unsigned char ucDevice, unsigned short packetType )
{
	OpParamEx op( m_HalServiceInterface, m_OpLock );
	op.Ack.ucDevice = ucDevice;
	op.Ack.packetType = packetType;

	return m_curProtocal->ReceiveAckPacket( op );
}

EnHandleResult CAutomatic::OnStart( LONG dwConnID )
{
	logInfo.module = ::LoadLibrary( _T("Logger.dll") );
	if( logInfo.module ){
		logInfo.initLog = (funInitLog)::GetProcAddress( logInfo.module, "InitLogInterface" );
		if( logInfo.initLog ){
			TCHAR chPath[MAX_PATH] = {0};
            TCHAR chTemp[MAX_PATH] = {0};

			::GetModuleFileName( NULL, chPath, MAX_PATH );
			*(_tcsrchr( chPath, _T('\\') ) + 1) = 0;
			transformat( chTemp, MAX_PATH, _T("SrvLog-%d.log"), dwConnID );
			_tcscat_s( chPath, MAX_PATH, _T("LogFile\\") );
			_tcscat_s( chPath, MAX_PATH, chTemp );
			(*logInfo.initLog)( _T("SrvLog"), chPath, 2/*DAILY*/, true, 10 );
		}

		logInfo.forceLog = (funForceLog)::GetProcAddress( logInfo.module, "ForceLog" );
		if( logInfo.forceLog ){
			TCHAR chTemp[MAX_PATH] = {0};
			transformat( chTemp, MAX_PATH, _T("HalService Started, Service id = %d"), dwConnID );
			(*logInfo.forceLog)( _T("SrvLog"), chTemp );
		}
	}

	return HR_OK;
}
EnHandleResult CAutomatic::OnStop( LONG dwConnID )
{
	if( logInfo.forceLog ){
		TCHAR chTemp[MAX_PATH] = {0};
		transformat( chTemp, MAX_PATH, _T("HalService Stoped, Service id = %d"), dwConnID );
		(*logInfo.forceLog)( _T("SrvLog"), chTemp );
	}   
	return HR_OK;
}
EnHandleResult CAutomatic::OnSend( LONG dwConnID, const BYTE* pData, int iLength )
{
	//int log_size_t = ( iLength * 3 + 20 ) * 2;
	//TCHAR* szLog = new TCHAR[log_size_t];

	//copytextto( szLog, log_size_t, _T("WriteData: "), lengthof(_T("WriteData: ")) );
	//BYTE* pByte = (BYTE*)pData;

	//for ( int index = 0; index < (int)iLength; ++index )
	//{
	//	TCHAR chTemp[6] = {0};
	//	if(m_bHexCode)
	//		transformat( chTemp, _T("%02x "), (int)( *(pByte+index) ) );
	//	else
	//		transformat( chTemp, _T("%c"), (char)(*(pByte+index)) );
	//	copytextappend( szLog, log_size_t, chTemp );
	//}

	//if( logInfo.forceLog ) (*logInfo.forceLog)( _T("SrvLog"), szLog );

	//delete[] szLog;

	return HR_OK;
}
EnHandleResult CAutomatic::OnReceive( LONG dwConnID, const BYTE* pData, int iLength )
{
	srvMsg  mark;
	BOOL bWaitPull = m_curProtocal->AnalyzeRecvAndMark( pData, iLength, mark );
	if(m_OpLock.Locked())  bWaitPull = TRUE;

	if( PACKET_START_TEST == mark.type )
	{
		::PostMessage( m_ComplexWnd, WM_START_TEST, mark.sP0, 0 );
	}
	else if( PACKET_USER_DATA == mark.type )
	{
		::PostMessage( m_ComplexWnd, WM_RECV_USER_DATA, mark.sP0 , mark.sP1 );
	}
	else
	{

	}

	//int log_size_t = ( iLength * 3 + 20 ) * 2;
	//TCHAR* szLog = new TCHAR[log_size_t];

	//copytextto( szLog, log_size_t, _T("ReadData:  "), lengthof(_T("ReadData:  ")) );
	//BYTE* pByte = (BYTE*)pData;

	//for ( int index = 0; index < (int)iLength; ++index )
	//{
	//	TCHAR chTemp[6] = {0};
	//	if(m_bHexCode)
	//		transformat( chTemp, _T("%02x "), (int)( *(pByte+index) ) );
	//	else
	//		transformat( chTemp, _T("%c"), (char)(*(pByte+index)) );
	//	copytextappend( szLog, log_size_t, chTemp );
	//}

	//if( logInfo.forceLog ) (*logInfo.forceLog)( _T("SrvLog"), szLog );

	//delete[] szLog;

	return bWaitPull ? HR_IGNORE : HR_OK;
}
EnHandleResult CAutomatic::OnReceive( LONG dwConnID, int iLength )
{
	return HR_IGNORE;
}
EnHandleResult CAutomatic::OnConnect( LONG dwConnID )
{
	if( logInfo.forceLog ){
		(*logInfo.forceLog)( _T("SrvLog"), _T("Connection build~") );
	}   

	return HR_IGNORE;
}
EnHandleResult CAutomatic::OnClose( LONG dwConnID )
{
	if( logInfo.forceLog ){
		(*logInfo.forceLog)( _T("SrvLog"), _T("Connection break~") );
	}   

	return HR_IGNORE;
}
EnHandleResult CAutomatic::OnError( LONG dwConnID, int iErrorCode )
{
	TCHAR chTemp[MAX_PATH] = {0};
	transformat( chTemp, MAX_PATH, _T("Error happened, error code = %d"), iErrorCode );
	(*logInfo.forceLog)( _T("SrvLog"), chTemp );

	return HR_IGNORE;
}
EnHandleResult CAutomatic::OnShutdown( LONG dwConnID )
{
	TCHAR chTemp[MAX_PATH] = {0};
	transformat( chTemp, MAX_PATH, _T("Service shut down, Service id = %d"), dwConnID );
	(*logInfo.forceLog)( _T("SrvLog"), chTemp );

	return HR_IGNORE;
}

unsigned int CAutomatic::ResetCommandEvent( unsigned char ucDevice, unsigned int iCommandEvent )
{
    return m_curProtocal->ResetCommandEvent( ucDevice, iCommandEvent);
}

unsigned int CAutomatic::WaitCommandEvent( unsigned char ucDevice, unsigned int iCommandEvent, unsigned int iwaitTime )
{
    return m_curProtocal->WaitCommandEvent( ucDevice, iCommandEvent, iwaitTime);
}


/**********************************************************************************************************************/

FtpClientProxy::FtpClientProxy()
	:m_pInetSession(NULL)
	,m_pFtpConnection(NULL)
	,m_bFileUploader(TRUE)
	,m_enType(ftp_task_none)
{
	m_mapDirExist.clear();

	m_pInetSession = new CInternetSession(_T("chsc_ftp"), 1, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);

	uintptr_t h = _beginthreadex(NULL, 0, FtpClientThreadEntry, this, 0, NULL);
}

FtpClientProxy::~FtpClientProxy()
{
	m_bFileUploader = FALSE;
	Sleep(100);
	if(m_pFtpConnection)
	{
		m_pFtpConnection->Close();
		delete m_pFtpConnection;
	}
	if(m_pInetSession) 
	{
		delete m_pInetSession;
	}
}

unsigned int WINAPI FtpClientProxy::FtpClientThreadEntry( LPVOID lp )
{
	FtpClientProxy* proxy = (FtpClientProxy*)lp;
	while( proxy->m_bFileUploader )
	{
		if(ftp_task_upload == proxy->m_enType)
		{
			if(0 == proxy->FindFileAndUpdate())
			{
				proxy->m_enType = ftp_task_none;
			}
		}
		else
		{
			Sleep(5000);
		}
	}

	return 0;
}

unsigned char FtpClientProxy::UpFile(LPCTSTR localDir, LPCTSTR server, LPCTSTR user, LPCTSTR password, unsigned short nport )
{
	m_szRootDir = localDir;
	m_szServer = server;
	m_szUser = user;
	m_szPassword = password;
	m_port = nport;

	m_enType = ftp_task_upload;

	return ERROR_CODE_OK;
}

unsigned char FtpClientProxy::FindFileAndUpdate()
{
	unsigned char ReCode = ERROR_CODE_OK;
	if(NULL == m_pInetSession) return ERROR_CODE_NO_DEVICE;

	try
	{
		if(NULL == m_pFtpConnection)
		{
			m_pFtpConnection = m_pInetSession->GetFtpConnection(m_szServer, m_szUser, m_szPassword, m_port, TRUE);
		}
		if(NULL != m_pFtpConnection)
		{
			ReCode = IterLoopUpdate( _T("" ) );
		}
	}
	catch(...)
	{
		ReCode = ERROR_CODE_COMM_ERROR;
	}

	if(NULL != m_pFtpConnection)
	{
		m_pFtpConnection->Close();
		delete m_pFtpConnection;
		m_pFtpConnection = NULL;
	}

	return ReCode;
}

unsigned char FtpClientProxy::IterLoopUpdate(CString szRelative)
{
	WIN32_FIND_DATA FindFileData;
	unsigned char ReCode = ERROR_CODE_OK;

	HANDLE hFind = ::FindFirstFile( m_szRootDir + szRelative + _T("\\*.*"), &FindFileData );
	if(INVALID_HANDLE_VALUE == hFind)   return ERROR_CODE_INVALID_PARAM;

	while(TRUE)
	{
		if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if(FindFileData.cFileName[0] != _T('.'))
			{
				szRelative = szRelative + _T("/") + FindFileData.cFileName;
				if(m_pFtpConnection && m_mapDirExist.end() == m_mapDirExist.find(szRelative)) 
				{
					m_pFtpConnection->CreateDirectory( szRelative );

					m_mapDirExist[szRelative] = TRUE;
				}

				

				ReCode = IterLoopUpdate(szRelative);
				if(0 != ReCode) break;
			}
		}
		else
		{
			if(NULL != findtext(FindFileData.cFileName, _T(".txt")))
			{
				if(m_pFtpConnection) 
				{
					CString szLocal = m_szRootDir + szRelative + _T("\\") + FindFileData.cFileName;
					szRelative.Replace( _T("\\"), _T("/") );  
					if(TRUE == m_pFtpConnection->PutFile( szLocal, szRelative + _T("/") + FindFileData.cFileName ))
					{
						::DeleteFile(szLocal);
					}
					else
					{
						m_mapDirExist.clear();
						m_pFtpConnection->Close();
						delete m_pFtpConnection;
						m_pFtpConnection = NULL;
						ReCode = ERROR_CODE_COMM_ERROR;
						break;
					}
				}
			}
		}

		if(!FindNextFile(hFind,&FindFileData))    break;
	}
	FindClose(hFind);

	return ReCode;
}

// unsigned char FtpClientProxy::DownFile( LPCTSTR remoteFile, LPCTSTR localFile )
// {
// 	unsigned char ReCode = ERROR_CODE_OK;
// 	if(NULL == m_pFtpConnection) return ERROR_CODE_NO_DEVICE;
// 
// 	try
// 	{
// 		m_pFtpConnection->GetFile(remoteFile, localFile, FALSE, FILE_ATTRIBUTE_NORMAL, INTERNET_FLAG_RELOAD, 1);
// 		m_pFtpConnection->Close();
// 	}
// 	catch(...)
// 	{
// 		ReCode = ERROR_CODE_COMM_ERROR;
// 	}
// 
// 	return ReCode; 
// }

// unsigned char FtpClientProxy::UpFile( unsigned short finalResult, LPCTSTR fromPath, LPCTSTR toPath )
// {
// 	unsigned char ReCode = ERROR_CODE_OK;
// 	if(NULL == m_pFtpConnection) return ERROR_CODE_NO_DEVICE;
// 
// 	try
// 	{
// 		if(RESULT_PASS == finalResult)
// 		{
// 			m_pFtpConnection->CreateDirectory("PASS");
// 		}
// 		else
// 		{
// 			m_pFtpConnection->CreateDirectory("NG");
// 		}
// 		m_pFtpConnection->PutFile(fromPath, toPath);
// 		m_pFtpConnection->Close();
// 	}
// 	catch(...)
// 	{
// 		ReCode = ERROR_CODE_COMM_ERROR;
// 	}
// 
// 	return ReCode;
// }

IFtpClientInterface* GetFtpInterface()
{
	static FtpClientProxy ftpClient;
	return &ftpClient;
}