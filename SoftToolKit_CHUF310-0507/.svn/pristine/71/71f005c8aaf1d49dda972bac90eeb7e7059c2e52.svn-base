#include "Chip5816.h"
#include "checksum.h"

REGIST_RUNTIME_CLASS( CHIP_TYPE, (CHIP_TYPE)SEMI_IC_5816, CChip5816 )

typedef CChip5816 CChip1716;
REGIST_RUNTIME_CLASS(CHIP_TYPE, (CHIP_TYPE)SEMI_IC_1716, CChip1716)
// typedef CChip5816 CChip5816;
// REGIST_RUNTIME_CLASS(CHIP_TYPE, (CHIP_TYPE)SEMI_IC_5816, CChip5816)

#define DUT_WR_BUFF_ADDR        0x20002000
#define DUT_RD_BUFF_ADDR        0x20002400
#define MTP_CFG_ADDR            (39 * 1024 + 256 * 3)

CChip5816Imp::CChip5816Imp()
{
	m_ProtocalApi = new ProtocalMcapApi();
}
CChip5816Imp::~CChip5816Imp()
{
	if( NULL != m_ProtocalApi )
	{
		delete m_ProtocalApi;
		m_ProtocalApi = NULL;
	}
}
unsigned int CChip5816Imp::SetCommContext( const CtpHalCfg& halCfg )
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
unsigned int CChip5816Imp::GetOSCTrim( unsigned char* trim32k, unsigned char* trim24m, unsigned int osStd32k, unsigned int osStd24m )
{
	unsigned int iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	unsigned short trim1 = 0, trim2 = 0;

	//unsigned int oscTrimTick = osStd/*600000*/;

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_DUT_CLK_CALIB, 0, 0, 0, osStd24m >> 16, osStd24m & 0xffff, osStd32k );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
	CHECK_RETURN_IF_FAIL( iReCode );

	if( rd.mcap.d0 & 0x01 ) *trim32k = rd.mcap.d1 & 0xff;
	if( rd.mcap.d0 & 0x02 ) *trim24m = rd.mcap.d2  & 0xff;

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
unsigned int CChip5816Imp::GetShortData( unsigned short* sData, unsigned short len )
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

	return iReCode;
}
unsigned int CChip5816Imp::GetBootVersion( unsigned short* bootVer )
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

	//*bootVer = ( readBuffer[5]<< 8 ) + readBuffer[4];

	unsigned char readBuffer[4] = {0};
	iReCode = ReadBurnSpace( 0x003c, readBuffer, 4 );
	CHECK_RETURN_IF_FAIL( iReCode );

	*bootVer = ( readBuffer[3] << 8 ) + readBuffer[2];

	return iReCode;
}
unsigned int CChip5816Imp::GetBootCheckSum( unsigned int* checkSum, unsigned int* omTime )
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
unsigned int CChip5816Imp::GetFirmWareConfig( unsigned char* configBuffer, unsigned short len )
{
	unsigned char iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_CTP_RST, 0 );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
	CHECK_RETURN_IF_FAIL( iReCode );

	SysDelay( 100 );

	//iReCode = ReadBurnSpace( MTP_CFG_ADDR, configBuffer, len );
	iReCode = ReadCoreSpace( 0x20000000 + 0x80, configBuffer, len );
	CHECK_RETURN_IF_FAIL( iReCode );

	return iReCode;
}
unsigned int CChip5816Imp::BurnBootBin( unsigned int bootLen, UINT64 VidPid /* = 0 */, unsigned int oscTrim /* = 0 */, long long icID /* = 0 */ )
{
	unsigned char iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;
	
	//fixedBootLen = bootLen + checksum
	//bootLen | checksum | time | svn
	const unsigned short fixedBootLen = bootLen;
	unsigned char burnType = OTP_W_CHK | TLK_DATACHK_EX1;

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_FLASH_ERASE, 0x04 );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 100 );
	CHECK_RETURN_IF_FAIL( iReCode );

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_MTK_MEM_MOVE, 0, fixedBootLen, 0x0d, TLK_DUT_FLASH );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 50 );
	CHECK_RETURN_IF_FAIL( iReCode );

	unsigned char writeBuffer[256] = {0};
	unsigned char* oneRecord = writeBuffer;
	memset( writeBuffer, 0xff, sizeof(writeBuffer) );

	SYSTEMTIME SysTime;
	::GetLocalTime(&SysTime);
    UINT32 burnTime = (SysTime.wMonth << 22) + (SysTime.wDay << 17) + (SysTime.wHour << 12) + (SysTime.wMinute << 6) + SysTime.wSecond;

	for( int index = 0; index < 9; index++ )
	{
		*((unsigned int*)oneRecord) = oscTrim;
		*((unsigned int*)(oneRecord + 4)) = burnTime;
		*((long long*)(oneRecord + 8)) = icID;
		*((UINT64*)(oneRecord + 16)) = VidPid;
		*((unsigned int*)(oneRecord + 24)) = caculate_check_sum_ex( oneRecord, 24 );
		oneRecord += 28;
	}

	iReCode = WriteBurnSpace( 40 * 1024, writeBuffer, sizeof(writeBuffer), burnType );
	CHECK_RETURN_IF_FAIL( iReCode );

	//unsigned char mark = 0x4b;
	//iReCode = WriteBurnSpace( 0x08, &mark, 1, burnType );
	//CHECK_RETURN_IF_FAIL( iReCode );

