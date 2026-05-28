#include "Chip5562.h"
#include "checksum.h"

REGIST_RUNTIME_CLASS( CHIP_TYPE, (CHIP_TYPE)SEMI_IC_5562, CChip5562 )

typedef CChip5562 CChip5460S;
REGIST_RUNTIME_CLASS(CHIP_TYPE, (CHIP_TYPE)SEMI_IC_5460S, CChip5460S)

typedef CChip5562 CChip5560;
REGIST_RUNTIME_CLASS(CHIP_TYPE, (CHIP_TYPE)SEMI_IC_5560, CChip5560)
typedef CChip5562 CChip7562;
REGIST_RUNTIME_CLASS(CHIP_TYPE, (CHIP_TYPE)SEMI_IC_7562, CChip7562)

#define DUT_WR_BUFF_ADDR        0x20010000
#define DUT_RD_BUFF_ADDR        0x20010400

CChip5562Imp::CChip5562Imp()
{
	m_ProtocalApi = new ProtocalMcapApi();
}
CChip5562Imp::~CChip5562Imp()
{
	if( NULL != m_ProtocalApi )
	{
		delete m_ProtocalApi;
		m_ProtocalApi = NULL;
	}
}
unsigned int CChip5562Imp::SetCommContext( const CtpHalCfg& halCfg )
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
unsigned int CChip5562Imp::GetOSCTrim( unsigned char* trim32k, unsigned char* trim96m, unsigned char* trim250m, unsigned char trim_mode, unsigned int osStd32k, unsigned int osStd96m, unsigned int osStd250m )
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
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 70 );
	CHECK_RETURN_IF_FAIL( iReCode );

    *ptrim32k = rd.mcap.d3 & 0xff;
    *ptrim96m = rd.mcap.d2  & 0x1ff;
    *ptrim250m = rd.mcap.d1  & 0xff;

	return iReCode;
}
unsigned int  CChip5562Imp:: GetOSCTrimN( unsigned char* trim32k, unsigned char* trim96m, unsigned char* trim250m, unsigned char trim_mode, unsigned int osStd32k, unsigned int osStd96m, unsigned int osStd250m,unsigned int osStd96mNo2,unsigned int osStd96mNo3,unsigned int osStd96mNo4,unsigned int osStd96mNo5 )
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

	unsigned char sData[16];
	memcpy(sData,&osStd96mNo2,4);
	memcpy(sData+4,&osStd96mNo3,4);
	memcpy(sData+8,&osStd96mNo4,4);
	memcpy(sData+12,&osStd96mNo5,4);
	//unsigned int oscTrimTick = osStd/*600000*/;

	iReCode = pComBase->WriteToUsbMemory( pComBase->GET_MTK_TXRX_BUF_MCAP(), (unsigned char*)sData, 16 );
	CHECK_RETURN_IF_FAIL( iReCode );

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_DUT_CLK_CALIB, osStd250m>>16, osStd250m&0xffff, osStd96m>>16, osStd96m&0xffff, osStd32k>>16, osStd32k&0xffff );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
	CHECK_RETURN_IF_FAIL( iReCode );

	*ptrim32k = rd.mcap.d3 & 0xff;
	*ptrim96m = rd.mcap.d2  & 0x1ff;
	*ptrim250m = rd.mcap.d1  & 0xff;

	return iReCode;
}
unsigned int CChip5562Imp::GetShortData( unsigned short* sData, unsigned short len )
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
unsigned int CChip5562Imp::GetBootVersion( unsigned short* bootVer )
{
	unsigned char iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	unsigned char readBuffer[4] = {0};

	int flag = 0;
	iReCode = ReadBurnSpace( 0x0030, (unsigned char*)&flag, 4 );
	CHECK_RETURN_IF_FAIL( iReCode );

	if((flag & 0xffff0000) == 0x62740000)
	{
		iReCode = ReadBurnSpace( 0x003c + 0x2000, readBuffer, 4 );
		CHECK_RETURN_IF_FAIL( iReCode );
	}
	else
	{
		iReCode = ReadBurnSpace( 0x003c, readBuffer, 4 );
		CHECK_RETURN_IF_FAIL( iReCode );
	}

	*bootVer = ( readBuffer[3] << 8 ) + readBuffer[2];

	return iReCode;
}
unsigned int CChip5562Imp::GetBootCheckSum( unsigned int* checkSum, unsigned int* omTime )
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
unsigned int CChip5562Imp::GetFirmWareConfig( unsigned char* configBuffer, unsigned short len )
{
	unsigned char iReCode = ERROR_CODE_OK;
	
	iReCode = ReadBurnSpace( 0x32000, configBuffer, len );
	CHECK_RETURN_IF_FAIL( iReCode );

	return iReCode;
}
unsigned int CChip5562Imp::BurnBootBin( unsigned int bootLen, unsigned int bootSVN/* = 0*/, unsigned short oscTrim /*= 0*/ )
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

	//m_ProtocalApi->PrepareIoDataToSend( wr, CMD_MTK_MEM_MOVE, 0, fixedBootLen, ((fixedBootLen >> 16) << 1) | 0x0d, TLK_DUT_FLASH );
	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_MTK_MEM_MOVE, 0, fixedBootLen, (fixedBootLen >> 16) , TLK_DUT_FLASH );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 90 );
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
unsigned int CChip5562Imp::BurnConfigBin( const unsigned char* config, unsigned short len )
{
	unsigned int iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	unsigned char burnType = OTP_W_CHK | TLK_DATACHK_EX1;

	iReCode = WriteBurnSpace( 0x32000, config, len, burnType );
	CHECK_RETURN_IF_FAIL( iReCode );

	//iReCode = WriteBurnSpace( 220*1024, config, len, burnType );
	//CHECK_RETURN_IF_FAIL( iReCode );

	return iReCode;
}
unsigned int CChip5562Imp::EraseBurnSpace( unsigned int addr, unsigned int len )
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
// unsigned int CChip5562Imp::GetIoVoltage( unsigned int (&voltage)[2][8] )
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
// unsigned int CChip5562Imp::GetCurrent( unsigned short* activeCurrrent, unsigned short* sleepCurrent, unsigned short* deepCurrent )
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
unsigned int CChip5562Imp::SetClkInFctMode( unsigned short clk, unsigned char filterOff )
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
unsigned int CChip5562Imp::GetDifferMax(unsigned short frames, short* sData, unsigned short len )
{
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;

	//ctp_cmd_std_t wr;
	//ctp_rsp_std_t rd;

	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	//m_ProtocalApi->PrepareIoDataToSend( wr, CMD_CTP_SSCAN, 0);
	//iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 50 );
	//CHECK_RETURN_IF_FAIL( iReCode );

	iReCode = ReadCoreSpace( m_RawDataAddr, (unsigned char*)sData, len );
	CHECK_RETURN_IF_FAIL( iReCode );

	//m_ProtocalApi->PrepareIoDataToSend( wr, CMD_CTP_SSCAN, 1 );
	//iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 50 );

	return iReCode;
}
unsigned int CChip5562Imp::GetCurrent55xx( short (&level)[2][3], unsigned short* activeCurrrent, unsigned short* sleepCurrent, unsigned short* deepCurrent, unsigned short* vbactiveCurrrent, unsigned short* vbsleepCurrent, unsigned short* vbdeepCurrent )
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

