#pragma once
#include "ChipBase.h"
class CChipMcapImp : public CChipBaseImp, public ISMChipMcapPart
{
public: 
	CChipMcapImp();
	virtual ~CChipMcapImp();

	virtual unsigned int GetTxRxBufferAddr();

	unsigned int HalAccessMode( unsigned char accType = 0 );
	unsigned int WriteRegister( unsigned int address, unsigned int ucData );
	unsigned int ReadRegister( unsigned int address, unsigned int* pUcData );

 	unsigned int SwitchMode( unsigned char modeType, unsigned short len );
	unsigned int GetRawData( short* rawdataBuffer, unsigned short len );
	unsigned int GetTouchPoint( unsigned char* pointBuffer, unsigned short* len );
//	unsigned int BSPRWriteAndRead( unsigned char* writeBuffer, unsigned int iWrite, unsigned char* readBuffer, unsigned int iRead );
    unsigned int GetIoVoltage( unsigned int (&voltage)[2][10] );
	unsigned int GetCurrent( short (&level)[2][3], unsigned short* activeCurrrent, unsigned short* sleepCurrent, unsigned short* deepCurrent, unsigned short* idle );
	unsigned int SetConfigInFctMode( unsigned char* cfgBuffer, unsigned short len );
protected:
	unsigned int m_RawDataAddr;
	unsigned int m_DifferAddr;
	unsigned int m_BaseAddr;
};