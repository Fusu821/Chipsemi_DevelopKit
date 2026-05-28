#pragma once
#include "TestBase.h"

#define FCT_ROM_VNM_REGION    (0x3E000)
#define ATE_ROM_VNM_REGION    (0x3F000)

#define USR_ROM_FACTORY_START (0x33000)

#define AddrMakeTraceRecord  108 * 1024
//#define	AddrOSCTrim          100 * 1024
#define	Addrbase             104 * 1024

#define FLASH_SAVE_SIG 0x43534843
#define CFG_CDSP_OFFSET (0x100)
#define CFG_CDSP_SIZE (0x300)

class CTest5562 : public CTestBase
{
//typedef TEST_ITEM_STATUS (CTest5562::*FunctionTest)( NativeTestItem& item );
public:
	CTest5562();
	virtual ~CTest5562();

public:
	void SetTestContext( unsigned char deviceNo, NativeTestInterface* native );

private:
	void ICArrayToSensorMatrix( unsigned short (&dataMappinged)[2][MAX_MCAP_COL], unsigned short* const dataToMapping, unsigned int dataCnt, unsigned short maxRows, unsigned short* pMaxCols );
// 	void ICMatrixToSensorMatrix( unsigned short (&dataMappinged)[MAX_MCAP_ROW][MAX_MCAP_COL],
// 		                unsigned short mappedRow,
// 		                unsigned short mappedCol,
// 		                const unsigned short (&dataToMapping)[MAX_MCAP_ROW][MAX_MCAP_COL],
// 		                unsigned short mappingRow,
// 		                unsigned short mappingCol );
// 	void SensorMatrixToIcMatrix( unsigned short (&dataMappinged)[MAX_MCAP_ROW][MAX_MCAP_COL],
// 		                unsigned short mappedRow,
// 			           	unsigned short mappedCol,
// 						const unsigned short (&dataToMapping)[MAX_MCAP_ROW][MAX_MCAP_COL],
// 						unsigned short mappingRow,
// 						unsigned short mappingCol );
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
	unsigned int ScapRawData_Test( NativeTestItem& itemQuote );
	unsigned int STC_Test( NativeTestItem& itemQuote );
	unsigned int MCapRawData_Test( NativeTestItem& itemQuote );
	unsigned int Short_Test( NativeTestItem& itemQuote );
	unsigned int FRT_Test( NativeTestItem& itemQuote );
	unsigned int IOVoltage_Test( NativeTestItem& itemQuote );
	unsigned int VT_Test( NativeTestItem& itemQuote );
	unsigned int Base_Test( NativeTestItem& itemQuote );
	unsigned int Noise_Test( NativeTestItem& itemQuote );
	unsigned int MISC_Test( NativeTestItem& itemQuote );
	void PrepareSimulate( SimulateData& sm );
	unsigned int FSD_Test( NativeTestItem& itemQuote );
	unsigned int WBase_Test( NativeTestItem& itemQuote );
private: 
	unsigned int SetClkInFctMode( unsigned short clkDiv );
	unsigned int MakeTraceRecord();
	unsigned int AverageData(short* buff, int len);

	//short tmp_1_mcapdata[MAX_MCAP_ROW][MAX_MCAP_COL];
	//short tmp_2_mcapdata[MAX_MCAP_ROW][MAX_MCAP_COL];
	//short tmp_3_mcapdata[MAX_MCAP_ROW][MAX_MCAP_COL];
	//short tmp_4_mcapdata[MAX_MCAP_ROW][MAX_MCAP_COL];
	//short tmp_5_mcapdata[MAX_MCAP_ROW][MAX_MCAP_COL];
	//short tmp_6_mcapdata[MAX_MCAP_ROW][MAX_MCAP_COL];
	//short tmp_7_mcapdata[MAX_MCAP_ROW][MAX_MCAP_COL];
	//short tmp_8_mcapdata[MAX_MCAP_ROW][MAX_MCAP_COL];
};