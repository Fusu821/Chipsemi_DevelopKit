#pragma once
#include "ChipBase.h"
#include "ChipMcap.h"

class CChip5816Imp : public CChipMcapImp, public ISMChip5816Part
{
public:
	CChip5816Imp();
	virtual ~CChip5816Imp();

public:
	unsigned int GetBootVersion( unsigned short* bootVer );
	unsigned int GetBootCheckSum( unsigned int* checkSum, unsigned int* omTime );
	unsigned int GetFirmWareConfig( unsigned char* configBuffer, unsigned short len );
	unsigned int GetOSCTrim( unsigned char* trim32k, unsigned char* trim24m, unsigned int osStd32k, unsigned int osStd24m );
	unsigned int GetShortData( unsigned short* sData, unsigned short len );
	unsigned int SetCommContext( const CtpHalCfg& halCfg );
	unsigned int BurnBootBin( unsigned int bootLen, UINT64 VidPid = 0, unsigned int oscTrim = 0, long long icID = 0 );
	unsigned int BurnConfigBin( const unsigned char* config, unsigned short len );
	unsigned int EraseBurnSpace( unsigned int addr, unsigned int len );
	//unsigned int GetIoVoltage( unsigned int (&voltage)[2][8] );
	//unsigned int GetCurrent( unsigned short* activeCurrrent, unsigned short* sleepCurrent, unsigned short* deepCurrent );
	unsigned int SetClkInFctMode( unsigned short clk, unsigned char filterOff );
};
class CChip5816 : public ISMChip5816
{
public:
	CChip5816(){}
	virtual ~CChip5816(){}

public:
	virtual LPVOID GetSRefInterface(){
		return m_Impl.GetSRefInterface(); 
	}
	inline BOOL HaveTpLinked( unsigned int retry = 1 ){
		return m_Impl.HaveTpLinked( retry );
	}
	inline unsigned int ReadCoreSpace( unsigned int addr, unsigned char* buffer, unsigned int len ){
		return m_Impl.ReadCoreSpace( addr, buffer, len );
	}
	inline unsigned int SetCommContext( const CtpHalCfg& halCfg ){
		return m_Impl.SetCommContext( halCfg );
	}
	inline unsigned int SwitchMode( unsigned char modeType, unsigned short len = 0 ){
		return m_Impl.SwitchMode( modeType, len );
	}
	inline unsigned int IncokeCommand( unsigned char command, unsigned int d0 = 0, unsigned short d1 = 0, unsigned short d2 = 0, unsigned char* retBuffer = NULL ){
		return m_Impl.IncokeCommand( command, d0, d1, d2, retBuffer );
	}
	inline unsigned int GetOSCTrim( unsigned char* trim32k, unsigned char* trim24m, unsigned int osStd32k, unsigned int osStd24m ){
		return m_Impl.GetOSCTrim( trim32k, trim24m, osStd32k, osStd24m );
	}
	inline unsigned int HalAccessMode( unsigned char accType = DIRECTLY_MODE ){
		return m_Impl.HalAccessMode( accType );
	}
	inline unsigned int WriteRegister( unsigned int address, unsigned int ucData ){
		return m_Impl.WriteRegister( address, ucData );
	}
	inline unsigned int ReadRegister( unsigned int address, unsigned int* pUcData ){
		return m_Impl.ReadRegister( address, pUcData );
	}
	inline unsigned int GetCurrent( short (&level)[2][3], unsigned short* activeCurrrent, unsigned short* sleepCurrent, unsigned short* deepCurrent, unsigned short* idle ){
		return m_Impl.GetCurrent( level, activeCurrrent, sleepCurrent, deepCurrent, idle );
	}
	inline unsigned int GetTouchPoint( unsigned char* pointBuffer, unsigned short* len ){
		return m_Impl.GetTouchPoint( pointBuffer, len );
	}
	inline unsigned int GetRawData( short* rawdataBuffer, unsigned short len ){
		return m_Impl.GetRawData( rawdataBuffer, len );
	}
	inline unsigned int WriteCoreSpace( unsigned int addr, unsigned char* buffer, unsigned int len ){
		return m_Impl.WriteCoreSpace( addr, buffer, len );
	}
	inline unsigned int ReadBurnSpace( unsigned int addr, unsigned char* buffer, unsigned int len ){
		return m_Impl.ReadBurnSpace( addr, buffer, len );
	}
	inline unsigned int ReadMtkFlash( unsigned int addr, unsigned char* buffer, unsigned int len){
		return m_Impl.ReadMtkFlash( addr, buffer, len );
	}
	inline unsigned int WriteBurnSpace( unsigned int addr, const unsigned char* buffer, unsigned int len, unsigned char type ){
		return m_Impl.WriteBurnSpace( addr, buffer, len, type );
	}
	inline unsigned int EraseBurnSpace( unsigned int addr, unsigned int len ){
		return m_Impl.EraseBurnSpace( addr, len );
	}
	inline unsigned int CheckCatchBootToMtk( unsigned int addr, unsigned char* bootBuffer, unsigned int bootLen, LPCheckCatchBootCallBack onBootCallBack = NULL ){
		return m_Impl.CheckCatchBootToMtk( addr, bootBuffer, bootLen, onBootCallBack );
	}
	inline unsigned int SetClkInFctMode( unsigned short clkDiv, unsigned char filterOff ){
		return m_Impl.SetClkInFctMode(clkDiv, filterOff );
	}
// 	inline unsigned int BSPRWrite( unsigned char* writeBuffer, unsigned int iWrite ){
// 		return m_Impl.BSPRWrite( writeBuffer, iWrite );
// 	}
// 	inline unsigned int BSPRRead( unsigned char* readBuffer, unsigned int iRead ){
// 		return m_Impl.BSPRRead( readBuffer, iRead );
// 	}
	inline unsigned int BSPRWriteAndRead( unsigned char* writeBuffer, unsigned int iWrite, unsigned char* readBuffer, unsigned int iRead ){
		return m_Impl.BSPRWriteAndRead( writeBuffer, iWrite, readBuffer, iRead );
	}
	//////////////////////////////////////////////////////////////////////////
	inline unsigned int GetShortData( unsigned short* sData, unsigned short len ){
		return m_Impl.GetShortData( sData, len );
	}
	inline unsigned int GetBootVersion( unsigned short* bootVer ){
		return m_Impl.GetBootVersion( bootVer );
	}
	inline unsigned int GetBootCheckSum( unsigned int* checkSum, unsigned int* omTime ){
		return m_Impl.GetBootCheckSum( checkSum, omTime );
	}
	inline unsigned int GetFirmWareConfig( unsigned char* configBuffer, unsigned short len ){
		return m_Impl.GetFirmWareConfig( configBuffer, len );
	}
	inline unsigned int BurnBootBin( unsigned int bootLen, UINT64 VidPid = 0, unsigned int oscTrim = 0, long long icID = 0 ){
		return m_Impl.BurnBootBin( bootLen, VidPid, oscTrim, icID );
	}
	inline unsigned int BurnConfigBin( const unsigned char* config, unsigned short len ){
		return m_Impl.BurnConfigBin( config, len );
	}
	inline unsigned int GetIoVoltage( unsigned int (&voltage)[2][10] ){
		return m_Impl.GetIoVoltage( voltage );
	}
	inline unsigned int SetConfigInFctMode( unsigned char* cfgBuffer, unsigned short len ){
		return m_Impl.SetConfigInFctMode( cfgBuffer, len );
	}
private:
	CChip5816Imp m_Impl;
};