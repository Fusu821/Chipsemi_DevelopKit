#include "checksum.h"
#include "Test5562.h"
#include "../Config/Config5562.h"
#include "Rolling.h"
#include <list>
#include "automaticInterface.h"
//#include <numeric>

extern CConfig* G_XMLConfig;
#define pCfg5562   (( const CConfig5562*)G_XMLConfig)
REGIST_RUNTIME_CLASS(TEST_TYPE, (TEST_TYPE)SEMI_IC_5562, CTest5562)

typedef CTest5562 CTest5460S;
REGIST_RUNTIME_CLASS(TEST_TYPE, (TEST_TYPE)SEMI_IC_5460S, CTest5460S)

typedef CTest5562 CTest5560;
REGIST_RUNTIME_CLASS(TEST_TYPE, (TEST_TYPE)SEMI_IC_5560, CTest5560)

typedef CTest5562 CTest7562;
REGIST_RUNTIME_CLASS(TEST_TYPE, (TEST_TYPE)SEMI_IC_7562, CTest7562)

// struct SortPacket 
// {
// 	double dpVal;
// 	int dpRow;
// 	int dpCol;
// 	SortPacket( int row, int col, double val = 0 )
// 		:dpRow(row)
// 		,dpCol(col)
// 		,dpVal(val)
// 	{
// 
// 	}
// 	bool operator < ( const SortPacket& cmp )
// 	{
// 		return this->dpVal < cmp.dpVal;
// 	}
// };

CTest5562::CTest5562()
:CTestBase()
{
// 	memset( m_CurTestItemAddr, 0, sizeof(m_CurTestItemAddr) );
// 	m_CurTestItemAddr[TEST_ITEM_MTK_CONNECT]     = new CRunTimeMethod<CTestBase>( this, &CTestBase::MTKConnectTest );
// 	m_CurTestItemAddr[TEST_ITEM_TP_WAIT]         = new CRunTimeMethod<CTestBase>( this, &CTestBase::TP_WaitTest );
// 	m_CurTestItemAddr[TEST_ITEM_TP_REMOVE]       = new CRunTimeMethod<CTestBase>( this, &CTestBase::TP_RemoveTest );
// 	m_CurTestItemAddr[TEST_ITEM_INT_TEST]        = new CRunTimeMethod<CTest5562>( this, &CTest5562::INT_Test );
// 	m_CurTestItemAddr[TEST_ITEM_RESET_TEST]      = new CRunTimeMethod<CTest5562>( this, &CTest5562::Reset_Test );
// 	m_CurTestItemAddr[TEST_ITEM_FSD_TEST_5562]   = new CRunTimeMethod<CTest5562>( this, &CTest5562::FSD_Test );
// 	m_CurTestItemAddr[TEST_ITEM_OS_TEST_5562]    = new CRunTimeMethod<CTest5562>( this, &CTest5562::OS_Test );
// 	m_CurTestItemAddr[TEST_ITEM_BOOT_TEST]       = new CRunTimeMethod<CTest5562>( this, &CTest5562::Boot_Test );
// 	m_CurTestItemAddr[TEST_ITEM_CFG_TEST]        = new CRunTimeMethod<CTest5562>( this, &CTest5562::Config_Test );
// 	m_CurTestItemAddr[TEST_ITEM_BUTTON_TEST]     = new CRunTimeMethod<CTest5562>( this, &CTestBase::Graph_Test );
// 	m_CurTestItemAddr[TEST_ITEM_LINEARLY_TEST]   = new CRunTimeMethod<CTest5562>( this, &CTestBase::Graph_Test );
// 	m_CurTestItemAddr[TEST_ITEM_FREE_PAINT_TEST] = new CRunTimeMethod<CTest5562>( this, &CTestBase::Graph_Test );
// 	m_CurTestItemAddr[TEST_ITEM_CURRENT_TEST]    = new CRunTimeMethod<CTest5562>( this, &CTest5562::Current_Test );
}
CTest5562::~CTest5562()
{
	
}
void CTest5562::SetTestContext( unsigned char deviceNo, NativeTestInterface* native )
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
		info.bSelected = pCfg5562->mtk_selected;
		info.jumpIfNG = false;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTestBase>( this, &CTestBase::MTKConnectTest );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_TP_WAIT;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("Waiting"), lengthof(_T("Waiting")));
		info.bSelected = pCfg5562->way_to_start == START_BY_AUTO;
		info.jumpIfNG = false;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTestBase>( this, &CTestBase::TP_WaitTest );
	}

	//////////////////////////////////////////////////////////////////////////
	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_FRT_TEST_5562;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("FRT"), lengthof(_T("FRT")));
		info.bSelected = pCfg5562->frt_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest5562>( this, &CTest5562::FRT_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_BOOT_TEST;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("Boot"), lengthof(_T("Boot")));
		info.bSelected = pCfg5562->boot_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest5562>( this, &CTest5562::Boot_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_CFG_TEST;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("Config"), lengthof(_T("Config")));
		info.bSelected = pCfg5562->config_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest5562>( this, &CTest5562::Config_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_OSCTRIM_TEST_5562;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("OSCTrim"), lengthof(_T("OSCTrim")));
		info.bSelected = pCfg5562->osctrim_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest5562>( this, &CTest5562::OSCTrim_Test );
	}
	
	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_OS_TEST_5562;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("Short"), lengthof(_T("Short")));
		info.bSelected = pCfg5562->short_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest5562>( this, &CTest5562::Short_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_MISC_TEST_5562;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("MISC"), lengthof(_T("MISC")));
		info.bSelected = pCfg5562->misc_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest5562>( this, &CTest5562::MISC_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_IOVOL_TEST_5562;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("IOVoltage"), lengthof(_T("IOVoltage")));
		info.bSelected = pCfg5562->iovol_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest5562>( this, &CTest5562::IOVoltage_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_INT_TEST;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("INT"), lengthof(_T("INT")));
		info.bSelected = pCfg5562->int_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest5562>( this, &CTest5562::INT_Test );
	}
	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_RESET_TEST;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("Reset"), lengthof(_T("Reset")));
		info.bSelected = pCfg5562->reset_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest5562>( this, &CTest5562::Reset_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_CURRENT_TEST;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("Current"), lengthof(_T("Current")));
		info.bSelected = pCfg5562->current_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest5562>( this, &CTest5562::Current_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_PROJECT_CODE;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("Project"), lengthof(_T("Project")));
		info.bSelected = platform_required_sel;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest5562>( this, &CTest5562::ProjectCode_Test );
	}

	//{
	//	InternalItemInfo& info = m_arrayItemInfo[indexSel++];
	//	info.item.ucDevice = m_deviceNo;
	//	info.item.testCode = TEST_ITEM_BASE_TEST_5562;
	//	info.item.testResult = ITEM_STA_NONE;
	//	copytextto(info.item.testName, _T("Base"), lengthof(_T("Base")));
	//	info.bSelected = pCfg5562->base_selected;
	//	if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest5562>( this, &CTest5562::Base_Test );
	//}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_SCAP_RAWDATA_TEST_5562;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("ScapData"), lengthof(_T("ScapData")));
		info.bSelected = pCfg5562->scap_rawdata_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest5562>( this, &CTest5562::ScapRawData_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_STC_5562;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("STC"), lengthof(_T("STC")));
		info.bSelected = pCfg5562->stc_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest5562>( this, &CTest5562::STC_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_MCAP_RAWDATA_5562;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("McapData"), lengthof(_T("McapData")));
		info.bSelected = pCfg5562->mcap_rawdata_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest5562>( this, &CTest5562::MCapRawData_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_NOISE_TEST_5562;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("Noise"), lengthof(_T("Noise")));
		info.bSelected = pCfg5562->noise_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest5562>( this, &CTest5562::Noise_Test );
	}
	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_BASE_TEST_5562;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("Base"), lengthof(_T("Base")));
		info.bSelected = pCfg5562->base_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest5562>( this, &CTest5562::Base_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_WBASE_TEST_5562;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("WBase"), lengthof(_T("WBase")));
		info.bSelected = pCfg5562->wbase_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest5562>( this, &CTest5562::WBase_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_FSD_TEST_5562;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("FSD"), lengthof(_T("FSD")));
		info.bSelected = pCfg5562->fsd_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest5562>( this, &CTest5562::FSD_Test );
	}
	
	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_BUTTON_TEST;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("Button"), lengthof(_T("Button")));
		info.bSelected = pCfg5562->button_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest5562>( this, &CTest5562::Graph_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_LINEARLY_TEST;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("Linearly"), lengthof(_T("Linearly")));
		info.bSelected = pCfg5562->LINEARITY_TEST;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest5562>( this, &CTest5562::Graph_Test );
	}

    {
        InternalItemInfo& info = m_arrayItemInfo[indexSel++];
        info.item.ucDevice = m_deviceNo;
        info.item.testCode = TEST_ITEM_EXP_LINEARLY_TEST;
        info.item.testResult = ITEM_STA_NONE;
        copytextto(info.item.testName, _T("ExpLinearly"), lengthof(_T("ExpLinearly")));
        info.bSelected = pCfg5562->EXP_LINEARITY_TEST;
        if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest5562>( this, &CTest5562::Graph_Test );
    }

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_FREE_PAINT_TEST;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("FreePaint"), lengthof(_T("FreePaint")));
		info.bSelected = pCfg5562->FREEPAINT_TEST;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest5562>( this, &CTest5562::Graph_Test );
	}

    //////////////////////////////////////////////////////////////////////////
	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_TP_REMOVE;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("Removing"), lengthof(_T("Removing")));
		info.bSelected = (pCfg5562->way_to_start == START_BY_AUTO || pCfg5562->way_to_start == START_BY_SN) && (pCfg5562->need_remove_ic != 1);
		info.jumpIfNG = false;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest5562>( this, &CTest5562::TP_RemoveTest );
	}

	if( SM_ChipBase(m_deviceNo) )
	{
		CtpHalCfg halCfg;
		halCfg.protocalType = (unsigned char)pCfg5562->protocalType;
		halCfg.speed = pCfg5562->Speed;
		halCfg.IIC.slaveAddr = pCfg5562->I2cAddr;
		halCfg.vddVoltage = pCfg5562->vddVotage;
		halCfg.iovddVotage = pCfg5562->ioVddVotage;
		halCfg.vihVotage = pCfg5562->vihVotage;
		halCfg.icType = pCfg5562->IcType;
		SM_ChipBase(m_deviceNo)->SetCommContext( halCfg );
	}

	ActionToXmlConfig();
}
void CTest5562::ICArrayToSensorMatrix( unsigned short (&dataMappinged)[2][MAX_MCAP_COL], unsigned short* const dataToMapping, unsigned int dataCnt, unsigned short maxRows, unsigned short* pMaxCols )
{
	for( int iTx = 0; iTx < pCfg5562->colsCnt; iTx++ )
	{
		unsigned short icChannel = pCfg5562->sensor_2_ic_map[iTx];
		dataMappinged[0][iTx] = dataToMapping[icChannel];
	}
	for( int iRx = 0; iRx < pCfg5562->rowsCnt; iRx++ )
	{
		unsigned short icChannel = pCfg5562->sensor_2_ic_map[iRx + MAX_TX_NUM_5562];
		dataMappinged[1][iRx] = dataToMapping[icChannel + MAX_TX_NUM_5562];
	}
}
// void CTest5562::ICArrayToSensorMatrix( unsigned short (&dataMappinged)[MAX_MCAP_ROW][MAX_MCAP_COL], unsigned short* const dataToMapping, unsigned int dataCnt, unsigned short maxRows, unsigned short maxCols )
// {
// 	memset( dataMappinged, 0, sizeof( dataMappinged ) );
// 
// 	for( int iRow = 0; iRow < maxRows; iRow++ )
// 	{
// 		for( int iCol = 0; iCol < maxCols; iCol++ )
// 		{
// 			int index = (int)iRow * maxCols + iCol;
// 			if( index >= (int)dataCnt )   continue;
// 
// 			int icPosition = pCfg5562->sensor_2_ic_map[index];
// 			dataMappinged[iRow][iCol] = dataToMapping[icPosition];
// 		}
// 	}
// 	for( int index = (int)maxRows * maxCols; index < (int)dataCnt; index++ )
// 	{
// 		int iCol = index - maxRows * maxCols + maxCols;
// 		int icPosition = pCfg5562->sensor_2_ic_map[index];
// 		dataMappinged[maxRows - 1][iCol] = dataToMapping[icPosition];
// 	}
// }
// void CTest5562::ICMatrixToSensorMatrix( unsigned short (&dataMappinged)[MAX_MCAP_ROW][MAX_MCAP_COL],
// 	unsigned short mappedRow,
// 	unsigned short mappedCol,
// 	const unsigned short (&dataToMapping)[MAX_MCAP_ROW][MAX_MCAP_COL],
// 	unsigned short mappingRow,
// 	unsigned short mappingCol )
// {
// 	memset( dataMappinged, 0, sizeof( dataMappinged ) );
// 
// 	for( int iRow = 0; iRow < mappedRow; iRow++ )
// 	{
// 		for( int iCol = 0; iCol < mappedCol; iCol++ )
// 		{
// 			int index = iRow * mappedCol + iCol;
// 			if( index >= (int)pCfg5562->real_channel_num )   continue;
// 
// 			int icPosition = pCfg5562->sensor_2_ic_map[index];
// 			int icRow = icPosition / mappingCol;
// 			int icCol = icPosition % mappingCol;
// 
// 			dataMappinged[iRow][iCol] = dataToMapping[icRow][icCol];
// 		}
// 	}
// }
// void CTest5562::SensorMatrixToIcMatrix( unsigned short (&dataMappinged)[MAX_MCAP_ROW][MAX_MCAP_COL],
// 	unsigned short mappedRow,
// 	unsigned short mappedCol,
// 	const unsigned short (&dataToMapping)[MAX_MCAP_ROW][MAX_MCAP_COL],
// 	unsigned short mappingRow,
// 	unsigned short mappingCol )
// {
// 	memset( dataMappinged, 0, sizeof( dataMappinged ) );
// 
// // 	for( int iRow = 0; iRow < mappedRow; iRow++ )
// // 	{
// // 		for( int iCol = 0; iCol < mappedCol; iCol++ )
// // 		{
// // 			int index = iRow * mappedCol + iCol;
// // 		    int sensorPos = pCfg5562->ic_2_sensor_map[index] - 1;
// // 			if( sensorPos >= MAX_MCAP_CHANNEL )
// // 				continue;
// // 			int sensorRow = sensorPos / mappingCol;
// // 			int sensorCol = sensorPos % mappingCol;
// // 
// // 			dataMappinged[iRow][iCol] = dataToMapping[sensorRow][sensorCol];
// // 		}
// // 	}
// 
// 	for( int iRow = 0; iRow < mappingRow; iRow++ )
// 	{
// 		for( int iCol = 0; iCol < mappingCol; iCol++ )
// 		{
// 			int index = iRow * mappingCol + iCol;
// 			if( index >= (int)pCfg5562->real_channel_num )   continue;
// 
// 			int icPosition = pCfg5562->sensor_2_ic_map[index];
// 			int icRow = icPosition / mappedCol;
// 			int icCol = icPosition % mappedCol;
// 
// 			dataMappinged[icRow][icCol] = dataToMapping[iRow][iCol];
// 		}
// 	}
// }
BOOL CTest5562::CheckTpBootSame( )
{
	BOOL bCheckBootOk = FALSE;
	unsigned int iReCode = ERROR_CODE_OK;
	ISMChip5562* iChip5562 = (ISMChip5562*)SM_ChipBase(m_deviceNo);
	if( NULL == iChip5562 )   return FALSE;

	unsigned int crc_from_tp = 0, otm_time = 0, crc_bootloader = 0;
	iReCode = iChip5562->GetNewBootCheckSum( &crc_from_tp, &otm_time ,&crc_bootloader);
	if( iReCode != ERROR_CODE_OK )  return FALSE;

	//TCHAR szBuffer[MAX_PATH] = {0};
	//transformat( szBuffer, _T("ID = 0x%x,   %d-%d, %d:%d:%d"), otm_time, (otm_time>>22)&0xf, (otm_time>>17)&0x1f,(otm_time>>12)&0x1f, (otm_time>>6)&0x3f, otm_time&0x3f );
	//TestResultInfo( szBuffer );
	TestResultInfoR( _T("ID = 0x%x,   %d-%d, %d:%d:%d"), otm_time, (otm_time>>22)&0xf, (otm_time>>17)&0x1f,(otm_time>>12)&0x1f, (otm_time>>6)&0x3f, otm_time&0x3f );
	
	if( (crc_from_tp == pCfg5562->boot_check_sum) && (crc_bootloader == pCfg5562->boot_loader_check_sum))
		return TRUE;

	return FALSE;
}
BOOL CTest5562::CheckFlashEraseOk()
{
	unsigned int iReCode = ERROR_CODE_OK;
	ISMChip5562* iChip5562 = (ISMChip5562*)SM_ChipBase(m_deviceNo);
	if( NULL == iChip5562 )  return FALSE;

	unsigned char readBuffer[4096] = {0};
	unsigned int writeData = 0x5ee5e55e, readData = 0x00000000;
	iReCode = iChip5562->WriteBurnSpace( 0xd000, (const unsigned char*)&writeData, sizeof(writeData), OTP_W_CHK | TLK_DATACHK_EX1 );
	if( iReCode != ERROR_CODE_OK ) return FALSE;

	iReCode = iChip5562->ReadBurnSpace( 0xd000, (unsigned char*)&readData, sizeof(writeData) );
	if( iReCode != ERROR_CODE_OK ) return FALSE;

	if( writeData != readData )
	{
		TestResultInfo( _T("Check Erase Falsh step 1 Failed\r\n") );
		return FALSE;
	}

	writeData = 0xe55e5ee5, readData = 0x00000000;
	iReCode = iChip5562->WriteBurnSpace( 0xd000, (const unsigned char*)&writeData, sizeof(writeData), OTP_W_CHK | TLK_DATACHK_EX1 );
	if( iReCode != ERROR_CODE_OK ) return FALSE;

	iReCode = iChip5562->ReadBurnSpace( 0xd000, (unsigned char*)&readData, sizeof(writeData) );
	if( iReCode != ERROR_CODE_OK ) return FALSE;

	if( writeData != readData )
	{
		TestResultInfo( _T("Check Erase Falsh step 2 Failed\r\n") );
		return false;
	}

	writeData = 0xffffffff;
	iReCode = iChip5562->WriteBurnSpace( 0xd000, (const unsigned char*)&writeData, sizeof(writeData), OTP_W_CHK | TLK_DATACHK_EX1 );
	if( iReCode != ERROR_CODE_OK ) return FALSE;

	iReCode = iChip5562->ReadBurnSpace( 0xd000, readBuffer, sizeof(readBuffer) );
	if( iReCode != ERROR_CODE_OK ) return FALSE;

	for( int index = 0; index < sizeof(readBuffer); index++ )
	{
		if( 0xff != readBuffer[index] ) 
		{
		    TestResultInfo( _T("Check Erase Falsh step 3 Failed\r\n") );
			return FALSE;
		}
	}

	//Gen ICID
	memset( readBuffer, 0xff, sizeof(readBuffer) );
	iReCode = iChip5562->ReadBurnSpace( 0xc000, readBuffer, 8 );
	if( iReCode != ERROR_CODE_OK ) return FALSE;

	UINT32* pIntData = (UINT32*)readBuffer;
	if( 0xffffffff == pIntData[0] && 0xffffffff == pIntData[1] )
	{
		SYSTEMTIME SysTime;
		::GetLocalTime(&SysTime);
		pIntData[0] = (SysTime.wMonth << 22) + (SysTime.wDay << 17) + (SysTime.wHour << 12) + (SysTime.wMinute << 6) + SysTime.wSecond;
		pIntData[1] = GetTickCount();
		iChip5562->WriteBurnSpace( 0xc000, readBuffer, 8, OTP_W_CHK | TLK_DATACHK_EX1 );
		if( iReCode != ERROR_CODE_OK ) return FALSE;
		
		SysDelay( 10 );
	}

	m_stOneRecord.ReleaseID = *(UINT64*)readBuffer;

	//TCHAR szBuffer[MAX_PATH] = {0};
	UINT32 otm_time = *(UINT32*)&m_stOneRecord.ReleaseID;
	//transformat( szBuffer, _T("ICID = 0x%llx,   %d-%d, %d:%d:%d\r\n"), m_stOneRecord.ReleaseID, (otm_time>>22)&0xf, (otm_time>>17)&0x1f,(otm_time>>12)&0x1f, (otm_time>>6)&0x3f, otm_time&0x3f );
	//TestResultInfo( szBuffer );
	TestResultInfoR( _T("ICID = 0x%llx,   %d-%d, %d:%d:%d\r\n"), m_stOneRecord.ReleaseID, (otm_time>>22)&0xf, (otm_time>>17)&0x1f,(otm_time>>12)&0x1f, (otm_time>>6)&0x3f, otm_time&0x3f );
	

	return TRUE;
}
unsigned int CTest5562::Boot_Test( NativeTestItem& itemQuote )
{
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );

	TestResultInfo( _T("\r\n------------------------------BOOT Test------------------------------\r\n") );

	ISMChip5562* iChip5562 = (ISMChip5562*)SM_ChipBase(m_deviceNo);
	if( NULL == iChip5562 )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

