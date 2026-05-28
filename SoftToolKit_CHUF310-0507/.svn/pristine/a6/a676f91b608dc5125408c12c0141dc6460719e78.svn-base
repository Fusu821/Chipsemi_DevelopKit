#include "Chip3535.h"
#include "checksum.h"

REGIST_RUNTIME_CLASS( CHIP_TYPE, (CHIP_TYPE)SEMI_IC_3535, CChip3535 )



CChip3535Imp::CChip3535Imp()
{
	m_ProtocalApi = new ProtocalScapApi();
}
CChip3535Imp::~CChip3535Imp()
{
	if( NULL != m_ProtocalApi )
	{
		delete m_ProtocalApi;
		m_ProtocalApi = NULL;
	}
}
unsigned int CChip3535Imp::SwitchMode( unsigned char modeType, unsigned short len )
{
	unsigned char iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	if( MODE_TOUCH == modeType )
	{
		m_ProtocalApi->PrepareIoDataToSend( wr, CMD_DATA_SYNC, LEN_RAW_POINT, 0xd450 );
		iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
		CHECK_RETURN_IF_FAIL( iReCode );
	}
	else if( MODE_RAWDATA == modeType )
	{
		m_ProtocalApi->PrepareIoDataToSend( wr, CMD_DATA_SYNC, len, 0xc600 );
		iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
		CHECK_RETURN_IF_FAIL( iReCode );
	}
	else if( MODE_DIFFER == modeType )
	{
		m_ProtocalApi->PrepareIoDataToSend( wr, CMD_DATA_SYNC, len, 0xc690 );
		iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
		CHECK_RETURN_IF_FAIL( iReCode );
	}

	return iReCode;
}
unsigned int CChip3535Imp::SetCommContext( const CtpHalCfg& halCfg )
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

	unsigned char chipFamily = GetContainerInterface()->GetChipFamily( SEMI_IC_3535 );
	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_CHK_CFG, 0, (chipFamily << 8) | m_slaveAddr, (halCfg.speed << 8) | halCfg.protocalType );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 5 );
	CHECK_RETURN_IF_FAIL(iReCode);

	//m_ProtocalApi->PrepareIoDataToSend( wr, CMD_MTK_ADDID, 0, 0, 0 );
	//iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
	//CHECK_RETURN_IF_FAIL(iReCode);

	return iReCode;
}
unsigned int CChip3535Imp::GetOSCTrim( unsigned short* trim, unsigned int osStd )
{
	unsigned int iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	unsigned short trim1 = 0, trim2 = 0;

	unsigned int oscTrimTick = osStd;

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
unsigned int CChip3535Imp::GetOSData( unsigned char integral, unsigned char scale_a, unsigned char scale_b, unsigned short* osData, unsigned short len )
{
	unsigned int iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	unsigned int os_ab_set = integral;
	os_ab_set = ( os_ab_set << 8 ) + scale_a;
	os_ab_set = ( os_ab_set << 8 ) + scale_b;

	//m_ProtocalApi->PrepareIoDataToSend( wr, CMD_OPEN_TST, 0, 0, 0 );
	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_OPEN_TST, os_ab_set & 0xffff, (os_ab_set >> 16) & 0xffff, 1024 );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
	CHECK_RETURN_IF_FAIL( iReCode );

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_DATA_SYNC, 74, 0xc000, 0 );
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
			if( (0x5555 == osData[37]) && (0x6306 == osData[36]) )
			{
				break;
			}
		}
		
		SysDelay( 50 );
	}
	tick.CheckTickAndMark( iReCode );
	CHECK_RETURN_IF_FAIL( iReCode );

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_CTP_RST );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );

	return iReCode;
}
unsigned int CChip3535Imp::GetFSDFastData( unsigned short fclkDiv, unsigned short integral, unsigned short* clkData, unsigned short buffersize, unsigned char fclkCnt /* = 4 */ )
{
	unsigned int iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_CTP_RST );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
	CHECK_RETURN_IF_FAIL( iReCode );
	SysDelay(20);

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_FSD_TST, fclkDiv, fclkDiv, fclkCnt );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
	CHECK_RETURN_IF_FAIL( iReCode );

	SysDelay(500);
	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_DATA_SYNC, buffersize, 0xf000, 0 );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 50 );
	CHECK_RETURN_IF_FAIL( iReCode );

	LoopTicker tick( 30 );
	while( tick.TickOnce() )
	{
		unsigned char bReady = 0;
		iReCode = pComBase->ReadFromUsbMemory( MTK_DATA_RDY, &bReady, 1 );
		if( bReady )
		{
			iReCode = pComBase->ReadFromUsbMemory( MTK_FUNC_BUF, (unsigned char*)clkData, buffersize + 2 );
			CHECK_RETURN_IF_FAIL( iReCode );
			if( 0x5555 == clkData[buffersize >> 1] )
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
unsigned int CChip3535Imp::GetFSDSlowData( unsigned short sclkDiv, unsigned short integral, unsigned short* clkData, unsigned short buffersize, unsigned char sclkCnt /* = 4 */ )
{
	unsigned int iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_CTP_RST );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_FSD_TST, sclkDiv, sclkDiv, sclkCnt );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
	CHECK_RETURN_IF_FAIL( iReCode );

	SysDelay(500);
	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_DATA_SYNC, buffersize, 0xf001, 0 );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 50 );
	CHECK_RETURN_IF_FAIL( iReCode );

	LoopTicker tick( 30 );
	while( tick.TickOnce() )
	{
		unsigned char bReady = 0;
		iReCode = pComBase->ReadFromUsbMemory( MTK_DATA_RDY, &bReady, 1 );
		if( bReady )
		{
			iReCode = pComBase->ReadFromUsbMemory( MTK_FUNC_BUF, (unsigned char*)clkData, buffersize + 2 );
			CHECK_RETURN_IF_FAIL( iReCode );
			if( 0x5555 == clkData[buffersize >> 1] )
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
unsigned int CChip3535Imp::GetBootVersion( unsigned short* bootVer )
{
	unsigned char iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_CTP_RST );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
	CHECK_RETURN_IF_FAIL( iReCode );

	SysDelay( 50 );

	unsigned char readBuffer[10] = {0};
	iReCode = ReadCoreSpace( 0x8000, readBuffer, 10 );
	CHECK_RETURN_IF_FAIL( iReCode );

	*bootVer = ( readBuffer[5]<< 8 ) + readBuffer[4];

	return iReCode;
}
unsigned int CChip3535Imp::GetBootCheckSum( unsigned int* checkSum, unsigned int* omTime, unsigned int* marginCheck, unsigned int* normalCheck )
{
	unsigned char iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_FW_SUM, 0x1313, 0, 0 );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
	CHECK_RETURN_IF_FAIL( iReCode );

	unsigned char readBuffer[16] = {0};
	iReCode = ReadCoreSpace( MTK_FUNC_BUF, readBuffer, 16 );
	CHECK_RETURN_IF_FAIL( iReCode );

	unsigned int* intPointer = (unsigned int*)readBuffer;
	
	*checkSum = intPointer[0];
	*omTime   = intPointer[1];

	*marginCheck = intPointer[2];
	*normalCheck = intPointer[3];

	return iReCode;
}
unsigned int CChip3535Imp::GetFirmWareConfig( unsigned int addr, unsigned char* configBuffer, unsigned short len )
{
	unsigned char iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	iReCode = ReadBurnSpace( addr, configBuffer, len );
	CHECK_RETURN_IF_FAIL( iReCode );

	return iReCode;
}
unsigned int CChip3535Imp::BurnBootBin( unsigned int bootLen, unsigned int bootSVN/* = 0*/, unsigned short oscTrim /*= 0*/, unsigned char reBurn /*= 0*/ )
{
	unsigned char iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;
	
	//fixedBootLen = bootLen + checksum
	//bootLen | checksum | time | svn
	const unsigned short fixedBootLen = (unsigned short)bootLen;
	unsigned char burnType = reBurn ? ( TLK_B4WRCHK_EX | OTP_W_CHK | TLK_DATACHK_EX1) : (OTP_W_CHK | TLK_DATACHK_EX1);

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_MTK_MEM_MOVE, 0, fixedBootLen, 0x0d, burnType );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 50 );
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

	return iReCode;
}
unsigned int CChip3535Imp::BurnConfigBin( unsigned int addr, const unsigned char* config, unsigned short len )
{
	unsigned int iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	unsigned char burnType = OTP_W_CHK | TLK_DATACHK_EX1;

	iReCode = WriteBurnSpace( addr, config, len, burnType );
	CHECK_RETURN_IF_FAIL( iReCode );

	return iReCode;
}
unsigned int CChip3535Imp::SetClkInFctMode( unsigned short clkDiv, unsigned char filterOff )
{
	unsigned char iReCode = ERROR_CODE_OK;

	unsigned short cfgBuffer[MAX_CFG_BIN_SIZE] = {0};
	iReCode = ReadCoreSpace( 0xD6E0, (unsigned char*)cfgBuffer, 204 );
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

	iReCode = WriteCoreSpace( 0xD7E0, (unsigned char*)cfgBuffer, 204 );
	CHECK_RETURN_IF_FAIL( iReCode );

	unsigned int cmd2[2] = { 0x6798, 0xcd3500ff };
	iReCode = WriteCoreSpace( 0xdf10, (unsigned char*)cmd2, 8 );
	CHECK_RETURN_IF_FAIL( iReCode );

	SysDelay( 300 );

	return iReCode;
}
unsigned int CChip3535Imp::FindLastCfgAddress()
{
	unsigned int iReCode = ERROR_CODE_OK;
	unsigned int lastCfgAddr = 0x7f80 - 256;
	unsigned short markData = 0;

	while ( lastCfgAddr > 0x5000 )
	{
		iReCode = ReadBurnSpace( lastCfgAddr, (unsigned char*)&markData, 2 );
		if( iReCode != ERROR_CODE_OK )  return lastCfgAddr = 0;

		if( 0xffff == markData ) break;

		lastCfgAddr -= 256;
	}

	return lastCfgAddr + 256;
}

unsigned int CChip3535Imp::CheckOtp(unsigned short* checknum)
{
	unsigned char iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;
	m_ProtocalApi->PrepareIoDataToSend( wr, 0x2f,0,0,0,0,0,0);
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 50 );
	CHECK_RETURN_IF_FAIL( iReCode );
	if(rd.scap.cc ==0 )
	{
	   if(rd.scap.d0 == 0x80)
	   {
	     *checknum = 0x80;	//Ð´¹ýOTP
	   }
	   return 0;	//Ã»Ð´¹ý OTP	
	}
	else
	{
	   *checknum = rd.scap.d0;
	   return 1;			
	}

}