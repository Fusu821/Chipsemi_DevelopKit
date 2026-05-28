#pragma once
#include "ChipBase.h"
#include "ChipMcap.h"

class CChip310Imp : public CChipMcapImp, public ISMChip310Part
{
public:
    CChip310Imp();
    virtual ~CChip310Imp();

public:
    unsigned int SwitchMode( unsigned char modeType, unsigned short len ) ;
    unsigned int GetBootVersion( unsigned short* bootVer );
    unsigned int GetBootCheckSum( unsigned int* checkSum, unsigned int* omTime );
    unsigned int GetFirmWareConfig( unsigned char* configBuffer, unsigned short len );
    unsigned int GetOSCTrim(fct_osc_temp_trim_310& fo_trim, unsigned int osStd52mNo1, unsigned int osStd52mNo2, unsigned int osStd52mNo3, unsigned char ischeck);
    unsigned int GetShortData( unsigned short* sData, unsigned short len );
    unsigned int SetCommContext( const CtpHalCfg& halCfg );
    unsigned int BurnBootBin( unsigned int bootLen, unsigned int bootSVN = 0, unsigned short oscTrim = 0 );
    unsigned int BurnConfigBin( const unsigned char* config, unsigned short len );
    unsigned int EraseBurnSpace( unsigned int addr, unsigned int len );
    unsigned int SetClkInFctMode( unsigned short clk, unsigned char filterOff );
    unsigned int GetDifferMax(unsigned short frames, short* sData, unsigned short len );
    unsigned int GetCurrent310( short (&level)[2][3], unsigned short* activeCurrrent, unsigned short* sleepCurrent, unsigned short* deepCurrent, unsigned short* vbactiveCurrrent, unsigned short* vbsleepCurrent, unsigned short* vbdeepCurrent ) override;
    unsigned int GetTempData( unsigned short* location1, unsigned short* location2, unsigned short* location3,unsigned short* location4) ;
	unsigned int GetPixelDefectData(signed short* sData0,signed short* sData1, signed short* sData2, unsigned short len);
	unsigned int GetFlyTimeData(signed short* sData, unsigned short len);
	unsigned int GetSRFData(signed short* sData, unsigned short len);
	unsigned int GetADCData(signed short* sData, unsigned short len, unsigned char mode);
	unsigned int GetOTPStatus(unsigned int* ate_flag, unsigned int* fct_flag);
	unsigned int GetNewBootCheckSum( unsigned int* checkSum, unsigned int* omTime, unsigned int* bootloadercheckSum) override;

    virtual unsigned int GetTouchPoint( unsigned char* pointBuffer, unsigned short* len );
    unsigned int GetRawData( short* rawdataBuffer, unsigned short len );
    virtual unsigned int ReadBurnSpace( unsigned int addr, unsigned char* buffer, unsigned int len ) override;
    virtual unsigned int WriteBurnSpace( unsigned int addr, const unsigned char* buffer, unsigned int len, unsigned char type )override;
    unsigned int GetTrimeDosc(fct_osc_temp_trim_310& fo_trim) override;
};



class CChip310 : public ISMChip310
{
public:
    CChip310(){}
    virtual ~CChip310(){}
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
    inline unsigned int GetOSCTrim(fct_osc_temp_trim_310& fo_trim, unsigned int osStd52mNo1, unsigned int osStd52mNo2, unsigned int osStd52mNo3, unsigned char ischeck){
        return m_Impl.GetOSCTrim(fo_trim, osStd52mNo1, osStd52mNo2, osStd52mNo3, ischeck );
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
    inline unsigned int GetCurrent310( short (&level)[2][3], unsigned short* activeCurrrent, unsigned short* sleepCurrent, unsigned short* deepCurrent, unsigned short* vbactiveCurrrent, unsigned short* vbsleepCurrent, unsigned short* vbdeepCurrent ){
        return m_Impl.GetCurrent310( level, activeCurrrent, sleepCurrent, deepCurrent,vbactiveCurrrent,vbsleepCurrent ,vbdeepCurrent );
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
    inline unsigned int BSPRWriteAndRead( unsigned char* writeBuffer, unsigned int iWrite, unsigned char* readBuffer, unsigned int iRead ){
        return m_Impl.BSPRWriteAndRead( writeBuffer, iWrite, readBuffer, iRead );
    }
    inline unsigned int GetShortData( unsigned short* sData, unsigned short len ){
        return m_Impl.GetShortData( sData, len );
    }
    inline unsigned int GetBootVersion( unsigned short* bootVer ){
        return m_Impl.GetBootVersion( bootVer );
    }
    inline unsigned int GetBootCheckSum( unsigned int* checkSum, unsigned int* omTime ){
        return m_Impl.GetBootCheckSum( checkSum, omTime );
    }
    inline unsigned int GetNewBootCheckSum( unsigned int* checkSum, unsigned int* omTime , unsigned int* bootloadercheckSum){
        return m_Impl.GetNewBootCheckSum( checkSum, omTime, bootloadercheckSum );
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
    inline unsigned int GetTrimeDosc(fct_osc_temp_trim_310& fo_trim){
        return m_Impl.GetTrimeDosc(fo_trim);
    }
	inline unsigned int GetTempData( unsigned short* location1, unsigned short* location2, unsigned short* location3,unsigned short* location4){
        return m_Impl.GetTempData( location1, location2,  location3,  location4);
    }
	inline unsigned int GetPixelDefectData(signed short* sData0,signed short* sData1, signed short* sData2, unsigned short len){
        return m_Impl.GetPixelDefectData( sData0, sData1, sData2 ,  len);
    }
	inline unsigned int GetFlyTimeData(signed short* sData, unsigned short len){
        return m_Impl.GetFlyTimeData( sData, len);
    }
	inline unsigned int GetSRFData(signed short* sData, unsigned short len){
        return m_Impl.GetSRFData( sData, len);
    }
	inline unsigned int GetADCData(signed short* sData, unsigned short len, unsigned char mode){
        return m_Impl.GetADCData( sData, len, mode);
    }
	inline unsigned int GetOTPStatus(unsigned int* ate_flag, unsigned int* fct_flag){
        return m_Impl.GetOTPStatus( ate_flag, fct_flag);
    }

private:
    CChip310Imp m_Impl;
};

