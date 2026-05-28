#pragma once
#include "ChipBase.h"
class CChipScapImp : public CChipBaseImp, public ISMChipScapPart
{
public: 
	CChipScapImp();
	virtual ~CChipScapImp();

public:
	virtual unsigned int GetTxRxBufferAddr();
	//virtual unsigned int ReadBurnSpace( unsigned int addr, unsigned char* buffer, unsigned int len );
	//virtual unsigned int ReadCoreSpace( unsigned int addr, unsigned char* buffer, unsigned int len );
	//virtual unsigned int WriteCoreSpace( unsigned int addr, unsigned char* buffer, unsigned int len );
	//virtual unsigned int BSPRWrite( unsigned int addr, unsigned char* buffer, unsigned int len );
	//virtual unsigned int BSPRRead( unsigned int addr, unsigned char* buffer, unsigned int len );
	virtual unsigned int WriteRegister( unsigned int address, unsigned int ucData );
	virtual unsigned int ReadRegister( unsigned int address, unsigned int* pUcData );
	//virtual unsigned int HalAccessMode( unsigned char accType = 0 );
	virtual unsigned int GetCurrent( unsigned short cmd, short (&level)[2][2], unsigned short* workCurrrent, unsigned short* sleepCurrent );

	//virtual unsigned int CheckCatchBootToMtk( unsigned int addr, unsigned char* bootBuffer, unsigned int bootLen, LPCheckCatchBootCallBack onBootCallBack/* = NULL */);
};