// 	if( !CheckFlashEraseOk() )
// 	{
// 		TestResultInfo( _T("Check Erase Falsh Failed\r\n") );
// 		return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( ERROR_CODE_CHECK_SUM_MISMATCH ) );
// 	}

	unsigned short booVerFromTp = 0;
	iReCode = iChip5562->GetBootVersion( &booVerFromTp );
	if( ERROR_CODE_OK != iReCode )  return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	//TCHAR szBootVer[MAX_PATH] = {0};
	//transformat( szBootVer, _T("Ver=0x%x"), booVerFromTp );

	BOOL bSameBoot = CheckTpBootSame();

	//wasim
	//bSameBoot = FALSE;

	if( bSameBoot )
	{
		TestResultInfo( _T("\r\nBoot from tp is same with Boot from setting\r\n") );
		//TestResultInfo( szBootVer );
		auto szBootVer = TestResultInfoR( _T("Ver=0x%x"), booVerFromTp );
		TestResultInfo( "\r\n\r\n//BOOT Test is Pass\r\n", ITEM_STA_PASS );
		itemNotify.UpdateItemResult( ITEM_STA_PASS, szBootVer );
	}
	else
	{
		if( pCfg5562->boot_only_check )
		{
			TestResultInfo( _T("\r\nBoot from tp is differant from setting\r\n") );
			//TestResultInfo( szBootVer );
			auto szBootVer = TestResultInfoR( _T("Ver=0x%x"), booVerFromTp );
			TestResultInfo( "\r\n\r\n//BOOT Test is Fail\r\n", ITEM_STA_FAIL );
			itemNotify.UpdateItemResult( ITEM_STA_FAIL, szBootVer );
		}
		else
		{
			//SM_CommBase(m_deviceNo)->SetIoVoltage(0x6E, pCfg5562->vddVotage == pCfg5562->ioVddVotage ? 0x6E : pCfg5562->ioVddVotage);
			//SysDelay(50);

			TestResultInfo( _T("\r\nDownlad new boot bin...\r\n") );
			iReCode = iChip5562->BurnBootBin( pCfg5562->bootBinSize, pCfg5562->boot_svn, m_stOneRecord.Mcap.oscTrim );
			if( iReCode == ERROR_CODE_OK )   
			{
				/*unsigned short */booVerFromTp = 0;
				iReCode = iChip5562->GetBootVersion( &booVerFromTp );
				if( ERROR_CODE_OK != iReCode )  return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
				//TCHAR szBootVer[MAX_PATH] = {0};
				//transformat( szBootVer, _T("NewVer=0x%x"), booVerFromTp );

				BOOL bSameBoot2 = CheckTpBootSame();
				if( bSameBoot2 )
				{
					TestResultInfo( "\r\n\r\n//BOOT Test is Pass\r\n", ITEM_STA_PASS );
					//TestResultInfo( szBootVer );
					auto szBootVer = TestResultInfoR( _T("NewVer=0x%x"), booVerFromTp );
					itemNotify.UpdateItemResult( ITEM_STA_PASS, szBootVer );
				}
				else
				{
					TestResultInfo( _T("\r\nBoot from tp is differant from setting\r\n") );
					//TestResultInfo( szBootVer );
					auto szBootVer = TestResultInfoR( _T("NewVer=0x%x"), booVerFromTp );
					TestResultInfo( "\r\n\r\n//BOOT Test is Fail\r\n", ITEM_STA_FAIL );
					itemNotify.UpdateItemResult( ITEM_STA_FAIL, szBootVer );
				}
			}
			else
			{
				TestResultInfo( _T("\r\nDownload boot exception\r\n") );
				//TestResultInfo( szBootVer );
				auto szBootVer = TestResultInfoR( _T("Ver=0x%x"), booVerFromTp );
				TestResultInfo( "\r\n\r\n//BOOT Test is Fail\r\n", ITEM_STA_FAIL );
				itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
			}

			//SM_CommBase(m_deviceNo)->SetIoVoltage(pCfg5562->vddVotage, pCfg5562->ioVddVotage);
			//SysDelay(50);
		}
	}

	return itemNotify;
}
BOOL CTest5562::CheckConfigSame( const unsigned char* pCfg, unsigned short len )
{
	if( len != pCfg5562->cfgBinSize ) return FALSE;

	unsigned int iReCode = ERROR_CODE_OK;
	ISMChip5562* iChip5562 = (ISMChip5562*)SM_ChipBase(m_deviceNo);
	if( NULL == iChip5562 )   return FALSE;

	unsigned int check = caculate_check_sum_u32( (unsigned int*)pCfg, len );
	if( check != pCfg5562->config_check_sum )
	{
		return FALSE;
	}

	for( int index = 0; index < len; index++ ) 
	{
		if( pCfg[index] != pCfg5562->cfgBinBuffer[index] )
			return FALSE;
	}

	return TRUE;
}
unsigned int CTest5562::MakeTraceRecord()
{
	unsigned int iReCode = ERROR_CODE_OK;
#ifdef _MSC_VER
	ISMChip5562* iChip5562 = (ISMChip5562*)SM_ChipBase(m_deviceNo);
	//char szBuffer[MAX_PATH] = {0};
	unsigned char record_buffer[3*1024] = {0};
	//auto record_buffer = new unsigned char[2*1024];
	Trace_Info* traceInfo = (Trace_Info*)record_buffer;
	One_Record* record = (One_Record*)(record_buffer + sizeof(Trace_Info));
	tstring userInfo = pCfg5562->szUserRecord ? tstring(pCfg5562->szUserRecord) : _T("");
	unsigned short crc = caculate_check_sum_ex( (unsigned char*)userInfo.c_str(), userInfo.length() + 1 ) >> 16;

	iReCode = iChip5562->ReadBurnSpace( AddrMakeTraceRecord, record_buffer, sizeof(Trace_Info) );
	if(iReCode != ERROR_CODE_OK) return iReCode;

	BOOL bExitSameUserRecord = FALSE;
	if(traceInfo->trace_cnt + traceInfo->reverse == 0xff)
	{
		traceInfo->tlen =  traceInfo->tlen >= 0x800 ? 0x800 : traceInfo->tlen ;
		iReCode = iChip5562->ReadBurnSpace( AddrMakeTraceRecord + sizeof(Trace_Info), (unsigned char*)record, traceInfo->tlen );
		if(iReCode != ERROR_CODE_OK) return iReCode;

		for(int index = 0; index < traceInfo->trace_cnt; index++)
		{
			if(0 != caculate_check_sum_u16((unsigned short*)record, sizeof(One_Record))) break;

			unsigned char textOutCnt = 0;
			if(m_pNativeIntr->DebugMode())
			{
				textOutCnt++;
				//transformat(szBuffer, _T("0x%04X CRC = 0x%04x, %d-%d, %d:%d:%d	"), record->vid_pid, record->sz_crc, (record->time>>22)&0xf, (record->time>>17)&0x1f, 
				//	(record->time>>12)&0x1f, (record->time>>6)&0x3f, record->time&0x3f);
				//TestResultInfo( szBuffer );
				TestResultInfoR( _T("0x%010llX CRC = 0x%04x, %d-%d, %d:%d:%d	"), record->vid_pid, record->sz_crc, (record->time>>22)&0xf, (record->time>>17)&0x1f, 
					(record->time>>12)&0x1f, (record->time>>6)&0x3f, record->time&0x3f );
			}

			if((record->szlen > 0) && record->szlen == align_4(lengthof((char*)(record + 1)) + 1))
			{
				textOutCnt++;
				//transformat(szBuffer, _T("%s"), (char*)(record + 1) );
				//TestResultInfo(szBuffer);
				TestResultInfoR(_T("%s"), (char*)(record + 1) );
			}

			if(textOutCnt > 0)
			{
				TestResultInfo( _T("\r\n") );
			}

			if(record->sz_crc == crc)
			{
				bExitSameUserRecord = TRUE;
			}

			record = (One_Record*)((unsigned char*)record + record->szlen + sizeof(One_Record));
		}
	}
	else if(0xff == traceInfo->trace_cnt && 0xff == traceInfo->reverse)
	{
		traceInfo->tlen = traceInfo->trace_cnt = 0;
	}
	else
	{
		//compatible to v5
		//delete[] record_buffer;
		return iReCode;
	}

	if(traceInfo->tlen + sizeof(Trace_Info) + sizeof(One_Record) + align_4(userInfo.length() + 1) > 0x800)
	{
		TestResultInfo(_T("\r\nTrace Info Exceed Max Buffer Count\r\n"));
	}
	else
	{
		SYSTEMTIME SysTime;
		::GetLocalTime(&SysTime);

		record->reserve = 0;
		record->record_crc = 0;
		record->vid_pid = pCfg5562->vid_pid;
		record->time = (SysTime.wMonth << 22) + (SysTime.wDay << 17) + (SysTime.wHour << 12) + (SysTime.wMinute << 6) + SysTime.wSecond;

		if(bExitSameUserRecord)
		{
			record->szlen = 0;
			record->sz_crc = crc;
		}
		else
		{
			record->szlen = align_4(userInfo.length() + 1);
			copytextto((TCHAR*)(record + 1), record->szlen, userInfo.c_str(), record->szlen);
			record->sz_crc = crc;
		}
		record->record_crc = 1 + (~caculate_check_sum_u16((unsigned short*)record, sizeof(One_Record)));

		traceInfo->trace_cnt++;
		traceInfo->reverse = ~traceInfo->trace_cnt;
		traceInfo->tlen += record->szlen + sizeof(One_Record);

		iReCode = iChip5562->WriteBurnSpace(AddrMakeTraceRecord, record_buffer, traceInfo->tlen + sizeof(Trace_Info), OTP_W_CHK | TLK_DATACHK_EX1);
		SysDelay(10);

		//transformat(szBuffer, _T("0x%04X CRC = 0x%04x, %d-%d, %d:%d:%d	"), record->vid_pid, record->sz_crc, (record->time>>22)&0xf, (record->time>>17)&0x1f, 
		//	(record->time>>12)&0x1f, (record->time>>6)&0x3f, record->time&0x3f);
		//TestResultInfo(szBuffer);
		TestResultInfoR(_T("0x%010llX CRC = 0x%04x, %d-%d, %d:%d:%d	"), record->vid_pid, record->sz_crc, (record->time>>22)&0xf, (record->time>>17)&0x1f, 
			(record->time>>12)&0x1f, (record->time>>6)&0x3f, record->time&0x3f);

		if(record->szlen > 0)
		{
			//transformat(szBuffer, _T("%s"), (char*)(record + 1) );
			//TestResultInfo(szBuffer);
			TestResultInfoR( _T("%s"), (char*)(record + 1));
		}

		TestResultInfo( _T("\r\n") );
	}
	//delete[] record_buffer;
#endif

	return iReCode;
}
unsigned int CTest5562::ProjectCode_Test( NativeTestItem& itemQuote )
{
	unsigned int iReCode = ERROR_CODE_OK;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );

	TestResultInfo( _T("\r\n------------------------------Project Test------------------------------\r\n") );

	//MakeTraceRecord();暂时不需要屏蔽

	ISMChip5562* iChip5562 = (ISMChip5562*)SM_ChipBase(m_deviceNo);
	if( NULL == iChip5562 )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_CTP_RST );
	if( iReCode != ERROR_CODE_OK ) itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	SysDelay( 200 );

	iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_SWITCH_IIC );
	if( iReCode != ERROR_CODE_OK ) itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_IDENTITY );
	if( iReCode != ERROR_CODE_OK ) itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	unsigned char cfgBuffer[MAX_CFG_5562_BIN_SIZE] = {0};
	iReCode = SM_ChipBase(m_deviceNo)->ReadCoreSpace( 0x20000000 + 0x80, (unsigned char*)cfgBuffer, pCfg5562->cfgBinSize );
	if( iReCode != ERROR_CODE_OK ) itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	TCHAR chTemp[MAX_PATH] = {0};
	unsigned short s = cfgBuffer[1];
	unsigned short p = (cfgBuffer[3] << 8) + cfgBuffer[2];
	unsigned short v = (cfgBuffer[5] << 8) + cfgBuffer[4];
	//transformat( chTemp, _T("SoftWare Ver = %d, ProjectCode = %d, VenderID = %d\r\n"), s, p, v );
	//TestResultInfo( chTemp );
	TestResultInfoR( _T("SoftWare Ver = %d, ProjectCode = %d, VenderID = %d\r\n"), s, p, v );

	transformat( chTemp, _T("S=%d, P=%d, V=%d"), s, p, v );

	if( pCfg5562->sVersion == s && pCfg5562->pVersion == p && pCfg5562->vVersion == v )
	{
		if(pCfg5562->cfgTestBinSize)
		{
			iReCode = iChip5562->SetConfigInFctMode( (unsigned char*)pCfg5562->cfgTestBinBuffer, pCfg5562->cfgTestBinSize );
			if(iReCode != ERROR_CODE_OK)
			{
				TestResultInfo( _T("\r\nSet Config dynamic failed\r\n") );
				return itemNotify.UpdateItemResult( ITEM_STA_FAIL );
			}
			else
			{
				TestResultInfo( _T("\r\nSet Config dynamic succesed\r\n") );
			}
		}

		//frequecy lockdown
		iReCode = iChip5562->IncokeCommand(CMD_CTP_FREQ, 3, 1);
		itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

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
unsigned int CTest5562::Config_Test( NativeTestItem& itemQuote )
{
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );

	TestResultInfo( _T("\r\n------------------------------CONFIG Test------------------------------\r\n") );

	ISMChip5562* iChip5562 = (ISMChip5562*)SM_ChipBase(m_deviceNo);
	if( NULL == iChip5562 )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	unsigned short cfgVerFromTp = 0;
	unsigned char configBuffer[MAX_CFG_5562_BIN_SIZE] = {0};
	iReCode = iChip5562->GetFirmWareConfig( configBuffer, pCfg5562->cfgBinSize );
	if( ERROR_CODE_OK != iReCode )  return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	cfgVerFromTp = configBuffer[1];
	//TCHAR szConfigVer[MAX_PATH] = {0};
	//transformat( szConfigVer, _T("Ver=0x%x"), cfgVerFromTp );

	BOOL bSameConfig = CheckConfigSame( configBuffer, pCfg5562->cfgBinSize );

	//wasim
	//bSameConfig = FALSE;

	if( bSameConfig )
	{
		TestResultInfo( _T("\r\nConfig from tp is same with Config from setting\r\n") );
		//TestResultInfo( szConfigVer );
		auto szConfigVer = TestResultInfoR( _T("Ver=0x%x"), cfgVerFromTp );
		TestResultInfo( "\r\n\r\n//Config Test is Pass\r\n", ITEM_STA_PASS );
		itemNotify.UpdateItemResult( ITEM_STA_PASS, szConfigVer );
	}
	else
	{
		if( pCfg5562->config_only_check )
		{
			TestResultInfo( _T("\r\nConfig from tp is differant from setting\r\n") );
			//TestResultInfo( szConfigVer );
			auto szConfigVer = TestResultInfoR( _T("Ver=0x%x"), cfgVerFromTp );
			TestResultInfo( "\r\n\r\n//Config Test is Fail\r\n", ITEM_STA_FAIL );
			itemNotify.UpdateItemResult( ITEM_STA_FAIL, szConfigVer );
		}
		else
		{
			//SM_CommBase(m_deviceNo)->SetIoVoltage(0x6E, pCfg5562->vddVotage == pCfg5562->ioVddVotage ? 0x6E : pCfg5562->ioVddVotage);
			//SysDelay(50);

			TestResultInfo( _T("\r\nDownlad new config bin...\r\n") );
			iReCode = iChip5562->BurnConfigBin( pCfg5562->cfgBinBuffer, pCfg5562->cfgBinSize );
			if( iReCode == ERROR_CODE_OK )   
			{
				memset( configBuffer, 0, sizeof(configBuffer) );
				iChip5562->GetFirmWareConfig( configBuffer, pCfg5562->cfgBinSize );
				BOOL bSameConfig2 = CheckConfigSame( configBuffer, pCfg5562->cfgBinSize );

				cfgVerFromTp = configBuffer[1];
				//TCHAR szConfigVer[MAX_PATH] = {0};
				//transformat( szConfigVer, _T("NewVer=0x%x"), cfgVerFromTp );

				if( bSameConfig2 )
				{
					TestResultInfo( "\r\n\r\n//Config Test is Pass\r\n", ITEM_STA_PASS );
					//TestResultInfo( szConfigVer );
					auto szConfigVer = TestResultInfoR( _T("NewVer=0x%x"), cfgVerFromTp );
					itemNotify.UpdateItemResult( ITEM_STA_PASS, szConfigVer );
				}
				else
				{
					TestResultInfo( _T("\r\nConfig from tp is differant from setting\r\n") );
					//TestResultInfo( szConfigVer );
					auto szConfigVer = TestResultInfoR( _T("NewVer=0x%x"), cfgVerFromTp );
					TestResultInfo( "\r\n\r\n//Config Test is Fail\r\n", ITEM_STA_FAIL );
					itemNotify.UpdateItemResult( ITEM_STA_FAIL, szConfigVer );
				}
			}
			else
			{
				TestResultInfo( _T("\r\nDownload config exception\r\n") );
				//TestResultInfo( szConfigVer );
				auto szConfigVer = TestResultInfoR( _T("Ver=0x%x"), cfgVerFromTp );
				TestResultInfo( "\r\n\r\n//Config Test is Fail\r\n", ITEM_STA_FAIL );
				itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
			}

			//SM_CommBase(m_deviceNo)->SetIoVoltage(pCfg5562->vddVotage, pCfg5562->ioVddVotage);
			//SysDelay(50);
		}
	}

	return itemNotify;
}

typedef struct __osc_trim_t{
    unsigned int sig;      // 0x467265xx, xx=0, 96M
    unsigned int d[5][2];  // trim&freq, trim&freq, trim&freq, trim&freq, trim&freq
	unsigned int chk;      // acc = 0
}osc_trim_t;

