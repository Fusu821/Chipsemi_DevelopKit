#include "TestBase.h"

#include "checksum.h"
#include "onlinelog.h"
#include "ToolKit.h"
#include "automaticInterface.h"
#include "Graph/VirtualButtonTest.h"

//#using "../SEMITestApp/bin/Debug/SEMIEmsSysUpLoad.dll"
//
//using namespace SEMIEmsSysUpLoad;

#ifdef _MSC_VER
#include <process.h>
#else
#include <pthread.h>
#include <sys/stat.h>
#include <sys/types.h>
#endif

extern CConfig* G_XMLConfig;
extern  void OnCopyBootCallBack( int dev, int pos, int max, LPCTSTR szText );
extern void __stdcall OnUpdateMtkCallBack( unsigned char devNo, int pos, int maxPos );

SpinLock  CTestResultSave::m_lock;
SYSTEMTIME CTestResultSave::m_StampTime = CTestResultSave::StartUpTime();
SYSTEMTIME CTestResultSave::m_StartUpTime = CTestResultSave::StartUpTime();
SYSTEMTIME CTestBase::m_StartTime = CTestBase::StartTestTime();
map<UINT64, CTestResultSave::StcResult> CTestResultSave::m_mapItemStc;
SYSTEMTIME CTestResultSave::StartUpTime()
{
	static SYSTEMTIME t;
	::GetLocalTime( &t );
	return t;
}
void CTestResultSave::UpDateStatistic( const RecordData& strDataMsg, InternalItemInfo (&itemResult)[MAX_TEST_ITEMS] )
{
	StcResult stResult( strDataMsg.TestResult, ITEM_STA_NONE );
	for( int index = 0; index < MAX_TEST_ITEMS; index++ )
	{
		InternalItemInfo& info = itemResult[index];
		if( !info.bSelected )  continue;
		if( info.item.testCode != TEST_ITEM_CURRENT_TEST ) continue;

		stResult.currentResult = info.item.testResult;
		//m_mapItemStc[strDataMsg.ReleaseID] = StcResult( strDataMsg.TestResult, info.item.testResult );

		break;
	}
	m_mapItemStc[strDataMsg.ReleaseID] = stResult;
}
LPCTSTR CTestResultSave::GetStatisticText()
{
	SYSTEMTIME curTime;
	::GetLocalTime( &curTime );
	static TCHAR szLocalBuffer[128] = {0};
	TCHAR szTemp[64] = {0};
	int numOfFailed = 0, iCurrnetFailed = 0;

	for( map<UINT64, StcResult>::iterator it = m_mapItemStc.begin(); it != m_mapItemStc.end(); it++ )
	{
		if( it->second.finalResult == TEST_NG )
			numOfFailed++;
		if( it->second.currentResult == ITEM_STA_FAIL )
			iCurrnetFailed++;
	}

	memset( szLocalBuffer, 0, sizeof(szLocalBuffer) );

	transformat( szTemp, _T("%02d:%02d:%02d - %02d:%02d:%02d  "), m_StartUpTime.wHour, m_StartUpTime.wMinute, m_StartUpTime.wSecond, curTime.wHour, curTime.wMinute, curTime.wSecond );
	copytextappend( szLocalBuffer, szTemp );

	transformat( szTemp, _T("Total = %d, Fail = %d, CurrentNG = %d\n"), (int)m_mapItemStc.size(), numOfFailed, iCurrnetFailed );
	copytextappend( szLocalBuffer, szTemp );

	return szLocalBuffer;
}
BOOL CTestResultSave::CurrentFailed( InternalItemInfo (&itemResult)[MAX_TEST_ITEMS] )
{
	BOOL currentFailed = FALSE;
	for( int index = 0; index < MAX_TEST_ITEMS; index++ )
	{
		InternalItemInfo& info = itemResult[index];
		if( !info.bSelected )  continue;
		if( info.item.testCode == TEST_ITEM_CURRENT_TEST )
		{
			currentFailed = info.item.testResult == ITEM_STA_FAIL ? TRUE : FALSE;
			break;
		}
	}

	return currentFailed;
}
void CTestResultSave::OnAppShutDown()
{
	if( m_mapItemStc.size() > 0 )
	{
		FILE* file = NULL;
		//string strOnStatistic = "";
		
		SYSTEMTIME curTime;
		::GetLocalTime( &curTime );
		TCHAR szFileName[MAX_PATH] = {0}, szWorkStation[MAX_PATH] = {0};
		CToolKit::UTF8ToGBK( G_XMLConfig->szWorkStation, szWorkStation, MAX_PATH );
		transformat( szFileName,  _T("%s\\SMCP\\LogFile\\%s-%4d-%02d-%02d.stm"), CToolKit::GetExecutePath(), szWorkStation, curTime.wYear, curTime.wMonth, curTime.wDay );

		LPCTSTR szStc = GetStatisticText();

		m_mapItemStc.clear();
		m_StampTime = curTime;
		m_StartUpTime = curTime;

		fopen_s( &file, szFileName, "a+" );
		if( NULL != file )
		{
			fwrite( szStc, 1, lengthof(szStc), file );

			fclose( file );
		}
	}
	
}
void CTestResultSave::MakeOneStatistic( LPCTSTR szSaveFileName, const RecordData& strDataMsg, InternalItemInfo (&itemResult)[MAX_TEST_ITEMS] )
{
	FILE* file = NULL;

	SYSTEMTIME curTime;
	::GetLocalTime( &curTime );
	TCHAR szFileName[MAX_PATH] = {0}, szWorkStation[MAX_PATH] = {0};
	CToolKit::UTF8ToGBK( G_XMLConfig->szWorkStation, szWorkStation, MAX_PATH );
	transformat( szFileName, _T("%s\\TestResult\\%s-%4d-%02d-%02d.stc"), CToolKit::GetExecutePath(), szWorkStation, curTime.wYear, curTime.wMonth, curTime.wDay );

	UpDateStatistic( strDataMsg, itemResult );

	TCHAR szTemp[128] = {0};
	string strOnStatistic = "";
	transformat( szTemp, _T("ID=0x%llx,"), strDataMsg.ReleaseID );
	strOnStatistic += szTemp;

	if( strDataMsg.TestResult == TEST_PASS )
	{
		transformat( szTemp, _T("Final=%s,"), _T("PASS") );
		strOnStatistic += szTemp;
	}
	else if( strDataMsg.TestResult == TEST_NG )
	{
		transformat( szTemp, _T("Final=%s,"), _T("NG") );
		strOnStatistic += szTemp;
	}
	else if( strDataMsg.TestResult == TEST_TBD )
	{
		transformat( szTemp, _T("Final=%s,"), _T("TBD") );
		strOnStatistic += szTemp;
	}

	for( int index = 0; index < MAX_TEST_ITEMS; index++ )
	{
		InternalItemInfo& info = itemResult[index];
		if( !info.bSelected )  continue;

		transformat( szTemp, _T("%s[%d],"), info.item.testName, info.item.testResult );
		strOnStatistic += szTemp;
	}

	transformat( szTemp, _T("File=%s,\n"), szSaveFileName );
	strOnStatistic += szTemp;

	if( TEST_NG == strDataMsg.TestResult && CurrentFailed( itemResult ) )
	{
		transformat( szTemp, _T("0x%llx: mode1 = %d, mode2 = %d, mode3 = %d, delta = %d\n"), strDataMsg.ReleaseID, strDataMsg.current_mode1, strDataMsg.current_mode2, strDataMsg.current_mode3, strDataMsg.current_delta );
		strOnStatistic += szTemp;
	}

	fopen_s( &file, szFileName, "a+" );
	if( NULL != file )
	{
		fwrite( strOnStatistic.c_str(), 1, strOnStatistic.length(), file );

		fclose( file );
	}

	int deltaTime = (curTime.wDay - m_StampTime.wDay) * 24 + (curTime.wHour - m_StampTime.wHour);
	deltaTime = deltaTime * 60 + (curTime.wMinute - m_StampTime.wMinute);
	if( deltaTime >= 60 )
	{
		strOnStatistic = GetStatisticText();
		//m_mapItemStc.clear();
		m_StampTime = curTime;
		memset( szFileName, 0, sizeof(szFileName) );
		transformat( szFileName, _T("%s\\SMCP\\LogFile\\%s-%4d-%02d-%02d.stm"), CToolKit::GetExecutePath(), szWorkStation, curTime.wYear, curTime.wMonth, curTime.wDay );
		fopen_s( &file, szFileName, "a+" );
		if( NULL != file )
		{
			fwrite( strOnStatistic.c_str(), 1, strOnStatistic.length(), file );

			fclose( file );
		}
	}
}
tstring CTestResultSave::MakeFileNameToSave( const RecordData& rcDataMsg, unsigned char simulate/* = 0*/ )
{
	TCHAR szName[MAX_PATH] = {0};

	SYSTEMTIME st = {0};
	GetLocalTime(&st);//获得当前本地时间

	if(simulate)
	{
		transformat( szName, _T("#%d_%d%02d%02d%02d%02d%02d%03d.txt"), rcDataMsg.ucDevice + 1, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds );
	}
	else
	{
		if( 0 == lengthof( (char*)rcDataMsg.snCode ) )
			transformat( szName, _T("#%d_%d%02d%02d%02d%02d%02d_%03d.txt"), rcDataMsg.ucDevice + 1, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds );
		else
			transformat( szName, _T("#%d_%s_%d%02d%02d%02d%02d%02d_%03d.txt"), rcDataMsg.ucDevice + 1, rcDataMsg.snCode, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond , st.wMilliseconds);
	}


	return szName;
}
tstring CTestResultSave::MakeRelativePath(unsigned int testRet, InternalItemInfo (&itemResult)[MAX_TEST_ITEMS], LPCTSTR szWorkStation, unsigned char simulate /*= 0*/)
{
	tstring strFileSave = _T("");

	if( simulate )
	{
		strFileSave += _T("/Fake");
	}
	else
	{
#ifdef _MSC_VER
		DWORD iSize = MAX_PATH;
		TCHAR chName[MAX_PATH] = {0};
		GetComputerName( chName, &iSize );//获取电脑名
		strFileSave += _T("/");
		strFileSave += chName;

		SYSTEMTIME st = {0};
		GetLocalTime( &st );//获得当前本地时间，作测试开始时间
		memset( chName, 0, sizeof(chName) );
		transformat( chName, _T("%s-%d-%02d-%02d"), szWorkStation, st.wYear, st.wMonth, st.wDay );
		strFileSave += _T("/");
		strFileSave += chName;
#endif
	}

	if( TEST_PASS == testRet ){
		strFileSave += _T("/PassLog");
	}
	else if( TEST_NG == testRet ){
		strFileSave += _T("/FailLog/");
		strFileSave += GetFailReason( itemResult );
	}
	else if( TEST_TBD == testRet ){
		strFileSave += _T("/TBDLog");
	}

	return strFileSave;
}
tstring CTestResultSave::MakeAbsolutePath( )
{
	tstring strFileSave;
	
	if(NULL == G_XMLConfig->szLogPath || 0 == lengthof(G_XMLConfig->szLogPath))
	{
		strFileSave.append(CToolKit::GetExecutePath());
		strFileSave.append( _T("/TestResult") );
	}
	else
	{
		TCHAR szTemp[MAX_PATH];
		CToolKit::UTF8ToGBK( G_XMLConfig->szLogPath, szTemp, MAX_PATH );
		strFileSave.append(szTemp);
	}

	return strFileSave;
}
tstring CTestResultSave::MakeAbsoluteBackUp()
{
	tstring strFileSave;

	strFileSave.append(CToolKit::GetExecutePath());
	strFileSave.append( _T("/TestBackup") );

	return strFileSave;
}
tstring CTestResultSave::GetFailReason( InternalItemInfo (&itemResult)[MAX_TEST_ITEMS] )
{
	tstring failReason = _T("UnHandle");
	for( int index = 0; index < MAX_TEST_ITEMS; index++ )
	{
		InternalItemInfo& info = itemResult[index];
		if( !info.bSelected ) continue;

		NativeTestItem& item = info.item;
		if( ITEM_STA_EXCEPTION == item.testResult )
			return _T("Exception");
		else if( item.testResult == ITEM_STA_FAIL ) 
			return item.testName;
		//if( item.testResult >= ITEM_STA_FAIL && item.testCode <= TEST_ITEM_SHARE_ALL )
		//	return _T("Error");
	}
	return failReason;
}
tstring CTestResultSave::GetFailReasonID( InternalItemInfo (&itemResult)[MAX_TEST_ITEMS] )
{
    tstring failReason = _T("6");
    for( int index = 0; index < MAX_TEST_ITEMS; index++ )
    {
        InternalItemInfo& info = itemResult[index];
        if( !info.bSelected ) continue;

        NativeTestItem& item = info.item;
        if( ITEM_STA_EXCEPTION == item.testResult )
            return _T("6");
        else if( item.testResult == ITEM_STA_FAIL ) 
        {
            TCHAR buf[32];
            _itot_s(item.testCode, buf, _countof(buf), 10);
            return tstring(buf);
        }
    }
    return failReason;
}

