#include "CommMtk.h"
#include "framework.h"
#include "checksum.h"
#include "../Protocal/Protocal.h"
#include "onlinelog.h"

//#define FIXED_READ_SIZE(x)  ((x) + 0)
#define FIXED_WRITE_SIZE(x) ((x) + 8)

REGIST_RUNTIME_CLASS_PVOID( COMM_TYPE, (COMM_TYPE)LINK_TYPE_USB, CCommMtk )


CCommMtk::CCommMtk(LPVOID param)
	:m_HalInterface( AllocateHalSrvInterface() )
	//,m_CommAddr(new CommAddr())
{
#ifdef _DEBUG
	m_iDeviceIndex = 0;
#endif
	
}
CCommMtk::~CCommMtk()
{
	RestoreHalSrvInterface( m_HalInterface );
	//if (m_CommAddr != nullptr )
	//{
	//	delete m_CommAddr;
	//	m_CommAddr = nullptr;
	//}
}
unsigned int CCommMtk::GetCommType()
{
	return LINK_TYPE_USB;
}
unsigned int CCommMtk::SyncWorkcInit( unsigned char bHold/* = 1*/ )
{
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	iReCode = GetMtkType();
	CHECK_RETURN_IF_FAIL( iReCode );

	if(GetCommAddr().Get_MtkType() == MTK_TYPE_V8)
	{
		ProtocalMcapApi protocalApi;
		protocalApi.PrepareIoDataToSend( wr, CMD_HOLD_MTK, bHold );
		return SendCommandAndCheck( &protocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
	}
	else
	{
		ProtocalMTKApi protocalApi;
		protocalApi.PrepareIoDataToSend( wr, CMD_HOLD_MTK, bHold );
		return SendCommandAndCheck( &protocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
	}


}
BOOL CCommMtk::Connected()
{
	return m_HalInterface->IsConnected(  );
}
unsigned int CCommMtk::HalTrySetDeviceManuly( Device hDevice )
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
unsigned int CCommMtk::SendCommand( unsigned char* pWrite, unsigned char* pRead )
{
	pRead;
	unsigned int iRetCode = ERROR_CODE_COMM_ERROR;

	{
		//clear response buffer
		unsigned char clearBuffer[] = {0x02, GET_MTK_RSP_BUF() >> 8, GET_MTK_RSP_BUF() & 0xff, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		iRetCode = m_HalInterface->Write( clearBuffer, sizeof(clearBuffer) );

	}
	SysDelay(3);
	if( ERROR_CODE_OK == iRetCode )
	{
		unsigned char* pDes = (unsigned char*)pWrite;
		const int writeLen = 8 + sizeof(ctp_cmd_std_t);
		unsigned char writeBuffer[writeLen] = { 0x02,  GET_MTK_CMD_BUF() >> 8, GET_MTK_CMD_BUF() & 0xff, 0x10, 0x10, 0x10, 0x10, 0x10 };
		for( int index = 0; index < sizeof(ctp_cmd_std_t); index++ )
		{
			writeBuffer[8 + index] = pDes[index];
		}

		iRetCode = m_HalInterface->Write( writeBuffer, writeLen );
	}
	
	return iRetCode;
}
unsigned int CCommMtk::SendCommandAndCheck( ProtocalApi* protocalApi, unsigned char* pWrite, unsigned char* pRead, unsigned short delay/* = 30*/ )
{
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;

	iReCode = SendCommand( pWrite, pRead );

	if( iReCode == ERROR_CODE_OK )
	{
		//SysDelay( 30 );  //wait for mtk board action done
		SysDelay( delay );

		memset( pRead, 0, sizeof(ctp_rsp_std_t) );

		unsigned char writeBuffer[] = { 0x02, GET_MTK_RSP_BUF() >> 8, GET_MTK_RSP_BUF() & 0xff, CMD_NA };

		LoopTicker tick( 100 );
		while ( tick.TickOnce() )
		{
			//iReCode = m_HalInterface->IoCtrl( writeBuffer, sizeof(writeBuffer), (unsigned char*)pRead, sizeof(ctp_rsp_std_t) );

			iReCode = ReadFromUsbMemory( GET_MTK_RSP_BUF(), pRead, protocalApi->ResponseLength() );
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
unsigned int CCommMtk::ReadFromUsbMemory( unsigned short addr, unsigned char* pRead, unsigned short len )
{
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;

	unsigned short lpAddr = addr;
	unsigned char* buffer = pRead;
	int byteLeft = len, maxLoop = len, onceRead = REAL_HAL_RD_LEN;
	while( byteLeft > 0 && (maxLoop--) > 0 )
	{
		onceRead = min( REAL_HAL_RD_LEN, byteLeft );

		unsigned char writeBuffer[] = { 0x02, lpAddr >> 8, lpAddr & 0xff, 0 };

		unsigned int readed = 0;
		iReCode = m_HalInterface->IoCtrl( writeBuffer, sizeof(writeBuffer), buffer, onceRead, &readed );
		if( iReCode != ERROR_CODE_OK ) break;

		byteLeft -= readed;
		buffer   += readed;
		lpAddr   += readed;
	}

	return iReCode;
}
unsigned int CCommMtk::WriteToUsbMemory( unsigned short addr, const unsigned char* pWrite, unsigned short len )
{
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;

	unsigned char writeBuffer[REAL_HAL_WR_LEN + 10] = {0};

	int byteLeft = len, onceWrite = REAL_HAL_WR_LEN;

	while( byteLeft > 0 )
	{
		onceWrite = min( REAL_HAL_WR_LEN, byteLeft );

		memset( writeBuffer, 0, sizeof(writeBuffer) );
		writeBuffer[0] = 0x02;
		writeBuffer[1] = (addr >> 8) & 0xff;
		writeBuffer[2] = (addr) & 0xff;
		memcpy_s( writeBuffer + 8, onceWrite, pWrite, onceWrite );

		iReCode = m_HalInterface->Write( writeBuffer, FIXED_WRITE_SIZE(onceWrite) );
		if( iReCode != ERROR_CODE_OK ) break;

		byteLeft -= onceWrite;
		pWrite += onceWrite;
		addr += onceWrite;
	}

	return iReCode;
}
unsigned int CCommMtk::SetIoVoltage( unsigned short vdd, unsigned short iovdd, unsigned short vih )
{
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	iReCode = GetMtkType();
	CHECK_RETURN_IF_FAIL( iReCode );

	if(GetCommAddr().Get_MtkType() == MTK_TYPE_V8)
	{
		ProtocalMcapApi protocalApi;
		protocalApi.PrepareIoDataToSend( wr, CMD_MTK_SET_VOLTAGE, vdd, iovdd, vih);
		iReCode = SendCommandAndCheck( &protocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 5 );
		CHECK_RETURN_IF_FAIL( iReCode );
	
	}
	else
	{
		ProtocalMTKApi protocalApi;
		protocalApi.PrepareIoDataToSend( wr, CMD_MTK_SET_VOLTAGE, vdd, iovdd, vih);
		iReCode = SendCommandAndCheck( &protocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 5 );
		CHECK_RETURN_IF_FAIL( iReCode );
	}


	return iReCode;
}
unsigned int CCommMtk::MtkBoardReBoot(unsigned int wantGo)
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
unsigned int CCommMtk::PrepareMtkBoardUpgrade(  )
{
	unsigned int iReCode = ERROR_CODE_COMM_ERROR, flags = 0;
	unsigned char writeBuffer[REAL_HAL_WR_LEN + 10] = {0};

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;
	

	TCHAR chName[50] = {0};
	transformat( chName, _T("%s-%d"), _T("IoDevice"), m_HalInterface->GetServiceFackID() );
	HANDLE ioEvent = ::OpenEvent( EVENT_ALL_ACCESS, FALSE, chName );
	ResetEvent( ioEvent );

	iReCode = GetMtkType();
	CHECK_RETURN_IF_FAIL( iReCode );

	iReCode = ReadFromUsbMemory( GET_MTK_VER_ADDR(), (unsigned char*)&flags, 4 );
	CHECK_RETURN_IF_FAIL( iReCode );

	memset( writeBuffer, 0, sizeof(writeBuffer) );
	iReCode = WriteToUsbMemory( GET_MTK_TXRX_BUF_MTK(), writeBuffer, 128 );
	CHECK_RETURN_IF_FAIL( iReCode );


	if(0x80 == (flags >> 24)||(GetCommAddr().Get_MtkType() == MTK_TYPE_V8))
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
unsigned int CCommMtk::UpgradeMtkBoard( unsigned char devNo, unsigned char* pMtkBin, unsigned int len, LPUpdateProcessPosCallBack lpProcess )
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

	iReCode = GetMtkType();
	CHECK_RETURN_IF_FAIL( iReCode );

	iReCode = ReadFromUsbMemory( GET_MTK_VER_ADDR(), (unsigned char*)&flags, 4 );
	CHECK_RETURN_IF_FAIL( iReCode );

	while( byteLeft > 0 )
	{
		onceWrite = byteLeft > 1024 ? 1024 : byteLeft;

		checkSum += caculate_check_sum_u816( pMtkBin, onceWrite );
		iReCode = WriteToUsbMemory( GET_MTK_TXRX_BUF_MTK(), pMtkBin, onceWrite );
		CHECK_RETURN_IF_FAIL( iReCode );

		if(0x80 == (flags >> 24)||(GetCommAddr().Get_MtkType() == MTK_TYPE_V8))
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

	iReCode = WriteToUsbMemory( GET_MTK_TXRX_BUF_MTK(), writeBuffer, 128 );
	CHECK_RETURN_IF_FAIL( iReCode );

	if(0x80 == (flags >> 24)||(GetCommAddr().Get_MtkType() == MTK_TYPE_V8))
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

unsigned int CCommMtk::ReadMtkBoard(unsigned char devNo, unsigned char* pMtkBin, unsigned int len, LPUpdateProcessPosCallBack lpProcess)
{
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
	int byteLeft = len, addr = 0, onceRead = REAL_HAL_RD_LEN;
	unsigned short checkSum = 0;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	ProtocalMcapApi protocalApi;
	//int a = 0xffff;
	//unsigned char buf[2*1024];

	//while(a--)
	//{
	//	unsigned char bReady = 0;
	//	iReCode = ReadFromUsbMemory( MTK_DATA_RDY, (unsigned char*)&bReady, 1 );
	//	if(iReCode!=0)
	//	{
	//		int b = 0;
	//	}
	//	iReCode = ReadFromUsbMemory( MTK_TXRX_BUF_MTK, (unsigned char*)buf, 2*1024 );
	//	if(iReCode!=0)
	//	{
	//		int b = 0;
	//	}
	//	iReCode = WriteToUsbMemory( MTK_TXRX_BUF_MTK, (unsigned char*)buf, 2*1024 );
	//	if(iReCode!=0)
	//	{
	//		int b = 0;
	//	}

	//	bReady = ~bReady;
	//	iReCode = WriteToUsbMemory( MTK_DATA_RDY, (unsigned char*)&bReady, 1 );
	//	if(iReCode!=0)
	//	{
	//		int b = 0;
	//	}
	//
	//}

	while( byteLeft > 0 )
	{
		onceRead = byteLeft > REAL_HAL_RD_LEN ? REAL_HAL_RD_LEN : byteLeft;

		protocalApi.PrepareIoDataToSend( wr, CMD_MTK_UPGRADE_READ, addr >> 16, addr & 0xffff, onceRead );
		iReCode = SendCommandAndCheck( &protocalApi,(unsigned char*)&wr, (unsigned char*)&rd );
		CHECK_RETURN_IF_FAIL( iReCode );

		iReCode = ReadFromUsbMemory( GET_MTK_TXRX_BUF_MTK(), pMtkBin, onceRead );
		CHECK_RETURN_IF_FAIL( iReCode );

		checkSum = caculate_check_sum_u816( pMtkBin, onceRead );
		if(rd.mcap.d0 != checkSum) iReCode = ERROR_CODE_CHECK_SUM_MISMATCH;
		CHECK_RETURN_IF_FAIL( iReCode );

		pMtkBin += onceRead;
		addr += onceRead;
		byteLeft -= onceRead;

		if( lpProcess ) lpProcess(devNo, addr, len);
	}
	return iReCode;
}

unsigned int CCommMtk::DetectMtkExtendSignal( unsigned char* signal/* = 0*/ )
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
unsigned int CCommMtk::SetMtkExternOutput( unsigned char PB0, unsigned char PB1, unsigned char PB2 )
{
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	iReCode = GetMtkType();
	CHECK_RETURN_IF_FAIL( iReCode );

	if(GetCommAddr().Get_MtkType() == MTK_TYPE_V8)
	{
		ProtocalMcapApi protocalApi;
		protocalApi.PrepareIoDataToSend( wr, CMD_MTK_EXT_OUTPUT, PB0, PB1, PB2 );
		//protocalApi.PrepareIoDataToSend( wr, CMD_MTK_UPGRADE_WRITE, iOffset, 1 );
		iReCode = SendCommandAndCheck( &protocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 3 );
		CHECK_RETURN_IF_FAIL( iReCode );
	}
	else
	{
		ProtocalMTKApi protocalApi;
		protocalApi.PrepareIoDataToSend( wr, CMD_MTK_EXT_OUTPUT, PB0, PB1, PB2 );
		//protocalApi.PrepareIoDataToSend( wr, CMD_MTK_UPGRADE_WRITE, iOffset, 1 );
		iReCode = SendCommandAndCheck( &protocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 3 );
		CHECK_RETURN_IF_FAIL( iReCode );
	}


	return iReCode;
}

unsigned int CCommMtk::GetMtkType()
{
	unsigned int iReCode = ERROR_CODE_COMM_ERROR, flags = 0;
	iReCode = ReadFromUsbMemory( MTK_LINK_AND_ID, (unsigned char*)&flags, 4 );
	CHECK_RETURN_IF_FAIL( iReCode );
	if(((flags&0xff000000)>>24) == 0x08)
	{
		GetCommAddr().SetMtkType(MTK_TYPE_V8);
	}
	else
	{
		GetCommAddr().SetMtkType(MTK_TYPE_V5);
	}
	return iReCode;
}

CommAddr& CCommMtk::GetCommAddr()
{
	return m_CommAddr;
}

unsigned short CCommMtk::GET_MTK_LINK_AND_ID()
{
	return GetCommAddr().GET_MTK_LINK_AND_ID();
}

unsigned short CCommMtk::GET_MTK_DEVICE_NO_ADDR()
{
	return GetCommAddr().GET_MTK_DEVICE_NO_ADDR();
}

unsigned short CCommMtk::GET_MTK_CMD_BUF()
{
	return GetCommAddr().GET_MTK_CMD_BUF();
}

unsigned short CCommMtk::GET_MTK_RSP_BUF()
{
	return GetCommAddr().GET_MTK_RSP_BUF();
}

unsigned short CCommMtk::GET_MTK_FUNC_BUF()
{
	return GetCommAddr().GET_MTK_FUNC_BUF();
}

unsigned short CCommMtk::GET_MTK_TXRX_BUF_SCAP()
{
	return GetCommAddr().GET_MTK_TXRX_BUF_SCAP();
}

unsigned short CCommMtk::GET_MTK_TXRX_BUF_MCAP()
{
	return GetCommAddr().GET_MTK_TXRX_BUF_MCAP();
}

unsigned short CCommMtk::GET_MTK_DATA_RDY()
{
	return GetCommAddr().GET_MTK_DATA_RDY();
}

unsigned short CCommMtk::GET_MTK_TXRX_BUF_MTK()
{
	return GetCommAddr().GET_MTK_TXRX_BUF_MTK();
}

unsigned short CCommMtk::GET_MTK_DEV_TYPE_ADDR()
{
	return GetCommAddr().GET_MTK_DEV_TYPE_ADDR();
}

unsigned short CCommMtk::GET_MTK_VER_ADDR()
{
	return GetCommAddr().GET_MTK_VER_ADDR();
}

unsigned short CCommMtk::GET_MTK_FLASHBOOT_1KCHK()
{
	return GetCommAddr().GET_MTK_FLASHBOOT_1KCHK();
}
