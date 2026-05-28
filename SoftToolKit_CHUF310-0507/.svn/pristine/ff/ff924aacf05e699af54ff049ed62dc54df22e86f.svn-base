#pragma once

#include "SEMITouch.h"

#define WM_START_TEST        WM_USER + 2001
#define WM_RECV_LINK_DATA    WM_USER + 2002
#define WM_QUEST_LINK_STATE  WM_USER + 2003
#define WM_RECV_USER_DATA    WM_USER + 2004
#define WM_UPDATA_SPC_DATA   WM_USER + 2005

#define		RESULT_NULL			0
#define		RESULT_PASS			1
#define		RESULT_NG		        2
#define		RESULT_TESTING		        3
#define		RESULT_TBD			4
#define		RESULT_REPLACE		        5
#define		RESULT_CONNECTING	        6

//****************Command Code**********************//
#define AUTO_LINE_START_TEST        0X00F0
#define AUTO_LINE_3GAMMA_RECHECK    0X00F8
#define AUTO_LINE_GET_3GAMMA        0X00F9
#define AUTO_LINE_TEST_FINISH       0x00FA

#define AUTO_LINE_TEST_START        0X0001
#define AUTO_LINE_TEST_END          0X0002
#define AUTO_LINE_TRANSFER_SN       0X0005
#define AUTO_LINE_LOG_PATH          0x0006
#define AUTO_LINE_LOG_NAME          0x000A
#define AUTO_LINE_LPWG_TEST_START   0x000B
#define AUTO_LINE_LPWG_TEST_END     0x000C
//**************************************************//


//****************TestResult附带的数据******************//
#define AUTO_EXDATA_SN              0x0005
#define AUTO_EXDATA_INI_NAME        0x0007
#define AUTO_EXDATA_TEST_TIME_SPEN  0x0008//测试的时长
#define AUTO_EXDATA_EDO_CODE        0x0009//和辉定的不良代码MT11,MT20,MT21

//*************************************************//

enum{ MUTI_START_ONE, MUTI_START_TWO, MUTI_START_THREE, MUTI_START_FOUR, MUTI_START_ALL = 0xff };

enum { OP_LIKE_DEFAULT, OP_LIKE_ICID, OP_LIKE_YY, OP_LIKE_EDO, OP_LIKE_HX, OP_LIKE_CLOUD, OP_LIKE_VSN, OP_LIKE_EMS, OP_LIKE_EMS_OFILM, OP_LIKE_EMS_PBH, OP_LIKE_XY, OP_LIKE_VISIONOX, OP_LIKE_JW,
    OP_LIKE_CHUANGWEI, OP_LIKE_HES, OP_LIKE_LS,};

enum { LINK_NONE, LINK_USE_COM = 0x1, LINK_USE_TCP = 0x2, LINK_USE_PIPE = 0x3, };

// union LinkParam 
// {
// 	struct  
// 	{
// 		LPCTSTR pszIpAddress;
// 		unsigned short port;
// 		unsigned char async;
// 	}tcp;
// 	struct 
// 	{
// 		unsigned short port;
// 		unsigned int   boartRate;
// 	}com;
// 	struct 
// 	{
//         LPCTSTR ptrPipeName;
// 	}pipe;
// };

struct Pile_Result
{
	unsigned char testCode;
	unsigned char testType;
	unsigned char testResult;
	char testName[50];
};
struct Trans_CustomData
{
	unsigned char packgeNum;
	struct cuData
	{
		int dataLen;
		int dataType;
		unsigned char *Buffer;
	}dataPackge[5];
};
struct TransInfo_Collection
{
	unsigned char uDevice;
	unsigned char bTestResult;
	unsigned char uFwVersion;
	char snNum[100];
	char stationID[30];
	char testerID[30];
	char macAddr[30];
	char icID[30];
	Pile_Result result[50];     //最多传送50个测试结果
	char lockDown[10];
	char GroupType[3];
	char csvFilePath[MAX_PATH];
	Trans_CustomData specData;
};

