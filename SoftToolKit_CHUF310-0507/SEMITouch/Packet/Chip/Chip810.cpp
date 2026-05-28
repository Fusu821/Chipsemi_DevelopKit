#include "Chip810.h"
#include "checksum.h"

REGIST_RUNTIME_CLASS( CHIP_TYPE, (CHIP_TYPE)SEMI_IC_CHGA810, CChip810 )

#define DUT_WR_BUFF_ADDR        0x20010000
#define DUT_RD_BUFF_ADDR        0x20010400

CChip810Imp::CChip810Imp()
{
	m_ProtocalApi = new ProtocalMcapApi();
}
CChip810Imp::~CChip810Imp()
{
	if( NULL != m_ProtocalApi )
	{
		delete m_ProtocalApi;
		m_ProtocalApi = NULL;
	}
}

unsigned int CChip810Imp::SwitchMode(unsigned char modeType, unsigned short len)
{
	unsigned char iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;
	if( 0 == len && MODE_TOUCH != modeType ) return ERROR_CODE_INVALID_PARAM;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	m_RawDataAddr = m_DifferAddr = m_BaseAddr = 0;

	unsigned char writeBuffer[] = {0x20, 0x00, 0x00, 0x00};
	//unsigned char readBuffer[0x34];
	//iReCode = BSPRWriteAndRead( writeBuffer, sizeof(writeBuffer), readBuffer, sizeof(readBuffer) );
	//iReCode = ReadCoreSpace( 0x20000000, readBuffer, sizeof(readBuffer) );

	//m_RawDataAddr = 0x20000000 + ( (unsigned int)(readBuffer[0x21] << 8) + readBuffer[0x20] );
	//m_DifferAddr  = 0x20000000 + ( (unsigned int)(readBuffer[0x23] << 8) + readBuffer[0x22] );
	//m_BaseAddr    = 0x20000000 + ( (unsigned int)(readBuffer[0x25] << 8) + readBuffer[0x24] );

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
	else if( MODE_SIMULATE_RAW == modeType )
	{
		m_ProtocalApi->PrepareIoDataToSend( wr, CMD_DATA_SYNC, m_RawDataAddr, len, 0 );
		iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd , 5 );
		CHECK_RETURN_IF_FAIL( iReCode );
	}
	else if( MODE_SIMULATE_DIFF == modeType )
	{
		m_ProtocalApi->PrepareIoDataToSend( wr, CMD_DATA_SYNC, m_DifferAddr, len, 0 );
		iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd , 5 );
		CHECK_RETURN_IF_FAIL( iReCode );
	}	
	else if( MODE_810ANALOG_RAW == modeType )
	{
		m_ProtocalApi->PrepareIoDataToSend( wr, CMD_DATA_SYNC, m_DifferAddr, len, MODE_810ANALOG_RAW );
		iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 5  );
		CHECK_RETURN_IF_FAIL( iReCode );
	}
	else if( MODE_810ANALOG_TOUCH == modeType )
	{
		m_ProtocalApi->PrepareIoDataToSend( wr, CMD_DATA_SYNC, 0x20000000 + 0x2c, 84, MODE_810ANALOG_TOUCH );
		iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd , 5 );
		CHECK_RETURN_IF_FAIL( iReCode );
	}
    else if( MODE_810TWOICS_RAWDATA == modeType )
    {
        m_ProtocalApi->PrepareIoDataToSend( wr, CMD_DATA_SYNC, m_RawDataAddr, len, 2 );
        iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 5 );
        CHECK_RETURN_IF_FAIL( iReCode );
    }
    else if( MODE_810TWOICS_TOUCH == modeType )
    {
        m_ProtocalApi->PrepareIoDataToSend( wr, CMD_DATA_SYNC, 0x20000000 + 0x2c, 84, 3 );
        iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd , 5 );
        CHECK_RETURN_IF_FAIL( iReCode );
    }
	return ERROR_CODE_OK;

}

