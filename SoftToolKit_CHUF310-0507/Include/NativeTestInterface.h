#ifndef __SM_TEST_INTERFACE__
#define __SM_TEST_INTERFACE__
/**************************************************************************************/

#include "Macro.h"
//#include <tchar.h>
#include <string>
#include <list>
using namespace std;

#define MAX_TEST_ITEMS                   (28 + 10)
#define TEST_ITEM_GRAPH_TEST_START       (22 + 10)
#define SIMULATE_TEST_DATA_CNT           10

enum TEST_ITEM_STATUS { ITEM_STA_NONE, ITEM_STA_WAIT, ITEM_STA_START, ITEM_STA_TBD, ITEM_STA_PASS, ITEM_STA_FAIL, ITEM_STA_EXCEPTION,ITEM_STA_PRESS };
enum EN_TEST_RESULT{ TEST_NONE, TEST_PASS, TEST_NG, TEST_TBD, TEST_GOING };
enum EN_START_WAY { START_BY_AUTO = 1, START_BY_BUTTON, START_BY_SN/*, START_BY_LOW_SINGNAL,*/ };
enum EN_RESULT_FORMAT { RESULT_FORMAT_DEF, };
enum EN_COMMAND_LINE_MODE { COMMAND_LINE_NONE = 0, COMMAND_LINE_DEBUG = 0x01, COMMAND_LINE_FAE = 0x02, COMMAND_LINE_STOP = 0x04, COMMAND_LINE_SHUT_DOWN = 0x08, };

class ColorText
{
public:
	ColorText( )
		:dwColor( 0 )
		,iHeight( TEXT_SIZE_SMALL )
		,bBold( false )
		,next( NULL )
	{

	}
	ColorText( const tstring& strAttr, int height = TEXT_SIZE_SMALL, bool bold = false )
		:dwColor( 0 )
		,strText( strAttr )
		,iHeight( height )
		,bBold( bold )
		,next( NULL )
	{

	}
	ColorText( const tstring& strAttr, unsigned int color, int height = TEXT_SIZE_SMALL, bool bold = false )
		:dwColor( color )
		,strText( strAttr )
		,iHeight( height )
		,bBold( bold )
		,next( NULL )
	{
	}
	virtual ~ColorText()
	{
		ColorText* pNext = this->next;
		while ( pNext )
		{
			ColorText* temp = pNext;
			pNext = pNext->next;
			temp->next = NULL;
			delete temp;
		}
	}
	ColorText& operator=( const tstring& strAttr )
	{
		ColorText* pNext = this->next;
		this->next = NULL;
		while ( pNext )
		{
			ColorText* temp = pNext;
			pNext = pNext->next;
			temp->next = NULL;
			delete temp;
		}
		strText = strAttr;
		return *this;
	}
	ColorText& operator+=( const tstring& strAttr )
	{
		ColorText* pNext = this->next;
		while ( pNext && pNext->next )
		{
			pNext = pNext->next;
		}
		if( NULL == pNext ){
			this->next = new ColorText( strAttr );
		}
		else{
			pNext->next = new ColorText( strAttr );
		}
		return *this;
	}
	ColorText& operator=( const ColorText& text )
	{
		ColorText* pNext = this->next;
		this->next = NULL;
		while ( pNext )
		{
			ColorText* temp = pNext;
			pNext = pNext->next;
			temp->next = NULL;
			delete temp;
		}

		ColorText* pTail = text.next;
		this->strText = text.strText;
		this->dwColor = text.dwColor;
		while( pTail )
		{
			ColorText* pNext = this->next;
			while ( pNext && pNext->next )
			{
				pNext = pNext->next;
			}
			if( NULL == pNext ){
				this->next = new ColorText( pTail->strText, pTail->dwColor, pTail->iHeight, pTail->bBold );
			}
			else{
				pNext->next = new ColorText( pTail->strText, pTail->dwColor, pTail->iHeight, pTail->bBold );
			}

			pTail = pTail->next;
		}

		return *this;
	}
	ColorText& operator+=( const ColorText& text )
	{
		const ColorText* pTail = &text;
		while( pTail )
		{
			ColorText* pNext = this->next;
			while ( pNext && pNext->next )
			{
				pNext = pNext->next;
			}
			if( NULL == pNext ){
				this->next = new ColorText( pTail->strText, pTail->dwColor, pTail->iHeight, pTail->bBold );
			}
			else{
				pNext->next = new ColorText( pTail->strText, pTail->dwColor, pTail->iHeight, pTail->bBold );
			}

			pTail = pTail->next;
		}

		return *this;
	}
	operator tstring()
	{
		tstring strTextAll;
		ColorText* pNext = this;
		while( pNext )
		{
			strTextAll += pNext->strText;
			pNext = pNext->next;
		}
		return strTextAll;
	}
public:
	unsigned int dwColor;
	//tstring strText;
	string strText;
	ColorText* next;
	int  iHeight;
	bool bBold;
};

struct SimulateData
{
	int itemID;
	unsigned char rows;
	unsigned char cols;
	int itemData[50][50];
	unsigned short itemArray[2500];
};

// enum TEST_TYPE {};
// enum CONFIG_TYPE {};

