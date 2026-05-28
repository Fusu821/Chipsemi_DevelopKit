#include "Chip3536.h"
#include "checksum.h"

REGIST_RUNTIME_CLASS( CHIP_TYPE, (CHIP_TYPE)SEMI_IC_3536, CChip3536 )

typedef CChip3536  CChip6440;
REGIST_RUNTIME_CLASS(CHIP_TYPE, (CHIP_TYPE)SEMI_IC_6440, CChip6440)
typedef CChip3536  CChip6448;
REGIST_RUNTIME_CLASS(CHIP_TYPE, (CHIP_TYPE)SEMI_IC_6448, CChip6448)
typedef CChip3536  CChip6413;
REGIST_RUNTIME_CLASS(CHIP_TYPE, (CHIP_TYPE)SEMI_IC_6413, CChip6413)
typedef CChip3536  CChip6417;
REGIST_RUNTIME_CLASS(CHIP_TYPE, (CHIP_TYPE)SEMI_IC_6417, CChip6417)
typedef CChip3536  CChip6540;
REGIST_RUNTIME_CLASS(CHIP_TYPE, (CHIP_TYPE)SEMI_IC_6540, CChip6540)
typedef CChip3536  CChip6545;
REGIST_RUNTIME_CLASS(CHIP_TYPE, (CHIP_TYPE)SEMI_IC_6545, CChip6545)
typedef CChip3536  CChip6410;
REGIST_RUNTIME_CLASS(CHIP_TYPE, (CHIP_TYPE)SEMI_IC_6410, CChip6410)
typedef CChip3536  CChip6430;
REGIST_RUNTIME_CLASS(CHIP_TYPE, (CHIP_TYPE)SEMI_IC_6430, CChip6430)
typedef CChip3536  CChip6448S;
REGIST_RUNTIME_CLASS(CHIP_TYPE, (CHIP_TYPE)SEMI_IC_6448S, CChip6448S)