unsigned int CChip810Imp::SetCommContext( const CtpHalCfg& halCfg )
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
unsigned int CChip810Imp::GetOSCTrim( unsigned char* trim32k, unsigned char* trim96m, unsigned char* trim250m, unsigned char trim_mode, unsigned int osStd32k, unsigned int osStd96m, unsigned int osStd250m )
{
	unsigned int iReCode = ERROR_CODE_OK;
	unsigned int *ptrim32k = (unsigned int *)trim32k;
	unsigned int *ptrim96m = (unsigned int *)trim96m;
	unsigned int *ptrim250m = (unsigned int *)trim250m;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	unsigned short trim1 = 0, trim2 = 0;

	//unsigned int oscTrimTick = osStd/*600000*/;

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_DUT_CLK_CALIB, osStd250m>>16, osStd250m&0xffff, osStd96m>>16, osStd96m&0xffff, osStd32k>>16, osStd32k&0xffff );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 5 );
	CHECK_RETURN_IF_FAIL( iReCode );

    *ptrim32k = rd.mcap.d3 & 0xff;
    *ptrim96m = rd.mcap.d2  & 0x1ff;
    *ptrim250m = rd.mcap.d1  & 0xff;

	return iReCode;
}
unsigned int  CChip810Imp:: RockerCalibR( unsigned short offset1, unsigned short offset2, unsigned short offset3,  unsigned short offset4, unsigned short csum_ref1, unsigned short csum_ref2, unsigned char* cfg, unsigned short len)
{
	unsigned int iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	unsigned short trim1 = 0, trim2 = 0;

	iReCode = pComBase->WriteToUsbMemory( pComBase->GET_MTK_TXRX_BUF_MCAP(), (unsigned char*)cfg, len );
	CHECK_RETURN_IF_FAIL( iReCode );

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_ROCKER_CALIB, offset1, offset2, offset3, offset4, csum_ref1, csum_ref2);
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd , 5 );
	CHECK_RETURN_IF_FAIL( iReCode );

	return iReCode;
}
unsigned int CChip810Imp::GetShortData( unsigned short* sData, unsigned short len )
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
unsigned int CChip810Imp::GetBootVersion( unsigned short* bootVer )
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
unsigned int CChip810Imp::GetBootCheckSum( unsigned int* checkSum, unsigned int* omTime )
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
unsigned int CChip810Imp::GetFirmWareConfig( unsigned char* configBuffer, unsigned short len )
{
	unsigned char iReCode = ERROR_CODE_OK;
	
	iReCode = ReadBurnSpace( 0x40, configBuffer, len );
	CHECK_RETURN_IF_FAIL( iReCode );

	return iReCode;
}
unsigned int CChip810Imp::BurnBootBin( unsigned int bootLen, unsigned int bootSVN/* = 0*/, unsigned short oscTrim /*= 0*/ )
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

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_MTK_MEM_MOVE, 0, fixedBootLen, (fixedBootLen >> 16), TLK_DUT_FLASH );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
	CHECK_RETURN_IF_FAIL( iReCode );

	//unsigned int dut_id = 0;
	//iReCode = ReadBurnSpace( fixedBootLen, (unsigned char*)&dut_id, 4 );
	//CHECK_RETURN_IF_FAIL( iReCode );

	//if( 0xffffffff == dut_id )
	//{
	//	SYSTEMTIME SysTime;
	//	::GetLocalTime(&SysTime);
	//	dut_id = (SysTime.wMonth << 22) + (SysTime.wDay << 17) + (SysTime.wHour << 12) + (SysTime.wMinute << 6) + SysTime.wSecond;

	//	iReCode = WriteBurnSpace( fixedBootLen, (unsigned char*)&dut_id, 4, burnType );
	//	CHECK_RETURN_IF_FAIL( iReCode );
	//}

	//if( bootSVN > 0 )
	//{
	//	unsigned int svn = 0;
	//	iReCode = ReadBurnSpace( fixedBootLen + 4, (unsigned char*)&svn, 4 );
	//	if( 0xffffffff == svn )
	//	{
	//		iReCode = WriteBurnSpace( fixedBootLen + 4, (unsigned char*)&bootSVN, 4, burnType );
	//		CHECK_RETURN_IF_FAIL( iReCode );
	//	}
	//}

	return iReCode;
}
unsigned int CChip810Imp::BurnConfigBin( const unsigned char* config, unsigned short len )
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
unsigned int CChip810Imp::EraseBurnSpace( unsigned int addr, unsigned int len )
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
// unsigned int CChip810Imp::GetIoVoltage( unsigned int (&voltage)[2][8] )
// {
// 	unsigned char iReCode = ERROR_CODE_OK;
// 
// 	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
// 	if( !pComBase )  return ERROR_CODE_COMM_ERROR;
// 
// 	iReCode = IncokeCommand( CMD_IOVOLTAGE_TST );
// 	CHECK_RETURN_IF_FAIL( iReCode );
// 
// 	//iReCode = ReadCoreSpace( 0x20000000, (unsigned char*)voltage, sizeof(voltage) );
// 
// 	iReCode = pComBase->ReadFromUsbMemory( GetTxRxBufferAddr(), (unsigned char*)voltage, sizeof(voltage) );
// 
// 	return iReCode;
// }
// unsigned int CChip810Imp::GetCurrent( unsigned short* activeCurrrent, unsigned short* sleepCurrent, unsigned short* deepCurrent )
// {
// 	unsigned int iReCode = ERROR_CODE_OK;
// 	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
// 	if( !pComBase )  return ERROR_CODE_COMM_ERROR;
// 
// 	ctp_cmd_std_t wr;
// 	ctp_rsp_std_t rd;
// 
// 	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_MTK_TEST_PINS_LEAK );
// 	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
// 	CHECK_RETURN_IF_FAIL( iReCode );
// 
// 	*activeCurrrent = rd.mcap.d0;
// 	*sleepCurrent = rd.mcap.d1;
// 	*deepCurrent = rd.mcap.d2;
// 
// 	return iReCode;
// }
unsigned int CChip810Imp::SetClkInFctMode( unsigned short clk, unsigned char filterOff )
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
unsigned int CChip810Imp::GetDifferMax(unsigned short frames, short* sData, unsigned short len )
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
unsigned int CChip810Imp::GetCurrent810( short (&level)[2][3], unsigned short* activeCurrrent, unsigned short* sleepCurrent, unsigned short* deepCurrent, unsigned short* vbactiveCurrrent, unsigned short* vbsleepCurrent, unsigned short* vbdeepCurrent )
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

unsigned int CChip810Imp::GetTouchPoint(unsigned char* pointBuffer, unsigned short* len)
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

unsigned int CChip810Imp::GetRawData(short* rawdataBuffer, unsigned short len)
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

unsigned int CChip810Imp::ReadBurnSpace(unsigned int addr, unsigned char* buffer, unsigned int len)
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

unsigned int CChip810Imp::WriteBurnSpace(unsigned int addr, const unsigned char* buffer, unsigned int len, unsigned char type)
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
		iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );//20
		CHECK_RETURN_IF_FAIL( iReCode );

		addr += onceLen;
		buffer += onceLen;
		left -= onceLen;
	}

	return iReCode;
}

