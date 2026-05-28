#include "Chip310.h"
#include "checksum.h"

REGIST_RUNTIME_CLASS( CHIP_TYPE, (CHIP_TYPE)SEMI_IC_CHUF310, CChip310 )

#define DUT_WR_BUFF_ADDR        0x20010000
#define DUT_RD_BUFF_ADDR        0x20010400

CChip310Imp::CChip310Imp()
{
	m_ProtocalApi = new ProtocalMcapApi();
}
CChip310Imp::~CChip310Imp()
{
	if( NULL != m_ProtocalApi )
	{
		delete m_ProtocalApi;
		m_ProtocalApi = NULL;
	}
}

unsigned int CChip310Imp::SwitchMode(unsigned char modeType, unsigned short len)
{
	unsigned char iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;
	if( 0 == len && MODE_TOUCH != modeType ) return ERROR_CODE_INVALID_PARAM;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	m_RawDataAddr = m_DifferAddr = m_BaseAddr = 0;

	unsigned char writeBuffer[] = {0x20, 0x00, 0x00, 0x00};

	if( MODE_RAWDATA == modeType )
	{
		m_ProtocalApi->PrepareIoDataToSend( wr, CMD_DATA_SYNC, m_RawDataAddr, len, 0 );
		iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 5 );
		CHECK_RETURN_IF_FAIL( iReCode );
	}
	else if( MODE_DIFFER == modeType )
	{
		m_ProtocalApi->PrepareIoDataToSend( wr, CMD_DATA_SYNC, m_DifferAddr, len, 0 );
		iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 5  );
		CHECK_RETURN_IF_FAIL( iReCode );
	}
	else if( MODE_TOUCH == modeType )
	{
		m_ProtocalApi->PrepareIoDataToSend( wr, CMD_DATA_SYNC, 0x20000000 + 0x2c, 84, 1 );
		iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd , 5 );
		CHECK_RETURN_IF_FAIL( iReCode );
	}
	else if( MODE_BASE == modeType )
	{
		m_ProtocalApi->PrepareIoDataToSend( wr, CMD_DATA_SYNC, m_BaseAddr, len, 0 );
		iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd , 5 );
		CHECK_RETURN_IF_FAIL( iReCode );
	}

	return ERROR_CODE_OK;
}

unsigned int CChip310Imp::SetCommContext( const CtpHalCfg& halCfg )
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

unsigned int CChip310Imp::GetOSCTrim( fct_osc_temp_trim_310& fo_trim, unsigned int osStd52mNo1, unsigned int osStd52mNo2, unsigned int osStd52mNo3, unsigned char ischeck)
{
    unsigned int iReCode = ERROR_CODE_OK;

    ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
    if( !pComBase )  return ERROR_CODE_COMM_ERROR;

    ctp_cmd_std_t wr;
    ctp_rsp_std_t rd;

    unsigned short trim1 = 0, trim2 = 0, trim3 = 0;
	trim1 = osStd52mNo1 / 10;
	trim2 = osStd52mNo2 / 10;
	trim3 = osStd52mNo3 / 10;

    m_ProtocalApi->PrepareIoDataToSend( wr, CMD_DUT_CLK_CALIB, trim1, trim2, trim3, ischeck );
    iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 70 );
    CHECK_RETURN_IF_FAIL( iReCode );

    iReCode = pComBase->ReadFromUsbMemory( GetTxRxBufferAddr(), (unsigned char*)&fo_trim, sizeof(fct_osc_temp_trim_310) );
    CHECK_RETURN_IF_FAIL( iReCode );
    return iReCode;
}

unsigned int CChip310Imp::GetTrimeDosc(fct_osc_temp_trim_310& fo_trim)
{
    unsigned char iReCode = ERROR_CODE_OK;
    ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
    if( !pComBase )  return ERROR_CODE_COMM_ERROR;

    ctp_cmd_std_t wr;
    ctp_rsp_std_t rd;

    m_ProtocalApi->PrepareIoDataToSend( wr, CMD_CLK_TST);
    iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 70);
    CHECK_RETURN_IF_FAIL( iReCode );

	SysDelay(30);

    iReCode = pComBase->ReadFromUsbMemory( GetTxRxBufferAddr(), (unsigned char*)&fo_trim, sizeof(fct_osc_temp_trim_310) );
    CHECK_RETURN_IF_FAIL( iReCode );

    return iReCode;

}

