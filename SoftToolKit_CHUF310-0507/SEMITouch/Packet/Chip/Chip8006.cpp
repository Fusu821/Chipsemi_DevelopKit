#include "Chip8006.h"
#include "checksum.h"

REGIST_RUNTIME_CLASS( CHIP_TYPE, (CHIP_TYPE)SEMI_IC_CHGA8006, CChip8006 )


#define DUT_WR_BUFF_ADDR        0x20010000
#define DUT_RD_BUFF_ADDR        0x20010400

CChip8006Imp::CChip8006Imp()
{
	m_ProtocalApi = new ProtocalMcapApi();
}
CChip8006Imp::~CChip8006Imp()
{
	if( NULL != m_ProtocalApi )
	{
		delete m_ProtocalApi;
		m_ProtocalApi = NULL;
	}
}
unsigned int CChip8006Imp::SetCommContext( const CtpHalCfg& halCfg )
{
	unsigned int iReCode = ERROR_CODE_OK;

	if( halCfg.IIC.slaveAddr < 0xff )
		m_slaveAddr = halCfg.IIC.slaveAddr;

	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	iReCode = pComBase->SetIoVoltage( halCfg.vddVoltage, halCfg.iovddVotage, halCfg.vihVotage );
	CHECK_RETURN_IF_FAIL( iReCode );

	unsigned char chipFamily = GetContainerInterface()->GetChipFamily( halCfg.icType );
	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_CHK_CFG, 0, (chipFamily << 8) | m_slaveAddr, (halCfg.speed << 8) | halCfg.protocalType );
	return pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 5 );
}
unsigned int CChip8006Imp::GetOSCTrim( unsigned char* trim32k, unsigned char* trim64m,unsigned int osStd32k, unsigned int osStd64m )
{
	unsigned int iReCode = ERROR_CODE_OK;

	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	unsigned short trim1 = 0, trim2 = 0;

	//unsigned int oscTrimTick = osStd/*600000*/;

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_DUT_CLK_CALIB, 0, osStd64m & 0xffff, osStd32k * 25 );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 70 );
	CHECK_RETURN_IF_FAIL( iReCode );

    *trim32k = rd.mcap.d1 & 0xff;
    *trim64m = rd.mcap.d0 & 0xff;

	return iReCode;
}
unsigned int CChip8006Imp::GetShortData( unsigned short* sData, unsigned short len )
{
	unsigned int iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_SHORT_TST, 0 );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
	CHECK_RETURN_IF_FAIL( iReCode );

	iReCode = pComBase->ReadFromUsbMemory( pComBase->GET_MTK_TXRX_BUF_MCAP(), (unsigned char*)sData, len );
	CHECK_RETURN_IF_FAIL( iReCode );

	//unsigned int checkSum = caculate_check_sum_ex( (unsigned char*)sData, len );
	//if( checkSum != ((rd.mcap.d1 << 16) + rd.mcap.d0))
	//	iReCode = ERROR_CODE_CHECK_SUM_MISMATCH;
	//CHECK_RETURN_IF_FAIL( iReCode );

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_CTP_RST );
	pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );

	return iReCode;
}
unsigned int CChip8006Imp::GetBootVersion( unsigned short* bootVer )
{
	unsigned char iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	//ctp_cmd_std_t wr;
	//ctp_rsp_std_t rd;

	//m_ProtocalApi->PrepareIoDataToSend( wr, CMD_CTP_RST );
	//iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
	//CHECK_RETURN_IF_FAIL( iReCode );

	//SysDelay( 50 );

	//unsigned char readBuffer[8] = {0};
	//iReCode = ReadCoreSpace( 0x20000000 + 0x10, readBuffer, 8 );
	//CHECK_RETURN_IF_FAIL( iReCode );

	//*bootVer = ( readBuffer[7]<< 8 ) + readBuffer[6];

	unsigned char readBuffer[4] = {0};
	iReCode = ReadBurnSpace( 0x003c, readBuffer, 4 );
	CHECK_RETURN_IF_FAIL( iReCode );

	*bootVer = ( readBuffer[1] << 8 ) + readBuffer[0];

	return iReCode;
}
unsigned int CChip8006Imp::GetBootCheckSum( unsigned int* checkSum, unsigned int* omTime )
{
	unsigned char iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_FW_SUM, 0, 0, 0 );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
	CHECK_RETURN_IF_FAIL( iReCode );

	*checkSum = (rd.mcap.d0 << 16) | rd.mcap.d1;
	*omTime = (rd.mcap.d2 << 16) | rd.mcap.d3;

	return iReCode;
}
unsigned int CChip8006Imp::GetFirmWareConfig( unsigned char* configBuffer, unsigned short len )
{
	unsigned char iReCode = ERROR_CODE_OK;
	
	iReCode = ReadBurnSpace( 0x7000, configBuffer, len );
	CHECK_RETURN_IF_FAIL( iReCode );

	return iReCode;
}
unsigned int CChip8006Imp::BurnBootBin( unsigned int bootLen, unsigned int bootSVN/* = 0*/, unsigned short oscTrim /*= 0*/ )
{
	unsigned char iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;
	
	//fixedBootLen = bootLen + checksum
	//bootLen | checksum | time | svn
	const unsigned int fixedBootLen = bootLen;
	unsigned char burnType = OTP_W_CHK | TLK_DATACHK_EX1;

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_MTK_MEM_MOVE, 0, fixedBootLen >> 16, (fixedBootLen & 0xffff));
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 30 );
	CHECK_RETURN_IF_FAIL( iReCode );

	//unsigned char mark = 0x4b;
	//iReCode = WriteBurnSpace( 0x08, &mark, 1, burnType );
	//CHECK_RETURN_IF_FAIL( iReCode );

	unsigned int dut_id = 0;
	iReCode = ReadBurnSpace( fixedBootLen, (unsigned char*)&dut_id, 4 );
	CHECK_RETURN_IF_FAIL( iReCode );

	if( 0xffffffff == dut_id )
	{
		SYSTEMTIME SysTime;
		::GetLocalTime(&SysTime);
		dut_id = (SysTime.wMonth << 22) + (SysTime.wDay << 17) + (SysTime.wHour << 12) + (SysTime.wMinute << 6) + SysTime.wSecond;

		iReCode = WriteBurnSpace( fixedBootLen, (unsigned char*)&dut_id, 4, burnType );
		CHECK_RETURN_IF_FAIL( iReCode );
	}

	if( bootSVN > 0 )
	{
		unsigned int svn = 0;
		iReCode = ReadBurnSpace( fixedBootLen + 4, (unsigned char*)&svn, 4 );
		if( 0xffffffff == svn )
		{
			iReCode = WriteBurnSpace( fixedBootLen + 4, (unsigned char*)&bootSVN, 4, burnType );
			CHECK_RETURN_IF_FAIL( iReCode );
		}
	}

	//if(oscTrim > 0)
	//{
	//	unsigned short osc =  ( ~oscTrim ) & 0xff;
	//	osc = ( osc << 8 ) + oscTrim;
	//	iReCode = WriteBurnSpace( 0xe000, (unsigned char*)&osc, 2, burnType );
	//	CHECK_RETURN_IF_FAIL( iReCode );
	//}

	return iReCode;
}
unsigned int CChip8006Imp::BurnConfigBin( const unsigned char* config, unsigned short len )
{
	unsigned int iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	unsigned char burnType = OTP_W_CHK | TLK_DATACHK_EX1;

	iReCode = WriteBurnSpace( 0x7000, config, len, burnType );
	CHECK_RETURN_IF_FAIL( iReCode );

	//iReCode = WriteBurnSpace( 0xf000, config, len, burnType );
	//CHECK_RETURN_IF_FAIL( iReCode );

	return iReCode;
}
unsigned int CChip8006Imp::EraseBurnSpace( unsigned int addr, unsigned int len )
{
	unsigned int iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_FLASH_ERASE, addr >> 16, addr & 0xffff, len >> 16, len & 0xffff );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 50 );
	CHECK_RETURN_IF_FAIL( iReCode );

	return iReCode;
}

