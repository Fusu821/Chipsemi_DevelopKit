#include "checksum.h"
#include "Test3535.h"
#include "../Config/Config3535.h"

#include <list>
//#include <numeric>

#define MAX_SCAP_BUFFER_3535         38

extern CConfig* G_XMLConfig;
#define pCfg3535   (( const CConfig3535*)G_XMLConfig)
REGIST_RUNTIME_CLASS(TEST_TYPE, (TEST_TYPE)SEMI_IC_3535, CTest3535)


CTest3535::CTest3535()
:CTestBase()
{

}
CTest3535::~CTest3535()
{
	
}
void CTest3535::SetTestContext( unsigned char deviceNo, NativeTestInterface* native )
{
	//m_listTestItems.clear();
	CTestBase::SetTestContext( deviceNo, native );

	int indexSel = 0;  //mtk = 0

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_MTK_CONNECT;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("MTK"), lengthof(_T("MTK")));
		info.bSelected = true;
		info.jumpIfNG = false;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTestBase>( this, &CTestBase::MTKConnectTest );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_TP_WAIT;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("Waiting"), lengthof(_T("Waiting")));
		info.bSelected = pCfg3535->way_to_start == START_BY_AUTO;
		info.jumpIfNG = false;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTestBase>( this, &CTestBase::TP_WaitTest );
	}
	//////////////////////////////////////////////////////////////////////////

	if( pCfg3535->int_selected )
	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_INT_TEST;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("INT"), lengthof(_T("INT")));
		info.bSelected = pCfg3535->int_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest3535>( this, &CTest3535::INT_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_RESET_TEST;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("Reset"), lengthof(_T("Reset")));
		info.bSelected = pCfg3535->reset_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest3535>( this, &CTest3535::Reset_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_OS_TEST_3535;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("OS"), lengthof(_T("OS")));
		info.bSelected = pCfg3535->os_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest3535>( this, &CTest3535::OS_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_BOOT_TEST;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("Boot"), lengthof(_T("Boot")));
		info.bSelected = pCfg3535->boot_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest3535>( this, &CTest3535::Boot_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_CFG_TEST;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("Config"), lengthof(_T("Config")));
		info.bSelected = pCfg3535->config_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest3535>( this, &CTest3535::Config_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_PROJECT_CODE;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("Project"), lengthof(_T("Project")));
		info.bSelected = 1;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest3535>( this, &CTest3535::ProjectCode_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_CURRENT_TEST;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("Current"), lengthof(_T("Current")));
		info.bSelected = pCfg3535->current_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest3535>( this, &CTest3535::Current_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_BASE_TEST_3535;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("Base"), lengthof(_T("Base")));
		info.bSelected = pCfg3535->base_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest3535>( this, &CTest3535::Base_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_FSD_TEST_3535;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("FSD"), lengthof(_T("FSD")));
		info.bSelected = pCfg3535->fsd_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest3535>( this, &CTest3535::FSD_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_BUTTON_TEST;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("Button"), lengthof(_T("Button")));
		info.bSelected = pCfg3535->button_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest3535>( this, &CTest3535::Graph_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_LINEARLY_TEST;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("Linearly"), lengthof(_T("Linearly")));
		info.bSelected = pCfg3535->LINEARITY_TEST;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest3535>( this, &CTest3535::Graph_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_FREE_PAINT_TEST;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("FreePaint"), lengthof(_T("FreePaint")));
		info.bSelected = pCfg3535->FREEPAINT_TEST;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest3535>( this, &CTest3535::Graph_Test );
	}

    //////////////////////////////////////////////////////////////////////////
	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_TP_REMOVE;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("Removing"), lengthof(_T("Removing")));
		info.bSelected = pCfg3535->way_to_start == START_BY_AUTO;
		info.jumpIfNG = false;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest3535>( this, &CTest3535::TP_RemoveTest );
	}

	if( SM_ChipBase(m_deviceNo) )
	{
		CtpHalCfg halCfg;
		halCfg.protocalType = PROTOCAL_IIC;
		halCfg.speed = pCfg3535->Speed;
		halCfg.IIC.slaveAddr = pCfg3535->I2cAddr;
		halCfg.vddVoltage = pCfg3535->vddVotage;
		halCfg.iovddVotage = pCfg3535->ioVddVotage;
		halCfg.icType = pCfg3535->IcType;
		SM_ChipBase(m_deviceNo)->SetCommContext( halCfg );
	}

	ActionToXmlConfig();
}
void CTest3535::ICArrayToSensorMatrix( unsigned short (&dataMappinged)[MAX_SCAP_ROW][MAX_SCAP_COL], unsigned short* const dataToMapping, unsigned int dataCnt, unsigned short maxRows, unsigned short maxCols )
{
	memset( dataMappinged, 0, sizeof( dataMappinged ) );

	for( int iRow = 0; iRow < maxRows; iRow++ )
	{
		for( int iCol = 0; iCol < maxCols; iCol++ )
		{
			int index = (int)iRow * maxCols + iCol;
			if( index >= (int)dataCnt )   continue;

			int icPosition = pCfg3535->sensor_2_ic_map[index];
			dataMappinged[iRow][iCol] = dataToMapping[icPosition];
		}
	}
	for( int index = (int)maxRows * maxCols; index < (int)dataCnt; index++ )
	{
		int iCol = index - maxRows * maxCols + maxCols;
		int icPosition = pCfg3535->sensor_2_ic_map[index];
		dataMappinged[maxRows - 1][iCol] = dataToMapping[icPosition];
	}
}
void CTest3535::ICMatrixToSensorMatrix( unsigned short (&dataMappinged)[MAX_SCAP_ROW][MAX_SCAP_COL],
	unsigned short mappedRow,
	unsigned short mappedCol,
	const unsigned short (&dataToMapping)[MAX_SCAP_ROW][MAX_SCAP_COL],
	unsigned short mappingRow,
	unsigned short mappingCol )
{
	memset( dataMappinged, 0, sizeof( dataMappinged ) );

	for( int iRow = 0; iRow < mappedRow; iRow++ )
	{
		for( int iCol = 0; iCol < mappedCol; iCol++ )
		{
			int index = iRow * mappedCol + iCol;
			if( index >= (int)pCfg3535->real_channel_num )   continue;

			int icPosition = pCfg3535->sensor_2_ic_map[index];
			int icRow = icPosition / mappingCol;
			int icCol = icPosition % mappingCol;

			dataMappinged[iRow][iCol] = dataToMapping[icRow][icCol];
		}
	}
}
void CTest3535::SensorMatrixToIcMatrix( unsigned short (&dataMappinged)[MAX_SCAP_ROW][MAX_SCAP_COL],
	unsigned short mappedRow,
	unsigned short* mappedCols,
	const unsigned short (&dataToMapping)[MAX_SCAP_ROW][MAX_SCAP_COL],
	unsigned short mappingRow,
	unsigned short mappingCol )
{
	memset( dataMappinged, 0, sizeof( dataMappinged ) );

	int index = 0;
	for( int iRow = 0; iRow < mappedRow; iRow++ )
	{
		for( int iCol = 0; iCol < mappedCols[iRow]; iCol++ )
		{
			//int index = iRow * mappedCol + iCol;
		    int sensorPos = pCfg3535->ic_2_sensor_map[index++] - 1;
			if( sensorPos < 0 )
				continue;
			if( sensorPos >= MAX_SCAP_CHANNEL )
				continue;
			int sensorRow = sensorPos / mappingCol;
			int sensorCol = sensorPos % mappingCol;

			dataMappinged[iRow][iCol] = dataToMapping[sensorRow][sensorCol];
		}
	}

// 	for( int iRow = 0; iRow < mappingRow; iRow++ )
// 	{
// 		for( int iCol = 0; iCol < mappingCol; iCol++ )
// 		{
// 			int index = iRow * mappingCol + iCol;
// 			if( index >= (int)pCfg3535->real_channel_num )   continue;
// 
// 			int icPosition = pCfg3535->sensor_2_ic_map[index];
// 			int icRow = icPosition / mappedCol;
// 			int icCol = icPosition % mappedCol;
// 
// 			dataMappinged[icRow][icCol] = dataToMapping[iRow][iCol];
// 		}
// 	}
}
void CTest3535::VerTriangleCompareDataCalc( short (&iRC)[MAX_SCAP_ROW][MAX_SCAP_COL],double (&dwOut)[MAX_SCAP_ROW][MAX_SCAP_COL] )
{
	double data_tt2[MAX_SCAP_ROW][MAX_SCAP_COL];
	double data_r12[MAX_SCAP_COL], data_r13[MAX_SCAP_COL], data_r14[MAX_SCAP_COL], data_r23[MAX_SCAP_COL], data_r24[MAX_SCAP_COL], data_r34[MAX_SCAP_COL];

	for( int iRow = 0; iRow < pCfg3535->rowsCnt; iRow++ )
	{
		for( int iCol = 0; iCol < pCfg3535->colsCnt; iCol++ )
		{
			data_tt2[iRow][iCol] = iRC[iRow][iCol];
			if( 0 == data_tt2[iRow][iCol] )
				data_tt2[iRow][iCol] = 1;
		}
	}

	for( int iCol = 0; iCol < pCfg3535->colsCnt; iCol++ )
	{
		data_r12[iCol] = data_tt2[0][iCol] / data_tt2[1][iCol];
		data_r13[iCol] = data_tt2[0][iCol] / data_tt2[2][iCol];
		data_r14[iCol] = data_tt2[0][iCol] / data_tt2[3][iCol];

		data_r23[iCol] = data_tt2[1][iCol] / data_tt2[2][iCol];
		data_r24[iCol] = data_tt2[1][iCol] / data_tt2[3][iCol];

		data_r34[iCol] = data_tt2[2][iCol] / data_tt2[3][iCol];
	}

	memset(dwOut, 0, sizeof(dwOut));
	for( int iCol = 0; iCol < pCfg3535->colsCnt; iCol++ )
	{
		dwOut[0][iCol] = data_r12[iCol] + data_r13[iCol] + data_r14[iCol];
		dwOut[1][iCol] = data_r12[iCol] + data_r23[iCol] + data_r24[iCol];
		dwOut[2][iCol] = data_r13[iCol] + data_r23[iCol] + data_r34[iCol];
		dwOut[3][iCol] = data_r14[iCol] + data_r24[iCol] + data_r34[iCol];
	}
}
void CTest3535::HorTriangleCompareDataCalc( short (&iRC)[MAX_SCAP_ROW][MAX_SCAP_COL],double (&dwOut)[MAX_SCAP_ROW][MAX_SCAP_COL] )
{
	double data_tt2[MAX_SCAP_ROW][MAX_SCAP_COL];
	double data_r12[MAX_SCAP_COL];

	for( int iRow = 0; iRow < pCfg3535->rowsCnt; iRow++ )
	{
		for( int iCol = 0; iCol < pCfg3535->colsCnt; iCol++ )
		{
			data_tt2[iRow][iCol] = iRC[iRow][iCol];
			if( 0 == data_tt2[iRow][iCol] )
				data_tt2[iRow][iCol] = 1;
		}
	}

	for( int iCol = 0; iCol < pCfg3535->colsCnt; iCol++ )
	{
		data_r12[iCol] = data_tt2[0][iCol] / data_tt2[1][iCol];
	}

	memset(dwOut, 0, sizeof(dwOut));
	for( int iCol = 0; iCol < pCfg3535->colsCnt; iCol++ )
	{
		dwOut[0][iCol] = data_r12[iCol];
	}
}
// double CTest3535::GetHarfScreenSortingMean( const unsigned short (&dataCopy)[MAX_SCAP_ROW][MAX_SCAP_COL], unsigned char* pRows, int RowsCnt )
// {
// 	double uDeltaHarfMean = 0;
// 	std::list<short> listHarf; 
// 
// 	for( int iRow = 0; iRow < RowsCnt; iRow++ )
// 	{
// 		int RealRow = pRows[iRow];
// 		for( int iCol = 0; iCol < pCfg3535->colsCnt; iCol++ )
// 		{
// 			listHarf.push_back( dataCopy[RealRow][iCol] );
// 		}
// 	}
// 	listHarf.sort();
// 
// 	for( int index = 0; index < 4; index++ )
// 	{
// 		listHarf.pop_front();
// 		listHarf.pop_back();
// 	}
// 
// 	for( std::list<short>::iterator it = listHarf.begin(); it != listHarf.end(); it++ )
// 		uDeltaHarfMean += *it;
// 
// 	uDeltaHarfMean /= (int)listHarf.size();
// 
// 	return uDeltaHarfMean;
// }
double CTest3535::GetHarfScreenNormalization( short (&dataCopy)[MAX_SCAP_ROW][MAX_SCAP_COL], unsigned char* pRows, int RowsCnt  )
{
	double dwDeltaHarfMean = 0;
	std::list<short> listHarf; 

	for( int iRow = 0; iRow < RowsCnt; iRow++ )
	{
		int RealRow = pRows[iRow];
		for( int iCol = 0; iCol < pCfg3535->colsCnt; iCol++ )
		{
			listHarf.push_back( dataCopy[RealRow][iCol] );
		}
	}
	listHarf.sort();

	if( abs( *listHarf.begin() ) > abs( *listHarf.rbegin() ) )
	{
		std::list<short>::reverse_iterator it = listHarf.rbegin();
		for( int index = 0; index < pCfg3535->harf_va_channel_num / 2; index++ )
			dwDeltaHarfMean += *it++;

		dwDeltaHarfMean = dwDeltaHarfMean / (pCfg3535->harf_va_channel_num / 2);
	}
	else
	{
		std::list<short>::iterator it = listHarf.begin();

		for( int index = 0; index < pCfg3535->harf_va_channel_num / 2; index++ )
			dwDeltaHarfMean += *it++;

		dwDeltaHarfMean = dwDeltaHarfMean / (pCfg3535->harf_va_channel_num / 2);
	}

	return dwDeltaHarfMean;
}
bool CTest3535::FSDPlusCheckMatched( int (&rcDeviation)[MAX_SCAP_ROW][MAX_SCAP_COL] )
{
	int ColT1[2] = { 0, pCfg3535->colsCnt - 1 };
	for( int iter = 0; iter < 2; iter++ )
	{
		int iCol = ColT1[iter];
		for( int iRow = 0; iRow < pCfg3535->rowsCnt; iRow++ )
		{
			if( rcDeviation[iRow][iCol] < pCfg3535->fsd_plus_t1 )
			{
				return false;
			}
		}
	}

	int ColT2[2] = { 1, pCfg3535->colsCnt - 2 };
	for( int iter = 0; iter < 2; iter++ )
	{
		int iCol = ColT2[iter];
		for( int iRow = 0; iRow < pCfg3535->rowsCnt; iRow++ )
		{
			if( rcDeviation[iRow][iCol] < pCfg3535->fsd_plus_t2 )
			{
				return false;
			}
		}
	}

	int ColT3[2] = { pCfg3535->colsCnt / 2 - 1, pCfg3535->colsCnt / 2 + 1 };
	for( int iter = 0; iter < 2; iter++ )
	{
		int iCol = ColT3[iter];
		for( int iRow = 0; iRow < pCfg3535->rowsCnt; iRow++ )
		{
			if( rcDeviation[iRow][iCol] > pCfg3535->fsd_plus_t3 )
			{
				return false;
			}
		}
	}

	int ColT4[2] = { pCfg3535->colsCnt / 2 };
	for( int iter = 0; iter < 1; iter++ )
	{
		int iCol = ColT4[iter];
		for( int iRow = 0; iRow < 4; iRow++ )
		{
			if( rcDeviation[iRow][iCol] > pCfg3535->fsd_plus_t4 )
			{
				return false;
			}
		}
	}

	int iMiddleCol = pCfg3535->colsCnt / 2;
	if( abs( (long)rcDeviation[1][iMiddleCol] ) < abs( (long)rcDeviation[0][iMiddleCol] ) ){
		return false;
	}
	if( abs( (long)rcDeviation[2][iMiddleCol] ) < abs( (long)rcDeviation[3][iMiddleCol] ) ){
		return false;
	}

	return true;
}
unsigned int CTest3535::FSD_Test( NativeTestItem& itemQuote )
{
	TEST_ITEM_STATUS itemStatus = (TEST_ITEM_STATUS)FSD_TestEx( itemQuote, 1 );

	if( itemStatus == ITEM_STA_FAIL && !GetSimulateGate() )
	{
		itemStatus = (TEST_ITEM_STATUS)FSD_TestEx( itemQuote, 4 );
	}

	return itemStatus;
}
unsigned int CTest3535::FSD_TestEx( NativeTestItem& itemQuote, unsigned char testCnt )
{
	bool bMarkAsTBD = false;
	BOOL bDeviationFail = FALSE;
	unsigned int iReCode = ERROR_CODE_OK, failerCount = 0;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );

	const unsigned char clkCnt = testCnt;
	unsigned short fsdTempBuffer[MAX_SCAP_BUFFER_CNT] = {0};
	unsigned short fastFSDRaw[MAX_SCAP_ROW][MAX_SCAP_COL] = {0}, slowFSDRaw[MAX_SCAP_ROW][MAX_SCAP_COL] = {0};

	short fsdData[MAX_SCAP_ROW][MAX_SCAP_COL] = {0};
	short deltaFSD[MAX_SCAP_ROW][MAX_SCAP_COL] = {0};

	unsigned char failed_channel[MAX_SCAP_ROW][MAX_SCAP_COL] = {0};
	memset( failed_channel, 0, sizeof(failed_channel) );

	TestResultInfo( _T("\r\n------------------------------FSD Test------------------------------\r\n") );
	
	ISMChip3535* iChip3535 = (ISMChip3535*)SM_ChipBase(m_deviceNo);
	if( NULL == iChip3535 )         return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	iReCode = iChip3535->GetFSDFastData( pCfg3535->f_clk, 1, fsdTempBuffer, 0x50, clkCnt );
	if( ERROR_CODE_OK != iReCode )  return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	ICArrayToSensorMatrix( fastFSDRaw, fsdTempBuffer, pCfg3535->va_channel_num, pCfg3535->rowsCnt, pCfg3535->colsCnt );

	iReCode = iChip3535->GetFSDSlowData( pCfg3535->s_clk, 1, fsdTempBuffer, 0x50, clkCnt );
	if( ERROR_CODE_OK != iReCode )  return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	ICArrayToSensorMatrix( slowFSDRaw, fsdTempBuffer, pCfg3535->va_channel_num, pCfg3535->rowsCnt, pCfg3535->colsCnt );


