#pragma once
#include "TestBase.h"

class CTest3535 : public CTestBase
{
//typedef TEST_ITEM_STATUS (CTest3535::*FunctionTest)( NativeTestItem& item );
public:
	CTest3535();
	virtual ~CTest3535();

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
			           	unsigned short* mappedCols,
						const unsigned short (&dataToMapping)[MAX_SCAP_ROW][MAX_SCAP_COL],
						unsigned short mappingRow,
						unsigned short mappingCol );
	void VerTriangleCompareDataCalc( short (&iRC)[MAX_SCAP_ROW][MAX_SCAP_COL], double (&dwOut)[MAX_SCAP_ROW][MAX_SCAP_COL] );

	void HorTriangleCompareDataCalc( short (&iRC)[MAX_SCAP_ROW][MAX_SCAP_COL], double (&dwOut)[MAX_SCAP_ROW][MAX_SCAP_COL] );

	double GetHarfScreenNormalization( short (&dataCopy)[MAX_SCAP_ROW][MAX_SCAP_COL], unsigned char* pRows, int RowsCnt );

	//double GetHarfScreenSortingMean( const unsigned short (&dataCopy)[MAX_SCAP_ROW][MAX_SCAP_COL], unsigned char* pRows, int RowsCnt  );

	bool FSDPlusCheckMatched( int (&rcDeviation)[MAX_SCAP_ROW][MAX_SCAP_COL] );
private:
	BOOL CheckTpBootSame( unsigned char* pForceburn = NULL );
	unsigned int SetClkInFctMode( unsigned short clkDiv );
	BOOL CheckConfigSame( const unsigned char* pCfg, unsigned short len );
	BOOL CheckTail( unsigned int* pTail );
	unsigned int CheckAndBurnTail();
	unsigned int FindLastCfgAddress();
	unsigned int FSD_Test( NativeTestItem& itemQuote );
	unsigned int FSD_TestEx( NativeTestItem& itemQuote, unsigned char testCnt );
	unsigned int OS_Test( NativeTestItem& itemQuote );
	unsigned int Boot_Test( NativeTestItem& itemQuote );
	unsigned int Config_Test( NativeTestItem& itemQuote );
	unsigned int ProjectCode_Test( NativeTestItem& itemQuote );
	unsigned int Current_Test( NativeTestItem& itemQuote );
	unsigned int Current_TestEx( NativeTestItem& itemQuote, unsigned char times );
	unsigned int OSCTrim();
	unsigned int Base_Test( NativeTestItem& itemQuote );
	void PrepareSimulate( SimulateData& sm );
};