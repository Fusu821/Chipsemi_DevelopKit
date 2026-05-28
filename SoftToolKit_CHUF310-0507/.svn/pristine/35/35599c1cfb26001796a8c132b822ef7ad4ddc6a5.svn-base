#include "Protocal.h"
#include "checksum.h"
#include "SEMITouch.h"

// void ProtocalApi::PrepareIoDataToSendEx( ctp_cmd_std_t& wr, unsigned char cmd, unsigned short d0 /* = 0 */, unsigned short d1 /* = 0 */, unsigned short d2 /* = 0 */ )
// {
// 
// }
unsigned short ProtocalScapApi::KindOfProcal()
{
	return IC_TYPE_SCAP;
}
unsigned short ProtocalScapApi::ResponseLength()
{
	return sizeof(s_ctp_rsp_std_t);
}
bool ProtocalScapApi::CheckResponseOk( unsigned int& iReCode, unsigned short delay, unsigned char* pWrite, unsigned char* pRead )
{
	bool bBreakDown = false;

	s_ctp_cmd_std_t* pcmd = (s_ctp_cmd_std_t*)pWrite;
	s_ctp_rsp_std_t* resp =  (s_ctp_rsp_std_t*)pRead;

	//id
	if( pcmd->id != resp->id )
	{
		SysDelay( delay );

		//OnLineLogApp.AppendLogMessage( GetWrapperAddr()->GetIDMark(), value_buffer_to_string<unsigned char>( pRead, sizeof(ctp_rsp_std_t) ).c_str() );

		return bBreakDown = false;
	}
	if( caculate_check_sum_u16( (unsigned short*)pRead, sizeof(ctp_rsp_std_t) ) )
	{
		SysDelay( delay );

		//OnLineLogApp.AppendLogMessage( GetWrapperAddr()->GetIDMark(), value_buffer_to_string<unsigned char>( pRead, sizeof(ctp_rsp_std_t) ).c_str() );

		return bBreakDown = false;
	}

	//cc
	if( iReCode == ERROR_CODE_OK &&  CC_SUCCESS == pRead[1] )
	{
		iReCode = ERROR_CODE_OK;

		return bBreakDown = true;
	}
	else
	{
		iReCode = ERROR_CODE_CHECK_RESPONSE_FAILED;
		//OnLineLogApp.AppendLogMessage( GetWrapperAddr()->GetIDMark(), value_buffer_to_string<unsigned char>( pRead, sizeof(ctp_rsp_std_t) ).c_str() );
		return bBreakDown = true;
	}

	return bBreakDown;
}
bool ProtocalScapApi::CheckCoreDataOk( const ctp_rsp_std_t& rd, unsigned char* buffer, unsigned short onceLen )
{
	unsigned short crc = caculate_check_sum_u816( buffer, onceLen );
	if( rd.scap.d0 != crc )
		return false;

	return true;
}
bool ProtocalScapApi::CheckOtpDataOk( const ctp_rsp_std_t& rd, unsigned char* buffer, unsigned short onceLen )
{
	unsigned int check = caculate_check_sum_ex( buffer, onceLen );
	if( ( rd.scap.d0 != (unsigned short)check ) || ( rd.scap.sn != (unsigned short)(check >> 16) ) ) 
		return false;

	return true;
}
void ProtocalScapApi::PrepareIoDataToSend( ctp_cmd_std_t& wr, unsigned char cmd, unsigned int d0 /* = 0 */, unsigned short d1 /* = 0 */, unsigned short d2 /* = 0 */, unsigned short ext1 /* = 0 */, unsigned short ext2 /* = 0 */, unsigned short ext3 /* = 0 */ )
{
	wr.scap.id = cmd;
	wr.scap.d0 = (unsigned short)d0;
	wr.scap.d1 = d1;
	wr.scap.d2 = d2;
	wr.scap.idv = ~wr.scap.id;
	wr.scap.tag = 0x35;
	wr.scap.resv = (unsigned char)ext1;
	wr.scap.s2Pad0 = ext2;
	wr.scap.s2Pad1 = ext3;
	wr.scap.chk = 1 + ( ~caculate_check_sum_u16( (unsigned short*)&wr, 10 ) );
}