#pragma pack(push)
#pragma pack(1)
struct NativeTestItem 
{
public:
	unsigned char ucDevice;
	int           testCode;
	int           testResult;
 	TCHAR testName[128];
 	TCHAR testMark[128];
	NativeTestItem()
	{
		ucDevice = 0;
		testCode = -1;
		memset(testName, 0, sizeof(testName));
		memset(testMark, 0, sizeof(testMark));
	}
};

struct UpLoadInfo 
{
public:
	int           codenum;
	TCHAR         str[51200];
	UpLoadInfo()
	{
		codenum = 0;
		memset(str, 0, sizeof(str));
	}
};
#pragma pack(pop)

typedef unsigned int (__stdcall *OnOneTestStartCallBack)(int deviceID);
typedef void (__stdcall *OnListItemChangeCallBack)(NativeTestItem* item);
typedef void (__stdcall *OnProcessBarChangingCallBack)(int deviceID, int pos, int max);
//typedef void (__stdcall *OnInitProcessBarCallBack)(int nax);
typedef unsigned int (__stdcall *OnOneTestOverCallBack)(int deviceID, unsigned int finalResult);
typedef void (__stdcall *OnTouchReportCallBack)(int deviceID);
typedef UpLoadInfo* (__stdcall *OnInformationUploadCallBack)(UpLoadInfo* info);

class NativeCallBack
{
public:
	OnOneTestStartCallBack  onOneTestStart;
	OnListItemChangeCallBack onListItemChange;
	OnProcessBarChangingCallBack onProcssBarChanging;
	//OnInitProcessBarCallBack onInitProcessBar;
	OnOneTestOverCallBack onOneTestOver;
	OnTouchReportCallBack onTouchReport;
	OnInformationUploadCallBack onInforUpload;

};

class SM_TEST_API NativeTestInterface
{
public:
	virtual unsigned int ReloadXmlConfig( BOOL onlyLoadXml = FALSE ) = 0;
	virtual unsigned int StartTest( int iDevice, LPCTSTR szCode = NULL ) = 0;
    virtual unsigned int SendTestRz( int iDevice, LPCTSTR sdCode = NULL ) = 0;
	virtual unsigned int SimulateTest( int iDevice, SimulateData (&arraySimulate)[SIMULATE_TEST_DATA_CNT] ) = 0;
	virtual ColorText& GetTestMessage( int device ) = 0;
	virtual NativeTestItem& GetNativeTestItemByIndex( int device, int index ) = 0;
	virtual void SetContextForGraphTest( int iDevice, HDC dc, RECT& rc ) = 0;
	virtual void RegistComplexCallBack( const NativeCallBack& callBack ) = 0;
	virtual void GameOver( unsigned char mustStopNow ) = 0;
	virtual unsigned int ForcePaint( int iDevice, bool enterPaint ) = 0;
	virtual void SetCommandLineParam( unsigned int commandLineMode ) = 0; 
	virtual unsigned int GetViewInfo( TCHAR* szWorkStation, TCHAR* szProjInfo, TCHAR* softWare,  TCHAR* snFilter,unsigned char& startWay, unsigned char& snLen, unsigned char& format, unsigned short& test_mode , unsigned short& agent,unsigned char& clickstart,unsigned char& displaytest) = 0;
	virtual unsigned int ParseTestSample( unsigned char* content, unsigned int len, TCHAR* szName, unsigned short (&lpMatrix)[MAX_SCAP_ROW][MAX_SCAP_COL] ) = 0;
	virtual LPCTSTR GetStatisticText() = 0;
	virtual unsigned short GetICTypeFromConfig() = 0;
	virtual BOOL CheckReadyForTest( int device ) = 0;

	virtual unsigned int SetCommContext( int index ) = 0;
	virtual unsigned int OnLine( unsigned char option, HWND hwnd ) = 0;
	virtual unsigned int Sign( unsigned char option, LPCTSTR szLine, LPCTSTR szAccount, LPCTSTR szPassword ) = 0;
	virtual unsigned int UserOperationBeforeTest( int device )= 0;
	virtual unsigned int UserOperationAfterTest( int device, int result ) = 0;
	virtual unsigned int ActionToOnLineMessage(int msg, unsigned int wparam, unsigned int lparam) = 0;
	virtual LPCTSTR GetOnLineMessageInfo( ) = 0;
public:
	virtual inline const NativeCallBack& GetCallBack() const = 0;
	virtual inline const bool DebugMode() const = 0;
	virtual inline const bool FAEMode() const = 0;
	virtual inline const bool ErrStop() const = 0;
	
};

SM_TEST_CSTYLE_API NativeTestInterface* GetTestWapperInterface();
SM_TEST_CSTYLE_API void ReleaseTestWrapperInterface(NativeTestInterface* addr);

SM_TEST_CSTYLE_API void ScreenXYChange( long x, long y, long& outX, long& outY, const RECT& tp, const RECT& pc );
// SM_TEST_CSTYLE_API void RegistComplexCallBack( OnListItemChangeCallBack onListChage, 
//                             //OnInitProcessBarCallBack onProcessInit,
//                             OnProcessBarChangingCallBack onProcessChange,
//                             OnOneTestOverCallBack onTestOver );

/**************************************************************************************/
#endif