#include "ChipBase.h"
#include "checksum.h"
#include "onlinelog.h"

#define SCAP_ACCESS_ADDR_SPACE  2

CChipBaseImp::CChipBaseImp()
	:m_slaveAddr(0x5c)
	,m_ProtocalApi(NULL)
{
}
CChipBaseImp::~CChipBaseImp()
{
}
LPVOID CChipBaseImp::GetSRefInterface()
{
	return dynamic_cast<RefSelf*>( this );
}
void CChipBaseImp::SetWrapperAddr( ISMChipWrapper* addr )
{
	RefSelf::SetWrapperAddr( addr );
}
unsigned int CChipBaseImp::GetTxRxBufferAddr()
{
	return 0;
}
BOOL CChipBaseImp::HaveTpLinked( unsigned int retry /*= 1*/ )
{
	unsigned char iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return FALSE;

	//不同版本的MTK板 区别对待
	unsigned int mtkVer = 0;
	iReCode = pComBase->ReadFromUsbMemory( pComBase->GET_MTK_VER_ADDR(), (unsigned char*)&mtkVer, 4 );
	BOOL bNewMtkBoard = ((mtkVer >> 16) & 0x0f) >= 8;

	unsigned char flags = 0xff;
	if( bNewMtkBoard ) pComBase->SyncWorkcInit( 0 );
	SysDelay( 30 );
	for( int index = 0; index < (int)retry; index++ )
	{
		iReCode = pComBase->ReadFromUsbMemory( 0x01, &flags, 1 );
		if( flags == m_slaveAddr ) break;

		if( ERROR_CODE_WRITE_USB_ERROR == iReCode )
		{
			SysDelay( 200 );
		}

		//IncokeCommand( CMD_CTP_RST );
		//SysDelay( 50 );
	}

	if( bNewMtkBoard ) pComBase->SyncWorkcInit( 1 );	
	SysDelay( 280 );
	if( ERROR_CODE_OK == iReCode &&( flags == m_slaveAddr||flags == 0x5c) )
		return TRUE;
	else
		return FALSE;
}
unsigned int CChipBaseImp::IncokeCommand( unsigned char command, unsigned int d0/* = 0*/, unsigned short d1 /*= 0*/, unsigned short d2 /*= 0*/, unsigned char* retBuffer /*= NULL*/ )
{
	unsigned char iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	m_ProtocalApi->PrepareIoDataToSend( wr, command, d0, d1, d2 );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 30 );
	CHECK_RETURN_IF_FAIL( iReCode );

	if( NULL != retBuffer )
	{
		memcpy_s( retBuffer, sizeof(ctp_rsp_std_t), &rd, sizeof(ctp_rsp_std_t) );
	}

	return iReCode;
}
unsigned int CChipBaseImp::GetOSCTrim( unsigned short* trim, unsigned int osStd )
{
	return ERROR_CODE_COMM_ERROR;
}
unsigned int CChipBaseImp::SetClkInFctMode( unsigned short clkDiv, unsigned char filterOff )
{
	return ERROR_CODE_COMM_ERROR;
}
unsigned int CChipBaseImp::SwitchMode( unsigned char modeType, unsigned short len )
{
	unsigned char iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;
	if( 0 == len && MODE_TOUCH != modeType ) return ERROR_CODE_INVALID_PARAM;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;
	unsigned char crcFlags = 0;

	iReCode = ReadCoreSpace( 0x000b, &crcFlags, 1 );
	if(0x00 != crcFlags)
	{
		crcFlags = 0x00;
		iReCode = WriteCoreSpace( 0x000b, &crcFlags, 1 );
	}

	if( MODE_TOUCH == modeType )
	{
		m_ProtocalApi->PrepareIoDataToSend( wr, CMD_DATA_SYNC, len, 0xfff0, 1 );
		iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
		CHECK_RETURN_IF_FAIL( iReCode );
	}
	else if( MODE_RAWDATA == modeType )
	{
		m_ProtocalApi->PrepareIoDataToSend( wr, CMD_DATA_SYNC, len, 0xfff0, 1 );
		iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
		CHECK_RETURN_IF_FAIL( iReCode );
	}
	else if( MODE_DIFFER == modeType )
	{
		m_ProtocalApi->PrepareIoDataToSend( wr, CMD_DATA_SYNC, len, 0xfff1, 1 );
		iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
		CHECK_RETURN_IF_FAIL( iReCode );
	}
	else if( MODE_BASE == modeType )
	{
		m_ProtocalApi->PrepareIoDataToSend( wr, CMD_DATA_SYNC, len, 0xfff2, 1 );
		iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
		CHECK_RETURN_IF_FAIL( iReCode );
	}

	return iReCode;
}
unsigned int CChipBaseImp::GetTouchPoint( unsigned char* pointBuffer, unsigned short* len )
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

		SysDelay( 2 );
	}
	tick.CheckTickAndMark( iReCode );
	CHECK_RETURN_IF_FAIL( iReCode );

	unsigned short report[5] = {0};

	unsigned short tcLen = 10;
	iReCode = pComBase->ReadFromUsbMemory( pComBase->GET_MTK_FUNC_BUF() + 122 - 10, (unsigned char*)report, tcLen );
	CHECK_RETURN_IF_FAIL( iReCode );

	static unsigned char uevent[2] = {0x01, 0x01};
	sm_pt_t *ppt = (sm_pt_t*)&pointBuffer[3];

	pointBuffer[0] = 0x00;
	pointBuffer[1] = 0x00;
	pointBuffer[2] = report[4] & 0x07;

	for(int index = 0; index < 2; index++)
	{
		ppt->id = 0x0f;
		ppt->event = 0x01;
		if(report[2 * index + 0] > 0 && report[2 * index + 1] > 0)
		{
			ppt->id = (report[2 * index + 0] & 0x8000) >> 15;
			ppt->x_l = (report[2 * index + 0] & 0x00ff) >> 0;
			ppt->x_h = (report[2 * index + 0] & 0x3f00) >> 8;
			ppt->y_l = (report[2 * index + 1] & 0x00ff) >> 0;
			ppt->y_h = (report[2 * index + 1] & 0x0f00) >> 8;
			ppt->event = 0x02;
		}
		else if(0x02 == uevent[index])
		{
			ppt->id = (report[2 * index + 0] & 0x8000) >> 15;
		}
		uevent[index] = ppt->event;

		ppt++;
	}

	unsigned int readyBuffer = 0;
	pComBase->WriteToUsbMemory( pComBase->GET_MTK_DATA_RDY(), (unsigned char*)&readyBuffer, 4 );

	*len = sizeof(scap_rpt_data_t);