unsigned int CTest5562::OSCTrim_Test( NativeTestItem& itemQuote )
{
	int failerCnt = 0;
	unsigned int iReCode = ERROR_CODE_OK;
	osc_trim_t testTrim;
	ISMChip5562* iChip5562 = (ISMChip5562*)SM_ChipBase(m_deviceNo);
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );

	TestResultInfo( _T("\r\n------------------------------OSC Trim Test------------------------------\r\n") );

	//unsigned short osTrim1 = 0, osTrim2 = 0, oscTrimNew = 0;
	unsigned int osTrim32k = 0, osTrim96m = 0, osTrim250m = 0,osTrimother = 0;
	unsigned char readBuffer[1024] = {0}, markBuffer[4] = {0};
	//char szBuffer[MAX_PATH] = {0};
	unsigned int crc;

	testTrim.sig = 0x46726530;

	iReCode = SM_ChipBase(m_deviceNo)->ReadBurnSpace( FCT_ROM_VNM_REGION, readBuffer, sizeof(readBuffer) );
	if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	iReCode = SM_ChipBase(m_deviceNo)->ReadCoreSpace( 0x40008034, markBuffer, sizeof(markBuffer) );
	if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	osTrim32k  = (unsigned int)readBuffer[0];
	osTrim96m  = (unsigned int)readBuffer[2];
	osTrim96m  = (osTrim96m<<8) + (unsigned int)readBuffer[1];
	osTrim250m  = (unsigned int)readBuffer[03];
	m_stOneRecord.ReleaseID = *(UINT64*)&readBuffer[8];

	crc = caculate_check_sum_u32((unsigned int*)&readBuffer[32], sizeof(osc_trim_t));

	if( 0xff != (readBuffer[1] + readBuffer[5]) 
		|| 0xff != (readBuffer[2] + readBuffer[6])
		|| 0xff != (readBuffer[3] + readBuffer[7])
		|| osTrim250m < pCfg5562->trim_250m_min 
		|| osTrim250m > pCfg5562->trim_250m_max
		|| osTrim96m < pCfg5562->trim_96m_min
		|| osTrim96m > pCfg5562->trim_96m_max 
		|| osTrim32k < pCfg5562->trim_32k_min
		|| osTrim32k > pCfg5562->trim_32k_max
		|| (0 != crc))
	{
		if (pCfg5562->trim_only_check)
		{
			failerCnt++;
			TestResultInfo( _T("\r\nOSCtrim only check error\r\n") );
			TestResultInfoR( _T("32K = 0x%02x, 96M=0x%02x, 250M=0x%02x, mark=0x%08x, crc=0x%08x"), osTrim32k, osTrim96m, osTrim250m, *(unsigned int*)markBuffer, crc);

			TestResultInfo( "\r\n\r\n//OSCTrim Test is Fail\r\n", ITEM_STA_FAIL );
			itemNotify.UpdateItemResult( ITEM_STA_FAIL );
			return itemNotify;
		}
		else
		{
			TestResultInfo( _T("Start Trim And Refresh Trim Value\r\n") );
			SysDelay( 10 );

			iReCode = iChip5562->GetOSCTrim( (unsigned char*)&osTrim32k, (unsigned char*)&osTrim96m,(unsigned char*) &osTrim250m, pCfg5562->trim_speed_mode, pCfg5562->tick_32k_standard, pCfg5562->tick_96m_standard, pCfg5562->tick_250m_standard );
			if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
			testTrim.d[2][0] = osTrim96m;
			testTrim.d[2][1] = pCfg5562->tick_96m_standard*1000;

			if( osTrim32k < pCfg5562->trim_32k_min )
				failerCnt++;
			else if( osTrim32k > pCfg5562->trim_32k_max )
				failerCnt++;
			else if( osTrim96m < pCfg5562->trim_96m_min )
				failerCnt++;
			else if( osTrim96m > pCfg5562->trim_96m_max )
				failerCnt++;
			else if( osTrim250m < pCfg5562->trim_250m_min )
				failerCnt++;
			else if( osTrim250m > pCfg5562->trim_250m_max )
				failerCnt++;

			if(failerCnt == 0){
				iReCode = iChip5562->GetOSCTrim( (unsigned char*)&osTrimother, (unsigned char*)&osTrim96m,(unsigned char*) &osTrimother, pCfg5562->trim_speed_mode, pCfg5562->tick_32k_standard, pCfg5562->tick_96m_standardNo2, 0);//88000
				if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
				testTrim.d[0][0] = osTrim96m;
				testTrim.d[0][1] = pCfg5562->tick_96m_standardNo2 * 1000;
				TestResultInfoR( _T("88M=0x%02x\r\n"),osTrim96m);

				iReCode = iChip5562->GetOSCTrim( (unsigned char*)&osTrimother, (unsigned char*)&osTrim96m,(unsigned char*) &osTrimother, pCfg5562->trim_speed_mode, pCfg5562->tick_32k_standard, pCfg5562->tick_96m_standardNo3, 0);//92000
				if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
				testTrim.d[1][0] = osTrim96m;
				testTrim.d[1][1] = pCfg5562->tick_96m_standardNo3 * 1000;
				TestResultInfoR( _T("92M=0x%02x\r\n"),osTrim96m);

				iReCode = iChip5562->GetOSCTrim( (unsigned char*)&osTrimother, (unsigned char*)&osTrim96m,(unsigned char*) &osTrimother, pCfg5562->trim_speed_mode, pCfg5562->tick_32k_standard, pCfg5562->tick_96m_standardNo4, 0);//100000
				if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
				testTrim.d[3][0] = osTrim96m;
				testTrim.d[3][1] = pCfg5562->tick_96m_standardNo4 * 1000;
				TestResultInfoR( _T("100M=0x%02x\r\n"),osTrim96m);

				iReCode = iChip5562->GetOSCTrim( (unsigned char*)&osTrimother, (unsigned char*)&osTrim96m,(unsigned char*) &osTrimother, pCfg5562->trim_speed_mode, pCfg5562->tick_32k_standard, pCfg5562->tick_96m_standardNo5, 0);//104000
				if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
				testTrim.d[4][0] = osTrim96m;
				testTrim.d[4][1] = pCfg5562->tick_96m_standardNo5 * 1000;
				TestResultInfoR( _T("104M=0x%02x\r\n"),osTrim96m);

				testTrim.chk  = testTrim.sig;
				testTrim.chk += testTrim.d[0][0];
				testTrim.chk += testTrim.d[0][1];
				testTrim.chk += testTrim.d[1][0];
				testTrim.chk += testTrim.d[1][1];
				testTrim.chk += testTrim.d[2][0];
				testTrim.chk += testTrim.d[2][1];
				testTrim.chk += testTrim.d[3][0];
				testTrim.chk += testTrim.d[3][1];
				testTrim.chk += testTrim.d[4][0];
				testTrim.chk += testTrim.d[4][1];
				testTrim.chk  = 0-testTrim.chk;

				osTrim96m = testTrim.d[2][0];

				readBuffer[0] = osTrim32k;
				readBuffer[1] = osTrim96m;
				readBuffer[2] = osTrim96m>>8;
				readBuffer[3] = osTrim250m;

				readBuffer[4] = ~readBuffer[0];
				readBuffer[5] = ~readBuffer[1];
				readBuffer[6] = ~readBuffer[2];
				readBuffer[7] = ~readBuffer[3];

				//Gen ICID
				unsigned int* pIntData = (unsigned int*)&readBuffer[8];
				unsigned short* pShortData = (unsigned short*)&readBuffer[8];
				if(0xffff != (pShortData[2] + pShortData[3]))
				{
					SYSTEMTIME SysTime;
					::GetLocalTime(&SysTime);
					pIntData[0] = (SysTime.wMonth << 22) + (SysTime.wDay << 17) + (SysTime.wHour << 12) + (SysTime.wMinute << 6) + SysTime.wSecond;

					std::srand((pIntData[0]+SysTime.wMilliseconds));
					::GetLocalTime(&SysTime);
					pShortData[2] = (((rand()&0xffff) + ((SysTime.wMilliseconds % 1000)<<3))&0xfff8) + m_deviceNo;
					pShortData[3] = ~pShortData[2];
				}
				//iReCode = SM_ChipBase(m_deviceNo)->WriteBurnSpace( 100 * 1024, readBuffer, sizeof(readBuffer), OTP_W_CHK | TLK_DATACHK_EX1 );
			}

			//vid_pid
			UINT64* p_vid_pid = (UINT64*)&readBuffer[16];
			*p_vid_pid = pCfg5562->vid_pid;

			memcpy(&readBuffer[32], &testTrim, sizeof(testTrim));
			iReCode = SM_ChipBase(m_deviceNo)->WriteBurnSpace( FCT_ROM_VNM_REGION, readBuffer, sizeof(readBuffer), OTP_W_CHK | TLK_DATACHK_EX1 );
			if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

		}
			
	}
	fct_osc_trim fo_trim;

	int offset32k = (pCfg5562->offset_32k) * pCfg5562->tick_32k_standard;
	int offset96m = (pCfg5562->offset_96m) * pCfg5562->tick_96m_standard;
	int offset88m = (pCfg5562->offset_96m) * pCfg5562->tick_96m_standardNo2;
	int offset92m = (pCfg5562->offset_96m) * pCfg5562->tick_96m_standardNo3;
	int offset100m = (pCfg5562->offset_96m) * pCfg5562->tick_96m_standardNo4;
	int offset104m = (pCfg5562->offset_96m) * pCfg5562->tick_96m_standardNo5;

	int offset250m = (pCfg5562->offset_250m) * pCfg5562->tick_250m_standard;

	iReCode = iChip5562->GetTrimeDosc(fo_trim);
	if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	int err32k = fo_trim.osc32k_freq - pCfg5562->tick_32k_standard*1000;
	int err88m = fo_trim.osc96m_meter[0] - pCfg5562->tick_96m_standardNo2*1000;
	int err92m = fo_trim.osc96m_meter[1] - pCfg5562->tick_96m_standardNo3*1000;
	int err96m = fo_trim.osc96m_meter[2] - pCfg5562->tick_96m_standard*1000;
	int err100m = fo_trim.osc96m_meter[3] - pCfg5562->tick_96m_standardNo4*1000;
	int err104m = fo_trim.osc96m_meter[4] - pCfg5562->tick_96m_standardNo5*1000;

	int err250m = fo_trim.osc250m_freq - pCfg5562->tick_250m_standard*1000;

	TestResultInfoR( _T("osc32k = %d, osc88m = %d, osc92m = %d, osc96m = %d, osc100m = %d, osc104m = %d, osc250m = %d\r\n"),
		fo_trim.osc32k_freq,fo_trim.osc96m_meter[0],fo_trim.osc96m_meter[1],fo_trim.osc96m_meter[2],fo_trim.osc96m_meter[3],fo_trim.osc96m_meter[4],fo_trim.osc250m_freq);
	if(abs(err32k) > offset32k )
	{
		failerCnt++;
		TestResultInfoR( _T("error 32k:Actual offset(%d), offset(%d), proportion(‰)(%d)\r\n"),abs(err32k),offset32k, pCfg5562->offset_32k);
	}
	if((abs(err88m) > offset88m) ||(abs(err92m) > offset92m) || (abs(err96m) > offset96m) || (abs(err100m) > offset100m) || (abs(err104m) > offset104m))
	{
		failerCnt++;
		TestResultInfoR( _T("error 96m:Actual offset(%d, %d, %d, %d, %d), offset(%d, %d, %d, %d, %d), proportion(‰)(%d)\r\n")
			,abs(err88m),abs(err92m),abs(err96m),abs(err100m),abs(err104m),offset88m,offset92m,offset96m,offset100m,offset104m, pCfg5562->offset_96m);
	}
	if(abs(err250m) > offset250m )
	{
		failerCnt++;
		TestResultInfoR( _T("error 250m:Actual offset(%d), offset(%d), proportion(‰)(%d)\r\n"),abs(err250m),offset250m, pCfg5562->offset_250m);
	}

	m_stOneRecord.ReleaseID = *(UINT64*)&readBuffer[8];
	UINT32 otm_time = *(UINT32*)&m_stOneRecord.ReleaseID;
	//transformat( szBuffer, _T("ICID = 0x%llx,   %d-%d, %d:%d:%d\r\n"), m_stOneRecord.ReleaseID, (otm_time>>22)&0xf, (otm_time>>17)&0x1f,(otm_time>>12)&0x1f, (otm_time>>6)&0x3f, otm_time&0x3f );
	//TestResultInfo( szBuffer );
	TestResultInfoR( _T("ICID = 0x%llx,   %d-%d, %d:%d:%d\r\n"), m_stOneRecord.ReleaseID, (otm_time>>22)&0xf, (otm_time>>17)&0x1f,(otm_time>>12)&0x1f, (otm_time>>6)&0x3f, otm_time&0x3f );

	m_stOneRecord.Mcap.oscTrim = *((unsigned int*)readBuffer);
	//transformat( szBuffer, _T("32K = h%02x, 96M=h%02x, 250M=h%02x, mark=0x%08x"), osTrim32k, osTrim96m, osTrim250m, *(unsigned int*)markBuffer );
	//TestResultInfo( szBuffer );
	auto szBuffer = TestResultInfoR( _T("32K = 0x%02x, 96M=0x%02x, 250M=0x%02x, mark=0x%08x"), osTrim32k, osTrim96m, osTrim250m, *(unsigned int*)markBuffer );

	if( failerCnt )
	{
		TestResultInfo( "\r\n\r\n//OSCTrim Test is Fail\r\n", ITEM_STA_FAIL );
		itemNotify.UpdateItemResult( ITEM_STA_FAIL, szBuffer );
	}
	else
	{
		TestResultInfo( "\r\n\r\n//OSCTrim Test is Pass\r\n", ITEM_STA_PASS );
		itemNotify.UpdateItemResult( ITEM_STA_PASS, szBuffer );
	}

	return itemNotify;
}
unsigned int CTest5562::Current_Test( NativeTestItem& itemQuote )
{
	TEST_ITEM_STATUS itemStatus = ITEM_STA_NONE;
	for( int index = 0; index < 3; index++ )
	{
		itemStatus = (TEST_ITEM_STATUS)Current_TestEx( itemQuote );
		if( itemStatus == ITEM_STA_PASS ) break;
	}
	return itemStatus;
}
unsigned int CTest5562::Current_TestEx( NativeTestItem& itemQuote )
{
	int failedCount = 0;
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );

	TestResultInfo( _T("\r\n------------------------------Current Test------------------------------\r\n") );

	ISMChip5562* iChip5562 = (ISMChip5562*)SM_ChipBase(m_deviceNo);
	if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	short deepCurrent = 0, sleepCurrent = 0, activeCurrent = 0, idleCurrent = 0;
	short vbus_deepCurrent = 0, vbus_sleepCurrent = 0, vbus_activeCurrent = 0;
	short level[2][3] = {
		pCfg5562->active_current_min, pCfg5562->sleep_current_min, pCfg5562->deep_current_min,
		pCfg5562->active_current_max, pCfg5562->sleep_current_max, pCfg5562->deep_current_max,
	};
	//iReCode = iChip5562->GetCurrent( level, (unsigned short*)&activeCurrent, (unsigned short*)&sleepCurrent, (unsigned short*)&deepCurrent, (unsigned short*)&idleCurrent );
	iReCode = iChip5562->GetCurrent55xx( level, (unsigned short*)&activeCurrent, (unsigned short*)&sleepCurrent, (unsigned short*)&deepCurrent,(unsigned short*)&vbus_activeCurrent, (unsigned short*)&vbus_sleepCurrent, (unsigned short*)&vbus_deepCurrent);
	if( ERROR_CODE_OK != iReCode )  return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	//iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_CTP_RST );
	//SysDelay( 50 );

	//TCHAR szTmep[MAX_PATH] = {0};

	{
		m_stOneRecord.current_mode1 = activeCurrent;
		m_stOneRecord.current_mode2 = sleepCurrent;
		m_stOneRecord.current_mode3 = deepCurrent;
		//transformat( szTmep, _T("\r\nactive = %d(mA), sleep = %d(uA), deep = %d(uA)\r\n"), activeCurrent, sleepCurrent, deepCurrent );
		//TestResultInfo( szTmep );
		TestResultInfoR( _T("\r\navdd_active = %d(mA), avdd_sleep = %d(uA), avdd_deep = %d(uA)\r\n"), activeCurrent, sleepCurrent, deepCurrent);
		TestResultInfoR( _T("\r\nvbus_active = %d(mA), vbus_sleep = %d(uA), vbus_deep = %d(uA)\r\n"), vbus_activeCurrent, vbus_sleepCurrent, vbus_deepCurrent);
	}
	if( activeCurrent < pCfg5562->active_current_min )
	{
		failedCount++;
		//transformat( szTmep, _T( "\r\nactive(%d) < setting min(%d)\r\n"), activeCurrent, pCfg5562->active_current_min );
		//TestResultInfo( szTmep );
		TestResultInfoR( _T( "\r\nactive(%d) < setting min(%d)\r\n"), activeCurrent, pCfg5562->active_current_min );
	}
	if( activeCurrent > pCfg5562->active_current_max )
	{
		failedCount++;
		//transformat( szTmep, _T( "\r\nactive(%d) > setting max(%d)\r\n"), activeCurrent, pCfg5562->active_current_max );
		//TestResultInfo( szTmep );
		TestResultInfoR( _T( "\r\nactive(%d) > setting max(%d)\r\n"), activeCurrent, pCfg5562->active_current_max );
	}
	if( sleepCurrent < pCfg5562->sleep_current_min )
	{
		failedCount++;
		//transformat( szTmep, _T( "\r\nsleep(%d) < setting min(%d)\r\n"), sleepCurrent, pCfg5562->sleep_current_min );
		//TestResultInfo( szTmep );
		TestResultInfoR( _T( "\r\nsleep(%d) < setting min(%d)\r\n"), sleepCurrent, pCfg5562->sleep_current_min );
	}
	if( sleepCurrent > pCfg5562->sleep_current_max )
	{
		failedCount++;
		//transformat( szTmep, _T( "\r\nsleep(%d) > setting max(%d)\r\n"), sleepCurrent, pCfg5562->sleep_current_max );
		//TestResultInfo( szTmep );
		TestResultInfoR( _T( "\r\nsleep(%d) > setting max(%d)\r\n"), sleepCurrent, pCfg5562->sleep_current_max );
	}
	if( deepCurrent < pCfg5562->deep_current_min )
	{
		failedCount++;
		//transformat( szTmep, _T( "\r\ndeep(%d) < setting min(%d)\r\n"), deepCurrent, pCfg5562->deep_current_min );
		//TestResultInfo( szTmep );
		TestResultInfoR( _T( "\r\ndeep(%d) < setting min(%d)\r\n"), deepCurrent, pCfg5562->deep_current_min );
	}
	if( deepCurrent > pCfg5562->deep_current_max )
	{
		failedCount++;
		//transformat( szTmep, _T( "\r\ndeep(%d) > setting max(%d)\r\n"), deepCurrent, pCfg5562->deep_current_max );
		//TestResultInfo( szTmep );
		TestResultInfoR( _T( "\r\ndeep(%d) > setting max(%d)\r\n"), deepCurrent, pCfg5562->deep_current_max );
	}

	if( vbus_activeCurrent < pCfg5562->vbus_active_current_min )
	{
		failedCount++;
		TestResultInfoR( _T( "\r\nvbus_active(%d) < setting min(%d)\r\n"), vbus_activeCurrent, pCfg5562->vbus_active_current_min );
	}
	if( vbus_activeCurrent > pCfg5562->vbus_active_current_max )
	{
		failedCount++;
		TestResultInfoR( _T( "\r\nvbus_active(%d) > setting max(%d)\r\n"), vbus_activeCurrent, pCfg5562->vbus_active_current_max );
	}

	if( vbus_sleepCurrent < pCfg5562->vbus_sleep_current_min )
	{
		failedCount++;
		TestResultInfoR( _T( "\r\nvbus_sleep(%d) < setting min(%d)\r\n"), vbus_sleepCurrent, pCfg5562->vbus_sleep_current_min );
	}
	if( vbus_sleepCurrent > pCfg5562->vbus_sleep_current_max )
	{
		failedCount++;
		TestResultInfoR( _T( "\r\nvbus_sleep(%d) > setting max(%d)\r\n"), vbus_sleepCurrent, pCfg5562->vbus_sleep_current_max );
	}

	if( vbus_deepCurrent < pCfg5562->vbus_deep_current_min )
	{
		failedCount++;
		TestResultInfoR( _T( "\r\nvbus_deep(%d) < setting min(%d)\r\n"), vbus_deepCurrent, pCfg5562->vbus_deep_current_min );
	}
	if( vbus_deepCurrent > pCfg5562->vbus_deep_current_max )
	{
		failedCount++;
		TestResultInfoR( _T( "\r\nvbus_deep(%d) > setting max(%d)\r\n"), vbus_deepCurrent, pCfg5562->vbus_deep_current_max );
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
unsigned int CTest5562::ScapRawData_Test( NativeTestItem& itemQuote )
{
    bool isCsv = false;
	int failerCount = 0;
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );
	signed short baseTempBuffer[MAX_MCAP_CHANNEL * 2] = {0};
	/*unsigned*/ short dataMatrix[MAX_MCAP_ROW][MAX_MCAP_COL];
	const unsigned int iRawDataLen = ((pCfg5562->rowsCnt + 1) * (pCfg5562->colsCnt + 1) * 2 + 3) & 0xfffffffc;
	const unsigned int iScapRawDataLen = pCfg5562->rowsCnt + pCfg5562->colsCnt;

	TestResultInfo( _T("\r\n------------------------------ScapData Test------------------------------\r\n") );

	if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	ISMChip5562* iChip5562 = (ISMChip5562*)SM_ChipBase(m_deviceNo);

    if(OP_LIKE_YY == G_XMLConfig->selected_format || OP_LIKE_XY == G_XMLConfig->selected_format)
    {
        isCsv = true;
    }

	int addRow = ( pCfg5562->real_channel_num - pCfg5562->va_channel_num ) ? 1 : 0;

	//iReCode = iChip5562->IncokeCommand( 0x05,0x02,0x5c);//取消补偿命令
	SysDelay( 100 );

	iReCode = iChip5562->SwitchMode( MODE_RAWDATA, iRawDataLen   );
	if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	SysDelay( 20 );

	for( int index = 0; index < 2; index++ )
	{
		iReCode = iChip5562->GetRawData( baseTempBuffer, iRawDataLen  );
		//if( iReCode == ERROR_CODE_OK ) break;
		if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	}

	int ref_channel_num = min(pCfg5562->real_channel_num - pCfg5562->va_channel_num, pCfg5562->colsCnt);
	AnalyzeInfo info( pCfg5562->rowsCnt, pCfg5562->colsCnt );
	unsigned short maxCols[] = { pCfg5562->colsCnt, pCfg5562->rowsCnt };
	ReShappingData</*unsigned*/ short>( dataMatrix, (/*unsigned*/ short*)baseTempBuffer + pCfg5562->rowsCnt * pCfg5562->colsCnt, iScapRawDataLen, 2, maxCols );
	//short baseMin[MAX_MCAP_ROW][MAX_MCAP_COL] = {0}, baseMax[MAX_MCAP_ROW][MAX_MCAP_COL] = {0};
	//FillArrayUseValue( baseMin, pCfg5562->base_min );
	//FillArrayUseValue( baseMax, pCfg5562->base_max );

	NodeVal nodeOutRange;
	ColorText textTemp( _T("\r\nScap Data:\r\n") );

	bool bResult = AnalyzeTestResultMSCapJudge( dataMatrix, pCfg5562->scap_rawdata_min, pCfg5562->scap_rawdata_max, pCfg5562->invalid_node, info, textTemp, nodeOutRange, isCsv, true );
	TestResultInfo( textTemp );
	if( !bResult )
	{
		failerCount++;
		LPCTSTR strHead = _T("\r\n//========= Out of Threshold in ScapDataTest: \r\n");
		PrintNodeValue( m_ColorText, &nodeOutRange, strHead );
	}

	if( failerCount )
	{
		itemNotify.UpdateItemResult( ITEM_STA_FAIL );
		TestResultInfo( "\r\n\r\n//ScapData Test is Fail\r\n", ITEM_STA_FAIL );
	}
	else
	{
		itemNotify.UpdateItemResult( ITEM_STA_PASS );
		TestResultInfo( "\r\n\r\n//ScapData Test is Pass\r\n", ITEM_STA_PASS );
	}

	return itemNotify;
}
unsigned int CTest5562::VT_Test( NativeTestItem& itemQuote )
{
	int failerCount = 0;
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );
	//unsigned short baseTempBuffer[MAX_MCAP_CHANNEL * 2] = {0};
	//unsigned short dataMatrixOn[1][MAX_MCAP_ROW];
	//unsigned short dataMatrixOff[1][MAX_MCAP_ROW];
	//short diffMatrix[1][MAX_MCAP_ROW];

	//short basediffMatrix[1][MAX_MCAP_ROW];

	//const unsigned int iRawDataLen = ((pCfg5562->rowsCnt + 1) * (pCfg5562->colsCnt + 1) * 2 + 3) & 0xfffffffc;
	//const unsigned int iScapRawDataLen = pCfg5562->rowsCnt + pCfg5562->colsCnt;
	//AnalyzeInfo info( pCfg5562->rowsCnt, pCfg5562->colsCnt );
	//unsigned short maxCols[] = { pCfg5562->colsCnt, pCfg5562->rowsCnt };

	//TestResultInfo( _T("\r\n------------------------------VT Test------------------------------\r\n") );

	//if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	//ISMChip5562* iChip5562 = (ISMChip5562*)SM_ChipBase(m_deviceNo);

	//int addRow = ( pCfg5562->real_channel_num - pCfg5562->va_channel_num ) ? 1 : 0;

	//iReCode = iChip5562->GetVtData( baseTempBuffer, 42*2 * 2 );
	//if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	//ICArrayToSensorMatrixVT( dataMatrixOn, dataMatrixOff,baseTempBuffer);
	//ColorText textTempa( _T("\r\nvt_on:\r\n") );
	//PrintMaxtrixValueScapRX<unsigned short,1,MAX_MCAP_ROW>(textTempa,dataMatrixOn,info,true);
	//TestResultInfo( textTempa );
	//textTempa = ( _T("\r\nvt_off:\r\n") );
	//PrintMaxtrixValueScapRX<unsigned short,1,MAX_MCAP_ROW>(textTempa,dataMatrixOff,info,true);
	//TestResultInfo( textTempa );
	//
	//MatrixSubtraction<short, unsigned short, 1, MAX_MCAP_COL>(diffMatrix,dataMatrixOff,dataMatrixOn,1,pCfg5562->rowsCnt);

	//textTempa = ( _T("\r\nvt_diff:\r\n") );
	//PrintMaxtrixValueScapRX< short,1,MAX_MCAP_ROW>(textTempa,diffMatrix,info,true);
	//TestResultInfo( textTempa );

	//textTempa = ( _T("\r\nvt_base_diff:\r\n") );
	//MatrixSubtraction<short, unsigned short, 1, MAX_MCAP_COL>(basediffMatrix,pCfg5562->vt_off,pCfg5562->vt_on,1,pCfg5562->rowsCnt);
	//PrintMaxtrixValueScapRX< short,1,MAX_MCAP_ROW>(textTempa,basediffMatrix,info,true);
	//TestResultInfo( textTempa );

	//MatrixSubtraction<short,  short, 1, MAX_MCAP_ROW>(diffMatrix,diffMatrix,basediffMatrix,1,pCfg5562->rowsCnt,true);

	////textTempa = ( _T("\r\nfinal_diff:\r\n") );
	////PrintMaxtrixValueScapRX< short,1,MAX_MCAP_ROW>(textTempa,diffMatrix,info,true);
	////TestResultInfo( textTempa );

	//NodeVal nodeOutRange;
	//unsigned short min[1][MAX_MCAP_COL] = {0};
	//ColorText textTemp( _T("\r\nvt_final_diff:\r\n") );
	//FillMatrixUseValue( min, (unsigned short)0 );
	//bool bResult = AnalyzeTestResultVTSCapRX<short,unsigned short,unsigned short,1,MAX_MCAP_ROW>( diffMatrix, min, pCfg5562->vt_diff_max, info, textTemp, nodeOutRange, true );
	//TestResultInfo( textTemp );
	//if( !bResult )
	//{
	//	failerCount++;
	//	LPCTSTR strHead = _T("\r\n//========= Out of Threshold in VtTest: \r\n");
	//	PrintNodeValue( m_ColorText, &nodeOutRange, strHead );
	//}
	//if( failerCount )
	//{
	//	itemNotify.UpdateItemResult( ITEM_STA_FAIL );
	//	TestResultInfo( "\r\n\r\n//VT Test is Fail\r\n", ITEM_STA_FAIL );
	//}
	//else
	//{
	//	itemNotify.UpdateItemResult( ITEM_STA_PASS );
	//	TestResultInfo( "\r\n\r\n//VT Test is Pass\r\n", ITEM_STA_PASS );
	//}
	itemNotify.UpdateItemResult( ITEM_STA_PASS );
	return itemNotify;
}
unsigned int CTest5562::STC_Test( NativeTestItem& itemQuote )
{
    bool isCsv = false;
	int failerCount = 0;
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );
	signed short baseTempBuffer[MAX_MCAP_CHANNEL * 2] = {0};
	signed int baseSum[MAX_MCAP_CHANNEL * 2] = {0};
	/*unsigned*/ short baseMatrix[MAX_MCAP_ROW][MAX_MCAP_COL], uniformityMin[MAX_MCAP_ROW][MAX_MCAP_COL];
	const unsigned int iRawDataLen = ((pCfg5562->rowsCnt) * (pCfg5562->colsCnt) * 2 + 3) & 0xfffffffc;
	const unsigned int iRetry = 20;

	TestResultInfo( _T("\r\n------------------------------STC Test------------------------------\r\n") );

	if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	ISMChip5562* iChip5562 = (ISMChip5562*)SM_ChipBase(m_deviceNo);

    if(OP_LIKE_YY == G_XMLConfig->selected_format || OP_LIKE_XY == G_XMLConfig->selected_format)
    {
        isCsv = true;
    }

	int addRow = ( pCfg5562->real_channel_num - pCfg5562->va_channel_num ) ? 1 : 0;
	memset( uniformityMin, 0, sizeof(uniformityMin) );

	//iReCode = iChip5562->IncokeCommand( CMD_CTP_RST );
	//SysDelay( 100 );

	//iReCode = iChip5562->SetClkInFctMode( pCfg5562->stc_clk_div, false );
	//if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	//SysDelay( 20 );

	iReCode = iChip5562->SwitchMode( MODE_RAWDATA, iRawDataLen );
	if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	SysDelay( 20 );

	memset( baseSum, 0, sizeof(baseSum) );
	for( int index = 0; index < iRetry; index++ )
	{
		iReCode = iChip5562->GetRawData( baseTempBuffer, iRawDataLen );
		if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

		if(0 == index) continue;
		ArrayAddtion( baseSum, baseTempBuffer, iRawDataLen );
	}
	ArrayAverage( baseTempBuffer, baseSum, iRawDataLen, iRetry - 1);

	int ref_channel_num = min(pCfg5562->real_channel_num - pCfg5562->va_channel_num, pCfg5562->colsCnt);
	AnalyzeInfo info( pCfg5562->rowsCnt, pCfg5562->colsCnt, ref_channel_num, false );
	ReShappingData</*unsigned*/ short>( baseMatrix, (/*unsigned*/ short*)baseTempBuffer, G_XMLConfig->real_channel_num * 2, pCfg5562->rowsCnt, pCfg5562->colsCnt );
	//short baseMin[MAX_MCAP_ROW][MAX_MCAP_COL] = {0}, baseMax[MAX_MCAP_ROW][MAX_MCAP_COL] = {0};
	//FillArrayUseValue( baseMin, pCfg5562->base_min );
	//FillArrayUseValue( baseMax, pCfg5562->base_max );

	{
		NodeVal nodeOutRange;
		ColorText textTemp( _T("\r\nstc_rawdata:\r\n") );
		short baseMin[MAX_MCAP_ROW][MAX_MCAP_COL] = {0}, baseMax[MAX_MCAP_ROW][MAX_MCAP_COL] = {0};
		FillMatrixUseValue<short>( baseMax, 30000 );
		bool bResult = AnalyzeTestResultJudge( baseMatrix, baseMin, baseMax, pCfg5562->invalid_node, info, textTemp, nodeOutRange, isCsv, true);
		TestResultInfo( textTemp );
	}

	{
		NodeVal nodeOutRange;
		ColorText textTemp( _T("\r\nstc_deviation:\r\n") );
		for( int iRow = 0; iRow < pCfg5562->rowsCnt; iRow++ )
		{
			for( int iCol = 0; iCol < pCfg5562->colsCnt; iCol++ )
			{
				int deviation = 10 * abs( baseMatrix[iRow][iCol] - pCfg5562->stc_mean[iRow][iCol] );
				baseMatrix[iRow][iCol] = (short)(100 * deviation / (deviation + 3 * pCfg5562->stc_mse[iRow][iCol] + 0.001));
			}
		}
			
				
		short stcMin[MAX_MCAP_ROW][MAX_MCAP_COL] = {0}, stcMax[MAX_MCAP_ROW][MAX_MCAP_COL] = {0};
		FillMatrixUseValue( stcMin, pCfg5562->stc_min );
		FillMatrixUseValue( stcMax, pCfg5562->stc_max );
		bool bResult = AnalyzeTestResultJudge( baseMatrix, stcMin, stcMax, pCfg5562->invalid_node, info, textTemp, nodeOutRange, isCsv, true );
		TestResultInfo( textTemp );
		if( !bResult )
		{
			failerCount++;
			LPCTSTR strHead = _T("\r\n//========= Out of Threshold in STC Test: \r\n");
			PrintNodeValue( m_ColorText, &nodeOutRange, strHead );
		}
	}

