#pragma once
#include "SEMITouch.h"
#include "HalServiceInterface.h"
#include "../RefSelf.h"
#include "helper.h"
class CCommFake : public ICommBase, public RefSelf
{
public:
	CCommFake(LPVOID param);
	virtual ~CCommFake();

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
	unsigned int UpgradeMtkBoard( unsigned char devNo, unsigned char* pMtkBin, unsigned int len, LPUpdateProcessPosCallBack lpProcess );
	unsigned int PrepareMtkBoardUpgrade(  );
	//unsigned int ReadFromBoardTxRxBuff( unsigned char* pRead, unsigned short len );
	unsigned int SetSimulateContext( LPVOID pContext );
private:
	//IHalServiceInterface* m_HalInterface;

	SimulateData m_localSimuArray[SIMULATE_TEST_DATA_CNT];

	unsigned short* m_fakeOut;

#ifdef _DEBUG
	unsigned char m_iDeviceIndex;
#endif
};