void CTestResultSave::CheckAndCreateFolder( const tstring& strFilePath )
{
    tstring strTemp = strFilePath;
	if( is_dir_exist(strTemp.c_str()) ) return;

	if( /*strrchr*/findtext( strTemp.c_str(), _T(".txt") ) == NULL )
	{
		//is a folder
		const TCHAR* chChar = strTemp.c_str();
		const TCHAR* chTemp = rfindtext( chChar, _T('/') );
		if( NULL != chTemp ) CheckAndCreateFolder( strTemp.substr( 0, chTemp - chChar ) );

		if( !is_dir_exist(strTemp.c_str()) )  create_dir( strTemp.c_str());
	}
	else
	{
		//is a file
		const TCHAR* chChar = strTemp.c_str();
		const TCHAR* chTemp = rfindtext( chChar, _T('/') );
		if( NULL != chTemp ) CheckAndCreateFolder( strTemp.substr( 0, chTemp - chChar ) );
	}
}
void CTestResultSave::ReplaceAllToken( tstring& strSource )
{
	if( strSource.empty() )  return;
	int length = (int)strSource.length();
	//strSource.replace( _T('\\'), _T('/') );
	while(true)   
	{     
		tstring::size_type pos(0);     
		if( (pos = strSource.find(_T('\\'))) != string::npos )     
		{ 
			strSource.replace( pos, 1, _T("/") );  
		}   
		else  { break; }
	}     
	if( strSource[length-1]==_T('/') )
	{
		strSource = strSource.substr( 0,(int)strSource.length() - 1 );
	}
	if( strSource[0]==_T('/') )
	{
		strSource = strSource.substr( 1,(int)strSource.length() - 1 );
	}
}
void CTestResultSave::SaveTestResult( const tstring& strContent, const RecordData& rcDataMsg, InternalItemInfo (&itemResult)[MAX_TEST_ITEMS], unsigned char simulate /*= 0 */)
{
	tstring strFile = _T("");
	tstring strSaveFileName = MakeFileNameToSave( rcDataMsg, simulate );
	tstring strAbsolute = MakeAbsolutePath();
	tstring strRelative = MakeRelativePath( rcDataMsg.TestResult, itemResult, (LPCTSTR)rcDataMsg.workStation, simulate );
	tstring strPath = strAbsolute + strRelative;
	ReplaceAllToken( strPath );
	CheckAndCreateFolder( strPath );

	FILE* file = NULL;

	file = NULL;
	try
	{
		strFile = strPath + _T("/") + strSaveFileName /*+ _T(".txt")*/;
		fopen_s( &file, strFile.c_str(), "wb" );
		if( NULL != file )
		{
			//string s = strContent.replace(_T("\r\n"), _T("\n"))
			fwrite( strContent.c_str(), 1, strContent.length(), file );
			fclose( file );
		}
	}
	catch(...)
	{
		if( NULL != file )
		{
			fclose( file );
		}
	}

	if(G_XMLConfig->ftp_type > 0)
	{
#ifdef _MSC_VER
		tstring strBackUp = MakeAbsoluteBackUp();
		strBackUp = strBackUp + strRelative;
		ReplaceAllToken( strBackUp );
		CheckAndCreateFolder( strBackUp );
		strBackUp += _T("/") + strSaveFileName;

		::CopyFile(strFile.c_str(), strBackUp.c_str(), FALSE);

		IFtpClientInterface* iFtpInterface = GetFtpInterface();
		iFtpInterface->UpFile( MakeAbsoluteBackUp().c_str(), G_XMLConfig->ftp_ip_addr, G_XMLConfig->ftp_account, G_XMLConfig->ftp_password, G_XMLConfig->ftp_port );
#endif
	}

	try
	{
		if( rcDataMsg.ReleaseID > 0 )
		{
			strSaveFileName = strSaveFileName.substr(0, strSaveFileName.length() - 4);
			MakeOneStatistic( strSaveFileName.c_str(), rcDataMsg, itemResult );
		}
	}
	catch (...)
	{
	}

}
tstring CTestResultSaveID::MakeFileNameToSave( const RecordData& rcDataMsg, unsigned char simulate /*= 0*/ )
{
	TCHAR szName[MAX_PATH] = {0};

	if(0 == rcDataMsg.ReleaseID)
	{
		SYSTEMTIME st = {0};
		GetLocalTime(&st);//获得当前本地时间

		if(simulate)
		{
			transformat( szName, _T("#%d_%d%02d%02d%02d%02d%02d%03d.txt"), rcDataMsg.ucDevice + 1, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds );
		}
		else
		{
			if( 0 == lengthof( (char*)rcDataMsg.snCode ) )
				transformat( szName, _T("#%d_%d%02d%02d%02d%02d%02d_%03d.txt"), rcDataMsg.ucDevice + 1, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds );
			else
				transformat( szName, _T("#%d_%s_%d%02d%02d%02d%02d%02d.txt"), rcDataMsg.ucDevice + 1, rcDataMsg.snCode, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond );
		}
	}
	else
	{
		UINT32 otm_time = *(UINT32*)&rcDataMsg.ReleaseID;
		transformat( szName, _T("0x%llx.txt"), rcDataMsg.ReleaseID/*, (otm_time>>22)&0xf, (otm_time>>17)&0x1f,(otm_time>>12)&0x1f, (otm_time>>6)&0x3f, otm_time&0x3f*/ );
	}

	return szName;
}
tstring CTestResultSaveYY::MakeFileNameToSave( const RecordData& rcDataMsg, unsigned char simulate /*= 0*/ )
{
	TCHAR szName[MAX_PATH] = {0};

	SYSTEMTIME st = {0};
	GetLocalTime(&st);//获得当前本地时间
	transformat( szName, _T("%s-0x%llx-%d%02d%02d%02d%02d%02d-%s.csv"), rcDataMsg.snCode, rcDataMsg.ReleaseID, 
		st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, rcDataMsg.TestResult == TEST_PASS ? _T("Pass") : _T("Fail"));

	return szName;
}
tstring CTestResultSaveEDO::MakeFileNameToSave( const RecordData& rcDataMsg, unsigned char simulate /*= 0*/ )
{
	TCHAR szName[MAX_PATH] = {0};

	SYSTEMTIME st = {0};
	GetLocalTime(&st);//获得当前本地时间
	transformat( szName, _T("%s-0x%llx-%d%02d%02d%02d%02d%02d-dev%d-%s.txt"), rcDataMsg.snCode, rcDataMsg.ReleaseID, 
		st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, rcDataMsg.ucDevice, rcDataMsg.TestResult == TEST_PASS ? _T("Pass") : _T("Fail"));

	return szName;
}
tstring CTestResultSaveCloud::MakeFileNameToSave( const RecordData& rcDataMsg, unsigned char simulate /* = 0 */ )
{
	tstring strFileSave = G_XMLConfig->szProjectName;
#ifdef _MSC_VER
	DWORD iSize = MAX_PATH;
	TCHAR chName[MAX_PATH] = {0};
	GetComputerName( chName, &iSize );//获取电脑名
	strFileSave += _T("_");
	strFileSave += chName;

	SYSTEMTIME st = {0};
	GetLocalTime( &st );//获得当前本地时间，作测试开始时间
	memset( chName, 0, sizeof(chName) );
	transformat( chName, _T("_0x%llx_%s.txt"), rcDataMsg.ReleaseID,  rcDataMsg.TestResult == TEST_PASS ? _T("Pass") : _T("Fail"));
	strFileSave += chName;
#endif

	return strFileSave;
}
tstring CTestResultSaveCloud::MakeRelativePath(unsigned int testRet, InternalItemInfo (&itemResult)[MAX_TEST_ITEMS], LPCTSTR szWorkStation, unsigned char simulate /* = 0 */)
{
	tstring szRelative = _T("/");
	if(NULL != G_XMLConfig->ftp_relative_path)
	{
		szRelative += G_XMLConfig->ftp_relative_path;
	}
	return szRelative;
}
tstring CTestResultSaveVSN::MakeRelativePath(unsigned int testRet, InternalItemInfo (&itemResult)[MAX_TEST_ITEMS], LPCTSTR szWorkStation, unsigned char simulate)
{
	tstring szRelative = _T("");
	TCHAR chName[MAX_PATH] = {0};

	if( TEST_PASS == testRet ){
		szRelative += _T("/Pass/");
	}
	else if( TEST_NG == testRet ){
		szRelative += _T("/Fail/");
	}
	else if( TEST_TBD == testRet ){
		szRelative += _T("/TBD/");
	}

	SYSTEMTIME st = {0};
	GetLocalTime( &st );
	memset( chName, 0, sizeof(chName) );
	transformat( chName, _T("%d-%02d-%02d"), st.wYear, st.wMonth, st.wDay );

	szRelative += chName;


	return szRelative;
}
tstring CTestResultSaveVSN::MakeFileNameToSave( const RecordData& rcDataMsg, unsigned char simulate)
{
	tstring szAbslute = _T("/");
	TCHAR chName[MAX_PATH] = {0};

	SYSTEMTIME st = {0};
	GetLocalTime( &st );
	memset( chName, 0, sizeof(chName) );
	transformat( chName, _T("%s_%s_%s_#%d_%d%02d%02d%02d%02d%02d"), G_XMLConfig->szProjectName, G_XMLConfig->szWorkStation,
		rcDataMsg.snCode , rcDataMsg.ucDevice, 
		st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond );

	szAbslute += chName;
	if( TEST_PASS == rcDataMsg.TestResult ){
		szAbslute += _T("_PassLog.txt");
	}
	else if( TEST_NG == rcDataMsg.TestResult ){
		szAbslute += _T("_Fail.txt");
	}
	else if( TEST_TBD == rcDataMsg.TestResult ){
		szAbslute += _T("_TBD.txt");
	}

	return szAbslute;
}

