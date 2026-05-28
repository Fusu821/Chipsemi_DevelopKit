#pragma once
#include "TestBase.h"
#include <vector>

#include "CRockerCalibration.h"

#define TCP_CALIBA_ADDR_810       (29 * 1024 + 0)

#define VCM_ATE_RC_ADDR            (36 * 1024 + 0)

#define AddrMakeTraceRecord  108 * 1024
//#define	AddrOSCTrim          100 * 1024
#define	Addrbase             104 * 1024

#define BIT0                            0x1
#define BIT1                            0x2
#define BIT2                            0x4
#define BIT3                            0x8
#define BIT4                            0x10
#define BIT5                            0x20
#define BIT6                            0x40
#define BIT7                            0x80
#define BIT8                            0x100
#define BIT9                            0x200
#define BIT10                           0x400
#define BIT11                           0x800
#define BIT12                           0x1000
#define BIT13                           0x2000
#define BIT14                           0x4000
#define BIT15                           0x8000
#define BIT16                           0x10000
#define BIT17                           0x20000
#define BIT18                           0x40000
#define BIT19                           0x80000
#define BIT20                           0x100000
#define BIT21                           0x200000
#define BIT22                           0x400000
#define BIT23                           0x800000
#define BIT24                           0x1000000
#define BIT25                           0x2000000
#define BIT26                           0x4000000
#define BIT27                           0x8000000
#define BIT28                           0x10000000
#define BIT29                           0x20000000
#define BIT30                           0x40000000
#define BIT31                           0x80000000

#define BIT(n)                  		( 1<<(n) )
#define BIT_MASK_LEN(len)               (BIT(len)-1)
#define BIT_MASK(start, len)    (BIT_MASK_LEN(len) << (start) )
#define BM_FLIP(x, mask)      	( (x) ^=  (mask) )
#define BIT_FLIP(x, n)   		((x) ^= BIT(n))
#define BIT_PREP(x, start, len) ((x)<<(start) & BIT_MASK(start, len))
#define BIT_GET(x, start, len)  (((x) >> (start)) & BIT_MASK_LEN(len))

#define BIT_GET_LOW(x, len)   	((x) & BIT_MASK_LEN(len))

#define BIT_MERGE(y, x, start, len)    ( y = ((y) &~ BIT_MASK(start, len)) | BIT_PREP(x, start, len) )

#define BIT_MERGE(y, x, start, len)    ( y = ((y) &~ BIT_MASK(start, len)) | BIT_PREP(x, start, len) )

typedef struct _rockerCali810
{
	short rocker_calibXN;
	short rocker_calibXC;
	short rocker_calibXP;
	short rocker_calibYN;
	short rocker_calibYC;
	short rocker_calibYP;

	short rocker_offset1;
	short rocker_offset2;
	short rocker_offset3;
	short rocker_offset4;

	unsigned short csum_ref1;
	unsigned short csum_ref2;

	unsigned short register_0xd6;

	unsigned short tag;
	unsigned short crc;

}RockerCali810;

typedef struct _ois_chip_calib_810
{
	unsigned char  ate_year;   
	unsigned char  ate_month;  
	unsigned char  ate_day;
	unsigned char  ate_hour;
	unsigned char  ate_minute;
	unsigned char  ate_second; 

	unsigned char  ate_ipoly5u_trim;   
	unsigned char  ate_cvdd12_trim;  
	unsigned char  ate_lccvdd12_trim;
	unsigned char  ate_dcdc2p6_L_trim;
	unsigned char  ate_dcdc3v_H_trim;
	unsigned char  ate_hv30_trim;
	unsigned char  ate_ldo25_trim; 

	unsigned char  ate_osc32k_trim;
	unsigned char  ate_osc24m_trim;
	unsigned char  ate_osc48m_trim;
	unsigned char  ate_cintsel_trim;
	unsigned char  ate_na;

	unsigned short  ate_cap_1pf_rx0;
	unsigned short  ate_cap_1pf_rx1;
	unsigned short  ate_cap_1pf_rx2;
	unsigned short  ate_cap_1pf_rx3;

	unsigned short  ate_tempsensor;

	unsigned char  ate_site_number;
	unsigned char  ate_write_flag;
}ois_chip_calib_810;

class CTest810 : public CTestBase
{
//typedef TEST_ITEM_STATUS (CTest810::*FunctionTest)( NativeTestItem& item );
public:
	CTest810();
	virtual ~CTest810();

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
	unsigned int TP_RemoveTest( NativeTestItem& itemQuote ) override;
	unsigned int TP_WaitTest( NativeTestItem& itemQuote ) override;
	bool HaveTpLinked_810();
private:
	BOOL CheckFlashEraseOk();
	BOOL CheckTpBootSame();
	BOOL CheckConfigSame( const unsigned char* pWCfg, const unsigned char* pRCfg,unsigned short len );
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
	unsigned int CVDiffY_Test( NativeTestItem& itemQuote );
	unsigned int CVDiffX_Test( NativeTestItem& itemQuote );
	unsigned int Base_Test( NativeTestItem& itemQuote );
	unsigned int SDRockerCalib_Test( NativeTestItem& itemQuote );
	unsigned int Noise_Test( NativeTestItem& itemQuote );
	unsigned int MISC_Test( NativeTestItem& itemQuote );
	unsigned int Graph_Test( NativeTestItem& itemQuote );
	unsigned int INT_Test( NativeTestItem& itemQuote );
	void PrepareSimulate( SimulateData& sm );
	bool Tick(ItemNotifyer&itemNotify);
	bool Tick(ItemNotifyer&itemNotify,int time);
	bool Judgmentconditions(int pframes, int pcValue, int pldownValue, int plupValue,int psValue);

	void InitRockerCali();
	
	unsigned short Chga810CalcCheckSumU16(unsigned short* buf, unsigned short length);

	unsigned short reg16_bit_range(unsigned short reg_v, unsigned short val, unsigned short start, unsigned short end);

	virtual void ForcePaintFlow() override;

private: 
	unsigned int SetClkInFctMode( unsigned short clkDiv );
	unsigned int MakeTraceRecord();
	int Iframes;
	int IfristValue;
	int Itick;

	RockerCali810 rockerCali;

	bool cfg_complete;

};

