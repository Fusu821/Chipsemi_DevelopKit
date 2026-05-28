#pragma once
#include "Protocal.h"

class CProtocalStandard : public CProtocal
{
public:
	CProtocalStandard();
	virtual ~CProtocalStandard();

	virtual unsigned char SendResultUpToServer( const OpParam& param );

	virtual bool NotifyTestStatus( const OpParam& param );

	virtual unsigned char AccountCheck( const OpParam& param );

	virtual unsigned char OnLineDoHandShake( const OpParam& param );

	virtual unsigned char OnGetUserData( const OpParam& param );

	virtual bool SendUserData(const OpParam& param );

	virtual bool SendAckPacket( const OpParam& param );

	virtual bool ReceiveAckPacket( const OpParam& param );

    virtual unsigned int ResetCommandEvent( unsigned char ucDevice, unsigned int iCommandEvent ) ;

    virtual unsigned int WaitCommandEvent( unsigned char ucDevice, unsigned int iCommandEvent ,unsigned int iwaitTime = 500);

    virtual unsigned int SetCommandEvent( unsigned char ucDevice, unsigned int iCommandEvent = 0xffff);

	BOOL AnalyzeRecvAndMark( const unsigned char* buffer, unsigned int len, srvMsg& mark );


private:
	unsigned char SendDataSerialy( const AutoWriteRead& wr );
    HANDLE m_hCommandEvent[MAX_DEVICE_NUM];
    unsigned int m_iCommand[MAX_DEVICE_NUM];
};
