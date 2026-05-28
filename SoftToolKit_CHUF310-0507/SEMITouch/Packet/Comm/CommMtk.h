#pragma once
#include "SEMITouch.h"
#include "HalServiceInterface.h"
#include "../RefSelf.h"
#include "../Protocal/Protocal.h"
#include "helper.h"

class CommAddr
{
public:
	CommAddr(){ m_MtkType = MTK_TYPE_V5; }
	~CommAddr() {}

	void SetMtkType(unsigned int pMtkType){ m_MtkType = pMtkType; }

	unsigned int Get_MtkType(){return m_MtkType;} 

	unsigned short GET_MTK_DEVICE_NO_ADDR(){return m_MtkType == MTK_TYPE_V5 ? SM_MTK_DEVICE_NO_ADDR :MTK_DEVICE_NO_ADDR_V8;} 

	unsigned short GET_MTK_CMD_BUF(){return m_MtkType == MTK_TYPE_V5 ? MTK_CMD_BUF : MTK_CMD_BUF_V8;} 

	unsigned short GET_MTK_RSP_BUF(){return m_MtkType == MTK_TYPE_V5 ? MTK_RSP_BUF : MTK_RSP_BUF_V8;} 

	unsigned short GET_MTK_FUNC_BUF(){return m_MtkType == MTK_TYPE_V5 ? MTK_FUNC_BUF : MTK_FUNC_BUF_V8;} 

	unsigned short GET_MTK_TXRX_BUF_SCAP(){return m_MtkType == MTK_TYPE_V5 ? MTK_TXRX_BUF_SCAP : MTK_TXRX_BUF_SCAP_V8;} 

	unsigned short GET_MTK_TXRX_BUF_MCAP(){return m_MtkType == MTK_TYPE_V5 ? MTK_TXRX_BUF_MCAP : MTK_TXRX_BUF_MCAP_V8;} 

	unsigned short GET_MTK_DATA_RDY(){return m_MtkType == MTK_TYPE_V5 ? MTK_DATA_RDY : MTK_DATA_RDY_V8;} 

	unsigned short GET_MTK_TXRX_BUF_MTK(){return m_MtkType == MTK_TYPE_V5 ? MTK_TXRX_BUF_MTK : MTK_TXRX_BUF_MTK_V8;} 

	unsigned short GET_MTK_DEV_TYPE_ADDR(){return m_MtkType == MTK_TYPE_V5 ? DEV_TYPE_ADDR : MTK_DEV_TYPE_ADDR_V8;} 

	unsigned short GET_MTK_VER_ADDR(){return m_MtkType == MTK_TYPE_V5 ? MTK_VER_ADDR : MTK_VER_ADDR_V8;} 

	unsigned short GET_MTK_FLASHBOOT_1KCHK() {return m_MtkType == MTK_TYPE_V5 ? MTK_FLASHBOOT_1KCHK : MTK_FLASHBOOT_1KCHK_V8;}

	unsigned short GET_MTK_LINK_AND_ID(){return MTK_LINK_AND_ID;} 

private:
	unsigned int m_MtkType;
};

class CCommMtk : public ICommBase, public RefSelf
{
public:
	CCommMtk(LPVOID param);
	virtual ~CCommMtk();

public:
	BOOL Connected();
	unsigned int GetCommType();
	unsigned int SyncWorkcInit( unsigned char bHold = 1 );
	unsigned int HalTrySetDeviceManuly( Device hDevice );
	unsigned int SendCommand( unsigned char* pWrite, unsigned char* pRead );
	unsigned int SendCommandAndCheck( ProtocalApi* protocalApi, unsigned char* pWrite, unsigned char* pRead, unsigned short delay = 30 );
	unsigned int ReadFromUsbMemory( unsigned short addr, unsigned char* pRead, unsigned short len );
	unsigned int WriteToUsbMemory( unsigned short addr, const unsigned char* pWrite, unsigned short len );
    unsigned int SetIoVoltage( unsigned short vdd, unsigned short iovdd, unsigned short vih );
    //unsigned int SetIoVoltageTest( unsigned short vdd, unsigned short iovdd, unsigned short vih,unsigned short vih1000=0) override;
	unsigned int UpgradeMtkBoard( unsigned char devNo, unsigned char* pMtkBin, unsigned int len, LPUpdateProcessPosCallBack lpProcess );
	unsigned int ReadMtkBoard( unsigned char devNo, unsigned char* pMtkBin, unsigned int len, LPUpdateProcessPosCallBack lpProcess ) override;
	unsigned int PrepareMtkBoardUpgrade(  );
	unsigned int MtkBoardReBoot(unsigned int wantGo);
	unsigned int DetectMtkExtendSignal( unsigned char* signal = 0 );
	unsigned int SetMtkExternOutput( unsigned char PB0, unsigned char PB1, unsigned char PB2 );
	//unsigned int ReadFromBoardTxRxBuff( unsigned char* pRead, unsigned short len );
	unsigned int GetMtkType();

	virtual unsigned short GET_MTK_LINK_AND_ID() override;
	virtual unsigned short GET_MTK_DEVICE_NO_ADDR() override; 
	virtual unsigned short GET_MTK_CMD_BUF() override;
	virtual unsigned short GET_MTK_RSP_BUF() override;
	virtual unsigned short GET_MTK_FUNC_BUF() override;
	virtual unsigned short GET_MTK_TXRX_BUF_SCAP() override;
	virtual unsigned short GET_MTK_TXRX_BUF_MCAP() override;
	virtual unsigned short GET_MTK_DATA_RDY() override;
	virtual unsigned short GET_MTK_TXRX_BUF_MTK() override;
	virtual unsigned short GET_MTK_DEV_TYPE_ADDR() override;
	virtual unsigned short GET_MTK_VER_ADDR() override;
	virtual unsigned short GET_MTK_FLASHBOOT_1KCHK() override;

	CommAddr& GetCommAddr();
private:
	IHalServiceInterface* m_HalInterface;
	CommAddr m_CommAddr;

#ifdef _DEBUG
	unsigned char m_iDeviceIndex;
#endif
};