int CTestResultSaveEMS::UploadEms(string codenum, string id, string station, string result)
{
	return 0;
}
// tstring CTestResultSaveEDO::MakeFileFoderToSave( unsigned int testRet, InternalItemInfo (&itemResult)[MAX_TEST_ITEMS], LPCTSTR szWorkStation, unsigned char simulate/* = 0*/ )
// {
// 	tstring strFileSave;
// 
// 	if(NULL == G_XMLConfig->szLogPath || 0 == lengthof(G_XMLConfig->szLogPath))
// 	{
// 		return CTestResultSave::MakeFileFoderToSave(testRet, itemResult, szWorkStation, simulate);
// 	}
// 	else
// 	{
// 		TCHAR szTemp[MAX_PATH];
// 		CToolKit::UTF8ToGBK( G_XMLConfig->szLogPath, szTemp, MAX_PATH );
// 		strFileSave.append(szTemp);
// 
// 		SYSTEMTIME st = {0};
// 		GetLocalTime( &st );//获得当前本地时间，作测试开始时间
// 		memset( szTemp, 0, sizeof(szTemp) );
// 		transformat( szTemp, _T("%d-%02d-%02d"), st.wYear, st.wMonth, st.wDay );
// 		strFileSave += _T("/");
// 		strFileSave += szTemp;
// 
// 		if( TEST_PASS == testRet ){
// 			strFileSave += _T("/PASS");
// 		}
// 		else if( TEST_NG == testRet ){
// 			strFileSave += _T("/FAIL");
// 		}
// 		else if( TEST_TBD == testRet ){
// 			strFileSave += _T("/TBDLog");
// 		}
// 		else{
// 
// 		}
// 	}
// 
// 	return strFileSave;
// }


