#include "checksum.h"
#include "Test7449.h"
#include "../Config/Config7449.h"

#include <list>
//#include <numeric>

extern CConfig* G_XMLConfig;
#define pCfg7449   (( const CConfig7449*)G_XMLConfig)
REGIST_RUNTIME_CLASS(TEST_TYPE, (TEST_TYPE)SEMI_IC_7449, CTest7449)

typedef CTest7449 CTest7438;
REGIST_RUNTIME_CLASS(TEST_TYPE, (TEST_TYPE)SEMI_IC_7438, CTest7438)

typedef CTest7449 CTest7448;
REGIST_RUNTIME_CLASS(TEST_TYPE, (TEST_TYPE)SEMI_IC_7448, CTest7448)

typedef CTest7449 CTest7464;
REGIST_RUNTIME_CLASS(TEST_TYPE, (TEST_TYPE)SEMI_IC_7464, CTest7464)

// typedef CTest7449 CTest5448;
// REGIST_RUNTIME_CLASS(TEST_TYPE, (TEST_TYPE)SEMI_IC_5448, CTest5448)


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

CTest7449::CTest7449()
:CTestBase()
{
// 	memset( m_CurTestItemAddr, 0, sizeof(m_CurTestItemAddr) );
// 	m_CurTestItemAddr[TEST_ITEM_MTK_CONNECT]     = new CRunTimeMethod<CTestBase>( this, &CTestBase::MTKConnectTest );
// 	m_CurTestItemAddr[TEST_ITEM_TP_WAIT]         = new CRunTimeMethod<CTestBase>( this, &CTestBase::TP_WaitTest );
// 	m_CurTestItemAddr[TEST_ITEM_TP_REMOVE]       = new CRunTimeMethod<CTestBase>( this, &CTestBase::TP_RemoveTest );
// 	m_CurTestItemAddr[TEST_ITEM_INT_TEST]        = new CRunTimeMethod<CTest7449>( this, &CTest7449::INT_Test );
// 	m_CurTestItemAddr[TEST_ITEM_RESET_TEST]      = new CRunTimeMethod<CTest7449>( this, &CTest7449::Reset_Test );
// 	m_CurTestItemAddr[TEST_ITEM_FSD_TEST_7449]   = new CRunTimeMethod<CTest7449>( this, &CTest7449::FSD_Test );
// 	m_CurTestItemAddr[TEST_ITEM_OS_TEST_7449]    = new CRunTimeMethod<CTest7449>( this, &CTest7449::OS_Test );
// 	m_CurTestItemAddr[TEST_ITEM_BOOT_TEST]       = new CRunTimeMethod<CTest7449>( this, &CTest7449::Boot_Test );
// 	m_CurTestItemAddr[TEST_ITEM_CFG_TEST]        = new CRunTimeMethod<CTest7449>( this, &CTest7449::Config_Test );
// 	m_CurTestItemAddr[TEST_ITEM_BUTTON_TEST]     = new CRunTimeMethod<CTest7449>( this, &CTestBase::Graph_Test );
// 	m_CurTestItemAddr[TEST_ITEM_LINEARLY_TEST]   = new CRunTimeMethod<CTest7449>( this, &CTestBase::Graph_Test );
// 	m_CurTestItemAddr[TEST_ITEM_FREE_PAINT_TEST] = new CRunTimeMethod<CTest7449>( this, &CTestBase::Graph_Test );
// 	m_CurTestItemAddr[TEST_ITEM_CURRENT_TEST]    = new CRunTimeMethod<CTest7449>( this, &CTest7449::Current_Test );
}
CTest7449::~CTest7449()
{
	
}
void CTest7449::SetTestContext( unsigned char deviceNo, NativeTestInterface* native )
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
		info.bSelected = pCfg7449->mtk_selected;
		info.jumpIfNG = false;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTestBase>( this, &CTestBase::MTKConnectTest );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_TP_WAIT;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("Waiting"), lengthof(_T("Waiting")));
		info.bSelected = pCfg7449->way_to_start == START_BY_AUTO;
		info.jumpIfNG = false;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTestBase>( this, &CTestBase::TP_WaitTest );
	}

	//////////////////////////////////////////////////////////////////////////
	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_FRT_TEST_7449;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("FRT"), lengthof(_T("FRT")));
		info.bSelected = pCfg7449->frt_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest7449>( this, &CTest7449::FRT_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_BOOT_TEST;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("Boot"), lengthof(_T("Boot")));
		info.bSelected = pCfg7449->boot_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest7449>( this, &CTest7449::Boot_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_CFG_TEST;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("Config"), lengthof(_T("Config")));
		info.bSelected = pCfg7449->config_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest7449>( this, &CTest7449::Config_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_OSCTRIM_TEST_7449;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("OSCTrim"), lengthof(_T("OSCTrim")));
		info.bSelected = pCfg7449->osctrim_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest7449>( this, &CTest7449::OSCTrim_Test );
	}
	
	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_OS_TEST_7449;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("Short"), lengthof(_T("Short")));
		info.bSelected = pCfg7449->short_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest7449>( this, &CTest7449::Short_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_MISC_TEST_7449;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("MISC"), lengthof(_T("MISC")));
		info.bSelected = pCfg7449->misc_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest7449>( this, &CTest7449::MISC_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_IOVOL_TEST_7449;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("IOVoltage"), lengthof(_T("IOVoltage")));
		info.bSelected = pCfg7449->iovol_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest7449>( this, &CTest7449::IOVoltage_Test );

	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_INT_TEST;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("INT"), lengthof(_T("INT")));
		info.bSelected = pCfg7449->int_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest7449>( this, &CTest7449::INT_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_ENPIN_TEST_7449;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("EnPin"), lengthof(_T("EnPin")));
		info.bSelected = pCfg7449->enpin_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest7449>( this, &CTest7449::EnPin_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_PROJECT_CODE;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("Project"), lengthof(_T("Project")));
		info.bSelected = platform_required_sel;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest7449>( this, &CTest7449::ProjectCode_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_RESET_TEST;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("Reset"), lengthof(_T("Reset")));
		info.bSelected = pCfg7449->reset_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest7449>( this, &CTest7449::Reset_Test );
	}



	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_CURRENT_TEST;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("Current"), lengthof(_T("Current")));
		info.bSelected = pCfg7449->current_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest7449>( this, &CTest7449::Current_Test );
	}


	//{
	//	InternalItemInfo& info = m_arrayItemInfo[indexSel++];
	//	info.item.ucDevice = m_deviceNo;
	//	info.item.testCode = TEST_ITEM_BASE_TEST_7449;
	//	info.item.testResult = ITEM_STA_NONE;
	//	copytextto(info.item.testName, _T("Base"), lengthof(_T("Base")));
	//	info.bSelected = pCfg7449->base_selected;
	//	if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest7449>( this, &CTest7449::Base_Test );
	//}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_SCAP_RAWDATA_TEST_7449;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("ScapData"), lengthof(_T("ScapData")));
		info.bSelected = pCfg7449->scap_rawdata_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest7449>( this, &CTest7449::ScapRawData_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_STC_7449;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("STC"), lengthof(_T("STC")));
		info.bSelected = pCfg7449->stc_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest7449>( this, &CTest7449::STC_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_MCAP_RAWDATA_7449;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("McapData"), lengthof(_T("McapData")));
		info.bSelected = pCfg7449->mcap_rawdata_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest7449>( this, &CTest7449::MCapRawData_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_NOISE_TEST_7449;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("Noise"), lengthof(_T("Noise")));
		info.bSelected = pCfg7449->noise_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest7449>( this, &CTest7449::Noise_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_VT_TEST_7449;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("VT"), lengthof(_T("VT")));
		info.bSelected = pCfg7449->vt_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest7449>( this, &CTest7449::VT_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_BASE_TEST_7449;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("Base"), lengthof(_T("Base")));
		info.bSelected = pCfg7449->base_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest7449>( this, &CTest7449::Base_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_BUTTON_TEST;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("Button"), lengthof(_T("Button")));
		info.bSelected = pCfg7449->button_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest7449>( this, &CTest7449::Graph_Test );
	}

	{
		if (pCfg7449->boot_exist_bootloader == 0x01)
		{
			InternalItemInfo& info = m_arrayItemInfo[indexSel++];
			info.item.ucDevice = m_deviceNo;
			info.item.testCode = TEST_ITEM_LINEARLY_TPAD_TEST;
			info.item.testResult = ITEM_STA_NONE;
			copytextto(info.item.testName, _T("Linearly"), lengthof(_T("Linearly")));
			info.bSelected = pCfg7449->LINEARITY_TEST;
			if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest7449>( this, &CTest7449::Graph_Test );
		
		}
		else
		{
			InternalItemInfo& info = m_arrayItemInfo[indexSel++];
			info.item.ucDevice = m_deviceNo;
			info.item.testCode = TEST_ITEM_LINEARLY_TEST;
			info.item.testResult = ITEM_STA_NONE;
			copytextto(info.item.testName, _T("Linearly"), lengthof(_T("Linearly")));
			info.bSelected = pCfg7449->LINEARITY_TEST;
			if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest7449>( this, &CTest7449::Graph_Test );
		
		}

	}

    {
        if (pCfg7449->boot_exist_bootloader != 0x01)
        {
            InternalItemInfo& info = m_arrayItemInfo[indexSel++];
            info.item.ucDevice = m_deviceNo;
            info.item.testCode = TEST_ITEM_EXP_LINEARLY_TEST;
            info.item.testResult = ITEM_STA_NONE;
            copytextto(info.item.testName, _T("ExpLinearly"), lengthof(_T("ExpLinearly")));
            info.bSelected = pCfg7449->EXP_LINEARITY_TEST;
            if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest7449>( this, &CTest7449::Graph_Test );
        }
    }

    {
        InternalItemInfo& info = m_arrayItemInfo[indexSel++];
        info.item.ucDevice = m_deviceNo;
        info.item.testCode = TEST_ITEM_FREE_PAINT_TEST;
        info.item.testResult = ITEM_STA_NONE;
        copytextto(info.item.testName, _T("FreePaint"), lengthof(_T("FreePaint")));
        info.bSelected = pCfg7449->FREEPAINT_TEST;
        if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest7449>( this, &CTest7449::Graph_Test );
    }

    //////////////////////////////////////////////////////////////////////////
	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_TP_REMOVE;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("Removing"), lengthof(_T("Removing")));
		info.bSelected = pCfg7449->way_to_start == START_BY_AUTO || pCfg7449->way_to_start == START_BY_SN;
		info.jumpIfNG = false;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest7449>( this, &CTest7449::TP_RemoveTest );
	}

	if( SM_ChipBase(m_deviceNo) )
	{
		CtpHalCfg halCfg;
		halCfg.protocalType = (unsigned char)pCfg7449->protocalType;
		halCfg.speed = pCfg7449->Speed;
		halCfg.IIC.slaveAddr = pCfg7449->I2cAddr;
		halCfg.vddVoltage = pCfg7449->vddVotage;
		halCfg.iovddVotage = pCfg7449->ioVddVotage;
		halCfg.icType = pCfg7449->IcType;
		SM_ChipBase(m_deviceNo)->SetCommContext( halCfg );
	}

	ActionToXmlConfig();
}
void CTest7449::ICArrayToSensorMatrix( unsigned short (&dataMappinged)[2][MAX_MCAP_COL], unsigned short* const dataToMapping, unsigned int dataCnt, unsigned short maxRows, unsigned short* pMaxCols )
{
	for( int iTx = 0; iTx < pCfg7449->colsCnt; iTx++ )
	{
		unsigned short icChannel = pCfg7449->sensor_2_ic_map[iTx];
		dataMappinged[0][iTx] = dataToMapping[icChannel];
	}
	for( int iRx = 0; iRx < pCfg7449->rowsCnt; iRx++ )
	{
		unsigned short icChannel = pCfg7449->sensor_2_ic_map[iRx + MAX_TX_NUM_7449];
		dataMappinged[1][iRx] = dataToMapping[icChannel + MAX_TX_NUM_7449];
	}
}
// void CTest7449::ICArrayToSensorMatrix( unsigned short (&dataMappinged)[MAX_MCAP_ROW][MAX_MCAP_COL], unsigned short* const dataToMapping, unsigned int dataCnt, unsigned short maxRows, unsigned short maxCols )
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
// 			int icPosition = pCfg7449->sensor_2_ic_map[index];
// 			dataMappinged[iRow][iCol] = dataToMapping[icPosition];
// 		}
// 	}
// 	for( int index = (int)maxRows * maxCols; index < (int)dataCnt; index++ )
// 	{
// 		int iCol = index - maxRows * maxCols + maxCols;
// 		int icPosition = pCfg7449->sensor_2_ic_map[index];
// 		dataMappinged[maxRows - 1][iCol] = dataToMapping[icPosition];
// 	}
// }
// void CTest7449::ICMatrixToSensorMatrix( unsigned short (&dataMappinged)[MAX_MCAP_ROW][MAX_MCAP_COL],
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
// 			if( index >= (int)pCfg7449->real_channel_num )   continue;
// 
// 			int icPosition = pCfg7449->sensor_2_ic_map[index];
// 			int icRow = icPosition / mappingCol;
// 			int icCol = icPosition % mappingCol;
// 
// 			dataMappinged[iRow][iCol] = dataToMapping[icRow][icCol];
// 		}
// 	}
// }
// void CTest7449::SensorMatrixToIcMatrix( unsigned short (&dataMappinged)[MAX_MCAP_ROW][MAX_MCAP_COL],
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
// // 		    int sensorPos = pCfg7449->ic_2_sensor_map[index] - 1;
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
// 			if( index >= (int)pCfg7449->real_channel_num )   continue;
// 
// 			int icPosition = pCfg7449->sensor_2_ic_map[index];
// 			int icRow = icPosition / mappedCol;
// 			int icCol = icPosition % mappedCol;
// 
// 			dataMappinged[icRow][icCol] = dataToMapping[iRow][iCol];
// 		}
// 	}
// }
BOOL CTest7449::CheckTpBootSame( )
{
	BOOL bCheckBootOk = FALSE;
	unsigned int iReCode = ERROR_CODE_OK;
	ISMChip7449* iChip7449 = (ISMChip7449*)SM_ChipBase(m_deviceNo);
	if( NULL == iChip7449 )   return FALSE;

	unsigned int crc_from_tp = 0, otm_time = 0;
	iReCode = iChip7449->GetBootCheckSum( &crc_from_tp, &otm_time );
	if( iReCode != ERROR_CODE_OK )  return FALSE;

	TestResultInfoR( _T("ID = 0x%x,   %d-%d, %d:%d:%d"), otm_time, (otm_time>>22)&0xf, (otm_time>>17)&0x1f,(otm_time>>12)&0x1f, (otm_time>>6)&0x3f, otm_time&0x3f );
	if( crc_from_tp == pCfg7449->boot_check_sum )
		return TRUE;

	return FALSE;
}
BOOL CTest7449::CheckFlashEraseOk()
{
	unsigned int iReCode = ERROR_CODE_OK;
	ISMChip7449* iChip7449 = (ISMChip7449*)SM_ChipBase(m_deviceNo);
	if( NULL == iChip7449 )  return FALSE;

	unsigned char readBuffer[4096] = {0};
	unsigned int writeData = 0x5ee5e55e, readData = 0x00000000;
	iReCode = iChip7449->WriteBurnSpace( 0xd000, (const unsigned char*)&writeData, sizeof(writeData), OTP_W_CHK | TLK_DATACHK_EX1 );
	if( iReCode != ERROR_CODE_OK ) return FALSE;

	iReCode = iChip7449->ReadBurnSpace( 0xd000, (unsigned char*)&readData, sizeof(writeData) );
	if( iReCode != ERROR_CODE_OK ) return FALSE;

	if( writeData != readData )
	{
		TestResultInfo( _T("Check Erase Falsh step 1 Failed\r\n") );
		return FALSE;
	}

	writeData = 0xe55e5ee5, readData = 0x00000000;
	iReCode = iChip7449->WriteBurnSpace( 0xd000, (const unsigned char*)&writeData, sizeof(writeData), OTP_W_CHK | TLK_DATACHK_EX1 );
	if( iReCode != ERROR_CODE_OK ) return FALSE;

	iReCode = iChip7449->ReadBurnSpace( 0xd000, (unsigned char*)&readData, sizeof(writeData) );
	if( iReCode != ERROR_CODE_OK ) return FALSE;

	if( writeData != readData )
	{
		TestResultInfo( _T("Check Erase Falsh step 2 Failed\r\n") );
		return false;
	}

	writeData = 0xffffffff;
	iReCode = iChip7449->WriteBurnSpace( 0xd000, (const unsigned char*)&writeData, sizeof(writeData), OTP_W_CHK | TLK_DATACHK_EX1 );
	if( iReCode != ERROR_CODE_OK ) return FALSE;

	iReCode = iChip7449->ReadBurnSpace( 0xd000, readBuffer, sizeof(readBuffer) );
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
	iReCode = iChip7449->ReadBurnSpace( 0xc000, readBuffer, 8 );
	if( iReCode != ERROR_CODE_OK ) return FALSE;

	UINT32* pIntData = (UINT32*)readBuffer;
	if( 0xffffffff == pIntData[0] && 0xffffffff == pIntData[1] )
	{
		SYSTEMTIME SysTime;
		::GetLocalTime(&SysTime);
		pIntData[0] = (SysTime.wMonth << 22) + (SysTime.wDay << 17) + (SysTime.wHour << 12) + (SysTime.wMinute << 6) + SysTime.wSecond;
		pIntData[1] = GetTickCount();
		iChip7449->WriteBurnSpace( 0xc000, readBuffer, 8, OTP_W_CHK | TLK_DATACHK_EX1 );
		if( iReCode != ERROR_CODE_OK ) return FALSE;
		
		SysDelay( 10 );
	}

	m_stOneRecord.ReleaseID = *(UINT64*)readBuffer;

	UINT32 otm_time = *(UINT32*)&m_stOneRecord.ReleaseID;
	TestResultInfoR( _T("ICID = 0x%llx,   %d-%d, %d:%d:%d\r\n"), m_stOneRecord.ReleaseID, (otm_time>>22)&0xf, (otm_time>>17)&0x1f,(otm_time>>12)&0x1f, (otm_time>>6)&0x3f, otm_time&0x3f );

	return TRUE;
}
unsigned int CTest7449::Boot_Test( NativeTestItem& itemQuote )
{
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );

	TestResultInfo( _T("\r\n------------------------------BOOT Test------------------------------\r\n") );

	ISMChip7449* iChip7449 = (ISMChip7449*)SM_ChipBase(m_deviceNo);
	if( NULL == iChip7449 )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