unsigned int CChip8006Imp::SetClkInFctMode( unsigned short clk, unsigned char filterOff )
{
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
	unsigned char cfgBuffer[1024] = {0};

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_CTP_SSCAN, 0, 0x00 );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 30 );
	CHECK_RETURN_IF_FAIL( iReCode );

	iReCode = ReadCoreSpace( 0x20000080, cfgBuffer, sizeof(cfgBuffer) );
	CHECK_RETURN_IF_FAIL( iReCode );

	cfgBuffer[0x23] = (unsigned char)clk;
	unsigned int checkSum = caculate_check_sum_u32((unsigned int*)cfgBuffer, sizeof(cfgBuffer) - 4);
	checkSum = 1 + ~checkSum;
	unsigned int* pCheckDest = (unsigned int*)&cfgBuffer[sizeof(cfgBuffer) - 4];
	*pCheckDest = checkSum;

	iReCode = WriteCoreSpace( 0x20000080, cfgBuffer, sizeof(cfgBuffer) );
	CHECK_RETURN_IF_FAIL( iReCode );

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_CTP_SSCAN, 1, 0x7265 );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 30 );
	CHECK_RETURN_IF_FAIL( iReCode );

	return iReCode;
}
unsigned int CChip8006Imp::GetDifferMax(unsigned short frames, short* sData, unsigned short len )
{
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_CFG_INIT, frames );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 1 );

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_CTP_SSCAN, 0, 0x0805, frames );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 50 );
	CHECK_RETURN_IF_FAIL( iReCode );

	iReCode = ReadCoreSpace( m_DifferAddr, (unsigned char*)sData, len );
	CHECK_RETURN_IF_FAIL( iReCode );

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_CTP_SSCAN, 1 );

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_CFG_INIT, 1 );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 1 );

	return iReCode;
}
unsigned int CChip8006Imp::GetCurrent8006( short (&level)[2][3], unsigned short* activeCurrrent, unsigned short* sleepCurrent, unsigned short* deepCurrent, unsigned short* vbactiveCurrrent, unsigned short* vbsleepCurrent, unsigned short* vbdeepCurrent )
{
	unsigned int iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_MTK_TEST_PINS_LEAK, level[0][0], level[0][1], level[0][2], level[1][0], level[1][1], level[1][2]);
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
	CHECK_RETURN_IF_FAIL( iReCode );

	*activeCurrrent = rd.mcap.d0;
	*sleepCurrent = rd.mcap.d1;
	*deepCurrent = rd.mcap.d2;
	*vbactiveCurrrent = rd.mcap.d3;
	*vbsleepCurrent   = rd.mcap.d4;
	*vbdeepCurrent   = rd.mcap.d5;
	return iReCode;
}