// class ONLINE_SERVICE_API IOperation
// {
// public:
// 	IOperation(){}
// 	virtual ~IOperation() {}
// public:
// 	virtual void Release()                                                      = 0;
// 	virtual void SetOperateComplexWnd( HWND hwnd )                              = 0;
// 	virtual int  OnLinePostTestResult( const TransInfo_Collection& trans )      = 0;
// 	virtual int  OnLineDoHandShake()                                            = 0;
// 	virtual void OnLinkDataArrive( unsigned int connID, int len, TCHAR* szIni, TCHAR* szBin )               = 0;
// };

class ONLINE_SERVICE_API IFtpClientInterface
{
public:
	virtual unsigned char UpFile(LPCTSTR localDir, LPCTSTR server, LPCTSTR user, LPCTSTR password, unsigned short nport ) {return 0;};

	//virtual unsigned char DownFile( LPCTSTR remoteFile, LPCTSTR localFile ) {return 0;};

	//virtual unsigned char UpFile( unsigned short finalResult, LPCTSTR fromPath, LPCTSTR toPath ) {return 0;};
};

class NativeTestInterface;
class ONLINE_SERVICE_API IAutomaticInterface
{
public:
	virtual unsigned char OnLine( unsigned char option, LPCTSTR szLine ){return 0;}

	virtual unsigned char AccountCheck( LPCTSTR szLine, LPCTSTR szAccount, LPCTSTR szPassword ){return 0;}

	virtual unsigned char LogOnMessage( LPCTSTR szLine, LPCTSTR sn ){return 0;}

	virtual unsigned char LogOffMessage( LPCTSTR szLine, LPCTSTR sn, int device, unsigned short result ){return 0;}

	virtual unsigned char ActionToOnLineMessage(NativeTestInterface* appInterface, int msg, unsigned int wparam, unsigned int lparam) {return 0;}

	virtual LPCTSTR GetOnLineMessageInfo( ){ return NULL; }

	virtual unsigned char SendResultUpToServer( const TransInfo_Collection& trans ) = 0;

	virtual bool NotifyTestStatus( unsigned char ucDevice, unsigned int testCode, unsigned short status, unsigned char result = RESULT_NULL ) = 0;

	virtual unsigned char OnLineDoHandShake() = 0;

	virtual void SetOperateComplexWnd( HWND hwnd ) = 0;

	virtual bool Initialize( unsigned int type, LinkParam& param ) = 0;

	virtual void GameOver( ) = 0;

	//virtual BOOL HandleRecvAndNotify( unsigned char* buffer, unsigned int len ) = 0;

	virtual void OnLinkDataArrived( unsigned char* recvBuffer, int len, bool bAnyTesting, char* szIni, char* szBin )  = 0;

	virtual unsigned char OnGetUserData( unsigned char ucDevice, unsigned short dataType, unsigned char* buffer, int len, int* readed ) = 0;

	virtual bool SendUserData( unsigned char ucDevice, unsigned short dataType, unsigned char* buffer, int len ) = 0;

	virtual bool SendAckPacket( unsigned char ucDevice, unsigned short packetType ) = 0;

	virtual bool ReceiveAckPacket( unsigned char ucDevice, unsigned short packetType ) = 0;

	virtual unsigned int ResetCommandEvent( unsigned char ucDevice, unsigned int iCommandEvent ) = 0;

	virtual unsigned int WaitCommandEvent( unsigned char ucDevice, unsigned int iCommandEvent ,unsigned int iwaitTime = 500) = 0;

};

ONLINE_SERVICE_CSTYLE_API IAutomaticInterface* GetAutomaticInterface( unsigned int type, HWND wind, LinkParam param );

ONLINE_SERVICE_CSTYLE_API IFtpClientInterface* GetFtpInterface( );