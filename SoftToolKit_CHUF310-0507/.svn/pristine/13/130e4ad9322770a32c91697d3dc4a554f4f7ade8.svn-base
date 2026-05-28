#pragma once
#include "ProtocalStandard.h"

//EDO EMS –≠“È
CProtocal* GetProtocalEDO();
//#define is_success_likely(x)                      (ERROR_CODE_OK == (x) || ERROR_CODE_WAIT_RESPONSE_TIMEOUT == (x)) 
inline bool is_success_likely(unsigned char ret)
{
	return (ERROR_CODE_OK == (ret) || ERROR_CODE_WAIT_RESPONSE_TIMEOUT == (ret));
}

class CProtocalEDO : public CProtocal
{
public:
	CProtocalEDO();
	virtual ~CProtocalEDO();

	virtual bool Initalize( LinkParam& param );

	virtual void UnInitalize();

	virtual unsigned char OnLine( const OpParam& param );

	virtual unsigned char AccountCheck( const OpParam& param );

	virtual unsigned char LogOnMessage( const OpParam& param );

	virtual unsigned char LogOffMessage( const OpParam& param );

	virtual BOOL AnalyzeRecvAndMark( const unsigned char* buffer, unsigned int len, srvMsg& mark );
private:
	bool ResponseOk( TCHAR* szContent, unsigned short len, int tag );

    unsigned char SendDataSerialy( const AutoWriteRead& wr );

	void LogIt(const AutoWriteRead& wr);

private:
	tstring m_szAccount;
	tstring m_szPassword;

	IHalServiceInterface* m_HalTclServerInterface;
};