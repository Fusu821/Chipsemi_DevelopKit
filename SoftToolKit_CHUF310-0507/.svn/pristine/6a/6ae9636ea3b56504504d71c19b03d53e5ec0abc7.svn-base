#include "Macro.h"
#include "onlinelog.h"
#include <tchar.h>
#include <stdio.h>

/*unsigned char OnLineLog::m_bInitialized[MAX_DEVICE_NUM] = {FALSE, FALSE, FALSE, FALSE};*/
OnLineLog::OnLineLog()
{
    //OnInitLogParam();
}
OnLineLog::~OnLineLog()
{

}
OnLineLog& OnLineLog::GetInstance()
{
	static OnLineLog online;
	return online;
}
void OnLineLog::OnInitLogParam( int device )
{
	TCHAR szHeader[MAX_PATH] = {0};
	transformat( szHeader, _T("SEMI-%d"), device + 1 );

	OnInitLogParam( szHeader );
}

void OnLineLog::OnInitLogParam( LPCTSTR strHeader/* = NULL*/, LPCTSTR szDir /*= NULL */)
{
	TCHAR szHeader[MAX_PATH] = {0};
	if(NULL == strHeader)
		copytextto( szHeader, _T("OnLineLog"), lengthof(_T("OnLineLog")) );
	else
		copytextto( szHeader, strHeader, lengthof(strHeader) );

	TCHAR szRealPath[MAX_PATH] = {0}, szRealDll[MAX_PATH] = {0};

	if( szDir )
		copytextto( szRealPath, MAX_PATH, szDir, lengthof(szDir) );
	else
	{
		HMODULE handle = ::GetModuleHandle( _T("BSPR.dll") );
		::GetModuleFileName( handle, szRealPath, MAX_PATH );
		*(_tcsrchr( szRealPath, _T('\\') ) + 1) = 0;
	}

	copytextto( szRealDll, MAX_PATH, szRealPath, lengthof(szRealPath) );
	copytextappend( szRealDll, _T("Logger.dll") );

	logInfo.module = ::LoadLibrary( szRealDll );
	if( logInfo.module ){
		logInfo.initLog = (funInitLog)::GetProcAddress( logInfo.module, "InitLogInterface" );
		if( logInfo.initLog ){
			//wprintf_s( chTemp, MAX_PATH, _T("OnLineLog.log") );
			_tcscat_s( szRealPath, MAX_PATH, _T("LogFile\\") );
			_tcscat_s( szRealPath, MAX_PATH, szHeader );
			_tcscat_s( szRealPath, MAX_PATH, _T(".log") );
			(*logInfo.initLog)( szHeader, szRealPath, 2/*DAILY*/, true, 10 );
		}

		logInfo.forceLog = (funForceLog)::GetProcAddress( logInfo.module, "ForceLog" );
		if( logInfo.forceLog ){
			(*logInfo.forceLog)( szHeader, _T("OnLine Started, Service id = 0") );
		}
	}
}
void OnLineLog::AppendLogMessage( LPCTSTR strText, LPCTSTR strHeader /*= NULL*/ )
{
	if( logInfo.forceLog ){
		if( strHeader )
			(*logInfo.forceLog)( strHeader, strText );
		else
			(*logInfo.forceLog)( _T("OnLineLog"), strText );
	}  
}
void OnLineLog::AppendLogMessage( int idevice, LPCTSTR strText )
{
	if( logInfo.forceLog ){
		TCHAR szHeader[MAX_PATH] = {0};
		transformat( szHeader, _T("SEMI-%d"), idevice + 1 );

		(*logInfo.forceLog)( szHeader, strText );
	}  
}
void OnLineLog::AppendLogMessage( int idevice, LPCTSTR szModule,  unsigned int errCode, LPCTSTR function, long line )
{
	if(logInfo.forceLog){
		TCHAR szHeader[MAX_PATH] = {0};
		transformat( szHeader, _T("SEMI-%d"), idevice + 1 );

		TCHAR szTemp[MAX_PATH] = {0};
		transformat( szTemp, _T("Module:%-10s, Error Code = %d, function = %s, line = %d"), szModule, errCode, function, line );
		(*logInfo.forceLog)( szHeader, szTemp );
	}
}