CChip3536Imp::CChip3536Imp()
{
	m_ProtocalApi = new ProtocalScapApi();
}
CChip3536Imp::~CChip3536Imp()
{
	if( NULL != m_ProtocalApi )
	{
		delete m_ProtocalApi;
		m_ProtocalApi = NULL;
	}
}
unsigned int CChip3536Imp::SetCommContext( const CtpHalCfg& halCfg )
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

	unsigned char chipFamily = GetContainerInterface()->GetChipFamily( SEMI_IC_3536 );
	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_CHK_CFG, 0, (chipFamily << 8) | m_slaveAddr, (halCfg.speed << 8) | halCfg.protocalType );
	return pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 5 );
}
unsigned int CChip3536Imp::GetOSCTrim( unsigned short* trim, unsigned int osStd )
{
	unsigned int iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	unsigned short trim1 = 0, trim2 = 0;

	unsigned int oscTrimTick = osStd/*600000*/;

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_DUT_CLK_CALIB, oscTrimTick & 0xffff, (oscTrimTick >> 16) & 0xffff, 250 );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
	CHECK_RETURN_IF_FAIL( iReCode );

	trim1 = rd.scap.d0;

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_DUT_CLK_CALIB, oscTrimTick & 0xffff, (oscTrimTick >> 16) & 0xffff, 250 );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
	CHECK_RETURN_IF_FAIL( iReCode );

	trim2 = rd.scap.d0;

	*trim = ( trim1 + trim2 ) >> 1;

	return iReCode;
}
unsigned int CChip3536Imp::GetOSData( unsigned char integral, unsigned char scale_a, unsigned char scale_b, unsigned short osClk, unsigned short* osData, unsigned short len )
{
	unsigned int iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	unsigned int os_ab_set = integral;
	os_ab_set = ( os_ab_set << 8 ) + scale_a;
	os_ab_set = ( os_ab_set << 8 ) + scale_b;

	//m_ProtocalApi->PrepareIoDataToSend( wr, CMD_CTP_RST );
	//iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
	//CHECK_RETURN_IF_FAIL( iReCode );
	//SysDelay(50);

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_OPEN_TST, os_ab_set & 0xffff, (os_ab_set >> 16) & 0xffff, 1024, 0, osClk );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
	CHECK_RETURN_IF_FAIL( iReCode );

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_DATA_SYNC, 100, 0xc000, 0/*0xfff4*/ );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
	CHECK_RETURN_IF_FAIL( iReCode );

	LoopTicker tick( 30 );
	while( tick.TickOnce() )
	{
		unsigned char bReady = 0;
		iReCode = pComBase->ReadFromUsbMemory( MTK_DATA_RDY, &bReady, 1 );
		if( bReady )
		{
			iReCode = pComBase->ReadFromUsbMemory( MTK_FUNC_BUF, (unsigned char*)osData, len );
			CHECK_RETURN_IF_FAIL( iReCode );
			if( (0x5555 == osData[50]) && (0x6306 == osData[48]) )
			{
				break;
			}
		}
		SysDelay( 50 );
	}
	tick.CheckTickAndMark( iReCode );
	CHECK_RETURN_IF_FAIL( iReCode );

	//m_ProtocalApi->PrepareIoDataToSend( wr, CMD_CTP_RST );
	//iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );

	return iReCode;
}
unsigned int CChip3536Imp::GetFSDFastData( unsigned short fclkDiv, unsigned short integral, unsigned short* clkData, unsigned short buffersize, unsigned char fclkCnt /* = 4 */ )
{
	unsigned int iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

// 	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_CTP_RST );
// 	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
// 	CHECK_RETURN_IF_FAIL( iReCode );
// 	SysDelay(50);

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_FSD_TST, fclkDiv, fclkDiv, (integral << 8) + fclkCnt );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 50 );
	CHECK_RETURN_IF_FAIL( iReCode );

	SysDelay(500);
	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_DATA_SYNC, 98, 0xf000, 0 );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 50 );
	CHECK_RETURN_IF_FAIL( iReCode );

	LoopTicker tick( 30 );
	while( tick.TickOnce() )
	{
		unsigned char bReady = 0;
		iReCode = pComBase->ReadFromUsbMemory( MTK_DATA_RDY, &bReady, 1 );
		if( bReady )
		{
			iReCode = pComBase->ReadFromUsbMemory( MTK_FUNC_BUF, (unsigned char*)clkData, buffersize );
			CHECK_RETURN_IF_FAIL( iReCode );

			//OnLineLogApp.AppendLogMessage( GetWrapperAddr()->GetIDMark(), value_buffer_to_string<unsigned char>( (unsigned char*)clkData, buffersize ).c_str() );

			if( (0x5555 == clkData[49]) && (0x6306 == clkData[48]) )
			{
				break;
			}
		}
		
		SysDelay( 100 );
	}

	tick.CheckTickAndMark( iReCode );
	CHECK_RETURN_IF_FAIL( iReCode );

	return iReCode;
}
unsigned int CChip3536Imp::GetFSDSlowData( unsigned short sclkDiv, unsigned short integral, unsigned short* clkData, unsigned short buffersize, unsigned char sclkCnt /* = 4 */ )
{
	unsigned int iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

// 	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_CTP_RST );
// 	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
// 	SysDelay(50);

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_FSD_TST, sclkDiv, sclkDiv, (integral << 8) + sclkCnt );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 50 );
	CHECK_RETURN_IF_FAIL( iReCode );

	SysDelay(500);
	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_DATA_SYNC, 98, 0xf001, 0 );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 50 );
	CHECK_RETURN_IF_FAIL( iReCode );

	LoopTicker tick( 100 );
	while( tick.TickOnce() )
	{
		unsigned char bReady = 0;
		iReCode = pComBase->ReadFromUsbMemory( MTK_DATA_RDY, &bReady, 1 );
		if( bReady )
		{
			iReCode = pComBase->ReadFromUsbMemory( MTK_FUNC_BUF, (unsigned char*)clkData, buffersize );
			CHECK_RETURN_IF_FAIL( iReCode );
			if( (0x5555 == clkData[49]) && (0x6306 == clkData[48]) )
			{
				break;
			}
		}
		
		SysDelay( 100 );
	}

	tick.CheckTickAndMark( iReCode );
	CHECK_RETURN_IF_FAIL( iReCode );

	return iReCode;
}
unsigned int CChip3536Imp::GetBootVersion( unsigned short* bootVer )
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

	//unsigned char readBuffer[10] = {0};
	//iReCode = ReadCoreSpace( 0x8000, readBuffer, 10 );
	//CHECK_RETURN_IF_FAIL( iReCode );

	//*bootVer = ( readBuffer[5]<< 8 ) + readBuffer[4];

	unsigned char readBuffer[8] = {0};
	iReCode = ReadBurnSpace( 0x0000, readBuffer, 8 );
	CHECK_RETURN_IF_FAIL( iReCode );

	*bootVer = ( readBuffer[5]<< 8 ) + readBuffer[4];

	return iReCode;
}
unsigned int CChip3536Imp::GetBootCheckSum( unsigned int* checkSum, unsigned int* omTime )
{
	unsigned char iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_FW_SUM, 0x1313, 0, 0 );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
	CHECK_RETURN_IF_FAIL( iReCode );

	unsigned char readBuffer[8] = {0};
	iReCode = ReadCoreSpace( 0x9000, readBuffer, 8 );
	CHECK_RETURN_IF_FAIL( iReCode );

	unsigned int* intPointer = (unsigned int*)readBuffer;
	
	*checkSum = intPointer[0];
	*omTime   = intPointer[1];

	return iReCode;
}
unsigned int CChip3536Imp::GetFirmWareConfig( unsigned char* configBuffer, unsigned short len )
{
	unsigned char iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	iReCode = ReadBurnSpace( 0x8000, configBuffer, len );
	CHECK_RETURN_IF_FAIL( iReCode );

	return iReCode;
}
unsigned int CChip3536Imp::BurnBootBin( unsigned int bootLen, unsigned int bootSVN/* = 0*/, unsigned short oscTrim /*= 0*/ )
{
	unsigned char iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;
	
	//fixedBootLen = bootLen + checksum
	//bootLen | checksum | time | svn
	const unsigned short fixedBootLen = (unsigned short)bootLen;
	unsigned char burnType = OTP_W_CHK | TLK_DATACHK_EX1;

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_MTK_MEM_MOVE, 0, fixedBootLen, 0x0d, TLK_DUT_FLASH );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 50 );
	CHECK_RETURN_IF_FAIL( iReCode );

	unsigned char mark = 0x4b;
	iReCode = WriteBurnSpace( 0x08, &mark, 1, burnType );
	CHECK_RETURN_IF_FAIL( iReCode );

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

	if(oscTrim > 0)
	{
		unsigned short osc =  ( ~oscTrim ) & 0xff;
		osc = ( osc << 8 ) + oscTrim;
		iReCode = WriteBurnSpace( 0xe000, (unsigned char*)&osc, 2, burnType );
		CHECK_RETURN_IF_FAIL( iReCode );
	}

	return iReCode;
}
unsigned int CChip3536Imp::BurnConfigBin( const unsigned char* config, unsigned short len )
{
	unsigned int iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	unsigned char burnType = OTP_W_CHK | TLK_DATACHK_EX1;

	iReCode = WriteBurnSpace( 0x8000, config, len, burnType );
	CHECK_RETURN_IF_FAIL( iReCode );

	iReCode = WriteBurnSpace( 0xf000, config, len, burnType );
	CHECK_RETURN_IF_FAIL( iReCode );

	return iReCode;
}
unsigned int CChip3536Imp::EraseBurnSpace( unsigned int addr, unsigned int len )
{
	unsigned int iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_FLASH_ERASE, addr / 4096, (len + 0x0fff) / 4096, 4096 );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 50 );
	CHECK_RETURN_IF_FAIL( iReCode );

	return iReCode;
}
unsigned int CChip3536Imp::SetClkInFctMode( unsigned short clkDiv, unsigned char filterOff )
{
	unsigned char iReCode = ERROR_CODE_OK;

	unsigned short cfgBuffer[MAX_CFG_BIN_SIZE] = {0};
	iReCode = ReadCoreSpace( 0x9E00, (unsigned char*)cfgBuffer, 204 );
	CHECK_RETURN_IF_FAIL( iReCode );

	unsigned short check = caculate_check_sum_u16( cfgBuffer, 204 );
	if( check )  iReCode = ERROR_CODE_CHECK_SUM_MISMATCH;
	CHECK_RETURN_IF_FAIL( iReCode );

	cfgBuffer[2]  = clkDiv;
	cfgBuffer[59] = ( cfgBuffer[59] & 0xff ) + ( ( cfgBuffer[59] >> 1 ) & 0xff00 );

	//////////////////////////////////////////////////////////////////////////
	//filter off
	if(filterOff)
	{
		cfgBuffer[57] &= 0xf7ff;
		cfgBuffer[59] &= 0x00ff;
		cfgBuffer[60] &= 0xfffE; 
	}

	unsigned short check16 = Sum( cfgBuffer, 101 );
	cfgBuffer[101] = 1 + (~check16);

	check = caculate_check_sum_u16( cfgBuffer, 204 );
	if( check )  iReCode = ERROR_CODE_CHECK_SUM_MISMATCH;
	CHECK_RETURN_IF_FAIL( iReCode );

	unsigned int cmd1[2] = { 0x35366798, 0x0c350055 };
	iReCode = WriteCoreSpace( 0x9f00, (unsigned char*)cmd1, 8 );
	CHECK_RETURN_IF_FAIL( iReCode );

	SysDelay( 300 );

	memset( cmd1, 0, sizeof(cmd1) );
	iReCode = ReadCoreSpace( 0x9f04, (unsigned char*)cmd1, 4 );
	CHECK_RETURN_IF_FAIL( iReCode );

	if( 0x0c300055 != cmd1[0] )
	{
		iReCode = ERROR_CODE_CHECK_RESPONSE_FAILED;
		CHECK_RETURN_IF_FAIL( iReCode );
	}

	iReCode = WriteCoreSpace( 0x9e00, (unsigned char*)cfgBuffer, 204 );
	CHECK_RETURN_IF_FAIL( iReCode );

	unsigned int cmd2[2] = { 0x35366798, 0xb73500aa };
	iReCode = WriteCoreSpace( 0x9f00, (unsigned char*)cmd2, 8 );
	CHECK_RETURN_IF_FAIL( iReCode );

	SysDelay( 100 );

	iReCode = ReadCoreSpace( 0x9f04, (unsigned char*)cmd2, 4 );
	CHECK_RETURN_IF_FAIL( iReCode );

	if( 0xb73000aa != cmd2[0] )
	{
		iReCode = ERROR_CODE_CHECK_RESPONSE_FAILED;
		CHECK_RETURN_IF_FAIL( iReCode );
	}

	return iReCode;
}
unsigned int CChip3536Imp::GetVirtualTouchData( unsigned short xyClk, unsigned short scale, unsigned short integral, unsigned short* vtData1, unsigned short* vtData2, unsigned short len )
{
	unsigned char iReCode = ERROR_CODE_OK;
	unsigned short fbRegister = 0;
	const int maxTry = 50;
	unsigned int iRawData1[MAX_SCAP_CHANNEL] = {0}, iRawData2[MAX_SCAP_CHANNEL] = {0};
	unsigned char vtData[128] = {0};

	iReCode = IncokeCommand( CMD_CTP_RST );
	SysDelay( 50 );

	iReCode = WriteCoreSpace( 0x202, (unsigned char*)&xyClk, sizeof(unsigned short) );
	CHECK_RETURN_IF_FAIL( iReCode );

	iReCode = WriteCoreSpace( 0x204, (unsigned char*)&integral, sizeof(unsigned short) );
	CHECK_RETURN_IF_FAIL( iReCode );

	iReCode = WriteCoreSpace( 0x40c, (unsigned char*)&scale, sizeof(unsigned short) );
	CHECK_RETURN_IF_FAIL( iReCode );

	iReCode = SwitchMode( MODE_RAWDATA, len );
	CHECK_RETURN_IF_FAIL( iReCode );

	SysDelay( 20 );

	for( int iRetry = 0; iRetry < maxTry; iRetry++ )
	{
		iReCode = GetRawData( (short*)vtData, len );
		CHECK_RETURN_IF_FAIL( iReCode );

		for( int index = 0; index < (len >> 1); index++ )
			iRawData1[index] += vtData[index];

		SysDelay( 10 );
	}

	//tb on
	iReCode = ReadCoreSpace( 0x409, (unsigned char*)&fbRegister, sizeof(unsigned short) );
	CHECK_RETURN_IF_FAIL( iReCode );

	fbRegister |= 0x02;
	iReCode = WriteCoreSpace( 0x409, (unsigned char*)&fbRegister, sizeof(unsigned short) );
	CHECK_RETURN_IF_FAIL( iReCode );

	iReCode = SwitchMode( MODE_RAWDATA, len );
	CHECK_RETURN_IF_FAIL( iReCode );

	SysDelay( 20 );

	for( int iRetry = 0; iRetry < maxTry; iRetry++ )
	{
		iReCode = GetRawData( (short*)vtData, len );
		CHECK_RETURN_IF_FAIL( iReCode );

		for( int index = 0; index < (len >> 1); index++ )
			iRawData2[index] += vtData[index];

		SysDelay( 10 );
	}

	//for( int index = 0; index < (len >> 1); index++ )
	//	vtData[index] = ( (short)(iRawData1[index] - iRawData2[index]) ) / (maxTry << 2);

	for( int index = 0; index < (len >> 1); index++ )
	{
		vtData1[index] = iRawData1[index] / (maxTry << 2);
		vtData2[index] = iRawData2[index] / (maxTry << 2);
	}

	return iReCode;
}
unsigned int CChip3536Imp::GetIoVoltage( unsigned int (&voltage)[2][8] )
{
	unsigned char iReCode = ERROR_CODE_OK;

	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_IOVOLTAGE_TST );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 30 );
	CHECK_RETURN_IF_FAIL( iReCode );

	//iReCode = ReadCoreSpace( 0x20000000, (unsigned char*)voltage, sizeof(voltage) );

	iReCode = pComBase->ReadFromUsbMemory( GetTxRxBufferAddr(), (unsigned char*)voltage, sizeof(voltage) );

	return iReCode;
}

unsigned int CChip3536Imp::GetTrimeDosc(int& fo_trim)
{

	unsigned int iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;



	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_CLK_TST );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
	CHECK_RETURN_IF_FAIL( iReCode );

	fo_trim = rd.scap.d0<<16|rd.scap.sn;

	return iReCode;
}
