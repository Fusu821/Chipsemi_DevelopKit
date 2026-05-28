#pragma once
#include "TestBase.h"

class CTest3536 : public CTestBase
{
//typedef TEST_ITEM_STATUS (CTest3536::*FunctionTest)( NativeTestItem& item );
public:
	CTest3536();
	virtual ~CTest3536();

public:
	void SetTestContext( unsigned char deviceNo, NativeTestInterface* native );

private:
	void ICArrayToSensorMatrix( unsigned short (&dataMappinged)[MAX_SCAP_ROW][MAX_SCAP_COL], unsigned short* const dataToMapping, unsigned int dataCnt, unsigned short maxRows, unsigned short maxCols );
	void ICMatrixToSensorMatrix( unsigned short (&dataMappinged)[MAX_SCAP_ROW][MAX_SCAP_COL],
		                unsigned short mappedRow,
		                unsigned short mappedCol,
		                const unsigned short (&dataToMapping)[MAX_SCAP_ROW][MAX_SCAP_COL],
		                unsigned short mappingRow,
		                unsigned short mappingCol );
	void SensorMatrixToIcMatrix( unsigned short (&dataMappinged)[MAX_SCAP_ROW][MAX_SCAP_COL],
		                unsigned short mappedRow,
			           	unsigned short mappedCol,
						const unsigned short (&dataToMapping)[MAX_SCAP_ROW][MAX_SCAP_COL],
						unsigned short mappingRow,
						unsigned short mappingCol );
	void VerTriangleCompareDataCalc( short (&iRC)[MAX_SCAP_ROW][MAX_SCAP_COL], double (&dwOut)[MAX_SCAP_ROW][MAX_SCAP_COL] );

	void HorTriangleCompareDataCalc( short (&iRC)[MAX_SCAP_ROW][MAX_SCAP_COL], double (&dwOut)[MAX_SCAP_ROW][MAX_SCAP_COL] );

	double GetHarfScreenNormalization( short (&dataCopy)[MAX_SCAP_ROW][MAX_SCAP_COL], unsigned char* pRows, int RowsCnt );

	bool GetHarfScreenNormalizationFactor( const unsigned short (&fastFSDRaw)[MAX_SCAP_ROW][MAX_SCAP_COL], const unsigned short (&slowFSDRaw)[MAX_SCAP_ROW][MAX_SCAP_COL],
		const unsigned short (&fastFSDBase)[MAX_SCAP_ROW][MAX_SCAP_COL], const unsigned short (&slowFSDBase)[MAX_SCAP_ROW][MAX_SCAP_COL], 
		unsigned char* pRows, int RowsCnt, int cols,
		double& dFactorFast, double& dFactorSlow );

	//double GetHarfScreenSortingMean( const unsigned short (&dataCopy)[MAX_SCAP_ROW][MAX_SCAP_COL], unsigned char* pRows, int RowsCnt );

	bool FSDPlusCheckMatched( int (&rcDeviation)[MAX_SCAP_ROW][MAX_SCAP_COL] );
private:
	unsigned int CheckFlashEraseOk();
	BOOL CheckTpBootSame();
	BOOL Ram_TestOk();
	BOOL CheckConfigSame( const unsigned char* pCfg, unsigned short len );
	unsigned int MakeTraceRecord();
	unsigned int FSD_Test( NativeTestItem& itemQuote );
	unsigned int FSD_TestEx( NativeTestItem& itemQuote, unsigned char testCnt );
	unsigned int FSDBK_Test( NativeTestItem& itemQuote );
	unsigned int FSDBK_TestEx( NativeTestItem& itemQuote, unsigned char testCnt );
	unsigned int OS_Test( NativeTestItem& itemQuote );
	unsigned int Boot_Test( NativeTestItem& itemQuote );
	unsigned int Config_Test( NativeTestItem& itemQuote );
	unsigned int ProjectCode_Test( NativeTestItem& itemQuote );
	unsigned int OSCTrim_Test( NativeTestItem& itemQuote );
	unsigned int Current_Test( NativeTestItem& itemQuote );
	unsigned int Current_TestEx( NativeTestItem& itemQuote, unsigned char times );
	unsigned int RawData_Test( NativeTestItem& itemQuote );
	unsigned int Noise_Test( NativeTestItem& itemQuote );
	unsigned int IOVoltage_Test( NativeTestItem& itemQuote );
	unsigned int Vp_Test( NativeTestItem& itemQuote );
	unsigned int Algorithm_Test( NativeTestItem& itemQuote );

	unsigned int MISC_Test( NativeTestItem& itemQuote );

	unsigned int ProblemJudgment(unsigned int addr, unsigned short plattenone,  unsigned short plattentwo);

	void PrepareSimulate( SimulateData& sm );
};