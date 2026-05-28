#pragma once
#include "TestBase.h"

#define CHUF310_X (80)
#define CHUF310_Y (80)
#define CHUF310_N (CHUF310_X*CHUF310_Y)

#define FCT_ROM_VNM_REGION    (0x3E000)
#define ATE_ROM_VNM_REGION    (0x3F000)

#define USR_ROM_FACTORY_START (0x33000)

#define AddrMakeTraceRecord  108 * 1024
#define	Addrbase             104 * 1024

#define FLASH_SAVE_SIG 0x43534843
#define CFG_CDSP_OFFSET (0x100)
#define CFG_CDSP_SIZE (0x300)

class CTest310 : public CTestBase
{
public:
    CTest310();
    virtual ~CTest310();

public:
    void SetTestContext( unsigned char deviceNo, NativeTestInterface* native );

private:
    void ICArrayToSensorMatrix( unsigned short (&dataMappinged)[2][MAX_MCAP_COL], unsigned short* const dataToMapping, unsigned int dataCnt, unsigned short maxRows, unsigned short* pMaxCols );

    void VerTriangleCompareDataCalc( short (&iRC)[MAX_MCAP_ROW][MAX_MCAP_COL], double (&dwOut)[MAX_MCAP_ROW][MAX_MCAP_COL] );

    void HorTriangleCompareDataCalc( short (&iRC)[MAX_MCAP_ROW][MAX_MCAP_COL], double (&dwOut)[MAX_MCAP_ROW][MAX_MCAP_COL] );

    double GetHarfScreenNormalization( short (&dataCopy)[MAX_MCAP_ROW][MAX_MCAP_COL], unsigned char* pRows, int RowsCnt );

    bool GetHarfScreenNormalizationFactor( const unsigned short (&fastFSDRaw)[MAX_MCAP_ROW][MAX_MCAP_COL], const unsigned short (&slowFSDRaw)[MAX_MCAP_ROW][MAX_MCAP_COL],
        const unsigned short (&fastFSDBase)[MAX_MCAP_ROW][MAX_MCAP_COL], const unsigned short (&slowFSDBase)[MAX_MCAP_ROW][MAX_MCAP_COL], 
        unsigned char* pRows, int RowsCnt, int cols,
        double& dFactorFast, double& dFactorSlow );

    //double GetHarfScreenSortingMean( const unsigned short (&dataCopy)[MAX_MCAP_ROW][MAX_MCAP_COL], unsigned char* pRows, int RowsCnt );

    bool FSDPlusCheckMatched( int (&rcDeviation)[MAX_MCAP_ROW][MAX_MCAP_COL] );
    unsigned int WorkForGraphMode( bool bEnterGraphing = false );
    //unsigned int TP_RemoveTest( NativeTestItem& itemQuote ) override;
    //unsigned int TP_WaitTest( NativeTestItem& itemQuote ) override;
    //bool HaveTpLinked_CHCT550();

    void ICArrayToSensorMatrixVT(unsigned short (&dataOn)[1][MAX_MCAP_COL],unsigned short (&dataOff)[1][MAX_MCAP_COL], unsigned short* const dataToMapping);
private:
    BOOL CheckFlashEraseOk();
    BOOL CheckTpBootSame();
    BOOL CheckConfigSame( const unsigned char* pCfg, unsigned short len );
    //unsigned int FSD_Test( NativeTestItem& itemQuote );
    //unsigned int FSD_TestEx( NativeTestItem& itemQuote, unsigned char testCnt );
    //unsigned int OS_Test( NativeTestItem& itemQuote );
    unsigned int Boot_Test( NativeTestItem& itemQuote );
    unsigned int Config_Test( NativeTestItem& itemQuote );
    unsigned int ProjectCode_Test( NativeTestItem& itemQuote );
    unsigned int OSCTrim_Test( NativeTestItem& itemQuote );
    unsigned int Current_Test( NativeTestItem& itemQuote );
    unsigned int Current_TestEx( NativeTestItem& itemQuote );
    //unsigned int Base_Test( NativeTestItem& itemQuote );
    //unsigned int ScapRawData_Test( NativeTestItem& itemQuote );
    //unsigned int STC_Test( NativeTestItem& itemQuote );
    //unsigned int MCapRawData_Test( NativeTestItem& itemQuote );
    unsigned int Temperature_Test( NativeTestItem& itemQuote );
    unsigned int Otp_Test( NativeTestItem& itemQuote );
    unsigned int Communication_Test( NativeTestItem& itemQuote );
    unsigned int Pressure_Contact_Test( NativeTestItem& itemQuote );
    unsigned int ADC_Test( NativeTestItem& itemQuote );
	unsigned int SRF_Test( NativeTestItem& itemQuote );
	unsigned int FlyTime_Test( NativeTestItem& itemQuote );
    unsigned int PixelDefect_Test( NativeTestItem& itemQuote );
    unsigned int FRT_Test( NativeTestItem& itemQuote );
    unsigned int IOVoltage_Test( NativeTestItem& itemQuote );
    //unsigned int VT_Test( NativeTestItem& itemQuote );
    //unsigned int Base_Test( NativeTestItem& itemQuote );
    unsigned int Noise_Test( NativeTestItem& itemQuote );
    //unsigned int MISC_Test( NativeTestItem& itemQuote );
    void PrepareSimulate( SimulateData& sm );
    //unsigned int FSD_Test( NativeTestItem& itemQuote );
    //unsigned int WBase_Test( NativeTestItem& itemQuote );
private: 
    unsigned int SetClkInFctMode( unsigned short clkDiv );
    unsigned int MakeTraceRecord();
    unsigned int AverageData(short* buff, int len);
	fct_osc_temp_trim_310 m_FoTrim;

};