unsigned int CChip8006Imp::SwitchMode(unsigned char modeType, unsigned short len)
{
	unsigned char iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;
	if( 0 == len && MODE_TOUCH != modeType ) return ERROR_CODE_INVALID_PARAM;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	m_RawDataAddr = m_DifferAddr = m_BaseAddr = 0;

	//m_ProtocalApi->PrepareIoDataToSend( wr, CMD_IDENTITY );
	//iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 5 );
	//CHECK_RETURN_IF_FAIL( iReCode );

	//if( 0xffff != (rd.mcap.d0 + rd.mcap.d1) || rd.mcap.d0 != 0xE902 )
	//{
	//	iReCode = ERROR_CODE_INVALID_PARAM;
	//	CHECK_RETURN_IF_FAIL( iReCode );
	//}

	//unsigned char writeBuffer[] = {0x20, 0x00, 0x00, 0x00};
	//unsigned char readBuffer[0x34];
	////iReCode = BSPRWriteAndRead( writeBuffer, sizeof(writeBuffer), readBuffer, sizeof(readBuffer) );
	//iReCode = ReadCoreSpace( 0x20000000, readBuffer, sizeof(readBuffer) );

	m_RawDataAddr = m_DifferAddr = m_BaseAddr = 0x20000000 + 0x100;
	//m_DifferAddr  = 0x20000000 + ( (unsigned int)(readBuffer[0x23] << 8) + readBuffer[0x22] );
	//m_BaseAddr    = 0x20000000 + ( (unsigned int)(readBuffer[0x25] << 8) + readBuffer[0x24] );

	if( MODE_RAWDATA == modeType )
	{
		m_ProtocalApi->PrepareIoDataToSend( wr, CMD_DATA_SYNC, m_RawDataAddr, len, 0 );
		iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
		CHECK_RETURN_IF_FAIL( iReCode );
	}
	else if( MODE_DIFFER == modeType )
	{
		m_ProtocalApi->PrepareIoDataToSend( wr, CMD_DATA_SYNC, m_DifferAddr, len, 0 );
		iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
		CHECK_RETURN_IF_FAIL( iReCode );
	}
	else if( MODE_TOUCH == modeType )
	{
		m_ProtocalApi->PrepareIoDataToSend( wr, CMD_DATA_SYNC, 0x20000000 + 0x130, 84, 1 );
		iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
		CHECK_RETURN_IF_FAIL( iReCode );
	}
	else if( MODE_BASE == modeType )
	{
		m_ProtocalApi->PrepareIoDataToSend( wr, CMD_DATA_SYNC, m_BaseAddr, len, 0 );
		iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
		CHECK_RETURN_IF_FAIL( iReCode );
	}
	else if( MODE_SIMULATE_RAW == modeType )
	{
		m_ProtocalApi->PrepareIoDataToSend( wr, CMD_DATA_SYNC, m_RawDataAddr, len, 0 );
		iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
		CHECK_RETURN_IF_FAIL( iReCode );
	}
	else if( MODE_SIMULATE_DIFF == modeType )
	{
		m_ProtocalApi->PrepareIoDataToSend( wr, CMD_DATA_SYNC, m_DifferAddr, len, 0 );
		iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
		CHECK_RETURN_IF_FAIL( iReCode );
	}
	else if( MODE_TWOICS_RAWDATA == modeType )
	{
		m_ProtocalApi->PrepareIoDataToSend( wr, CMD_DATA_SYNC, m_RawDataAddr, len, 2 );
		iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
		CHECK_RETURN_IF_FAIL( iReCode );
	}
	else if( MODE_TWOICS_TOUCH == modeType )
	{
		m_ProtocalApi->PrepareIoDataToSend( wr, CMD_DATA_SYNC, 0x20000000 + 0x130, 84, 3 );
		iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
		CHECK_RETURN_IF_FAIL( iReCode );
	}

	return ERROR_CODE_OK;
}

