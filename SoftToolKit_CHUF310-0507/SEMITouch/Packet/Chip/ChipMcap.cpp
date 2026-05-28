#include "ChipMcap.h"
#include "checksum.h"

#define IS_VALID_ADDR(addr)   (((addr) & 0xff000000) == 0x20000000)
#define MCAP_ACCESS_ADDR_SPACE  4

CChipMcapImp::CChipMcapImp()
	:m_RawDataAddr(0)
	,m_DifferAddr(0)
	,m_BaseAddr(0)
{

}

CChipMcapImp::~CChipMcapImp()
{

}

unsigned int CChipMcapImp::HalAccessMode( unsigned char accType /*= 0*/ )
{
	return ERROR_CODE_OK;
}

unsigned int CChipMcapImp::GetTxRxBufferAddr()
{
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	return pComBase->GET_MTK_TXRX_BUF_MCAP();
}

unsigned int CChipMcapImp::WriteRegister( unsigned int address, unsigned int ucData ) 
{
	unsigned char iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	unsigned char writeBuffer[] = { (unsigned char)(address >> 24), (unsigned char)(address >> 16), (unsigned char)(address >> 8),(unsigned char)(address >> 0),
								     (unsigned char)(ucData >> 0) , (unsigned char)(ucData >> 8),(unsigned char)(ucData >> 16),(unsigned char)(ucData >> 24)  };

	iReCode = BSPRWriteAndRead( writeBuffer, 8, NULL, 0 );
	CHECK_RETURN_IF_FAIL( iReCode );

	return iReCode;
}
unsigned int CChipMcapImp::ReadRegister( unsigned int address, unsigned int* pUcData )
{
	unsigned char iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	unsigned char writeBuffer[] = { (unsigned char)(address >> 24), (unsigned char)(address >> 16), (unsigned char)(address >> 8), (unsigned char)(address >> 0)  };
	unsigned char readBuffer[] = {0, 0, 0, 0};

	iReCode = BSPRWriteAndRead( writeBuffer, 4, (unsigned char*)pUcData, 4 );
	CHECK_RETURN_IF_FAIL( iReCode );

	//*pUcData = (readBuffer[0] << 24) | (readBuffer[1] << 16) | (readBuffer[2] << 8) | (readBuffer[3]);

	return iReCode;
}

unsigned int CChipMcapImp::SwitchMode( unsigned char modeType, unsigned short len )
{
	unsigned char iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;
	if( 0 == len && MODE_TOUCH != modeType ) return ERROR_CODE_INVALID_PARAM;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	m_RawDataAddr = m_DifferAddr = m_BaseAddr = 0;

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_IDENTITY );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 5 );
	CHECK_RETURN_IF_FAIL( iReCode );

	if( 0xffff != (rd.mcap.d0 + rd.mcap.d1) || rd.mcap.d0 != 0xE902 )
	{
		iReCode = ERROR_CODE_INVALID_PARAM;
		CHECK_RETURN_IF_FAIL( iReCode );
	}
    
	unsigned char writeBuffer[] = {0x20, 0x00, 0x00, 0x00};
	unsigned char readBuffer[0x34];
	//iReCode = BSPRWriteAndRead( writeBuffer, sizeof(writeBuffer), readBuffer, sizeof(readBuffer) );
	iReCode = ReadCoreSpace( 0x20000000, readBuffer, sizeof(readBuffer) );

	m_RawDataAddr = 0x20000000 + ( (unsigned int)(readBuffer[0x21] << 8) + readBuffer[0x20] );
	m_DifferAddr  = 0x20000000 + ( (unsigned int)(readBuffer[0x23] << 8) + readBuffer[0x22] );
	m_BaseAddr    = 0x20000000 + ( (unsigned int)(readBuffer[0x25] << 8) + readBuffer[0x24] );

	if( MODE_RAWDATA == modeType )
	{
		m_ProtocalApi->PrepareIoDataToSend( wr, CMD_DATA_SYNC, m_RawDataAddr, len, 0, MODE_RAWDATA);
		iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
		CHECK_RETURN_IF_FAIL( iReCode );
	}
	else if( MODE_DIFFER == modeType )
	{
		m_ProtocalApi->PrepareIoDataToSend( wr, CMD_DATA_SYNC, m_DifferAddr, len, 0 ,MODE_DIFFER);
		iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
		CHECK_RETURN_IF_FAIL( iReCode );
	}
	else if( MODE_TOUCH == modeType )
	{
		m_ProtocalApi->PrepareIoDataToSend( wr, CMD_DATA_SYNC, 0x20000000 + 0x2c, 84, 1 ,MODE_TOUCH);
		iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
		CHECK_RETURN_IF_FAIL( iReCode );
	}
	else if( MODE_BASE == modeType )
	{
		m_ProtocalApi->PrepareIoDataToSend( wr, CMD_DATA_SYNC, m_BaseAddr, len, 0 ,MODE_BASE);
		iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
		CHECK_RETURN_IF_FAIL( iReCode );
	}
	else if( MODE_SIMULATE_RAW == modeType )
	{
		m_ProtocalApi->PrepareIoDataToSend( wr, CMD_DATA_SYNC, m_RawDataAddr, len, 0 ,MODE_SIMULATE_RAW);
		iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
		CHECK_RETURN_IF_FAIL( iReCode );
	}
	else if( MODE_SIMULATE_DIFF == modeType )
	{
		m_ProtocalApi->PrepareIoDataToSend( wr, CMD_DATA_SYNC, m_DifferAddr, len, 0 ,MODE_SIMULATE_DIFF);
		iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
		CHECK_RETURN_IF_FAIL( iReCode );
	}
	else
	{
		return ERROR_CODE_LOOP_BEYOND_MAX_RETRY;
	}

	return iReCode;
}