// 	{
// 		NodeVal nodeOutRange;
// 		ColorText textTemp( _T("\r\nstc_convolution_h:\r\n") );
// 		short uniformityHorMatrix[MAX_MCAP_ROW][MAX_MCAP_COL];
// 		unsigned char uniformityHorInvalid[MAX_MCAP_ROW][MAX_MCAP_COL];
// 		CopyAndInvalid( uniformityHorInvalid, pCfg5562->invalid_node, 0, MAX_MCAP_COL );
// 		GenHorizontalConvolution( baseMatrix, uniformityHorMatrix, pCfg5562->rowsCnt, pCfg5562->colsCnt );
// 		bool bResult = AnalyzeTestResult( uniformityHorMatrix, uniformityMin, pCfg5562->stc_uniformity_h, uniformityHorInvalid, info, textTemp, nodeOutRange, true );
// 		TestResultInfo( textTemp );
// 		if( !bResult )
// 		{
// 			failerCount++;
// 			LPCTSTR strHead = _T("\r\n//========= Out of Threshold in STC Uniformity-H: \r\n");
// 			PrintNodeValue( m_ColorText, &nodeOutRange, strHead );
// 		}
// 	}
// 	
// 	{
// 		NodeVal nodeOutRange;
// 		ColorText textTemp( _T("\r\nstc_convolution_v:\r\n") );
// 		short uniformityVerMatrix[MAX_MCAP_ROW][MAX_MCAP_COL];
// 		unsigned char uniformityVerInvalid[MAX_MCAP_ROW][MAX_MCAP_COL];
// 		CopyAndInvalid( uniformityVerInvalid, pCfg5562->invalid_node, MAX_MCAP_ROW, 0 );
// 		GenVerticalConvolution( baseMatrix, uniformityVerMatrix, pCfg5562->rowsCnt, pCfg5562->colsCnt );
// 		bool bResult = AnalyzeTestResult( uniformityVerMatrix, uniformityMin, pCfg5562->stc_uniformity_v, uniformityVerInvalid, info, textTemp, nodeOutRange, true );
// 		TestResultInfo( textTemp );
// 		if( !bResult )
// 		{
// 			failerCount++;
// 			LPCTSTR strHead = _T("\r\n//========= Out of Threshold in STC Uniformity-V: \r\n");
// 			PrintNodeValue( m_ColorText, &nodeOutRange, strHead );
// 		}
// 	}

	if( failerCount )
	{
		itemNotify.UpdateItemResult( ITEM_STA_FAIL );
		TestResultInfo( "\r\n\r\n//STC Test is Fail\r\n", ITEM_STA_FAIL );
	}
	else
	{
		itemNotify.UpdateItemResult( ITEM_STA_PASS );
		TestResultInfo( "\r\n\r\n//STC Test is Pass\r\n", ITEM_STA_PASS );
	}

	return itemNotify;
}
unsigned int CTest5562::MCapRawData_Test( NativeTestItem& itemQuote )
{
    bool isCsv = false;
	int failerCount = 0;
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );
	signed short baseTempBuffer[MAX_MCAP_CHANNEL * 2] = {0};
	signed int baseSum[MAX_MCAP_CHANNEL * 2] = {0};
	/*unsigned*/ short baseMatrix[MAX_MCAP_ROW][MAX_MCAP_COL], uniformityMin[MAX_MCAP_ROW][MAX_MCAP_COL];
	short NormalizationMatrix[MAX_MCAP_ROW][MAX_MCAP_COL];
	const unsigned int iRawDataLen = ((pCfg5562->rowsCnt) * (pCfg5562->colsCnt) * 2 + 3) & 0xfffffffc;
	const unsigned int iRetry = 20;

	TestResultInfo( _T("\r\n------------------------------MCap RawData Test------------------------------\r\n") );

	if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	ISMChip5562* iChip5562 = (ISMChip5562*)SM_ChipBase(m_deviceNo);

    if(OP_LIKE_YY == G_XMLConfig->selected_format || OP_LIKE_XY == G_XMLConfig->selected_format)
    {
        isCsv = true;
    }

	int addRow = ( pCfg5562->real_channel_num - pCfg5562->va_channel_num ) ? 1 : 0;
	memset( uniformityMin, 0, sizeof(uniformityMin) );

	//iReCode = iChip5562->IncokeCommand( CMD_CTP_RST );
	//SysDelay( 100 );

	//iReCode = iChip5562->SetClkInFctMode( pCfg5562->mcap_clk_div, false );
	//if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	//SysDelay( 20 );
	//iReCode = iChip5562->IncokeCommand( 0x05,0x02,0x5c);//取消补偿命令
	//SysDelay( 20 );

	iReCode = iChip5562->SwitchMode( MODE_RAWDATA, iRawDataLen );
	if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	SysDelay( 20 );

	memset( baseSum, 0, sizeof(baseSum) );
	for( int index = 0; index < iRetry; index++ )
	{
		iReCode = iChip5562->GetRawData( baseTempBuffer, iRawDataLen );
		if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

		if(0 == index) continue;
		ArrayAddtion( baseSum, baseTempBuffer, iRawDataLen );
	}
	ArrayAverage( baseTempBuffer, baseSum, iRawDataLen, iRetry - 1);

	int ref_channel_num = min(pCfg5562->real_channel_num - pCfg5562->va_channel_num, pCfg5562->colsCnt);
	AnalyzeInfo info( pCfg5562->rowsCnt, pCfg5562->colsCnt, ref_channel_num, false );
	ReShappingData</*unsigned*/ short>( baseMatrix, (/*unsigned*/ short*)baseTempBuffer, G_XMLConfig->real_channel_num * 2, pCfg5562->rowsCnt, pCfg5562->colsCnt );
	//short baseMin[MAX_MCAP_ROW][MAX_MCAP_COL] = {0}, baseMax[MAX_MCAP_ROW][MAX_MCAP_COL] = {0};
	//FillArrayUseValue( baseMin, pCfg5562->base_min );
	//FillArrayUseValue( baseMax, pCfg5562->base_max );

	ColorText textTempa( _T("\r\nmcap_rawdata:\r\n") );
	PrintMaxtrixValueJudge( textTempa, baseMatrix,pCfg5562->invalid_node, info,isCsv, true );
	TestResultInfo( textTempa );
	Copy_RawData<MAX_MCAP_ROW,MAX_MCAP_COL>(NormalizationMatrix, baseMatrix, pCfg5562->rowsCnt, pCfg5562->colsCnt);

	auto pioce = 1.0f;
	RawData_Normalization<MAX_MCAP_ROW,MAX_MCAP_COL>(NormalizationMatrix,pCfg5562->mcap_rawdata_min, pCfg5562->mcap_rawdata_max,pCfg5562->rowsCnt, pCfg5562->colsCnt,pCfg5562->macp_normalization_ratio_min,pCfg5562->macp_normalization_ratio_max,pioce);

	TestResultInfoR(_T("\r\nnormalization_constant = %.2f, min =%.2f, max= %.2f\r\n"),pioce,pCfg5562->macp_normalization_ratio_min,pCfg5562->macp_normalization_ratio_max );

	{
		NodeVal nodeOutRange;
		ColorText textTemp( _T("\r\nmcap_normalization:\r\n") );
		bool bResult = AnalyzeTestResultJudge( NormalizationMatrix, pCfg5562->mcap_rawdata_min, pCfg5562->mcap_rawdata_max, pCfg5562->invalid_node, info, textTemp, nodeOutRange, isCsv, true );
		TestResultInfo( textTemp );
		if( !bResult )
		{
			failerCount++;
			LPCTSTR strHead = _T("\r\n//========= Out of Threshold in MCap RawData Test: \r\n");
			PrintNodeValue( m_ColorText, &nodeOutRange, strHead );
		}
	}
	
	if(pCfg5562->check_uniformity_hor)
	{
		NodeVal nodeOutRange;
		NodeVal nodeOutRange1;
		unsigned short hv_over_limit_num=0;
		ColorText textTemp( _T("\r\nmcap_uniformity_h:\r\n") );
		short uniformityHorMatrix[MAX_MCAP_ROW][MAX_MCAP_COL];
		unsigned char uniformityHorInvalid[MAX_MCAP_ROW][MAX_MCAP_COL];
		CopyAndInvalid( uniformityHorInvalid, pCfg5562->invalid_node, 0, MAX_MCAP_COL );
		GenHorizontalUniformity( NormalizationMatrix, uniformityHorMatrix, pCfg5562->rowsCnt, pCfg5562->colsCnt );
		bool bResult = AnalyzeTestResult_H_V_Judge<short,short,unsigned short,float,unsigned short,50,50>
			( uniformityHorMatrix, uniformityMin, pCfg5562->mcap_uniformity_h, uniformityHorInvalid, info, textTemp, nodeOutRange,
			pCfg5562->uniformity_invalid_node,pCfg5562->macp_h_v_over_limit_ratio,hv_over_limit_num, nodeOutRange1,isCsv, true);
		TestResultInfo( textTemp );
		if( !bResult )
		{
			failerCount++;
			LPCTSTR strHead = _T("\r\n//========= Out of Threshold in MCap Uniformity-H: \r\n");
			PrintNodeValue( m_ColorText, &nodeOutRange, strHead );
		}
		if (hv_over_limit_num > 0)
		{
			TestResultInfoR("\r\nPoint:%d,Exceeds the threshold by (%.2f%%)\r\n",hv_over_limit_num,pCfg5562->macp_h_v_over_limit_ratio*100);
			LPCTSTR strHead1 = _T("//========= Risk Point in MCap Uniformity-H: \r\n");
			PrintNodeValue( m_ColorText, &nodeOutRange1, strHead1 );
			if (hv_over_limit_num > pCfg5562->macp_h_v_over_limit_maxnum)
			{
				TestResultInfoR("Uniformity-H:number of abnormal points(%d) > limit num(%d)\r\n",hv_over_limit_num,pCfg5562->macp_h_v_over_limit_maxnum);
				failerCount++;
			}
		}
	}

	if(pCfg5562->check_uniformity_ver)
	{
		NodeVal nodeOutRange;
		ColorText textTemp( _T("\r\nmcap_uniformity_v:\r\n") );
		NodeVal nodeOutRange1;
		unsigned short hv_over_limit_num=0;
		short uniformityVerMatrix[MAX_MCAP_ROW][MAX_MCAP_COL];
		unsigned char uniformityVerInvalid[MAX_MCAP_ROW][MAX_MCAP_COL];
		CopyAndInvalid( uniformityVerInvalid, pCfg5562->invalid_node, MAX_MCAP_ROW, 0 );
		GenVerticalUniformity( NormalizationMatrix, uniformityVerMatrix, pCfg5562->rowsCnt, pCfg5562->colsCnt );
		bool bResult = AnalyzeTestResult_H_V_Judge<short,short,unsigned short,float,unsigned short,50,50>
			( uniformityVerMatrix, uniformityMin, pCfg5562->mcap_uniformity_v, uniformityVerInvalid, info, textTemp, nodeOutRange, 
			pCfg5562->uniformity_invalid_node,pCfg5562->macp_h_v_over_limit_ratio,hv_over_limit_num, nodeOutRange1, isCsv, true );
		TestResultInfo( textTemp );
		if( !bResult )
		{
			failerCount++;
			LPCTSTR strHead = _T("\r\n//========= Out of Threshold in MCap Uniformity-V: \r\n");
			PrintNodeValue( m_ColorText, &nodeOutRange, strHead );
		}
		if (hv_over_limit_num > 0)
		{
			TestResultInfoR("\r\nPoint:%d,Exceeds the threshold by (%.2f%%)\r\n",hv_over_limit_num,pCfg5562->macp_h_v_over_limit_ratio*100);
			LPCTSTR strHead1 = _T("//========= Risk Point in MCap Uniformity-V: \r\n");
			PrintNodeValue( m_ColorText, &nodeOutRange1, strHead1 );
			if (hv_over_limit_num > pCfg5562->macp_h_v_over_limit_maxnum)
			{
				TestResultInfoR("Uniformity-V:number of abnormal points(%d) > limit num(%d)\r\n",hv_over_limit_num,pCfg5562->macp_h_v_over_limit_maxnum);
				failerCount++;
			}
		}
	}

	auto sampling = Judge_RawData_sampling<MAX_MCAP_ROW,MAX_MCAP_COL>(pCfg5562->mcap_rawdata_min, pCfg5562->mcap_rawdata_max,pCfg5562->invalid_node,pCfg5562->rowsCnt, pCfg5562->colsCnt,pCfg5562->rawdata_min_value,pCfg5562->rawdata_max_value);
	if(sampling == false)
	{
		failerCount++;
		TestResultInfoR(_T("\r\nMcap_rawdata not sampled\r\n"));
	}

	if( failerCount )
	{
		itemNotify.UpdateItemResult( ITEM_STA_FAIL );
		TestResultInfo( "\r\n\r\n//MCap RawData Test is Fail\r\n", ITEM_STA_FAIL );
	}
	else
	{
		itemNotify.UpdateItemResult( ITEM_STA_PASS );
		TestResultInfo( "\r\n\r\n//MCap Test is Pass\r\n", ITEM_STA_PASS );
	}

	return itemNotify;
}
unsigned int CTest5562::Short_Test( NativeTestItem& itemQuote )
{
    bool isCsv = false;
	int failerCount = 0;
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );
	const int max_short_adc_num = (20+42);
	unsigned short shortAdc[max_short_adc_num] = {0};
	unsigned short adcMatrix[2][MAX_MCAP_COL] = {0};
	AnalyzeInfo info( pCfg5562->rowsCnt, pCfg5562->colsCnt, 0, false );

	TestResultInfo( _T("\r\n------------------------------Short Test------------------------------\r\n") );

	if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	ISMChip5562* iChip5562 = (ISMChip5562*)SM_ChipBase(m_deviceNo);

    if(OP_LIKE_YY == G_XMLConfig->selected_format || OP_LIKE_XY == G_XMLConfig->selected_format)
    {
        isCsv = true;
    }

	iReCode = iChip5562->IncokeCommand(CMD_CTP_RST);
	SysDelay( 500 );

	iReCode = iChip5562->GetShortData( shortAdc, max_short_adc_num * 2 );
	if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	unsigned short maxCols[] = { pCfg5562->colsCnt, pCfg5562->rowsCnt };
	ICArrayToSensorMatrix( adcMatrix, shortAdc, max_short_adc_num, 2, maxCols );

	NodeVal nodeOutRange;
	NodeVal nodeOutRange_add;
	unsigned short adcMin[2][MAX_MCAP_COL] = {0};
	unsigned short adcMax[2][MAX_MCAP_COL] = {0}; 
	ColorText textTemp( _T("\r\nShort Data:\r\n") );
	ColorText textTemp_add( _T("\r\nAdditional Short Data:\r\n") );
	FillMatrixUseValue( adcMin, (unsigned short)0 );
	FillMatrixRowUseValue( adcMax, pCfg5562->short_tx_max, 0 );
	FillMatrixRowUseValue( adcMax, pCfg5562->short_rx_max, 1 );
	adcMax[0][6] = 1300;
	bool bResult = AnalyzeTestResultMSCapJudge<unsigned short>( adcMatrix, adcMin, adcMax, pCfg5562->invalid_node, info, textTemp, nodeOutRange, isCsv );
	TestResultInfo( textTemp );
	if( !bResult )
	{
		failerCount++;
		LPCTSTR strHead = _T("\r\n//========= Out of Threshold in ShortTest: \r\n");
		PrintNodeValue( m_ColorText, &nodeOutRange, strHead );
	}

	if( failerCount )
	{
		itemNotify.UpdateItemResult( ITEM_STA_FAIL );
		TestResultInfo( "\r\n\r\n//Short Test is Fail\r\n", ITEM_STA_FAIL );
	}
	else
	{
        bool bResult_add = AnalyzeTestResultAdditionalMSCapJudge<unsigned short>( shortAdc, adcMin, adcMax, MAX_RX_NUM_5562, MAX_TX_NUM_5562, textTemp_add, nodeOutRange_add, isCsv);
        if( !bResult_add )
        {
            TestResultInfo( textTemp_add );
            LPCTSTR strHead_add = _T("\r\n//========= Out of Threshold in Additional ShortTest: \r\n");
            PrintNodeValue( m_ColorText, &nodeOutRange_add, strHead_add );
            itemNotify.UpdateItemResult( ITEM_STA_FAIL );
            TestResultInfo( "\r\n\r\n//Short Test is Fail\r\n", ITEM_STA_FAIL );
        }
        else
        {
            itemNotify.UpdateItemResult( ITEM_STA_PASS );
            TestResultInfo( "\r\n\r\n//Short Test is Pass\r\n", ITEM_STA_PASS );
        }
	}

	return itemNotify;
}
unsigned int CTest5562::FRT_Test( NativeTestItem& itemQuote )
{
	int failerCnt = 0;
	unsigned int iReCode = ERROR_CODE_COMM_ERROR, errCode = 0;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );
	unsigned char retBuffer[20];
	//char tempBuffer[MAX_PATH];

	TestResultInfo( _T("\r\n------------------------------FRT Test------------------------------\r\n") );

	if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	ISMChip5562* iChip5562 = (ISMChip5562*)SM_ChipBase(m_deviceNo);

	iReCode = iChip5562->IncokeCommand( CMD_RAM_TST, 0, 0, 0, retBuffer );
	if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	errCode = *(unsigned int*)&retBuffer[2];
	if(0x54000000 != errCode)
	{
		failerCnt++;
		//transformat( tempBuffer, _T("ReadCoreSpace, Code = 0x%x\r\n"), errCode );
		//TestResultInfo( tempBuffer );
		TestResultInfoR( _T("ReadCoreSpace, Code = 0x%x\r\n"), errCode );
	}


	iReCode = iChip5562->IncokeCommand( CMD_FLASH_TST, 0, 0, 0, retBuffer );
	if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	errCode = *(unsigned int*)&retBuffer[2];
	if(0x54000000 != errCode)
	{
		failerCnt++;
		//transformat( tempBuffer, _T("ReadBurnSpace, Code = 0x%x\r\n"), errCode );
		//TestResultInfo( tempBuffer );
		TestResultInfoR( _T("ReadBurnSpace, Code = 0x%x\r\n"), errCode );
	}

	if( failerCnt )
	{
		itemNotify.UpdateItemResult( ITEM_STA_FAIL );
		TestResultInfo( "\r\n\r\n//FRT Test is Fail\r\n", ITEM_STA_FAIL );
	}
	else
	{
		itemNotify.UpdateItemResult( ITEM_STA_PASS );
		TestResultInfo( "\r\n\r\n//FRT Test is Pass\r\n", ITEM_STA_PASS );
	}

	return itemNotify;
}
unsigned int CTest5562::IOVoltage_Test( NativeTestItem& itemQuote )
{
	int failerCnt = 0;
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );
	//TCHAR szTemp[MAX_PATH] = {0};

	TestResultInfo( _T("\r\n------------------------------IOVoltage Test------------------------------\r\n") );

	if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	ISMChip5562* iChip5562 = (ISMChip5562*)SM_ChipBase(m_deviceNo);

	unsigned int ioVols[2][10] = {0};
	iReCode = iChip5562->GetIoVoltage( ioVols );
	if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	if( PROTOCAL_IIC == pCfg5562->protocalType )
	{
		//transformat( szTemp, _T("pin = low,  int vol = %-6d,	sda vol = %-6d,	scl vol = %-6d\r\n"), ioVols[0][2], ioVols[0][0], ioVols[0][1] );
		//TestResultInfo( szTemp );
		TestResultInfoR( _T("pin = low,  int vol = %-6d,	sda vol = %-6d,	scl vol = %-6d\r\n"), ioVols[0][2], ioVols[0][0], ioVols[0][1] );
		//transformat( szTemp, _T("pin = high, int vol = %-6d,	sda vol = %-6d,	scl vol = %-6d\r\n"), ioVols[1][2], ioVols[1][0], ioVols[1][1] );
		//TestResultInfo( szTemp );
		TestResultInfoR( _T("pin = high, int vol = %-6d,	sda vol = %-6d,	scl vol = %-6d\r\n"), ioVols[1][2], ioVols[1][0], ioVols[1][1] );
	}
	else if( PROTOCAL_SPI == pCfg5562->protocalType )
	{
		//transformat( szTemp, _T("pin = low,  int vol = %-6d,	csn vol = %-6d,	mosi vol = %-6d,	miso = %-6d,	clk = %-6d\r\n"), ioVols[0][2], ioVols[0][3], ioVols[0][4], ioVols[0][5], ioVols[0][6] );
		//TestResultInfo( szTemp );
		TestResultInfoR( _T("pin = low,  int vol = %-6d,	csn vol = %-6d,	mosi vol = %-6d,	miso = %-6d,	clk = %-6d\r\n"), ioVols[0][2], ioVols[0][3], ioVols[0][4], ioVols[0][5], ioVols[0][6] );
		//transformat( szTemp, _T("pin = high, int vol = %-6d,	csn vol = %-6d,	mosi vol = %-6d,	miso = %-6d,	clk = %-6d\r\n"), ioVols[1][2], ioVols[1][3], ioVols[1][4], ioVols[1][5], ioVols[1][6] );
		//TestResultInfo( szTemp );
		TestResultInfoR( _T("pin = high, int vol = %-6d,	csn vol = %-6d,	mosi vol = %-6d,	miso = %-6d,	clk = %-6d\r\n"), ioVols[1][2], ioVols[1][3], ioVols[1][4], ioVols[1][5], ioVols[1][6] );
	}

	if( ioVols[0][2] < pCfg5562->int_low_min || ioVols[0][2] > pCfg5562->int_low_max )
	{
		failerCnt++;
		//transformat( szTemp, _T("int vol = %d, th = [%d - %d]\r\n"), ioVols[0][2], pCfg5562->int_low_min, pCfg5562->int_low_max );
		//TestResultInfo( szTemp );
		TestResultInfoR( _T("int vol = %d, th = [%d - %d]\r\n"), ioVols[0][2], pCfg5562->int_low_min, pCfg5562->int_low_max );
	}
	if( ioVols[1][2] < pCfg5562->int_high_min || ioVols[1][2] > pCfg5562->int_high_max )
	{
		failerCnt++;
		//transformat( szTemp, _T("int vol = %d, th = [%d - %d]\r\n"), ioVols[1][2], pCfg5562->int_high_min, pCfg5562->int_high_max );
		//TestResultInfo( szTemp );
		TestResultInfoR( _T("int vol = %d, th = [%d - %d]\r\n"), ioVols[1][2], pCfg5562->int_high_min, pCfg5562->int_high_max );
	}

	if( PROTOCAL_IIC == pCfg5562->protocalType )
	{
		if( ioVols[0][0] < pCfg5562->iic_low_min || ioVols[0][0] > pCfg5562->iic_low_max )
		{
			failerCnt++;
			//transformat( szTemp, _T("sda vol = %d, th = [%d - %d]\r\n"), ioVols[0][0], pCfg5562->iic_low_min, pCfg5562->iic_low_max );
			//TestResultInfo( szTemp );
			TestResultInfoR( _T("sda vol = %d, th = [%d - %d]\r\n"), ioVols[0][0], pCfg5562->iic_low_min, pCfg5562->iic_low_max);
		}
		if( ioVols[1][0] < pCfg5562->iic_high_min || ioVols[1][0] > pCfg5562->iic_high_max )
		{
			failerCnt++;
			//transformat( szTemp, _T("sda vol = %d, th = [%d - %d]\r\n"), ioVols[1][0], pCfg5562->iic_high_min, pCfg5562->iic_high_max );
			//TestResultInfo( szTemp );
			TestResultInfoR( _T("sda vol = %d, th = [%d - %d]\r\n"), ioVols[1][0], pCfg5562->iic_high_min, pCfg5562->iic_high_max );
		}

		if( ioVols[0][1] < pCfg5562->iic_low_min || ioVols[0][1] > pCfg5562->iic_low_max )
		{
			failerCnt++;
			//transformat( szTemp, _T("scl vol = %d, th = [%d - %d]\r\n"), ioVols[0][1], pCfg5562->iic_low_min, pCfg5562->iic_low_max );
			//TestResultInfo( szTemp );
			TestResultInfoR( _T("scl vol = %d, th = [%d - %d]\r\n"), ioVols[0][1], pCfg5562->iic_low_min, pCfg5562->iic_low_max );
		}
		if( ioVols[1][1] < pCfg5562->iic_high_min || ioVols[1][1] > pCfg5562->iic_high_max )
		{
			failerCnt++;
			//transformat( szTemp, _T("scl vol = %d, th = [%d - %d]\r\n"), ioVols[1][1], pCfg5562->iic_high_min, pCfg5562->iic_high_max );
			//TestResultInfo( szTemp );
			TestResultInfoR( _T("scl vol = %d, th = [%d - %d]\r\n"), ioVols[1][1], pCfg5562->iic_high_min, pCfg5562->iic_high_max );
		}
	}
	else if( PROTOCAL_SPI == pCfg5562->protocalType )
	{
		if( ioVols[0][3] < pCfg5562->spi_low_min || ioVols[0][3] > pCfg5562->spi_low_max )
		{
			failerCnt++;
			//transformat( szTemp, _T("csn vol = %d, th = [%d - %d]\r\n"), ioVols[0][3], pCfg5562->spi_low_min, pCfg5562->spi_low_max );
			//TestResultInfo( szTemp );
			TestResultInfoR( _T("csn vol = %d, th = [%d - %d]\r\n"), ioVols[0][3], pCfg5562->spi_low_min, pCfg5562->spi_low_max );
		}
		if( ioVols[1][3] < pCfg5562->spi_high_min || ioVols[1][3] > pCfg5562->spi_high_max )
		{
			failerCnt++;
			//transformat( szTemp, _T("csn vol = %d, th = [%d - %d]\r\n"), ioVols[1][3], pCfg5562->spi_high_min, pCfg5562->spi_high_max );
			//TestResultInfo( szTemp );
			TestResultInfoR( _T("csn vol = %d, th = [%d - %d]\r\n"), ioVols[1][3], pCfg5562->spi_high_min, pCfg5562->spi_high_max );
		}

		if( ioVols[0][4] < pCfg5562->spi_low_min || ioVols[0][4] > pCfg5562->spi_low_max )
		{
			failerCnt++;
			//transformat( szTemp, _T("mosi vol = %d, th = [%d - %d]\r\n"), ioVols[0][4], pCfg5562->spi_low_min, pCfg5562->spi_low_max );
			//TestResultInfo( szTemp );
			TestResultInfoR( _T("mosi vol = %d, th = [%d - %d]\r\n"), ioVols[0][4], pCfg5562->spi_low_min, pCfg5562->spi_low_max );
		}
		if( ioVols[1][4] < pCfg5562->spi_high_min || ioVols[1][4] > pCfg5562->spi_high_max )
		{
			failerCnt++;
			//transformat( szTemp, _T("mosi vol = %d, th = [%d - %d]\r\n"), ioVols[1][4], pCfg5562->spi_high_min, pCfg5562->spi_high_max );
			//TestResultInfo( szTemp );
			TestResultInfoR( _T("mosi vol = %d, th = [%d - %d]\r\n"), ioVols[1][4], pCfg5562->spi_high_min, pCfg5562->spi_high_max );
		}

		if( ioVols[0][5] < pCfg5562->spi_low_min || ioVols[0][5] > pCfg5562->spi_low_max )
		{
			failerCnt++;
			//transformat( szTemp, _T("miso vol = %d, th = [%d - %d]\r\n"), ioVols[0][5], pCfg5562->spi_low_min, pCfg5562->spi_low_max );
			//TestResultInfo( szTemp );
			TestResultInfoR(  _T("miso vol = %d, th = [%d - %d]\r\n"), ioVols[0][5], pCfg5562->spi_low_min, pCfg5562->spi_low_max );
		}
		if( ioVols[1][5] < pCfg5562->spi_high_min || ioVols[1][5] > pCfg5562->spi_high_max )
		{
			failerCnt++;
			//transformat( szTemp, _T("miso vol = %d, th = [%d - %d]\r\n"), ioVols[1][5], pCfg5562->spi_high_min, pCfg5562->spi_high_max );
			//TestResultInfo( szTemp );
			TestResultInfoR( _T("miso vol = %d, th = [%d - %d]\r\n"), ioVols[1][5], pCfg5562->spi_high_min, pCfg5562->spi_high_max );
		}

		if( ioVols[0][6] < pCfg5562->spi_low_min || ioVols[0][6] > pCfg5562->spi_low_max )
		{
			failerCnt++;
			//transformat( szTemp, _T("sclk vol = %d, th = [%d - %d]\r\n"), ioVols[0][6], pCfg5562->spi_low_min, pCfg5562->spi_low_max );
			//TestResultInfo( szTemp );
			TestResultInfoR( _T("sclk vol = %d, th = [%d - %d]\r\n"), ioVols[0][6], pCfg5562->spi_low_min, pCfg5562->spi_low_max );
		}
		if( ioVols[1][6] < pCfg5562->spi_high_min || ioVols[1][6] > pCfg5562->spi_high_max )
		{
			failerCnt++;
			//transformat( szTemp, _T("sclk vol = %d, th = [%d - %d]\r\n"), ioVols[1][6], pCfg5562->spi_high_min, pCfg5562->spi_high_max );
			//TestResultInfo( szTemp );
			TestResultInfoR(_T("sclk vol = %d, th = [%d - %d]\r\n"), ioVols[1][6], pCfg5562->spi_high_min, pCfg5562->spi_high_max );
		}
	}

	if( failerCnt )
	{
		itemNotify.UpdateItemResult( ITEM_STA_FAIL );
		TestResultInfo( "\r\n\r\n//IOVoltage Test is Fail\r\n", ITEM_STA_FAIL );
	}
	else
	{
		itemNotify.UpdateItemResult( ITEM_STA_PASS );
		TestResultInfo( "\r\n\r\n//IOVoltage Test is Pass\r\n", ITEM_STA_PASS );
	}

	return itemNotify;
}
unsigned int CTest5562::Noise_Test( NativeTestItem& itemQuote )
{
    bool isCsv = false;
	int failerCount = 0;
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );
	signed short baseTempBuffer[MAX_MCAP_CHANNEL * 2] = {0};
	//signed short MaxTempBuffer[MAX_MCAP_CHANNEL * 2] = {0};
	//signed short MinTempBuffer[MAX_MCAP_CHANNEL * 2] = {0};
	//signed short diffTempBuffer[MAX_MCAP_CHANNEL * 2] = {0};
	/*unsigned*/ short dataMatrix[MAX_MCAP_ROW][MAX_MCAP_COL];
	const unsigned int iRawDataLen = ((pCfg5562->rowsCnt + 1) * (pCfg5562->colsCnt + 1) * 2 + 3) & 0xfffffffc;
	const unsigned int iScapRawDataLen = pCfg5562->rowsCnt + pCfg5562->colsCnt;
	unsigned short retBuffer[16] = {0};
	short noiseMin[MAX_MCAP_ROW][MAX_MCAP_COL], noiseMax[MAX_MCAP_ROW][MAX_MCAP_COL];

	short MaxMcapNoise[8] = {pCfg5562->noise_max_mcap1, pCfg5562->noise_max_mcap2, pCfg5562->noise_max_mcap3, pCfg5562->noise_max_mcap4, pCfg5562->noise_max_mcap5, pCfg5562->noise_max_mcap6, pCfg5562->noise_max_mcap7, pCfg5562->noise_max_mcap7 };
	short MaxScapNoise[8] = {pCfg5562->noise_max_scap1, pCfg5562->noise_max_scap2, pCfg5562->noise_max_scap3, pCfg5562->noise_max_scap4, pCfg5562->noise_max_scap5, pCfg5562->noise_max_scap6, pCfg5562->noise_max_scap7, pCfg5562->noise_max_scap7 };

	TestResultInfo( _T("\r\n------------------------------Noise Test------------------------------\r\n") );

	if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	ISMChip5562* iChip5562 = (ISMChip5562*)SM_ChipBase(m_deviceNo);

    if(OP_LIKE_YY == G_XMLConfig->selected_format || OP_LIKE_XY == G_XMLConfig->selected_format)
    {
        isCsv = true;
    }

	iReCode = iChip5562->SwitchMode( MODE_RAWDATA, iRawDataLen );
	if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	for (int i =1; i<= pCfg5562->tmp_num; i++)
	{
		iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand(CMD_CTP_FREQ,16,i, pCfg5562->noise_frame,(unsigned char*)retBuffer);
		if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
		for (int k=0; k<100; k++)
		{
			SysDelay(20);
			iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand(CMD_CTP_FREQ,16,100, 0,(unsigned char*)retBuffer);
			if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
			unsigned short d0 = retBuffer[1];
			if(1 == d0)
			{
				break;

			}else if(0 == d0)
			{
				TestResultInfoR("\r\nGet tmp %d noise fail!!!", i);
				return itemNotify.UpdateItemResult( ITEM_STA_FAIL);
			}
			if (k > 30)
			{
				TestResultInfoR("\r\nGet tmp %d noise timeout!!!", i);
				return itemNotify.UpdateItemResult( ITEM_STA_FAIL);
			}

		}
		
		iReCode = iChip5562->GetFwData((short*)baseTempBuffer, iRawDataLen );
		if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

		//iReCode = iChip5562->SwitchMode( MODE_RAWDATA, iRawDataLen );
		//if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
		//SysDelay( 5 );
		//iReCode = iChip5562->GetRawData( (short*)baseTempBuffer, iRawDataLen  );
		//if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

		int ref_channel_num = min(pCfg5562->real_channel_num - pCfg5562->va_channel_num, pCfg5562->colsCnt);
		AnalyzeInfo info( pCfg5562->rowsCnt, pCfg5562->colsCnt, ref_channel_num, false );
		ReShappingData</*unsigned*/ short>( dataMatrix, (/*unsigned*/ short*)baseTempBuffer, G_XMLConfig->real_channel_num * 2, pCfg5562->rowsCnt, pCfg5562->colsCnt );

		
		FillMatrixUseValue( noiseMin, (short)0 );
		FillMatrixUseRatio<short,float,50,50>( noiseMax,pCfg5562->noise_mcap_base ,((float)MaxMcapNoise[i-1])/100 );

		NodeVal nodeOutRange;
		ColorText textTemp(StrFormat("\r\nNoise Tmp %d McapData:\r\n",i) );
		bool bResult = AnalyzeTestResultJudge<short, short, short, MAX_MCAP_ROW, MAX_MCAP_COL>( dataMatrix, noiseMin, noiseMax, pCfg5562->invalid_node, info, textTemp, nodeOutRange, isCsv, true );
		TestResultInfo( textTemp );
		if( !bResult )
		{
			failerCount++;
			LPCTSTR strHead = _T("\r\n//========= Out of Threshold in McapNoiseTest: \r\n");
			PrintNodeValue( m_ColorText, &nodeOutRange, strHead );
			//break;
		}


		NodeVal nodeOutRangeScap;
		FillMatrixUseValue( dataMatrix, (short)0 );
		FillMatrixUseValue( noiseMin, (short)0 );
		FillMatrixUseRatio<short,float,50,50>( noiseMax,pCfg5562->noise_scap_base, ((float)MaxScapNoise[i-1])/100 );
		unsigned short maxCols[] = { pCfg5562->colsCnt, pCfg5562->rowsCnt };
		ReShappingData</*unsigned*/ short>( dataMatrix, (/*unsigned*/ short*)baseTempBuffer + pCfg5562->rowsCnt * pCfg5562->colsCnt, iScapRawDataLen, 2, maxCols );
		ColorText textTempScap(StrFormat("\r\nNoise Tmp %d ScapData:\r\n",i) );
		bResult = AnalyzeTestResultMSCapJudge<short, short, short, MAX_MCAP_ROW, MAX_MCAP_COL>( dataMatrix, noiseMin, noiseMax, pCfg5562->invalid_node, info, textTempScap, nodeOutRangeScap, isCsv, true );
		TestResultInfo( textTempScap );
		if( !bResult )
		{
			failerCount++;
			LPCTSTR strHead = _T("\r\n//========= Out of Threshold in ScapNoiseTest: \r\n");
			PrintNodeValue( m_ColorText, &nodeOutRangeScap, strHead );
			//break;
		}

		if(0 != failerCount)
		{
			//break;
		}

	}

	if( failerCount )
	{
		itemNotify.UpdateItemResult( ITEM_STA_FAIL );
		TestResultInfo( "\r\n\r\n//Noise Test is Fail\r\n", ITEM_STA_FAIL );
	}
	else
	{
		itemNotify.UpdateItemResult( ITEM_STA_PASS );
		TestResultInfo( "\r\n\r\n//Noise Test is Pass\r\n", ITEM_STA_PASS );
	}

	return itemNotify;

	
}