unsigned int CChip8006Imp::GetRawData(short* rawdataBuffer, unsigned short len)
{
	unsigned int iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	LoopTicker tick( 500 );
	while( tick.TickOnce() )
	{
		unsigned char bReady = 0;
		iReCode = pComBase->ReadFromUsbMemory( pComBase->GET_MTK_DATA_RDY(), (unsigned char*)&bReady, 1 );
		if( bReady ) break;

		SysDelay( 1 );
	}

	tick.CheckTickAndMark( iReCode );
	CHECK_RETURN_IF_FAIL( iReCode );

	iReCode = pComBase->ReadFromUsbMemory( GetTxRxBufferAddr(), (unsigned char*)rawdataBuffer, len );
	CHECK_RETURN_IF_FAIL( iReCode );

	unsigned int readyBuffer = 0;
	pComBase->WriteToUsbMemory( pComBase->GET_MTK_DATA_RDY(), (unsigned char*)&readyBuffer, 1 );//4

	int numTail = ((len - 6) % 4) ? 6 : 8;
	unsigned short* pTail = (unsigned short*)((unsigned char*)rawdataBuffer + len - numTail);
	if(*pTail + *(pTail + 1) == 0xffff)
	{
		unsigned short crc = caculate_check_sum_u16( (unsigned short*)rawdataBuffer, len - numTail );
		if(crc != (*pTail))
		{
			//iReCode = ERROR_CODE_CHECK_SUM_MISMATCH;
		}
	}
	else
	{
		//iReCode = ERROR_CODE_INVALID_PARAM;
	}

	return iReCode;

}

