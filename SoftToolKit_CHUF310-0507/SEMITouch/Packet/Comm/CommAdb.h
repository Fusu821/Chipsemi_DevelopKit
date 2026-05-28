#pragma once
#include "SEMITouch.h"
#include "HalServiceInterface.h"
#include "../RefSelf.h"
#include "../Protocal/Protocal.h"
#include "helper.h"
class CCommAdb : public ICommBase, public RefSelf
{
public:
	CCommAdb(LPVOID param);
	virtual ~CCommAdb();

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
	BOOL CheckIfSpecial( unsigned char rw, unsigned short addr, unsigned char* buffer, unsigned short len );
	//unsigned int ReadFromBoardTxRxBuff( unsigned char* pRead, unsigned short len );
private:
	IHalServiceInterface* m_HalInterface;
	unsigned char m_bDelaySync;

#ifdef _DEBUG
	unsigned char m_iDeviceIndex;
#endif
};