CTestBase::CTestBase()
	:m_deviceNo(0)
	// 	,m_bIsTestRuning(false)
	// 	,m_bInGraphing(false)
	// 	,m_bExitRuningLoop(false)
	// 	,m_bMtkBootUpdated(false)
	// 	,m_bGameOver(false)
	,m_iRealGraphIndex(0)
	,m_hThreadHandle(0)
	,m_mtkUpdateGate(FALSE)
{
	//memset( m_CurTestItemAddr, 0, sizeof(m_CurTestItemAddr) );
	//m_ColorText =  _T("this is mu text");
	InitTestStatus();
	memset( m_vecGraphTest, 0, sizeof(m_vecGraphTest) );
	memset( m_szSNCode, 0, sizeof(m_szSNCode) );

	//record_buffer = new unsigned char[2*1024];

	cpx_create_thread( m_hThreadHandle, NULL, TestThreadEntry, this );
}
CTestBase::~CTestBase()
{
	//delete[] record_buffer;
	for( int index = 0; index < MAX_GRAPH_ITEM; index++ )
	{
		if( m_vecGraphTest[index] )
			delete m_vecGraphTest[index];

		m_vecGraphTest[index] = 0;
	}
}
void CTestBase::SetTestContext( unsigned char deviceNo, NativeTestInterface* native )
{
	m_deviceNo = deviceNo;
	m_pNativeIntr = native;
}
BOOL CTestBase::MtkUpdateGate()
{
	return m_mtkUpdateGate;
}
unsigned int CTestBase::ActionToXmlConfig()
{
	if( START_BY_AUTO != G_XMLConfig->way_to_start )
		return ERROR_CODE_OK;
	if( NULL == SM_ChipBase( m_deviceNo ) ) 
		return ERROR_CODE_NO_KINDOF_IC;
	if( IsTestStillOnLine(this) )
		return ERROR_CODE_ONE_PROCESS_RUNING;

	SetOperationNormal(this);
	//m_hThreadHandle = (HANDLE)_beginthreadex( NULL, 0, TestThreadEntry, this, 0, NULL );

	return ERROR_CODE_OK;
}
bool CTestBase::MakeTestOver( unsigned char mustStopNow /* = 1 */ )
{
	//m_bExitRuningLoop = true;

	SetGameOver();

	for( int index = 0; index < MAX_GRAPH_ITEM; index++ )
	{
		CGraphItemTest* pGraphTest = m_vecGraphTest[index];
		if( NULL != pGraphTest ) 
		{
			pGraphTest->Exit();
		}
	}

	if( mustStopNow )
	{
		for( int index = 0; index < 10; index++ )
		{
			Sleep( 50 );
			if( !IsTestStillOnLine(this) ) break;
		}
		//if thread still not exit... kill it.
		if( IsTestStillOnLine(this) ) kill_thread( m_hThreadHandle, -1 );
	}

	return IsTestStillOnLine(this);
}
unsigned int CTestBase::WorkForGraphMode( bool bEnterGraphing /*= false*/ )
{
	unsigned int iReCode = ERROR_CODE_OK;

	if( bEnterGraphing && !IsTestInGraphStep() )
	{
		if( G_XMLConfig->w_clk > 0 )
		{
			iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_CTP_RST );
			CHECK_RETURN_IF_FAIL( iReCode );
			SysDelay( 70 );

			iReCode = SetClkInFctMode( G_XMLConfig->w_clk );
			CHECK_RETURN_IF_FAIL( iReCode );

			SysDelay( 50 );

			iReCode = SM_ChipBase(m_deviceNo)->SwitchMode( MODE_TOUCH, G_XMLConfig->sync_length );
			CHECK_RETURN_IF_FAIL( iReCode );
		}
	}
	else
	{

	}

	bEnterGraphing ? SetTestStatusInGraphStep() : SetTestStatusInDataStep();

	return iReCode;
}
unsigned int CTestBase::SetClkInFctMode( unsigned short clkDiv )
{
	unsigned char iReCode = ERROR_CODE_OK;

	unsigned short cfgBuffer[MAX_CFG_BIN_SIZE] = {0};
	iReCode = SM_ChipBase(m_deviceNo)->ReadCoreSpace( 0x9E00, (unsigned char*)cfgBuffer, 204 );
	CHECK_RETURN_IF_FAIL( iReCode );

	unsigned short check = caculate_check_sum_u16( cfgBuffer, 204 );
	if( check )  iReCode = ERROR_CODE_CHECK_SUM_MISMATCH;
	CHECK_RETURN_IF_FAIL( iReCode );

	cfgBuffer[2]  = clkDiv;
	cfgBuffer[59] = ( cfgBuffer[59] & 0xff ) + ( ( cfgBuffer[59] >> 1 ) & 0xff00 );

	//////////////////////////////////////////////////////////////////////////
	//filter off
	if(G_XMLConfig->filter_off)
	{
		cfgBuffer[57] &= 0xf7ff;
		cfgBuffer[59] &= 0x00ff;
		cfgBuffer[60] &= 0xfffE; 
	}

	if(G_XMLConfig->key_thr)
	{
		cfgBuffer[48] &= 0x00ff;
		cfgBuffer[48] |= G_XMLConfig->key_thr << 8;
	}

	unsigned short check16 = Sum( cfgBuffer, 101 );
	cfgBuffer[101] = 1 + (~check16);

	check = caculate_check_sum_u16( cfgBuffer, 204 );
	if( check )  iReCode = ERROR_CODE_CHECK_SUM_MISMATCH;
	CHECK_RETURN_IF_FAIL( iReCode );

	unsigned int cmd1[2] = { 0x35366798, 0x0c350055 };
	iReCode = SM_ChipBase(m_deviceNo)->WriteCoreSpace( 0x9f00, (unsigned char*)cmd1, 8 );
	CHECK_RETURN_IF_FAIL( iReCode );

	SysDelay( 300 );

	memset( cmd1, 0, sizeof(cmd1) );
	iReCode = SM_ChipBase(m_deviceNo)->ReadCoreSpace( 0x9f04, (unsigned char*)cmd1, 4 );
	CHECK_RETURN_IF_FAIL( iReCode );

	if( 0x0c300055 != cmd1[0] )
	{
		iReCode = ERROR_CODE_CHECK_RESPONSE_FAILED;
		CHECK_RETURN_IF_FAIL( iReCode );
	}

	iReCode = SM_ChipBase(m_deviceNo)->WriteCoreSpace( 0x9e00, (unsigned char*)cfgBuffer, 204 );
	CHECK_RETURN_IF_FAIL( iReCode );

	unsigned int cmd2[2] = { 0x35366798, 0xb73500aa };
	iReCode = SM_ChipBase(m_deviceNo)->WriteCoreSpace( 0x9f00, (unsigned char*)cmd2, 8 );
	CHECK_RETURN_IF_FAIL( iReCode );

	SysDelay( 100 );

	iReCode = SM_ChipBase(m_deviceNo)->ReadCoreSpace( 0x9f04, (unsigned char*)cmd2, 4 );
	CHECK_RETURN_IF_FAIL( iReCode );

	if( 0xb73000aa != cmd2[0] )
	{
		iReCode = ERROR_CODE_CHECK_RESPONSE_FAILED;
		CHECK_RETURN_IF_FAIL( iReCode );
	}

	return iReCode;
}
unsigned int CTestBase::MTKConnectTest( NativeTestItem& itemQuote )
{
	unsigned int iReCode = ERROR_CODE_OK, errorCount = 0;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );
	if( !SM_CommBase(m_deviceNo) )
		return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION );

	TCHAR chTemp[MAX_PATH] = {0};

	if( G_XMLConfig->mtk_selected )
	{
		unsigned int flags = 0;
		unsigned int curMtkVersion = 0xff;
// 		iReCode = SM_CommBase(m_deviceNo)->ReadFromUsbMemory( DEV_TYPE_ADDR, (unsigned char*)&flags, 4 );
// 		if( 0x7169616f == flags )
// 		{
// 		}

		iReCode = SM_CommBase(m_deviceNo)->ReadFromUsbMemory( SM_CommBase(m_deviceNo)->GET_MTK_VER_ADDR(), (unsigned char*)&flags, 4 );
		if( ( flags & 0xfff00000 ) == 0x61600000 ||( flags & 0xfff00000 ) == 0x80000000)
		{
			TCHAR chMtkVersion[MAX_PATH] = {0};
			curMtkVersion = flags & 0xfffff;
			m_stOneRecord.mtkVerson = curMtkVersion;
			transformat(chMtkVersion, _T("Mtk Version = 0x%x\r\n"), curMtkVersion);
			TestResultInfo( chMtkVersion );
		}

		transformat( chTemp, _T("MTK = %d"), m_deviceNo + 1 );

		if (G_XMLConfig->mtk_auto_update == 0)
		{
			if( curMtkVersion < G_XMLConfig->mtk_version )
			{
				errorCount++;
				transformat( chTemp, _T("MTK = %d, Ver = %x"), m_deviceNo + 1, curMtkVersion );
			}
		}
		else if (G_XMLConfig->mtk_auto_update == 1)
		{
			if(curMtkVersion < G_XMLConfig->mtk_version && ( G_XMLConfig->mtk_app_size > 0 ))
			{
				m_mtkUpdateGate = TRUE;
				iReCode = SM_CommBase(m_deviceNo)->PrepareMtkBoardUpgrade();
				SysDelay(100);
				m_mtkUpdateGate = FALSE;
				iReCode = SM_CommBase(m_deviceNo)->UpgradeMtkBoard( m_deviceNo, G_XMLConfig->mtk_app_bin, G_XMLConfig->mtk_app_size, OnUpdateMtkCallBack );

				flags = 0;
				iReCode = SM_CommBase(m_deviceNo)->ReadFromUsbMemory( SM_CommBase(m_deviceNo)->GET_MTK_VER_ADDR(), (unsigned char*)&flags, 4 );
				//if( ( flags & 0xfff00000 ) == 0x61600000 ||( flags & 0xfff00000 ) == 0x80000000 )
				{
					TCHAR chMtkVersion[MAX_PATH] = {0};
					curMtkVersion = flags & 0xfffff;
					transformat(chMtkVersion, _T("Mtk Version = 0x%x\r\n"), curMtkVersion);
					TestResultInfo( chMtkVersion );	
				}

				if( curMtkVersion < G_XMLConfig->mtk_version )
				{
					errorCount++;
					transformat( chTemp, _T("MTK = %d, Ver = %x"), m_deviceNo + 1, curMtkVersion );
				}
				
			}


		}
		else if (G_XMLConfig->mtk_auto_update == 2)
		{
			if( curMtkVersion != G_XMLConfig->mtk_version  && ( G_XMLConfig->mtk_app_size > 0 ))
			{
				m_mtkUpdateGate = TRUE;
				iReCode = SM_CommBase(m_deviceNo)->PrepareMtkBoardUpgrade();
				SysDelay(100);
				m_mtkUpdateGate = FALSE;
				iReCode = SM_CommBase(m_deviceNo)->UpgradeMtkBoard( m_deviceNo, G_XMLConfig->mtk_app_bin, G_XMLConfig->mtk_app_size, OnUpdateMtkCallBack );

				flags = 0;
				iReCode = SM_CommBase(m_deviceNo)->ReadFromUsbMemory( SM_CommBase(m_deviceNo)->GET_MTK_VER_ADDR(), (unsigned char*)&flags, 4 );
				//if( ( flags & 0xfff00000 ) == 0x61600000 )
				{
					TCHAR chMtkVersion[MAX_PATH] = {0};
					curMtkVersion = flags & 0xfffff;
					transformat(chMtkVersion, _T("Mtk Version = 0x%x\r\n"), curMtkVersion);
					TestResultInfo( chMtkVersion );	
				}
				if( curMtkVersion != G_XMLConfig->mtk_version )
				{
					errorCount++;
					transformat( chTemp, _T("MTK = %d, Ver = %x"), m_deviceNo + 1, curMtkVersion );
				
				}
			}
		}

		/*if( curMtkVersion >= G_XMLConfig->mtk_version && G_XMLConfig->mtk_auto_update <= 1)
		{
			transformat( chTemp, _T("MTK = %d"), m_deviceNo + 1 );
		}
		else
		{
			if( G_XMLConfig->mtk_auto_update == 0)
			{
				if( curMtkVersion < G_XMLConfig->mtk_version )
				{
					errorCount++;
					transformat( chTemp, _T("MTK = %d, Ver = %x"), m_deviceNo + 1, curMtkVersion );
				}
			
			}
			else if((G_XMLConfig->mtk_auto_update>0) && ( G_XMLConfig->mtk_app_size > 0 ) )
			{
				m_mtkUpdateGate = TRUE;
				iReCode = SM_CommBase(m_deviceNo)->PrepareMtkBoardUpgrade();
				SysDelay(100);
				m_mtkUpdateGate = FALSE;
				iReCode = SM_CommBase(m_deviceNo)->UpgradeMtkBoard( m_deviceNo, G_XMLConfig->mtk_app_bin, G_XMLConfig->mtk_app_size, OnUpdateMtkCallBack );
			
				flags = 0;
				iReCode = SM_CommBase(m_deviceNo)->ReadFromUsbMemory( SM_CommBase(m_deviceNo)->GET_MTK_VER_ADDR(), (unsigned char*)&flags, 4 );
				if( ( flags & 0xfff00000 ) == 0x61600000 )
				{
					TCHAR chMtkVersion[MAX_PATH] = {0};
					curMtkVersion = flags & 0xfffff;
					transformat(chMtkVersion, _T("Mtk Version = 0x%x\r\n"), curMtkVersion);
					TestResultInfo( chMtkVersion );	
				}
				if(G_XMLConfig->mtk_auto_update==1)
				{
					if( curMtkVersion < G_XMLConfig->mtk_version )
					{
						errorCount++;
						transformat( chTemp, _T("MTK = %d, Ver = %x"), m_deviceNo + 1, curMtkVersion );
					}
				}
				if(G_XMLConfig->mtk_auto_update > 1)
				{
					if( curMtkVersion != G_XMLConfig->mtk_version )
					{
						errorCount++;
						transformat( chTemp, _T("MTK = %d, Ver = %x"), m_deviceNo + 1, curMtkVersion );
					}
				}

			}
				
		}*/
	}
	else
	{
		transformat( chTemp, _T("MTK = %d"), m_deviceNo + 1 );
		if( !SM_CommBase(m_deviceNo)->Connected() )
			errorCount++;
	}

	iReCode = SM_ChipBase(m_deviceNo)->HaveTpLinked( 3 );

	if( errorCount )
		return itemNotify.UpdateItemResult( ITEM_STA_FAIL, chTemp ); 
	else
		return itemNotify.UpdateItemResult( ITEM_STA_PASS, chTemp );
}
unsigned int CTestBase::TP_WaitTest( NativeTestItem& itemQuote )
{
	unsigned int iReCode = ERROR_CODE_OK;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );

	while( IsLoopStillRun() )
	{
		if( SM_ChipBase(m_deviceNo)->HaveTpLinked() ) break;

		itemNotify.UpdateItemResult( ITEM_STA_WAIT );
		//::Sleep( 500 );

		if( SM_ChipBase(m_deviceNo)->HaveTpLinked() ) break;

		itemNotify.UpdateItemResult( ITEM_STA_START );
		//::Sleep( 500 );
	}

	SysDelay( 50 );

	return itemNotify.UpdateItemResult( ITEM_STA_PASS );
}
unsigned int CTestBase::TP_RemoveTest( NativeTestItem& itemQuote )
{
	unsigned int iReCode = ERROR_CODE_OK;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );

	//test is over, wait tp remove
	//navCallBack.onOneTestOver( m_deviceNo, FinalResult() );

	while( IsLoopStillRun() )
	{
		if( !SM_ChipBase(m_deviceNo)->HaveTpLinked() ) break;

		itemNotify.UpdateItemResult( ITEM_STA_WAIT );
		//::Sleep( 300 );

		if( !SM_ChipBase(m_deviceNo)->HaveTpLinked() ) break;

		itemNotify.UpdateItemResult( ITEM_STA_START );
		//::Sleep( 300 );
	}

	return itemNotify.UpdateItemResult( ITEM_STA_PASS );/*SM_CommBase( m_deviceNo )->Connected() ? itemNotify.UpdateItemResult( ITEM_STA_PASS ) : itemNotify.UpdateItemResult( ITEM_STA_FAIL );*/
}
NativeTestItem& CTestBase::GetNativeTestItemByIndex( int index )
{
	static NativeTestItem emptyItem;

	if( index < 0 ) return emptyItem;
	if( index >= MAX_TEST_ITEMS ) return emptyItem;

	if( m_arrayItemInfo[index].bSelected )
		return m_arrayItemInfo[index].item;
	else
		return emptyItem;
}
InternalItemInfo* CTestBase::GetInternalItemInfoByID( unsigned char testCode )
{
	InternalItemInfo* pInfo = NULL;
	for( int index = 0; index < MAX_TEST_ITEMS; index++ )
	{
		if( testCode == m_arrayItemInfo[index].item.testCode )
		{
			pInfo = &m_arrayItemInfo[index];
			break;
		}
	}
	return pInfo;
}
// list<NativeTestItem>& CTestBase::GetAllTestItemLists()
// {
// 	return m_listTestItems;
// }
ColorText& CTestBase::GetTestMessage()
{
	return m_ColorText;
}
void CTestBase::CleanLastResult()
{
	ICommBase* pCommBase = SM_CommBase(m_deviceNo);
	if( pCommBase )
	{
		pCommBase->SetMtkExternOutput( 0, 0, 0 );
	}

	m_ColorText = _T("");

	for( int index = 0; index < MAX_TEST_ITEMS; index++ )
	{
		InternalItemInfo& info = m_arrayItemInfo[index];
		if( info.bSelected )
		{
			info.item.testResult = ITEM_STA_NONE;
			memset( info.item.testMark, 0, sizeof(info.item.testMark) );
		}
	}

	m_stOneRecord.ReleaseID = 0;
	m_stOneRecord.Mcap.oscTrim = 0;
	m_stOneRecord.Scap.oscTrim = 0;
	
}
unsigned int CTestBase::SimulateTest( int iDevice, SimulateData (&arraySimulate)[SIMULATE_TEST_DATA_CNT] )
{
	ICommBase* fake = SM_CommBase(m_deviceNo);

	if( fake == NULL )  return ERROR_CODE_NO_DEVICE;

	for( int index = 0; index < SIMULATE_TEST_DATA_CNT; index++ )
	{
		SimulateData& sm = arraySimulate[index];
		if( 0 == sm.itemID ) continue;

		PrepareSimulate( sm );
	}

	SetSimulateGate( TRUE );

	fake->SetSimulateContext( (LPVOID)&arraySimulate );

	for( int index = 0; index < MAX_TEST_ITEMS; index++ )
	{
		InternalItemInfo& info = m_arrayItemInfo[index];
		if( info.item.testCode <= TEST_ITEM_SHARE_ALL )
			info.bSelected = false;
		else if( info.item.testCode >= TEST_ITEM_SIMULATE_TEST_MAX )
			info.bSelected = false;
	}

	//simulate = TRUE
	TestFlow( TRUE );

	SetSimulateGate( FALSE );

	return ERROR_CODE_OK;
}

