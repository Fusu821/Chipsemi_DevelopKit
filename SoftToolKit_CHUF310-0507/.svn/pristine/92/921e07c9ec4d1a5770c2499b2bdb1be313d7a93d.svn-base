#ifndef __SEMI_TOUCH_ONLINE_LOG__
#define __SEMI_TOUCH_ONLINE_LOG__
#include "Macro.h"
#define OnLineLogApp OnLineLog::GetInstance()

#define LOG_SEMI_TOUCH_OPEN          1
#define LOG_SEMI_TEST_OPEN           1


#ifdef LOG_SEMI_TOUCH_OPEN
#ifdef SM_CHIP_BASE
#define CHECK_RETURN_IF_FAIL(x) do{ if( ERROR_CODE_OK!=(x) ) { OnLineLogApp.AppendLogMessage( GetWrapperAddr()->GetIDMark(), _T("SEMI_TOUCH"), (x), __FUNCTION__, __LINE__ ); return (x); } }while(0)    
#endif //SM_CHIP_BASE
#endif

#if LOG_SEMI_TEST_OPEN 
#ifdef SM_TEST_BASE
#define CHECK_RETURN_IF_FAIL(x) do{ if( ERROR_CODE_OK!=(x) ) { OnLineLogApp.AppendLogMessage( m_deviceNo, _T("SEMI_TEST"), (x), __FUNCTION__, __LINE__ ); return (x); } }while(0) 
#endif //SM_TEST_BASE  
#endif

#ifndef CHECK_RETURN_IF_FAIL
#define CHECK_RETURN_IF_FAIL(x) do{ if( ERROR_CODE_OK!=(x) ) return (x); }while(0)
#endif

class OnLineLog
{
	typedef void ( *funForceLog )( LPCTSTR pstrName, LPCTSTR pstrText );
	typedef bool ( *funInitLog )( LPCTSTR pstrName, LPCTSTR pstrPath, UINT32 schedule, bool bImmFlush, int maxBack );
	struct LogInfo{
		HMODULE module;
		funForceLog forceLog;
		funInitLog initLog;
	}logInfo;
public:
	OnLineLog();
	virtual ~OnLineLog();

	static OnLineLog& GetInstance();
public:
	void AppendLogMessage( LPCTSTR strText, LPCTSTR strHeader = NULL );
	void AppendLogMessage( int device, LPCTSTR strText );
	void AppendLogMessage( int idevice, LPCTSTR szModule, unsigned int errCode, LPCTSTR function, long line );
	void OnInitLogParam( int device );
public:
	void OnInitLogParam( LPCTSTR strHeader = NULL, LPCTSTR szDir = NULL  );
};

#endif //__SEMI_TOUCH_ONLINE_LOG__