unsigned int CChip8006Imp::GetTouchPoint(unsigned char* pointBuffer, unsigned short* len)
{
	unsigned int iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;
	//if( !IS_VALID_ADDR(m_RawDataAddr) )  return ERROR_CODE_INVALID_PARAM;

	LoopTicker tick( 500 );
	while( tick.TickOnce() )
	{
		unsigned char bReady = 0;
		iReCode = pComBase->ReadFromUsbMemory( pComBase->GET_MTK_DATA_RDY(), &bReady, 1 );
		if( bReady ) break;

		SysDelay( 1 );
	}
	tick.CheckTickAndMark( iReCode );
	CHECK_RETURN_IF_FAIL( iReCode );

	unsigned short dataLen = 84;
	iReCode = pComBase->ReadFromUsbMemory( GetTxRxBufferAddr(), (unsigned char*)pointBuffer, dataLen );
	CHECK_RETURN_IF_FAIL( iReCode );

	*len = dataLen;
	unsigned int readyBuffer = 0;
	pComBase->WriteToUsbMemory( pComBase->GET_MTK_DATA_RDY(), (unsigned char*)&readyBuffer, 4 );

	return iReCode;

}

unsigned int CChip8006Imp::WriteBurnSpace(unsigned int addr, const unsigned char* buffer, unsigned int len, unsigned char type)
{
	unsigned int iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	unsigned int left = len;
	while( left > 0 )
	{
		unsigned int onceLen = min( left, MAX_TXRX_SIZE );
		iReCode = pComBase->WriteToUsbMemory( GetTxRxBufferAddr(), buffer, onceLen );
		CHECK_RETURN_IF_FAIL( iReCode );

		unsigned int check_Sum = caculate_check_sum_ex( buffer, onceLen );
		m_ProtocalApi->PrepareIoDataToSend( wr, CMD_MEM_WR, addr, onceLen, (unsigned short)check_Sum, type, (unsigned short)(check_Sum >> 16) );
		iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 30 );//20
		CHECK_RETURN_IF_FAIL( iReCode );

		addr += onceLen;
		buffer += onceLen;
		left -= onceLen;
	}

	return iReCode;
}


unsigned int CChip8006Imp::ReadBurnSpace( unsigned int addr, unsigned char* buffer, unsigned int len )
{
	unsigned int iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	unsigned int left = len;

	while( left > 0 )
	{
		int onceLen = min( left, MAX_TXRX_SIZE );

		m_ProtocalApi->PrepareIoDataToSend( wr, CMD_MEM_RD, addr, onceLen, addr >> 16, OTP_R );
		iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 30 );
		CHECK_RETURN_IF_FAIL( iReCode );

		SysDelay(3);
		iReCode = pComBase->ReadFromUsbMemory( GetTxRxBufferAddr(), buffer, onceLen );
		CHECK_RETURN_IF_FAIL( iReCode );

		unsigned int check = caculate_check_sum_ex( buffer, onceLen );
		if( !m_ProtocalApi->CheckOtpDataOk( rd, buffer, onceLen ) ) 
		{
			//OnLineLogApp.AppendLogMessage( GetWrapperAddr()->GetIDMark(), value_buffer_to_string<unsigned char>( buffer, onceLen ).c_str() );
			iReCode = ERROR_CODE_CHECK_SUM_MISMATCH;

			break;
		}

		addr += onceLen;
		buffer += onceLen;
		left -= onceLen;
	}

	CHECK_RETURN_IF_FAIL( iReCode );

	return iReCode;
}