SYSTEMTIME CTestBase::StartTestTime()
{
    static SYSTEMTIME t;
    ::GetLocalTime( &t );
    return t;
}

unsigned int CTestBase::StartTest( LPCTSTR szCode/* = NULL*/ )
{
	if( NULL == G_XMLConfig ) 
		return ERROR_CODE_INVALID_PARAM;
    if (OP_LIKE_LS == G_XMLConfig->selected_format)
    {
        m_StartTime = StartTestTime();
    }
	if( NULL == SM_ChipBase( m_deviceNo ) ) 
		return ERROR_CODE_NO_KINDOF_IC;
	if( NULL == SM_CommBase( m_deviceNo ) )
		return ERROR_CODE_NO_DEVICE;
	if( IsTestStillOnLine(this) )
		return ERROR_CODE_ONE_PROCESS_RUNING;

	SetOperationNormal(this);
	memset( m_szSNCode, 0, sizeof(m_szSNCode) );
	if( NULL != szCode ) copytextto( m_szSNCode, szCode, min( lengthof(szCode), 100 ) );
	//_beginthreadex( NULL, 0, TestThreadEntry, this, 0, NULL );

	return ERROR_CODE_OK;
}
unsigned int CTestBase::SendTestRz( LPCTSTR sdCode/* = NULL*/ )
{
    if( NULL == G_XMLConfig ) 
        return ERROR_CODE_INVALID_PARAM;
    if( NULL == SM_ChipBase( m_deviceNo ) ) 
        return ERROR_CODE_NO_KINDOF_IC;
    memset( m_szDisplayCode, 0, sizeof(m_szDisplayCode) );
    if( NULL != sdCode ) copytextto( m_szDisplayCode, sdCode, min( lengthof(sdCode), 20 ) );
    //_beginthreadex( NULL, 0, TestThreadEntry, this, 0, NULL );

    return ERROR_CODE_OK;
}
entry_type WINAPI CTestBase::TestThreadEntry( LPVOID lp )
{
	CTestBase* ptrTest = (CTestBase*)lp;

	::Sleep( 100 );

	if( IsTestStillOnLine(ptrTest) ) 
		return (entry_type)-1;
	while( !IsGameOver(ptrTest) )
	{
		unsigned int signals = 0;
		ICommBase* pCommBase = SM_CommBase(ptrTest->m_deviceNo);
		if( pCommBase && ERROR_CODE_WRITE_USB_ERROR != pCommBase->ReadFromUsbMemory( pCommBase->GET_MTK_DEVICE_NO_ADDR(), (unsigned char*)&signals, 4 ) )
		//if( pCommBase && ERROR_CODE_WRITE_USB_ERROR != pCommBase->DetectMtkExtendSignal( &signals ) )
		{
			auto a = (char)(signals >> 8);
			if( 't' == ((char)(signals >> 8)) )
			{
				SetOperationNormal(ptrTest);
			}

			if( DoOperationNarmal(ptrTest) ) 
			{
				ptrTest->TestFlow( );
			}
			if( DoOperationForcePaint(ptrTest) )
			{
				//SetOperationEmpty(ptrTest);
				SetOperationNormal(ptrTest);
				ptrTest->ForcePaintFlow();
			}
			else
			{

			}
		}
		else
		{
			Sleep( 500 );
		}

		if( START_BY_AUTO != G_XMLConfig->way_to_start )
		{
			SetOperationEmpty(ptrTest);
		}
		Sleep( 200 );
	}

	return 0;
}
//UINT32 WINAPI CTestBase::AutoTestThreadEntry( LPVOID lp )
// {
// 	CTestBase* ptrTest = (CTestBase*)lp;
// 
// 	::Sleep( 500 );
// 
// 	while( !ptrTest->ExitRuningLoop() )
// 	{
// 		ptrTest->TestFlow();
// 	}
// 
// 	return 0;
// }
bool CTestBase::CheckIfNeedUpdateMtkBoot()
{
#ifdef _MSC_VER
	unsigned int iReCode = 0;//= SM_ChipBase(m_deviceNo)->CheckCatchBootToMtk( 0xd000, G_XMLConfig->bootBinBuffer, G_XMLConfig->bootBinSize, OnCopyBootCallBack );

	if( iReCode == ERROR_CODE_OK )
	{
		//SetMtkUpdatedMark();
		return true;
	}
	else
	{
		TestResultInfo( _T("UpDate Mtk Boot Error\r\n") );
		return false;
	}
#endif

	return true;
}
int CTestBase::SelectedItemCont()
{
	int counter = 0;
	for( int index = 0; index < MAX_TEST_ITEMS; index++ )
	{
		InternalItemInfo& info = m_arrayItemInfo[index];
		if( info.bSelected ) counter++;
	}

	return counter;
}
void CTestBase::TestFlow( unsigned char simulate /*= 0 */)
{
	SetLoopRuning();
	SetTestFlowOnLine( );
	m_stOneRecord.DoInit( m_szSNCode );
	WorkForGraphMode( false );

	if( simulate ? true : CheckIfNeedUpdateMtkBoot() )
	{
		CleanLastResult();
		if( ERROR_CODE_OK == navCallBack.onOneTestStart( m_deviceNo ) )
		{
			unsigned char chipFamily = GetContainerInterface()->GetChipFamily( G_XMLConfig->IcType );
			if(chipFamily == (SEMI_IC_5472>>8)||chipFamily == (SEMI_IC_7449>>8))
			{	
				SM_ChipBase(m_deviceNo)->IncokeCommand(CMD_CHK_CFG, 0, (chipFamily << 8) | 0x5c, (G_XMLConfig->Speed << 8) | G_XMLConfig->protocalType);//改变ramcode地址
			}
			else if(chipFamily == (SEMI_IC_CHGA8006>>8))
			{
				SM_ChipBase(m_deviceNo)->IncokeCommand(CMD_CHK_CFG, 0, (chipFamily << 8) | 0x6c, (G_XMLConfig->Speed << 8) | G_XMLConfig->protocalType);//改变ramcode地址
			}
			int itemFinished = 0, allItemCount = SelectedItemCont();
			navCallBack.onProcssBarChanging( m_deviceNo, 0, allItemCount );

			bool jumpTest = false;
			TestResultInfo(TestAppVersion);
			TCHAR szTemp[MAX_PATH] = {0};
			transformat(szTemp, _T("\r\nWorkStation: %s   ProjectName: %s\r\n"), G_XMLConfig->szWorkStation, G_XMLConfig->szProjectName);
			TestResultInfo(szTemp);

			InternalItemInfo* pMtkConnect = GetInternalItemInfoByID(TEST_ITEM_MTK_CONNECT);
			if( NULL != pMtkConnect && pMtkConnect->bSelected )
			{
				ItemTestByItemQuote( *pMtkConnect );	
			}

			InternalItemInfo* pTpWait = GetInternalItemInfoByID(TEST_ITEM_TP_WAIT);
			if( NULL != pTpWait && pTpWait->bSelected )
			{
				ItemTestByItemQuote( *pTpWait );	

				SysDelay(G_XMLConfig->hold_up);
			}

			SM_CommBase(m_deviceNo)->SetIoVoltage( G_XMLConfig->vddVotage, G_XMLConfig->ioVddVotage, G_XMLConfig->vihVotage );
			SysDelay( 80 );

			for( int index = 0; IsLoopStillRun() && index < MAX_TEST_ITEMS; index++ )
			{
				InternalItemInfo& info = m_arrayItemInfo[index];
				if( !info.bSelected ) continue;
				if( jumpTest && info.jumpIfNG ) continue;
				if(info.item.testCode < TEST_ITEM_FACTORY_REAL) continue;

				TEST_ITEM_STATUS itemResult = ItemTestByItemQuote( info );

				if( m_pNativeIntr->ErrStop() && !simulate && itemResult >= ITEM_STA_FAIL )
				{
					MakeTestOver( 0 );
					break;
				}

				//fix some bug
				if( ITEM_STA_EXCEPTION == itemResult )
				{
					SysDelay( 350 );
					itemResult = ItemTestByItemQuote( info );
				}

				if( ITEM_STA_EXCEPTION == itemResult )
				{
					SysDelay( 350 );
					itemResult = ItemTestByItemQuote( info );
				}

				info.item.testResult = itemResult;
				navCallBack.onProcssBarChanging( m_deviceNo, itemFinished++, allItemCount );

				if( !m_pNativeIntr->DebugMode() && !simulate && itemResult >= ITEM_STA_FAIL )
					jumpTest = true;
			}

			if( IsLoopStillRun() )
			{
				navCallBack.onProcssBarChanging( m_deviceNo, allItemCount, allItemCount );
				EN_TEST_RESULT finalRet = FinalResult();
				SaveResult( finalRet, simulate );
				navCallBack.onOneTestOver( m_deviceNo, finalRet );
			}

			if(G_XMLConfig->heatbeatVotage > 0)
			{
				SM_CommBase(m_deviceNo)->SetIoVoltage( G_XMLConfig->heatbeatVotage, 0x00, 0 );	
			}

			InternalItemInfo* pTpRemove = GetInternalItemInfoByID(TEST_ITEM_TP_REMOVE);
			if( NULL != pTpRemove && pTpRemove->bSelected )
			{
				ItemTestByItemQuote( *pTpRemove );	

				if(!SM_ChipBase(m_deviceNo)->HaveTpLinked())
				{
					navCallBack.onOneTestOver( m_deviceNo, TEST_NONE );
					SM_CommBase(m_deviceNo)->SetMtkExternOutput( 0, 0, 0 );
				}
			}
		}
		else
		{
			navCallBack.onOneTestOver( m_deviceNo, TEST_NG );
		}
	}

	SetTestFlowOffLine( );
}

LONGLONG SystemTimeToTimestamp(const SYSTEMTIME& st)
{
    FILETIME ft;

    if (!SystemTimeToFileTime(&st, &ft))
    {
        return -1;
    }

    ULARGE_INTEGER uli;
    uli.LowPart = ft.dwLowDateTime;
    uli.HighPart = ft.dwHighDateTime;

    //return ms
    return uli.QuadPart / 10000;
}

double CalculateTimeDifferenceInSeconds(const SYSTEMTIME& st1, const SYSTEMTIME& st2)
{
    LONGLONG ts1 = SystemTimeToTimestamp(st1);
    LONGLONG ts2 = SystemTimeToTimestamp(st2);

    if (ts1 == -1 || ts2 == -1)
    {
        return -1.0;
    }

    return abs(static_cast<double>(ts2 - ts1)) / 1000.0;
}