unsigned int CChip5562Imp::GetNewBootCheckSum(unsigned int* checkSum, unsigned int* omTime, unsigned int* bootloadercheckSum)
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

unsigned int CChip5562Imp::CheckCatchBootToMtk(unsigned int addr, unsigned char* bootBuffer, unsigned int bootLen, LPCheckCatchBootCallBack onBootCallBack/* = NULL */)
{
	BOOL bBootSame = FALSE;
	unsigned int iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	//unsigned short bulkLen =  1024;
	unsigned char* bootCopy = bootBuffer;

	iReCode = CheckCatchBootFromMtk( pComBase->GET_MTK_FLASHBOOT_1KCHK(), bootCopy, bootLen, 1024, bBootSame );
	CHECK_RETURN_IF_FAIL( iReCode );

	if( !bBootSame )
	{
		int device = GetWrapperAddr()->GetIDMark();
		m_ProtocalApi->PrepareIoDataToSend( wr, CMD_MTK_FBOOT_CHK, 0, bootLen, (bootLen >> 16) );
		iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
		CHECK_RETURN_IF_FAIL( iReCode );

		if( NULL != onBootCallBack ) (*onBootCallBack)( device, 0, 0, _T("compare boot checksum...\r\n") );

		iReCode = CheckCatchBootFromMtk( pComBase->GET_MTK_FLASHBOOT_1KCHK(), bootCopy, bootLen, 1024, bBootSame );
		CHECK_RETURN_IF_FAIL( iReCode );

		//wasim
		//bBootSame = FALSE;

		if( bBootSame )
		{
			if( NULL != onBootCallBack ) (*onBootCallBack)( device, 0, 0, _T("boot checksum match...\r\n") );
		}
		else
		{
			if( NULL != onBootCallBack ) (*onBootCallBack)( device, 0, 0, _T("checksum mismatch, erase flash...\r\n") );

			//erase flash
			unsigned short block_n = ( bootLen + 4095 ) >> 12;
			m_ProtocalApi->PrepareIoDataToSend( wr, CMD_MTK_FLASH_ERASE, addr >> 12, block_n );
			iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd,300 );
			CHECK_RETURN_IF_FAIL( iReCode );

			if( NULL != onBootCallBack ) (*onBootCallBack)( device, 0, 0, _T("checksum mismatch, start write to mtk flash...\r\n") );
			//write flash to mtk
			int left = bootLen;
			bootCopy = bootBuffer;
			while( left > 0 )
			{
				int onceWrite = left > 1024 ? 1024 : left;
				iReCode = WriteFlashData( bootCopy, addr, onceWrite );
				CHECK_RETURN_IF_FAIL( iReCode );

				left -= onceWrite;
				addr += onceWrite;
				bootCopy += onceWrite;

				if( NULL != onBootCallBack ) (*onBootCallBack)( device, bootLen - left, bootLen, _T("copy data to mtk flash...\r\n") );
			}

			if( NULL != onBootCallBack ) (*onBootCallBack)( device, bootLen - left, bootLen, _T("move boot to mtk flash complete...\r\n") );
		}

		m_ProtocalApi->PrepareIoDataToSend( wr, CMD_MTK_FBOOT_CHK, 0, bootLen, (bootLen >> 16));
		iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
		CHECK_RETURN_IF_FAIL( iReCode );
	}


	return iReCode;
}

unsigned int CChip5562Imp::GetTrimeDosc(fct_osc_trim& fo_trim)
{
	unsigned char iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_CLK_TST);
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 70);
	CHECK_RETURN_IF_FAIL( iReCode );

	iReCode = pComBase->ReadFromUsbMemory( GetTxRxBufferAddr(), (unsigned char*)&fo_trim, sizeof(fct_osc_trim) );
	CHECK_RETURN_IF_FAIL( iReCode );

	return iReCode;

}

unsigned int CChip5562Imp::GetVtData(unsigned short* sData, unsigned short len)
{
	unsigned int iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_VT_TST, 0 );
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

unsigned int CChip5562Imp::GetFwData(short* sData, unsigned short len)
{
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;


	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	iReCode = ReadCoreSpace( m_RawDataAddr, (unsigned char*)sData, len );
	CHECK_RETURN_IF_FAIL( iReCode );

	return iReCode;
}


