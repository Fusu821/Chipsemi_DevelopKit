#include "CommFake.h"
#include "framework.h"
#include "checksum.h"

#include "onlinelog.h"

#include "../Protocal/Protocal.h"

//#define FIXED_READ_SIZE(x)  ((x) + 0)
#define FIXED_WRITE_SIZE(x) ((x) + 8)

REGIST_RUNTIME_CLASS_PVOID( COMM_TYPE, (COMM_TYPE)LINK_TYPE_FAKE, CCommFake )


CCommFake::CCommFake(LPVOID param)
:m_fakeOut(NULL)
{
#ifdef _DEBUG
	m_iDeviceIndex = 0;
#endif
}
CCommFake::~CCommFake()
{
}
unsigned int CCommFake::GetCommType()
{
	return LINK_TYPE_FAKE;
}
unsigned int CCommFake::SyncWorkcInit( unsigned char bHold/* = 1 */)
{
	return ERROR_CODE_OK;
}
BOOL CCommFake::Connected()
{
	return TRUE;
}
unsigned int CCommFake::HalTrySetDeviceManuly( Device hDevice )
{
	return ERROR_CODE_OK;
}
unsigned int CCommFake::SetSimulateContext( LPVOID pContext )
{
	m_fakeOut = NULL;
	memcpy_s( m_localSimuArray, sizeof(m_localSimuArray), pContext, sizeof(m_localSimuArray) );

	return ERROR_CODE_OK;
}
unsigned int CCommFake::SendCommand( unsigned char* pWrite, unsigned char* pRead )
{
// 	pRead;
// 	unsigned int iRetCode = ERROR_CODE_COMM_ERROR;
// 
// 	{
// 		//clear response buffer
// 		unsigned char clearBuffer[] = {0x02, MTK_RSP_BUF >> 8, MTK_RSP_BUF & 0xff, 0, 0, 0, 0, 0, 0, 0, 0, 0};
// 		iRetCode = m_HalInterface->Write( clearBuffer, sizeof(clearBuffer) );
// 
// 	}
// 
// 	if( ERROR_CODE_OK == iRetCode )
// 	{
// 		unsigned char* pDes = (unsigned char*)pWrite;
// 		const int writeLen = 8 + sizeof(ctp_cmd_std_t);
// 		unsigned char writeBuffer[writeLen] = { 0x02, MTK_CMD_BUF >> 8, MTK_CMD_BUF & 0xff, 0x10, 0x10, 0x10, 0x10, 0x10 };
// 		for( int index = 0; index < sizeof(ctp_cmd_std_t); index++ )
// 		{
// 			writeBuffer[8 + index] = pDes[index];
// 		}
// 
// 		iRetCode = m_HalInterface->Write( writeBuffer, writeLen );
// 	}
//	
//	return iRetCode;

	return ERROR_CODE_OK;
}
unsigned int CCommFake::SendCommandAndCheck( ProtocalApi* protocalApi, unsigned char* pWrite, unsigned char* pRead, unsigned short delay/* = 30*/ )
{
	ctp_cmd_std_t* commandAddr = (ctp_cmd_std_t*)pWrite;
	if( NULL == commandAddr ) return ERROR_CODE_COMM_ERROR;

	for( int index = 0; index < SIMULATE_TEST_DATA_CNT; index++ )
	{
		unsigned char cmdID = m_localSimuArray[index].itemID & 0xff;
		unsigned short exeClk = ( m_localSimuArray[index].itemID >> 16 ) & 0xffff;
		if( commandAddr->scap.id == cmdID && exeClk == commandAddr->cross.d0 )
		{
			m_fakeOut = m_localSimuArray[index].itemArray;
			break;
		}
		else if( commandAddr->mcap.id == cmdID && exeClk == commandAddr->cross.d0 )
		{
			m_fakeOut = m_localSimuArray[index].itemArray;

			if( CMD_DATA_SYNC == cmdID )
			{
				if( CMD_DATA_SYNC == (m_localSimuArray[index + 1].itemID & 0xff) )
				{
					m_localSimuArray[index + 1].itemID = m_localSimuArray[index].itemID;
					m_localSimuArray[index].itemID = 0;	
				}
			}
			
			if( CMD_IDENTITY == commandAddr->mcap.id )
			{
				for( int iCnt = 0; iCnt < sizeof(ctp_rsp_std_t); iCnt++ )
				{
					pRead[iCnt] = (unsigned char)m_fakeOut[iCnt];
				}
			}
			else 
			{
				ctp_rsp_std_t* respondAddr = (ctp_rsp_std_t*)pRead;
				unsigned short len = commandAddr->mcap.d1;
				len = min(len, sizeof(m_localSimuArray[index].itemArray) / sizeof(short));
				respondAddr->mcap.d0 = caculate_check_sum_u816( (unsigned char*)m_fakeOut, len );
			}

			break;
		}
	}

	

// 	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
// 
// 	iReCode = SendCommand( pWrite, pRead );
// 
// 	if( iReCode == ERROR_CODE_OK )
// 	{
// 		//SysDelay( 30 );  //wait for mtk board action done
// 		SysDelay( delay );
// 
// 		memset( pRead, 0, sizeof(ctp_rsp_std_t) );
// 
// 		unsigned char writeBuffer[] = { 0x02, MTK_RSP_BUF >> 8, MTK_RSP_BUF & 0xff, CMD_NA };
// 
// 		LoopTicker tick( 100 );
// 		while ( tick.TickOnce() )
// 		{
// 			iReCode = m_HalInterface->IoCtrl( writeBuffer, sizeof(writeBuffer), (unsigned char*)pRead, sizeof(ctp_rsp_std_t) );
// 
// 			//id
// 			if( pWrite[0] != pRead[0] )
// 			{
// 				SysDelay( delay );
// 
// 				//OnLineLogApp.AppendLogMessage( GetWrapperAddr()->GetIDMark(), value_buffer_to_string<unsigned char>( pRead, sizeof(ctp_rsp_std_t) ).c_str() );
// 
// 				continue;
// 			}
// 			if( caculate_check_sum_u16( (unsigned short*)pRead, sizeof(ctp_rsp_std_t) ) )
// 			{
// 				SysDelay( delay );
// 
// 				//OnLineLogApp.AppendLogMessage( GetWrapperAddr()->GetIDMark(), value_buffer_to_string<unsigned char>( pRead, sizeof(ctp_rsp_std_t) ).c_str() );
// 
// 				continue;
// 			}
// 
// 			//cc
// 			if( iReCode == ERROR_CODE_OK &&  CC_SUCCESS == pRead[1] )
// 			{
// 				iReCode = ERROR_CODE_OK;
// 				break;
// 			}
// 			else
// 			{
// 				iReCode = ERROR_CODE_CHECK_RESPONSE_FAILED;
// 				//OnLineLogApp.AppendLogMessage( GetWrapperAddr()->GetIDMark(), value_buffer_to_string<unsigned char>( pRead, sizeof(ctp_rsp_std_t) ).c_str() );
// 				break;
// 			}
// 		}
// 
// 		tick.CheckTickAndMark( iReCode );
// 	}
// 
// 	return iReCode;

	return ERROR_CODE_OK;
}
unsigned int CCommFake::ReadFromUsbMemory( unsigned short addr, unsigned char* pRead, unsigned short len )
{
	if( NULL == m_fakeOut ) 
		return ERROR_CODE_OK;

	if( MTK_FUNC_BUF == addr )
	{
		//pRead = (unsigned char*)m_fakeOut;
		memcpy_s( pRead, len, (void*)m_fakeOut, len );
	}
	else if( MTK_DATA_RDY == addr )
	{
		*pRead = 1;
	}
	else if( MTK_TXRX_BUF_MCAP == addr )
	{
		memcpy_s( pRead, len, (void*)m_fakeOut, len );
	}

	return ERROR_CODE_OK;
}
unsigned int CCommFake::WriteToUsbMemory( unsigned short addr, const unsigned char* pWrite, unsigned short len )
{
// 	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
// 
// 	unsigned char writeBuffer[REAL_HAL_WR_LEN + 10] = {0};
// 
// 	int byteLeft = len, onceWrite = REAL_HAL_WR_LEN;
// 
// 	while( byteLeft > 0 )
// 	{
// 		onceWrite = min( REAL_HAL_WR_LEN, byteLeft );
// 
// 		memset( writeBuffer, 0, sizeof(writeBuffer) );
// 		writeBuffer[0] = 0x02;
// 		writeBuffer[1] = (addr >> 8) & 0xff;
// 		writeBuffer[2] = (addr) & 0xff;
// 		memcpy_s( writeBuffer + 8, onceWrite, pWrite, onceWrite );
// 
// 		iReCode = m_HalInterface->Write( writeBuffer, FIXED_WRITE_SIZE(onceWrite) );
// 
// 		byteLeft -= onceWrite;
// 		pWrite += onceWrite;
// 		addr += onceWrite;
// 
// 		if( iReCode != ERROR_CODE_OK ) break;
// 	}
// 
// 	return iReCode;

	return ERROR_CODE_OK;
}
unsigned int CCommFake::SetIoVoltage( unsigned short vdd, unsigned short iovdd, unsigned short vih )
{
   return ERROR_CODE_OK;
}
unsigned int CCommFake::UpgradeMtkBoard( unsigned char devNo, unsigned char* pMtkBin, unsigned int len, LPUpdateProcessPosCallBack lpProcess )
{
	return ERROR_CODE_OK;
}
unsigned int CCommFake::PrepareMtkBoardUpgrade(  )
{
	return ERROR_CODE_OK;
}