// 	if( !CheckFlashEraseOk() )
// 	{
// 		TestResultInfo( _T("Check Erase Falsh Failed\r\n") );
// 		return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( ERROR_CODE_CHECK_SUM_MISMATCH ) );
// 	}

	unsigned short booVerFromTp = 0;
	if (pCfg7449->boot_exist_bootloader == 0x01)
	{
		iReCode = iChip7449->GetNewBootVersion( &booVerFromTp,0x2000);
	} 
	else
	{
		iReCode = iChip7449->GetNewBootVersion( &booVerFromTp,0x0);
	}
		
	if( ERROR_CODE_OK != iReCode )  return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	BOOL bSameBoot = CheckTpBootSame();

	//wasim
	//bSameBoot = FALSE;

	if( bSameBoot )
	{	
		TestResultInfo( _T("\r\nBoot from tp is same with Boot from setting\r\n") );
		auto szBootVer = TestResultInfoR( _T("Ver=0x%x,Set=0x%x"), booVerFromTp, pCfg7449->version_set);
		if (booVerFromTp == pCfg7449->version_set)
		{
			TestResultInfo( "\r\n\r\n//BOOT Test is Pass\r\n", ITEM_STA_PASS );
			itemNotify.UpdateItemResult( ITEM_STA_PASS, szBootVer );
		} 
		else
		{
			TestResultInfo( "\r\n\r\n//BOOT Test is Fail\r\n", ITEM_STA_FAIL );
			itemNotify.UpdateItemResult( ITEM_STA_FAIL, szBootVer );
		}

	}
	else
	{
		if( pCfg7449->boot_only_check )
		{
			TestResultInfo( _T("\r\nBoot from tp is differant from setting\r\n") );
			auto szBootVer = TestResultInfoR( _T("Ver=0x%x,Set=0x%x"), booVerFromTp, pCfg7449->version_set);
			TestResultInfo( "\r\n\r\n//BOOT Test is Fail\r\n", ITEM_STA_FAIL );
			itemNotify.UpdateItemResult( ITEM_STA_FAIL, szBootVer );
		}
		else
		{
			//SM_CommBase(m_deviceNo)->SetIoVoltage(0x6E, pCfg7449->vddVotage == pCfg7449->ioVddVotage ? 0x6E : pCfg7449->ioVddVotage);
			//SysDelay(50);

			TestResultInfo( _T("\r\nDownlad new boot bin...\r\n") );
			iReCode = iChip7449->BurnBootBin( pCfg7449->bootBinSize, pCfg7449->boot_svn, m_stOneRecord.Mcap.oscTrim );
			if( iReCode == ERROR_CODE_OK )   
			{
				/*unsigned short */booVerFromTp = 0;
				if (pCfg7449->boot_exist_bootloader == 0x01)
				{
					iReCode = iChip7449->GetNewBootVersion( &booVerFromTp,0x2000);
				} 
				else
				{
					iReCode = iChip7449->GetNewBootVersion( &booVerFromTp,0x0);
				}
				if( ERROR_CODE_OK != iReCode )  return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

				BOOL bSameBoot2 = CheckTpBootSame();
				if( bSameBoot2 )
				{
					TestResultInfo( "\r\n\r\n//BOOT Test is Pass\r\n", ITEM_STA_PASS );
					auto szBootVer = TestResultInfoR( _T("NewVer=0x%x,Set=0x%x"), booVerFromTp, pCfg7449->version_set);
					if (booVerFromTp == pCfg7449->version_set)
					{
						TestResultInfo( "\r\n\r\n//BOOT Test is Pass\r\n", ITEM_STA_PASS );
						itemNotify.UpdateItemResult( ITEM_STA_PASS, szBootVer );
					} 
					else
					{
						TestResultInfo( "\r\n\r\n//BOOT Test is Fail\r\n", ITEM_STA_FAIL );
						itemNotify.UpdateItemResult( ITEM_STA_FAIL, szBootVer );
					}
				}
				else
				{
					TestResultInfo( _T("\r\nBoot from tp is differant from setting\r\n") );
					auto szBootVer = TestResultInfoR( _T("NewVer=0x%x,Set=0x%x"), booVerFromTp, pCfg7449->version_set);
					TestResultInfo( "\r\n\r\n//BOOT Test is Fail\r\n", ITEM_STA_FAIL );
					itemNotify.UpdateItemResult( ITEM_STA_FAIL, szBootVer );
				}
			}
			else
			{
				TestResultInfo( _T("\r\nDownload boot exception\r\n") );
				auto szBootVer = TestResultInfoR( _T("Ver=0x%x,Set=0x%x"), booVerFromTp, pCfg7449->version_set);
				TestResultInfo( "\r\n\r\n//BOOT Test is Fail\r\n", ITEM_STA_FAIL );
				itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
			}

			//SM_CommBase(m_deviceNo)->SetIoVoltage(pCfg7449->vddVotage, pCfg7449->ioVddVotage);
			//SysDelay(50);
		}
	}

	return itemNotify;
}
BOOL CTest7449::CheckConfigSame( const unsigned char* pCfg, unsigned short len )
{
	if( len != pCfg7449->cfgBinSize ) return FALSE;

	unsigned int iReCode = ERROR_CODE_OK;
	ISMChip7449* iChip7449 = (ISMChip7449*)SM_ChipBase(m_deviceNo);
	if( NULL == iChip7449 )   return FALSE;

	unsigned int check = caculate_check_sum_ex( pCfg, len );
	if( check != pCfg7449->config_check_sum )
	{
		return FALSE;
	}

	for( int index = 0; index < len; index++ ) 
	{
		if( pCfg[index] != pCfg7449->cfgBinBuffer[index] )
			return FALSE;
	}

	return TRUE;
}
unsigned int CTest7449::MakeTraceRecord()
{
	unsigned int iReCode = ERROR_CODE_OK;
#ifdef _MSC_VER
	ISMChip7449* iChip7449 = (ISMChip7449*)SM_ChipBase(m_deviceNo);
	unsigned char record_buffer[3*1024] = {0};
	//auto record_buffer = new unsigned char[2*1024];
	Trace_Info* traceInfo = (Trace_Info*)record_buffer;
	One_Record* record = (One_Record*)(record_buffer + sizeof(Trace_Info));
	tstring userInfo = pCfg7449->szUserRecord ? tstring(pCfg7449->szUserRecord) : _T("");
	unsigned short crc = caculate_check_sum_ex( (unsigned char*)userInfo.c_str(), userInfo.length() + 1 ) >> 16;

	iReCode = iChip7449->ReadBurnSpace( AddrMakeTraceRecord, record_buffer, sizeof(Trace_Info) );
	if(iReCode != ERROR_CODE_OK) return iReCode;

	BOOL bExitSameUserRecord = FALSE;
	if(traceInfo->trace_cnt + traceInfo->reverse == 0xff)
	{
		traceInfo->tlen =  traceInfo->tlen >= 0x800 ? 0x800 : traceInfo->tlen ;
		iReCode = iChip7449->ReadBurnSpace( AddrMakeTraceRecord + sizeof(Trace_Info), (unsigned char*)record, traceInfo->tlen );
		if(iReCode != ERROR_CODE_OK) return iReCode;

		for(int index = 0; index < traceInfo->trace_cnt; index++)
		{
			if(0 != caculate_check_sum_u16((unsigned short*)record, sizeof(One_Record))) break;

			unsigned char textOutCnt = 0;
			if(m_pNativeIntr->DebugMode())
			{
				textOutCnt++;
				TestResultInfoR( _T("0x%010llX CRC = 0x%04x, %d-%d, %d:%d:%d	"), record->vid_pid, record->sz_crc, (record->time>>22)&0xf, (record->time>>17)&0x1f, 
					(record->time>>12)&0x1f, (record->time>>6)&0x3f, record->time&0x3f );
			}

			if((record->szlen > 0) && record->szlen == align_4(lengthof((char*)(record + 1)) + 1))
			{
				textOutCnt++;
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
		record->vid_pid = pCfg7449->vid_pid;
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

		iReCode = iChip7449->WriteBurnSpace(AddrMakeTraceRecord, record_buffer, traceInfo->tlen + sizeof(Trace_Info), OTP_W_CHK | TLK_DATACHK_EX1);
		SysDelay(10);

		TestResultInfoR(_T("0x%010llX CRC = 0x%04x, %d-%d, %d:%d:%d	"), record->vid_pid, record->sz_crc, (record->time>>22)&0xf, (record->time>>17)&0x1f, 
			(record->time>>12)&0x1f, (record->time>>6)&0x3f, record->time&0x3f);

		if(record->szlen > 0)
		{
			TestResultInfoR(_T("%s"), (char*)(record + 1));
		}

		TestResultInfo( _T("\r\n") );
	}
	//delete[] record_buffer;
#endif

	return iReCode;
}
unsigned int CTest7449::ProjectCode_Test( NativeTestItem& itemQuote )
{
	unsigned int iReCode = ERROR_CODE_OK;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );

	TestResultInfo( _T("\r\n------------------------------Project Test------------------------------\r\n") );

	MakeTraceRecord();

	ISMChip7449* iChip7449 = (ISMChip7449*)SM_ChipBase(m_deviceNo);
	if( NULL == iChip7449 )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_CTP_RST );
	if( iReCode != ERROR_CODE_OK ) itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	SysDelay( 200 );

	unsigned char chipFamily = GetContainerInterface()->GetChipFamily( G_XMLConfig->IcType );
	SM_ChipBase(m_deviceNo)->IncokeCommand(CMD_CHK_CFG, 0, (chipFamily << 8) | G_XMLConfig->I2cAddr, (G_XMLConfig->Speed << 8) | G_XMLConfig->protocalType);

	iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_SWITCH_IIC );
	if( iReCode != ERROR_CODE_OK ) itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_IDENTITY );
	if( iReCode != ERROR_CODE_OK ) itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	unsigned char cfgBuffer[MAX_CFG_BIN_SIZE] = {0};
	iReCode = SM_ChipBase(m_deviceNo)->ReadCoreSpace( 0x20000000 + 0x80, (unsigned char*)cfgBuffer, pCfg7449->cfgBinSize );
	if( iReCode != ERROR_CODE_OK ) itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	TCHAR chTemp[MAX_PATH] = {0};
	unsigned short s = cfgBuffer[1];
	unsigned short p = (cfgBuffer[3] << 8) + cfgBuffer[2];
	unsigned short v = (cfgBuffer[5] << 8) + cfgBuffer[4];
	TestResultInfoR( _T("SoftWare Ver = %d, ProjectCode = %d, VenderID = %d\r\n"), s, p, v );

	transformat( chTemp, _T("S=%d, P=%d, V=%d"), s, p, v );

	if( pCfg7449->sVersion == s && pCfg7449->pVersion == p && pCfg7449->vVersion == v )
	{
		if(pCfg7449->cfgTestBinSize)
		{
			iReCode = iChip7449->SetConfigInFctMode( (unsigned char*)pCfg7449->cfgTestBinBuffer, pCfg7449->cfgTestBinSize );
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
		iReCode = iChip7449->IncokeCommand(CMD_CTP_FREQ, 3, 1);
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
unsigned int CTest7449::Config_Test( NativeTestItem& itemQuote )
{
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );

	TestResultInfo( _T("\r\n------------------------------CONFIG Test------------------------------\r\n") );

	ISMChip7449* iChip7449 = (ISMChip7449*)SM_ChipBase(m_deviceNo);
	if( NULL == iChip7449 )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	unsigned short cfgVerFromTp = 0;
	unsigned char configBuffer[MAX_CFG_BIN_SIZE] = {0};
	iReCode = iChip7449->GetFirmWareConfig( configBuffer, pCfg7449->cfgBinSize );
	if( ERROR_CODE_OK != iReCode )  return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	cfgVerFromTp = configBuffer[1];
	//TCHAR szConfigVer[MAX_PATH] = {0};
	//transformat( szConfigVer, _T("Ver=0x%x"), cfgVerFromTp );

	BOOL bSameConfig = CheckConfigSame( configBuffer, pCfg7449->cfgBinSize );

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
		if( pCfg7449->config_only_check )
		{
			TestResultInfo( _T("\r\nConfig from tp is differant from setting\r\n") );
			//TestResultInfo( szConfigVer );
			auto szConfigVer = TestResultInfoR( _T("Ver=0x%x"), cfgVerFromTp );
			TestResultInfo( "\r\n\r\n//Config Test is Fail\r\n", ITEM_STA_FAIL );
			itemNotify.UpdateItemResult( ITEM_STA_FAIL, szConfigVer );
		}
		else
		{
			//SM_CommBase(m_deviceNo)->SetIoVoltage(0x6E, pCfg7449->vddVotage == pCfg7449->ioVddVotage ? 0x6E : pCfg7449->ioVddVotage);
			//SysDelay(50);

			TestResultInfo( _T("\r\nDownlad new config bin...\r\n") );
			iReCode = iChip7449->BurnConfigBin( pCfg7449->cfgBinBuffer, pCfg7449->cfgBinSize );
			if( iReCode == ERROR_CODE_OK )   
			{
				memset( configBuffer, 0, sizeof(configBuffer) );
				iChip7449->GetFirmWareConfig( configBuffer, pCfg7449->cfgBinSize );
				BOOL bSameConfig2 = CheckConfigSame( configBuffer, pCfg7449->cfgBinSize );

				cfgVerFromTp = configBuffer[1];

				if( bSameConfig2 )
				{
					TestResultInfo( "\r\n\r\n//Config Test is Pass\r\n", ITEM_STA_PASS );
					auto szConfigVer = TestResultInfoR( _T("NewVer=0x%x"), cfgVerFromTp );
					itemNotify.UpdateItemResult( ITEM_STA_PASS, szConfigVer );
				}
				else
				{
					TestResultInfo( _T("\r\nConfig from tp is differant from setting\r\n") );
					auto szConfigVer = TestResultInfoR( _T("NewVer=0x%x"), cfgVerFromTp );
					TestResultInfo( "\r\n\r\n//Config Test is Fail\r\n", ITEM_STA_FAIL );
					itemNotify.UpdateItemResult( ITEM_STA_FAIL, szConfigVer );
				}
			}
			else
			{
				TestResultInfo( _T("\r\nDownload config exception\r\n") );
				auto szConfigVer = TestResultInfoR( _T("Ver=0x%x"), cfgVerFromTp );
				TestResultInfo( "\r\n\r\n//Config Test is Fail\r\n", ITEM_STA_FAIL );
				itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
			}

			//SM_CommBase(m_deviceNo)->SetIoVoltage(pCfg7449->vddVotage, pCfg7449->ioVddVotage);
			//SysDelay(50);
		}
	}

	return itemNotify;
}
unsigned int CTest7449::OSCTrim_Test( NativeTestItem& itemQuote )
{
	int failerCnt = 0;
	unsigned int iReCode = ERROR_CODE_OK;
	ISMChip7449* iChip7449 = (ISMChip7449*)SM_ChipBase(m_deviceNo);
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );

	TestResultInfo( _T("\r\n------------------------------OSC Trim Test------------------------------\r\n") );

	unsigned char osTrim32k = 0, osTrim48m = 0, osTrim64m = 0, osTrim150m = 0;
	unsigned char mode1_osTrim32k = 0, mode1_osTrim64m = 0, mode1_osTrim150m = 0;
	unsigned char readBuffer[64] = {0};

	iReCode = SM_ChipBase(m_deviceNo)->ReadBurnSpace( AddrOSCTrim, readBuffer, sizeof(readBuffer) );
	if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	osTrim150m = readBuffer[1];
	osTrim48m  = readBuffer[2];
	osTrim32k  = readBuffer[3];
	mode1_osTrim150m = readBuffer[33];
	mode1_osTrim64m  = readBuffer[34];
	mode1_osTrim32k  = readBuffer[35];
	m_stOneRecord.ReleaseID = *(UINT64*)&readBuffer[8];

	if( m_stOneRecord.ReleaseID != pCfg7449->vid_pid
		|| 0xff != (readBuffer[1] + readBuffer[5]) 
		|| 0xff != (readBuffer[2] + readBuffer[6])
		|| 0xff != (readBuffer[3] + readBuffer[7])
		|| 0xff != (readBuffer[33] + readBuffer[37]) 
		|| 0xff != (readBuffer[34] + readBuffer[38])
		|| 0xff != (readBuffer[35] + readBuffer[39])
		|| osTrim150m < pCfg7449->trim_150m_min 
		|| osTrim150m > pCfg7449->trim_150m_max
		|| osTrim48m < pCfg7449->trim_48m_min
		|| osTrim48m > pCfg7449->trim_48m_max 
		|| osTrim32k < pCfg7449->trim_32k_min
		|| osTrim32k > pCfg7449->trim_32k_max
		|| mode1_osTrim150m < pCfg7449->trim_150m_min 
		|| mode1_osTrim150m > pCfg7449->trim_150m_max
		|| mode1_osTrim64m < pCfg7449->trim_64m_min
		|| mode1_osTrim64m > pCfg7449->trim_64m_max 
		|| mode1_osTrim32k < pCfg7449->trim_32k_min
		|| mode1_osTrim32k > pCfg7449->trim_32k_max)
	{
		TestResultInfo( _T("Start Trim And Refresh Trim Value\r\n") );

		SysDelay( 10 );
		iReCode = iChip7449->GetOSCTrim( &osTrim32k, &osTrim48m, &osTrim150m, pCfg7449->trim_speed_mode, pCfg7449->tick_32k_standard, pCfg7449->tick_48m_standard, pCfg7449->tick_150m_standard );
		if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

		if( osTrim32k < pCfg7449->trim_32k_min )
			failerCnt++;
		else if( osTrim32k > pCfg7449->trim_32k_max )
			failerCnt++;
		else if( osTrim48m < pCfg7449->trim_48m_min )
			failerCnt++;
		else if( osTrim48m > pCfg7449->trim_48m_max )
			failerCnt++;
		else if( osTrim150m < pCfg7449->trim_150m_min )
			failerCnt++;
		else if( osTrim150m > pCfg7449->trim_150m_max )
			failerCnt++;

		if( failerCnt == 0 )
		{
			readBuffer[0] = pCfg7449->trim_speed_mode;
			readBuffer[1] = osTrim150m;
			readBuffer[2] = osTrim48m;
			readBuffer[3] = osTrim32k;

			readBuffer[4] = ~pCfg7449->trim_speed_mode;
			readBuffer[5] = ~osTrim150m;
			readBuffer[6] = ~osTrim48m;
			readBuffer[7] = ~osTrim32k;

			iReCode = iChip7449->GetOSCTrim( &mode1_osTrim32k, &mode1_osTrim64m, &mode1_osTrim150m, 1, pCfg7449->tick_32k_standard, pCfg7449->tick_64m_standard, pCfg7449->tick_150m_standard );

			if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

			if( mode1_osTrim32k < pCfg7449->trim_32k_min )
				failerCnt++;
			else if( mode1_osTrim32k > pCfg7449->trim_32k_max )
				failerCnt++;
			else if( mode1_osTrim64m < pCfg7449->trim_64m_min )
				failerCnt++;
			else if( mode1_osTrim64m > pCfg7449->trim_64m_max )
				failerCnt++;
			else if( mode1_osTrim150m < pCfg7449->trim_150m_min )
				failerCnt++;
			else if( mode1_osTrim150m > pCfg7449->trim_150m_max )
				failerCnt++;

			if( failerCnt == 0 )
			{
				readBuffer[32] = 1;
				readBuffer[33] = mode1_osTrim150m;
				readBuffer[34] = mode1_osTrim64m;
				readBuffer[35] = mode1_osTrim32k;

				readBuffer[36] = ~1;
				readBuffer[37] = ~mode1_osTrim150m;
				readBuffer[38] = ~mode1_osTrim64m;
				readBuffer[39] = ~mode1_osTrim32k;

			}

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
			//iReCode = SM_ChipBase(m_deviceNo)->WriteBurnSpace( AddrOSCTrim, readBuffer, sizeof(readBuffer), OTP_W_CHK | TLK_DATACHK_EX1 );


		}

		//vid_pid
		UINT64* p_vid_pid = (UINT64*)&readBuffer[16];
		*p_vid_pid = pCfg7449->vid_pid;

		iReCode = SM_ChipBase(m_deviceNo)->WriteBurnSpace( AddrOSCTrim, readBuffer, sizeof(readBuffer), OTP_W_CHK | TLK_DATACHK_EX1 );
		if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

		//iReCode = SM_ChipBase(m_deviceNo)->GetOSCTrim( &osTrim2, pCfg7449->tick_standard );
		//if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

// 		if((osTrim1 - osTrim2) * (osTrim1 - osTrim2) > 49)
// 		{
// 			TestResultInfo( _T("OSTrim Value Out Of Range\r\n") );
// 			return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( ERROR_CODE_INVALID_PARAM ) );
// 		}

// 		oscTrimNew = (osTrim1 + osTrim2) >> 1;
// 		m_stOneRecord.Mcap.oscTrim = oscTrimNew;

// 		unsigned short osc =  ( ~oscTrimNew ) & 0xff;
// 		osc = ( osc << 8 ) + oscTrimNew;	

// 		SysDelay( 10 );
// 		iReCode = SM_ChipBase(m_deviceNo)->WriteBurnSpace( 0xe000, (unsigned char*)&osc, 2, OTP_W_CHK | TLK_DATACHK_EX1 );
// 		if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
// 
// 		SysDelay( 10 );
// 		iReCode = SM_ChipBase(m_deviceNo)->ReadBurnSpace( 0xe000, readBuffer, 2 );
// 		if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

		//transformat( szBuffer, _T("OSCTrim = 0x%02x"), readBuffer[0] );
		
	}

	m_stOneRecord.ReleaseID = *(UINT64*)&readBuffer[8];
	UINT32 otm_time = *(UINT32*)&m_stOneRecord.ReleaseID;
	TestResultInfoR( _T("ICID = 0x%llx,   %d-%d, %d:%d:%d\r\n"), m_stOneRecord.ReleaseID, (otm_time>>22)&0xf, (otm_time>>17)&0x1f,(otm_time>>12)&0x1f, (otm_time>>6)&0x3f, otm_time&0x3f );

	m_stOneRecord.Mcap.oscTrim = *((unsigned int*)readBuffer);
	auto szBuffer = TestResultInfoR( _T("mode 0: 32K = 0x%02x, 48M/64M = 0x%02x, 150M = 0x%02x\r\n"), osTrim32k, osTrim48m, osTrim150m);
    szBuffer = TestResultInfoR( _T("mode 1: 32K = 0x%02x, 64M = 0x%02x, 150M = 0x%02x\r\n"), mode1_osTrim32k, mode1_osTrim64m, mode1_osTrim150m);

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
unsigned int CTest7449::Current_Test( NativeTestItem& itemQuote )
{
	TEST_ITEM_STATUS itemStatus = ITEM_STA_NONE;
	for( int index = 0; index < 3; index++ )
	{
		itemStatus = (TEST_ITEM_STATUS)Current_TestEx( itemQuote );
		if( itemStatus == ITEM_STA_PASS ) break;
	}
	return itemStatus;
}
unsigned int CTest7449::Current_TestEx( NativeTestItem& itemQuote )
{
	int failedCount = 0;
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );

	TestResultInfo( _T("\r\n------------------------------Current Test------------------------------\r\n") );

	ISMChip7449* iChip7449 = (ISMChip7449*)SM_ChipBase(m_deviceNo);
	if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	short deepCurrent = 0, sleepCurrent = 0, activeCurrent = 0, idleCurrent = 0;
	short level[2][3] = {
		pCfg7449->active_current_min, pCfg7449->sleep_current_min, pCfg7449->deep_current_min,
		pCfg7449->active_current_max, pCfg7449->sleep_current_max, pCfg7449->deep_current_max,
	};
	iReCode = iChip7449->GetCurrent( level, (unsigned short*)&activeCurrent, (unsigned short*)&sleepCurrent, (unsigned short*)&deepCurrent, (unsigned short*)&idleCurrent );
	if( ERROR_CODE_OK != iReCode )  return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	//iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_CTP_RST );
	//SysDelay( 50 );


	{
		m_stOneRecord.current_mode1 = activeCurrent;
		m_stOneRecord.current_mode2 = sleepCurrent;
		m_stOneRecord.current_mode3 = deepCurrent;
		TestResultInfoR( _T("\r\nactive = %d, sleep = %d, deep = %d\r\n"), activeCurrent, sleepCurrent, deepCurrent );
	}
	if( activeCurrent < pCfg7449->active_current_min )
	{
		failedCount++;
		TestResultInfoR( _T( "\r\nactive(%d) < setting min(%d)\r\n"), activeCurrent, pCfg7449->active_current_min );
	}
	if( activeCurrent > pCfg7449->active_current_max )
	{
		failedCount++;
		TestResultInfoR( _T( "\r\nactive(%d) > setting max(%d)\r\n"), activeCurrent, pCfg7449->active_current_max );
	}
	if( sleepCurrent < pCfg7449->sleep_current_min )
	{
		failedCount++;
		TestResultInfoR( _T( "\r\nsleep(%d) < setting min(%d)\r\n"), sleepCurrent, pCfg7449->sleep_current_min );
	}
	if( sleepCurrent > pCfg7449->sleep_current_max )
	{
		failedCount++;
		TestResultInfoR( _T( "\r\nsleep(%d) > setting max(%d)\r\n"), sleepCurrent, pCfg7449->sleep_current_max );
	}
	if( deepCurrent < pCfg7449->deep_current_min )
	{
		failedCount++;
		TestResultInfoR( _T( "\r\ndeep(%d) < setting min(%d)\r\n"), deepCurrent, pCfg7449->deep_current_min );
	}
	if( deepCurrent > pCfg7449->deep_current_max )
	{
		failedCount++;
		TestResultInfoR( _T( "\r\ndeep(%d) > setting max(%d)\r\n"), deepCurrent, pCfg7449->deep_current_max );
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
//unsigned int CTest7449::Base_Test( NativeTestItem& itemQuote )
//{
//	int failerCount = 0;
//	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
//	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );
//	signed short baseTempBuffer[MAX_MCAP_CHANNEL * 2] = {0};
//	/*unsigned*/ short baseMatrix[MAX_MCAP_ROW][MAX_MCAP_COL];
//	const unsigned int iRawDataLen = ((pCfg7449->rowsCnt) * (pCfg7449->colsCnt) * 2 + 3) & 0xfffffffc;
//
//	TestResultInfo( _T("\r\n------------------------------Base Test------------------------------\r\n") );
//
//	if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
//	ISMChip7449* iChip7449 = (ISMChip7449*)SM_ChipBase(m_deviceNo);
//
//	int addRow = ( pCfg7449->real_channel_num - pCfg7449->va_channel_num ) ? 1 : 0;
//
//	iReCode = iChip7449->IncokeCommand( CMD_CTP_RST );
//	SysDelay( 50 );
//
//	iReCode = iChip7449->SwitchMode( MODE_RAWDATA, iRawDataLen );
//	if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
//	SysDelay( 20 );
//
//	for( int index = 0; index < 2; index++ )
//	{
//		iReCode = iChip7449->GetRawData( baseTempBuffer, iRawDataLen );
//		if( iReCode == ERROR_CODE_OK ) break;
//		if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
//	}
//	
//	int ref_channel_num = min(pCfg7449->real_channel_num - pCfg7449->va_channel_num, pCfg7449->colsCnt);
//	AnalyzeInfo info( pCfg7449->rowsCnt, pCfg7449->colsCnt, ref_channel_num, false );
//	ReShappingData</*unsigned*/ short>( baseMatrix, (/*unsigned*/ short*)baseTempBuffer, G_XMLConfig->real_channel_num * 2, pCfg7449->rowsCnt, pCfg7449->colsCnt );
//	//short baseMin[MAX_MCAP_ROW][MAX_MCAP_COL] = {0}, baseMax[MAX_MCAP_ROW][MAX_MCAP_COL] = {0};
//	//FillArrayUseValue( baseMin, pCfg7449->base_min );
//	//FillArrayUseValue( baseMax, pCfg7449->base_max );
//
//	NodeVal nodeOutRange;
//	ColorText textTemp( _T("\r\nBase Data:\r\n") );
//	bool bResult = AnalyzeTestResult( baseMatrix, pCfg7449->base_min, pCfg7449->base_max, pCfg7449->invalid_node, info, textTemp, nodeOutRange, true );
//	TestResultInfo( textTemp );
//	if( !bResult )
//	{
//		failerCount++;
//		LPCTSTR strHead = _T("\r\n//========= Out of Threshold in BaseTest: \r\n");
//		PrintNodeValue( m_ColorText, &nodeOutRange, strHead );
//	}
//
//	if( failerCount )
//	{
//		itemNotify.UpdateItemResult( ITEM_STA_FAIL );
//		TestResultInfo( "\r\n\r\n//Base Test is Fail\r\n", ITEM_STA_FAIL );
//	}
//	else
//	{
//		itemNotify.UpdateItemResult( ITEM_STA_PASS );
//		TestResultInfo( "\r\n\r\n//Base Test is Pass\r\n", ITEM_STA_PASS );
//	}
//
//	return itemNotify;
//}
unsigned int CTest7449::ScapRawData_Test( NativeTestItem& itemQuote )
{
	int failerCount = 0;
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );
	signed short baseTempBuffer[MAX_MCAP_CHANNEL * 2] = {0};
	/*unsigned*/ short dataMatrix[MAX_MCAP_ROW][MAX_MCAP_COL];
	const unsigned int iRawDataLen = ((pCfg7449->rowsCnt + 1) * (pCfg7449->colsCnt + 1) * 2 + 3) & 0xfffffffc;
	const unsigned int iScapRawDataLen = pCfg7449->rowsCnt + pCfg7449->colsCnt;

	TestResultInfo( _T("\r\n------------------------------ScapData Test------------------------------\r\n") );

	if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	ISMChip7449* iChip7449 = (ISMChip7449*)SM_ChipBase(m_deviceNo);

	int addRow = ( pCfg7449->real_channel_num - pCfg7449->va_channel_num ) ? 1 : 0;

	//iReCode = iChip7449->IncokeCommand( CMD_CTP_RST );
	//SysDelay( 50 );

	iReCode = iChip7449->SwitchMode( MODE_RAWDATA, iRawDataLen );
	if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	SysDelay( 20 );

	for( int index = 0; index < 2; index++ )
	{
		iReCode = iChip7449->GetRawData( baseTempBuffer, iRawDataLen );
		if( iReCode == ERROR_CODE_OK ) break;
		if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	}

	int ref_channel_num = min(pCfg7449->real_channel_num - pCfg7449->va_channel_num, pCfg7449->colsCnt);
	AnalyzeInfo info( pCfg7449->rowsCnt, pCfg7449->colsCnt );
	unsigned short maxCols[] = { pCfg7449->colsCnt, pCfg7449->rowsCnt };
	ReShappingData</*unsigned*/ short>( dataMatrix, (/*unsigned*/ short*)baseTempBuffer + pCfg7449->rowsCnt * pCfg7449->colsCnt, iScapRawDataLen, 2, maxCols );
	//short baseMin[MAX_MCAP_ROW][MAX_MCAP_COL] = {0}, baseMax[MAX_MCAP_ROW][MAX_MCAP_COL] = {0};
	//FillArrayUseValue( baseMin, pCfg7449->base_min );
	//FillArrayUseValue( baseMax, pCfg7449->base_max );

	NodeVal nodeOutRange;
	ColorText textTemp( _T("\r\nScap Data:\r\n") );
	bool bResult = AnalyzeTestResultMSCap( dataMatrix, pCfg7449->scap_rawdata_min, pCfg7449->scap_rawdata_max, pCfg7449->invalid_node, info, textTemp, nodeOutRange, true );
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
unsigned int CTest7449::VT_Test( NativeTestItem& itemQuote )
{
	int failerCount = 0;
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );
	signed short baseTempBuffer1[MAX_MCAP_CHANNEL * 2] = {0};
	signed short baseTempBuffer2[MAX_MCAP_CHANNEL * 2] = {0};
	/*unsigned*/ short dataMatrix[2][MAX_MCAP_COL];
	const unsigned int iRawDataLen = ((pCfg7449->rowsCnt + 1) * (pCfg7449->colsCnt + 1) * 2 + 3) & 0xfffffffc;
	const unsigned int iScapRawDataLen = pCfg7449->rowsCnt + pCfg7449->colsCnt;

	TestResultInfo( _T("\r\n------------------------------VT Test------------------------------\r\n") );

	if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	ISMChip7449* iChip7449 = (ISMChip7449*)SM_ChipBase(m_deviceNo);

	int addRow = ( pCfg7449->real_channel_num - pCfg7449->va_channel_num ) ? 1 : 0;

	//iReCode = iChip7449->IncokeCommand( CMD_CTP_RST );
	//SysDelay( 50 );

	iReCode = iChip7449->SwitchMode( MODE_RAWDATA, iRawDataLen );
	if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	SysDelay( 20 );

	for( int index = 0; index < 2; index++ )
	{
		iReCode = iChip7449->GetRawData( baseTempBuffer1, iRawDataLen );
		if( iReCode == ERROR_CODE_OK ) break;
		if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	}

// 	unsigned int regCtrl = 0;
// 	iReCode = iChip7449->ReadCoreSpace( 0x40002000 + 0xf8, (unsigned char*)&regCtrl, 4 );
// 	//regCtrl = regCtrl & (~(0x01 << 16));
// 	regCtrl = regCtrl | (0x01 << 16);
// 	iReCode = iChip7449->WriteCoreSpace( 0x40002000 + 0xf8, (unsigned char*)&regCtrl, 4 );

	iReCode = iChip7449->IncokeCommand(CMD_CTP_FREQ, 5, 1);

	iReCode = iChip7449->SwitchMode( MODE_RAWDATA, iRawDataLen );
	if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	SysDelay( 20 );

	for( int index = 0; index < 2; index++ )
	{
		iReCode = iChip7449->GetRawData( baseTempBuffer2, iRawDataLen );
		if( iReCode == ERROR_CODE_OK ) break;
		if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	}

	AnalyzeInfo info( pCfg7449->rowsCnt, pCfg7449->colsCnt );
	unsigned short maxCols[] = { pCfg7449->colsCnt, pCfg7449->rowsCnt };
	short vtMin[2][MAX_MCAP_COL] = {0}, vtMax[2][MAX_MCAP_COL] = {0};
	
	{
		NodeVal nodeOutRange;
		ColorText textTemp( _T("\r\nVT Cap-Off:\r\n") );
		FillMatrixUseValue<short>( vtMin, -30000 );
		FillMatrixUseValue<short>( vtMax, +30000 );
		ReShappingData<short>( dataMatrix, (/*unsigned*/ short*)baseTempBuffer1 + pCfg7449->rowsCnt * pCfg7449->colsCnt, iScapRawDataLen, 2, maxCols );
		AnalyzeTestResultMSCap( dataMatrix, vtMin, vtMax, pCfg7449->invalid_node, info, textTemp, nodeOutRange, true );
		TestResultInfo( textTemp );
	}

	{
		NodeVal nodeOutRange;
		ColorText textTemp( _T("\r\nVT Cap-On:\r\n") );
		FillMatrixUseValue<short>( vtMin, -30000 );
		FillMatrixUseValue<short>( vtMax, +30000 );
		ReShappingData<short>( dataMatrix, (/*unsigned*/ short*)baseTempBuffer2 + pCfg7449->rowsCnt * pCfg7449->colsCnt, iScapRawDataLen, 2, maxCols );
		AnalyzeTestResultMSCap( dataMatrix, vtMin, vtMax, pCfg7449->invalid_node, info, textTemp, nodeOutRange, true );
		TestResultInfo( textTemp );
	}
	

	ArraySubstract( baseTempBuffer2, baseTempBuffer1, iRawDataLen << 1 );

	//int ref_channel_num = min(pCfg7449->real_channel_num - pCfg7449->va_channel_num, pCfg7449->colsCnt);
	
	
	ReShappingData<short>( dataMatrix, (/*unsigned*/ short*)baseTempBuffer2 + pCfg7449->rowsCnt * pCfg7449->colsCnt, iScapRawDataLen, 2, maxCols );
	NormalizationData<short>( dataMatrix, 2, maxCols );

	{
		NodeVal nodeOutRange;
		ColorText textTemp( _T("\r\nVT Data:\r\n") );
		FillMatrixUseValue( vtMin, pCfg7449->vt_min );
		FillMatrixUseValue( vtMax, pCfg7449->vt_max );
		bool bResult = AnalyzeTestResultMSCap( dataMatrix, vtMin, vtMax, pCfg7449->invalid_node, info, textTemp, nodeOutRange, true );
		TestResultInfo( textTemp );
		if( !bResult )
		{
			failerCount++;
			LPCTSTR strHead = _T("\r\n//========= Out of Threshold in VTTest: \r\n");
			PrintNodeValue( m_ColorText, &nodeOutRange, strHead );
		}
	}

	if( failerCount )
	{
		itemNotify.UpdateItemResult( ITEM_STA_FAIL );
		TestResultInfo( "\r\n\r\n//VT Test is Fail\r\n", ITEM_STA_FAIL );
	}
	else
	{
		itemNotify.UpdateItemResult( ITEM_STA_PASS );
		TestResultInfo( "\r\n\r\n//VT Test is Pass\r\n", ITEM_STA_PASS );
	}

	return itemNotify;
}
unsigned int CTest7449::STC_Test( NativeTestItem& itemQuote )
{
	int failerCount = 0;
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );
	signed short baseTempBuffer[MAX_MCAP_CHANNEL * 2] = {0};
	signed int baseSum[MAX_MCAP_CHANNEL * 2] = {0};
	/*unsigned*/ short baseMatrix[MAX_MCAP_ROW][MAX_MCAP_COL], uniformityMin[MAX_MCAP_ROW][MAX_MCAP_COL];
	const unsigned int iRawDataLen = ((pCfg7449->rowsCnt) * (pCfg7449->colsCnt) * 2 + 3) & 0xfffffffc;
	const unsigned int iRetry = 20;

	TestResultInfo( _T("\r\n------------------------------STC Test------------------------------\r\n") );

	if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	ISMChip7449* iChip7449 = (ISMChip7449*)SM_ChipBase(m_deviceNo);

	int addRow = ( pCfg7449->real_channel_num - pCfg7449->va_channel_num ) ? 1 : 0;
	memset( uniformityMin, 0, sizeof(uniformityMin) );

	//iReCode = iChip7449->IncokeCommand( CMD_CTP_RST );
	//SysDelay( 100 );

	//iReCode = iChip7449->SetClkInFctMode( pCfg7449->stc_clk_div, false );
	//if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	//SysDelay( 20 );

	iReCode = iChip7449->SwitchMode( MODE_RAWDATA, iRawDataLen );
	if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	SysDelay( 20 );

	memset( baseSum, 0, sizeof(baseSum) );
	for( int index = 0; index < iRetry; index++ )
	{
		iReCode = iChip7449->GetRawData( baseTempBuffer, iRawDataLen );
		if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

		if(0 == index) continue;
		ArrayAddtion( baseSum, baseTempBuffer, iRawDataLen );
	}
	ArrayAverage( baseTempBuffer, baseSum, iRawDataLen, iRetry - 1);

	int ref_channel_num = min(pCfg7449->real_channel_num - pCfg7449->va_channel_num, pCfg7449->colsCnt);
	AnalyzeInfo info( pCfg7449->rowsCnt, pCfg7449->colsCnt, ref_channel_num, false );
	ReShappingData</*unsigned*/ short>( baseMatrix, (/*unsigned*/ short*)baseTempBuffer, G_XMLConfig->real_channel_num * 2, pCfg7449->rowsCnt, pCfg7449->colsCnt );
	//short baseMin[MAX_MCAP_ROW][MAX_MCAP_COL] = {0}, baseMax[MAX_MCAP_ROW][MAX_MCAP_COL] = {0};
	//FillArrayUseValue( baseMin, pCfg7449->base_min );
	//FillArrayUseValue( baseMax, pCfg7449->base_max );

	{
		NodeVal nodeOutRange;
		ColorText textTemp( _T("\r\nstc_rawdata:\r\n") );
		short baseMin[MAX_MCAP_ROW][MAX_MCAP_COL] = {0}, baseMax[MAX_MCAP_ROW][MAX_MCAP_COL] = {0};
		FillMatrixUseValue<short>( baseMax, 30000 );
		bool bResult = AnalyzeTestResult( baseMatrix, baseMin, baseMax, pCfg7449->invalid_node, info, textTemp, nodeOutRange, true );
		TestResultInfo( textTemp );
	}

	{
		NodeVal nodeOutRange;
		ColorText textTemp( _T("\r\nstc_deviation:\r\n") );
		for( int iRow = 0; iRow < pCfg7449->rowsCnt; iRow++ )
		{
			for( int iCol = 0; iCol < pCfg7449->colsCnt; iCol++ )
			{
				int deviation = 10 * abs( baseMatrix[iRow][iCol] - pCfg7449->stc_mean[iRow][iCol] );
				baseMatrix[iRow][iCol] = (short)(100 * deviation / (deviation + 3 * pCfg7449->stc_mse[iRow][iCol] + 0.001));
			}
		}
			
				
		short stcMin[MAX_MCAP_ROW][MAX_MCAP_COL] = {0}, stcMax[MAX_MCAP_ROW][MAX_MCAP_COL] = {0};
		FillMatrixUseValue( stcMin, pCfg7449->stc_min );
		FillMatrixUseValue( stcMax, pCfg7449->stc_max );
		bool bResult = AnalyzeTestResult( baseMatrix, stcMin, stcMax, pCfg7449->invalid_node, info, textTemp, nodeOutRange, true );
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
// 		CopyAndInvalid( uniformityHorInvalid, pCfg7449->invalid_node, 0, MAX_MCAP_COL );
// 		GenHorizontalConvolution( baseMatrix, uniformityHorMatrix, pCfg7449->rowsCnt, pCfg7449->colsCnt );
// 		bool bResult = AnalyzeTestResult( uniformityHorMatrix, uniformityMin, pCfg7449->stc_uniformity_h, uniformityHorInvalid, info, textTemp, nodeOutRange, true );
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
// 		CopyAndInvalid( uniformityVerInvalid, pCfg7449->invalid_node, MAX_MCAP_ROW, 0 );
// 		GenVerticalConvolution( baseMatrix, uniformityVerMatrix, pCfg7449->rowsCnt, pCfg7449->colsCnt );
// 		bool bResult = AnalyzeTestResult( uniformityVerMatrix, uniformityMin, pCfg7449->stc_uniformity_v, uniformityVerInvalid, info, textTemp, nodeOutRange, true );
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
unsigned int CTest7449::MCapRawData_Test( NativeTestItem& itemQuote )
{
	int failerCount = 0;
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );
	signed short baseTempBuffer[MAX_MCAP_CHANNEL * 2] = {0};
	signed int baseSum[MAX_MCAP_CHANNEL * 2] = {0};
	/*unsigned*/ short baseMatrix[MAX_MCAP_ROW][MAX_MCAP_COL], uniformityMin[MAX_MCAP_ROW][MAX_MCAP_COL], NormalizationMatrix[MAX_MCAP_ROW][MAX_MCAP_COL];
	const unsigned int iRawDataLen = ((pCfg7449->rowsCnt) * (pCfg7449->colsCnt) * 2 + 3) & 0xfffffffc;
	const unsigned int iRetry = 20;

	TestResultInfo( _T("\r\n------------------------------MCap RawData Test------------------------------\r\n") );

	if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	ISMChip7449* iChip7449 = (ISMChip7449*)SM_ChipBase(m_deviceNo);

	int addRow = ( pCfg7449->real_channel_num - pCfg7449->va_channel_num ) ? 1 : 0;
	memset( uniformityMin, 0, sizeof(uniformityMin) );

	//iReCode = iChip7449->IncokeCommand( CMD_CTP_RST );
	//SysDelay( 100 );

	//iReCode = iChip7449->SetClkInFctMode( pCfg7449->mcap_clk_div, false );
	//if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	//SysDelay( 20 );

	iReCode = iChip7449->SwitchMode( MODE_RAWDATA, iRawDataLen );
	if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	SysDelay( 20 );

	memset( baseSum, 0, sizeof(baseSum) );
	for( int index = 0; index < iRetry; index++ )
	{
		iReCode = iChip7449->GetRawData( baseTempBuffer, iRawDataLen );
		if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

		if(0 == index) continue;
		ArrayAddtion( baseSum, baseTempBuffer, iRawDataLen );
	}
	ArrayAverage( baseTempBuffer, baseSum, iRawDataLen, iRetry - 1);

	int ref_channel_num = min(pCfg7449->real_channel_num - pCfg7449->va_channel_num, pCfg7449->colsCnt);
	AnalyzeInfo info( pCfg7449->rowsCnt, pCfg7449->colsCnt, ref_channel_num, false );
	ReShappingData</*unsigned*/ short>( baseMatrix, (/*unsigned*/ short*)baseTempBuffer, G_XMLConfig->real_channel_num * 2, pCfg7449->rowsCnt, pCfg7449->colsCnt );
	//short baseMin[MAX_MCAP_ROW][MAX_MCAP_COL] = {0}, baseMax[MAX_MCAP_ROW][MAX_MCAP_COL] = {0};
	//FillArrayUseValue( baseMin, pCfg7449->base_min );
	//FillArrayUseValue( baseMax, pCfg7449->base_max );
	ColorText textTempa( _T("\r\nmcap_rawdata:\r\n") );
	PrintMaxtrixValue( textTempa, baseMatrix,pCfg7449->invalid_node, info, true );
	TestResultInfo( textTempa );
	Copy_RawData<MAX_MCAP_ROW,MAX_MCAP_COL>(NormalizationMatrix, baseMatrix, pCfg7449->rowsCnt, pCfg7449->colsCnt);

	auto pioce = 1.0f;
	RawData_Normalization<MAX_MCAP_ROW,MAX_MCAP_COL>(NormalizationMatrix,pCfg7449->mcap_rawdata_min, pCfg7449->mcap_rawdata_max,pCfg7449->rowsCnt, pCfg7449->colsCnt,pCfg7449->macp_normalization_ratio_min,pCfg7449->macp_normalization_ratio_max,pioce);

	TestResultInfoR(_T("\r\nnormalization_constant = %.2f, min =%.2f, max= %.2f\r\n"),pioce,pCfg7449->macp_normalization_ratio_min,pCfg7449->macp_normalization_ratio_max );

	{
		NodeVal nodeOutRange;
		ColorText textTemp( _T("\r\nmcap_normalization:\r\n") );
		bool bResult = AnalyzeTestResult( NormalizationMatrix, pCfg7449->mcap_rawdata_min, pCfg7449->mcap_rawdata_max, pCfg7449->invalid_node, info, textTemp, nodeOutRange, true );
		TestResultInfo( textTemp );
		if( !bResult )
		{
			failerCount++;
			LPCTSTR strHead = _T("\r\n//========= Out of Threshold in MCap RawData Test: \r\n");
			PrintNodeValue( m_ColorText, &nodeOutRange, strHead );
			if(pCfg7449->mcap_allow_overrun_num>0)
			{
				LPCTSTR strHead = _T("\r\n//========= Judge MCap RawData Again: \r\n");
				if(0 == JudgeNodeOutRangeAgain(m_ColorText,&nodeOutRange, strHead, pCfg7449->mcap_ranks_allow_overrun_num, pCfg7449->mcap_allow_overrun_num, pCfg7449->mcap_allow_overrun_ratio))
				{
					failerCount = 0;
				}
			}
		}

	}
	
	if(pCfg7449->check_uniformity_hor)
	{
		NodeVal nodeOutRange;
		ColorText textTemp( _T("\r\nmcap_uniformity_h:\r\n") );
		short uniformityHorMatrix[MAX_MCAP_ROW][MAX_MCAP_COL];
		unsigned char uniformityHorInvalid[MAX_MCAP_ROW][MAX_MCAP_COL];
		CopyAndInvalid( uniformityHorInvalid, pCfg7449->invalid_node, 0, MAX_MCAP_COL );
		GenHorizontalUniformity( NormalizationMatrix, uniformityHorMatrix, pCfg7449->rowsCnt, pCfg7449->colsCnt );
		bool bResult = AnalyzeTestResult( uniformityHorMatrix, uniformityMin, pCfg7449->mcap_uniformity_h, uniformityHorInvalid, info, textTemp, nodeOutRange, true );
		TestResultInfo( textTemp );
		if( !bResult )
		{
			failerCount++;
			LPCTSTR strHead = _T("\r\n//========= Out of Threshold in MCap Uniformity-H: \r\n");
			PrintNodeValue( m_ColorText, &nodeOutRange, strHead );
		}
	}

	if(pCfg7449->check_uniformity_ver)
	{
		NodeVal nodeOutRange;
		ColorText textTemp( _T("\r\nmcap_uniformity_v:\r\n") );
		short uniformityVerMatrix[MAX_MCAP_ROW][MAX_MCAP_COL];
		unsigned char uniformityVerInvalid[MAX_MCAP_ROW][MAX_MCAP_COL];
		CopyAndInvalid( uniformityVerInvalid, pCfg7449->invalid_node, MAX_MCAP_ROW, 0 );
		GenVerticalUniformity( NormalizationMatrix, uniformityVerMatrix, pCfg7449->rowsCnt, pCfg7449->colsCnt );
		bool bResult = AnalyzeTestResult( uniformityVerMatrix, uniformityMin, pCfg7449->mcap_uniformity_v, uniformityVerInvalid, info, textTemp, nodeOutRange, true );
		TestResultInfo( textTemp );
		if( !bResult )
		{
			failerCount++;
			LPCTSTR strHead = _T("\r\n//========= Out of Threshold in MCap Uniformity-V: \r\n");
			PrintNodeValue( m_ColorText, &nodeOutRange, strHead );
		}
	}

	auto sampling = Judge_RawData_sampling<MAX_MCAP_ROW,MAX_MCAP_COL>(pCfg7449->mcap_rawdata_min, pCfg7449->mcap_rawdata_max,pCfg7449->invalid_node,pCfg7449->rowsCnt, pCfg7449->colsCnt,pCfg7449->rawdata_min_value,pCfg7449->rawdata_max_value);
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
unsigned int CTest7449::Short_Test( NativeTestItem& itemQuote )
{
    bool isCsv = false;
	int failerCount = 0;
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );
	const int max_short_adc_num = 72;
	unsigned short shortAdc[max_short_adc_num] = {0};
	unsigned short adcMatrix[2][MAX_MCAP_COL] = {0};
	AnalyzeInfo info( pCfg7449->rowsCnt, pCfg7449->colsCnt, 0, false );

	TestResultInfo( _T("\r\n------------------------------Short Test------------------------------\r\n") );

	if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	ISMChip7449* iChip7449 = (ISMChip7449*)SM_ChipBase(m_deviceNo);

	iReCode = iChip7449->GetShortData( shortAdc, max_short_adc_num * 2 );
	if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	unsigned short maxCols[] = { pCfg7449->colsCnt, pCfg7449->rowsCnt };
	ICArrayToSensorMatrix( adcMatrix, shortAdc, max_short_adc_num, 2, maxCols );

	NodeVal nodeOutRange;
	NodeVal nodeOutRange_add;
	unsigned short adcMin[2][MAX_MCAP_COL] = {0};
	unsigned short adcMax[2][MAX_MCAP_COL] = {0};
	ColorText textTemp( _T("\r\nShort Data:\r\n") );
	ColorText textTemp_add( _T("\r\nAdditional Short Data:\r\n") );
	FillMatrixUseValue( adcMin, (unsigned short)0 );
	FillMatrixRowUseValue( adcMax, pCfg7449->short_tx_max, 0 );
	FillMatrixRowUseValue( adcMax, pCfg7449->short_rx_max, 1 );
	adcMax[0][6] = 1300;
	bool bResult = AnalyzeTestResultMSCap<unsigned short>( adcMatrix, adcMin, adcMax, pCfg7449->invalid_node, info, textTemp, nodeOutRange, true );
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
        bool bResult_add = AnalyzeTestResultAdditionalMSCapJudge<unsigned short>( shortAdc, adcMin, adcMax, MAX_RX_NUM_7449, MAX_TX_NUM_7449, textTemp_add, nodeOutRange_add, isCsv);
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
unsigned int CTest7449::FRT_Test( NativeTestItem& itemQuote )
{
	SysDelay( 200 );
	int failerCnt = 0;
	unsigned int iReCode = ERROR_CODE_COMM_ERROR, errCode = 0;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );
	unsigned char retBuffer[20];

	TestResultInfo( _T("\r\n------------------------------FRT Test------------------------------\r\n") );

	if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	ISMChip7449* iChip7449 = (ISMChip7449*)SM_ChipBase(m_deviceNo);

	iReCode = iChip7449->IncokeCommand( CMD_RAM_TST, 0, 0, 0, retBuffer );
	if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	errCode = *(unsigned int*)&retBuffer[2];
	if(0x54000000 != errCode)
	{
		failerCnt++;
		TestResultInfoR( _T("ReadCoreSpace, Code = 0x%x\r\n"), errCode );
	}


	iReCode = iChip7449->IncokeCommand( CMD_FLASH_TST, 0, 0, 0, retBuffer );
	if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	errCode = *(unsigned int*)&retBuffer[2];
	if(0x54000000 != errCode)
	{
		failerCnt++;
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
unsigned int CTest7449::IOVoltage_Test( NativeTestItem& itemQuote )
{
	int failerCnt = 0;
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );

	TestResultInfo( _T("\r\n------------------------------IOVoltage Test------------------------------\r\n") );

	if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	ISMChip7449* iChip7449 = (ISMChip7449*)SM_ChipBase(m_deviceNo);

	unsigned int ioVols[2][10] = {0};
	iReCode = iChip7449->GetIoVoltage( ioVols );
	if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	if( PROTOCAL_IIC == pCfg7449->protocalType )
	{
		TestResultInfoR(  _T("pin = low,  int vol = %-6d,	sda vol = %-6d,	scl vol = %-6d\r\n"), ioVols[0][2], ioVols[0][0], ioVols[0][1] );
		TestResultInfoR(  _T("pin = high, int vol = %-6d,	sda vol = %-6d,	scl vol = %-6d\r\n"), ioVols[1][2], ioVols[1][0], ioVols[1][1]);
	}
	else if( PROTOCAL_SPI == pCfg7449->protocalType )
	{
		TestResultInfoR( _T("pin = low,  int vol = %-6d,	csn vol = %-6d,	mosi vol = %-6d,	miso = %-6d,	clk = %-6d\r\n"), ioVols[0][2], ioVols[0][3], ioVols[0][4], ioVols[0][5], ioVols[0][6] );
		TestResultInfoR( _T("pin = high, int vol = %-6d,	csn vol = %-6d,	mosi vol = %-6d,	miso = %-6d,	clk = %-6d\r\n"), ioVols[1][2], ioVols[1][3], ioVols[1][4], ioVols[1][5], ioVols[1][6] );
	}

	if( ioVols[0][2] < pCfg7449->int_low_min || ioVols[0][2] > pCfg7449->int_low_max )
	{
		failerCnt++;
		TestResultInfoR( _T("int vol = %d, th = [%d - %d]\r\n"), ioVols[0][2], pCfg7449->int_low_min, pCfg7449->int_low_max );
	}
	if( ioVols[1][2] < pCfg7449->int_high_min || ioVols[1][2] > pCfg7449->int_high_max )
	{
		failerCnt++;
		TestResultInfoR( _T("int vol = %d, th = [%d - %d]\r\n"), ioVols[1][2], pCfg7449->int_high_min, pCfg7449->int_high_max );
	}

	if( PROTOCAL_IIC == pCfg7449->protocalType )
	{
		if( ioVols[0][0] < pCfg7449->iic_low_min || ioVols[0][0] > pCfg7449->iic_low_max )
		{
			failerCnt++;
			TestResultInfoR( _T("sda vol = %d, th = [%d - %d]\r\n"), ioVols[0][0], pCfg7449->iic_low_min, pCfg7449->iic_low_max );
		}
		if( ioVols[1][0] < pCfg7449->iic_high_min || ioVols[1][0] > pCfg7449->iic_high_max )
		{
			failerCnt++;
			TestResultInfoR( _T("sda vol = %d, th = [%d - %d]\r\n"), ioVols[1][0], pCfg7449->iic_high_min, pCfg7449->iic_high_max );
		}

		if( ioVols[0][1] < pCfg7449->iic_low_min || ioVols[0][1] > pCfg7449->iic_low_max )
		{
			failerCnt++;
			TestResultInfoR( _T("scl vol = %d, th = [%d - %d]\r\n"), ioVols[0][1], pCfg7449->iic_low_min, pCfg7449->iic_low_max );
		}
		if( ioVols[1][1] < pCfg7449->iic_high_min || ioVols[1][1] > pCfg7449->iic_high_max )
		{
			failerCnt++;
			TestResultInfoR( _T("scl vol = %d, th = [%d - %d]\r\n"), ioVols[1][1], pCfg7449->iic_high_min, pCfg7449->iic_high_max );
		}
	}
	else if( PROTOCAL_SPI == pCfg7449->protocalType )
	{
		if( ioVols[0][3] < pCfg7449->spi_low_min || ioVols[0][3] > pCfg7449->spi_low_max )
		{
			failerCnt++;
			TestResultInfoR( _T("csn vol = %d, th = [%d - %d]\r\n"), ioVols[0][3], pCfg7449->spi_low_min, pCfg7449->spi_low_max );
		}
		if( ioVols[1][3] < pCfg7449->spi_high_min || ioVols[1][3] > pCfg7449->spi_high_max )
		{
			failerCnt++;
			TestResultInfoR( _T("csn vol = %d, th = [%d - %d]\r\n"), ioVols[1][3], pCfg7449->spi_high_min, pCfg7449->spi_high_max );
		}

		if( ioVols[0][4] < pCfg7449->spi_low_min || ioVols[0][4] > pCfg7449->spi_low_max )
		{
			failerCnt++;
			TestResultInfoR( _T("mosi vol = %d, th = [%d - %d]\r\n"), ioVols[0][4], pCfg7449->spi_low_min, pCfg7449->spi_low_max );
		}
		if( ioVols[1][4] < pCfg7449->spi_high_min || ioVols[1][4] < pCfg7449->spi_high_max )
		{
			failerCnt++;
			TestResultInfoR( _T("mosi vol = %d, th = [%d - %d]\r\n"), ioVols[1][4], pCfg7449->spi_high_min, pCfg7449->spi_high_max );
		}

		if( ioVols[0][5] < pCfg7449->spi_low_min || ioVols[0][5] > pCfg7449->spi_low_max )
		{
			failerCnt++;
			TestResultInfoR( _T("miso vol = %d, th = [%d - %d]\r\n"), ioVols[0][5], pCfg7449->spi_low_min, pCfg7449->spi_low_max );
		}
		if( ioVols[1][5] < pCfg7449->spi_high_min || ioVols[1][5] < pCfg7449->spi_high_max )
		{
			failerCnt++;
			TestResultInfoR( _T("miso vol = %d, th = [%d - %d]\r\n"), ioVols[1][5], pCfg7449->spi_high_min, pCfg7449->spi_high_max );
		}

		if( ioVols[0][6] < pCfg7449->spi_low_min || ioVols[0][6] > pCfg7449->spi_low_max )
		{
			failerCnt++;
			TestResultInfoR( _T("sclk vol = %d, th = [%d - %d]\r\n"), ioVols[0][6], pCfg7449->spi_low_min, pCfg7449->spi_low_max );
		}
		if( ioVols[1][6] < pCfg7449->spi_high_min || ioVols[1][6] < pCfg7449->spi_high_max )
		{
			failerCnt++;
			TestResultInfoR( _T("sclk vol = %d, th = [%d - %d]\r\n"), ioVols[1][6], pCfg7449->spi_high_min, pCfg7449->spi_high_max );
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
unsigned int CTest7449::Noise_Test( NativeTestItem& itemQuote )
{
	int failerCount = 0;
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );
	signed short diffTempBuffer[MAX_MCAP_CHANNEL * 2] = {0};
	/*unsigned*/ short dataMatrix[MAX_MCAP_ROW][MAX_MCAP_COL];
	const unsigned int iRawDataLen = ((pCfg7449->rowsCnt + 1) * (pCfg7449->colsCnt + 1) * 2 + 3) & 0xfffffffc;
	const unsigned int iScapRawDataLen = pCfg7449->rowsCnt + pCfg7449->colsCnt;
	unsigned short readBuffer[128] = {0};

	TestResultInfo( _T("\r\n------------------------------Noise Test------------------------------\r\n") );

	if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	ISMChip7449* iChip7449 = (ISMChip7449*)SM_ChipBase(m_deviceNo);

	iReCode = iChip7449->GetDifferMax( pCfg7449->noise_frame, diffTempBuffer, iRawDataLen );
	if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	int ref_channel_num = min(pCfg7449->real_channel_num - pCfg7449->va_channel_num, pCfg7449->colsCnt);
	AnalyzeInfo info( pCfg7449->rowsCnt, pCfg7449->colsCnt, ref_channel_num, false );
	ReShappingData</*unsigned*/ short>( dataMatrix, (/*unsigned*/ short*)diffTempBuffer, G_XMLConfig->real_channel_num * 2, pCfg7449->rowsCnt, pCfg7449->colsCnt );

	short noiseMin[MAX_MCAP_ROW][MAX_MCAP_COL], noiseMax[MAX_MCAP_ROW][MAX_MCAP_COL];
	FillMatrixUseValue( noiseMin, (short)0 );
	FillMatrixUseValue( noiseMax, (short)pCfg7449->noise_max );

	NodeVal nodeOutRange;
	ColorText textTemp( _T("\r\nNoise Data:\r\n") );
	bool bResult = AnalyzeTestResult( dataMatrix, noiseMin, noiseMax, pCfg7449->invalid_node, info, textTemp, nodeOutRange, true );
	TestResultInfo( textTemp );
	if( !bResult )
	{
		failerCount++;
		LPCTSTR strHead = _T("\r\n//========= Out of Threshold in NoiseTest: \r\n");
		PrintNodeValue( m_ColorText, &nodeOutRange, strHead );
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
unsigned int CTest7449::Base_Test( NativeTestItem& itemQuote )
{
	int failerCount = 0;
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );
	signed short baseTempBuffer[MAX_MCAP_CHANNEL * 2] = {0};
	/*unsigned*/ short dataMatrix[MAX_MCAP_ROW][MAX_MCAP_COL];
	const unsigned int iRawDataLen = ((pCfg7449->rowsCnt + 1) * (pCfg7449->colsCnt + 1) * 2 + 3) & 0xfffffffc;
	const unsigned int iScapRawDataLen = pCfg7449->rowsCnt + pCfg7449->colsCnt;
	unsigned short readBuffer[128] = {0};

	TestResultInfo( _T("\r\n------------------------------Base Test------------------------------\r\n") );

	if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	ISMChip7449* iChip7449 = (ISMChip7449*)SM_ChipBase(m_deviceNo);

	int addRow = ( pCfg7449->real_channel_num - pCfg7449->va_channel_num ) ? 1 : 0;

	iReCode = iChip7449->IncokeCommand( CMD_CTP_RST );
	SysDelay( 100 );

	iReCode = iChip7449->SwitchMode( MODE_RAWDATA, iRawDataLen );
	if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	SysDelay( 20 );

	for( int index = 0; index < 2; index++ )
	{
		iReCode = iChip7449->GetRawData( baseTempBuffer, iRawDataLen );
		if( iReCode == ERROR_CODE_OK ) break;
		if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	}

	int ref_channel_num = min(pCfg7449->real_channel_num - pCfg7449->va_channel_num, pCfg7449->colsCnt);
	AnalyzeInfo info( pCfg7449->rowsCnt, pCfg7449->colsCnt );
	unsigned short maxCols[] = { pCfg7449->colsCnt, pCfg7449->rowsCnt };
	ReShappingData</*unsigned*/ short>( dataMatrix, (/*unsigned*/ short*)baseTempBuffer + pCfg7449->rowsCnt * pCfg7449->colsCnt, iScapRawDataLen, 2, maxCols );
	//short baseMin[MAX_MCAP_ROW][MAX_MCAP_COL] = {0}, baseMax[MAX_MCAP_ROW][MAX_MCAP_COL] = {0};
	//FillArrayUseValue( baseMin, pCfg7449->base_min );
	//FillArrayUseValue( baseMax, pCfg7449->base_max );

	for(int index = 0; index < pCfg7449->colsCnt; index++)
		dataMatrix[0][index] = (short)(dataMatrix[0][index] * 1024 * 2 / (pCfg7449->scap_rawdata_min[0][index] + pCfg7449->scap_rawdata_max[0][index] + 0.1));
	for(int index = 0; index < pCfg7449->rowsCnt; index++)
		dataMatrix[1][index] = (short)(dataMatrix[1][index] * 1024 * 2 / (pCfg7449->scap_rawdata_min[1][index] + pCfg7449->scap_rawdata_max[1][index] + 0.1));

	short baseMin[MAX_MCAP_ROW][MAX_MCAP_COL], baseMax[MAX_MCAP_ROW][MAX_MCAP_COL];
	FillMatrixUseValue( baseMin, (short)pCfg7449->base_min );
	FillMatrixUseValue( baseMax, (short)pCfg7449->base_max );

	NodeVal nodeOutRange;
	ColorText textTemp( _T("\r\nBase Data:\r\n") );
	bool bResult = AnalyzeTestResultMSCap( dataMatrix, baseMin, baseMax, pCfg7449->invalid_node, info, textTemp, nodeOutRange, true );
	TestResultInfo( textTemp );
	if( !bResult )
	{
		failerCount++;
		LPCTSTR strHead = _T("\r\n//========= Out of Threshold in BaseTest: \r\n");
		PrintNodeValue( m_ColorText, &nodeOutRange, strHead );
	}
	else
	{
		unsigned short base_cnt = 0;
		iReCode = SM_ChipBase(m_deviceNo)->ReadBurnSpace( Addrbase, (unsigned char*)readBuffer, sizeof(readBuffer) );
		if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
		if(readBuffer[0] + readBuffer[1] == 0xffff)
			base_cnt = readBuffer[0];
		base_cnt++;

		for(int index = 0; index < pCfg7449->colsCnt; index++)
			baseTempBuffer[index] = dataMatrix[0][index];
		for(int index = 0; index < pCfg7449->rowsCnt; index++)
			baseTempBuffer[index + pCfg7449->colsCnt] = dataMatrix[1][index];

		unsigned short scap_data_len = (pCfg7449->rowsCnt + pCfg7449->colsCnt) * 2;
		unsigned short checkSum = caculate_check_sum_u16( (unsigned short*)baseTempBuffer, scap_data_len );
		readBuffer[0]  = base_cnt;
		readBuffer[1] = ~base_cnt;
		readBuffer[2] = checkSum;
		readBuffer[3] = ~checkSum;
		memcpy_s( readBuffer + 4, scap_data_len, (unsigned char*)baseTempBuffer, scap_data_len );
		iReCode = SM_ChipBase(m_deviceNo)->WriteBurnSpace( Addrbase, (unsigned char*)readBuffer, sizeof(readBuffer), 0 );
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

unsigned int CTest7449::EnPin_Test( NativeTestItem& itemQuote )
{
	int failerCount = 0;
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );

	TestResultInfo( _T("\r\n------------------------------EnPin Test------------------------------\r\n") );

	if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	ISMChip7449* iChip7449 = (ISMChip7449*)SM_ChipBase(m_deviceNo);


	iReCode = iChip7449->IncokeCommand( CMD_ENPIN_TST );
	//if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	SysDelay( 100 );

	if( iReCode )
	{
		itemNotify.UpdateItemResult( ITEM_STA_FAIL );
		TestResultInfo( "\r\n\r\n//EnPin Test is Fail\r\n", ITEM_STA_FAIL );
	}
	else
	{
		itemNotify.UpdateItemResult( ITEM_STA_PASS );
		TestResultInfo( "\r\n\r\n//EnPin Test is Pass\r\n", ITEM_STA_PASS );
	}

	return itemNotify;
}

unsigned int CTest7449::SetClkInFctMode( unsigned short clkDiv )
{
	return SM_ChipBase(m_deviceNo)->SetClkInFctMode(clkDiv, pCfg7449->filter_off);
}
unsigned int CTest7449::WorkForGraphMode( bool bEnterGraphing /*= false*/ )
{
	unsigned int iReCode = ERROR_CODE_OK;

	if( bEnterGraphing && !IsTestInGraphStep() )
	{
		iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_CTP_RST );
		CHECK_RETURN_IF_FAIL( iReCode );
		SysDelay( 120 );

		iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_SWITCH_IIC );
		CHECK_RETURN_IF_FAIL( iReCode );
		SysDelay( 20 );

		iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_CTP_SET,0x02,0x5c);
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
void CTest7449::PrepareSimulate( SimulateData& sm )
{
	unsigned char cmdID = sm.itemID & 0xff;
	unsigned char dataIndex = (sm.itemID >> 8) & 0xff;
	unsigned char sumCnt = 1;
	int iDesIndex = 0;

	//scap data
	if( sm.itemID == ((0xfa << 16) + 0x28) )
	{
		iDesIndex += pCfg7449->rowsCnt * pCfg7449->colsCnt;
		for( int iCol = 0; iCol <  pCfg7449->colsCnt; iCol++ )
			sm.itemArray[iDesIndex++] = sm.itemData[0][iCol] * sumCnt;
		for( int iCol = 0; iCol < pCfg7449->rowsCnt; iCol++ )
			sm.itemArray[iDesIndex++] = sm.itemData[1][iCol] * sumCnt;
	}
	else
	{
		for( int iRow = 0; iRow < sm.rows; iRow++ )
		{
			for( int iCol = 0; iCol < sm.cols; iCol++ )
			{
				if( iDesIndex >= sizeof(sm.itemArray)/sizeof(short) ) break;

				//int icPosition = pCfg7449->sensor_2_ic_map[index];
				sm.itemArray[iDesIndex++] = sm.itemData[iRow][iCol] * sumCnt;
			}
		}
	}
}

unsigned int CTest7449::MISC_Test( NativeTestItem& itemQuote )
{
	int failerCnt = 0;
	unsigned int iReCode = ERROR_CODE_COMM_ERROR, errCode = 0;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );
	//char tempBuffer[MAX_PATH];

	TestResultInfo( _T("\r\n------------------------------MISC Test------------------------------\r\n") );

	if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	ISMChip7449* iChip7449 = (ISMChip7449*)SM_ChipBase(m_deviceNo);

	unsigned short rsp[8] = {0};
	iReCode = iChip7449->IncokeCommand( CMD_MISC_TST, pCfg7449->misc_mode, 0, 0, (unsigned char*)rsp );
	if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	if(rsp[1])
	{
		failerCnt++;
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
