#include "Chip7449.h"
#include "checksum.h"
//#define   Existboot
REGIST_RUNTIME_CLASS( CHIP_TYPE, (CHIP_TYPE)SEMI_IC_7449, CChip7449 )

typedef CChip7449 CChip7438;
REGIST_RUNTIME_CLASS(CHIP_TYPE, (CHIP_TYPE)SEMI_IC_7438, CChip7438)

typedef CChip7449 CChip7448;
REGIST_RUNTIME_CLASS(CHIP_TYPE, (CHIP_TYPE)SEMI_IC_7448, CChip7448)

typedef CChip7449 CChip7464;
REGIST_RUNTIME_CLASS(CHIP_TYPE, (CHIP_TYPE)SEMI_IC_7464, CChip7464)

#define DUT_WR_BUFF_ADDR        0x20008000
#define DUT_RD_BUFF_ADDR        0x20008400

CChip7449Imp::CChip7449Imp()
{
	m_ProtocalApi = new ProtocalMcapApi();
}
CChip7449Imp::~CChip7449Imp()
{
	if( NULL != m_ProtocalApi )
	{
		delete m_ProtocalApi;
		m_ProtocalApi = NULL;
	}
}
unsigned int CChip7449Imp::SetCommContext( const CtpHalCfg& halCfg )
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
unsigned int CChip7449Imp::GetOSCTrim( unsigned char* trim32k, unsigned char* trim48m, unsigned char* trim150m, unsigned char trim_mode, unsigned int osStd32k, unsigned int osStd48m, unsigned int osStd150m )
{
	unsigned int iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	unsigned short trim1 = 0, trim2 = 0;

	//unsigned int oscTrimTick = osStd/*600000*/;

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_DUT_CLK_CALIB, trim_mode, osStd150m >> 16, osStd150m & 0xffff, osStd48m >> 16, osStd48m & 0xffff, osStd32k );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
	CHECK_RETURN_IF_FAIL( iReCode );

	if( trim_mode )
	{
		if( rd.mcap.d0 & 0x01 ) *trim32k = rd.mcap.d1 & 0xff;
		if( rd.mcap.d0 & 0x02 ) *trim48m = rd.mcap.d2  & 0xff;
		if( rd.mcap.d0 & 0x08 ) *trim150m = rd.mcap.d3  & 0xff;
	}
	else
	{
		if( rd.mcap.d0 & 0x01 ) *trim32k = rd.mcap.d1 & 0xff;
		if( rd.mcap.d0 & 0x02 ) *trim48m = rd.mcap.d2 & 0xff;
		if( rd.mcap.d0 & 0x08 ) *trim150m = rd.mcap.d3 & 0xff;
	}

// 	osStd48m = rd.mcap.d2 & 0xff;
// 
// 	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_DUT_CLK_CALIB, 0, (osStd150m) & 0xffff, (osStd48m) & 0xffff, osStd32k );
// 	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
// 	CHECK_RETURN_IF_FAIL( iReCode );
// 
// 	osStd48m = rd.mcap.d2 & 0xff;
// 
// 	*trim = ( trim1 + trim2 ) >> 1;

	return iReCode;
}
unsigned int CChip7449Imp::GetShortData( unsigned short* sData, unsigned short len )
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

	unsigned int checkSum = caculate_check_sum_ex( (unsigned char*)sData, len );
	if( checkSum != ((rd.mcap.d1 << 16) + rd.mcap.d0))
		iReCode = ERROR_CODE_CHECK_SUM_MISMATCH;
	CHECK_RETURN_IF_FAIL( iReCode );

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_CTP_RST );
	pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
	SysDelay(200);
	return iReCode;
}
unsigned int CChip7449Imp::GetBootVersion( unsigned short* bootVer )
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
#ifdef Existboot
	iReCode = ReadBurnSpace( (0x003c + 0x2000), readBuffer, 4 );
#else
	iReCode = ReadBurnSpace( (0x003c), readBuffer, 4 );