typedef struct _raw_flash_info {
	unsigned int sig;
	unsigned char sizeHead;
	unsigned char cnt;
	unsigned char version;
	unsigned char type;
	unsigned short lenTotal;
	unsigned short lenSingle;
	unsigned int chkHead;
	unsigned int chkAll;
	unsigned int chk[8];
	unsigned int chkCfgCdsp;
	unsigned char head2En;
	unsigned char reserveByte;
	unsigned short head2Offset;
	unsigned int time;
	unsigned int reserve[4];
} raw_flash_info;

unsigned int CTest5562::Base_Test( NativeTestItem& itemQuote )
{
    bool isCsv = false;
	int failerCount = 0;
	unsigned short retBuffer[16];
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );
	short baseTempBuffer[MAX_MCAP_CHANNEL * 2] = {0};
	short baseTempBuffer1[MAX_MCAP_CHANNEL] = {0};
	short mcap_dataMatrix[MAX_MCAP_ROW][MAX_MCAP_COL];
	short scap_dataMatrix[MAX_MCAP_ROW][MAX_MCAP_COL];

	const unsigned short (*tmp_base[8])[50]={pCfg5562->tmp_1_mcapdata, pCfg5562->tmp_2_mcapdata, pCfg5562->tmp_3_mcapdata, pCfg5562->tmp_4_mcapdata, pCfg5562->tmp_5_mcapdata, pCfg5562->tmp_6_mcapdata, pCfg5562->tmp_7_mcapdata, pCfg5562->tmp_8_mcapdata};
	
	const unsigned int iRetry = 10;

	const unsigned int iRawDataLen = ((pCfg5562->rowsCnt * pCfg5562->colsCnt + pCfg5562->rowsCnt + pCfg5562->colsCnt) * 2 + 3) & 0xfffffffc;
	const unsigned int iScapRawDataLen = pCfg5562->rowsCnt + pCfg5562->colsCnt;

	short diff_dataMatrix[MAX_MCAP_ROW][MAX_MCAP_COL];

	TestResultInfo( _T("\r\n------------------------------Base Data Test------------------------------\r\n") );

	if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	ISMChip5562* iChip5562 = (ISMChip5562*)SM_ChipBase(m_deviceNo);

    if(OP_LIKE_YY == G_XMLConfig->selected_format || OP_LIKE_XY == G_XMLConfig->selected_format)
    {
        isCsv = true;
    }

	int addRow = ( pCfg5562->real_channel_num - pCfg5562->va_channel_num ) ? 1 : 0;

	int ref_channel_num = min(pCfg5562->real_channel_num - pCfg5562->va_channel_num, pCfg5562->colsCnt);
	AnalyzeInfo info( pCfg5562->rowsCnt, pCfg5562->colsCnt );
	unsigned short maxCols[] = { pCfg5562->colsCnt, pCfg5562->rowsCnt };

	ColorText textTemp;

	iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_CTP_RST );
	if( iReCode != ERROR_CODE_OK ) itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	SysDelay( 200 );

	iReCode = iChip5562->SwitchMode( MODE_RAWDATA, iRawDataLen );
	if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	for(int i = 0; i < 8; i++)
	{
		if (i < pCfg5562->tmp_num)
		{ 
			iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand(CMD_CTP_FREQ,0x15,i + 1, 20);
			if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

			for (int k=0; k<100; k++)
			{
				SysDelay(20);
				iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand(CMD_CTP_FREQ,0x15,100, 0,(unsigned char*)retBuffer);
				if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
				unsigned short d0 = retBuffer[1];
				if(1 == d0)
				{
					break;

				}else if(0 == d0)
				{
					TestResultInfoR("\r\nGet fast freq data fail!!!");
					return itemNotify.UpdateItemResult( ITEM_STA_FAIL);
				}
				if (k > 30)
				{
					TestResultInfoR("\r\nGet fast freq data timeout!!!");
					return itemNotify.UpdateItemResult( ITEM_STA_FAIL);
				}

			}

			iReCode = iChip5562->GetFwData((short*)baseTempBuffer, iRawDataLen );
			if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

		}
		else
		{
			memset(baseTempBuffer,0,sizeof(baseTempBuffer));
			break;
		}
		
		auto str = StrFormat("\r\ntmp_%d_mcapdata:\r\n",i+1);
		textTemp+=str;

		ReShappingData</*unsigned*/ short>( mcap_dataMatrix, (/*unsigned*/ short*)baseTempBuffer, G_XMLConfig->real_channel_num * 2, pCfg5562->rowsCnt, pCfg5562->colsCnt );
		PrintMaxtrixValueJudge<short, MAX_MCAP_ROW, MAX_MCAP_COL>( textTemp, mcap_dataMatrix, info, isCsv, true );

		str = StrFormat("\r\ntmp_%d_scapdata:\r\n",i+1);
		textTemp+=str;
		ReShappingData</*unsigned*/ short>( scap_dataMatrix, (/*unsigned*/ short*)baseTempBuffer + pCfg5562->rowsCnt * pCfg5562->colsCnt, iScapRawDataLen, 2, maxCols );
		PrintScapDataJudge<short, MAX_MCAP_ROW, MAX_MCAP_COL>( textTemp, scap_dataMatrix, pCfg5562->tmp_invalid_node, info, isCsv, true );

		str = StrFormat("\r\nnormalization_%d_mcapdata:\r\n",i+1);
		textTemp+=str;
		tmp_data_normalization<short, short, MAX_MCAP_ROW, MAX_MCAP_COL>(mcap_dataMatrix, mcap_dataMatrix, pCfg5562->rowsCnt, pCfg5562->colsCnt,1);
		PrintMaxtrixValueJudge<short, MAX_MCAP_ROW, MAX_MCAP_COL>( textTemp, mcap_dataMatrix, info, isCsv, true );

		str = StrFormat("\r\nnormalization_%d_bmcapdata:\r\n",i+1);
		textTemp+=str;
		PrintMaxtrixValueJudge<const unsigned short, MAX_MCAP_ROW, MAX_MCAP_COL>( textTemp, tmp_base[i], info, isCsv, true );

		MatrixSubtraction<short, short, const unsigned short, MAX_MCAP_ROW, MAX_MCAP_COL>(diff_dataMatrix, mcap_dataMatrix, tmp_base[i], MAX_MCAP_ROW, MAX_MCAP_COL);	

		str = StrFormat("\r\ndiff_%d_mcapdata:\r\n",i+1);
		textTemp+=str;
		PrintMaxtrixValueJudge<short, MAX_MCAP_ROW, MAX_MCAP_COL>( textTemp, diff_dataMatrix, info, isCsv, true );

		ConvertShappingData<short, MAX_MCAP_ROW, MAX_MCAP_COL>(baseTempBuffer1,diff_dataMatrix, G_XMLConfig->real_channel_num * 2, pCfg5562->rowsCnt, pCfg5562->colsCnt );

		RollingR pRolling;
		pRolling.RollingNoiseFit1(baseTempBuffer1,(unsigned char)pCfg5562->rowsCnt, (unsigned char)pCfg5562->colsCnt);

		ReShappingData</*unsigned*/ short>( diff_dataMatrix, (/*unsigned*/ short*)baseTempBuffer1, G_XMLConfig->real_channel_num * 2, pCfg5562->rowsCnt, pCfg5562->colsCnt );

		MatrixInvalidSet<short, MAX_MCAP_ROW, MAX_MCAP_COL>(diff_dataMatrix, pCfg5562->tmp_invalid_node, MAX_MCAP_ROW, MAX_MCAP_COL, 0);

		str = StrFormat("\r\nfinal_diff_%d_mcapdata:\r\n",i+1);
		textTemp+=str;
		NodeVal nodeOutRange;
		bool bResult = WTmpDiffAnalyzeTestResultJudge<short, MAX_MCAP_ROW,MAX_MCAP_COL>(diff_dataMatrix, pCfg5562->rowsCnt, pCfg5562->colsCnt, pCfg5562->base_diff_max, pCfg5562->base_num_max,
			pCfg5562->base_all_diff_max, pCfg5562->base_all_num_max, textTemp, nodeOutRange, isCsv);
		if (!bResult)
		{
			failerCount++;
			LPCTSTR strHead = _T("\r\n//========= Out of Threshold in base Test: \r\n");
			PrintBaseNodeValue( textTemp, &nodeOutRange, strHead );
		}

	}

	TestResultInfo( textTemp );

	if( failerCount )
	{
		itemNotify.UpdateItemResult( ITEM_STA_FAIL );
		TestResultInfo( "\r\n\r\n//BaseData Test is Fail\r\n", ITEM_STA_FAIL );
	}
	else
	{
		itemNotify.UpdateItemResult( ITEM_STA_PASS );
		TestResultInfo( "\r\n\r\n//BaseData Test is Pass\r\n", ITEM_STA_PASS );
	}

	return itemNotify;
}
unsigned int CTest5562::SetClkInFctMode( unsigned short clkDiv )
{
	return SM_ChipBase(m_deviceNo)->SetClkInFctMode(clkDiv, pCfg5562->filter_off);
}
unsigned int CTest5562::WorkForGraphMode( bool bEnterGraphing /*= false*/ )
{
	unsigned int iReCode = ERROR_CODE_OK;

	if( bEnterGraphing && !IsTestInGraphStep() )
	{
		iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_CTP_RST );
		CHECK_RETURN_IF_FAIL( iReCode );

		SysDelay( 200 );

		iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_SWITCH_IIC );
		CHECK_RETURN_IF_FAIL( iReCode );

		SysDelay( 50 );

		iReCode = SM_ChipBase(m_deviceNo)->SwitchMode( MODE_TOUCH );
		CHECK_RETURN_IF_FAIL( iReCode );
	}
	else
	{

	}

	bEnterGraphing ? SetTestStatusInGraphStep() : SetTestStatusInDataStep();

	return iReCode;
}

