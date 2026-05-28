#pragma once
#include "ChipBase.h"
#include "ChipMcap.h"

class CChip810Imp : public CChipMcapImp, public ISMChip810Part
{
public:
	CChip810Imp();
	virtual ~CChip810Imp();

public:
	unsigned int SwitchMode( unsigned char modeType, unsigned short len ) ;
	unsigned int GetBootVersion( unsigned short* bootVer );
	unsigned int GetBootCheckSum( unsigned int* checkSum, unsigned int* omTime );
	unsigned int GetFirmWareConfig( unsigned char* configBuffer, unsigned short len );
	unsigned int GetOSCTrim( unsigned char* trim32k, unsigned char* trim96m, unsigned char* trim250m, unsigned char trim_mode, unsigned int osStd32k, unsigned int osStd96m, unsigned int osStd250m );
	unsigned int RockerCalibR(unsigned short offset1, unsigned short offset2, unsigned short offset3,  unsigned short offset4, unsigned short csum_ref1, unsigned short csum_ref2, unsigned char* cfg, unsigned short len) override;
	unsigned int GetShortData( unsigned short* sData, unsigned short len );
	unsigned int SetCommContext( const CtpHalCfg& halCfg );
	unsigned int BurnBootBin( unsigned int bootLen, unsigned int bootSVN = 0, unsigned short oscTrim = 0 );
	unsigned int BurnConfigBin( const unsigned char* config, unsigned short len );
	unsigned int EraseBurnSpace( unsigned int addr, unsigned int len );
	unsigned int SetClkInFctMode( unsigned short clk, unsigned char filterOff );
	unsigned int GetDifferMax(unsigned short frames, short* sData, unsigned short len );
	unsigned int GetCurrent810( short (&level)[2][3], unsigned short* activeCurrrent, unsigned short* sleepCurrent, unsigned short* deepCurrent, unsigned short* vbactiveCurrrent, unsigned short* vbsleepCurrent, unsigned short* vbdeepCurrent ) override;
	virtual unsigned int GetTouchPoint( unsigned char* pointBuffer, unsigned short* len );
	unsigned int GetRawData( short* rawdataBuffer, unsigned short len );
	virtual unsigned int ReadBurnSpace( unsigned int addr, unsigned char* buffer, unsigned int len ) override;
	virtual unsigned int WriteBurnSpace( unsigned int addr, const unsigned char* buffer, unsigned int len, unsigned char type )override;
};



class CChip810 : public ISMChip810
{
public:
	CChip810(){}
	virtual ~CChip810(){}
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
	inline unsigned int GetOSCTrim( unsigned char* trim32k, unsigned char* trim96m, unsigned char* trim250m, unsigned char trim_mode, unsigned int osStd32k, unsigned int osStd96m, unsigned int osStd250m ){
		return m_Impl.GetOSCTrim( trim32k, trim96m, trim250m, trim_mode, osStd32k, osStd96m, osStd250m );
	}
	inline unsigned int  RockerCalibR( unsigned short offset1, unsigned short offset2, unsigned short offset3,  unsigned short offset4, unsigned short csum_ref1, unsigned short csum_ref2, unsigned char* cfg, unsigned short len){
		return m_Impl.RockerCalibR( offset1, offset2, offset3, offset4, csum_ref1, csum_ref2, cfg, len);
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
	inline unsigned int GetCurrent810( short (&level)[2][3], unsigned short* activeCurrrent, unsigned short* sleepCurrent, unsigned short* deepCurrent, unsigned short* vbactiveCurrrent, unsigned short* vbsleepCurrent, unsigned short* vbdeepCurrent ){
		return m_Impl.GetCurrent810( level, activeCurrrent, sleepCurrent, deepCurrent,vbactiveCurrrent,vbsleepCurrent ,vbdeepCurrent );
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
	inline unsigned int BurnBootBin( unsigned int bootLen, unsigned int bootSVN = 0, unsigned short oscTrim = 0 ){
		return m_Impl.BurnBootBin( bootLen, bootSVN, oscTrim );
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
	inline unsigned int GetDifferMax(unsigned short frames, short* sData, unsigned short len ){
		return m_Impl.GetDifferMax(frames, sData, len);
	}
private:
	CChip810Imp m_Impl;
};

