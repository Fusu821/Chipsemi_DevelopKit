#pragma once
#include "SEMITouch.h"
#include "framework.h"
#include "onlinelog.h"
#include "../RefSelf.h"
#include "../Protocal/Protocal.h"
#include "helper.h"


class CChipBaseImp : public ISMChipBase, public RefSelf 
{
public:
	CChipBaseImp( );
	virtual ~CChipBaseImp();

public:
	LPVOID GetSRefInterface();
	virtual BOOL HaveTpLinked( unsigned int retry = 1 );
	void SetWrapperAddr( ISMChipWrapper* addr );
	virtual unsigned int SwitchMode( unsigned char modeType, unsigned short len = 0 );
	virtual unsigned int IncokeCommand( unsigned char command, unsigned int d0 = 0, unsigned short d1 = 0, unsigned short d2 = 0, unsigned char* retBuffer = NULL );
	virtual unsigned int GetOSCTrim( unsigned short* trim, unsigned int osStd );
	virtual unsigned int HalAccessMode( unsigned char accType = DIRECTLY_MODE );
	virtual unsigned int WriteRegister( unsigned int address, unsigned int ucData );
	virtual unsigned int ReadRegister( unsigned int address, unsigned int* pUcData );
	virtual unsigned int GetCurrent( unsigned short cmd, short (&level)[2][2], unsigned short* workCurrrent, unsigned short* sleepCurrent );
	virtual unsigned int GetTouchPoint( unsigned char* pointBuffer, unsigned short* len );
	virtual unsigned int GetRawData( short* rawdataBuffer, unsigned short len );
	virtual unsigned int ReadCoreSpace( unsigned int addr, unsigned char* buffer, unsigned int len );
	virtual unsigned int WriteCoreSpace( unsigned int addr, unsigned char* buffer, unsigned int len );
	virtual unsigned int ReadBurnSpace( unsigned int addr, unsigned char* buffer, unsigned int len );
	virtual unsigned int WriteBurnSpace( unsigned int addr, const unsigned char* buffer, unsigned int len, unsigned char type );
	virtual unsigned int EraseBurnSpace( unsigned int addr, unsigned int len );
	virtual unsigned int ReadMtkFlash( unsigned int addr, unsigned char* buffer, unsigned int len);
	virtual unsigned int CheckCatchBootToMtk( unsigned int addr, unsigned char* bootBuffer, unsigned int bootLen, LPCheckCatchBootCallBack onBootCallBack = NULL );
	virtual unsigned int SetClkInFctMode( unsigned short clkDiv, unsigned char filterOff );
	//virtual unsigned int BSPRWrite( unsigned char* writeBuffer, unsigned int iWrite );
	//virtual unsigned int BSPRRead( unsigned char* readBuffer, unsigned int iRead );
	virtual unsigned int BSPRWriteAndRead( unsigned char* writeBuffer, unsigned int iWrite, unsigned char* readBuffer, unsigned int iRead );
	virtual unsigned int GetTxRxBufferAddr();
	virtual unsigned int CheckCatchBootFromMtk( unsigned int checkaddr, unsigned char* bootBuffer, unsigned int bootLen, unsigned short bulkLen, BOOL& bBootSame );

	unsigned int WriteFlashData( unsigned char* pData, unsigned int addr, unsigned short len );
// 	unsigned int BSPRWrite( unsigned char* buffer, unsigned int len );
// 	unsigned int BSPRRead( unsigned char* wBuffer, unsigned int wLen, unsigned char* buffer, unsigned int len );
	
protected:
	unsigned char m_slaveAddr;
	ProtocalApi* m_ProtocalApi;
};