//unsigned int CTest5562::TP_RemoveTest(NativeTestItem& itemQuote)
//{
//	unsigned int iReCode = ERROR_CODE_OK;
//	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );
//
//	while( IsLoopStillRun() )
//	{
//		if( !HaveTpLinked_CHCT550()) break;
//
//		itemNotify.UpdateItemResult( ITEM_STA_WAIT );
//		::Sleep( 300 );
//
//		if( !HaveTpLinked_CHCT550() ) break;
//
//		itemNotify.UpdateItemResult( ITEM_STA_START );
//		::Sleep( 300 );
//	}
//
//	return itemNotify.UpdateItemResult( ITEM_STA_PASS );
//
//}
//
//unsigned int CTest5562::TP_WaitTest(NativeTestItem& itemQuote)
//{
//	unsigned int iReCode = ERROR_CODE_OK;
//	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );
//
//	while( IsLoopStillRun() )
//	{
//		if( HaveTpLinked_CHCT550()) break;
//
//		itemNotify.UpdateItemResult( ITEM_STA_WAIT );
//		::Sleep( 300 );
//
//		if( HaveTpLinked_CHCT550() ) break;
//
//		itemNotify.UpdateItemResult( ITEM_STA_START );
//		::Sleep( 300 );
//	}
//
//	return itemNotify.UpdateItemResult( ITEM_STA_PASS );
//}
//
//bool CTest5562::HaveTpLinked_CHCT550()
//{
//	unsigned int iReCode = 0;
//	unsigned int buff_w = 0x11223344;
//	unsigned int buff_r = 0;
//	bool ret = false;
//	for (int k =0; k<5; k++)
//	{
//		iReCode = SM_ChipBase(m_deviceNo)->WriteCoreSpace( 0x20000000, (unsigned char*)&buff_w, 4 );
//		if( iReCode != ERROR_CODE_OK ) ret = false;
//		iReCode = SM_ChipBase(m_deviceNo)->ReadCoreSpace( 0x20000000, (unsigned char*)&buff_r, 4 );
//		if( iReCode != ERROR_CODE_OK ) ret = false;
//		if(buff_w == buff_r) break;
//	}
//	if(buff_w == buff_r)
//	{
//		ret = true;
//	}
//	else
//	{
//		ret = false;
//	}
//
//	return ret;
//
//}

