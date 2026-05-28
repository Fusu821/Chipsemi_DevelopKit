#pragma once
#include "HalServiceInterface.h"
#include "automaticInterface.h"
#include "Wait.h"

enum PacketType{ PACKET_NORMAL, PACKET_START_TEST, PACKET_USER_DATA, };

struct srvMsg 
{
	PacketType type;
	unsigned short sP0;
	unsigned short sP1;
};

struct AutoWriteRead 
{
	unsigned char* pWrite;
	int numOfWrite;
	unsigned char* pRead;
	int numOfRead;
	int numOfReaded;
	IHalServiceInterface* context;
	AutoWriteRead( IHalServiceInterface* cx )
		:context(cx)
		,numOfReaded(0)
	{

	}
};
struct OpParam 
{
	IHalServiceInterface* context;
	union
	{
        struct  
        {
			const TransInfo_Collection* pCollection;
        }SendResult;
		struct  
		{
			LPCTSTR lineID;
			LPCTSTR account;
			LPCTSTR password;
		}AccountCheck;
		struct  
		{
			LPCTSTR lineID;
			unsigned char option;
		}SwitchMode;
		struct 
		{
			LPCTSTR lineID;
			LPCTSTR pannelID;
		}LogOn;
		struct 
		{
			LPCTSTR lineID;
			LPCTSTR pannelID;
			int nDevice;
			unsigned short result;
		}LogOff;
		struct  
		{
			unsigned char  ucDevice;
            unsigned int   testCode;
			unsigned short status;
			unsigned char  result;
		}NotifyStatus;
		struct  
		{
			unsigned char result;
		}HandShake;
		struct  
		{
			char* szIni;
			char* szBin;
		}Linkdata;
		struct 
		{
			int msg;
			WPARAM wparam;
			LPARAM lparam;
			NativeTestInterface* pcallBack;
		}UserData;
		struct 
		{
			unsigned char  ucDevice; 
            unsigned short packetType;
		}Ack;
	};
	OpParam(IHalServiceInterface* cx)
		:context( cx )
	{

	}
};
struct OpParamEx : public OpParam
{
public:
	OpParamEx( IHalServiceInterface* cx, SpinLock& locked )
		:OpParam( cx )
		,lock( locked )
	{
        lock.Lock();
	}
	~OpParamEx()
	{
		lock.Unlock();
	}
private:
	SpinLock& lock;
};

class CProtocal
{
public:
	CProtocal(){}

	virtual ~CProtocal(){}

	virtual bool Initalize( LinkParam& param ){ return true; }

	virtual void UnInitalize(){}

	virtual unsigned char SendResultUpToServer( const OpParam& param ) { return ERROR_CODE_OK; }

	virtual bool NotifyTestStatus( const OpParam& param ) { return false; }

	virtual unsigned char OnLine( const OpParam& param ){return ERROR_CODE_READ_USB_ERROR;}

	virtual unsigned char AccountCheck( const OpParam& param ){return ERROR_CODE_READ_USB_ERROR;}

	virtual unsigned char LogOnMessage( const OpParam& param ){return ERROR_CODE_READ_USB_ERROR;}

	virtual unsigned char LogOffMessage( const OpParam& param ){return ERROR_CODE_READ_USB_ERROR;}

	virtual unsigned char ActionToOnLineMessage(const OpParam& param){return ERROR_CODE_READ_USB_ERROR;}

	virtual LPCTSTR GetOnLineMessageInfo( ){ return m_szMsg; }

	virtual unsigned char OnLineDoHandShake( const OpParam& param ){ return false; }

	void OnLinkDataArrived( const OpParam& param ){ }

	virtual unsigned char OnGetUserData( const OpParam& param ){ return false; }

	virtual bool SendUserData(const OpParam& param){return false;}

	virtual bool SendAckPacket( const OpParam& param ){return false;}

	virtual bool ReceiveAckPacket( const OpParam& param ){return false;}

	virtual BOOL AnalyzeRecvAndMark( const unsigned char* buffer, unsigned int len, srvMsg& mark ) = 0;

    virtual unsigned int ResetCommandEvent( unsigned char ucDevice, unsigned int iCommandEvent){return 0xff;}

    virtual unsigned int WaitCommandEvent( unsigned char ucDevice, unsigned int iCommandEvent ,unsigned int iwaitTime){return 0xff;}

protected:
	TCHAR m_szMsg[MAX_PATH];
};

CProtocal* GetProtocalLikeStandard();
CProtocal* GetProtocalEDO();
CProtocal* GetProtocalHXD();
//CProtocal* GetProtocalTMCTP();