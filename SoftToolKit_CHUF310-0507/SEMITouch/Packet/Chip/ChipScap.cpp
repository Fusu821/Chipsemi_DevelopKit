#include "ChipScap.h"
#include "checksum.h"

CChipScapImp::CChipScapImp()
{

}
CChipScapImp::~CChipScapImp()
{

}

unsigned int CChipScapImp::GetTxRxBufferAddr()
{
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();

	return pComBase->GET_MTK_TXRX_BUF_SCAP();
}

// unsigned int CChipScapImp::WriteCoreSpace( unsigned int addr, unsigned char* buffer, unsigned int len )
// {
// 	unsigned int iReCode = ERROR_CODE_OK;
// 	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
// 	if( !pComBase )  return ERROR_CODE_COMM_ERROR;
// 
// 	ctp_cmd_std_t wr;
// 	ctp_rsp_std_t rd;
// 
// 	unsigned int left = len;
// 
// 	while( left > 0 )
// 	{
// 		int onceLen = min( left, MAX_TXRX_SIZE );
// 		iReCode = pComBase->WriteToUsbMemory( MTK_TXRX_BUF, buffer, onceLen );
// 		CHECK_RETURN_IF_FAIL( iReCode );
// 
// 		unsigned short crc = caculate_check_sum_u816( buffer, onceLen );
// 		m_ProtocalApi->PrepareIoDataToSend( wr, CMD_MEM_WR, addr, onceLen, crc, CORE_W );
// 		iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
// 		CHECK_RETURN_IF_FAIL( iReCode );
// 
// 		//code can't be run...
// 		//if( CC_ERR_CMDDATA_CHK == rd.scap.cc )
// 		//{
// 		//	iReCode = ERROR_CODE_CHECK_RESPONSE_FAILED;
// 		//	break;
// 		//}
// 
// 		addr += onceLen;
// 		buffer += onceLen;
// 		left -= onceLen;
// 	}
// 
// 	CHECK_RETURN_IF_FAIL( iReCode );
// 
// 	return iReCode;
// }

unsigned int CChipScapImp::GetCurrent( unsigned short cmd, short (&level)[2][2], unsigned short* workCurrrent, unsigned short* sleepCurrent )
{
	unsigned int iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_MTK_TEST_PINS_LEAK, 0x7563, cmd, level[0][0], (char)level[0][1], level[1][0], level[1][1] );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
	CHECK_RETURN_IF_FAIL( iReCode );

	*workCurrrent = rd.scap.d0;
	*sleepCurrent = rd.scap.sn;

	return iReCode;
}

unsigned int CChipScapImp::WriteRegister( unsigned int address, unsigned int ucData ) 
{
	unsigned char iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_WRITE_REGISTER, address, ucData );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
	CHECK_RETURN_IF_FAIL( iReCode );

	return iReCode;
}
unsigned int CChipScapImp::ReadRegister( unsigned int address, unsigned int* pUcData )
{
	unsigned char iReCode = ERROR_CODE_OK;
	ICommBase* pComBase = GetWrapperAddr()->GetCommBaseInterface();
	if( !pComBase )  return ERROR_CODE_COMM_ERROR;

	ctp_cmd_std_t wr;
	ctp_rsp_std_t rd;

	m_ProtocalApi->PrepareIoDataToSend( wr, CMD_READ_REGISTER, (unsigned short)address );
	iReCode = pComBase->SendCommandAndCheck( m_ProtocalApi, (unsigned char*)&wr, (unsigned char*)&rd );
	CHECK_RETURN_IF_FAIL( iReCode );

	*pUcData = rd.scap.d0;

	return iReCode;
}