// 	//////////////////////////////////////////////////////////////////////////
// 	unsigned short tempBufferF[MAX_SCAP_BUFFER_CNT] = {
// 		1561,1552,1568,1597,1605,1631,1607,	
// 		1535,1560,1560,1575,1603,1616,1656,	
// 		1870,1902,1925,1911,2004,1971,1805,	
// 		1747,1892,1916,1943,1961,1993,1974,
// 	};
// 	ReShappingData( fastFSDRaw, tempBufferF, (unsigned int)pCfg3535->va_channel_num, pCfg3535->rowsCnt, pCfg3535->colsCnt );
// 	unsigned short tempBufferS[MAX_SCAP_BUFFER_CNT] = {
// 		1582,1573,1590,1622,1627,1654,1629,	
// 		1557,1582,1581,1596,1625,1639,1682,	
// 		1897,1933,1955,1941,2035,2003,1831,	
// 		1774,1922,1949,1973,1993,2024,2007,
// 	};
// 	ReShappingData( slowFSDRaw, tempBufferS, (unsigned int)pCfg3535->va_channel_num, pCfg3535->rowsCnt, pCfg3535->colsCnt );
// 	clkCnt = 1;
// 	//////////////////////////////////////////////////////////////////////////
	int offset = 2048;
	int offset_t = 2048 - offset;

	unsigned char RowsUp[MAX_SCAP_ROW] = {0};
	unsigned char RowsDn[MAX_SCAP_ROW] = {0};
	for( int iRow = 0; iRow < pCfg3535->rowsCnt / 2; iRow++ )
	{
		RowsUp[iRow] = iRow;
		RowsDn[iRow] = iRow + pCfg3535->rowsCnt / 2;
	}

	double dwFastMeanUp = 0, dwFastMeanDown = 0, dwFastBaseUp = 0, dwFastBaseDown = 0;
	double dwSlowMeanUp = 0, dwSlowMeanDown = 0, dwSlowBaseUp = 0, dwSlowBaseDown = 0;
	unsigned short fastFSDRawCopy[MAX_SCAP_ROW][MAX_SCAP_COL] = {0}, slowFSDRawCopy[MAX_SCAP_ROW][MAX_SCAP_COL] = {0};

	for( int iRow = 0; iRow < pCfg3535->rowsCnt; iRow++ )
	{
		for( int iCol = 0; iCol < pCfg3535->colsCnt; iCol++ )
		{
			fastFSDRaw[iRow][iCol] /= clkCnt;
			slowFSDRaw[iRow][iCol] /= clkCnt;
		}
	}

	memcpy_s( fastFSDRawCopy, sizeof(fastFSDRawCopy), fastFSDRaw, sizeof(fastFSDRaw) );
	memcpy_s( slowFSDRawCopy, sizeof(slowFSDRawCopy), slowFSDRaw, sizeof(slowFSDRaw) );

	dwFastMeanUp   = GetHarfScreenSortingMean( fastFSDRawCopy, RowsUp, pCfg3535->rowsCnt / 2, pCfg3535->colsCnt ) - offset_t;
	dwFastMeanDown = GetHarfScreenSortingMean( fastFSDRawCopy, RowsDn, pCfg3535->rowsCnt / 2, pCfg3535->colsCnt ) - offset_t;
	dwFastBaseUp   = GetHarfScreenSortingMean( pCfg3535->fsd_fast, RowsUp, pCfg3535->rowsCnt / 2, pCfg3535->colsCnt ) - offset_t;
	dwFastBaseDown = GetHarfScreenSortingMean( pCfg3535->fsd_fast, RowsDn, pCfg3535->rowsCnt / 2, pCfg3535->colsCnt ) - offset_t;

	dwSlowMeanUp   = GetHarfScreenSortingMean( slowFSDRawCopy, RowsUp, pCfg3535->rowsCnt / 2, pCfg3535->colsCnt ) - offset_t;
	dwSlowMeanDown = GetHarfScreenSortingMean( slowFSDRawCopy, RowsDn, pCfg3535->rowsCnt / 2, pCfg3535->colsCnt ) - offset_t;
	dwSlowBaseUp   = GetHarfScreenSortingMean( pCfg3535->fsd_slow, RowsUp, pCfg3535->rowsCnt / 2, pCfg3535->colsCnt ) - offset_t;
	dwSlowBaseDown = GetHarfScreenSortingMean( pCfg3535->fsd_slow, RowsDn, pCfg3535->rowsCnt / 2, pCfg3535->colsCnt ) - offset_t;

	double dwFastEfficientUp = dwFastBaseUp / (dwFastMeanUp ? dwFastMeanUp : 1);
	double dwFastEfficientDn = dwFastBaseDown / (dwFastMeanDown ? dwFastMeanDown : 1);
	double dwSlowEfficientUp = dwSlowBaseUp / (dwSlowMeanUp ? dwSlowMeanUp : 1);
	double dwSlowEfficientDn = dwSlowBaseDown / (dwSlowMeanDown ? dwSlowMeanDown : 1);


	for( int iRow = 0; iRow < pCfg3535->rowsCnt; iRow++ )
	{
		for( int iCol = 0; iCol < pCfg3535->colsCnt; iCol++ )
		{
			double dwFastEfficient = iRow >= pCfg3535->rowsCnt / 2 ? dwFastEfficientDn : dwFastEfficientUp;
			double dwSlowEfficinet = iRow >= pCfg3535->rowsCnt / 2 ? dwSlowEfficientDn : dwSlowEfficientUp; 

			fastFSDRawCopy[iRow][iCol] = (unsigned short)( ( fastFSDRawCopy[iRow][iCol] - offset_t ) * dwFastEfficient ) + offset_t;
			slowFSDRawCopy[iRow][iCol] = (unsigned short)( ( slowFSDRawCopy[iRow][iCol] - offset_t ) * dwSlowEfficinet ) + offset_t;
			fsdData[iRow][iCol] = slowFSDRawCopy[iRow][iCol] - fastFSDRawCopy[iRow][iCol];
			deltaFSD[iRow][iCol] = fsdData[iRow][iCol] - pCfg3535->fsd_base[iRow][iCol];
		}
	}

	/********************************************************************************************/
	/*backup test result data*/
	memcpy_s( m_stOneRecord.Scap.fsd_test_buff, sizeof(m_stOneRecord.Scap.fsd_test_buff), fsdData, sizeof(fsdData) );
	memcpy_s( m_stOneRecord.Scap.fsd_fast_buff, sizeof(m_stOneRecord.Scap.fsd_fast_buff), fastFSDRaw, sizeof(fastFSDRaw) );
	memcpy_s( m_stOneRecord.Scap.fsd_slow_buff, sizeof(m_stOneRecord.Scap.fsd_slow_buff), slowFSDRaw, sizeof(slowFSDRaw) );
	/********************************************************************************************/

	{
		AnalyzeInfo info( pCfg3535->rowsCnt, pCfg3535->colsCnt );
		PrintMaxtrixValue( m_ColorText, slowFSDRaw, pCfg3535->invalid_node, info, _T("\r\nSlow CLK RawData:\r\n") );
	}
	{
		AnalyzeInfo info( pCfg3535->rowsCnt, pCfg3535->colsCnt );
		PrintMaxtrixValue( m_ColorText, fastFSDRaw, pCfg3535->invalid_node, info, _T("\r\nFast CLK RawData:\r\n") );
	}
	{
		AnalyzeInfo info( pCfg3535->rowsCnt, pCfg3535->colsCnt );
		unsigned char dataFailChannel[MAX_SCAP_ROW][MAX_SCAP_COL] = {0};
		memset( dataFailChannel, 0, sizeof(dataFailChannel) );
		for( int iRow = 0; iRow < pCfg3535->rowsCnt; iRow++ )
		{
			for( int iCol = 0; iCol < pCfg3535->colsCnt; iCol++ )
			{
				if( ( fsdData[iRow][iCol] < pCfg3535->fsd_min ) 
					/*&& ( abs(fastFSDRaw[iRow][iCol] - 2048) < 20 )*/ 
					/*&& ( abs(slowFSDRaw[iRow][iCol] - 2048) < 20 )*/ )
				{
					failerCount++;
					bDeviationFail = TRUE;	
					dataFailChannel[iRow][iCol] = 1;
				}
			}
		}

		PrintMaxtrixValue( m_ColorText, fsdData, dataFailChannel, pCfg3535->invalid_node, info, _T("\r\nFSD Data:\r\n") );
	}

	//case 0
	if( dwFastEfficientUp <= 0.5 || dwFastEfficientUp >= 1.5 )
	{
		failerCount++;
		bDeviationFail = TRUE;	
	}
	if( dwFastEfficientDn <= 0.5 || dwFastEfficientDn >= 1.5 )
	{
		failerCount++;
		bDeviationFail = TRUE;
	}
	if( dwSlowEfficientUp <= 0.5 || dwSlowEfficientUp >= 1.5 )
	{
		failerCount++;
		bDeviationFail = TRUE;
	}
	if( dwSlowEfficientDn <= 0.5 || dwSlowEfficientDn >= 1.5 )
	{
		failerCount++;
		bDeviationFail = TRUE;
	}
	if( failerCount )
	{
		TCHAR chTemp[256] = {0};
		transformat( chTemp, _T("\r\nfast coefficient up = %.3f, fast coefficient dn = %.3f, slow coefficient up = %.3f, slow coefficient dn = %.3f\r\n"), 
			dwFastEfficientUp, dwFastEfficientDn, dwSlowEfficientUp, dwSlowEfficientDn );
		ColorText text( chTemp, RGB( 255, 0, 0 ), TEXT_SIZE_SMALL, false );
		TestResultInfo( text );
	}

	//case 1
	short slowRc[MAX_SCAP_ROW][MAX_SCAP_COL] = {0};
	short fastRc[MAX_SCAP_ROW][MAX_SCAP_COL] = {0};

	for( int iRow = 0; iRow < pCfg3535->rowsCnt; iRow++ )
	{
		for( int iCol = 0; iCol < pCfg3535->colsCnt; iCol++ )
		{
			slowRc[iRow][iCol] = slowFSDRawCopy[iRow][iCol] - offset_t;
			if( 0 == slowRc[iRow][iCol] ) slowRc[iRow][iCol] = 1;

			fastRc[iRow][iCol] = fastFSDRawCopy[iRow][iCol] - offset_t;
			if( 0 == fastRc[iRow][iCol] ) fastRc[iRow][iCol] = 1;
		}
	}

	
	short fsdDataCopy1[MAX_SCAP_ROW][MAX_SCAP_COL] = {0};
	double data_r[MAX_SCAP_ROW][MAX_SCAP_COL], data_t_r[MAX_SCAP_ROW][MAX_SCAP_COL];

	memcpy_s( fsdDataCopy1, sizeof(fsdDataCopy1), fsdData, sizeof(fsdData) );
	for( int iCol = 0; pCfg3535->bVerticalTriangle && iCol < pCfg3535->colsCnt; iCol++ )
	{
		short baseDel = 0;
		baseDel = pCfg3535->fsd_base[0 + 1][iCol] - pCfg3535->fsd_base[0][iCol];
		fsdDataCopy1[0][iCol] += baseDel;

		baseDel = pCfg3535->fsd_base[pCfg3535->rowsCnt - 2][iCol] - pCfg3535->fsd_base[pCfg3535->rowsCnt -1][iCol];
		fsdDataCopy1[pCfg3535->rowsCnt -1][iCol] += baseDel;
	}

	if( pCfg3535->bVerticalTriangle )
	{
		VerTriangleCompareDataCalc( slowRc, data_r );
		VerTriangleCompareDataCalc( fsdDataCopy1, data_t_r );
	}
	else
	{
		HorTriangleCompareDataCalc( slowRc, data_r );
		HorTriangleCompareDataCalc( fsdDataCopy1, data_t_r );
	}

	int datar_r_cmp[MAX_SCAP_ROW][MAX_SCAP_COL];
	double nbChannelCoef[MAX_SCAP_ROW][MAX_SCAP_COL];
	for( int iRow = 0; iRow < pCfg3535->rowsCnt; iRow += 2 )
	{
		for( int iCol = 0; iCol < pCfg3535->colsCnt; iCol++ )
		{
			int iUpDownDev = abs( fsdDataCopy1[iRow][iCol] - fsdDataCopy1[iRow + 1][iCol] );
			iUpDownDev = iUpDownDev ? iUpDownDev : 1;
			nbChannelCoef[iRow][iCol] = ((double)iUpDownDev) * 2 / 10;

			if(iCol == 0 || iCol == (pCfg3535->colsCnt - 1))
			{
				nbChannelCoef[iRow][iCol] /= 3;
			}
			nbChannelCoef[iRow + 1][iCol] = nbChannelCoef[iRow][iCol];
		}
	}

	for( int iRow = 0; iRow < pCfg3535->rowsCnt; iRow++ )
	{
		for( int iCol = 0; iCol < pCfg3535->colsCnt; iCol++ )
		{
			datar_r_cmp[iRow][iCol] = (int)( 1000 * ( data_r[iRow][iCol] / data_t_r[iRow][iCol] - 1 ) * nbChannelCoef[iRow][iCol] );
		}
	}

	{
		NodeVal nodeOutRange;
		ColorText textTemp( _T("\r\nFSD CMP:\r\n") );
		AnalyzeInfo info( pCfg3535->bVerticalTriangle ? pCfg3535->rowsCnt : 1, pCfg3535->colsCnt );
		int cmp_min[MAX_SCAP_ROW][MAX_SCAP_COL] = {0};
		int cmp_max[MAX_SCAP_ROW][MAX_SCAP_COL] = {0};
		FillMatrixUseValue( cmp_min, -(int)(3 * pCfg3535->cmp_max) );
		FillMatrixUseValue( cmp_max, (int)pCfg3535->cmp_max );

		bool bResult = AnalyzeTestResult( datar_r_cmp, cmp_min, cmp_max, pCfg3535->invalid_node, info, textTemp, nodeOutRange );
		TestResultInfo( textTemp );
		if( !bResult )
		{
			LPCTSTR strHead = _T("\r\n//========= Out of Threshold in FSD CMP: \r\n");
			PrintNodeValue( m_ColorText, &nodeOutRange, strHead );
			MarkNodeToMatrix( &nodeOutRange, failed_channel );
			failerCount++;
		}
	}

	//case 2
	double dwDeltaUpMean = 0, dwDeltaDownMean = 0;
	short fsdDeltaCopy2[MAX_SCAP_ROW][MAX_SCAP_COL] = {0};
	memcpy_s( fsdDeltaCopy2, sizeof(fsdDeltaCopy2), deltaFSD, sizeof(deltaFSD) );

	//dwDeltaUpMean = ( Sum( fsdDeltaCopy[0], pCfg3535->colsCnt ) + Sum( fsdDeltaCopy[1], pCfg3535->colsCnt ) ) / pCfg3535->harf_va_channel_num;
	//dwDeltaDownMean =( Sum( fsdDeltaCopy[2], pCfg3535->colsCnt ) + Sum( fsdDeltaCopy[3], pCfg3535->colsCnt ) ) / pCfg3535->harf_va_channel_num;

	dwDeltaUpMean = GetHarfScreenNormalization( fsdDeltaCopy2, RowsUp, pCfg3535->rowsCnt / 2 );
	dwDeltaDownMean = GetHarfScreenNormalization( fsdDeltaCopy2, RowsDn, pCfg3535->rowsCnt / 2 );

	for( int iRow = 0; iRow < pCfg3535->rowsCnt; iRow++ )
	{
		for( int iCol = 0; iCol < pCfg3535->colsCnt; iCol++ )
		{
			int fsdDeltaFixed = 0;
			if( iRow < pCfg3535->rowsCnt / 2 )
				fsdDeltaFixed = fsdDeltaCopy2[iRow][iCol] - (int)dwDeltaUpMean;
			else
				fsdDeltaFixed = fsdDeltaCopy2[iRow][iCol] - (int)dwDeltaDownMean;

			fsdDeltaCopy2[iRow][iCol] = abs( fsdDeltaFixed );
		}
	}

	{
		NodeVal nodeOutRange;
		ColorText textTemp( _T("\r\nFSD Delta:\r\n") );
		AnalyzeInfo info( pCfg3535->rowsCnt, pCfg3535->colsCnt );
		int delta_min[MAX_SCAP_ROW][MAX_SCAP_COL] = {0};
		FillMatrixUseValue( delta_min, 0 );

		bool bResult = AnalyzeTestResult( fsdDeltaCopy2, delta_min, pCfg3535->fsd_delta_max, pCfg3535->invalid_node, info, textTemp, nodeOutRange );
		TestResultInfo( textTemp );
		if( !bResult )
		{
			LPCTSTR strHead = _T("\r\n//========= Out of Threshold in FSD Delta: \r\n");
			PrintNodeValue( m_ColorText, &nodeOutRange, strHead );
			MarkNodeToMatrix( &nodeOutRange, failed_channel );
			failerCount++;
		}
	}

	//case 3
	//normalization
	short fsdDataCopy3[MAX_SCAP_ROW][MAX_SCAP_COL] = {0};
	memcpy_s( fsdDataCopy3, sizeof(fsdDataCopy3), fsdData, sizeof(fsdData) );
	for( int iRow = 0; iRow < pCfg3535->rowsCnt; iRow++ )
	{
		{
			int iCol = 0;
			double dwNormalization = (double)pCfg3535->fsd_base[iRow][iCol+1] / ( (pCfg3535->fsd_base[iRow][iCol] == 0) ? 0.001 : pCfg3535->fsd_base[iRow][iCol] );
			fsdDataCopy3[iRow][iCol] =  (short)( dwNormalization * fsdDataCopy3[iRow][iCol] );
		}
		{
			int iCol = pCfg3535->colsCnt - 1;
			double dwNormalization = (double)pCfg3535->fsd_base[iRow][iCol-1] / ( (pCfg3535->fsd_base[iRow][iCol] == 0) ? 0.001 : pCfg3535->fsd_base[iRow][iCol] );
			fsdDataCopy3[iRow][iCol] = (short)( dwNormalization * fsdDataCopy3[iRow][iCol] );
		}
	}
	{
		AnalyzeInfo info( pCfg3535->rowsCnt, pCfg3535->colsCnt );
		PrintMaxtrixValue( m_ColorText, fsdDataCopy3, pCfg3535->invalid_node, info, _T("\r\nNormalization:\r\n") );
	}

	{
		NodeVal nodeOutRange;
		ColorText textTemp( _T("\r\nFSD Delta Uniformity Left:\r\n") );
		AnalyzeInfo info( pCfg3535->rowsCnt, pCfg3535->colsCnt );
		int pannel_left_min[MAX_SCAP_ROW][MAX_SCAP_COL] = {0};
		int pannel_left_val[MAX_SCAP_ROW][MAX_SCAP_COL] = {0};
		unsigned char invalidTemp[MAX_SCAP_ROW][MAX_SCAP_COL] = {0};
		CopyAndInvalid( invalidTemp, pCfg3535->invalid_node, MAX_SCAP_ROW,  0 );
		for( int iRow = 0; iRow < pCfg3535->rowsCnt; iRow++ )
		{
			for( int iCol = 1; iCol < pCfg3535->colsCnt; iCol++ )
			{
				pannel_left_val[iRow][iCol] = abs( fsdDataCopy3[iRow][iCol] - fsdDataCopy3[iRow][iCol - 1] );
			}
		}

		bool bResult = AnalyzeTestResult( pannel_left_val, pannel_left_min, pCfg3535->fsd_uniformity_left, invalidTemp, info, textTemp, nodeOutRange );
		TestResultInfo( textTemp );
		if( !bResult )
		{
			LPCTSTR strHead = _T("\r\n//========= Out of Threshold in FSD Delta Uniformity Left: \r\n");
			PrintNodeValue( m_ColorText, &nodeOutRange, strHead );
			MarkNodeToMatrix( &nodeOutRange, failed_channel );
			failerCount++;
		}
	}

	{
		NodeVal nodeOutRange;
		ColorText textTemp( _T("\r\nFSD Delta Uniformity Right:\r\n") );
		AnalyzeInfo info( pCfg3535->rowsCnt, pCfg3535->colsCnt );
		int pannel_right_min[MAX_SCAP_ROW][MAX_SCAP_COL] = {0};
		int pannel_right_val[MAX_SCAP_ROW][MAX_SCAP_COL] = {0};
		unsigned char invalidTemp[MAX_SCAP_ROW][MAX_SCAP_COL] = {0};
		CopyAndInvalid( invalidTemp, pCfg3535->invalid_node, MAX_SCAP_ROW, pCfg3535->colsCnt - 1 );
		for( int iRow = 0; iRow < pCfg3535->rowsCnt; iRow++ )
		{
			for( int iCol = 0; iCol < pCfg3535->colsCnt - 1; iCol++ )
			{
				pannel_right_val[iRow][iCol] = abs( fsdDataCopy3[iRow][iCol]- fsdDataCopy3[iRow][iCol + 1] );
			}
		}

		bool bResult = AnalyzeTestResult( pannel_right_val, pannel_right_min, pCfg3535->fsd_uniformity_right, invalidTemp, info, textTemp, nodeOutRange );
		TestResultInfo( textTemp );
		if( !bResult )
		{
			LPCTSTR strHead = _T("\r\n//========= Out of Threshold in FSD Delta Uniformity Right: \r\n");
			PrintNodeValue( m_ColorText, &nodeOutRange, strHead );
			MarkNodeToMatrix( &nodeOutRange, failed_channel );
			failerCount++;
		}
	}

	//case 4
	int rcSlowDeviation[MAX_SCAP_ROW][MAX_SCAP_COL] = {0};
	{
		/*unsigned*/ short baseSlowRc[MAX_SCAP_ROW][MAX_SCAP_COL] = {0};
		for( int iRow = 0; iRow < pCfg3535->rowsCnt; iRow++ )
		{
			for( int iCol = 0; iCol < pCfg3535->colsCnt; iCol++ )
			{
				baseSlowRc[iRow][iCol] = pCfg3535->fsd_slow[iRow][iCol] - offset_t;
				if( 0 == baseSlowRc[iRow][iCol] ) baseSlowRc[iRow][iCol] = 1;

				rcSlowDeviation[iRow][iCol] = baseSlowRc[iRow][iCol] - slowRc[iRow][iCol];
			}
		}

		double dwMeanUp = 0, dwMeanDown = 0;
		dwMeanUp = GetHarfScreenSortingMean( rcSlowDeviation, RowsUp, pCfg3535->rowsCnt / 2, pCfg3535->colsCnt );
		dwMeanDown = GetHarfScreenSortingMean( rcSlowDeviation, RowsDn, pCfg3535->rowsCnt / 2, pCfg3535->colsCnt );
// 		if( pCfg3535->bVerticalTriangle )
// 		{
// 			for( int iRow = 0; iRow < pCfg3535->rowsCnt / 2; iRow++ )
// 			{
// 				dwMeanUp += Sum( rcSlowDeviation[iRow], pCfg3535->colsCnt );
// 				dwMeanDown = Sum( rcSlowDeviation[iRow + pCfg3535->rowsCnt / 2], pCfg3535->colsCnt );
// 			}
// 			dwMeanUp /= pCfg3535->harf_va_channel_num;
// 			dwMeanDown /= pCfg3535->harf_va_channel_num;
// 		}
// 		else
// 		{
// 			for( int iRow = 0; iRow < pCfg3535->rowsCnt; iRow++ )
// 				dwMeanUp += Sum( rcSlowDeviation[iRow], pCfg3535->colsCnt );
// 
// 			dwMeanDown = dwMeanUp = dwMeanUp / pCfg3535->va_channel_num;
// 		}
		
		for( int iRow = 0; iRow < pCfg3535->rowsCnt; iRow++ )
		{
			for( int iCol = 0; iCol < pCfg3535->colsCnt; iCol++ )
			{
				if( iRow < pCfg3535->rowsCnt / 2 )
					rcSlowDeviation[iRow][iCol] = rcSlowDeviation[iRow][iCol] - (int)dwMeanUp;
				else 
					rcSlowDeviation[iRow][iCol] = rcSlowDeviation[iRow][iCol] - (int)dwMeanDown;

				rcSlowDeviation[iRow][iCol] = 1000 * rcSlowDeviation[iRow][iCol] / baseSlowRc[iRow][iCol]; 
			}
		}
		NodeVal nodeOutRange;
		ColorText textTemp( _T("\r\nFSD Deviation:\r\n") );
		AnalyzeInfo info( pCfg3535->rowsCnt, pCfg3535->colsCnt );
		int deviation_min[MAX_SCAP_ROW][MAX_SCAP_COL] = {0};
		for( int iRow = 0; iRow < pCfg3535->rowsCnt; iRow++ )
		{
			for( int iCol = 0; iCol < pCfg3535->colsCnt; iCol++ )
			{
				deviation_min[iRow][iCol] = (-3) * pCfg3535->fsd_deviation[iRow][iCol];
			}
		}
		bool bResult = AnalyzeTestResult( rcSlowDeviation, deviation_min, pCfg3535->fsd_deviation, pCfg3535->invalid_node, info, textTemp, nodeOutRange );
		TestResultInfo( textTemp );
		if( !bResult )
		{
			LPCTSTR strHead = _T("\r\n//========= Out of Threshold in FSD Deviation Test: \r\n");
			PrintNodeValue( m_ColorText, &nodeOutRange, strHead );
			MarkNodeToMatrix( &nodeOutRange, failed_channel );
			failerCount++;
			bDeviationFail = TRUE;
		}
	}

	//case 5
	int rcFastDeviation[MAX_SCAP_ROW][MAX_SCAP_COL] = {0};
	{
		/*unsigned*/ short baseFastRc[MAX_SCAP_ROW][MAX_SCAP_COL] = {0};
		for( int iRow = 0; iRow < pCfg3535->rowsCnt; iRow++ )
		{
			for( int iCol = 0; iCol < pCfg3535->colsCnt; iCol++ )
			{
				baseFastRc[iRow][iCol] = pCfg3535->fsd_fast[iRow][iCol] - offset_t;
				if( 0 == baseFastRc[iRow][iCol] ) baseFastRc[iRow][iCol] = 1;

				rcFastDeviation[iRow][iCol] = baseFastRc[iRow][iCol] - fastRc[iRow][iCol];
			}
		}
		double dwMeanUp = 0, dwMeanDown = 0;
		dwMeanUp = GetHarfScreenSortingMean( rcFastDeviation, RowsUp, pCfg3535->rowsCnt / 2, pCfg3535->colsCnt );
		dwMeanDown = GetHarfScreenSortingMean( rcFastDeviation, RowsDn, pCfg3535->rowsCnt / 2, pCfg3535->colsCnt );
		//dwMeanUp = (double)( Sum( rcFastDeviation[0], pCfg3535->colsCnt ) + Sum( rcFastDeviation[1], pCfg3535->colsCnt ) ) / pCfg3535->harf_va_channel_num;
		//dwMeanDown = (double)( Sum( rcFastDeviation[2], pCfg3535->colsCnt ) + Sum( rcFastDeviation[3], pCfg3535->colsCnt ) ) / pCfg3535->harf_va_channel_num;
		for( int iRow = 0; iRow < pCfg3535->rowsCnt; iRow++ )
		{
			for( int iCol = 0; iCol < pCfg3535->colsCnt; iCol++ )
			{
				if( iRow < pCfg3535->rowsCnt / 2 )
					rcFastDeviation[iRow][iCol] = rcFastDeviation[iRow][iCol] - (int)dwMeanUp;
				else 
					rcFastDeviation[iRow][iCol] = rcFastDeviation[iRow][iCol] - (int)dwMeanDown;

				rcFastDeviation[iRow][iCol] = 1000 * rcFastDeviation[iRow][iCol] / baseFastRc[iRow][iCol]; 
			}
		}
// 		NodeVal nodeOutRange;
// 		ColorText textTemp( _T("\r\nFSD Deviation:\r\n") );
// 		AnalyzeInfo info( pCfg3535->rowsCnt, pCfg3535->colsCnt );
// 		bool bResult = AnalyzeTestResult( rcFastDeviation, pCfg3535->fsd_deviation, pCfg3535->fsd_deviation, pCfg3535->invalid_node, info, textTemp, nodeOutRange );
// 		TestResultInfo( textTemp );
	}

	{
		AnalyzeInfo info( pCfg3535->rowsCnt, pCfg3535->colsCnt );
		PrintMaxtrixValue( m_ColorText, rcFastDeviation, pCfg3535->invalid_node, info, _T("\r\nFast Deviation:\r\n") );
	}

	//case 6  打补丁放水
	if( !bDeviationFail && failerCount > 0 )
	{
		for( int iRow = 0; iRow < pCfg3535->rowsCnt; iRow++ )
		{
			for( int iCol = 0; iCol < pCfg3535->colsCnt; iCol++ )
			{
				//int index = iRow * pCfg3535->colsCnt + iCol;
				int asbDeltaFSD = fsdDeltaCopy2[iRow][iCol];
				if( (asbDeltaFSD >= pCfg3535->fsd_triger_min)
					&& (asbDeltaFSD <= pCfg3535->fsd_triger_max)
					&& (rcSlowDeviation[iRow][iCol] >= pCfg3535->fsd_critical_slow_min)
					&& (rcSlowDeviation[iRow][iCol] <= pCfg3535->fsd_critical_slow_max) 
					&& (rcFastDeviation[iRow][iCol] <= pCfg3535->fsd_critical_fast_max) )
				{
					failed_channel[iRow][iCol] = 0;
					for( int iRow2 = 0; iRow2 < pCfg3535->rowsCnt; iRow2++ )
					{
						if( abs( fsdDeltaCopy2[iRow2][iCol] ) < pCfg3535->fsd_besides_min )
							failed_channel[iRow2][iCol] = 0;
					}
					int iLeft  =  iCol == 0 ? 0 : iCol - 1;
					int iRight = iCol == (pCfg3535->colsCnt - 1) ?  (pCfg3535->colsCnt - 1) : iCol + 1;
					if( abs( (long)fsdDeltaCopy2[iRow * pCfg3535->colsCnt + iLeft] ) < pCfg3535->fsd_besides_min )
					{
						failed_channel[iRow][iLeft] = 0;
					}
					if( abs( (long)fsdDeltaCopy2[iRow * pCfg3535->colsCnt + iRight] ) < pCfg3535->fsd_besides_min )
					{
						failed_channel[iRow][iRight] = 0;
					}
				}
			}
		}

		failerCount = Sum( failed_channel[0], pCfg3535->colsCnt ) + Sum( failed_channel[1], pCfg3535->colsCnt ) + Sum( failed_channel[2], pCfg3535->colsCnt ) + Sum( failed_channel[3], pCfg3535->colsCnt );
		if( failerCount > 0 )
		{

		}
		else
		{
			bMarkAsTBD = pCfg3535->fsd_recheck ? false : true;
		}
	}
	
	//cast 7  
	if( !failerCount && pCfg3535->fsd_plus_check )
	{
		bool plus_feature_match = FSDPlusCheckMatched( rcSlowDeviation );
		if( plus_feature_match )
		{
			failerCount++;
			for( int iRow = 0; iRow < pCfg3535->rowsCnt; iRow++ )
			{
				failed_channel[iRow][0] = 1;
				failed_channel[iRow][pCfg3535->colsCnt - 1] = 1;
				failed_channel[iRow][1] = 1;
				failed_channel[iRow][pCfg3535->colsCnt - 2] = 1;
				failed_channel[iRow][pCfg3535->colsCnt / 2] = 1;
			}
		}
	}

	if( pCfg3535->fsd_recheck || pCfg3535->fsd_plus_check )
	{
		AnalyzeInfo info( pCfg3535->rowsCnt, pCfg3535->colsCnt );
		PrintMaxtrixValue( m_ColorText, rcSlowDeviation, failed_channel, pCfg3535->invalid_node, info, _T("\r\nFSD Redjuge:\r\n") );
	}

	if( failerCount )
	{
		itemNotify.UpdateItemResult( ITEM_STA_FAIL );
		TestResultInfo( "\r\n\r\n//FSD Test is Fail\r\n", ITEM_STA_FAIL );
	}
	else
	{
		if( bMarkAsTBD )
		{
			itemNotify.UpdateItemResult( ITEM_STA_TBD );
			TestResultInfo( "\r\n\r\n//FSD Test is TBD\r\n", ITEM_STA_TBD );
		}
		else
		{
			itemNotify.UpdateItemResult( ITEM_STA_PASS );
			TestResultInfo( "\r\n\r\n//FSD Test is Pass\r\n", ITEM_STA_PASS );
		}	
	}

	return itemNotify;
}
unsigned int CTest3535::OS_Test( NativeTestItem& itemQuote )
{
	//err_type 0 = no err; 1 - open; 2-short; 4-tbd
	unsigned char err_type_linkly = 0;
	//failerStep 1 - M1; 2 - M2; 4 - M3
	unsigned int iReCode = ERROR_CODE_OK, failerStep = 0;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );

	int os_delta[MAX_SCAP_ROW][MAX_SCAP_COL] = {0};
	unsigned short osTempBuffer[MAX_SCAP_BUFFER_3535] = {0};
	unsigned short osSsRawDataMatrix[MAX_SCAP_ROW][MAX_SCAP_COL] = {0}, osIcRawDataMatrix[MAX_SCAP_ROW][MAX_SCAP_COL] = {0};
	unsigned short osICBaseMatrix[MAX_SCAP_ROW][MAX_SCAP_COL] = {0};
	unsigned short ic_2_sensor_matrix[MAX_SCAP_ROW][MAX_SCAP_COL] = {0};

	int ref_channel_num = min(pCfg3535->real_channel_num - pCfg3535->va_channel_num, pCfg3535->colsCnt);

	TestResultInfo( _T("\r\n------------------------------OS Test------------------------------\r\n") );

	ISMChip3535* iChip3535 = (ISMChip3535*)SM_ChipBase(m_deviceNo);
	if( NULL == iChip3535 )         return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	//iReCode = iChip3535->WriteCoreSpace( 0x41c, (unsigned char*)&m_stOneRecord.Scap.oscTrim, 1 );
	//if( ERROR_CODE_OK != iReCode )  return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	iReCode = iChip3535->GetOSData( pCfg3535->integral, pCfg3535->scale_a, pCfg3535->scale_b, osTempBuffer, MAX_SCAP_BUFFER_3535 * sizeof(unsigned short) );

	//////////////////////////////////////////////////////////////////////////