typedef int(*Dllfun)(int, string);
void CTestBase::SaveResult( EN_TEST_RESULT& finalResult, unsigned char simulate /*= 0 */)
{
	if( NULL == G_XMLConfig ) return;

	//RecordData testRecord;
	
 	m_stOneRecord.ucDevice = m_deviceNo;
	m_stOneRecord.TestResult = finalResult;
	m_stOneRecord.ChipType = G_XMLConfig->IcType;/*0x3535*/
	m_stOneRecord.RealSize = G_XMLConfig->real_channel_num;
	m_stOneRecord.VaChannelNum = G_XMLConfig->va_channel_num;
	m_stOneRecord.channelX = G_XMLConfig->rowsCnt;
	m_stOneRecord.channelY = G_XMLConfig->colsCnt;
	CToolKit::UTF8ToGBK( G_XMLConfig->szWorkStation, (TCHAR*)m_stOneRecord.workStation, sizeof(m_stOneRecord.workStation) );
	//memcpy_s( m_stOneRecord.workStation, sizeof(m_stOneRecord.workStation), G_XMLConfig->szWorkStation, sizeof(m_stOneRecord.workStation) );

	//standard
	if(OP_LIKE_DEFAULT == G_XMLConfig->selected_format)
	{
		CTestResultSave save;
		save.SaveTestResult( m_ColorText, m_stOneRecord, m_arrayItemInfo, simulate );
	}
	else if(OP_LIKE_ICID == G_XMLConfig->selected_format)
	{
		CTestResultSaveID save;
		save.SaveTestResult( m_ColorText, m_stOneRecord, m_arrayItemInfo, simulate );
	}
	else if(OP_LIKE_YY == G_XMLConfig->selected_format)
	{
		CTestResultSaveYY save;
		save.SaveTestResult( m_ColorText, m_stOneRecord, m_arrayItemInfo, simulate );
	}
	else if(OP_LIKE_EDO == G_XMLConfig->selected_format)
	{
		CTestResultSaveEDO save;
		save.SaveTestResult( m_ColorText, m_stOneRecord, m_arrayItemInfo, simulate );
	}
	else if(OP_LIKE_CLOUD == G_XMLConfig->selected_format)
	{
		CTestResultSaveCloud save;
		save.SaveTestResult( m_ColorText, m_stOneRecord, m_arrayItemInfo, simulate );
	}
	else if(OP_LIKE_VSN == G_XMLConfig->selected_format)
	{
		CTestResultSaveVSN save;
		save.SaveTestResult( m_ColorText, m_stOneRecord, m_arrayItemInfo, simulate );
	}
	else if(OP_LIKE_EMS == G_XMLConfig->selected_format)
	{
		string id = G_XMLConfig->customv2_device_id;
		string name = G_XMLConfig->customv2_process_name;
		string result = finalResult != TEST_PASS ? "N":"G";
		string snnum =  GetSnNumber();
		string infor = snnum+'^'+ id +'^'+ name +'^' + result;

		UpLoadInfo info;
		info.codenum = OP_LIKE_EMS;
		memcpy_s( info.str, 51200, (LPCSTR)infor.c_str(), infor.size());

		CTestResultSaveEMS save;

		if (finalResult == TEST_PASS)
		{
			auto ret = navCallBack.onInforUpload(&info);//产测成功才上传ems
			if (ret->codenum!=0)
			{
				m_stOneRecord.TestResult = TEST_NG;
				finalResult = TEST_NG;
				TestResultInfo( _T("\r\n//Upload EMS Fail\r\n"),ITEM_STA_FAIL );
				TestResultInfo(ret->str);
			}
			else
			{
				TestResultInfo( _T("\r\n//Upload EMS success\r\n"),ITEM_STA_PASS );
			}

		}
			
		save.SaveTestResult( m_ColorText, m_stOneRecord, m_arrayItemInfo, simulate );
	}
	else if(OP_LIKE_EMS_OFILM == G_XMLConfig->selected_format)
	{

		string userId= G_XMLConfig->costom_ofilm_userId;
		string fixtureId= G_XMLConfig->costom_ofilm_fixtureId;
		string eqpId= G_XMLConfig->costom_ofilm_eqpId;
		string mesUrl= G_XMLConfig->costom_ofilm_mesUrl;
		string stepId= G_XMLConfig->costom_ofilm_stepId;
		string testStepId= G_XMLConfig->costom_ofilm_testStepId;
		string macAddress= G_XMLConfig->costom_ofilm_macAddress;
		string IsPass = finalResult != TEST_PASS ? "N":"G";
		string SerialNumber =  GetSnNumber();
		//string ChipId = std::to_string(m_stOneRecord.ReleaseID);
		char str[20];
		std::sprintf(str,"%llX",m_stOneRecord.ReleaseID);
		string ChipId = str;

		string infor = mesUrl+'^'+ userId +'^'+ eqpId +'^' + stepId+'^' + SerialNumber+'^' + ChipId+'^' + testStepId+'^' + IsPass+'^' + macAddress+'^' + fixtureId;

		UpLoadInfo info;
		info.codenum = OP_LIKE_EMS_OFILM;
		memcpy_s( info.str, 51200, (LPCSTR)infor.c_str(), infor.size());
		CTestResultSaveEmsOfilm save;

		auto ret = navCallBack.onInforUpload(&info);

		if (ret->codenum!=0)
		{
			m_stOneRecord.TestResult = TEST_NG;
			finalResult = TEST_NG;
			TestResultInfo( _T("\r\n//Upload EMS Fail\r\n"),ITEM_STA_FAIL );
			TestResultInfo(ret->str);

		}
		else
		{
			TestResultInfo( _T("\r\n//Upload EMS success\r\n"),ITEM_STA_PASS );
		}

		save.SaveTestResult( m_ColorText, m_stOneRecord, m_arrayItemInfo, simulate );
	}
	else if(OP_LIKE_EMS_PBH == G_XMLConfig->selected_format)
	{

		string mesUrl      = G_XMLConfig->costom_pbh_mesUrl;
		string fixtureId   = G_XMLConfig->costom_pbh_fixtureId;
		string testStepId  = G_XMLConfig->costom_pbh_testStepId;
		string stationId   = G_XMLConfig->costom_pbh_stationId;
		string userId      = G_XMLConfig->costom_pbh_userId;
		string passWord    = G_XMLConfig->costom_pbh_passWord;

		string isPass = finalResult != TEST_PASS ? "FAIL":"PASS";
		string serialNumber =  GetSnNumber();

		string infor = mesUrl + '^' + fixtureId + '^' + testStepId + '^'+ stationId +'^'+ userId +'^' + passWord+'^' + serialNumber+'^' + isPass;

		UpLoadInfo info;
		info.codenum = OP_LIKE_EMS_PBH;
		memcpy_s( info.str, 51200, (LPCSTR)infor.c_str(), infor.size());
		CTestResultSavePbh save;

		auto ret = navCallBack.onInforUpload(&info);

		if (ret->codenum!=0)
		{
			m_stOneRecord.TestResult = TEST_NG;
			finalResult = TEST_NG;
			TestResultInfo( _T("\r\n//Upload EMS Fail\r\n"),ITEM_STA_FAIL );
			TestResultInfo(ret->str);

		}
		else
		{
			TestResultInfo( _T("\r\n//Upload EMS success\r\n"),ITEM_STA_PASS );
			TestResultInfo(ret->str);
		}

		save.SaveTestResult( m_ColorText, m_stOneRecord, m_arrayItemInfo, simulate );
	}
	else if(OP_LIKE_XY == G_XMLConfig->selected_format)
	{
		CTestResultSaveXY save;
		string sn_num =  GetSnNumber();
		if (sn_num!="")TestResultInfo("SN_CODE:"+sn_num);		
		save.SaveTestResult( m_ColorText, m_stOneRecord, m_arrayItemInfo, simulate );
	}
	else if(OP_LIKE_VISIONOX == G_XMLConfig->selected_format)
	{
		CTestResultSaveVisionox save;
		string sn_num =  GetSnNumber();
		if (sn_num!="")TestResultInfo("SN_CODE:"+sn_num);		
		save.SaveTestResult( m_ColorText, m_stOneRecord, m_arrayItemInfo, simulate );
	}
	else if(OP_LIKE_JW == G_XMLConfig->selected_format)
	{
		CTestResultSaveJW save;
		string sn_num =  GetSnNumber();
		if (sn_num!="")TestResultInfo("SN_CODE:"+sn_num);		
		save.SaveTestResult( m_ColorText, m_stOneRecord, m_arrayItemInfo, simulate );
	}
	else if(OP_LIKE_CHUANGWEI == G_XMLConfig->selected_format)
	{
		CTestResultSaveChuangWei save;

		string mesUrl        = G_XMLConfig->costom_ChuangWei_mesUrl;
		string user          = G_XMLConfig->costom_ChuangWei_usercode;
		string processcode   = G_XMLConfig->costom_ChuangWei_processcode;
		string linecode      = G_XMLConfig->costom_ChuangWei_linecode;
		string barcode       = GetSnNumber();
		string result        = finalResult != TEST_PASS ? "NG":"OK";
		string message       = G_XMLConfig->costom_ChuangWei_message;

		string simulationUp  = G_XMLConfig->costom_ChuangWei_simulationUp;
		string orderno       = G_XMLConfig->costom_ChuangWei_orderno;
		string macAddress    = G_XMLConfig->costom_ChuangWei_macAddress;
		string failReason    =  save.GetFailReason( m_arrayItemInfo );

		string infor = mesUrl + '^' + user + '^' + processcode + '^'+ linecode +'^'+ barcode +'^'+ result +'^' + message+ '^'+ simulationUp +'^' + orderno +'^' + TestAppVersion +'^'+ macAddress+'^'+failReason;
		
		UpLoadInfo info;
		info.codenum = OP_LIKE_CHUANGWEI;
		memcpy_s( info.str, 51200, (LPCSTR)infor.c_str(), infor.size());
		

		auto ret = navCallBack.onInforUpload(&info);

		if (ret->codenum!=0)
		{
			m_stOneRecord.TestResult = TEST_NG;
			finalResult = TEST_NG;
			TestResultInfo( _T("\r\n//Upload EMS Fail\r\n"),ITEM_STA_FAIL );
			TestResultInfo(ret->str);

		}
		else
		{
			TestResultInfo( _T("\r\n//Upload EMS success\r\n"),ITEM_STA_PASS );
			TestResultInfo(ret->str);
		}

		string sn_num =  GetSnNumber();
		if (sn_num!="")TestResultInfo("SN_CODE:"+sn_num);

		save.SaveTestResult( m_ColorText, m_stOneRecord, m_arrayItemInfo, simulate );
	}
    else if(OP_LIKE_HES == G_XMLConfig->selected_format)
    {
        CTestResultSaveHes save;

        string mesUrl = G_XMLConfig->costom_Hes_mesUrl;
        string machine_no = G_XMLConfig->costom_Hes_machine_no;
        string lot_no = G_XMLConfig->costom_Hes_lot_no;
        string subop_no  = G_XMLConfig->costom_Hes_subop_no;
        string person = G_XMLConfig->costom_Hes_person;
        string barcode       = GetSnNumber();
        string result        = finalResult != TEST_PASS ? "0":"1";
        string failReason    =  save.GetFailReasonID( m_arrayItemInfo );
        unsigned short ic_type = (G_XMLConfig->IcType >> 8);
        string s_ic_type ="1";//multi_cap
        if ((G_XMLConfig->IcType >> 8) == 2) //3536
        {
            s_ic_type = "0";
        }
        string infor = mesUrl + '^' +machine_no + '^' + lot_no + '^'+ subop_no +'^'+ person +'^' + barcode +'^'+ result +'^'+failReason+'^'+ s_ic_type;

        UpLoadInfo info;
        info.codenum = OP_LIKE_HES;
        memcpy_s( info.str, 51200, (LPCSTR)infor.c_str(), infor.size());


        auto ret = navCallBack.onInforUpload(&info);

        if (ret->codenum != 0)
        {
            m_stOneRecord.TestResult = TEST_NG;
            finalResult = TEST_NG;
            TestResultInfo( _T("\r\n//Upload MES Fail\r\n"),ITEM_STA_FAIL );
            TestResultInfo(ret->str);
        }
        else
        {
            TestResultInfo( _T("\r\n//Upload MES success\r\n"),ITEM_STA_PASS );
            TestResultInfo(ret->str);
        }


        if (barcode!="")TestResultInfo("SN_CODE:"+barcode);

        save.SaveTestResult( m_ColorText, m_stOneRecord, m_arrayItemInfo, simulate );
    }
    else if(OP_LIKE_LS == G_XMLConfig->selected_format)
    {
        CTestResultSaveLS save;

        string MesUrl = G_XMLConfig->costom_Ls_mesUrl;
        string Resource_no = G_XMLConfig->costom_Ls_resource_no;
        string Special_Code = G_XMLConfig->costom_Ls_special_code;
        string Operator_Ls  = G_XMLConfig->costom_Ls_operator;
        string Device_num = G_XMLConfig->costom_Ls_device_num;
        string Barcode       = GetSnNumber();
        unsigned char DisplayTestEn = G_XMLConfig->costom_Ls_displaytest;
        string Result        = finalResult != TEST_PASS ? "FAIL":"PASS";
        string FailReason    =  save.GetFailReason( m_arrayItemInfo );
        string DisplayEn = "0";
        if (1 == DisplayTestEn)
        {
            DisplayEn = "1";
            Result = GetDisplayRz();
            FailReason = "Display Test Fail";
        }
        SYSTEMTIME st01 = m_StartTime;
        SYSTEMTIME st02 = {0};
        GetLocalTime(&st02);
        double diffSeconds = CalculateTimeDifferenceInSeconds(st01, st02);
        TCHAR chName[MAX_PATH] = {0};
        //memset( chName, 0, sizeof(chName) );
        transformat( chName, _T("%04d-%02d-%02d %02d:%02d:%02d "), st01.wYear, st01.wMonth, st01.wDay, st01.wHour, st01.wMinute, st01.wSecond );
        string StartTime = chName;
        string TestTime;
        if (diffSeconds >= 0.0)
        {
            char szTempBuf[32] = {0}; 
            sprintf_s(szTempBuf, sizeof(szTempBuf), "%.1f s", diffSeconds);
            TestTime = szTempBuf;
        }
        else
        {
            TestTime = "20.1 s";
        }

        string logContent = m_ColorText;

        //int count_l = logContent.size();
        //char debugBuf[256] = {0};
        //sprintf_s(debugBuf, "Log Content Length: %d chars, First 100 chars: %.100s", 
        //    count_l, logContent.c_str());
        //OutputDebugStringA(debugBuf);
        //OutputDebugStringA("\n");

        //string Infor = MesUrl + '^' +Resource_no + '^' + Special_Code + '^'+ Operator_Ls +'^'+ Device_num +'^' + Barcode +'^'+ Result +'^' + FailReason +'^'+ TestAppVersion +'^'+ StartTime  +'^' + TestTime +'^' + DisplayEn+'^' + logContent;

        std::stringstream ss;
        ss.str().reserve(102400);

         ss << MesUrl << '^'
            << Resource_no << '^'
            << Special_Code << '^'
            << Operator_Ls << '^'
            << Device_num << '^'
            << Barcode << '^'
            << Result << '^'
            << FailReason << '^'
            << TestAppVersion << '^'
            << StartTime << '^'
            << TestTime << '^'
            << DisplayEn << '^'
            << logContent;

        string Infor = ss.str();

        UpLoadInfo info;
        info.codenum = OP_LIKE_LS;
        memcpy_s( info.str, 51200, (LPCSTR)Infor.c_str(), Infor.size());
        auto ret = navCallBack.onInforUpload(&info);

        if (ret->codenum!=0)
        {
            m_stOneRecord.TestResult = TEST_NG;
            finalResult = TEST_NG;
            TestResultInfo( _T("\r\n//Upload MES Fail\r\n"),ITEM_STA_FAIL );
            TestResultInfo(ret->str);
        }
        else
        {
            TestResultInfo( _T("\r\n//Upload MES success\r\n"),ITEM_STA_PASS );
            TestResultInfo(ret->str);
        }

        if (Barcode!="")TestResultInfo("\r\nSN_CODE:"+Barcode);

        save.SaveTestResult( m_ColorText, m_stOneRecord, m_arrayItemInfo, simulate );
    }
	else
	{
		CTestResultSaveID save;
		save.SaveTestResult( m_ColorText, m_stOneRecord, m_arrayItemInfo, simulate );
	}

	SysDelay(30);
	if( SM_CommBase(m_deviceNo) )
	{
		SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_CTP_RST );
		if(m_stOneRecord.mtkVerson < 0x91223)
		{
			SM_CommBase(m_deviceNo)->SetMtkExternOutput( finalResult, 0, 0 );
		}
		else
		{
			if(TEST_PASS == finalResult)
				SM_CommBase(m_deviceNo)->SetMtkExternOutput( 1, 0, 0 );
			else 
				SM_CommBase(m_deviceNo)->SetMtkExternOutput( 0, 1, 0 );
		}
	}
}
EN_TEST_RESULT CTestBase::FinalResult()
{
	EN_TEST_RESULT finalTestResult = TEST_PASS;

	for( int index = 0; index < MAX_TEST_ITEMS; index++ )
	{
		InternalItemInfo& info = m_arrayItemInfo[index];
		if( !info.bSelected ) continue;
		if( TEST_ITEM_TP_REMOVE == info.item.testCode ) continue;

		NativeTestItem& item = info.item;
		if( ITEM_STA_FAIL == item.testResult )
		{
			finalTestResult = TEST_NG;
			break;
		}
		if( ITEM_STA_NONE == item.testResult )
		{
			finalTestResult = TEST_NG;
			break;
		}
		if( ITEM_STA_EXCEPTION == item.testResult )
		{
			finalTestResult = TEST_NG;
			break;
		}
		if( ITEM_STA_TBD == item.testResult )
		{
			finalTestResult = TEST_TBD;
		}
	}

	if( finalTestResult == TEST_PASS )
		TestResultInfo( "\r\n\r\n//Final result is Pass\r\n", ITEM_STA_PASS );
	else if( finalTestResult == TEST_NG )
		TestResultInfo( "\r\n\r\n//Final result is NG\r\n", ITEM_STA_FAIL );
	else if( finalTestResult == TEST_TBD )
		TestResultInfo( "\r\n\r\n//Final result is TBD\r\n", ITEM_STA_TBD );
	else{ }

	return finalTestResult;
}
TEST_ITEM_STATUS CTestBase::ItemTestByItemQuote( InternalItemInfo& itemQuote )
{
	if( itemQuote.item.testCode >= MAX_TEST_ITEMS )
		return ITEM_STA_EXCEPTION;
	if( NULL == itemQuote.funAddr )
		return ITEM_STA_EXCEPTION;

	if( m_pNativeIntr->DebugMode() )
	{
		SYSTEMTIME curTime;
		TCHAR szTime[MAX_PATH] = {0};
		::GetLocalTime( &curTime );
		transformat( szTime, _T("\r\nTime Stamp:	%4d-%02d-%02d %02d:%02d:%02d %03d\r\n"), curTime.wYear, curTime.wMonth, curTime.wDay, curTime.wHour, curTime.wMinute, curTime.wSecond, curTime.wMilliseconds );	
		TestResultInfo( szTime );
	}

	return (TEST_ITEM_STATUS)itemQuote.funAddr->Invoke( itemQuote.item );
}
void CTestBase::TestResultInfo( const ColorText& text )
{
	m_ColorText += text;
}
void CTestBase::TestResultInfo( LPCTSTR strResult, unsigned char ucColorType/* = 0xff*/ )
{
	if( ucColorType == ITEM_STA_PASS )
		m_ColorText += ColorText( strResult, RGB( 0, 255, 0 ), TEXT_SIZE_LARGE, true );
	else if( ucColorType == ITEM_STA_FAIL )
		m_ColorText += ColorText( strResult, RGB( 255, 0, 0 ), TEXT_SIZE_LARGE, true );
	else
		m_ColorText += strResult;
}
TCHAR* CTestBase::TestResultInfoR( LPCTSTR strResult...)
{
	static TCHAR szBuffer[MAX_PATH] = {0};

	memset(szBuffer,0,MAX_PATH);

	va_list arg_ptr;
	va_start(arg_ptr, strResult);
	int temp_size =  _vsnprintf_s(szBuffer,MAX_PATH-1, strResult, arg_ptr);
	va_end(arg_ptr);

	TestResultInfo(szBuffer);

	return szBuffer;
}