#endif
	
	CHECK_RETURN_IF_FAIL( iReCode );

	*bootVer = ( readBuffer[3] << 8 ) + readBuffer[2];

	return iReCode;
}
unsigned int CChip7449Imp:: GetNewBootVersion( unsigned short* bootVer,unsigned int addr )
{
	unsigned char iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	unsigned char readBuffer[4] = {0};

	iReCode = ReadBurnSpace( (0x003c + addr), readBuffer, 4 );
	
	CHECK_RETURN_IF_FAIL( iReCode );

	*bootVer = ( readBuffer[3] << 8 ) + readBuffer[2];

	return iReCode;
}
unsigned int CChip7449Imp::GetBootCheckSum( unsigned int* checkSum, unsigned int* omTime )
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
unsigned int CChip7449Imp::GetFirmWareConfig( unsigned char* configBuffer, unsigned short len )
{
	unsigned char iReCode = ERROR_CODE_OK;
	
	iReCode = ReadBurnSpace( (200*1024) , configBuffer, len );//(0x18000 + (1024 * 8))
	CHECK_RETURN_IF_FAIL( iReCode );

	return iReCode;
}
unsigned int CChip7449Imp::BurnBootBin( unsigned int bootLen, unsigned int bootSVN/* = 0*/, unsigned short oscTrim /*= 0*/ )
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

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_MTK_MEM_MOVE, 0, fixedBootLen, ((fixedBootLen >> 16) << 1) | 0x0d, TLK_DUT_FLASH );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 120 );
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
unsigned int CChip7449Imp::BurnConfigBin( const unsigned char* config, unsigned short len )
{
	unsigned int iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	unsigned char burnType = OTP_W_CHK | TLK_DATACHK_EX1;

	iReCode = WriteBurnSpace( 200*1024 , config, len, burnType );//(0x18000 + (8 * 1024))
	CHECK_RETURN_IF_FAIL( iReCode );

	//iReCode = WriteBurnSpace( 0xf000, config, len, burnType );
	//CHECK_RETURN_IF_FAIL( iReCode );

	return iReCode;
}
unsigned int CChip7449Imp::EraseBurnSpace( unsigned int addr, unsigned int len )
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
// unsigned int CChip7449Imp::GetIoVoltage( unsigned int (&voltage)[2][8] )
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
// unsigned int CChip7449Imp::GetCurrent( unsigned short* activeCurrrent, unsigned short* sleepCurrent, unsigned short* deepCurrent )
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
unsigned int CChip7449Imp::SetClkInFctMode( unsigned short clk, unsigned char filterOff )
{
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
	unsigned char cfgBuffer[256] = {0};

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
	unsigned short checkSum = caculate_check_sum_u16((unsigned short*)cfgBuffer, sizeof(cfgBuffer) - 2);
	checkSum = 1 + ~checkSum;
	unsigned short* pCheckDest = (unsigned short*)&cfgBuffer[sizeof(cfgBuffer) - 2];
	*pCheckDest = checkSum;

	iReCode = WriteCoreSpace( 0x20000080, cfgBuffer, sizeof(cfgBuffer) );
	CHECK_RETURN_IF_FAIL( iReCode );

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_CTP_SSCAN, 1, 0x7265 );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 30 );
	CHECK_RETURN_IF_FAIL( iReCode );

	return iReCode;
}
unsigned int CChip7449Imp::GetDifferMax(unsigned short frames, short* sData, unsigned short len )
{
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_CFG_INIT, frames );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 1 );

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_CTP_SSCAN, 0, 0x0805, frames );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 80 );
	CHECK_RETURN_IF_FAIL( iReCode );

	iReCode = ReadCoreSpace( m_DifferAddr, (unsigned char*)sData, len );
	CHECK_RETURN_IF_FAIL( iReCode );

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_CTP_SSCAN, 1 );

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_CFG_INIT, 1 );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 1 );

	return iReCode;
}