// 	unsigned short osTemp[] = {
// 		300,1164,1176,   0,1154,1140,1104,1094, 852, 744,   0,   0,	
// 		630, 668, 944, 916, 886, 888, 886, 902, 936, 930, 944, 946,	
// 		0,   0, 704, 670, 780, 874,1132,1148,1202,1158, 326, 290,	
// 		314, 344,   0,   0, 368, 338, 298, 266,   0,   0,   0,   0
// 	};
// 	memcpy_s( osTempBuffer, sizeof(osTempBuffer), osTemp, sizeof(osTemp) );
	//////////////////////////////////////////////////////////////////////////

	if( ERROR_CODE_OK != iReCode )  return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	ICArrayToSensorMatrix( osSsRawDataMatrix, osTempBuffer, pCfg3535->real_channel_num, pCfg3535->rowsCnt + 1, pCfg3535->colsCnt );

	// 4 * 12
	unsigned short maxICRows[] = {8, 8, 10, 10};
	ReShappingData( ic_2_sensor_matrix, (unsigned short*)pCfg3535->ic_2_sensor_map, MAX_SCAP_CHANNEL, MAX_CHANNEL_ONE_GROUP, maxICRows );
	ReShappingData( osIcRawDataMatrix, osTempBuffer, MAX_SCAP_CHANNEL, MAX_CHANNEL_ONE_GROUP, maxICRows );
	SensorMatrixToIcMatrix( osICBaseMatrix, MAX_CHANNEL_ONE_GROUP, maxICRows, pCfg3535->os_base, pCfg3535->rowsCnt + 1, pCfg3535->colsCnt );

	/********************************************************************************************/
	/*backup test result data*/
	memcpy_s( m_stOneRecord.Scap.OS_test_buff, sizeof(m_stOneRecord.Scap.OS_test_buff), osSsRawDataMatrix, sizeof(osSsRawDataMatrix) );
	/********************************************************************************************/

	//OS - M1
	{
		NodeVal nodeOutRange;
		ColorText textTemp( _T("\r\nOS - M1:\r\n") );
		AnalyzeInfo info( pCfg3535->rowsCnt, pCfg3535->colsCnt,  ref_channel_num, true );

		unsigned short os_m2_min[MAX_SCAP_ROW][MAX_SCAP_COL] = {0};
		unsigned short os_m2_max[MAX_SCAP_ROW][MAX_SCAP_COL] = {0};

		for( int iRow = 0; iRow < pCfg3535->rowsCnt; iRow++ )
		{
			for( int iCol = 0; iCol < pCfg3535->colsCnt; iCol++ )
			{
				os_m2_min[iRow][iCol] = pCfg3535->os_base[iRow][iCol] - (pCfg3535->os_base[iRow][iCol] * pCfg3535->m1_ratio_lower_va) / 100;
				os_m2_max[iRow][iCol] = pCfg3535->os_base[iRow][iCol] + (pCfg3535->os_base[iRow][iCol] * pCfg3535->m1_ratio_upper_va) / 100;
			}
		}
		for( int iCol = 0; iCol < pCfg3535->colsCnt; iCol++ )
		{
			os_m2_min[pCfg3535->rowsCnt][iCol] = pCfg3535->os_base[pCfg3535->rowsCnt][iCol] - (pCfg3535->os_base[pCfg3535->rowsCnt][iCol] * pCfg3535->m1_ratio_lower_ref) / 100;
			os_m2_max[pCfg3535->rowsCnt][iCol] = pCfg3535->os_base[pCfg3535->rowsCnt][iCol] + (pCfg3535->os_base[pCfg3535->rowsCnt][iCol] * pCfg3535->m1_ratio_upper_ref) / 100;
		}

		bool bResult = AnalyzeTestResult( osSsRawDataMatrix, os_m2_min, os_m2_max, pCfg3535->invalid_node, info, textTemp, nodeOutRange );
		TestResultInfo( textTemp );
		if( !bResult )
		{
			LPCTSTR strHead = _T("\r\n//========= Out of Threshold in OS - M1: \r\n");
			PrintNodeValue( m_ColorText, &nodeOutRange, strHead );
			failerStep |= 0x01;
		}
	}

	//OS - M2
	unsigned char failedChannel[MAX_SCAP_ROW][MAX_SCAP_COL] = {0};
	unsigned char osInvalidM1[MAX_SCAP_ROW][MAX_SCAP_COL] = {0};
	memset( failedChannel, 0, sizeof(failedChannel) );
	memset( osInvalidM1, 0x00, sizeof(osInvalidM1) );
	for( int iCol = 0; iCol < MAX_IX_NUM_3535; iCol++ )
	{
		//no active channel
		if( 0 == ( ic_2_sensor_matrix[0][iCol] + ic_2_sensor_matrix[1][iCol] + ic_2_sensor_matrix[2][iCol] + ic_2_sensor_matrix[3][iCol] ) ) continue;

		for( int iRow = 0; iRow < MAX_CHANNEL_ONE_GROUP; iRow++ )
		{
			if( 0 == ic_2_sensor_matrix[iRow][iCol] ) continue;

			int nextRow = iRow;
			for( int index = 0; index < MAX_CHANNEL_ONE_GROUP; index++ )
			{
				nextRow = ( nextRow + 1 ) % MAX_CHANNEL_ONE_GROUP;
				if( ic_2_sensor_matrix[nextRow][iCol] ) break;
			}
			
			osInvalidM1[iRow][iCol]   = 1;
			osInvalidM1[nextRow][iCol] = 1;
			int productLast = osIcRawDataMatrix[iRow][iCol] * osICBaseMatrix[nextRow][iCol];
			int productNext = osIcRawDataMatrix[nextRow][iCol] * osICBaseMatrix[iRow][iCol];

			//打个补丁
			if( !productLast || !productNext )  continue;

			if( productLast > productNext + (productNext * pCfg3535->m2_ratio) / 100 )
			{
				failedChannel[iRow][iCol] = 1;
				failedChannel[nextRow][iCol] = 1;
				failerStep |= 0x02;
			}
			else if( productNext > productLast + (productLast * pCfg3535->m2_ratio) / 100 )
			{
				failedChannel[iRow][iCol] = 1;
				failedChannel[nextRow][iCol] = 1;
				failerStep |= 0x02;
			}
		}
	}
	//Print M1
	{
		AnalyzeInfo info( MAX_CHANNEL_ONE_GROUP, MAX_IX_NUM_3535 );
		PrintMaxtrixValue( m_ColorText, osIcRawDataMatrix, failedChannel, osInvalidM1, info, _T("\r\nOS - M2:\r\n") );
	}

	//OS - M3
	unsigned int sumBaseUp = 0, sumTestUp = 0;
	unsigned int sumBaseDn = 0, sumTestDn = 0;
	unsigned char RowsUp[MAX_SCAP_ROW] = {0};
	unsigned char RowsDn[MAX_SCAP_ROW] = {0};
	for( int iRow = 0; iRow < pCfg3535->rowsCnt / 2; iRow++ )
	{
		RowsUp[iRow] = iRow;
		RowsDn[iRow] = iRow + pCfg3535->rowsCnt / 2;
	}

	sumTestUp = (unsigned int)GetHarfScreenSortingMean( osSsRawDataMatrix, RowsUp, pCfg3535->rowsCnt / 2, pCfg3535->colsCnt );
	sumTestDn = (unsigned int)GetHarfScreenSortingMean( osSsRawDataMatrix, RowsDn, pCfg3535->rowsCnt / 2, pCfg3535->colsCnt );
	sumBaseUp = (unsigned int)GetHarfScreenSortingMean( pCfg3535->os_base, RowsUp, pCfg3535->rowsCnt / 2, pCfg3535->colsCnt );
	sumBaseDn = (unsigned int)GetHarfScreenSortingMean( pCfg3535->os_base, RowsDn, pCfg3535->rowsCnt / 2, pCfg3535->colsCnt );

	short normalizationData[MAX_SCAP_ROW][MAX_SCAP_COL] = {0};