TCHAR* CTestBase::StrFormat(LPCTSTR strResult...)
{
	static TCHAR szBuffer[MAX_PATH] = {0};

	memset(szBuffer,0,MAX_PATH);

	va_list arg_ptr;
	va_start(arg_ptr, strResult);
	int temp_size =  _vsnprintf_s(szBuffer,MAX_PATH-1, strResult, arg_ptr);
	va_end(arg_ptr);

	return szBuffer;
}

unsigned int CTestBase::INT_Test( NativeTestItem& itemQuote )
{
	unsigned int iReCode = ERROR_CODE_OK, failerCount = 0;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );

	TestResultInfo( _T("\r\n------------------------------INT Test------------------------------\r\n") );

	int index = 0;
	for( index = 0; index < 30; index++ )
	{
		iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_INT_TST );
		if( ERROR_CODE_OK == iReCode ) break;
		SysDelay( 10 );
	}

	if( ERROR_CODE_OK == iReCode )
	{
		itemNotify.UpdateItemResult( ITEM_STA_PASS );
		TestResultInfo( "\r\n\r\n//INT Test is Pass\r\n", ITEM_STA_PASS );
	}
	else
	{
		itemNotify.UpdateItemResult( ITEM_STA_FAIL );
		TestResultInfo( "\r\n\r\n//INT Test is Fail\r\n", ITEM_STA_FAIL );
	}

	return itemNotify;
}
unsigned int CTestBase::Reset_Test( NativeTestItem& itemQuote )
{
	unsigned int iReCode = ERROR_CODE_OK, failerCount = 0;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );

	TestResultInfo( _T("\r\n------------------------------RESET Test------------------------------\r\n") );

    iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand(CMD_CTP_RST);
    if (iReCode != ERROR_CODE_OK) return itemNotify.UpdateItemResult(ITEM_STA_EXCEPTION, GetErrorMessage(iReCode));
    SysDelay(50);

	for( int index = 0; index < 5; index++ )
	{
		iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_RST_TST );
		if( ERROR_CODE_OK == iReCode ) break;
		SysDelay( 100 );
	}

	if( ERROR_CODE_OK == iReCode )
	{
		itemNotify.UpdateItemResult( ITEM_STA_PASS );
		TestResultInfo( "\r\n\r\n//Reset Test is Pass\r\n", ITEM_STA_PASS );
	}
	else
	{
		itemNotify.UpdateItemResult( ITEM_STA_FAIL );
		TestResultInfo( "\r\n\r\n//Reset Test is Fail\r\n", ITEM_STA_FAIL );
	}

	//OSTrim();

	return itemNotify;
}
void CTestBase::SetGraphTestContext( HDC hdc, RECT& rc )
{
	if( (m_iRealGraphIndex < 0) || (m_iRealGraphIndex >= MAX_GRAPH_ITEM) )  return;

	//m_GraphTestTool.CreateMemDC( hdc, typeRect( 0, 0, width, height ) );
	CGraphItemTest* pGraphTest = m_vecGraphTest[m_iRealGraphIndex];
	if( NULL == pGraphTest )  return;

	pGraphTest->GraphRefresh( hdc, typeRect( rc ) );
}
unsigned int CTestBase::Graph_Test( NativeTestItem& itemQuote )
{
	unsigned int iReCode = ERROR_CODE_INVALID_PARAM, failerCount = 0;

	WorkForGraphMode( true );

	m_iRealGraphIndex = itemQuote.testCode - TEST_ITEM_GRAPH_TEST_START;
	CGraphItemTest* pGraphTest = m_vecGraphTest[m_iRealGraphIndex];
	if( NULL == pGraphTest )
	{
		GraphParam param( m_deviceNo, m_GraphTestTool );
		pGraphTest = (CGraphItemTest*)RunTimeClassFactoryInstEx(GRAPH_TYPE).CreateObject( (GRAPH_TYPE)(itemQuote.testCode), (unsigned long)&param );
		m_vecGraphTest[m_iRealGraphIndex] = pGraphTest;
	}

	//ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );

	//pGraphTest->DoInit( m_deviceNo );

	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );

	BOOL bResult = pGraphTest->LoopAndDone(  );

	itemNotify.UpdateItemResult( bResult ? ITEM_STA_PASS : ITEM_STA_FAIL );

	TCHAR chTemp[MAX_PATH] = {0};
	if( bResult )
	{
		transformat( chTemp, _T("\r\n\r\n%s Test is Pass\r\n"), itemQuote.testName );
		TestResultInfo( chTemp, ITEM_STA_PASS );
	}
	else
	{
		transformat( chTemp, _T("\r\n\r\n%s Test is Fail\r\n"), itemQuote.testName );
		TestResultInfo( chTemp, ITEM_STA_FAIL );
	}

	return itemNotify;
}
// UINT32 CTestBase::ForcePaintThreadEntry( LPVOID lp )
// {
// 	CTestBase* pThis = (CTestBase*)lp;
// 	pThis->ForcePaintFlow();
// 
// 	return 0;
// }
void CTestBase::ForcePaintFlow()
{
	SetTestFlowOnLine(  );
	SM_CommBase(m_deviceNo)->SetIoVoltage( G_XMLConfig->vddVotage, G_XMLConfig->ioVddVotage, G_XMLConfig->vihVotage );
	unsigned int iReCode = WorkForGraphMode( true );
	if( ERROR_CODE_OK != iReCode ) 
	{
		SetTestFlowOffLine(); 
		return;
	}

	CGraphItemTest* pGraphTest = NULL;
	m_iRealGraphIndex = TEST_ITEM_FREE_PAINT_TEST - TEST_ITEM_GRAPH_TEST_START;
	if( NULL == m_vecGraphTest[m_iRealGraphIndex] )
	{
		GraphParam param( m_deviceNo, m_GraphTestTool );
		pGraphTest = (CGraphItemTest*)RunTimeClassFactoryInstEx(GRAPH_TYPE).CreateObject( (GRAPH_TYPE)(TEST_ITEM_FREE_PAINT_TEST), (unsigned long)&param );
		m_vecGraphTest[m_iRealGraphIndex] = pGraphTest;
	}

	pGraphTest = m_vecGraphTest[m_iRealGraphIndex];
	if( NULL != pGraphTest ) 
	{
		pGraphTest->LoopAndDone( );
	}

	//if( 0 == pGraphTest->GetTimeLeft() )
	navCallBack.onOneTestOver( m_deviceNo, 0 );
	if(G_XMLConfig->heatbeatVotage > 0)
	{
		SM_CommBase(m_deviceNo)->SetIoVoltage( G_XMLConfig->heatbeatVotage, 0, 0 );
	}

	SetTestFlowOffLine( );
}
unsigned int CTestBase::ForcePaint( bool enterPaint )
{
	unsigned int iReCode = ERROR_CODE_WAIT_RESPONSE_TIMEOUT;
	CGraphItemTest* pGraphTest = NULL;

	if( enterPaint )
	{
		// 		if( IsTestRuning() ) 
		// 			return ERROR_CODE_ONE_PROCESS_RUNING;
		// 
		// 		unsigned int uThreadHandle = _beginthreadex( NULL, 0, ForcePaintThreadEntry, this, 0, NULL );
		// 		for( int index = 0; index < 200; index++ )
		// 		{
		// 			if( m_bInGraphing )
		// 			{
		// 				Sleep( 20 );
		//   				iReCode = ERROR_CODE_OK;
		// 				break;
		// 			}
		// 			Sleep( 10 );
		// 		}
		// 		::CloseHandle( (HANDLE)uThreadHandle );


		SetOperationForcePaint(this);

		if( IsTestStillOnLine(this) )
		{
			StopLoopRuning();
		}
		else 
		{
		}

		for( int index = 0; index < 200; index++ )
		{
			if( !DoOperationForcePaint(this) )
			{
				iReCode = ERROR_CODE_OK;
				break;
			}

			Sleep( 20 );
		}
	}
	else
	{
		StopLoopRuning();
		int freePaintIndex = TEST_ITEM_FREE_PAINT_TEST - TEST_ITEM_GRAPH_TEST_START;
		CGraphItemTest* pGraphTest = m_vecGraphTest[freePaintIndex];
		WorkForGraphMode( false );
		if( pGraphTest )  pGraphTest->Exit();
		Sleep( 100 );
		iReCode = ERROR_CODE_OK;
		//navCallBack.onOneTestOver( m_deviceNo, 0 );
	}

	return iReCode;
}