unsigned int CChip310Imp::GetShortData( unsigned short* sData, unsigned short len )
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
unsigned int CChip310Imp::GetBootVersion( unsigned short* bootVer )
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

	unsigned short readBuffer[2] = {0};
	iReCode = ReadBurnSpace( 60, (unsigned char*)readBuffer, 4 );
	CHECK_RETURN_IF_FAIL( iReCode );

	*bootVer = readBuffer[0];

	return iReCode;
}
unsigned int CChip310Imp::GetBootCheckSum( unsigned int* checkSum, unsigned int* omTime )
{
	unsigned char iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_FW_SUM, 0, 0, 0 );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
	CHECK_RETURN_IF_FAIL( iReCode );

	unsigned char readBuffer[8] = {0};
	iReCode = ReadCoreSpace( DUT_RD_BUFF_ADDR, readBuffer, 8 );
	CHECK_RETURN_IF_FAIL( iReCode );

	unsigned int* intPointer = (unsigned int*)readBuffer;
	
	*checkSum = intPointer[0];
	*omTime   = intPointer[1];

	return iReCode;
}
unsigned int CChip310Imp::GetFirmWareConfig( unsigned char* configBuffer, unsigned short len )
{
	unsigned char iReCode = ERROR_CODE_OK;
	
	iReCode = ReadBurnSpace( 0x40, configBuffer, len );
	CHECK_RETURN_IF_FAIL( iReCode );

	return iReCode;
}
unsigned int CChip310Imp::BurnBootBin( unsigned int bootLen, unsigned int bootSVN/* = 0*/, unsigned short oscTrim /*= 0*/ )
{
	unsigned char iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	const unsigned int fixedBootLen = bootLen;
	unsigned char burnType = OTP_W_CHK | TLK_DATACHK_EX1;

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_MTK_MEM_MOVE, 0, fixedBootLen, (fixedBootLen >> 16), TLK_DUT_FLASH );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
	CHECK_RETURN_IF_FAIL( iReCode );

	return iReCode;
}
unsigned int CChip310Imp::BurnConfigBin( const unsigned char* config, unsigned short len )
{
	unsigned int iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	unsigned char burnType = OTP_W_CHK | TLK_DATACHK_EX1;

	iReCode = WriteBurnSpace( 0x40, config, len, burnType );
	CHECK_RETURN_IF_FAIL( iReCode );

	unsigned int dut_id = 0;
	unsigned char read_burn_time[32];
	unsigned char write_burn_time[32];
	iReCode = ReadBurnSpace( 512, (unsigned char*)read_burn_time, 32);
	CHECK_RETURN_IF_FAIL( iReCode );

	SYSTEMTIME SysTime;
	::GetLocalTime(&SysTime);
	dut_id = (SysTime.wMonth << 22) + (SysTime.wDay << 17) + (SysTime.wHour << 12) + (SysTime.wMinute << 6) + SysTime.wSecond;
	memcpy(write_burn_time,(unsigned char*)&dut_id,4);

	for(int i=0; i<28; i++ )
	{
		write_burn_time[4 + i] = read_burn_time[i];
	}

	iReCode = WriteBurnSpace( 512, (unsigned char*)write_burn_time, 32, burnType );
	CHECK_RETURN_IF_FAIL( iReCode );

	return iReCode;
}
unsigned int CChip310Imp::EraseBurnSpace( unsigned int addr, unsigned int len )
{
	unsigned int iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_FLASH_ERASE, addr&0xffff, len, len/32 );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 30 );
	CHECK_RETURN_IF_FAIL( iReCode );

	return iReCode;
}

unsigned int CChip310Imp::SetClkInFctMode( unsigned short clk, unsigned char filterOff )
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
unsigned int CChip310Imp::GetDifferMax(unsigned short frames, short* sData, unsigned short len )
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
unsigned int CChip310Imp::GetCurrent310( short (&level)[2][3], unsigned short* activeCurrrent, unsigned short* sleepCurrent, unsigned short* deepCurrent, unsigned short* vbactiveCurrrent, unsigned short* vbsleepCurrent, unsigned short* vbdeepCurrent )
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