void CTest5562::PrepareSimulate( SimulateData& sm )
{
	unsigned char cmdID = sm.itemID & 0xff;
	unsigned char dataIndex = (sm.itemID >> 8) & 0xff;
	unsigned char sumCnt = 1;
	int iDesIndex = 0;

	//scap data
	if( sm.itemID == ((0xfa << 16) + 0x28) )
	{
		iDesIndex += pCfg5562->rowsCnt * pCfg5562->colsCnt;
		for( int iCol = 0; iCol <  pCfg5562->colsCnt; iCol++ )
			sm.itemArray[iDesIndex++] = sm.itemData[0][iCol] * sumCnt;
		for( int iCol = 0; iCol < pCfg5562->rowsCnt; iCol++ )
			sm.itemArray[iDesIndex++] = sm.itemData[1][iCol] * sumCnt;
	}
	else
	{
		for( int iRow = 0; iRow < sm.rows; iRow++ )
		{
			for( int iCol = 0; iCol < sm.cols; iCol++ )
			{
				if( iDesIndex >= sizeof(sm.itemArray)/sizeof(short) ) break;

				//int icPosition = pCfg5562->sensor_2_ic_map[index];
				sm.itemArray[iDesIndex++] = sm.itemData[iRow][iCol] * sumCnt;
			}
		}
	}
}

unsigned int CTest5562::MISC_Test( NativeTestItem& itemQuote )
{
	int failerCnt = 0;
	unsigned int iReCode = ERROR_CODE_COMM_ERROR, errCode = 0;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );
	//char tempBuffer[MAX_PATH];

	TestResultInfo( _T("\r\n------------------------------MISC Test------------------------------\r\n") );

	if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	ISMChip5562* iChip5562 = (ISMChip5562*)SM_ChipBase(m_deviceNo);

	unsigned short rsp[8] = {0};
	iReCode = iChip5562->IncokeCommand( CMD_MISC_TST, pCfg5562->misc_mode, 0, 0, (unsigned char*)rsp );
	if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	if(rsp[1])
	{
		failerCnt++;
		//transformat( tempBuffer, _T("Misc(%d), Code = 0x%x\r\n"), rsp[1],  (rsp[2] << 16) + rsp[3]);
		//TestResultInfo( tempBuffer );
		TestResultInfoR( _T("Misc(%d), Code = 0x%x\r\n"), rsp[1],  (rsp[2] << 16) + rsp[3] );
	}

	if( failerCnt )
	{
		itemNotify.UpdateItemResult( ITEM_STA_FAIL );
		TestResultInfo( "\r\n\r\n//MISC Test is Fail\r\n", ITEM_STA_FAIL );
	}
	else
	{
		itemNotify.UpdateItemResult( ITEM_STA_PASS );
		TestResultInfo( "\r\n\r\n//MISC Test is Pass\r\n", ITEM_STA_PASS );
	}

	return itemNotify;
}

unsigned int CTest5562::AverageData(short* buff, int len)
{
	int sum =0;
	short* data = (short*)buff;

	for (int i = 0; i< len; i++)
	{
		sum = sum + data[i];
	}

	return sum/len;
}

unsigned int CTest5562::FSD_Test(NativeTestItem& itemQuote)
{
    bool isCsv = false;
	int failerCount = 0;
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );
	signed short baseTempBuffer[MAX_MCAP_CHANNEL * 2] = {0};
	short fdataMatrix[MAX_MCAP_ROW][MAX_MCAP_COL];
	short sdataMatrix[MAX_MCAP_ROW][MAX_MCAP_COL];
	short diffMatrix[MAX_MCAP_ROW][MAX_MCAP_COL];
	short basediffMatrix[MAX_MCAP_ROW][MAX_MCAP_COL];
	const unsigned int iRawDataLen = ((pCfg5562->rowsCnt + 1) * (pCfg5562->colsCnt + 1) * 2 + 3) & 0xfffffffc;
	const unsigned int iScapRawDataLen = pCfg5562->rowsCnt + pCfg5562->colsCnt;
	unsigned short retBuffer[16] = {0};
	unsigned int data_addr = 0;

	int ref_channel_num = min(pCfg5562->real_channel_num - pCfg5562->va_channel_num, pCfg5562->colsCnt);
	AnalyzeInfo info( pCfg5562->rowsCnt, pCfg5562->colsCnt, ref_channel_num, false );

	TestResultInfo( _T("\r\n------------------------------FSD Test------------------------------\r\n") );

	if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	ISMChip5562* iChip5562 = (ISMChip5562*)SM_ChipBase(m_deviceNo);

    if(OP_LIKE_YY == G_XMLConfig->selected_format || OP_LIKE_XY == G_XMLConfig->selected_format)
    {
        isCsv = true;
    }

	iReCode = iChip5562->IncokeCommand(CMD_FSD_TST );
	if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand(CMD_IDENTITY,0,0,0,(unsigned char*)retBuffer);
	if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	if ((retBuffer[1] + retBuffer[2] != 0xffff) || (retBuffer[1] != 0xe903))
	{
		return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	}

	data_addr = (retBuffer[4] <<16) | retBuffer[3];

	iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand(CMD_CTP_PMU, pCfg5562->fsd_xy_num|pCfg5562->fsd_i2v_rfb<<8,
		pCfg5562->fsd_lpf_sft|pCfg5562->fsd_dec_sft<<8, pCfg5562->fsd_c2v_rfb|pCfg5562->fsd_rx_rin<<8,(unsigned char*)retBuffer);
	if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand(CMD_CTP_FREQ,0x15,pCfg5562->fsd_fast_div, pCfg5562->fsd_frames);
	if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	for (int k=0; k<100; k++)
	{
		SysDelay(20);
		iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand(CMD_CTP_FREQ,0x15,100, 0,(unsigned char*)retBuffer);
		if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
		unsigned short d0 = retBuffer[1];
		if(1 == d0)
		{
			break;

		}else if(0 == d0)
		{
			TestResultInfoR("\r\nGet fast freq data fail!!!");
			return itemNotify.UpdateItemResult( ITEM_STA_FAIL);
		}
		if (k > 30)
		{
			TestResultInfoR("\r\nGet fast freq data timeout!!!");
			return itemNotify.UpdateItemResult( ITEM_STA_FAIL);
		}

	}

	//iReCode = iChip5562->GetFwData((short*)baseTempBuffer, iRawDataLen );
	iReCode = iChip5562->ReadCoreSpace(data_addr,(unsigned char*)baseTempBuffer, iRawDataLen );
	if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	ReShappingData</*unsigned*/ short>( fdataMatrix, (/*unsigned*/ short*)baseTempBuffer, G_XMLConfig->real_channel_num * 2, pCfg5562->rowsCnt, pCfg5562->colsCnt );

	ColorText textTempa( _T("\r\nfsd_fast:\r\n") );
	PrintMaxtrixValueJudge<short,MAX_MCAP_ROW, MAX_MCAP_COL> ( textTempa, fdataMatrix,pCfg5562->invalid_node, info, isCsv, true );
	TestResultInfo( textTempa );

	iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand(CMD_CTP_FREQ,0x15,pCfg5562->fsd_slow_div, pCfg5562->fsd_frames);
	if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	for (int k=0; k<100; k++)
	{
		SysDelay(20);
		iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand(CMD_CTP_FREQ,0x15,100, 0,(unsigned char*)retBuffer);
		if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
		unsigned short d0 = retBuffer[1];
		if(1 == d0)
		{
			break;

		}else if(0 == d0)
		{
			TestResultInfoR("\r\nGet fast freq data fail!!!");
			return itemNotify.UpdateItemResult( ITEM_STA_FAIL);
		}
		if (k > 30)
		{
			TestResultInfoR("\r\nGet fast freq data timeout!!!");
			return itemNotify.UpdateItemResult( ITEM_STA_FAIL);
		}

	}

	//iReCode = iChip5562->GetFwData((short*)baseTempBuffer, iRawDataLen );
	iReCode = iChip5562->ReadCoreSpace(data_addr,(unsigned char*)baseTempBuffer, iRawDataLen );
	if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	ReShappingData</*unsigned*/ short>( sdataMatrix, (/*unsigned*/ short*)baseTempBuffer, G_XMLConfig->real_channel_num * 2, pCfg5562->rowsCnt, pCfg5562->colsCnt );

	textTempa = ( _T("\r\nfsd_slow:\r\n") );
	PrintMaxtrixValueJudge<short,MAX_MCAP_ROW, MAX_MCAP_COL> ( textTempa, sdataMatrix,pCfg5562->invalid_node, info, isCsv, true );
	TestResultInfo( textTempa );

	if (pCfg5562->fsd_fast_mcap_test == 1)
	{
		NodeVal nodeOutRange;
		ColorText textTemp = (_T("\r\nfast_macap_tset:\r\n")) ;
		bool bResult = AnalyzeTestResultJudge<short, unsigned short, unsigned short, MAX_MCAP_ROW, MAX_MCAP_COL>( fdataMatrix, pCfg5562->fsd_fast_min,pCfg5562->fsd_fast_max, pCfg5562->invalid_node, info, textTemp, nodeOutRange, isCsv, true );
		TestResultInfo( textTemp );
		if( !bResult )
		{
			failerCount++;
			LPCTSTR strHead = _T("\r\n//========= Out of Threshold in macap: \r\n");
			PrintNodeValue( m_ColorText, &nodeOutRange, strHead );
		}

	}

	fsd_diff<short,short,MAX_MCAP_ROW, MAX_MCAP_COL>(diffMatrix,fdataMatrix,sdataMatrix,pCfg5562->rowsCnt,pCfg5562->colsCnt);
	textTempa = ( _T("\r\nfsd_data:\r\n") );
	PrintMaxtrixValueJudge<short,MAX_MCAP_ROW, MAX_MCAP_COL> ( textTempa, diffMatrix,pCfg5562->invalid_node, info, isCsv, true );
	TestResultInfo( textTempa );

	fsd_diff<short,unsigned short,MAX_MCAP_ROW, MAX_MCAP_COL>(basediffMatrix,pCfg5562->fsd_fast,pCfg5562->fsd_slow,pCfg5562->rowsCnt,pCfg5562->colsCnt);

	textTempa = ( _T("\r\nfsd_base_data:\r\n") );
	PrintMaxtrixValueJudge<short,MAX_MCAP_ROW, MAX_MCAP_COL> ( textTempa, basediffMatrix,pCfg5562->invalid_node, info, isCsv, true );
	TestResultInfo( textTempa );

	textTempa = ( _T("\r\nfsd_diff:\r\n") );
	MatrixSubtraction<short, short, short, MAX_MCAP_ROW, MAX_MCAP_COL>(diffMatrix,basediffMatrix,diffMatrix,pCfg5562->rowsCnt,pCfg5562->colsCnt);
	PrintMaxtrixValueJudge<short,MAX_MCAP_ROW, MAX_MCAP_COL> ( textTempa, diffMatrix,pCfg5562->invalid_node, info, isCsv, true );
	TestResultInfo( textTempa );

	fsd_LineSubtraction<short, short, MAX_MCAP_ROW, MAX_MCAP_COL>(basediffMatrix,diffMatrix,pCfg5562->rowsCnt,pCfg5562->colsCnt,true);

	unsigned short mindata[MAX_MCAP_ROW][MAX_MCAP_COL];
	FillMatrixUseValue( mindata, (unsigned short)0 );

	NodeVal nodeOutRange;
	ColorText textTemp = (_T("\r\nfsd_final_diff:\r\n")) ;
	bool bResult = AnalyzeTestResultJudge<short, unsigned short, unsigned short, MAX_MCAP_ROW, MAX_MCAP_COL>( basediffMatrix, mindata, pCfg5562->fsd_diff_max, pCfg5562->invalid_node, info, textTemp, nodeOutRange, isCsv, true );
	TestResultInfo( textTemp );
	if( !bResult )
	{
		failerCount++;
		LPCTSTR strHead = _T("\r\n//========= Out of Threshold in base_diff: \r\n");
		PrintNodeValue( m_ColorText, &nodeOutRange, strHead );
	}

	if( failerCount )
	{
		itemNotify.UpdateItemResult( ITEM_STA_FAIL );
		TestResultInfo( "\r\n\r\n//FSD Test is Fail\r\n", ITEM_STA_FAIL );
	}
	else
	{
		itemNotify.UpdateItemResult( ITEM_STA_PASS );
		TestResultInfo( "\r\n\r\n//FSD Test is Pass\r\n", ITEM_STA_PASS );
	}

	return itemNotify;
}

void CTest5562::ICArrayToSensorMatrixVT(unsigned short (&dataOn)[1][MAX_MCAP_COL],unsigned short (&dataOff)[1][MAX_MCAP_COL], unsigned short* const dataToMapping)
{
	for( int iRx = 0; iRx < pCfg5562->rowsCnt; iRx++ )
	{
		unsigned short icChannel = pCfg5562->sensor_2_ic_map[iRx + MAX_TX_NUM_5562];
		dataOff[0][iRx] = dataToMapping[icChannel];
		dataOn[0][iRx] = dataToMapping[icChannel + 42];
	}
}