// 	for( int iRow = 0; iRow < pCfg3535->rowsCnt / 2; iRow++ )
// 	{
// 		sumBaseUp += Sum( &pCfg3535->os_base[iRow][1], pCfg3535->colsCnt - 2 );
// 		sumTestUp += Sum( &osSsRawDataMatrix[iRow][1], pCfg3535->colsCnt - 2 );
// 	}
// 	for( int iRow = pCfg3535->rowsCnt / 2; iRow < pCfg3535->rowsCnt; iRow++ )
// 	{
// 		sumBaseDn += Sum( &pCfg3535->os_base[iRow][1], pCfg3535->colsCnt - 2 );
// 		sumTestDn += Sum( &osSsRawDataMatrix[iRow][1], pCfg3535->colsCnt - 2 );
// 	}
	memset( os_delta, 0, sizeof(os_delta) );
	//va channel
	for( int iRow = 0; iRow < pCfg3535->rowsCnt; iRow++ )
	{
		for( int iCol = 0; iCol < pCfg3535->colsCnt; iCol++ )
		{
			short oNormalization = 0;
			if( ( iRow * pCfg3535->colsCnt + iCol ) < pCfg3535->harf_va_channel_num )
				oNormalization = osSsRawDataMatrix[iRow][iCol] * sumBaseUp / (sumTestUp ? sumTestUp : 1);
			else
				oNormalization = osSsRawDataMatrix[iRow][iCol] * sumBaseDn / (sumTestDn ? sumTestDn : 1);

			os_delta[iRow][iCol] = oNormalization - pCfg3535->os_base[iRow][iCol];
			normalizationData[iRow][iCol] = oNormalization;
		}
	}
	//ref channel
	unsigned int sumBaseKey = 0, sumTestKey = 0;
	sumBaseKey = Sum( &pCfg3535->os_base[pCfg3535->rowsCnt][0], ref_channel_num );
	sumTestKey = Sum( &osSsRawDataMatrix[pCfg3535->rowsCnt][0], ref_channel_num );
	for( int iCol = 0; iCol < ref_channel_num; iCol++ )
	{
		unsigned int sumBaseAdd = sumBaseUp + sumBaseDn + sumBaseKey;
		unsigned int sumTestAdd = sumTestUp + sumTestDn + sumTestKey;
		os_delta[pCfg3535->rowsCnt][iCol] = osSsRawDataMatrix[pCfg3535->rowsCnt][iCol] * (sumBaseAdd) / (sumTestAdd ? sumTestAdd : 1)
			- pCfg3535->os_base[pCfg3535->rowsCnt][iCol];
	}

	{
		unsigned char failedChannel[MAX_SCAP_ROW][MAX_SCAP_COL] = {0};
		memset( failedChannel, 0 , sizeof(failedChannel) );

		//va channel
		for( int iRow = 0; iRow < pCfg3535->rowsCnt; iRow += 2 )
		{
			for( int iCol = 0; iCol < pCfg3535->colsCnt; iCol++ )
			{
				if( os_delta[iRow][iCol] > pCfg3535->m3_delta_va_max || os_delta[iRow+1][iCol] > pCfg3535->m3_delta_va_max )
				{
					failerStep |= 0x04;
					failedChannel[iRow][iCol] = 1;
					failedChannel[iRow+1][iCol] = 1;

					err_type_linkly |= 0x02;
				}

				if( os_delta[iRow][iCol] < pCfg3535->m3_delta_level2 && os_delta[iRow+1][iCol] < pCfg3535->m3_delta_level2 )
				{
					failerStep |= 0x04;
					failedChannel[iRow][iCol] = 1;
					failedChannel[iRow+1][iCol] = 1;
					if( normalizationData[iRow][iCol] < 200 && normalizationData[iRow+1][iCol] < 200 )
						err_type_linkly |= 0x01;
					else
						err_type_linkly |= 0x02;
				}

				if( os_delta[iRow][iCol] < (pCfg3535->m3_delta_level2 + pCfg3535->m3_delta_level1) || os_delta[iRow+1][iCol] < (pCfg3535->m3_delta_level2 + pCfg3535->m3_delta_level1) )
				{
					failerStep |= 0x04;
					failedChannel[iRow][iCol] = 1;
					failedChannel[iRow+1][iCol] = 1;
					if( normalizationData[iRow][iCol] < 200 && normalizationData[iRow+1][iCol] < 200 )
						err_type_linkly |= 0x01;
					else
						err_type_linkly |= 0x02;
				}

				if( os_delta[iRow][iCol] < pCfg3535->m3_delta_level1 && os_delta[iRow+1][iCol] < pCfg3535->m3_delta_level1 )
				{
					failedChannel[iRow][iCol] = 1;
					failedChannel[iRow+1][iCol] = 1;
					err_type_linkly |= 0x04;
				}

				if( os_delta[iRow][iCol] < pCfg3535->m3_delta_level2 || os_delta[iRow+1][iCol] < pCfg3535->m3_delta_level2 )
				{
					failedChannel[iRow][iCol] = 1;
					failedChannel[iRow+1][iCol] = 1;
					err_type_linkly |= 0x04;
				}
			}
		}

		for( int iCol = 0; iCol < ref_channel_num; iCol++ )
		{
			if( os_delta[pCfg3535->rowsCnt][iCol] > 2 * (pCfg3535->m3_delta_ref_max + abs(pCfg3535->m3_delta_level1)) )
			{
				failerStep |= 0x04;
				failedChannel[pCfg3535->rowsCnt][iCol] = 1;
				err_type_linkly |= 0x01;
			}
			if( os_delta[pCfg3535->rowsCnt][iCol] < -(pCfg3535->m3_delta_ref_max + abs(pCfg3535->m3_delta_level1)) )
			{
				failerStep |= 0x04;
				failedChannel[pCfg3535->rowsCnt][iCol] = 1;
				err_type_linkly |= 0x02;
			}
			if( os_delta[pCfg3535->rowsCnt][iCol] > 2 * pCfg3535->m3_delta_ref_max )
			{
				failedChannel[pCfg3535->rowsCnt][iCol] = 1;
				err_type_linkly |= 0x04;
			}
			if( os_delta[pCfg3535->rowsCnt][iCol] < -pCfg3535->m3_delta_ref_max )
			{
				failedChannel[pCfg3535->rowsCnt][iCol] = 1;
				err_type_linkly |= 0x04;
			}
		}

		AnalyzeInfo info( pCfg3535->rowsCnt, pCfg3535->colsCnt, ref_channel_num, true );
		PrintMaxtrixValue( m_ColorText, os_delta, failedChannel, pCfg3535->invalid_node, info, _T("\r\nOS - M3:\r\n") );
	}

	//M4
	if( failerStep )
	{
		if( failerStep & 0x01 ) itemNotify.UpdateItemResult( ITEM_STA_FAIL, _T("M1") );
		else if( failerStep & 0x02 ) itemNotify.UpdateItemResult( ITEM_STA_FAIL, _T("M2") );
		else if( failerStep & 0x04 ) itemNotify.UpdateItemResult( ITEM_STA_FAIL, _T("M3") );
		else itemNotify.UpdateItemResult( ITEM_STA_FAIL );

		if( err_type_linkly & 0x01 )
			TestResultInfo( _T("\r\nChannel Open likely\r\n") );
		else if( err_type_linkly & 0x02 )
			TestResultInfo( _T("\r\nChannel short likely\r\n") );

		TestResultInfo( "\r\n\r\n//OS Test is Fail\r\n", ITEM_STA_FAIL );
	}
	else
	{
		if( err_type_linkly & 0x04 )
		{
			itemNotify.UpdateItemResult( ITEM_STA_TBD );
			TestResultInfo( "\r\n\r\n//OS Test is TBD\r\n", ITEM_STA_TBD );
		}
		else
		{
			itemNotify.UpdateItemResult( ITEM_STA_PASS );
			TestResultInfo( "\r\n\r\n//OS Test is Pass\r\n", ITEM_STA_PASS );
		}
	}

	return itemNotify;
}
BOOL CTest3535::CheckTpBootSame( unsigned char* pForceburn /*= NULL*/ )
{
	BOOL bCheckBootOk = FALSE;
	unsigned int iReCode = ERROR_CODE_OK;
	ISMChip3535* iChip3535 = (ISMChip3535*)SM_ChipBase(m_deviceNo);
	if( NULL == iChip3535 )   return FALSE;

	unsigned int crc_from_tp = 0, otm_time = 0, margin_check = 0, normal_check = 0;
	iReCode = iChip3535->GetBootCheckSum( &crc_from_tp, &otm_time, &margin_check, &normal_check );
	if( iReCode != ERROR_CODE_OK ) return FALSE;

	TCHAR szBuffer[MAX_PATH] = {0};
	transformat( szBuffer, _T("ID = 0x%x"), otm_time );
	TestResultInfo( szBuffer );

	m_stOneRecord.ReleaseID = otm_time;
	/*
	0. 空芯片， GetBootCheckSum 返回值 > 0， 不会走到下面

	1. 芯片里面烧录的校验值不对并且为FFFFFFFF，可以认为是烧录过程中异常断电，按BIT检查重新烧录。
	风险点：
	    存在OTP中间部分异常的可能性，导致烧录过程因为自我检查失败而终止。对于这种重新按BIT检查烧录
	大概率任然是烧录失败的。不过存在极低可能性中的极低可能性存在某些BIT位不稳，导致不容易检查出来，不过
	这种情况按正常流程也有可能漏掉，多次尝试增加了漏掉的可能性而已。
	按BIT检测重烧

	2. 芯片里面烧录的校验值不对并且不为FFFFFFFF，对于这种情况直接报错不再尝试重烧，一般这种情况是拿了其它项目的TP
	极低可能性是最后校验值出错的可能性
	FAIL

	3. normal_check==boot_check_sum， margin_check==boot_check_sum
	PASS

	4. normal_check==boot_check_sum， margin_check！=boot_check_sum
	没写透，重新按BIT检查烧录

	5. normal_check！=boot_check_sum， margin_check==boot_check_sum
	可能有CELL被不同程度的误写，直接报错不补救
	FAIL
	6. normal_check！=boot_check_sum， margin_check！=boot_check_sum
	FAIL
	*/
	if( crc_from_tp == 0xFFFFFFFF )
	{
		if( pForceburn ) *pForceburn = TRUE;
		return FALSE;
	}
	else if( crc_from_tp != pCfg3535->boot_check_sum )
		return FALSE;
	else if( normal_check != pCfg3535->boot_check_sum )
		return FALSE;
	else if( margin_check != pCfg3535->boot_check_sum )
	{
		if( pForceburn ) *pForceburn = TRUE;
		return FALSE;
	}

	return TRUE;
}
BOOL CTest3535::CheckTail( unsigned int* pTail )
{
	BOOL bNeedTailBurn = FALSE;
	for( int index = 0; index < pCfg3535->otp_tail_cnt; index++ )
	{
		if( pCfg3535->otp_tail_buff[index + 1] != pTail[index] )
		{
			if( (pTail[index] & 0xffff00ff) == 0x000100bf && 
				(pCfg3535->otp_tail_buff[index + 1] & 0xffff00ff) == 0x000100bf )
			{
				continue;
			}
			bNeedTailBurn = TRUE;
			break;
		}
	}

	return !bNeedTailBurn;
}
unsigned int CTest3535::CheckAndBurnTail()
{
	BOOL bNeedTailBurn = FALSE;
	unsigned int iReCode = ERROR_CODE_OK;
	ISMChip3535* iChip3535 = (ISMChip3535*)SM_ChipBase(m_deviceNo);
	if( NULL == iChip3535 )   iReCode = ERROR_CODE_NO_DEVICE;

	unsigned char tailTemp[8 * 4] = {0};
	unsigned short tailAddr = pCfg3535->otp_tail_buff[0];
	unsigned char* otpData = (unsigned char*)&pCfg3535->otp_tail_buff[1];

	iReCode = iChip3535->ReadBurnSpace( tailAddr, tailTemp, pCfg3535->otp_tail_cnt * 4 );
	if( iReCode != ERROR_CODE_OK ) return iReCode;

	BOOL bCheckTail = CheckTail( (unsigned int*)tailTemp );

	if( !bCheckTail )
	{
		iReCode = iChip3535->WriteBurnSpace( tailAddr, otpData, pCfg3535->otp_tail_cnt * 4, OTP_W_TAIL| 0x10 );
		if( iReCode != ERROR_CODE_OK ) return iReCode;

		iReCode = iChip3535->ReadBurnSpace( tailAddr, tailTemp, pCfg3535->otp_tail_cnt * 4 );
		if( iReCode != ERROR_CODE_OK ) return iReCode;

		bCheckTail = CheckTail( (unsigned int*)tailTemp );
	}

	if( !bCheckTail )
	{
		iReCode = ERROR_CODE_CHECK_SUM_MISMATCH;
	}
	
	return iReCode;
}
unsigned int CTest3535::Boot_Test( NativeTestItem& itemQuote )
{
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );

	TestResultInfo( _T("\r\n------------------------------BOOT Test------------------------------\r\n") );

	ISMChip3535* iChip3535 = (ISMChip3535*)SM_ChipBase(m_deviceNo);
	if( NULL == iChip3535 )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	unsigned short booVerFromTp = 0;
	iReCode = iChip3535->GetBootVersion( &booVerFromTp );
	if( ERROR_CODE_OK != iReCode )  return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	TCHAR szBootVer[MAX_PATH] = {0};
	transformat( szBootVer, _T("Ver=0x%x"), booVerFromTp );

	unsigned char forceReburn = FALSE;
	BOOL bSameBoot = CheckTpBootSame( &forceReburn );

	//unsigned short checknum;
	//iReCode=iChip3535->CheckOtp(&checknum);
	//if(iReCode == 0)
	//{
	//	if(checknum==0x80)
	//	{
	//		TestResultInfo( _T("\r\n 0tp has been burned \r\n") );
	//	}
	//}
	//else
	//{
	//	TestResultInfo( _T("\r\nBoot 0tp Fail \r\n") );
	//	TestResultInfo( "\r\n\r\n//Boot 0tp Fail\r\n", ITEM_STA_FAIL );
	//	itemNotify.UpdateItemResult( ITEM_STA_FAIL, szBootVer );
	//	return itemNotify;
	//}
	//wasim
	//bSameBoot = FALSE;
	//LostBits = TRUE;

	if( bSameBoot )
	{
		iReCode = CheckAndBurnTail();
		if( ERROR_CODE_OK != iReCode )  return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

		TestResultInfo( _T("\r\nBoot from tp is same with Boot from setting\r\n") );
		TestResultInfo( szBootVer );
		TestResultInfo( "\r\n\r\n//BOOT Test is Pass\r\n", ITEM_STA_PASS );
		itemNotify.UpdateItemResult( ITEM_STA_PASS, szBootVer );
	}
	else
	{
		if( pCfg3535->boot_only_check && !forceReburn )
		{
			TestResultInfo( _T("\r\nBoot from tp is differant from setting\r\n") );
			TestResultInfo( szBootVer );
			TestResultInfo( "\r\n\r\n//BOOT Test is Fail\r\n", ITEM_STA_FAIL );
			itemNotify.UpdateItemResult( ITEM_STA_FAIL, szBootVer );
		}
		else
		{
			TestResultInfo( _T("\r\nDownlad new boot bin...\r\n") );
			iReCode = iChip3535->BurnBootBin( pCfg3535->bootBinSize, pCfg3535->boot_svn, m_stOneRecord.Scap.oscTrim, forceReburn );

			if( iReCode == ERROR_CODE_OK ) iReCode = CheckAndBurnTail(  );
			if( ERROR_CODE_OK != iReCode )  return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

			if( iReCode == ERROR_CODE_OK )   
			{
				SysDelay( 20 );

				iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_CTP_RST );

				SysDelay( 50 );

				/*unsigned short */booVerFromTp = 0;
				iReCode = iChip3535->GetBootVersion( &booVerFromTp );
				if( ERROR_CODE_OK != iReCode )  return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
				TCHAR szBootVer[MAX_PATH] = {0};
				transformat( szBootVer, _T("NewVer=0x%x"), booVerFromTp );

				BOOL bSameBoot2 = CheckTpBootSame(  );

				if( bSameBoot2 )
				{
					TestResultInfo( "\r\n\r\n//BOOT Test is Pass\r\n", ITEM_STA_PASS );
					TestResultInfo( szBootVer );
					itemNotify.UpdateItemResult( ITEM_STA_PASS, szBootVer );
				}
				else
				{
					TestResultInfo( _T("\r\nBoot from tp is differant from setting\r\n") );
					TestResultInfo( szBootVer );
					TestResultInfo( "\r\n\r\n//BOOT Test is Fail\r\n", ITEM_STA_FAIL );
					itemNotify.UpdateItemResult( ITEM_STA_FAIL, szBootVer );
				}
			}
			else
			{
				TestResultInfo( _T("\r\nDownload boot exception\r\n") );
				TestResultInfo( szBootVer );
				TestResultInfo( "\r\n\r\n//BOOT Test is Fail\r\n", ITEM_STA_FAIL );
				itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
			}
		}
	}

	return itemNotify;
}
unsigned int CTest3535::FindLastCfgAddress()
{
	unsigned int iReCode = ERROR_CODE_OK;
	unsigned int lastCfgAddr = 0x7f80 - 256;
	unsigned short markData = 0;

	ISMChip3535* iChip3535 = (ISMChip3535*)SM_ChipBase( m_deviceNo );
	if( NULL == iChip3535 )   return FALSE;

	while ( lastCfgAddr > 0x5000 )
	{
		iReCode = iChip3535->ReadBurnSpace( lastCfgAddr, (unsigned char*)&markData, 2 );
		if( iReCode != ERROR_CODE_OK )  return lastCfgAddr = 0;

		if( 0xffff == markData ) 
		{
			iReCode = iChip3535->ReadBurnSpace( lastCfgAddr - 256, (unsigned char*)&markData, 2 );
			if( iReCode != ERROR_CODE_OK )  return lastCfgAddr = 0;

			if( 0xffff == markData )
			{
				break;
			}
		}

		lastCfgAddr -= 256;
	}

	return lastCfgAddr + 256;
}
BOOL CTest3535::CheckConfigSame( const unsigned char* pCfg, unsigned short len )
{
	if( len != pCfg3535->cfgBinSize ) return FALSE;

	unsigned int iReCode = ERROR_CODE_OK;
	ISMChip3535* iChip3535 = (ISMChip3535*)SM_ChipBase(m_deviceNo);
	if( NULL == iChip3535 )   return FALSE;

	unsigned int check = caculate_check_sum_ex( pCfg, len );
	if( check != pCfg3535->config_check_sum )
	{
		return FALSE;
	}

	for( int index = 0; index < len; index++ ) 
	{
		if( pCfg[index] != pCfg3535->cfgBinBuffer[index] )
			return FALSE;
	}

	return TRUE;
}
unsigned int CTest3535::SetClkInFctMode( unsigned short clkDiv )
{
	unsigned char iReCode = ERROR_CODE_OK;

	unsigned short cfgBuffer[MAX_CFG_BIN_SIZE] = {0};
	iReCode = SM_ChipBase(m_deviceNo)->ReadCoreSpace( 0xD6E0, (unsigned char*)cfgBuffer, 204 );
	CHECK_RETURN_IF_FAIL( iReCode );

	unsigned short check = caculate_check_sum_u16( cfgBuffer, 204 );
	if( check )  iReCode = ERROR_CODE_CHECK_SUM_MISMATCH;
	CHECK_RETURN_IF_FAIL( iReCode );

	cfgBuffer[2]  = clkDiv;
	cfgBuffer[59] = ( cfgBuffer[59] & 0xff ) + ( ( cfgBuffer[59] >> 1 ) & 0xff00 );

	//////////////////////////////////////////////////////////////////////////
	//filter off
	if(G_XMLConfig->filter_off)
	{
		cfgBuffer[57] &= 0xf7ff;
		cfgBuffer[59] &= 0x00ff;
		cfgBuffer[60] &= 0xfffE; 
	}

	unsigned short check16 = Sum( cfgBuffer, 101 );
	cfgBuffer[101] = 1 + (~check16);

	check = caculate_check_sum_u16( cfgBuffer, 204 );
	if( check )  iReCode = ERROR_CODE_CHECK_SUM_MISMATCH;
	CHECK_RETURN_IF_FAIL( iReCode );

	iReCode = SM_ChipBase(m_deviceNo)->WriteCoreSpace( 0xD7E0, (unsigned char*)cfgBuffer, 204 );
	CHECK_RETURN_IF_FAIL( iReCode );

	unsigned int cmd2[2] = { 0x6798, 0xcd3500ff };
	iReCode = SM_ChipBase(m_deviceNo)->WriteCoreSpace( 0xdf10, (unsigned char*)cmd2, 8 );
	CHECK_RETURN_IF_FAIL( iReCode );

	SysDelay( 300 );

	return iReCode;
}
unsigned int CTest3535::ProjectCode_Test( NativeTestItem& itemQuote )
{
	unsigned int iReCode = ERROR_CODE_OK;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );

	TestResultInfo( _T("\r\n------------------------------Project Test------------------------------\r\n") );

	iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_CTP_RST );
	if( iReCode != ERROR_CODE_OK ) itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	SysDelay( 100 );

	unsigned short cfgBuffer[MAX_CFG_BIN_SIZE] = {0};
	iReCode = SM_ChipBase(m_deviceNo)->ReadCoreSpace( 0xD6E0, (unsigned char*)cfgBuffer, 204 );
	if( iReCode != ERROR_CODE_OK ) itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	TCHAR chTemp[MAX_PATH] = {0};
	unsigned char s = cfgBuffer[1] >> 10;
	unsigned char p = cfgBuffer[0] & 0x1ff;
	unsigned char v = cfgBuffer[0] >> 9;
	transformat( chTemp, _T("SoftWare Ver = %d, ProjectCode = %d, VenderID = %d\r\n"), s, p, v );
	TestResultInfo( chTemp );

	transformat( chTemp, _T("S=%d, P=%d, V=%d"), s, p, v );

	if( pCfg3535->sVersion == s && pCfg3535->pVersion == p && pCfg3535->vVersion == v )
	{
		TestResultInfo( "\r\n\r\n//Project Test is Pass\r\n", ITEM_STA_PASS );
		itemNotify.UpdateItemResult( ITEM_STA_PASS, chTemp );
	}
	else
	{
		TestResultInfo( "\r\n\r\n//Project Test is Fail\r\n", ITEM_STA_FAIL );
		itemNotify.UpdateItemResult( ITEM_STA_FAIL, chTemp );
	}
	
	return itemNotify;
}
unsigned int CTest3535::Config_Test( NativeTestItem& itemQuote )
{
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );

	TestResultInfo( _T("\r\n------------------------------CONFIG Test------------------------------\r\n") );

	ISMChip3535* iChip3535 = (ISMChip3535*)SM_ChipBase(m_deviceNo);
	if( NULL == iChip3535 )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	unsigned short cfgVerFromTp = 0;
	unsigned char configBuffer[MAX_CFG_BIN_SIZE] = {0};

	unsigned int lastOptAddr = FindLastCfgAddress();
	if( lastOptAddr <= 0x5000 || lastOptAddr > 0x7f80 )
	{
		TestResultInfo( _T("No Valid Opt Address\r\n") );
		return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( ERROR_CODE_INVALID_PARAM ) );
	}

	if( 0x7f80 != lastOptAddr )
	{
		//not empty chip
		iReCode = iChip3535->GetFirmWareConfig( lastOptAddr, configBuffer, pCfg3535->cfgBinSize );
		if( ERROR_CODE_OK != iReCode )  return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	}

	cfgVerFromTp = configBuffer[3] >> 2;
	TCHAR szConfigVer[MAX_PATH] = {0};
	transformat( szConfigVer, _T("Ver=0x%x"), cfgVerFromTp );

	BOOL bSameConfig = CheckConfigSame( configBuffer, pCfg3535->cfgBinSize );

	//wasim
	//bSameConfig = FALSE;

	if( bSameConfig )
	{
		TestResultInfo( _T("\r\nConfig from tp is same with Config from setting\r\n") );
		TestResultInfo( szConfigVer );
		TestResultInfo( "\r\n\r\n//Config Test is Pass\r\n", ITEM_STA_PASS );
		itemNotify.UpdateItemResult( ITEM_STA_PASS, szConfigVer );
	}
	else
	{
		if( pCfg3535->config_only_check )
		{
			TestResultInfo( _T("\r\nConfig from tp is differant from setting\r\n") );
			TestResultInfo( szConfigVer );
			TestResultInfo( "\r\n\r\n//Config Test is Fail\r\n", ITEM_STA_FAIL );
			itemNotify.UpdateItemResult( ITEM_STA_FAIL, szConfigVer );
		}
		else
		{
			TestResultInfo( _T("\r\nDownlad new config bin...\r\n") );
			iReCode = iChip3535->BurnConfigBin( lastOptAddr - 256, pCfg3535->cfgBinBuffer, pCfg3535->cfgBinSize );
			if( iReCode == ERROR_CODE_OK )   
			{
				memset( configBuffer, 0, sizeof(configBuffer) );
				iChip3535->GetFirmWareConfig( lastOptAddr - 256, configBuffer, pCfg3535->cfgBinSize );
				BOOL bSameConfig2 = CheckConfigSame( configBuffer, pCfg3535->cfgBinSize );

				cfgVerFromTp = configBuffer[3] >> 2;
				TCHAR szConfigVer[MAX_PATH] = {0};
				transformat( szConfigVer, _T("NewVer=0x%x"), cfgVerFromTp );

				if( bSameConfig2 )
				{
					TestResultInfo( "\r\n\r\n//Config Test is Pass\r\n", ITEM_STA_PASS );
					TestResultInfo( szConfigVer );
					itemNotify.UpdateItemResult( ITEM_STA_PASS, szConfigVer );
				}
				else
				{
					TestResultInfo( _T("\r\nConfig from tp is differant from setting\r\n") );
					TestResultInfo( szConfigVer );
					TestResultInfo( "\r\n\r\n//Config Test is Fail\r\n", ITEM_STA_FAIL );
					itemNotify.UpdateItemResult( ITEM_STA_FAIL, szConfigVer );
				}
			}
			else
			{
				TestResultInfo( _T("\r\nDownload config exception\r\n") );
				TestResultInfo( szConfigVer );
				TestResultInfo( "\r\n\r\n//Config Test is Fail\r\n", ITEM_STA_FAIL );
				itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
			}
		}
	}

	if( ERROR_CODE_OK != OSCTrim() )
		itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, szConfigVer );

	return itemNotify;
}
unsigned int CTest3535::OSCTrim()
{
	BOOL trimOk = FALSE;
	unsigned short oscTrim = 0, osTrim1 = 0, osTrim2 = 0;
	unsigned int iReCode = ERROR_CODE_OK;
	ISMChip3535* iChip3535 = (ISMChip3535*)SM_ChipBase(m_deviceNo);
	unsigned char optTrimBuffer[64] = {0}, newOscTrim[1] = {0};
	//wasim
	iReCode = iChip3535->GetOSCTrim( (unsigned short*)&osTrim1, 600000 );
	if( iReCode != ERROR_CODE_OK ) return iReCode;

	iReCode = iChip3535->GetOSCTrim( (unsigned short*)&osTrim2, 600000 );
	if( iReCode != ERROR_CODE_OK ) return iReCode;

	if((osTrim1 - osTrim2) * (osTrim1 - osTrim2) > 49)
	{
		TestResultInfo( _T("OSTrim Value Out Of Range\r\n") );
		return ERROR_CODE_INVALID_PARAM;
	}

	oscTrim = (osTrim1 + osTrim2) >> 1;

	TCHAR szBuffer[MAX_PATH] = {0};
	transformat( szBuffer, _T("\r\n\r\nOscTrim= 0x%x\r\n"), oscTrim );
	TestResultInfo( szBuffer );

	m_stOneRecord.Scap.oscTrim = oscTrim;

	if( oscTrim > 0 && oscTrim < 0xff )
	{
		iReCode = iChip3535->ReadBurnSpace( 0x7f80, optTrimBuffer, 64 );

		for( int index = 63; index >= 0; index-- )
		{
			if( 0xff != optTrimBuffer[index] )
			{
				// no need update 24*24
				if( (oscTrim - optTrimBuffer[index]) * (oscTrim - optTrimBuffer[index]) >= 576 )
				{
					TCHAR szBuffer[MAX_PATH] = {0};
					transformat( szBuffer, _T("\r\nOld OscTrim = 0x%x, Write OscTrim = 0x%x\r\n"), optTrimBuffer[index], oscTrim );
					TestResultInfo( szBuffer );

					newOscTrim[0] = oscTrim & 0xff;
					iReCode = iChip3535->WriteBurnSpace( 0x7f80 + index + 1, newOscTrim, 1, OTP_W_CHK );

					iReCode = iChip3535->ReadBurnSpace( 0x7f80 + index + 1, newOscTrim, 1 );

					if( oscTrim == newOscTrim[0] )
						trimOk = TRUE;
				}
				else
				{
					trimOk = TRUE;
				}

				break;
			}
		}

		if( !trimOk )
		{
			TCHAR szBuffer[MAX_PATH] = {0};
			transformat( szBuffer, _T("\r\nWrite First OscTrim = 0x%x\r\n"), oscTrim );
			TestResultInfo( szBuffer );

			newOscTrim[0] = oscTrim & 0xff;
			iReCode = iChip3535->WriteBurnSpace( 0x7f80, newOscTrim, 1, OTP_W_CHK );

			iReCode = iChip3535->ReadBurnSpace( 0x7f80, newOscTrim, 1 );

			if( oscTrim == newOscTrim[0] )
				trimOk = TRUE;
		}
	}
	else
	{
		TestResultInfo( _T("Get OSC Trim Exception\r\n") );
		trimOk = FALSE;
	}

	if( (iReCode == ERROR_CODE_OK) && trimOk )
	{
		
	}
	else
	{
		iReCode = ERROR_CODE_INVALID_PARAM;
		transformat( szBuffer, _T("\r\n\r\nOscTrim Failed\r\n\r\n") );
		TestResultInfo( szBuffer );
	}

	return iReCode;
}
unsigned int CTest3535::Current_Test( NativeTestItem& itemQuote )
{
	TEST_ITEM_STATUS itemStatus = ITEM_STA_NONE;
	for( int index = 0; index < 3; index++ )
	{
		itemStatus = (TEST_ITEM_STATUS)Current_TestEx( itemQuote, index );
		if( itemStatus == ITEM_STA_PASS ) break;
	}
	return itemStatus;
}
unsigned int CTest3535::Current_TestEx( NativeTestItem& itemQuote, unsigned char times )
{
	int failedCount = 0;
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );

	TestResultInfo( _T("\r\n------------------------------Current Test------------------------------\r\n") );

	ISMChip3535* iChip3535 = (ISMChip3535*)SM_ChipBase(m_deviceNo);
	if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	//new SEMI.Util.SMDefinition(0x80, "sleep"),
	//new SEMI.Util.SMDefinition(0x40, "stop"),
	//new SEMI.Util.SMDefinition(0x00, "active"),

	short deltaCurrent = 0;
	short workCurrent = 0, sleepCurrent = 0, activeCurrent = 0, emptyCurrent = 0;
	short level1[2][2] = {
		(short)pCfg3535->work_current_min, (short)(char)pCfg3535->sleep_current_min,
		(short)pCfg3535->work_current_max, (short)(pCfg3535->sleep_current_max),
	};
	iReCode = iChip3535->GetCurrent( 0x80, level1, (unsigned short*)&workCurrent, (unsigned short*)&sleepCurrent );
	if( iReCode != ERROR_CODE_OK )
	{
		failedCount++;
	}

	short level2[2][2] = {
		(short)(pCfg3535->active_current_min), 0,
		(short)(pCfg3535->active_current_max), 0,
	};
	iReCode = iChip3535->GetCurrent( 0x00, level2, (unsigned short*)&activeCurrent, (unsigned short*)&emptyCurrent );
	if( iReCode != ERROR_CODE_OK )
	{
		failedCount++;
	}

	iReCode = iChip3535->IncokeCommand( CMD_CTP_RST );
	SysDelay( 50 );

	deltaCurrent = workCurrent - sleepCurrent;

	TCHAR szTmep[MAX_PATH] = {0};

	{
		m_stOneRecord.current_mode1 = workCurrent;
		m_stOneRecord.current_mode2 = sleepCurrent;
		m_stOneRecord.current_mode3 = activeCurrent;
		m_stOneRecord.current_delta = deltaCurrent;
		transformat( szTmep, _T("\r\nmode1 = %d, mode2 = %d, mode3 = %d, delta = %d\r\n"), workCurrent, sleepCurrent, activeCurrent, deltaCurrent );
		TestResultInfo( szTmep );
	}
	if( workCurrent < pCfg3535->work_current_min )
	{
		failedCount++;
		transformat( szTmep, _T( "\r\nmode1(%d) < setting min(%d)\r\n"), workCurrent, pCfg3535->work_current_min );
		TestResultInfo( szTmep );
	}
	if( workCurrent > pCfg3535->work_current_max )
	{
		failedCount++;
		transformat( szTmep, _T( "\r\nmode1(%d) > setting max(%d)\r\n"), workCurrent, pCfg3535->work_current_max );
		TestResultInfo( szTmep );
	}
	if( sleepCurrent < pCfg3535->sleep_current_min )
	{
		failedCount++;
		transformat( szTmep, _T( "\r\nmode2(%d) < setting min(%d)\r\n"), sleepCurrent, pCfg3535->sleep_current_min );
		TestResultInfo( szTmep );
	}
	if( sleepCurrent > pCfg3535->sleep_current_max )
	{
		failedCount++;
		transformat( szTmep, _T( "\r\nmode2(%d) > setting max(%d)\r\n"), sleepCurrent, pCfg3535->sleep_current_max );
		TestResultInfo( szTmep );
	}
	if( deltaCurrent < pCfg3535->delta_current_min )
	{
		failedCount++;
		transformat( szTmep, _T( "\r\ndelta(%d) < setting min(%d)\r\n"), deltaCurrent, pCfg3535->delta_current_min );
		TestResultInfo( szTmep );
	}
	if( deltaCurrent > pCfg3535->delta_current_max )
	{
		failedCount++;
		transformat( szTmep, _T( "\r\ndelta(%d) > setting max(%d)\r\n"), deltaCurrent, pCfg3535->delta_current_max );
		TestResultInfo( szTmep );
	}
	if( activeCurrent < pCfg3535->active_current_min )
	{
		failedCount++;
		transformat( szTmep, _T( "\r\nmode3(%d) < setting min(%d)\r\n"), activeCurrent, pCfg3535->active_current_min );
		TestResultInfo( szTmep );
	}
	if( activeCurrent > pCfg3535->active_current_max )
	{
		failedCount++;
		transformat( szTmep, _T( "\r\nmode3(%d) > setting max(%d)\r\n"), activeCurrent, pCfg3535->active_current_max );
		TestResultInfo( szTmep );
	}

	if( failedCount )
	{
		itemNotify.UpdateItemResult( ITEM_STA_FAIL );
		TestResultInfo( "\r\n\r\n//Current Test is Fail\r\n", ITEM_STA_FAIL );
	}
	else
	{
		itemNotify.UpdateItemResult( ITEM_STA_PASS );
		TestResultInfo( "\r\n\r\n//Current Test is Pass\r\n", ITEM_STA_PASS );
	}

	return itemNotify;
}
unsigned int CTest3535::Base_Test( NativeTestItem& itemQuote )
{
	int failerCount = 0;
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );
	signed short baseTempBuffer[100] = {0};
	unsigned short baseMatrix[MAX_SCAP_ROW][MAX_SCAP_COL];

	TestResultInfo( _T("\r\n------------------------------Base Test------------------------------\r\n") );

	if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	ISMChip3535* iChip3535 = (ISMChip3535*)SM_ChipBase(m_deviceNo);

	int addRow = ( pCfg3535->real_channel_num - pCfg3535->va_channel_num ) ? 1 : 0;

	iReCode = iChip3535->IncokeCommand( CMD_CTP_RST );
	SysDelay( 20 );

	for( int index = 0; index < 2; index++ )
	{
		iReCode = iChip3535->SwitchMode( MODE_RAWDATA, (pCfg3535->rowsCnt + 1) * pCfg3535->colsCnt * 2 );
		if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
		SysDelay( 50 );

		iReCode = iChip3535->GetRawData( baseTempBuffer, (pCfg3535->rowsCnt + 1) * pCfg3535->colsCnt * 2 );
		if( iReCode == ERROR_CODE_OK ) break;
		if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	}

	AnalyzeInfo info( pCfg3535->rowsCnt, pCfg3535->colsCnt, pCfg3535->real_channel_num - pCfg3535->va_channel_num, true );
	ReShappingData( baseMatrix, (unsigned short*)baseTempBuffer, G_XMLConfig->real_channel_num * 2, pCfg3535->rowsCnt + 1, pCfg3535->colsCnt );
	short baseMin[MAX_SCAP_ROW][MAX_SCAP_COL] = {0}, baseMax[MAX_SCAP_ROW][MAX_SCAP_COL] = {0};
	FillMatrixUseValue( baseMin, pCfg3535->base_min );
	FillMatrixUseValue( baseMax, pCfg3535->base_max );
	
	NodeVal nodeOutRange;
	ColorText textTemp( _T("\r\nBase Data:\r\n") );
	bool bResult = AnalyzeTestResult( baseMatrix, baseMin, baseMax, pCfg3535->invalid_node, info, textTemp, nodeOutRange );
	TestResultInfo( textTemp );
	if( !bResult )
	{
		failerCount++;
		LPCTSTR strHead = _T("\r\n//========= Out of Threshold in BaseTest: \r\n");
		PrintNodeValue( m_ColorText, &nodeOutRange, strHead );
	}

	if( !failerCount )
	{
		BOOL bAllInvalid = TRUE;
		for( int iRow = 0; iRow < pCfg3535->rowsCnt; iRow++ )
		{
			for( int iCol = 0; iCol < pCfg3535->colsCnt; iCol++ )
			{
				if( 4096 != baseMatrix[iRow][iCol] )
					bAllInvalid = FALSE;
				if( 2048 != baseMatrix[iRow][iCol] )
					bAllInvalid = FALSE;
			}
		}
		if( bAllInvalid ) 
		{
			TestResultInfo( _T("\r\nBase Data Is Invalid\r\n") );
			failerCount++;
		}
	}

	if( failerCount )
	{
		itemNotify.UpdateItemResult( ITEM_STA_FAIL );
		TestResultInfo( "\r\n\r\n//Base Test is Fail\r\n", ITEM_STA_FAIL );
	}
	else
	{
		itemNotify.UpdateItemResult( ITEM_STA_PASS );
		TestResultInfo( "\r\n\r\n//Base Test is Pass\r\n", ITEM_STA_PASS );
	}

	return itemNotify;
}
void CTest3535::PrepareSimulate( SimulateData& sm )
{
	unsigned char cmdID = sm.itemID & 0xff;
	unsigned char dataIndex = (sm.itemID >> 8) & 0xff;
	unsigned char sumCnt = 1;

	if( CMD_OPEN_TST == cmdID )
	{
		sm.itemArray[36] = 0x6306;
		sm.itemArray[37] = 0x5555;
		unsigned short exeParam = pCfg3535->integral;
		exeParam = (exeParam << 8) + pCfg3535->scale_a;
		exeParam = (exeParam << 8) + pCfg3535->scale_b;
		sm.itemID |= (exeParam << 16);
	}
	else if( CMD_FSD_TST == cmdID )
	{
		sumCnt = 1;
		sm.itemArray[0x50 >> 1] = 0x5555;
		dataIndex ? (sm.itemID |= pCfg3535->s_clk << 16) : (sm.itemID |= pCfg3535->f_clk << 16);
	}

	for( int iRow = 0; iRow < sm.rows; iRow++ )
	{
		for( int iCol = 0; iCol < sm.cols; iCol++ )
		{
			int index = iRow * sm.cols + iCol;
			if( index >= pCfg3535->real_channel_num ) break;

			int icPosition = pCfg3535->sensor_2_ic_map[index];
			sm.itemArray[icPosition] = sm.itemData[iRow][iCol] * sumCnt;
		}
	}
}