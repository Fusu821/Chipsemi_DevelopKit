#pragma once
#include "TestBase.h"

#define AddrMakeTraceRecord  108 * 1024
#define	AddrOSCTrim          100 * 1024
#define	Addrbase             104 * 1024

class CTest5472 : public CTestBase
{
//typedef TEST_ITEM_STATUS (CTest5472::*FunctionTest)( NativeTestItem& item );
public:
	CTest5472();
	virtual ~CTest5472();

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
private: 
	unsigned int SetClkInFctMode( unsigned short clkDiv );
	unsigned int MakeTraceRecord();
};