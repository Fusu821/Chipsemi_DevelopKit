#include "CommAdb.h"
#include "framework.h"
#include "checksum.h"
#include "../Protocal/Protocal.h"

#include "onlinelog.h"

//#define FIXED_READ_SIZE(x)  ((x) + 0)
#define FIXED_WRITE_SIZE(x) ((x) + 8)

REGIST_RUNTIME_CLASS_PVOID( COMM_TYPE, (COMM_TYPE)LINK_TYPE_TCP, CCommAdb )


CCommAdb::CCommAdb(LPVOID param)
	:m_HalInterface( NULL )
	,m_bDelaySync( FALSE )
{
#ifdef _DEBUG
	m_iDeviceIndex = 0;
#endif

	//WinExec(_T("WifiDbg\\agent.bat"), SW_SHOWNORMAL);
// 	PROCESS_INFORMATION ProcessInfo; 
// 	STARTUPINFO StartupInfo; //This is an [in] parameter 
// 	ZeroMemory(&StartupInfo, sizeof(StartupInfo)); 
// 	StartupInfo.cb = sizeof StartupInfo ; //Only compulsory field 
// 	CreateProcess( _T("WifiDbg\\agent.bat"),"", NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &StartupInfo, &ProcessInfo );
// 
// 	WaitForSingleObject( ProcessInfo.hProcess, 30000 );
// 	SysDelay(500);

	typedef IHalServiceInterface* ( *funAllocInterface )(  );
	HMODULE hDllLib = ::LoadLibrary( _T("HalTcpClientSrv.dll") );
	funAllocInterface fun = (funAllocInterface)::GetProcAddress( hDllLib, "AllocateHalSrvInterface" );
	if( fun )  
	{
		m_HalInterface = (*fun)();

		LinkParam* lp = (LinkParam*)param;
		m_HalInterface->HalTryAttachLink( 0, lp->tcp.pszIpAddress, lp->tcp.port, lp->tcp.async );
	}
}
CCommAdb::~CCommAdb()
{
	//m_HalInterface->HalTryDetachLink( 0 );
	//SysDelay(20);
	RestoreHalSrvInterface( m_HalInterface );
}
unsigned int CCommAdb::GetCommType()
{
	return LINK_TYPE_TCP;
}
unsigned int CCommAdb::SyncWorkcInit( unsigned char bHold/* = 1*/ )
{
// 	ctp_cmd_std_t wr;
// 	ctp_rsp_std_t rd;
//
// 	ProtocalMTKApi protocalApi;
//  	protocalApi.PrepareIoDataToSend( wr, CMD_HOLD_MTK, bHold );
//  	return SendCommandAndCheck( &protocalApi, (unsigned char*)&wr, (unsigned char*)&rd );

	//return m_HalInterface->HalTryAttachLink( 0, param.tcp.pszIpAddress, param.tcp.port, param.tcp.async );

	return ERROR_CODE_OK;
}
BOOL CCommAdb::Connected()
{
	return m_HalInterface->IsConnected(  );
}
unsigned int CCommAdb::HalTrySetDeviceManuly( Device hDevice )
{
	int deviceIndex = hDevice.iDevIndex;

#ifdef _DEBUG
	m_iDeviceIndex = (unsigned char)deviceIndex;
#endif

// 	TCHAR chName[50] = {0};
// 	CloseHandle( m_hTouchEvent );
// 	transformat( chName, 50, _T("Touch_%d"), deviceIndex );
// 	m_hTouchEvent = ::CreateEvent( NULL, TRUE, FALSE, chName );
// 
// 	CloseHandle( m_hAutoReport );
// 	transformat( chName, 50, _T("AutoReport_%d"), deviceIndex );
// 	m_hAutoReport = ::CreateEvent( NULL, TRUE, FALSE, chName );
// 
// 	CloseHandle( m_hLevelEvent );
// 	transformat( chName, 50, _T("LevelPulse_%d"), deviceIndex );
// 	m_hLevelEvent = ::CreateEvent( NULL, TRUE, FALSE, chName );

	return m_HalInterface->HalTrySetDeviceManuly( hDevice.handle, hDevice.iDevIndex );
}
unsigned int CCommAdb::SendCommand( unsigned char* pWrite, unsigned char* pRead )
{
	pRead;
	unsigned int iRetCode = ERROR_CODE_COMM_ERROR;

	{
		//clear response buffer
		//unsigned char clearBuffer[] = {0x02, MTK_RSP_BUF >> 8, MTK_RSP_BUF & 0xff, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		//iRetCode = m_HalInterface->Write( clearBuffer, sizeof(clearBuffer) );
		unsigned char clearBuffer[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		iRetCode = WriteToUsbMemory( MTK_RSP_BUF, clearBuffer, sizeof(clearBuffer) );
	}

	if( ERROR_CODE_OK == iRetCode )
	{
		unsigned char* pDes = (unsigned char*)pWrite;
// 		const int writeLen = 8 + sizeof(ctp_cmd_std_t);
// 		unsigned char writeBuffer[writeLen] = { 0x02, MTK_CMD_BUF >> 8, MTK_CMD_BUF & 0xff, 0x10, 0x10, 0x10, 0x10, 0x10 };
// 		for( int index = 0; index < sizeof(ctp_cmd_std_t); index++ )
// 		{
// 			writeBuffer[8 + index] = pDes[index];
// 		}
// 
// 		iRetCode = m_HalInterface->Write( writeBuffer, writeLen );

		iRetCode = WriteToUsbMemory( MTK_CMD_BUF, pDes, sizeof(ctp_cmd_std_t) );
	}
	
	return iRetCode;
}
unsigned int CCommAdb::SendCommandAndCheck( ProtocalApi* protocalApi, unsigned char* pWrite, unsigned char* pRead, unsigned short delay/* = 30*/ )
{
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;

	iReCode = SendCommand( pWrite, pRead );

	if( iReCode == ERROR_CODE_OK )
	{
		//SysDelay( 30 );  //wait for Adb board action done
		SysDelay( delay );

		memset( pRead, 0, sizeof(ctp_rsp_std_t) );

		unsigned char writeBuffer[] = { 0x02, MTK_RSP_BUF >> 8, MTK_RSP_BUF & 0xff, CMD_NA };

		LoopTicker tick( 100 );
		while ( tick.TickOnce() )
		{
			//iReCode = m_HalInterface->IoCtrl( writeBuffer, sizeof(writeBuffer), (unsigned char*)pRead, sizeof(ctp_rsp_std_t) );

			iReCode = ReadFromUsbMemory( MTK_RSP_BUF, pRead, protocalApi->ResponseLength() );

			if( protocalApi->CheckResponseOk( iReCode, delay, pWrite, pRead ) )
			{
				break;
			}

			SysDelay( delay );
		}

		tick.CheckTickAndMark( iReCode );
		CHECK_RETURN_IF_FAIL( iReCode );
	}

	return iReCode;
}
BOOL CCommAdb::CheckIfSpecial( unsigned char rw, unsigned short addr, unsigned char* buffer, unsigned short len )
{
	if( MTK_DATA_RDY == addr ) 
	{
		m_bDelaySync = rw ? 0x01 : 0;
		if(1 == rw) buffer[0] = 1;

		return TRUE;
	}

	return FALSE;
}
unsigned int CCommAdb::ReadFromUsbMemory( unsigned short addr, unsigned char* pRead, unsigned short len )
{
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
	unsigned short opType = addr;

	if( CheckIfSpecial( 1, addr, pRead, len ) ) return ERROR_CODE_OK;

	unsigned short lpAddr = addr;
	unsigned char* buffer = pRead;
	int byteLeft = len, maxLoop = len, onceRead = REAL_TCP_RD_LEN;
	while( byteLeft > 0 && (maxLoop--) > 0 )
	{
		onceRead = min( REAL_TCP_RD_LEN, byteLeft );

		unsigned char writeBuffer[] = { 0x08, lpAddr >> 8, lpAddr & 0xff, opType >> 8, opType & 0xff, onceRead >> 8, onceRead & 0xff, m_bDelaySync };

		unsigned int readed = 0;
		iReCode = m_HalInterface->IoCtrl( writeBuffer, sizeof(writeBuffer), buffer, onceRead, &readed );

		byteLeft -= readed;
		buffer   += readed;
		lpAddr   += readed;
	}

	return iReCode;
}
unsigned int CCommAdb::WriteToUsbMemory( unsigned short addr, const unsigned char* pWrite, unsigned short len )
{
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
	unsigned short opType = addr;

	if( CheckIfSpecial( 0, addr, (unsigned char*)pWrite, len ) ) return ERROR_CODE_OK;

	unsigned char writeBuffer[REAL_HAL_WR_LEN + 10] = {0};

	int byteLeft = len, onceWrite = REAL_HAL_WR_LEN;

	while( byteLeft > 0 )
	{
		onceWrite = min( REAL_HAL_WR_LEN, byteLeft );

		memset( writeBuffer, 0, sizeof(writeBuffer) );
		writeBuffer[0] = 0x02;
		writeBuffer[1] = (addr >> 8) & 0xff;
		writeBuffer[2] = (addr) & 0xff;
		writeBuffer[3] = (opType >> 8) & 0xff;
		writeBuffer[4] = (opType) & 0xff;
		writeBuffer[5] = (onceWrite >> 8) & 0xff;
		writeBuffer[6] = onceWrite & 0xff;
		memcpy_s( writeBuffer + 8, onceWrite, pWrite, onceWrite );

		iReCode = m_HalInterface->Write( writeBuffer, FIXED_WRITE_SIZE(onceWrite) );

		byteLeft -= onceWrite;
		pWrite += onceWrite;
		addr += onceWrite;

		if( iReCode != ERROR_CODE_OK ) break;
	}

	return iReCode;
}
unsigned int CCommAdb::SetIoVoltage( unsigned short vdd, unsigned short iovdd, unsigned short vih )
{
// 	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
// 
// 	ctp_cmd_std_t wr;
// 	ctp_rsp_std_t rd;
// 	ProtocalMTKApi protocalApi;
// 
// 	protocalApi.PrepareIoDataToSend( wr, CMD_MTK_SET_VOLTAGE, vdd, iovdd );
// 	iReCode = SendCommandAndCheck( &protocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
// 	CHECK_RETURN_IF_FAIL( iReCode );
// 
// 	return iReCode;

	return ERROR_CODE_OK;
}
unsigned int CCommAdb::PrepareMtkBoardUpgrade(  )
{
	return ERROR_CODE_OK;
}
unsigned int CCommAdb::UpgradeMtkBoard( unsigned char devNo, unsigned char* pAdbBin, unsigned int len, LPUpdateProcessPosCallBack lpProcess )
{
	return ERROR_CODE_OK;
}