#pragma once
#include "ProtocalStandard.h"

//EDO EMS –≠“È
CProtocal* GetProtocalHXD();
//#define is_success_likely(x)                      (ERROR_CODE_OK == (x) || ERROR_CODE_WAIT_RESPONSE_TIMEOUT == (x)) 
inline bool is_success_likely(unsigned char ret)
{
	return (ERROR_CODE_OK == (ret) || ERROR_CODE_WAIT_RESPONSE_TIMEOUT == (ret));
}

class CProtocalHXD : public CProtocal
{
public:
	CProtocalHXD();
	virtual ~CProtocalHXD();

	virtual unsigned char OnLine( const OpParam& param );

	unsigned char ActionToOnLineMessage(const OpParam& param);

    unsigned char SendResultUpToServer( const OpParam& param );

	unsigned char LogOffMessage( const OpParam& param );

	virtual BOOL AnalyzeRecvAndMark( const unsigned char* buffer, unsigned int len, srvMsg& mark );
private:
	bool ResponseOk( TCHAR* szContent, unsigned short len, int tag );

    unsigned char SendDataSerialy( const AutoWriteRead& wr );

	//unsigned char ReadDataSerialy( const AutoWriteRead& wr );

	void LogIt(const AutoWriteRead& wr);

	void LogItEx(const AutoWriteRead& wr);

private:
	BOOL m_bWaitRsp;
};