unsigned int CChip310Imp::GetNewBootCheckSum(unsigned int* checkSum, unsigned int* omTime, unsigned int* bootloadercheckSum)
{
    unsigned char iReCode = ERROR_CODE_OK;
    ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
    if( !pComBase )  return ERROR_CODE_COMM_ERROR;

    ctp_cmd_std_t wr;
    ctp_rsp_std_t rd;

    m_ProtocalApi->PrepareIoDataToSend( wr, CMD_FW_SUM, 0, 0, 0 );
    iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
    CHECK_RETURN_IF_FAIL( iReCode );

    unsigned char readBuffer[12] = {0};
    iReCode = ReadCoreSpace( DUT_RD_BUFF_ADDR, readBuffer, 12 );
    CHECK_RETURN_IF_FAIL( iReCode );

    unsigned int* intPointer = (unsigned int*)readBuffer;

    *checkSum = intPointer[0];
    *omTime   = intPointer[1];
    * bootloadercheckSum = intPointer[2];

    return iReCode;

}

unsigned int CChip310Imp::GetTouchPoint(unsigned char* pointBuffer, unsigned short* len)
{
	unsigned int iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;
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

unsigned int CChip310Imp::GetRawData(short* rawdataBuffer, unsigned short len)
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

	return iReCode;
}

unsigned int CChip310Imp::ReadBurnSpace(unsigned int addr, unsigned char* buffer, unsigned int len)
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
		iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
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

unsigned int CChip310Imp::WriteBurnSpace(unsigned int addr, const unsigned char* buffer, unsigned int len, unsigned char type)
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
		iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd ,30);//20
		CHECK_RETURN_IF_FAIL( iReCode );

		addr += onceLen;
		buffer += onceLen;
		left -= onceLen;
	}

	return iReCode;
}

unsigned int CChip310Imp::GetTempData( unsigned short* location1, unsigned short* location2, unsigned short* location3, unsigned short* location4)
{
	unsigned int iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_ENTER_UPGRADE_MODE, 1,2 ,3 ,4 );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
	CHECK_RETURN_IF_FAIL( iReCode );

	*location1 = rd.mcap.d0;
	*location2 = rd.mcap.d1;
	*location3 = rd.mcap.d2;
	*location4 = rd.mcap.d3;

	return iReCode;
}

unsigned int CChip310Imp::GetPixelDefectData(signed short* sData0,signed short* sData1, signed short* sData2, unsigned short len)
{
	unsigned int iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_SHORT_TST, len * 2 );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
	CHECK_RETURN_IF_FAIL( iReCode );

	SysDelay(30);
	iReCode = GetRawData(sData0,len * 2);
	CHECK_RETURN_IF_FAIL( iReCode );

	iReCode = GetRawData(sData1,len * 2);
	CHECK_RETURN_IF_FAIL( iReCode );

	iReCode = GetRawData(sData2,len * 2);
	CHECK_RETURN_IF_FAIL( iReCode );

	return iReCode;
}

unsigned int CChip310Imp::GetFlyTimeData(signed short* sData, unsigned short len)
{
	unsigned int iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_FSD_TST, len );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
	CHECK_RETURN_IF_FAIL( iReCode );

	SysDelay(2500);
	iReCode = GetRawData(sData, len);
	CHECK_RETURN_IF_FAIL( iReCode );


	return iReCode;
}

unsigned int CChip310Imp::GetSRFData(signed short* sData, unsigned short len)
{
	unsigned int iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_JUMP_RAMCODE, len );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
	CHECK_RETURN_IF_FAIL( iReCode );

	SysDelay(8000);
	iReCode = GetRawData(sData, len);
	CHECK_RETURN_IF_FAIL( iReCode );


	return iReCode;
}

unsigned int CChip310Imp::GetADCData(signed short* sData, unsigned short len, unsigned char mode)
{
	unsigned int iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_RAM_TST, len , mode );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
	CHECK_RETURN_IF_FAIL( iReCode );

	SysDelay(30);
	iReCode = GetRawData(sData, len);
	CHECK_RETURN_IF_FAIL( iReCode );


	return iReCode;
}

unsigned int CChip310Imp::GetOTPStatus(unsigned int* ate_flag, unsigned int* fct_flag)
{
	unsigned int iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_FW_SUM, 0 , 0 );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
	CHECK_RETURN_IF_FAIL( iReCode );

	*ate_flag =(unsigned int) rd.mcap.d0;
	*fct_flag =(unsigned int) rd.mcap.d1;

	return iReCode;
}