unsigned short ProtocalMcapApi::KindOfProcal()
{
	return IC_TYPE_MCAP;
}
unsigned short ProtocalMcapApi::ResponseLength()
{
	return sizeof(m_ctp_rsp_std_t);
}
bool ProtocalMcapApi::CheckResponseOk( unsigned int& iReCode, unsigned short delay, unsigned char* pWrite, unsigned char* pRead )
{
	bool bBreakDown = false;

	m_ctp_cmd_std_t* pcmd = (m_ctp_cmd_std_t*)pWrite;
	m_ctp_rsp_std_t* resp =  (m_ctp_rsp_std_t*)pRead;
	//id
	if( pcmd->id != resp->id )
	{
		SysDelay( delay );

		//OnLineLogApp.AppendLogMessage( GetWrapperAddr()->GetIDMark(), value_buffer_to_string<unsigned char>( pRead, sizeof(ctp_rsp_std_t) ).c_str() );

		return bBreakDown = false;
	}
	if( caculate_check_sum_u16( (unsigned short*)pRead, sizeof(ctp_rsp_std_t) ) )
	{
		SysDelay( delay );

		//OnLineLogApp.AppendLogMessage( GetWrapperAddr()->GetIDMark(), value_buffer_to_string<unsigned char>( pRead, sizeof(ctp_rsp_std_t) ).c_str() );

		return bBreakDown = false;
	}

	//cc
	if( iReCode == ERROR_CODE_OK &&  CC_SUCCESS == resp->cc )
	{
		iReCode = ERROR_CODE_OK;

		return bBreakDown = true;
	}
	else
	{
		iReCode = ERROR_CODE_CHECK_RESPONSE_FAILED;
		//OnLineLogApp.AppendLogMessage( GetWrapperAddr()->GetIDMark(), value_buffer_to_string<unsigned char>( pRead, sizeof(ctp_rsp_std_t) ).c_str() );
		return bBreakDown = true;
	}

	return bBreakDown;
}
bool ProtocalMcapApi::CheckCoreDataOk( const ctp_rsp_std_t& rd, unsigned char* buffer, unsigned short onceLen )
{
	unsigned short crc = caculate_check_sum_u816( buffer, onceLen );

	if( rd.mcap.d0 != crc )
		return false;

	return true;
}
bool ProtocalMcapApi::CheckOtpDataOk( const ctp_rsp_std_t& rd, unsigned char* buffer, unsigned short onceLen )
{
	unsigned int check = caculate_check_sum_ex( buffer, onceLen );
	if( ( rd.mcap.d0 != (unsigned short)check ) || ( rd.mcap.d1 != (unsigned short)(check >> 16) ) ) 
		return false;

	return true;
}
void ProtocalMcapApi::PrepareIoDataToSend( ctp_cmd_std_t& wr, unsigned char cmd, unsigned int d0 /* = 0 */, unsigned short d1 /* = 0 */, unsigned short d2 /* = 0 */, unsigned short ext1 /* = 0 */, unsigned short ext2 /* = 0 */, unsigned short ext3 /* = 0 */ )
 {
	 wr.mcap.id = cmd;
	 wr.mcap.d0 = d0;
	 wr.mcap.d1 = d1;
	 wr.mcap.d2 = d2;
	 wr.mcap.d3 = ext1;
	 wr.mcap.d4 = ext2;
	 wr.mcap.d5 = ext3;
	 wr.mcap.tag = 0xE9;
	 if( (d0 & 0xffff0000) > 0 )
	 {
		 wr.mcap.d5 = (d0 & 0xffff0000) >> 16;
	 }
	 wr.mcap.chk = 1 + ( ~caculate_check_sum_u16( (unsigned short*)&wr.mcap.d0, 14 ) );
 }

//void ProtocalApi::PrepareIoDataToSend( ctp_cmd_std_t& wr, unsigned char cmd, unsigned short d0 /*= 0*/, unsigned short d1/* = 0*/, unsigned short d2/* = 0*/, ... )
//{
//
//}
//
//void ProtocalScapApi::PrepareIoDataToSend( ctp_cmd_std_t& wr, unsigned char cmd, unsigned short d0 /*= 0*/, unsigned short d1/* = 0*/, unsigned short d2/* = 0*/, ... )
//{
//
//}