unsigned int CTest5562::WBase_Test(NativeTestItem& itemQuote)
{
    bool isCsv = false;
	int failerCount = 0;
	unsigned short retBuffer[16];
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );
	short baseTempBuffer[MAX_MCAP_CHANNEL] = {0};
	short baseTempBuffer1[MAX_MCAP_CHANNEL] = {0};
	short mcap_dataMatrix[MAX_MCAP_ROW][MAX_MCAP_COL];
	short scap_dataMatrix[MAX_MCAP_ROW][MAX_MCAP_COL];

	const unsigned short (*tmp_base[8])[MAX_MCAP_COL]={pCfg5562->tmp_1_mcapdata, pCfg5562->tmp_2_mcapdata, pCfg5562->tmp_3_mcapdata, pCfg5562->tmp_4_mcapdata, pCfg5562->tmp_5_mcapdata, pCfg5562->tmp_6_mcapdata, pCfg5562->tmp_7_mcapdata, pCfg5562->tmp_8_mcapdata};

	const unsigned int iRetry = 10;

	const unsigned int iRawDataLen = ((pCfg5562->rowsCnt * pCfg5562->colsCnt + pCfg5562->rowsCnt + pCfg5562->colsCnt) * 2 + 3) & 0xfffffffc;
	const unsigned int iScapRawDataLen = pCfg5562->rowsCnt + pCfg5562->colsCnt;

	unsigned char writeBuffer[20*1024] = {0};
	memset(writeBuffer,0xff,sizeof(writeBuffer));//必须初始化成0xff

	unsigned char readBuffer[20*1024] = {0};
	memset(readBuffer,0xff,sizeof(readBuffer));//必须初始化成0xff

	short diff_dataMatrix[MAX_MCAP_ROW][MAX_MCAP_COL];

	raw_flash_info* tmp_data;
	tmp_data = (raw_flash_info*)&writeBuffer[0];

	TestResultInfo( _T("\r\n------------------------------WBase Data Test------------------------------\r\n") );

	if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	ISMChip5562* iChip5562 = (ISMChip5562*)SM_ChipBase(m_deviceNo);

    if(OP_LIKE_YY == G_XMLConfig->selected_format || OP_LIKE_XY == G_XMLConfig->selected_format)
    {
        isCsv = true;
    }

	int addRow = ( pCfg5562->real_channel_num - pCfg5562->va_channel_num ) ? 1 : 0;

	int ref_channel_num = min(pCfg5562->real_channel_num - pCfg5562->va_channel_num, pCfg5562->colsCnt);
	AnalyzeInfo info( pCfg5562->rowsCnt, pCfg5562->colsCnt );
	unsigned short maxCols[] = { pCfg5562->colsCnt, pCfg5562->rowsCnt };

	ColorText textTemp;

	tmp_data->sig = FLASH_SAVE_SIG;
	tmp_data->sizeHead = sizeof(raw_flash_info);
	tmp_data->cnt = 1;
	tmp_data->version = 1;
	tmp_data->type = 0;
	tmp_data->lenSingle = iRawDataLen;
	tmp_data->lenTotal = sizeof(raw_flash_info) + iRawDataLen * pCfg5562->tmp_num;
	tmp_data->head2En = 0;
	tmp_data->chkHead = 0;
	tmp_data->chkAll = 0;

	SYSTEMTIME SysTime;
	::GetLocalTime(&SysTime);
	tmp_data->time = (SysTime.wMonth << 22) + (SysTime.wDay << 17) + (SysTime.wHour << 12) + (SysTime.wMinute << 6) + SysTime.wSecond;

	iReCode = SM_ChipBase(m_deviceNo)->EraseBurnSpace( USR_ROM_FACTORY_START, 20 * 1024);
	if( iReCode != ERROR_CODE_OK ) itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_CTP_RST );
	if( iReCode != ERROR_CODE_OK ) itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	SysDelay( 200 );

	iReCode = iChip5562->SwitchMode( MODE_RAWDATA, iRawDataLen );
	if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	for(int i = 0; i < 8; i++)
	{
		if (i < pCfg5562->tmp_num)
		{ 
			iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand(CMD_CTP_FREQ,0x15,i + 1, 20);
			if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

			for (int k=0; k<100; k++)
			{
				SysDelay(20);
				iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand(CMD_CTP_FREQ,0x15,100, 0,(unsigned char*)retBuffer);
				if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
				unsigned short d0 = retBuffer[1];
				if(1 == d0)
				{
					break;

				}else if(0 == d0)
				{
					TestResultInfoR("\r\nGet fast freq data fail!!!");
					return itemNotify.UpdateItemResult( ITEM_STA_FAIL);
				}
				if (k > 30)
				{
					TestResultInfoR("\r\nGet fast freq data timeout!!!");
					return itemNotify.UpdateItemResult( ITEM_STA_FAIL);
				}

			}

			iReCode = iChip5562->GetFwData((short*)baseTempBuffer, iRawDataLen );
			if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

		}
		else
		{
			memset(baseTempBuffer,0,sizeof(baseTempBuffer));
			break;
		}

		auto str = StrFormat("\r\ntmp_%d_mcapdata:\r\n",i+1);
		textTemp+=str;

		ReShappingData</*unsigned*/ short>( mcap_dataMatrix, (/*unsigned*/ short*)baseTempBuffer, G_XMLConfig->real_channel_num * 2, pCfg5562->rowsCnt, pCfg5562->colsCnt );
		PrintMaxtrixValueJudge<short, MAX_MCAP_ROW, MAX_MCAP_COL>( textTemp, mcap_dataMatrix, info, isCsv, true );

		str = StrFormat("\r\ntmp_%d_scapdata:\r\n",i+1);
		textTemp+=str;
		ReShappingData</*unsigned*/ short>( scap_dataMatrix, (/*unsigned*/ short*)baseTempBuffer + pCfg5562->rowsCnt * pCfg5562->colsCnt, iScapRawDataLen, 2, maxCols );
		PrintScapDataJudge<short, MAX_MCAP_ROW, MAX_MCAP_COL>( textTemp, scap_dataMatrix, pCfg5562->tmp_invalid_node, info, isCsv, true );

		str = StrFormat("\r\nnormalization_%d_mcapdata:\r\n",i+1);
		textTemp+=str;
		tmp_data_normalization<short, short, MAX_MCAP_ROW, MAX_MCAP_COL>(mcap_dataMatrix, mcap_dataMatrix, pCfg5562->rowsCnt, pCfg5562->colsCnt,1);
		PrintMaxtrixValueJudge<short, MAX_MCAP_ROW, MAX_MCAP_COL>( textTemp, mcap_dataMatrix, info, isCsv, true );

		str = StrFormat("\r\nnormalization_%d_bmcapdata:\r\n",i+1);
		textTemp+=str;
		PrintMaxtrixValueJudge<const unsigned short, MAX_MCAP_ROW, MAX_MCAP_COL>( textTemp, tmp_base[i], info, isCsv, true );

		MatrixSubtraction<short, short, const unsigned short, MAX_MCAP_ROW, MAX_MCAP_COL>(diff_dataMatrix, mcap_dataMatrix, tmp_base[i], MAX_MCAP_ROW, MAX_MCAP_COL);	

		str = StrFormat("\r\ndiff_%d_mcapdata:\r\n",i+1);
		textTemp+=str;
		/*调试屏蔽*/
		PrintMaxtrixValueJudge<short, MAX_MCAP_ROW, MAX_MCAP_COL>( textTemp, diff_dataMatrix, info, isCsv, true );

		ConvertShappingData<short, MAX_MCAP_ROW, MAX_MCAP_COL>(baseTempBuffer1,diff_dataMatrix, G_XMLConfig->real_channel_num * 2, pCfg5562->rowsCnt, pCfg5562->colsCnt );

		RollingR pRolling;
		pRolling.RollingNoiseFit1(baseTempBuffer1,(unsigned char)pCfg5562->rowsCnt, (unsigned char)pCfg5562->colsCnt);

		ReShappingData</*unsigned*/ short>( diff_dataMatrix, (/*unsigned*/ short*)baseTempBuffer1, G_XMLConfig->real_channel_num * 2, pCfg5562->rowsCnt, pCfg5562->colsCnt );

		MatrixInvalidSet<short, MAX_MCAP_ROW, MAX_MCAP_COL>(diff_dataMatrix, pCfg5562->tmp_invalid_node, MAX_MCAP_ROW, MAX_MCAP_COL, 0);

		str = StrFormat("\r\nfinal_diff_%d_mcapdata:\r\n",i+1);
		textTemp+=str;

		NodeVal nodeOutRange;
		bool bResult = WTmpDiffAnalyzeTestResultJudge<short, MAX_MCAP_ROW,MAX_MCAP_COL>(diff_dataMatrix, pCfg5562->rowsCnt, pCfg5562->colsCnt, pCfg5562->wbase_node33_diff_max, pCfg5562->wbase_node33_num_max,
			pCfg5562->wbase_all_diff_max, pCfg5562->wbase_all_num_max, textTemp, nodeOutRange, isCsv);
		if (!bResult)
		{
			failerCount++;
			LPCTSTR strHead = _T("\r\n//========= Out of Threshold in Wbase Test: \r\n");
			PrintBaseNodeValue( textTemp, &nodeOutRange, strHead );
		}

		if ((failerCount == 0))
		{
			memcpy((unsigned char*)&writeBuffer[sizeof(raw_flash_info)+(i * iRawDataLen)],(unsigned char*)baseTempBuffer,iRawDataLen);
			unsigned int chk = caculate_check_sum_u32((unsigned int*)baseTempBuffer, iRawDataLen);
			tmp_data->chk[i] = chk;
			tmp_data->chkAll += chk;
		
		}
	}

	TestResultInfo( textTemp );

	if ((failerCount == 0))
	{
		tmp_data->chkCfgCdsp = caculate_check_sum_u32((unsigned int*)&pCfg5562->cfgBinBuffer[CFG_CDSP_OFFSET], CFG_CDSP_SIZE);
		tmp_data->chkHead = 0 - caculate_check_sum_u32((unsigned int*)tmp_data, sizeof(raw_flash_info));
		memcpy((unsigned char*)&writeBuffer[sizeof(raw_flash_info)+(pCfg5562->tmp_num * iRawDataLen)],(unsigned char*)pCfg5562->cfgBinBuffer,pCfg5562->cfgBinSize);

		iReCode = SM_ChipBase(m_deviceNo)->WriteBurnSpace( USR_ROM_FACTORY_START, writeBuffer, sizeof(writeBuffer), OTP_W_CHK | TLK_DATACHK_EX1);
		if( iReCode != ERROR_CODE_OK )
		{
			TestResultInfoR("\r\nWrite base data fail!!!");
			return itemNotify.UpdateItemResult( ITEM_STA_FAIL, GetErrorMessage( iReCode ) );
		}

		iReCode = SM_ChipBase(m_deviceNo)->ReadBurnSpace( USR_ROM_FACTORY_START, readBuffer, sizeof(readBuffer));
		if( iReCode != ERROR_CODE_OK )
		{
			TestResultInfoR("\r\nRead base data fail!!!");
			return itemNotify.UpdateItemResult( ITEM_STA_FAIL, GetErrorMessage( iReCode ) );
		}

		tmp_data = (raw_flash_info*)&readBuffer[0];

		for (int i=0; i<sizeof(readBuffer); i++)
		{
			if (readBuffer[i] != writeBuffer[i])
			{
				TestResultInfoR("\r\nCheck base data fail!!!");
				failerCount++;

				break;
			}

		}
	}

	iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_CTP_RST );
	if( iReCode != ERROR_CODE_OK ) itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	SysDelay( 200 );

	iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand(CMD_CTP_FREQ,0x0c,2);
	if( iReCode != ERROR_CODE_OK )
	{
		TestResultInfoR("\r\nIC check base data fail!!!");

		iReCode = SM_ChipBase(m_deviceNo)->EraseBurnSpace( USR_ROM_FACTORY_START, 4 * 1024);
		if( iReCode != ERROR_CODE_OK )
		{
			TestResultInfoR("\r\nErase base data fail!!!");
		}

		failerCount++;
	}

	if( failerCount )
	{
		itemNotify.UpdateItemResult( ITEM_STA_FAIL );
		TestResultInfo( "\r\n\r\n//WBaseData Test is Fail\r\n", ITEM_STA_FAIL );
	}
	else
	{
		itemNotify.UpdateItemResult( ITEM_STA_PASS );
		TestResultInfo( "\r\n\r\n//WBaseData Test is Pass\r\n", ITEM_STA_PASS );
	}

	return itemNotify;

}

//unsigned int CTest5562::WBase_Test(NativeTestItem& itemQuote)
//{
//	int failerCount = 0;
//	unsigned short retBuffer[16];
//	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
//	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );
//	short baseTempBuffer[MAX_MCAP_CHANNEL * 2] = {0};
//	short mcap_dataMatrix[MAX_MCAP_ROW][MAX_MCAP_COL];
//	short scap_dataMatrix[MAX_MCAP_ROW][MAX_MCAP_COL];
//
//	short fast_dataMatrix[MAX_MCAP_ROW][MAX_MCAP_COL];
//	short slow_dataMatrix[MAX_MCAP_ROW][MAX_MCAP_COL];
//
//	const unsigned short (*tmp_base[8])[MAX_MCAP_COL]={pCfg5562->tmp_1_mcapdata, pCfg5562->tmp_2_mcapdata, pCfg5562->tmp_3_mcapdata, pCfg5562->tmp_4_mcapdata, pCfg5562->tmp_5_mcapdata, pCfg5562->tmp_6_mcapdata, pCfg5562->tmp_7_mcapdata, pCfg5562->tmp_8_mcapdata};
//
//	const unsigned int iRetry = 10;
//
//	const unsigned int iRawDataLen = ((pCfg5562->rowsCnt * pCfg5562->colsCnt + pCfg5562->rowsCnt + pCfg5562->colsCnt) * 2 + 3) & 0xfffffffc;
//	const unsigned int iScapRawDataLen = pCfg5562->rowsCnt + pCfg5562->colsCnt;
//
//	unsigned char writeBuffer[20*1024] = {0};
//	memset(writeBuffer,0xff,sizeof(writeBuffer));//必须初始化成0xff
//
//	unsigned char readBuffer[20*1024] = {0};
//	memset(readBuffer,0xff,sizeof(readBuffer));//必须初始化成0xff
//
//	short diff_dataMatrix[MAX_MCAP_ROW][MAX_MCAP_COL];
//
//	raw_flash_info* tmp_data;
//	tmp_data = (raw_flash_info*)&writeBuffer[0];
//
//	TestResultInfo( _T("\r\n------------------------------WBase Data Test------------------------------\r\n") );
//
//	if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
//	ISMChip5562* iChip5562 = (ISMChip5562*)SM_ChipBase(m_deviceNo);
//
//	int addRow = ( pCfg5562->real_channel_num - pCfg5562->va_channel_num ) ? 1 : 0;
//
//	int ref_channel_num = min(pCfg5562->real_channel_num - pCfg5562->va_channel_num, pCfg5562->colsCnt);
//	AnalyzeInfo info( pCfg5562->rowsCnt, pCfg5562->colsCnt );
//	unsigned short maxCols[] = { pCfg5562->colsCnt, pCfg5562->rowsCnt };
//
//	ColorText textTemp;
//
//	tmp_data->sig = FLASH_SAVE_SIG;
//	tmp_data->sizeHead = sizeof(raw_flash_info);
//	tmp_data->cnt = 1;
//	tmp_data->version = 1;
//	tmp_data->type = 0;
//	tmp_data->lenSingle = iRawDataLen;
//	tmp_data->lenTotal = sizeof(raw_flash_info) + iRawDataLen * pCfg5562->tmp_num;
//	tmp_data->head2En = 0;
//	tmp_data->chkHead = 0;
//	tmp_data->chkAll = 0;
//
//	SYSTEMTIME SysTime;
//	::GetLocalTime(&SysTime);
//	tmp_data->time = (SysTime.wMonth << 22) + (SysTime.wDay << 17) + (SysTime.wHour << 12) + (SysTime.wMinute << 6) + SysTime.wSecond;
//
//
//	iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_CTP_RST );
//	if( iReCode != ERROR_CODE_OK ) itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
//	SysDelay( 200 );
//
//	iReCode = iChip5562->SwitchMode( MODE_RAWDATA, iRawDataLen );
//	if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
//
//	for(int i = 0; i < 8; i++)
//	{
//		if (i < pCfg5562->tmp_num)
//		{ 
//			iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand(CMD_CTP_FREQ,0x15,i + 1, 20);
//			if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
//
//			for (int k=0; k<100; k++)
//			{
//				SysDelay(20);
//				iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand(CMD_CTP_FREQ,0x15,100, 0,(unsigned char*)retBuffer);
//				if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
//				unsigned short d0 = retBuffer[1];
//				if(1 == d0)
//				{
//					break;
//
//				}else if(0 == d0)
//				{
//					TestResultInfoR("\r\nGet fast freq data fail!!!");
//					return itemNotify.UpdateItemResult( ITEM_STA_FAIL);
//				}
//				if (k > 30)
//				{
//					TestResultInfoR("\r\nGet fast freq data timeout!!!");
//					return itemNotify.UpdateItemResult( ITEM_STA_FAIL);
//				}
//
//			}
//
//			iReCode = iChip5562->GetFwData((short*)baseTempBuffer, iRawDataLen );
//			if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
//
//		}
//		else
//		{
//			memset(baseTempBuffer,0,sizeof(baseTempBuffer));
//			break;
//		}
//
//		auto str = StrFormat("\r\ntmp_%d_mcapdata:\r\n",i+1);
//		textTemp+=str;
//
//		ReShappingData</*unsigned*/ short>( mcap_dataMatrix, (/*unsigned*/ short*)baseTempBuffer, G_XMLConfig->real_channel_num * 2, pCfg5562->rowsCnt, pCfg5562->colsCnt );
//
//		PrintMaxtrixValue<short, MAX_MCAP_ROW, MAX_MCAP_COL >( textTemp, mcap_dataMatrix, info, true );
//		//bool bResult = AnalyzeTestResult( mcap_dataMatrix, pCfg5562->tmp_rawdata_min, pCfg5562->tmp_rawdata_max, pCfg5562->invalid_node, info, textTemp, nodeOutRange, true );
//
//		str = StrFormat("\r\ntmp_%d_scapdata:\r\n",i+1);
//		textTemp+=str;
//		ReShappingData</*unsigned*/ short>( scap_dataMatrix, (/*unsigned*/ short*)baseTempBuffer + pCfg5562->rowsCnt * pCfg5562->colsCnt, iScapRawDataLen, 2, maxCols );
//		PrintScapData( textTemp, scap_dataMatrix,pCfg5562->tmp_invalid_node, info, true );
//
//		memcpy((unsigned char*)&writeBuffer[sizeof(raw_flash_info)+(i * iRawDataLen)],(unsigned char*)baseTempBuffer,iRawDataLen);
//		unsigned int chk = caculate_check_sum_u32((unsigned int*)baseTempBuffer, iRawDataLen);
//		tmp_data->chk[i] = chk;
//		tmp_data->chkAll += chk;
//		
//		if(i == pCfg5562->wbase_fast)
//		{
//			ReShappingData</*unsigned*/ short>( fast_dataMatrix, (/*unsigned*/ short*)baseTempBuffer, G_XMLConfig->real_channel_num * 2, pCfg5562->rowsCnt, pCfg5562->colsCnt );
//		}
//		if(i == pCfg5562->wbase_slow)
//		{
//			ReShappingData</*unsigned*/ short>( slow_dataMatrix, (/*unsigned*/ short*)baseTempBuffer, G_XMLConfig->real_channel_num * 2, pCfg5562->rowsCnt, pCfg5562->colsCnt );
//		}
//	}
//
//	MatrixMultiplication<short, short,float, MAX_MCAP_ROW, MAX_MCAP_COL>(slow_dataMatrix,slow_dataMatrix,pCfg5562->fator_HL,pCfg5562->rowsCnt,pCfg5562->colsCnt);
//
//	textTemp += _T("\r\nslow_hl:\r\n");
//	PrintMaxtrixValue<short, MAX_MCAP_ROW, MAX_MCAP_COL >( textTemp, slow_dataMatrix,pCfg5562->tmp_invalid_node, info, true );
//
//	TestResultInfo( textTemp );
//
//	tmp_diff<short, short, short, MAX_MCAP_ROW,MAX_MCAP_COL>(diff_dataMatrix,fast_dataMatrix,slow_dataMatrix,pCfg5562->rowsCnt, pCfg5562->colsCnt,pCfg5562->tmp_invalid_node);
//
//	textTemp = _T("\r\ndiff fast-slow_hl:\r\n");
//
//	NodeVal nodeOutRange;
//	bool bResult = WTmpDiffAnalyzeTestResult<short, MAX_MCAP_ROW,MAX_MCAP_COL>(diff_dataMatrix, pCfg5562->rowsCnt, pCfg5562->colsCnt, pCfg5562->wbase_node33_diff_max, pCfg5562->wbase_node33_num_max,
//		//pCfg5562->wbase_node55_diff_max, pCfg5562->wbase_node55_num_max,
//		pCfg5562->wbase_all_diff_max, pCfg5562->wbase_all_num_max, textTemp, nodeOutRange);
//;
//	if (!bResult)
//	{
//		failerCount++;
//		LPCTSTR strHead = _T("\r\n//========= Out of Threshold in Wbase Test: \r\n");
//		PrintBaseNodeValue( textTemp, &nodeOutRange, strHead );
//	}
//	TestResultInfo( textTemp );
//
//
//	if ((failerCount == 0))
//	{
//		tmp_data->chkCfgCdsp = caculate_check_sum_u32((unsigned int*)&pCfg5562->cfgBinBuffer[CFG_CDSP_OFFSET], CFG_CDSP_SIZE);
//		tmp_data->chkHead = 0 - caculate_check_sum_u32((unsigned int*)tmp_data, sizeof(raw_flash_info));
//		memcpy((unsigned char*)&writeBuffer[sizeof(raw_flash_info)+(pCfg5562->tmp_num * iRawDataLen)],(unsigned char*)pCfg5562->cfgBinBuffer,pCfg5562->cfgBinSize);
//
//		iReCode = SM_ChipBase(m_deviceNo)->WriteBurnSpace( USR_ROM_FACTORY_START, writeBuffer, sizeof(writeBuffer), OTP_W_CHK | TLK_DATACHK_EX1);
// 		if( iReCode != ERROR_CODE_OK )
//		{
//			TestResultInfoR("\r\nWrite base data fail!!!");
//			return itemNotify.UpdateItemResult( ITEM_STA_FAIL, GetErrorMessage( iReCode ) );
//		}
//
//		iReCode = SM_ChipBase(m_deviceNo)->ReadBurnSpace( USR_ROM_FACTORY_START, readBuffer, sizeof(readBuffer));
//		if( iReCode != ERROR_CODE_OK )
//		{
//			TestResultInfoR("\r\nRead base data fail!!!");
//			return itemNotify.UpdateItemResult( ITEM_STA_FAIL, GetErrorMessage( iReCode ) );
//		}
//
//		tmp_data = (raw_flash_info*)&readBuffer[0];
//
//		for (int i=0; i<sizeof(readBuffer); i++)
//		{
//			if (readBuffer[i] != writeBuffer[i])
//			{
//				TestResultInfoR("\r\nCheck base data fail!!!");
//				failerCount++;
//
//				break;
//			}
//
//		}
//	}
//
//	iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_CTP_RST );
//	if( iReCode != ERROR_CODE_OK ) itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
//	SysDelay( 200 );
//
//	iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand(CMD_CTP_FREQ,0x0c,2);
//	if( iReCode != ERROR_CODE_OK )
//	{
//		TestResultInfoR("\r\nIC check base data fail!!!");
//
//		iReCode = SM_ChipBase(m_deviceNo)->EraseBurnSpace( USR_ROM_FACTORY_START, 4 * 1024);
//		if( iReCode != ERROR_CODE_OK )
//		{
//			TestResultInfoR("\r\nErase base data fail!!!");
//		}
//
//		failerCount++;
//	}
//
//	if( failerCount )
//	{
//		itemNotify.UpdateItemResult( ITEM_STA_FAIL );
//		TestResultInfo( "\r\n\r\n//WBaseData Test is Fail\r\n", ITEM_STA_FAIL );
//	}
//	else
//	{
//		itemNotify.UpdateItemResult( ITEM_STA_PASS );
//		TestResultInfo( "\r\n\r\n//WBaseData Test is Pass\r\n", ITEM_STA_PASS );
//	}
//
//	return itemNotify;
//
//}