// 	unsigned int dut_id = 0;
// 	unsigned char readBuffer[8] = {0};
// 	unsigned int* pIntData = (unsigned int*)&readBuffer[0];
// 	unsigned short* pShortData = (unsigned short*)&readBuffer[0];
// 	iReCode = ReadBurnSpace( fixedBootLen, readBuffer, 8 );
// 	CHECK_RETURN_IF_FAIL( iReCode );
// 
// 	if(0xffff != (pShortData[2] + pShortData[3]))
// 	{
// 		SYSTEMTIME SysTime;
// 		::GetLocalTime(&SysTime);
// 		pIntData[0] = (SysTime.wMonth << 22) + (SysTime.wDay << 17) + (SysTime.wHour << 12) + (SysTime.wMinute << 6) + SysTime.wSecond;
// 		pShortData[2] = rand() & 0xffff;
// 		pShortData[3] = ~pShortData[2];
// 
// 		iReCode = WriteBurnSpace( fixedBootLen, readBuffer, 8, burnType );
// 		CHECK_RETURN_IF_FAIL( iReCode );
// 	}
// 
// 	if( bootSVN > 0 )
// 	{
// 		unsigned int svn = 0;
// 		iReCode = ReadBurnSpace( fixedBootLen + 4, (unsigned char*)&svn, 4 );
// 		if( 0xffffffff == svn )
// 		{
// 			iReCode = WriteBurnSpace( fixedBootLen + 4, (unsigned char*)&bootSVN, 4, burnType );
// 			CHECK_RETURN_IF_FAIL( iReCode );
// 		}
// 	}

	//if(oscTrim > 0)
	//{
	//	unsigned short osc =  ( ~oscTrim ) & 0xff;
	//	osc = ( osc << 8 ) + oscTrim;
	//	iReCode = WriteBurnSpace( 0xe000, (unsigned char*)&osc, 2, burnType );
	//	CHECK_RETURN_IF_FAIL( iReCode );
	//}

	return iReCode;
}
unsigned int CChip5816Imp::BurnConfigBin( const unsigned char* config, unsigned short len )
{
	return ERROR_CODE_COMM_ERROR;
}
unsigned int CChip5816Imp::EraseBurnSpace( unsigned int addr, unsigned int len )
{
	unsigned int iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	unsigned char eraseType = 0x00;
	if( addr < 40 * 1024 )
	{
		eraseType |= 0x01;
	}
	else if(addr < 40 * 1024 + 256)
	{
		eraseType |= 0x02;
	}
	if( addr + len > 40 * 1024 )
	{
		eraseType |= 0x04;
	}

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_FLASH_ERASE, eraseType );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 50 );
	CHECK_RETURN_IF_FAIL( iReCode );

	return iReCode;
}
// unsigned int CChip5816Imp::GetIoVoltage( unsigned int (&voltage)[2][8] )
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
// unsigned int CChip5816Imp::GetCurrent( unsigned short* activeCurrrent, unsigned short* sleepCurrent, unsigned short* deepCurrent )
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
unsigned int CChip5816Imp::SetClkInFctMode( unsigned short clk, unsigned char filterOff )
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