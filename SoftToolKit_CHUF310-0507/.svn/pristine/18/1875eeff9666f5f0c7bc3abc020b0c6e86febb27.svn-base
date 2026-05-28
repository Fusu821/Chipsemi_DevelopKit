#include "CommHID.h"
#include "framework.h"
#include "checksum.h"
#include "../Protocal/Protocal.h"
#include "onlinelog.h"

//#define FIXED_READ_SIZE(x)  ((x) + 0)
#define MAX_HID_PACKET_LEN  64
#define REAL_HID_WR_LEN     (MAX_HID_PACKET_LEN - 5)
#define REAL_HID_RD_LEN     (MAX_HID_PACKET_LEN - 1)
#define HID_ID              0x0c

REGIST_RUNTIME_CLASS_PVOID( COMM_TYPE, (COMM_TYPE)LINK_TYPE_HID, CCommHID )
typedef CCommHID CCommHID_IIC;
REGIST_RUNTIME_CLASS_PVOID( COMM_TYPE, (COMM_TYPE)LINK_TYPE_HID_IIC, CCommHID_IIC )

CCommHID::CCommHID(LPVOID param)
	//:m_HalInterface( AllocateHalSrvInterface() )
{
#ifdef _DEBUG
	m_iDeviceIndex = 0;
#endif
	m_Link_Type = 0;
	LinkParam* t_param= (LinkParam*)param;
	typedef IHalServiceInterface* ( *funAllocInterface )(  );
	HMODULE hDllLib = NULL;
	funAllocInterface fun = NULL; 
	m_Link_Type = t_param->LinkType;
	if(m_Link_Type == LINK_TYPE_HID)
	{
		 hDllLib = ::LoadLibrary( _T("HalHIDLayerSrv.dll") );
		 fun = (funAllocInterface)::GetProcAddress( hDllLib, "AllocateHalSrvInterface" );
	}
	else if(m_Link_Type == LINK_TYPE_HID_IIC)
	{
		hDllLib = ::LoadLibrary( _T("HalHIDIICLayerSrv.dll") );
		fun = (funAllocInterface)::GetProcAddress( hDllLib, "AllocateHalSrvInterface" );
	}	
	if( fun )  
	{
		m_HalInterface = (*fun)();
	}
}
CCommHID::~CCommHID()
{
	RestoreHalSrvInterface( m_HalInterface );
}
unsigned int CCommHID::GetCommType()
{
	return m_Link_Type;
}
unsigned int CCommHID::SyncWorkcInit( unsigned char bHold/* = 1*/ )
{
	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	ProtocalMTKApi protocalApi;
 	protocalApi.PrepareIoDataToSend( wr, CMD_HOLD_MTK, bHold );
 	return SendCommandAndCheck( &protocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
}
BOOL CCommHID::Connected()
{
	return m_HalInterface->IsConnected(  );
}
unsigned int CCommHID::HalTrySetDeviceManuly( Device hDevice )
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
unsigned int CCommHID::SendCommand( unsigned char* pWrite, unsigned char* pRead )
{
	pRead;
	unsigned int iRetCode = ERROR_CODE_COMM_ERROR;

	{
		//clear response buffer
		unsigned char clearBuffer[MAX_HID_PACKET_LEN] = {HID_ID, MTK_RSP_BUF >> 8, MTK_RSP_BUF & 0xff, 0x10, 0x00, 0x00};
		iRetCode = m_HalInterface->Write( clearBuffer, MAX_HID_PACKET_LEN );

	}

	if( ERROR_CODE_OK == iRetCode )
	{
		unsigned char* pDes = (unsigned char*)pWrite;
		const int writeLen = 5 + sizeof(ctp_cmd_std_t);
		unsigned char writeBuffer[writeLen] = { HID_ID, MTK_CMD_BUF >> 8, MTK_CMD_BUF & 0xff, 0x10, 0x00};
		for( int index = 0; index < sizeof(ctp_cmd_std_t); index++ )
		{
			writeBuffer[5 + index] = pDes[index];
		}

		iRetCode = m_HalInterface->Write( writeBuffer, MAX_HID_PACKET_LEN );
	}
	
	return iRetCode;
}
unsigned int CCommHID::SendCommandAndCheck( ProtocalApi* protocalApi, unsigned char* pWrite, unsigned char* pRead, unsigned short delay/* = 30*/ )
{
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;

	iReCode = SendCommand( pWrite, pRead );

	if( iReCode == ERROR_CODE_OK )
	{
		//SysDelay( 30 );  //wait for mtk board action done
		SysDelay( delay );

		memset( pRead, 0, sizeof(ctp_rsp_std_t) );

		//unsigned char writeBuffer[MAX_HID_PACKET_LEN] = { 0x02, MTK_RSP_BUF >> 8, MTK_RSP_BUF & 0xff, CMD_NA };

		LoopTicker tick( 100 );
		while ( tick.TickOnce() )
		{
			//iReCode = m_HalInterface->IoCtrl( writeBuffer, sizeof(writeBuffer), (unsigned char*)pRead, sizeof(ctp_rsp_std_t) );

			iReCode = ReadFromUsbMemory( MTK_RSP_BUF, pRead, protocalApi->ResponseLength() );
			if( ERROR_CODE_OK != iReCode ) break;

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
unsigned int CCommHID::ReadFromUsbMemory( unsigned short addr, unsigned char* pRead, unsigned short len )
{
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;

	unsigned short lpAddr = addr;
	unsigned char* buffer = pRead;
	int byteLeft = len, onceRead = MAX_HID_PACKET_LEN;
	while( byteLeft > 0 )
	{
		onceRead = min( REAL_HID_RD_LEN, byteLeft );

		unsigned char writeBuffer[MAX_HID_PACKET_LEN] = { HID_ID, lpAddr >> 8, lpAddr & 0xff, onceRead, 1 };
		unsigned char readBuffer[MAX_HID_PACKET_LEN] = {HID_ID};

		unsigned int readed = 0;
		//iReCode = m_HalInterface->IoCtrl( writeBuffer, sizeof(writeBuffer), buffer, onceRead, &readed );
		iReCode = m_HalInterface->Write( writeBuffer, MAX_HID_PACKET_LEN );
		if( iReCode != ERROR_CODE_OK ) break;

		iReCode = m_HalInterface->Read( readBuffer, MAX_HID_PACKET_LEN );
		memcpy_s(buffer, MAX_HID_PACKET_LEN, readBuffer + 1, onceRead);

		byteLeft -= onceRead;
		buffer   += onceRead;
		lpAddr   += onceRead;
	}

	return iReCode;
}
unsigned int CCommHID::WriteToUsbMemory( unsigned short addr, const unsigned char* pWrite, unsigned short len )
{
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;

	unsigned char writeBuffer[MAX_HID_PACKET_LEN] = {0};

	int byteLeft = len, onceWrite = REAL_HAL_WR_LEN;

	while( byteLeft > 0 )
	{
		onceWrite = min( REAL_HID_WR_LEN, byteLeft );

		memset( writeBuffer, 0, sizeof(writeBuffer) );
		writeBuffer[0] = HID_ID;
		writeBuffer[1] = (addr >> 8) & 0xff;
		writeBuffer[2] = (addr) & 0xff;
		writeBuffer[3] = (unsigned char)onceWrite;
		writeBuffer[4] = 0x00;
		memcpy_s( writeBuffer + 5, onceWrite, pWrite, onceWrite );

		iReCode = m_HalInterface->Write( writeBuffer, MAX_HID_PACKET_LEN );
		if( iReCode != ERROR_CODE_OK ) break;

		byteLeft -= onceWrite;
		pWrite += onceWrite;
		addr += onceWrite;
	}

	return iReCode;
}
unsigned int CCommHID::SetIoVoltage( unsigned short vdd, unsigned short iovdd, unsigned short vih )
{
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;
	ProtocalMTKApi protocalApi;

	protocalApi.PrepareIoDataToSend( wr, CMD_MTK_SET_VOLTAGE, vdd, iovdd, vih);
	iReCode = SendCommandAndCheck( &protocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 5 );
	CHECK_RETURN_IF_FAIL( iReCode );

	return iReCode;
}
unsigned int CCommHID::MtkBoardReBoot(unsigned int wantGo)
{
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	ProtocalMcapApi protocalApi;

	protocalApi.PrepareIoDataToSend( wr, CMD_MTK_UPGRADE_ENTER, wantGo & 0xffff);
	SendCommand( (unsigned char*)&wr, (unsigned char*)&rd );
	
	Sleep(1500);

	return iReCode;
}
unsigned int CCommHID::PrepareMtkBoardUpgrade(  )
{
	unsigned int iReCode = ERROR_CODE_COMM_ERROR, flags = 0;
	unsigned char writeBuffer[REAL_HAL_WR_LEN + 10] = {0};

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;
	

	TCHAR chName[50] = {0};
	transformat( chName, _T("%s-%d"), _T("IoDevice"), m_HalInterface->GetServiceFackID() );
	HANDLE ioEvent = ::OpenEvent( EVENT_ALL_ACCESS, FALSE, chName );
	ResetEvent( ioEvent );

	iReCode = ReadFromUsbMemory( MTK_VER_ADDR, (unsigned char*)&flags, 4 );
	CHECK_RETURN_IF_FAIL( iReCode );

	memset( writeBuffer, 0, sizeof(writeBuffer) );
	iReCode = WriteToUsbMemory( MTK_TXRX_BUF_MTK, writeBuffer, 128 );
	CHECK_RETURN_IF_FAIL( iReCode );

	if(0x80 == (flags >> 24))
	{
		int iOffset = -4096;
		ProtocalMcapApi protocalApi;
		protocalApi.PrepareIoDataToSend( wr, CMD_MTK_UPGRADE_WRITE, iOffset >> 16, iOffset & 0xffff, 128, caculate_check_sum_u816(writeBuffer, 128) );
		iReCode = SendCommandAndCheck( &protocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
		CHECK_RETURN_IF_FAIL( iReCode );

		protocalApi.PrepareIoDataToSend( wr, CMD_MTK_UPGRADE_ENTER );
		SendCommand( (unsigned char*)&wr, (unsigned char*)&rd );
		DWORD dwResult = ::WaitForSingleObject( ioEvent, 10000 );
		if( dwResult != WAIT_OBJECT_0 ) iReCode = ERROR_CODE_WAIT_RESPONSE_TIMEOUT;
		CHECK_RETURN_IF_FAIL( iReCode );
	}
	else
	{
		int iOffset = 2048;
		ProtocalMTKApi protocalApi;
		protocalApi.PrepareIoDataToSend( wr, CMD_MTK_UPGRADE_WRITE, iOffset >> 16, iOffset & 0xffff, -1, 0, 128 );
		iReCode = SendCommandAndCheck( &protocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
		CHECK_RETURN_IF_FAIL( iReCode );

		protocalApi.PrepareIoDataToSend( wr, CMD_MTK_UPGRADE_ENTER );
		SendCommand( (unsigned char*)&wr, (unsigned char*)&rd );
		DWORD dwResult = ::WaitForSingleObject( ioEvent, 10000 );
		if( dwResult != WAIT_OBJECT_0 ) iReCode = ERROR_CODE_WAIT_RESPONSE_TIMEOUT;
		CHECK_RETURN_IF_FAIL( iReCode );
	}


	Sleep( 500 );

	return ERROR_CODE_OK;
}
unsigned int CCommHID::UpgradeMtkBoard( unsigned char devNo, unsigned char* pMtkBin, unsigned int len, LPUpdateProcessPosCallBack lpProcess )
{
	unsigned int iReCode = ERROR_CODE_COMM_ERROR, flags = 0;
	unsigned char writeBuffer[REAL_HAL_WR_LEN] = {0};
	int byteLeft = len, iOffset = 0, onceWrite = REAL_HAL_WR_LEN;
	unsigned short checkSum = 0;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	TCHAR chName[50] = {0};
	transformat( chName, _T("%s-%d"), _T("IoDevice"), m_HalInterface->GetServiceFackID() );
	HANDLE ioEvent = ::OpenEvent( EVENT_ALL_ACCESS, FALSE, chName );
	ResetEvent( ioEvent );

	iReCode = ReadFromUsbMemory( MTK_VER_ADDR, (unsigned char*)&flags, 4 );
	CHECK_RETURN_IF_FAIL( iReCode );

	while( byteLeft > 0 )
	{
		onceWrite = byteLeft > 1024 ? 1024 : byteLeft;

		checkSum += caculate_check_sum_u816( pMtkBin, onceWrite );
		iReCode = WriteToUsbMemory( MTK_TXRX_BUF_MTK, pMtkBin, onceWrite );
		CHECK_RETURN_IF_FAIL( iReCode );

		if(0x80 == (flags >> 24))
		{
			ProtocalMcapApi protocalApi;
			protocalApi.PrepareIoDataToSend( wr, CMD_MTK_UPGRADE_WRITE, iOffset >> 16, iOffset & 0xffff, onceWrite, caculate_check_sum_u816(pMtkBin, onceWrite));
			//protocalApi.PrepareIoDataToSend( wr, CMD_MTK_UPGRADE_WRITE, iOffset, 1 );
			iReCode = SendCommandAndCheck( &protocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
			CHECK_RETURN_IF_FAIL( iReCode );
		}
		else
		{
			ProtocalMTKApi protocalApi;
			protocalApi.PrepareIoDataToSend( wr, CMD_MTK_UPGRADE_WRITE, iOffset >> 16, iOffset & 0xffff, 1, 0, onceWrite );
			//protocalApi.PrepareIoDataToSend( wr, CMD_MTK_UPGRADE_WRITE, iOffset, 1 );
			iReCode = SendCommandAndCheck( &protocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
			CHECK_RETURN_IF_FAIL( iReCode );
		}


		pMtkBin += onceWrite;
		iOffset += onceWrite;
		byteLeft -= onceWrite;

		if( lpProcess ) lpProcess(devNo, iOffset, len);
	}

	memset( writeBuffer, 0, sizeof(writeBuffer) );
	writeBuffer[0] = 0x35;
	writeBuffer[1] = ~writeBuffer[0];
	writeBuffer[2] = len >> 24;
	writeBuffer[3] = len >> 16;
	writeBuffer[4] = len >> 8;
	writeBuffer[5] = len & 0xff;
	writeBuffer[6] = checkSum >> 8;
	writeBuffer[7] = checkSum & 0xff;

	iReCode = WriteToUsbMemory( MTK_TXRX_BUF_MTK, writeBuffer, 128 );
	CHECK_RETURN_IF_FAIL( iReCode );

	if(0x80 == (flags >> 24))
	{
		iOffset = -2048;
		ProtocalMcapApi protocalApi;
		protocalApi.PrepareIoDataToSend( wr, CMD_MTK_UPGRADE_WRITE, iOffset >> 16, iOffset & 0xffff, 128, caculate_check_sum_u816(writeBuffer, 128) );
		iReCode = SendCommandAndCheck( &protocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
		CHECK_RETURN_IF_FAIL( iReCode );

		protocalApi.PrepareIoDataToSend( wr, CMD_MTK_UPGRADE_LEAVE );
		SendCommand( (unsigned char*)&wr, (unsigned char*)&rd );
		//CHECK_RETURN_IF_FAIL( iReCode );
	}
	else
	{
		iOffset = 2048;
		ProtocalMTKApi protocalApi;
		protocalApi.PrepareIoDataToSend( wr, CMD_MTK_UPGRADE_WRITE, iOffset >> 16, iOffset & 0xffff, -1, 0, 128 );
		iReCode = SendCommandAndCheck( &protocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
		CHECK_RETURN_IF_FAIL( iReCode );

		protocalApi.PrepareIoDataToSend( wr, CMD_MTK_UPGRADE_LEAVE );
		SendCommand( (unsigned char*)&wr, (unsigned char*)&rd );
		//CHECK_RETURN_IF_FAIL( iReCode );
	}


	DWORD dwResult = ::WaitForSingleObject( ioEvent, 10000 );
	if( dwResult != WAIT_OBJECT_0 ) iReCode = ERROR_CODE_WAIT_RESPONSE_TIMEOUT;
	CHECK_RETURN_IF_FAIL( iReCode );

	Sleep( 500 );

	return iReCode;
}
unsigned int CCommHID::DetectMtkExtendSignal( unsigned char* signal/* = 0*/ )
{
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;

	//ctp_cmd_std_t wr;
	//ctp_rsp_std_t rd;
	//ProtocalMTKApi protocalApi;

	//protocalApi.PrepareIoDataToSend( wr, CMD_MTK_EXT_INT_STA );
	//protocalApi.PrepareIoDataToSend( wr, CMD_MTK_UPGRADE_WRITE, iOffset, 1 );
	//iReCode = SendCommandAndCheck( &protocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
	//CHECK_RETURN_IF_FAIL( iReCode );

	//*signal = (unsigned char)rd.scap.d0;

	return iReCode;
}
unsigned int CCommHID::SetMtkExternOutput( unsigned char PB0, unsigned char PB1, unsigned char PB2 )
{
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;
	ProtocalMTKApi protocalApi;

	protocalApi.PrepareIoDataToSend( wr, CMD_MTK_EXT_OUTPUT, PB0, PB1, PB2 );
	//protocalApi.PrepareIoDataToSend( wr, CMD_MTK_UPGRADE_WRITE, iOffset, 1 );
	iReCode = SendCommandAndCheck( &protocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 3 );
	CHECK_RETURN_IF_FAIL( iReCode );

	return iReCode;
}