unsigned int CChipMcapImp::GetRawData( short* rawdataBuffer, unsigned short len )
{
	unsigned int iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;
	if( !IS_VALID_ADDR(m_RawDataAddr) )  return ERROR_CODE_INVALID_PARAM;

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

unsigned int CChipMcapImp::GetTouchPoint( unsigned char* pointBuffer, unsigned short* len )
{
	unsigned int iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;
	if( !IS_VALID_ADDR(m_RawDataAddr) )  return ERROR_CODE_INVALID_PARAM;

	LoopTicker tick( 50 );
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
//unsigned int CChipMcapImp::BSPRWriteAndRead( unsigned char* writeBuffer, unsigned int iWrite, unsigned char* readBuffer, unsigned int iRead )
//{
//	unsigned iReCode = ERROR_CODE_OK;
//	if( iWrite < MCAP_ACCESS_ADDR_SPACE )  return ERROR_CODE_INVALID_PARAM;
//
//	unsigned int addrDest = 0;
//	unsigned char* pAddrDest = (unsigned char*)&addrDest + sizeof(addrDest) - 1;
//	for( int index = 0; index < sizeof(addrDest); index++ )
//		*pAddrDest-- = *writeBuffer++;
//
//	iWrite = iWrite - sizeof(addrDest);
//	if( iWrite > 0 )
//	{
//		iReCode = WriteCoreSpace( addrDest, writeBuffer, iWrite );
//	}
//	if( iRead > 0 )
//	{
//		iReCode = ReadCoreSpace( addrDest, readBuffer, iRead );
//	}
//
//	// 	if( iWrite > 4 )
//	// 	{
//	// 		iReCode = BSPRWrite( writeBuffer, iWrite );
//	// 		CHECK_RETURN_IF_FAIL( iReCode );
//	// 	}
//	// 	
//	// 	if( iRead > 0 )
//	// 	{
//	// 		iReCode = BSPRRead( writeBuffer, iWrite, readBuffer, iRead );
//	// 		CHECK_RETURN_IF_FAIL( iReCode );
//	// 	}
//
//	return iReCode;
//}
unsigned int CChipMcapImp::SetConfigInFctMode( unsigned char* cfgBuffer, unsigned short len )
{
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_CTP_SSCAN, 0, 0x00 );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 30 );
	CHECK_RETURN_IF_FAIL( iReCode );

	iReCode = WriteCoreSpace( 0x20000080, cfgBuffer, len );
	CHECK_RETURN_IF_FAIL( iReCode );

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_CTP_SSCAN, 1, 0x7265 );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd, 30 );
	CHECK_RETURN_IF_FAIL( iReCode );

	return iReCode;
}
unsigned int CChipMcapImp::GetIoVoltage( unsigned int (&voltage)[2][10] )
{
	unsigned char iReCode = ERROR_CODE_OK;

	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	iReCode = IncokeCommand( CMD_IOVOLTAGE_TST );
	CHECK_RETURN_IF_FAIL( iReCode );

	//iReCode = ReadCoreSpace( 0x20000000, (unsigned char*)voltage, sizeof(voltage) );

	iReCode = pComBase->ReadFromUsbMemory( GetTxRxBufferAddr(), (unsigned char*)voltage, sizeof(voltage) );

	return iReCode;
}
unsigned int CChipMcapImp::GetCurrent( short (&level)[2][3], unsigned short* activeCurrrent, unsigned short* sleepCurrent, unsigned short* deepCurrent, unsigned short* idle )
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
	*idle = rd.mcap.d3;

	return iReCode;
}