// 	unsigned short check = caculate_check_sum_u16( (unsigned short*)pointBuffer, 30 );
// 	if( 0 == check )  
// 		*len = tcLen;
// 	else
// 		*len = 0;

	return iReCode;
}
unsigned int CChipBaseImp::GetRawData( short* rawdataBuffer, unsigned short len )
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

	LoopTicker tick2( 30 );
	while( tick2.TickOnce() )
	{
		unsigned short rawLen = len + 2;
		iReCode = pComBase->ReadFromUsbMemory( pComBase->GET_MTK_FUNC_BUF(), (unsigned char*)rawdataBuffer, rawLen + 4 );
		CHECK_RETURN_IF_FAIL( iReCode );

		if( rawdataBuffer[len >> 1] == 0x5555 )
		{
			iReCode = ERROR_CODE_OK;
			break;
		}
		else
		{
			iReCode = ERROR_CODE_CHECK_SUM_MISMATCH;
		}
	}
	tick2.CheckTickAndMark( iReCode );
	CHECK_RETURN_IF_FAIL( iReCode );

	unsigned int readyBuffer = 0;
	pComBase->WriteToUsbMemory( pComBase->GET_MTK_DATA_RDY(), (unsigned char*)&readyBuffer, 4 );

	return iReCode;
}
unsigned int CChipBaseImp::ReadCoreSpace( unsigned int addr, unsigned char* buffer, unsigned int len )
{
	unsigned char iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	unsigned int left = len;

	while( left > 0 )
	{
		int onceLen = min( left, MAX_TXRX_SIZE );

		m_ProtocalApi->PrepareIoDataToSend( wr, CMD_MEM_RD, addr, onceLen, 0, CORE_R );
		iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
		CHECK_RETURN_IF_FAIL( iReCode );

		iReCode = pComBase->ReadFromUsbMemory( GetTxRxBufferAddr(), buffer, onceLen );
		CHECK_RETURN_IF_FAIL( iReCode );

		//unsigned short crc = caculate_check_sum_u816( buffer, onceLen );
		if( !m_ProtocalApi->CheckCoreDataOk( rd, buffer, onceLen ) )
		{
			//OnLineLogApp.AppendLogMessage( GetWrapperAddr()->GetIDMark(), value_buffer_to_string<unsigned char>( buffer, onceLen ).c_str() );
			iReCode = ERROR_CODE_CHECK_SUM_MISMATCH;

			break;
		}

		addr += onceLen;
		buffer += onceLen;
		left -= onceLen;
	}

	return iReCode;
}

