#pragma once
#include "SEMITouch.h"
#include "HalServiceInterface.h"
#include "../RefSelf.h"
#include "../Protocal/Protocal.h"
#include "helper.h"
class CCommHID : public ICommBase, public RefSelf
{
public:
	CCommHID(LPVOID param);
	virtual ~CCommHID();

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
	unsigned int PrepareMtkBoardUpgrade(  );
	unsigned int MtkBoardReBoot(unsigned int wantGo);
	unsigned int DetectMtkExtendSignal( unsigned char* signal = 0 );
	unsigned int SetMtkExternOutput( unsigned char PB0, unsigned char PB1, unsigned char PB2 );
	//unsigned int ReadFromBoardTxRxBuff( unsigned char* pRead, unsigned short len );
private:
	IHalServiceInterface* m_HalInterface;

	unsigned int m_Link_Type;

#ifdef _DEBUG
	unsigned char m_iDeviceIndex;
#endif
};