tstring CTestResultSaveXY::MakeRelativePath(unsigned int testRet, InternalItemInfo (&itemResult)[MAX_TEST_ITEMS], LPCTSTR szWorkStation, unsigned char simulate /*= 0*/)
{
	tstring szRelative = _T("");
	TCHAR chName[MAX_PATH] = {0};

	SYSTEMTIME st = {0};
	GetLocalTime( &st );
	memset( chName, 0, sizeof(chName) );
	transformat( chName, _T("/%d-%02d-%02d/"), st.wYear, st.wMonth, st.wDay );

	szRelative += chName;

	if( TEST_PASS == testRet ){
		szRelative += _T("Pass");
	}
	else if( TEST_NG == testRet ){
		szRelative += _T("Fail");
	}
	else if( TEST_TBD == testRet ){
		szRelative += _T("TBD");
	}


	return szRelative;

}

tstring CTestResultSaveXY::MakeFileNameToSave(const RecordData& rcDataMsg, unsigned char simulate /*= 0 */)
{
	TCHAR szName[MAX_PATH] = {0};

	SYSTEMTIME st = {0};
	GetLocalTime(&st);//获得当前本地时间
	transformat( szName, _T("%s_0x%llx_%d%02d%02d%02d%02d%02d_%s.csv"), rcDataMsg.snCode, rcDataMsg.ReleaseID, 
		st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, rcDataMsg.TestResult == TEST_PASS ? _T("Pass") : _T("Fail"));

	return szName;
}

//tstring CTestResultSaveVisionox::MakeRelativePath(unsigned int testRet, InternalItemInfo (&itemResult)[MAX_TEST_ITEMS], LPCTSTR szWorkStation, unsigned char simulate /*= 0*/)
//{
//	tstring szRelative = _T("");
//	TCHAR chName[MAX_PATH] = {0};
//
//	SYSTEMTIME st = {0};
//	GetLocalTime( &st );
//	memset( chName, 0, sizeof(chName) );
//	transformat( chName, _T("/%d-%02d-%02d/"), st.wYear, st.wMonth, st.wDay );
//
//	szRelative += chName;
//
//	if( TEST_PASS == testRet ){
//		szRelative += _T("Pass");
//	}
//	else if( TEST_NG == testRet ){
//		szRelative += _T("Fail");
//	}
//	else if( TEST_TBD == testRet ){
//		szRelative += _T("TBD");
//	}
//
//
//	return szRelative;
//}

tstring CTestResultSaveVisionox::MakeFileNameToSave(const RecordData& rcDataMsg, unsigned char simulate /*= 0 */)
{
	TCHAR szName[MAX_PATH] = {0};

	SYSTEMTIME st = {0};
	GetLocalTime(&st);//获得当前本地时间
	transformat( szName, _T("%s_%s_%d%02d%02d_%02d%02d%02d.txt"), rcDataMsg.snCode, rcDataMsg.TestResult == TEST_PASS ? _T("Pass") : _T("Fail"), 
		st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

	return szName;

}

tstring CTestResultSaveJW::MakeFileNameToSave(const RecordData& rcDataMsg, unsigned char simulate /*= 0 */)
{
	//transformat( szName, _T("0x%llx.txt"), rcDataMsg.ReleaseID
	TCHAR szName[MAX_PATH] = {0};

	SYSTEMTIME st = {0};
	GetLocalTime(&st);//获得当前本地时间
	transformat( szName, _T("0x%llx_%s_%d%02d%02d_%02d%02d%02d_%s.csv"),  rcDataMsg.ReleaseID,rcDataMsg.snCode, 
		st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, rcDataMsg.TestResult == TEST_PASS ? _T("OK") : _T("NG"));

	return szName;
}

tstring CTestResultSaveChuangWei::MakeFileNameToSave(const RecordData& rcDataMsg, unsigned char simulate /*= 0 */)
{
	//transformat( szName, _T("0x%llx.txt"), rcDataMsg.ReleaseID
	TCHAR szName[MAX_PATH] = {0};

	SYSTEMTIME st = {0};
	GetLocalTime(&st);//获得当前本地时间
	transformat( szName, _T("0x%llx_%s_%d%02d%02d_%02d%02d%02d_%s.txt"),  rcDataMsg.ReleaseID,rcDataMsg.snCode, 
		st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, rcDataMsg.TestResult == TEST_PASS ? _T("OK") : _T("NG"));

	return szName;
}