unsigned int CChipBaseImp::WriteCoreSpace( unsigned int addr, unsigned char* buffer, unsigned int len )
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
		iReCode = pComBase->WriteToUsbMemory( GetTxRxBufferAddr(), buffer, onceLen );
		CHECK_RETURN_IF_FAIL( iReCode );

		unsigned short crc = caculate_check_sum_u816( buffer, onceLen );
		m_ProtocalApi->PrepareIoDataToSend( wr, CMD_MEM_WR, addr, onceLen, crc, CORE_W );
		iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
		CHECK_RETURN_IF_FAIL( iReCode );

		//code can't be run...
		//if( CC_ERR_CMDDATA_CHK == rd.scap.cc )
		//{
		//	iReCode = ERROR_CODE_CHECK_RESPONSE_FAILED;
		//	break;
		//}

		addr += onceLen;
		buffer += onceLen;
		left -= onceLen;
	}

	CHECK_RETURN_IF_FAIL( iReCode );

	return iReCode;
}

unsigned int CChipBaseImp::ReadBurnSpace( unsigned int addr, unsigned char* buffer, unsigned int len )
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
		iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 60 );
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
unsigned int CChipBaseImp::WriteBurnSpace( unsigned int addr, const unsigned char* buffer, unsigned int len, unsigned char type )
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
		iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 110 );//20
		CHECK_RETURN_IF_FAIL( iReCode );

		addr += onceLen;
		buffer += onceLen;
		left -= onceLen;
	}

	return iReCode;
}
unsigned int CChipBaseImp::EraseBurnSpace( unsigned int addr, unsigned int len )
{
	return ERROR_CODE_INVALID_PARAM;
}
unsigned int CChipBaseImp::GetCurrent( unsigned short cmd, short (&level)[2][2], unsigned short* workCurrrent, unsigned short* sleepCurrent )
{
	return ERROR_CODE_NO_KINDOF_IC;
}
unsigned int CChipBaseImp::ReadMtkFlash( unsigned int addr, unsigned char* buffer, unsigned int len)
{
	return ERROR_CODE_NO_KINDOF_IC;
}
unsigned int CChipBaseImp::CheckCatchBootFromMtk( unsigned int checkaddr, unsigned char* bootBuffer, unsigned int bootLen, unsigned short bulkLen, BOOL& bBootSame )
{
	unsigned int iReCode = ERROR_CODE_OK;
	unsigned char readBuffer[200*4] = {0};
	unsigned short read_len = bootLen <= 128 * 1024 ? (128 *4) :(200 * 4) ;
	unsigned int* pReadInt = (unsigned int*)readBuffer;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	iReCode = pComBase->ReadFromUsbMemory( checkaddr, readBuffer, read_len );
	CHECK_RETURN_IF_FAIL( iReCode );

	bBootSame = TRUE;

	int left = bootLen;
	while( left > 0 )
	{
		unsigned short onceCheck = left < bulkLen ? left : bulkLen;
		if( *pReadInt != caculate_check_sum_ex( bootBuffer, onceCheck ) )
		{
			bBootSame = FALSE;
			break;
		}

		pReadInt++;
		left -= onceCheck;
		bootBuffer += onceCheck;
	}

	return iReCode;
}
unsigned int CChipBaseImp::CheckCatchBootToMtk( unsigned int addr, unsigned char* bootBuffer, unsigned int bootLen, LPCheckCatchBootCallBack onBootCallBack/* = NULL */)
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
		m_ProtocalApi->PrepareIoDataToSend( wr, CMD_MTK_FBOOT_CHK, 0, bootLen, ((bootLen >> 16) << 1) | 0x0d );
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

		m_ProtocalApi->PrepareIoDataToSend( wr, CMD_MTK_FBOOT_CHK, 0, bootLen, ((bootLen >> 16) << 1) | 0x0d );
		iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
		CHECK_RETURN_IF_FAIL( iReCode );
	}


	return iReCode;
}
unsigned int CChipBaseImp::WriteFlashData( unsigned char* pData, unsigned int addr, unsigned short len )
{
	unsigned int iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	int left = len;
	while( left > 0 )
	{
		unsigned short onceWrite = left > 256 ? 256 : left;
		iReCode = pComBase->WriteToUsbMemory( GetTxRxBufferAddr(), pData, onceWrite );

		unsigned int checkSum = caculate_check_sum_ex( pData, onceWrite );
		m_ProtocalApi->PrepareIoDataToSend( wr, CMD_MTK_MEM_WR, addr & 0xffff, addr >> 16, onceWrite, MTK_FLASH, checkSum, checkSum >> 16 );
		iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
		CHECK_RETURN_IF_FAIL( iReCode );

		left -= onceWrite;
		addr += onceWrite;
		pData += onceWrite;
	}

	return iReCode;
}
unsigned int CChipBaseImp::HalAccessMode( unsigned char accType /*= 0*/ )
{
	unsigned char iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_CFG_IIC, accType );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
	CHECK_RETURN_IF_FAIL( iReCode );

	return iReCode;
}
unsigned int CChipBaseImp::WriteRegister( unsigned int address, unsigned int ucData ) 
{
	return ERROR_CODE_NO_KINDOF_IC;
}
unsigned int CChipBaseImp::ReadRegister( unsigned int address, unsigned int* pUcData )
{
	return ERROR_CODE_NO_KINDOF_IC;
}
//unsigned int CChipBaseImp::BSPRWrite( unsigned char* buffer, unsigned int len )
//{
//	unsigned int iReCode = ERROR_CODE_OK;
//	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
//	if( !pComBase )  return ERROR_CODE_COMM_ERROR;
//
//	ctp_cmd_std_t wr;
//	ctp_rsp_std_t rd;
//
//	unsigned int left = len;
//	unsigned short packetID = 0;
//
//	while( left > 0 )
//	{
//		int onceLen = min( left, MAX_TXRX_SIZE );
//		if( left <= MAX_TXRX_SIZE ) packetID |= 0x8000;
//		iReCode = pComBase->WriteToUsbMemory( GetTxRxBufferAddr(), buffer, onceLen );
//		CHECK_RETURN_IF_FAIL( iReCode );
//
//		unsigned short crc = caculate_check_sum_u816( buffer, onceLen );
//		m_ProtocalApi->PrepareIoDataToSend( wr, CMD_BSPR_WRITE, packetID++, onceLen, crc, CORE_W );
//		iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
//		CHECK_RETURN_IF_FAIL( iReCode );
//
//		if( CC_ERR_CMDDATA_CHK == rd.scap.cc )
//		{
//			iReCode = ERROR_CODE_CHECK_RESPONSE_FAILED;
//			break;
//		}
//
//		buffer += onceLen;
//		left -= onceLen;
//	}
//
//	CHECK_RETURN_IF_FAIL( iReCode );
//
//	return iReCode;
//}
//
//unsigned int CChipBaseImp::BSPRRead( unsigned char* buffer, unsigned int len )
//{
//	unsigned char iReCode = ERROR_CODE_OK;
//	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
//	if( !pComBase )  return ERROR_CODE_COMM_ERROR;
//
//	ctp_cmd_std_t wr;
//	ctp_rsp_std_t rd;
//
//	unsigned int left = len;
//	unsigned short packetID = 0;
//
//	while( left > 0 )
//	{
//		int onceLen = min( left, MAX_TXRX_SIZE );
//		if( left <= MAX_TXRX_SIZE ) packetID |= 0x8000;
//
//		m_ProtocalApi->PrepareIoDataToSend( wr, CMD_BSPR_READ, packetID++, onceLen, 0, CORE_R );
//		iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
//		CHECK_RETURN_IF_FAIL( iReCode );
//
//		iReCode = pComBase->ReadFromUsbMemory( GetTxRxBufferAddr(), buffer, onceLen );
//		CHECK_RETURN_IF_FAIL( iReCode );
//
//		unsigned short crc = caculate_check_sum_u816( buffer, onceLen );
//		if( rd.scap.d0 != crc )
//		{
//			//OnLineLogApp.AppendLogMessage( GetWrapperAddr()->GetIDMark(), value_buffer_to_string<unsigned char>( buffer, onceLen ).c_str() );
//			iReCode = ERROR_CODE_CHECK_SUM_MISMATCH;
//
//			break;
//		}
//
//		buffer += onceLen;
//		left -= onceLen;
//	}
//
//	return iReCode;
//}
unsigned int CChipBaseImp::BSPRWriteAndRead( unsigned char* writeBuffer, unsigned int iWrite, unsigned char* readBuffer, unsigned int iRead )
{
	unsigned int iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;
	if(iWrite > MAX_TXRX_SIZE || iRead > MAX_TXRX_SIZE) return ERROR_CODE_INVALID_PARAM;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;
	// GetTxRxBufferAddr()  
	if(iWrite > 0)
	{
		iReCode = pComBase->WriteToUsbMemory(pComBase->GET_MTK_TXRX_BUF_MCAP(), writeBuffer, iWrite );
		CHECK_RETURN_IF_FAIL( iReCode );
	}


	unsigned short crc = caculate_check_sum_u816( writeBuffer, iWrite );
	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_BSPR_RW, iWrite, iRead, crc, CORE_W );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
	CHECK_RETURN_IF_FAIL( iReCode );

	if(iRead > 0)
	{
		iReCode = pComBase->ReadFromUsbMemory( pComBase->GET_MTK_TXRX_BUF_MCAP(), readBuffer, iRead );
		CHECK_RETURN_IF_FAIL( iReCode );

		unsigned short crc = caculate_check_sum_u816( readBuffer, iRead );
		if( rd.scap.d0 != crc ) iReCode = ERROR_CODE_CHECK_SUM_MISMATCH;
	}

	return iReCode;
}