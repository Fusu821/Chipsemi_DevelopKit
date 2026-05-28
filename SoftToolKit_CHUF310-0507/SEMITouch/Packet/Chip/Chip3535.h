#pragma once
#include "ChipScap.h"

class CChip3535Imp : public CChipScapImp, public ISMChip3535Part
{
public:
	CChip3535Imp();
	virtual ~CChip3535Imp();

public:
	unsigned int SwitchMode( unsigned char modeType, unsigned short len = 0 );
	unsigned int GetBootVersion( unsigned short* bootVer );
	unsigned int GetBootCheckSum( unsigned int* checkSum, unsigned int* omTime, unsigned int* marginCheck, unsigned int* normalCheck );
	unsigned int GetFirmWareConfig( unsigned int addr, unsigned char* configBuffer, unsigned short len );
	unsigned int GetOSCTrim( unsigned short* trim, unsigned int osStd );
	unsigned int GetOSData( unsigned char integral, unsigned char scale_a, unsigned char scale_b, unsigned short* osData, unsigned short len );
	unsigned int GetFSDFastData( unsigned short fclkDiv, unsigned short integral, unsigned short* clkData, unsigned short buffersize, unsigned char fclkCnt = 4 );
	unsigned int GetFSDSlowData( unsigned short sclkDiv, unsigned short integral, unsigned short* clkData, unsigned short buffersize, unsigned char sclkCnt = 4 );
	unsigned int SetCommContext( const CtpHalCfg& halCfg );
	unsigned int BurnBootBin( unsigned int bootLen, unsigned int bootSVN = 0, unsigned short oscTrim = 0, unsigned char reBurn = 0 );
	unsigned int BurnConfigBin( unsigned int addr, const unsigned char* config, unsigned short len );
	unsigned int SetClkInFctMode( unsigned short clkDiv, unsigned char filterOff );
	unsigned int FindLastCfgAddress();
	unsigned int CheckOtp(unsigned short* checknum);
};
class CChip3535 : public ISMChip3535
{
public:
	CChip3535(){}
	virtual ~CChip3535(){}

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
	inline unsigned int GetOSCTrim( unsigned short* trim, unsigned int osStd ){
		return m_Impl.GetOSCTrim( trim, osStd );
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
	inline unsigned int GetCurrent( unsigned short cmd, short (&level)[2][2], unsigned short* workCurrrent, unsigned short* sleepCurrent ){
		return m_Impl.GetCurrent( cmd, level, workCurrrent, sleepCurrent );
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
		return m_Impl.SetClkInFctMode( clkDiv, filterOff );
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
	inline unsigned int GetOSData( unsigned char integral, unsigned char scale_a, unsigned char scale_b, unsigned short* osData, unsigned short len ){
		return m_Impl.GetOSData( integral, scale_a, scale_b, osData, len );
	}
	inline unsigned int GetFSDFastData( unsigned short fclkDiv, unsigned short integral, unsigned short* fsdData, unsigned short buffersize, unsigned char fclkCnt = 4 ){
		return m_Impl.GetFSDFastData( fclkDiv, integral, fsdData, buffersize, fclkCnt );
	}
	inline unsigned int GetFSDSlowData( unsigned short fclkDiv, unsigned short integral, unsigned short* fsdData, unsigned short buffersize, unsigned char fclkCnt = 4 ){
		return m_Impl.GetFSDSlowData( fclkDiv, integral, fsdData, buffersize, fclkCnt );
	}
	inline unsigned int GetBootVersion( unsigned short* bootVer ){
		return m_Impl.GetBootVersion( bootVer );
	}
	inline unsigned int GetBootCheckSum( unsigned int* checkSum, unsigned int* omTime, unsigned int* marginCheck, unsigned int* normalCheck ){
		return m_Impl.GetBootCheckSum( checkSum, omTime, marginCheck, normalCheck );
	}
	inline unsigned int GetFirmWareConfig( unsigned int addr, unsigned char* configBuffer, unsigned short len ){
		return m_Impl.GetFirmWareConfig( addr, configBuffer, len );
	}
	inline unsigned int BurnBootBin( unsigned int bootLen, unsigned int bootSVN = 0, unsigned short oscTrim = 0, unsigned char reBurn = 0 ){
		return m_Impl.BurnBootBin( bootLen, bootSVN, oscTrim, reBurn );
	}
	inline unsigned int BurnConfigBin( unsigned int addr, const unsigned char* config, unsigned short len ){
		return m_Impl.BurnConfigBin( addr, config, len );
	}
	inline unsigned int FindLastCfgAddress(){
		return m_Impl.FindLastCfgAddress();
	}
	inline unsigned int CheckOtp(unsigned short* checknum){
		return m_Impl.CheckOtp(checknum);
	}
private:
	CChip3535Imp m_Impl;
};