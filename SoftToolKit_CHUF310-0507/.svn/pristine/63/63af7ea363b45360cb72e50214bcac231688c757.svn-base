#include "checksum.h"
#include "Test8006.h"
#include "../Config/Config8006.h"

#include <list>
//#include <numeric>
extern CConfig* G_XMLConfig;
#define pCfg8006   (( const CConfig8006*)G_XMLConfig)
REGIST_RUNTIME_CLASS(TEST_TYPE, (TEST_TYPE)SEMI_IC_CHGA8006, CTest8006)


CTest8006::CTest8006()
:CTestBase()
{
	Iframes = 0;
	IfristValue = 0;
	Itick = 0;
}
CTest8006::~CTest8006()
{
	
}
void CTest8006::SetTestContext( unsigned char deviceNo, NativeTestInterface* native )
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
		info.bSelected = pCfg8006->mtk_selected;
		info.jumpIfNG = false;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTestBase>( this, &CTestBase::MTKConnectTest );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_TP_WAIT;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("Waiting"), lengthof(_T("Waiting")));
		info.bSelected = pCfg8006->way_to_start == START_BY_AUTO;
		info.jumpIfNG = false;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest8006>( this, &CTest8006::TP_WaitTest );
	}

	//////////////////////////////////////////////////////////////////////////
	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_FRT_TEST_8006;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("FRT"), lengthof(_T("FRT")));
		info.bSelected = pCfg8006->frt_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest8006>( this, &CTest8006::FRT_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_BOOT_TEST;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("Boot"), lengthof(_T("Boot")));
		info.bSelected = pCfg8006->boot_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest8006>( this, &CTest8006::Boot_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_CFG_TEST;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("Config"), lengthof(_T("Config")));
		info.bSelected = pCfg8006->config_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest8006>( this, &CTest8006::Config_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_OSCTRIM_TEST_8006;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("OSCTrim"), lengthof(_T("OSCTrim")));
		info.bSelected = pCfg8006->osctrim_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest8006>( this, &CTest8006::OSCTrim_Test );
	}
	
	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_OS_TEST_8006;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("Short"), lengthof(_T("Short")));
		info.bSelected = pCfg8006->short_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest8006>( this, &CTest8006::Short_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_IOVOL_TEST_8006;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("IOVoltage"), lengthof(_T("IOVoltage")));
		info.bSelected = pCfg8006->iovol_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest8006>( this, &CTest8006::IOVoltage_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_INT_TEST;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("INT"), lengthof(_T("INT")));
		info.bSelected = pCfg8006->int_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest8006>( this, &CTest8006::INT_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_RESET_TEST;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("Reset"), lengthof(_T("Reset")));
		info.bSelected = pCfg8006->reset_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest8006>( this, &CTest8006::Reset_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_PROJECT_CODE;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("Project"), lengthof(_T("Project")));
		info.bSelected = platform_required_sel;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest8006>( this, &CTest8006::ProjectCode_Test );
	}

	//{
	//	InternalItemInfo& info = m_arrayItemInfo[indexSel++];
	//	info.item.ucDevice = m_deviceNo;
	//	info.item.testCode = TEST_ITEM_BASE_TEST_8006;
	//	info.item.testResult = ITEM_STA_NONE;
	//	copytextto(info.item.testName, _T("Base"), lengthof(_T("Base")));
	//	info.bSelected = pCfg8006->base_selected;
	//	if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest8006>( this, &CTest8006::Base_Test );
	//}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_SCAP_RAWDATA_TEST_8006;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("ScapData"), lengthof(_T("ScapData")));
		info.bSelected = pCfg8006->scap_rawdata_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest8006>( this, &CTest8006::ScapRawData_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_STC_8006;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("STC"), lengthof(_T("STC")));
		info.bSelected = pCfg8006->stc_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest8006>( this, &CTest8006::STC_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_MCAP_RAWDATA_8006;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("McapData"), lengthof(_T("McapData")));
		info.bSelected = pCfg8006->mcap_rawdata_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest8006>( this, &CTest8006::MCapRawData_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_NOISE_TEST_8006;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("Noise"), lengthof(_T("Noise")));
		info.bSelected = pCfg8006->noise_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest8006>( this, &CTest8006::Noise_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_BASE_TEST_8006;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("RockerCalib"), lengthof(_T("RockerCalib")));
		info.bSelected = pCfg8006->base_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest8006>( this, &CTest8006::Base_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_SDRockerCalib_TEST_8006;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("SDRockerCalib"), lengthof(_T("SDRockerCalib")));
		info.bSelected = pCfg8006->sdrc_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest8006>( this, &CTest8006::SDRockerCalib_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_CVDIFF_Y_8006;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("CVDiffY"), lengthof(_T("CVDiffY")));
		info.bSelected = pCfg8006->cvdiff_selected_y;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest8006>( this, &CTest8006::CVDiffY_Test );
	}
	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_CVDIFF_X_8006;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("CVDiffX"), lengthof(_T("CVDiffX")));
		info.bSelected = pCfg8006->cvdiff_selected_x;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest8006>( this, &CTest8006::CVDiffX_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_CURRENT_TEST;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("Current"), lengthof(_T("Current")));
		info.bSelected = pCfg8006->current_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest8006>( this, &CTest8006::Current_Test );
	}
	
	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_BUTTON_TEST;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("Button"), lengthof(_T("Button")));
		info.bSelected = pCfg8006->button_selected;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest8006>( this, &CTest8006::Graph_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_LINEARLY_ROCKER_TEST;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("Linearly"), lengthof(_T("Linearly")));
		info.bSelected = pCfg8006->LINEARITY_TEST;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest8006>( this, &CTest8006::Graph_Test );
	}

	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_LINEARLY_ROCKER_TEST;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("FreePaint"), lengthof(_T("FreePaint")));
		info.bSelected = pCfg8006->FREEPAINT_TEST;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest8006>( this, &CTest8006::Graph_Test );
	}

    //////////////////////////////////////////////////////////////////////////
	{
		InternalItemInfo& info = m_arrayItemInfo[indexSel++];
		info.item.ucDevice = m_deviceNo;
		info.item.testCode = TEST_ITEM_TP_REMOVE;
		info.item.testResult = ITEM_STA_NONE;
		copytextto(info.item.testName, _T("Removing"), lengthof(_T("Removing")));
		info.bSelected = pCfg8006->way_to_start == START_BY_AUTO || pCfg8006->way_to_start == START_BY_SN;
		info.jumpIfNG = false;
		if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest8006>( this, &CTest8006::TP_RemoveTest );
	}

	if( SM_ChipBase(m_deviceNo) )
	{
		CtpHalCfg halCfg;
		halCfg.protocalType = (unsigned char)pCfg8006->protocalType;
		halCfg.speed = pCfg8006->Speed;
		halCfg.IIC.slaveAddr = pCfg8006->I2cAddr;
		halCfg.vddVoltage = pCfg8006->vddVotage;
		halCfg.iovddVotage = pCfg8006->ioVddVotage;
		halCfg.vihVotage = pCfg8006->vihVotage;
		halCfg.icType = pCfg8006->IcType;
		SM_ChipBase(m_deviceNo)->SetCommContext( halCfg );
	}

	ActionToXmlConfig();
}
void CTest8006::ICArrayToSensorMatrix( unsigned short (&dataMappinged)[2][MAX_MCAP_COL], unsigned short* const dataToMapping, unsigned int dataCnt, unsigned short maxRows, unsigned short* pMaxCols )
{
	for( int iTx = 0; iTx < pCfg8006->colsCnt; iTx++ )
	{
		unsigned short icChannel = pCfg8006->sensor_2_ic_map[iTx];
		dataMappinged[0][iTx] = dataToMapping[icChannel];
	}
	for( int iRx = 0; iRx < pCfg8006->rowsCnt; iRx++ )
	{
		unsigned short icChannel = pCfg8006->sensor_2_ic_map[iRx + MAX_TX_NUM_5562];
		dataMappinged[1][iRx] = dataToMapping[icChannel + MAX_TX_NUM_5562];
	}
}
// void CTest8006::ICArrayToSensorMatrix( unsigned short (&dataMappinged)[MAX_MCAP_ROW][MAX_MCAP_COL], unsigned short* const dataToMapping, unsigned int dataCnt, unsigned short maxRows, unsigned short maxCols )
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
// 			int icPosition = pCfg8006->sensor_2_ic_map[index];
// 			dataMappinged[iRow][iCol] = dataToMapping[icPosition];
// 		}
// 	}
// 	for( int index = (int)maxRows * maxCols; index < (int)dataCnt; index++ )
// 	{
// 		int iCol = index - maxRows * maxCols + maxCols;
// 		int icPosition = pCfg8006->sensor_2_ic_map[index];
// 		dataMappinged[maxRows - 1][iCol] = dataToMapping[icPosition];
// 	}
// }
// void CTest8006::ICMatrixToSensorMatrix( unsigned short (&dataMappinged)[MAX_MCAP_ROW][MAX_MCAP_COL],
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
// 			if( index >= (int)pCfg8006->real_channel_num )   continue;
// 
// 			int icPosition = pCfg8006->sensor_2_ic_map[index];
// 			int icRow = icPosition / mappingCol;
// 			int icCol = icPosition % mappingCol;
// 
// 			dataMappinged[iRow][iCol] = dataToMapping[icRow][icCol];
// 		}
// 	}
// }
// void CTest8006::SensorMatrixToIcMatrix( unsigned short (&dataMappinged)[MAX_MCAP_ROW][MAX_MCAP_COL],
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
// // 		    int sensorPos = pCfg8006->ic_2_sensor_map[index] - 1;
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
// 			if( index >= (int)pCfg8006->real_channel_num )   continue;
// 
// 			int icPosition = pCfg8006->sensor_2_ic_map[index];
// 			int icRow = icPosition / mappedCol;
// 			int icCol = icPosition % mappedCol;
// 
// 			dataMappinged[icRow][icCol] = dataToMapping[iRow][iCol];
// 		}
// 	}
// }
BOOL CTest8006::CheckTpBootSame( )
{
	BOOL bCheckBootOk = FALSE;
	unsigned int iReCode = ERROR_CODE_OK;
	ISMChip8006* iChip8006 = (ISMChip8006*)SM_ChipBase(m_deviceNo);
	if( NULL == iChip8006 )   return FALSE;

	unsigned int crc_from_tp = 0, otm_time = 0;
	iReCode = iChip8006->GetBootCheckSum( &crc_from_tp, &otm_time );
	if( iReCode != ERROR_CODE_OK )  return FALSE;

	//TCHAR szBuffer[MAX_PATH] = {0};
	//transformat( szBuffer, _T("ID = 0x%x,   %d-%d, %d:%d:%d"), otm_time, (otm_time>>22)&0xf, (otm_time>>17)&0x1f,(otm_time>>12)&0x1f, (otm_time>>6)&0x3f, otm_time&0x3f );
	//TestResultInfo( szBuffer );
	TestResultInfoR( _T("ID = 0x%x,   %d-%d, %d:%d:%d"), otm_time, (otm_time>>22)&0xf, (otm_time>>17)&0x1f,(otm_time>>12)&0x1f, (otm_time>>6)&0x3f, otm_time&0x3f );
	
	if( crc_from_tp == pCfg8006->boot_check_sum )
		return TRUE;

	return FALSE;
}
BOOL CTest8006::CheckFlashEraseOk()
{
	unsigned int iReCode = ERROR_CODE_OK;
	ISMChip8006* iChip8006 = (ISMChip8006*)SM_ChipBase(m_deviceNo);
	if( NULL == iChip8006 )  return FALSE;

	unsigned char readBuffer[4096] = {0};
	unsigned int writeData = 0x5ee5e55e, readData = 0x00000000;
	iReCode = iChip8006->WriteBurnSpace( 0xd000, (const unsigned char*)&writeData, sizeof(writeData), OTP_W_CHK | TLK_DATACHK_EX1 );
	if( iReCode != ERROR_CODE_OK ) return FALSE;

	iReCode = iChip8006->ReadBurnSpace( 0xd000, (unsigned char*)&readData, sizeof(writeData) );
	if( iReCode != ERROR_CODE_OK ) return FALSE;

	if( writeData != readData )
	{
		TestResultInfo( _T("Check Erase Falsh step 1 Failed\r\n") );
		return FALSE;
	}

	writeData = 0xe55e5ee5, readData = 0x00000000;
	iReCode = iChip8006->WriteBurnSpace( 0xd000, (const unsigned char*)&writeData, sizeof(writeData), OTP_W_CHK | TLK_DATACHK_EX1 );
	if( iReCode != ERROR_CODE_OK ) return FALSE;

	iReCode = iChip8006->ReadBurnSpace( 0xd000, (unsigned char*)&readData, sizeof(writeData) );
	if( iReCode != ERROR_CODE_OK ) return FALSE;

	if( writeData != readData )
	{
		TestResultInfo( _T("Check Erase Falsh step 2 Failed\r\n") );
		return false;
	}

	writeData = 0xffffffff;
	iReCode = iChip8006->WriteBurnSpace( 0xd000, (const unsigned char*)&writeData, sizeof(writeData), OTP_W_CHK | TLK_DATACHK_EX1 );
	if( iReCode != ERROR_CODE_OK ) return FALSE;

	iReCode = iChip8006->ReadBurnSpace( 0xd000, readBuffer, sizeof(readBuffer) );
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
	iReCode = iChip8006->ReadBurnSpace( 0xc000, readBuffer, 8 );
	if( iReCode != ERROR_CODE_OK ) return FALSE;

	UINT32* pIntData = (UINT32*)readBuffer;
	if( 0xffffffff == pIntData[0] && 0xffffffff == pIntData[1] )
	{
		SYSTEMTIME SysTime;
		::GetLocalTime(&SysTime);
		pIntData[0] = (SysTime.wMonth << 22) + (SysTime.wDay << 17) + (SysTime.wHour << 12) + (SysTime.wMinute << 6) + SysTime.wSecond;
		pIntData[1] = GetTickCount();
		iChip8006->WriteBurnSpace( 0xc000, readBuffer, 8, OTP_W_CHK | TLK_DATACHK_EX1 );
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
unsigned int CTest8006::Boot_Test( NativeTestItem& itemQuote )
{
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );

	TestResultInfo( _T("\r\n------------------------------BOOT Test------------------------------\r\n") );

	ISMChip8006* iChip8006 = (ISMChip8006*)SM_ChipBase(m_deviceNo);
	if( NULL == iChip8006 )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	unsigned short booVerFromTp = 0;
	iReCode = iChip8006->GetBootVersion( &booVerFromTp );
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
		if( pCfg8006->boot_only_check )
		{
			TestResultInfo( _T("\r\nBoot from tp is differant from setting\r\n") );
			//TestResultInfo( szBootVer );
			auto szBootVer = TestResultInfoR( _T("Ver=0x%x"), booVerFromTp );
			TestResultInfo( "\r\n\r\n//BOOT Test is Fail\r\n", ITEM_STA_FAIL );
			itemNotify.UpdateItemResult( ITEM_STA_FAIL, szBootVer );
		}
		else
		{
			//SM_CommBase(m_deviceNo)->SetIoVoltage(0x6E, pCfg8006->vddVotage == pCfg8006->ioVddVotage ? 0x6E : pCfg8006->ioVddVotage);
			//SysDelay(50);

			TestResultInfo( _T("\r\nDownlad new boot bin...\r\n") );
			iReCode = iChip8006->BurnBootBin( pCfg8006->bootBinSize, pCfg8006->boot_svn, m_stOneRecord.Mcap.oscTrim );
			if( iReCode == ERROR_CODE_OK )   
			{
				/*unsigned short */booVerFromTp = 0;
				iReCode = iChip8006->GetBootVersion( &booVerFromTp );
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

			//SM_CommBase(m_deviceNo)->SetIoVoltage(pCfg8006->vddVotage, pCfg8006->ioVddVotage);
			//SysDelay(50);
		}
	}

	return itemNotify;
}
BOOL CTest8006::CheckConfigSame( const unsigned char* pCfg, unsigned short len )
{
	if( len != pCfg8006->cfgBinSize ) return FALSE;

	unsigned int iReCode = ERROR_CODE_OK;
	ISMChip8006* iChip8006 = (ISMChip8006*)SM_ChipBase(m_deviceNo);
	if( NULL == iChip8006 )   return FALSE;

	unsigned int check = caculate_check_sum_u16( (unsigned short*)pCfg, len );
	if( check != 0 )
	{
		return FALSE;
	}

	for( int index = 0; index < len; index++ ) 
	{
		if( pCfg[index] != pCfg8006->cfgBinBuffer[index] )
			return FALSE;
	}

	return TRUE;
}
unsigned int CTest8006::MakeTraceRecord()
{
	unsigned int iReCode = ERROR_CODE_OK;
#ifdef _MSC_VER
	ISMChip8006* iChip8006 = (ISMChip8006*)SM_ChipBase(m_deviceNo);
	//char szBuffer[MAX_PATH] = {0};
	unsigned char record_buffer[3*1024] = {0};
	//auto record_buffer = new unsigned char[2*1024];
	Trace_Info* traceInfo = (Trace_Info*)record_buffer;
	One_Record* record = (One_Record*)(record_buffer + sizeof(Trace_Info));
	tstring userInfo = pCfg8006->szUserRecord ? tstring(pCfg8006->szUserRecord) : _T("");
	unsigned short crc = caculate_check_sum_ex( (unsigned char*)userInfo.c_str(), userInfo.length() + 1 ) >> 16;

	iReCode = iChip8006->ReadBurnSpace( AddrMakeTraceRecord, record_buffer, sizeof(Trace_Info) );
	if(iReCode != ERROR_CODE_OK) return iReCode;

	BOOL bExitSameUserRecord = FALSE;
	if(traceInfo->trace_cnt + traceInfo->reverse == 0xff)
	{
		traceInfo->tlen =  traceInfo->tlen >= 0x800 ? 0x800 : traceInfo->tlen ;
		iReCode = iChip8006->ReadBurnSpace( AddrMakeTraceRecord + sizeof(Trace_Info), (unsigned char*)record, traceInfo->tlen );
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
		record->vid_pid = pCfg8006->vid_pid;
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

		iReCode = iChip8006->WriteBurnSpace(AddrMakeTraceRecord, record_buffer, traceInfo->tlen + sizeof(Trace_Info), OTP_W_CHK | TLK_DATACHK_EX1);
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
unsigned int CTest8006::ProjectCode_Test( NativeTestItem& itemQuote )
{
	unsigned int iReCode = ERROR_CODE_OK;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );

	TestResultInfo( _T("\r\n------------------------------Project Test------------------------------\r\n") );

	//MakeTraceRecord();

	ISMChip8006* iChip8006 = (ISMChip8006*)SM_ChipBase(m_deviceNo);
	if( NULL == iChip8006 )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_CTP_RST );
	if( iReCode != ERROR_CODE_OK ) itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	SysDelay( 50 );

	unsigned char chipFamily = GetContainerInterface()->GetChipFamily( G_XMLConfig->IcType );
	SM_ChipBase(m_deviceNo)->IncokeCommand(CMD_CHK_CFG, 0, (chipFamily << 8) | G_XMLConfig->I2cAddr, (G_XMLConfig->Speed << 8) | G_XMLConfig->protocalType);

	iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_SWITCH_IIC );
	if( iReCode != ERROR_CODE_OK ) itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_IDENTITY );
	if( iReCode != ERROR_CODE_OK ) itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	unsigned short cfgBuffer[MAX_CFG_BIN_SIZE] = {0};
	iReCode = SM_ChipBase(m_deviceNo)->ReadCoreSpace( 0x20000000 + 0x1c, (unsigned char*)cfgBuffer, pCfg8006->cfgBinSize );
	if( iReCode != ERROR_CODE_OK ) itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	TCHAR chTemp[MAX_PATH] = {0};
	unsigned short s = cfgBuffer[1] >> 10;
	unsigned short p = (((cfgBuffer[1] >> 4) & 0x03) << 9) | (cfgBuffer[0] & 0x1ff);
	unsigned short v = (((cfgBuffer[1] >> 6) & 0x03) << 7) | (cfgBuffer[0] >> 9);
	//transformat( chTemp, _T("SoftWare Ver = %d, ProjectCode = %d, VenderID = %d\r\n"), s, p, v );
	//TestResultInfo( chTemp );
	TestResultInfoR( _T("SoftWare Ver = %d, ProjectCode = %d, VenderID = %d\r\n"), s, p, v );

	transformat( chTemp, _T("S=%d, P=%d, V=%d"), s, p, v );

	if( pCfg8006->sVersion == s && pCfg8006->pVersion == p && pCfg8006->vVersion == v )
	{
		if(pCfg8006->cfgTestBinSize)
		{
			iReCode = iChip8006->SetConfigInFctMode( (unsigned char*)pCfg8006->cfgTestBinBuffer, pCfg8006->cfgTestBinSize );
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

		////frequecy lockdown
		//iReCode = iChip8006->IncokeCommand(CMD_CTP_FREQ, 3, 1);
		//itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

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
unsigned int CTest8006::Config_Test( NativeTestItem& itemQuote )
{
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );

	TestResultInfo( _T("\r\n------------------------------CONFIG Test------------------------------\r\n") );

	ISMChip8006* iChip8006 = (ISMChip8006*)SM_ChipBase(m_deviceNo);
	if( NULL == iChip8006 )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	unsigned short cfgVerFromTp = 0;
	unsigned char configBuffer[204] = {0};
	iReCode = iChip8006->GetFirmWareConfig( configBuffer, pCfg8006->cfgBinSize );
	if( ERROR_CODE_OK != iReCode )  return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	cfgVerFromTp = configBuffer[3] >> 2;
	//TCHAR szConfigVer[MAX_PATH] = {0};
	//transformat( szConfigVer, _T("Ver=0x%x"), cfgVerFromTp );

	BOOL bSameConfig = CheckConfigSame( configBuffer, pCfg8006->cfgBinSize );

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
		if( pCfg8006->config_only_check )
		{
			TestResultInfo( _T("\r\nConfig from tp is differant from setting\r\n") );
			//TestResultInfo( szConfigVer );
			auto szConfigVer = TestResultInfoR( _T("Ver=0x%x"), cfgVerFromTp );
			TestResultInfo( "\r\n\r\n//Config Test is Fail\r\n", ITEM_STA_FAIL );
			itemNotify.UpdateItemResult( ITEM_STA_FAIL, szConfigVer );
		}
		else
		{
			//SM_CommBase(m_deviceNo)->SetIoVoltage(0x6E, pCfg8006->vddVotage == pCfg8006->ioVddVotage ? 0x6E : pCfg8006->ioVddVotage);
			//SysDelay(50);

			TestResultInfo( _T("\r\nDownlad new config bin...\r\n") );
			iReCode = iChip8006->BurnConfigBin( pCfg8006->cfgBinBuffer, pCfg8006->cfgBinSize );
			if( iReCode == ERROR_CODE_OK )   
			{
				memset( configBuffer, 0, sizeof(configBuffer) );
				iChip8006->GetFirmWareConfig( configBuffer, pCfg8006->cfgBinSize );
				BOOL bSameConfig2 = CheckConfigSame( configBuffer, pCfg8006->cfgBinSize );

				cfgVerFromTp = configBuffer[3] >> 2;
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

			//SM_CommBase(m_deviceNo)->SetIoVoltage(pCfg8006->vddVotage, pCfg8006->ioVddVotage);
			//SysDelay(50);
		}
	}

	return itemNotify;
}


typedef struct _ois_chip_calib_
{
	unsigned char  osc_trim64;   
	unsigned char  osc_trim64_v;  
	unsigned char  osc_trim32;    
	unsigned char  osc_trim32_v;  
	unsigned char  data[4];      
	unsigned long long ICID;     
	unsigned long long  vid_pid;  
	unsigned char  data1[4];      
	unsigned short  tag;          
	unsigned short checksum;     
}ois_chip_calib;

unsigned int CTest8006::OSCTrim_Test( NativeTestItem& itemQuote )
{
	int failerCnt = 0;
	unsigned int iReCode = ERROR_CODE_OK;

	ISMChip8006* iChip8006 = (ISMChip8006*)SM_ChipBase(m_deviceNo);
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );
	bool NeedOsCTrim = false;

	TestResultInfo( _T("\r\n------------------------------OSC Trim Test------------------------------\r\n") );

	unsigned int osTrim32k = 0, osTrim64m = 0;
	unsigned char readBuffer[1024] = {0};
	unsigned char readBuffer_36k[1024] = {0};

	iReCode = SM_ChipBase(m_deviceNo)->ReadBurnSpace( TCP_CALIBA_ADDR_8006, readBuffer, sizeof(readBuffer) ); 
	if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	ois_chip_calib* ois_calib = (ois_chip_calib*)readBuffer;

	if(0 == caculate_check_sum_u16( (unsigned short*)readBuffer,sizeof(ois_chip_calib )))
	{
		osTrim32k = readBuffer[2];
		osTrim64m = readBuffer[0];
	}
	else
	{
		NeedOsCTrim = true;
	}

	if(NeedOsCTrim || 0xff != (readBuffer[1] + readBuffer[0]) //true || 
		|| 0xff != (readBuffer[2] + readBuffer[3])
		|| osTrim64m < pCfg8006->trim_64m_min
		|| osTrim64m > pCfg8006->trim_64m_max 
		|| osTrim32k < pCfg8006->trim_32k_min
		|| osTrim32k > pCfg8006->trim_32k_max)
	{
		TestResultInfo( _T("Start Trim And Refresh Trim Value\r\n") );

		iReCode = SM_ChipBase(m_deviceNo)->ReadBurnSpace( VCM_ATE_RC_ADDR, readBuffer_36k, sizeof(readBuffer_36k) ); 
		if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

		unsigned int osc_trim_64   = *(unsigned int *)&readBuffer_36k[96];
		unsigned int osc_trim_64_v = *(unsigned int *)&readBuffer_36k[100];
		unsigned int osc_trim_32   = *(unsigned int *)&readBuffer_36k[104];
		unsigned int osc_trim_32_v = *(unsigned int *)&readBuffer_36k[108];

		if((0xffffffff==( osc_trim_64 + osc_trim_64_v ))&&(0xffffffff==( osc_trim_32 + osc_trim_32_v )))
		{
			osTrim64m = osc_trim_64 & 0xff;
			osTrim32k = osc_trim_32 & 0xff;

			if((osTrim32k < pCfg8006->trim_32k_min)||(osTrim32k > pCfg8006->trim_32k_max)||(osTrim64m < pCfg8006->trim_64m_min)||(osTrim64m > pCfg8006->trim_64m_max))
			{
				iReCode = iChip8006->GetOSCTrim( (unsigned char*)&osTrim32k, (unsigned char*)&osTrim64m, pCfg8006->tick_32k_standard, pCfg8006->tick_64m_standard);
				if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
			}
		}
		else
		{
			iReCode = iChip8006->GetOSCTrim( (unsigned char*)&osTrim32k, (unsigned char*)&osTrim64m, pCfg8006->tick_32k_standard, pCfg8006->tick_64m_standard);
			if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

			TestResultInfoR( _T("ATE OSCTrim Defect"));
		}

		if( osTrim32k < pCfg8006->trim_32k_min )
			failerCnt++;
		else if( osTrim32k > pCfg8006->trim_32k_max )
			failerCnt++;
		else if( osTrim64m < pCfg8006->trim_64m_min )
			failerCnt++;
		else if( osTrim64m > pCfg8006->trim_64m_max )
			failerCnt++;

		if(failerCnt == 0)
		{
			ois_calib->osc_trim64    = osTrim64m;
			ois_calib->osc_trim64_v  = ~ois_calib->osc_trim64;
			ois_calib->osc_trim32    = osTrim32k;
			ois_calib->osc_trim32_v = ~ois_calib->osc_trim32;
		}

		//Gen ICID
		unsigned int* pIntData = (unsigned int*)&ois_calib->ICID;
		unsigned short* pShortData = (unsigned short*)&ois_calib->ICID;
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

		//vid_pid
		ois_calib->vid_pid = pCfg8006->vid_pid;

		ois_calib->tag = 0x8006;

		ois_calib->checksum = 1 + ~caculate_check_sum_u16( (unsigned short*)ois_calib, sizeof(ois_chip_calib) - 2 );
		
		memcpy_s( readBuffer, sizeof(ois_chip_calib), ois_calib, sizeof(ois_chip_calib) );
		
		iReCode = SM_ChipBase(m_deviceNo)->WriteBurnSpace( TCP_CALIBA_ADDR_8006, readBuffer, sizeof(readBuffer), OTP_W_CHK | TLK_DATACHK_EX1 );
		if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
		
	}

	m_stOneRecord.ReleaseID = *(UINT64*)&ois_calib->ICID;
	UINT32 otm_time = *(UINT32*)&m_stOneRecord.ReleaseID;
	//transformat( szBuffer, _T("ICID = 0x%llx,   %d-%d, %d:%d:%d\r\n"), m_stOneRecord.ReleaseID, (otm_time>>22)&0xf, (otm_time>>17)&0x1f,(otm_time>>12)&0x1f, (otm_time>>6)&0x3f, otm_time&0x3f );
	//TestResultInfo( szBuffer );
	TestResultInfoR( _T("ICID = 0x%llx,   %d-%d, %d:%d:%d\r\n"), ois_calib->ICID, (otm_time>>22)&0xf, (otm_time>>17)&0x1f,(otm_time>>12)&0x1f, (otm_time>>6)&0x3f, otm_time&0x3f );

	m_stOneRecord.Mcap.oscTrim = *((unsigned int*)readBuffer);

	auto szBuffer = TestResultInfoR( _T("32K = 0x%02x, 64M=0x%02x"), osTrim32k, osTrim64m );

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
unsigned int CTest8006::Current_Test( NativeTestItem& itemQuote )
{
	TEST_ITEM_STATUS itemStatus = ITEM_STA_NONE;
	for( int index = 0; index < 3; index++ )
	{
		itemStatus = (TEST_ITEM_STATUS)Current_TestEx( itemQuote );
		if( itemStatus == ITEM_STA_PASS ) break;
	}
	return itemStatus;
}
unsigned int CTest8006::Current_TestEx( NativeTestItem& itemQuote )
{
	int failedCount = 0;
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );

	TestResultInfo( _T("\r\n------------------------------Current Test------------------------------\r\n") );

	ISMChip8006* iChip8006 = (ISMChip8006*)SM_ChipBase(m_deviceNo);
	if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	short deepCurrent = 0, sleepCurrent = 0, activeCurrent = 0, idleCurrent = 0;
	short vbus_deepCurrent = 0, vbus_sleepCurrent = 0, vbus_activeCurrent = 0;
	short level[2][3] = {
		pCfg8006->active_current_min, pCfg8006->sleep_current_min, pCfg8006->deep_current_min,
		pCfg8006->active_current_max, pCfg8006->sleep_current_max, pCfg8006->deep_current_max,
	};
	//iReCode = iChip8006->GetCurrent( level, (unsigned short*)&activeCurrent, (unsigned short*)&sleepCurrent, (unsigned short*)&deepCurrent, (unsigned short*)&idleCurrent );
	iReCode = iChip8006->GetCurrent8006( level, (unsigned short*)&activeCurrent, (unsigned short*)&sleepCurrent, (unsigned short*)&deepCurrent,(unsigned short*)&vbus_activeCurrent, (unsigned short*)&vbus_sleepCurrent, (unsigned short*)&vbus_deepCurrent);
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
		TestResultInfoR( _T("\r\navdd_active = %d(uA), avdd_sleep = %d(uA)\r\n"), activeCurrent, sleepCurrent);
		//TestResultInfoR( _T("\r\nvbus_active = %d(uA), vbus_sleep = %d(uA), vbus_deep = %d(uA)\r\n"), vbus_activeCurrent, vbus_sleepCurrent, vbus_deepCurrent);
	}
	if( activeCurrent < pCfg8006->active_current_min )
	{
		failedCount++;
		//transformat( szTmep, _T( "\r\nactive(%d) < setting min(%d)\r\n"), activeCurrent, pCfg8006->active_current_min );
		//TestResultInfo( szTmep );
		TestResultInfoR( _T( "\r\nactive(%d) < setting min(%d)\r\n"), activeCurrent, pCfg8006->active_current_min );
	}
	if( activeCurrent > pCfg8006->active_current_max )
	{
		failedCount++;
		//transformat( szTmep, _T( "\r\nactive(%d) > setting max(%d)\r\n"), activeCurrent, pCfg8006->active_current_max );
		//TestResultInfo( szTmep );
		TestResultInfoR( _T( "\r\nactive(%d) > setting max(%d)\r\n"), activeCurrent, pCfg8006->active_current_max );
	}
	if( sleepCurrent < pCfg8006->sleep_current_min )
	{
		failedCount++;
		//transformat( szTmep, _T( "\r\nsleep(%d) < setting min(%d)\r\n"), sleepCurrent, pCfg8006->sleep_current_min );
		//TestResultInfo( szTmep );
		TestResultInfoR( _T( "\r\nsleep(%d) < setting min(%d)\r\n"), sleepCurrent, pCfg8006->sleep_current_min );
	}
	if( sleepCurrent > pCfg8006->sleep_current_max )
	{
		failedCount++;
		//transformat( szTmep, _T( "\r\nsleep(%d) > setting max(%d)\r\n"), sleepCurrent, pCfg8006->sleep_current_max );
		//TestResultInfo( szTmep );
		TestResultInfoR( _T( "\r\nsleep(%d) > setting max(%d)\r\n"), sleepCurrent, pCfg8006->sleep_current_max );
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

unsigned int CTest8006::ScapRawData_Test( NativeTestItem& itemQuote )
{
	int failerCount = 0;
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );
	signed short baseTempBuffer[MAX_MCAP_CHANNEL * 2] = {0};
	/*unsigned*/ short dataMatrix[MAX_MCAP_ROW][MAX_MCAP_COL];
	const unsigned int iRawDataLen = ((pCfg8006->rowsCnt + 1) * (pCfg8006->colsCnt + 1) * 2 + 3) & 0xfffffffc;
	const unsigned int iScapRawDataLen = pCfg8006->rowsCnt + pCfg8006->colsCnt;

	TestResultInfo( _T("\r\n------------------------------ScapData Test------------------------------\r\n") );

	if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	ISMChip8006* iChip8006 = (ISMChip8006*)SM_ChipBase(m_deviceNo);

	int addRow = ( pCfg8006->real_channel_num - pCfg8006->va_channel_num ) ? 1 : 0;

	//iReCode = iChip8006->IncokeCommand( 0x05,0x02,0x5c);
	SysDelay( 100 );

	iReCode = iChip8006->SwitchMode( MODE_RAWDATA, iRawDataLen   );
	if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	SysDelay( 20 );

	for( int index = 0; index < 2; index++ )
	{
		iReCode = iChip8006->GetRawData( baseTempBuffer, iRawDataLen  );
		//if( iReCode == ERROR_CODE_OK ) break;
		if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	}

	int ref_channel_num = min(pCfg8006->real_channel_num - pCfg8006->va_channel_num, pCfg8006->colsCnt);
	AnalyzeInfo info( pCfg8006->rowsCnt, pCfg8006->colsCnt );
	unsigned short maxCols[] = { pCfg8006->colsCnt, pCfg8006->rowsCnt };
	ReShappingData</*unsigned*/ short>( dataMatrix, (/*unsigned*/ short*)baseTempBuffer + pCfg8006->rowsCnt * pCfg8006->colsCnt, iScapRawDataLen, 2, maxCols );
	//short baseMin[MAX_MCAP_ROW][MAX_MCAP_COL] = {0}, baseMax[MAX_MCAP_ROW][MAX_MCAP_COL] = {0};
	//FillArrayUseValue( baseMin, pCfg8006->base_min );
	//FillArrayUseValue( baseMax, pCfg8006->base_max );

	NodeVal nodeOutRange;
	ColorText textTemp( _T("\r\nScap Data:\r\n") );
	bool bResult = AnalyzeTestResultMSCap( dataMatrix, pCfg8006->scap_rawdata_min, pCfg8006->scap_rawdata_max, pCfg8006->invalid_node, info, textTemp, nodeOutRange, true );
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
typedef struct _rockerXY
{
	unsigned short X;
	unsigned short Y;
	_rockerXY()
	{
		X = 0;
		Y = 0;

	}
}RockerXY;
typedef struct _pointXY
{
	unsigned short X;
	unsigned short Y;
	
}PointXY;

typedef struct _pointData
{

	unsigned int Data;

}PointData;

typedef struct _pointAgreement
{
	unsigned char data[4];
	unsigned char chk;
	unsigned char type_id;
}PointAgreement;

unsigned int CTest8006::CVDiffY_Test( NativeTestItem& itemQuote )
{
	int failerCount = 0;
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );
	unsigned int times = 0;
	unsigned char baseTempBuffer[100]={0};
	unsigned short bufferLen = 84;
	RockerXY centerXY;
	RockerXY currentXY;
	RockerXY minXY;
	RockerXY maxXY;
	RockerXY s1;
	RockerXY s0;
	unsigned int complet_flag = 0;

	bool posdirection = true;
	unsigned short firstframe_x = 0;
	unsigned short firstframe_y = 0;

	PointAgreement* pagreement = (PointAgreement*)baseTempBuffer;

	TestResultInfo( _T("\r\n------------------------------CVDiffY Test------------------------------\r\n") );

	if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	ISMChip8006* iChip8006 = (ISMChip8006*)SM_ChipBase(m_deviceNo);

	iReCode = iChip8006->IncokeCommand( CMD_CTP_RST );

	SysDelay( 40 );

	//iReCode = iChip8006->IncokeCommand( CMD_SWITCH_IIC );

	if( iReCode != ERROR_CODE_OK ) itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	iReCode = SM_ChipBase(m_deviceNo)->SwitchMode( MODE_TOUCH, 8);
	if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	//SysDelay( 20 );

	for( int index = 0; index < 2; index++ )
	{
		iReCode = iChip8006->GetTouchPoint( baseTempBuffer, &bufferLen );
		if( iReCode == ERROR_CODE_OK ) break;
		if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	}
	if(pagreement->type_id==0)
	{
		centerXY.X = pagreement->data[0]<<8|pagreement->data[1];
		centerXY.Y = pagreement->data[2]<<8|pagreement->data[3];

		if(1 == pCfg8006->is_xy_reverse)
		{
			unsigned short tmp = centerXY.X;
			centerXY.X = centerXY.Y;
			centerXY.Y = tmp;
		}

		if (1 == pCfg8006->is_x_reverse)
		{
			centerXY.X = pCfg8006->resolution_x - centerXY.X;
		}

		if (1 == pCfg8006->is_y_reverse)
		{
			centerXY.Y = pCfg8006->resolution_y - centerXY.Y;
		}

	}
	else if(pagreement->type_id==1)
	{
		centerXY.X =0;
		centerXY.Y = pagreement->data[0]<<8|pagreement->data[1];
	}
	
	//minXY.X = maxXY.X = centerXY.X;
	//minXY.Y = maxXY.Y = centerXY.Y;
	auto resolution_y_2 = (pCfg8006->resolution_y)/2;
	itemNotify.UpdateItemResult( ITEM_STA_WAIT, "");

	while(times <= pCfg8006->time_out_frames_y)
	{
		times++;
		iReCode = iChip8006->GetTouchPoint( baseTempBuffer, &bufferLen );
		if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
		
		if(pagreement->type_id==0)
		{
			currentXY.X = pagreement->data[0]<<8|pagreement->data[1];
			currentXY.Y = pagreement->data[2]<<8|pagreement->data[3];

			if(1 == pCfg8006->is_xy_reverse)
			{
				unsigned short tmp = currentXY.X;
				currentXY.X = currentXY.Y;
				currentXY.Y = tmp;
			}

			if (1 == pCfg8006->is_x_reverse)
			{
				currentXY.X = pCfg8006->resolution_x - currentXY.X;
			}

			if (1 == pCfg8006->is_y_reverse)
			{
				currentXY.Y = pCfg8006->resolution_y - currentXY.Y;
			}

		}
		else if(pagreement->type_id==1)
		{
			currentXY.X =0;
			currentXY.Y = pagreement->data[0]<<8|pagreement->data[1];
		}

		if (times == 1)
		{
			firstframe_x = currentXY.X;
			firstframe_y = currentXY.Y;
		}

		if( complet_flag == 0)
		{
			if(currentXY.Y - firstframe_y > pCfg8006->point_range_y)
			{
				posdirection = false;
				complet_flag = 1;
			}
			if(firstframe_y - currentXY.Y > pCfg8006->point_range_y)
			{
				posdirection = true;
				complet_flag = 1;
			}
			continue;
		}

		if( complet_flag == 1)
		{
			if (posdirection == true)
			{
				auto ret = Judgmentconditions(pCfg8006->stabl_frames_y, currentXY.Y, 0, pCfg8006->p_min_y + pCfg8006->base_proportion_value ,pCfg8006->shake_range_y);//+ 2*pCfg8006->point_range_y
				if(ret == true)
				{
					minXY.X = currentXY.X;
					minXY.Y = currentXY.Y;
					complet_flag = 2;
					times = 0;
					itemNotify.UpdateItemResult( ITEM_STA_WAIT, "0" );	
				}
			}
			else
			{
				auto ret = Judgmentconditions(pCfg8006->stabl_frames_y, currentXY.Y, pCfg8006->p_max_y - pCfg8006->base_proportion_value, pCfg8006->resolution_y, pCfg8006->shake_range_y);//-2*pCfg8006->point_range_y
				if(ret == true )
				{

					maxXY.X = currentXY.X;
					maxXY.Y = currentXY.Y;
					complet_flag = 2;
					times = 0;
					itemNotify.UpdateItemResult( ITEM_STA_WAIT, "0" );	
				}
			}
	

			continue;
		}

		if (complet_flag == 2)
		{
			if((currentXY.Y <= (resolution_y_2 + 2*pCfg8006->point_range_y))&&(currentXY.Y >= (resolution_y_2 - 2*pCfg8006->point_range_y)))
			{
				complet_flag = 3;
				times = 0;
				itemNotify.UpdateItemResult( ITEM_STA_START, "1" );	
			}

			continue;

		}

		if (complet_flag == 3)
		{
			//auto ret = Judgmentconditions(pCfg8006->stabl_frames_y, currentXY.Y, currentXY.Y,currentXY.Y,pCfg8006->shake_range_y );
			auto ret = Judgmentconditions(pCfg8006->stabl_frames_y, currentXY.Y, resolution_y_2 - pCfg8006->point_range_y,resolution_y_2 + pCfg8006->point_range_y ,pCfg8006->shake_range_y );
			if(ret == true)
			{
				s0.X = currentXY.X;
				s0.Y = currentXY.Y;
				complet_flag = 4;
				times = 0;
				itemNotify.UpdateItemResult( ITEM_STA_WAIT, "2" );	
			}
			continue;

		}

		if (complet_flag == 4)
		{
			if (posdirection == true)
			{
				auto ret = Judgmentconditions(pCfg8006->stabl_frames_y, currentXY.Y, pCfg8006->p_max_y - pCfg8006->base_proportion_value, pCfg8006->resolution_y, pCfg8006->shake_range_y);//-2*pCfg8006->point_range_y
				if(ret == true )
				{

					maxXY.X = currentXY.X;
					maxXY.Y = currentXY.Y;
					complet_flag = 5;
					times = 0;
					itemNotify.UpdateItemResult( ITEM_STA_WAIT, "3" );	
				}
			
			}
			else
			{
				auto ret = Judgmentconditions(pCfg8006->stabl_frames_y, currentXY.Y, 0, pCfg8006->p_min_y + pCfg8006->base_proportion_value ,pCfg8006->shake_range_y);//+ 2*pCfg8006->point_range_y
				if(ret == true)
				{
					minXY.X = currentXY.X;
					minXY.Y = currentXY.Y;
					complet_flag = 5;
					times = 0;
					itemNotify.UpdateItemResult( ITEM_STA_WAIT, "3" );	
				}
			
			}

			continue;
		}

		if (complet_flag == 5)
		{
			if((currentXY.Y <= (resolution_y_2 + 2*pCfg8006->point_range_y))&&(currentXY.Y >= (resolution_y_2 - 2*pCfg8006->point_range_y)))
			{
				complet_flag = 6;
				times = 0;
				itemNotify.UpdateItemResult( ITEM_STA_START, "4" );	
			}

			continue;

		}

		if (complet_flag == 6)
		{
			//auto ret = Judgmentconditions(pCfg8006->stabl_frames_y, currentXY.Y, currentXY.Y,currentXY.Y,pCfg8006->shake_range_y );
			auto ret = Judgmentconditions(pCfg8006->stabl_frames_y, currentXY.Y, resolution_y_2 - pCfg8006->point_range_y, resolution_y_2 + pCfg8006->point_range_y , pCfg8006->shake_range_y );
			if(ret == true)
			{
				s1.X = currentXY.X;
				s1.Y = currentXY.Y;
				complet_flag = 7;
				times = 0;
				itemNotify.UpdateItemResult( ITEM_STA_WAIT, "5" );	
			}
			continue;

		}
		if (complet_flag == 7)
		{
			//complet_flag = 0;
			break; 
		}

	}
	if(complet_flag!=0)
	{
		float ratio_y_div = (((float)(maxXY.Y - minXY.Y)))<=0?1:(((float)(maxXY.Y - minXY.Y)));
		float ratio_y = ((float)(abs(s1.Y - s0.Y)))/ratio_y_div*1000;
		float ratio_y1 = ((float)(abs(s1.Y - s0.Y)))/ratio_y_div*100;
		float ratio_resolution_y = ((float)(abs(s1.Y - s0.Y)))/pCfg8006->resolution_y*100;
		float ratio_real = ((float)(abs(s1.Y - s0.Y)))/(pCfg8006->resolution_y-2*pCfg8006->base_proportion_value)*100;

		TestResultInfoR(_T("\r\nYMin=%d(%.1f%%)\r\n"),minXY.Y, ((float)(minXY.Y))/((float)pCfg8006->resolution_y)*100);
		TestResultInfoR(_T("\r\nYCMin=%d(%.1f%%)\r\n"),s0.Y, ((float)(s0.Y)/ ((float)pCfg8006->resolution_y))*100);
		TestResultInfoR(_T("\r\nYMax=%d(%.1f%%)\r\n"),maxXY.Y, ((float)(maxXY.Y)/ ((float)pCfg8006->resolution_y))*100);
		TestResultInfoR(_T("\r\nYCMax=%d(%.1f%%)\r\n"),s1.Y, ((float)(s1.Y)/ ((float)pCfg8006->resolution_y))*100);
		TestResultInfoR(_T("\r\nYABS=%d(%.1f%%)\r\n"),abs(s1.Y - s0.Y), ratio_y1);
		TestResultInfoR(_T("\r\nYABS(pixel)=%d(%.1f%%)\r\n"),abs(s1.Y - s0.Y), ratio_resolution_y);
		TestResultInfoR(_T("\r\nYABS(theory)=%d(%.1f%%)\r\n"),abs(s1.Y - s0.Y), ratio_real);
		TestResultInfoR(_T("\r\nEffectiveStroke=%.1f\r\n"), (((float)(maxXY.Y - minXY.Y))));
		TestResultInfoR(_T("\r\nTheoryStroke=%.1f\r\n"), (float)(pCfg8006->resolution_y-2*pCfg8006->base_proportion_value));

		if(ratio_y > pCfg8006->cv_diff_ratio_y||(maxXY.Y - minXY.Y) < (pCfg8006->resolution_y*0.7)||s1.Y<(pCfg8006->resolution_y*0.3)||s0.Y<(pCfg8006->resolution_y*0.3))
		{
			failerCount++;

		}
	
	}
	else
	{
		TestResultInfoR(_T("\r\ntime out\r\n"));
		failerCount++;
	}

	if( failerCount )
	{
		itemNotify.UpdateItemResult( ITEM_STA_FAIL );
		TestResultInfo( "\r\n\r\n//CVDiffY Test is Fail\r\n", ITEM_STA_FAIL );
	}
	else
	{
		itemNotify.UpdateItemResult( ITEM_STA_PASS );
		TestResultInfo( "\r\n\r\n//CVDiffY Test is Pass\r\n", ITEM_STA_PASS );
	}

	return itemNotify;
}

unsigned int CTest8006::CVDiffX_Test(NativeTestItem& itemQuote)
{
	int failerCount = 0;
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );
	unsigned int times = 0;
	unsigned char baseTempBuffer[100]={0};
	unsigned short bufferLen = 84;
	RockerXY centerXY;
	RockerXY currentXY;
	RockerXY minXY;
	RockerXY maxXY;
	RockerXY s1;
	RockerXY s0;
	unsigned int complet_flag = 0;

	bool posdirection = true;
	unsigned short firstframe_x = 0;
	unsigned short firstframe_y = 0;

	TestResultInfo( _T("\r\n------------------------------CVDiffX Test------------------------------\r\n") );

	if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	ISMChip8006* iChip8006 = (ISMChip8006*)SM_ChipBase(m_deviceNo);

	iReCode = iChip8006->IncokeCommand( CMD_CTP_RST );

	SysDelay( 20 );

	iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_SWITCH_IIC );
	if( iReCode != ERROR_CODE_OK ) itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	iReCode = SM_ChipBase(m_deviceNo)->SwitchMode( MODE_TOUCH, 8);
	if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	//SysDelay( 20 );

	for( int index = 0; index < 2; index++ )
	{
		iReCode = iChip8006->GetTouchPoint( baseTempBuffer, &bufferLen );
		if( iReCode == ERROR_CODE_OK ) break;
		if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	}

	centerXY.X = baseTempBuffer[0]<<8|baseTempBuffer[1];
	centerXY.Y = baseTempBuffer[2]<<8|baseTempBuffer[3];

	if(1 == pCfg8006->is_xy_reverse)
	{
		unsigned short tmp = centerXY.X;
		centerXY.X = centerXY.Y;
		centerXY.Y = tmp;
	}

	if (1 == pCfg8006->is_x_reverse)
	{
		centerXY.X = pCfg8006->resolution_x - centerXY.X;
	}

	if (1 == pCfg8006->is_y_reverse)
	{
		centerXY.Y = pCfg8006->resolution_y - centerXY.Y;
	}

	//minXY.X = maxXY.X = centerXY.X;
	//minXY.Y = maxXY.Y = centerXY.Y;
	auto resolution_x_2 = (pCfg8006->resolution_x)/2;
	itemNotify.UpdateItemResult( ITEM_STA_WAIT, "");	
	while(times <= pCfg8006->time_out_frames_x)
	{
		times++;
		iReCode = iChip8006->GetTouchPoint( baseTempBuffer, &bufferLen );
		if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

		currentXY.X = baseTempBuffer[0]<<8|baseTempBuffer[1];
		currentXY.Y = baseTempBuffer[2]<<8|baseTempBuffer[3];

		if(1 == pCfg8006->is_xy_reverse)
		{
			unsigned short tmp = currentXY.X;
			currentXY.X = currentXY.Y;
			currentXY.Y = tmp;
		}

		if (1 == pCfg8006->is_x_reverse)
		{
			currentXY.X = pCfg8006->resolution_x - currentXY.X;
		}

		if (1 == pCfg8006->is_y_reverse)
		{
			currentXY.Y = pCfg8006->resolution_y - currentXY.Y;
		}

		if (times == 1)
		{
			firstframe_x = currentXY.X;
			firstframe_y = currentXY.Y;
		}

		if( complet_flag == 0)
		{
			if(currentXY.X - firstframe_x > pCfg8006->point_range_x)
			{
				posdirection = false;
				complet_flag = 1;
			}
			if(firstframe_x - currentXY.X > pCfg8006->point_range_x)
			{
				posdirection = true;
				complet_flag = 1;
			}
			continue;
		}

		if( complet_flag == 1)
		{
			if (posdirection == true)
			{
				auto ret = Judgmentconditions(pCfg8006->stabl_frames_x, currentXY.X, 0, pCfg8006->p_min_x + pCfg8006->base_proportion_value ,pCfg8006->shake_range_x);//+ 2*pCfg8006->point_range_x
				if(ret == true)
				{
					minXY.X = currentXY.X;
					minXY.Y = currentXY.Y;
					complet_flag = 2;
					times = 0;
					itemNotify.UpdateItemResult( ITEM_STA_WAIT, "0" );	
				}
			} 
			else
			{
				auto ret = Judgmentconditions(pCfg8006->stabl_frames_x, currentXY.X, pCfg8006->p_max_x - pCfg8006->base_proportion_value, pCfg8006->resolution_x, pCfg8006->shake_range_x);//-2*pCfg8006->point_range_x
				if(ret == true)
				{

					maxXY.X = currentXY.X;
					maxXY.Y = currentXY.Y;
					complet_flag = 2;
					times = 0;
					itemNotify.UpdateItemResult( ITEM_STA_WAIT, "0" );	
				}
			}

			continue;
		}

		if (complet_flag == 2)
		{
			if((currentXY.X <= (resolution_x_2 + 2*pCfg8006->point_range_x))&&(currentXY.X >= (resolution_x_2 - 2*pCfg8006->point_range_x)))
			{
				complet_flag = 3;
				times = 0;
				itemNotify.UpdateItemResult( ITEM_STA_START, "1" );	
			}

			continue;

		}

		if (complet_flag == 3)
		{

			auto ret = Judgmentconditions(pCfg8006->stabl_frames_x, currentXY.X, resolution_x_2 - pCfg8006->point_range_x, resolution_x_2 + pCfg8006->point_range_x ,pCfg8006->shake_range_x );
			if(ret == true)
			{
				s0.X = currentXY.X;
				s0.Y = currentXY.Y;
				complet_flag = 4;
				times = 0;
				itemNotify.UpdateItemResult( ITEM_STA_WAIT, "2" );	
			}
			continue;

		}

		if (complet_flag == 4)
		{
			if (posdirection == true)
			{
				auto ret = Judgmentconditions(pCfg8006->stabl_frames_x, currentXY.X, pCfg8006->p_max_x - pCfg8006->base_proportion_value, pCfg8006->resolution_x, pCfg8006->shake_range_x);//-2*pCfg8006->point_range_x
				if(ret == true)
				{

					maxXY.X = currentXY.X;
					maxXY.Y = currentXY.Y;
					complet_flag = 5;
					times = 0;
					itemNotify.UpdateItemResult( ITEM_STA_WAIT, "3" );	
				}
			
			}
			else
			{
				auto ret = Judgmentconditions(pCfg8006->stabl_frames_x, currentXY.X, 0, pCfg8006->p_min_x + pCfg8006->base_proportion_value ,pCfg8006->shake_range_x);//+ 2*pCfg8006->point_range_x
				if(ret == true)
				{
					minXY.X = currentXY.X;
					minXY.Y = currentXY.Y;
					complet_flag = 5;
					times = 0;
					itemNotify.UpdateItemResult( ITEM_STA_WAIT, "3" );	
				}
			}

			continue;
		}

		if (complet_flag == 5)
		{
			if((currentXY.X <= (resolution_x_2 + 2*pCfg8006->point_range_x))&&(currentXY.X >= (resolution_x_2 - 2*pCfg8006->point_range_x)))
			{
				complet_flag = 6;
				times = 0;
				itemNotify.UpdateItemResult( ITEM_STA_START, "4" );	
			}

			continue;

		}

		if (complet_flag == 6)
		{

			auto ret = Judgmentconditions(pCfg8006->stabl_frames_x, currentXY.X, resolution_x_2 - pCfg8006->point_range_x,resolution_x_2 + pCfg8006->point_range_x ,pCfg8006->shake_range_x );
			if(ret == true)
			{
				s1.X = currentXY.X;
				s1.Y = currentXY.Y;
				complet_flag = 7;
				times = 0;
				itemNotify.UpdateItemResult( ITEM_STA_WAIT, "5" );	
			}
			continue;

		}
		if (complet_flag == 7)
		{
			//complet_flag = 0;
			break; 
		}

	}
	if(complet_flag!=0)
	{
		float ratio_x_div = (((float)(maxXY.X - minXY.X))) <=0 ? 1 : (((float)(maxXY.X - minXY.X)));
		float ratio_x = ((float)(abs(s1.X - s0.X)))/ratio_x_div*1000;
		float ratio_x1 = ((float)(abs(s1.X - s0.X)))/ratio_x_div*100;
		float ratio_resolution_x = ((float)(abs(s1.X - s0.X)))/pCfg8006->resolution_x*100;
		float ratio_real = ((float)(abs(s1.X - s0.X)))/(pCfg8006->resolution_x-2*pCfg8006->base_proportion_value)*100;

		TestResultInfoR(_T("\r\nXMin=%d(%.1f%%)\r\n"),minXY.X, ((float)(minXY.X))/((float)pCfg8006->resolution_x)*100);
		TestResultInfoR(_T("\r\nXCMin=%d(%.1f%%)\r\n"),s0.X, ((float)(s0.X)/ ((float)pCfg8006->resolution_x))*100);
		TestResultInfoR(_T("\r\nXMax=%d(%.1f%%)\r\n"),maxXY.X, ((float)(maxXY.X)/ ((float)pCfg8006->resolution_x))*100);
		TestResultInfoR(_T("\r\nXCMax=%d(%.1f%%)\r\n"),s1.X, ((float)(s1.X)/ ((float)pCfg8006->resolution_x))*100);
		TestResultInfoR(_T("\r\nXABS=%d(%.1f%%)\r\n"),abs(s1.X - s0.X), ratio_x1);
		TestResultInfoR(_T("\r\nXABS(pixel)=%d(%.1f%%)\r\n"),abs(s1.X - s0.X), ratio_resolution_x);
		TestResultInfoR(_T("\r\nXABS(theory)=%d(%.1f%%)\r\n"),abs(s1.X - s0.X), ratio_real);

		TestResultInfoR(_T("\r\nEffectiveStroke=%.1f\r\n"), (((float)(maxXY.X - minXY.X))));
		TestResultInfoR(_T("\r\nTheoryStroke=%.1f\r\n"), (float)(pCfg8006->resolution_x-2*pCfg8006->base_proportion_value));

		if(ratio_x > pCfg8006->cv_diff_ratio_x||(maxXY.X - minXY.X) < (pCfg8006->resolution_y*0.7)||s1.X<(pCfg8006->resolution_y*0.3)||s0.X<(pCfg8006->resolution_y*0.3))
		{
			failerCount++;

		}

	}
	else
	{
		TestResultInfoR(_T("\r\ntime out\r\n"));
		failerCount++;
	}

	if( failerCount )
	{
		itemNotify.UpdateItemResult( ITEM_STA_FAIL );
		TestResultInfo( "\r\n\r\n//CVDiffX Test is Fail\r\n", ITEM_STA_FAIL );
	}
	else
	{
		itemNotify.UpdateItemResult( ITEM_STA_PASS );
		TestResultInfo( "\r\n\r\n//CVDiffX Test is Pass\r\n", ITEM_STA_PASS );
	}

	return itemNotify;

}

unsigned int CTest8006::STC_Test( NativeTestItem& itemQuote )
{
	int failerCount = 0;
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );
	signed short baseTempBuffer[MAX_MCAP_CHANNEL * 2] = {0};
	signed int baseSum[MAX_MCAP_CHANNEL * 2] = {0};
	/*unsigned*/ short baseMatrix[MAX_MCAP_ROW][MAX_MCAP_COL], uniformityMin[MAX_MCAP_ROW][MAX_MCAP_COL];
	const unsigned int iRawDataLen = ((pCfg8006->rowsCnt) * (pCfg8006->colsCnt) * 2 + 3) & 0xfffffffc;
	const unsigned int iRetry = 20;

	TestResultInfo( _T("\r\n------------------------------STC Test------------------------------\r\n") );

	if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	ISMChip8006* iChip8006 = (ISMChip8006*)SM_ChipBase(m_deviceNo);

	int addRow = ( pCfg8006->real_channel_num - pCfg8006->va_channel_num ) ? 1 : 0;
	memset( uniformityMin, 0, sizeof(uniformityMin) );

	//iReCode = iChip8006->IncokeCommand( CMD_CTP_RST );
	//SysDelay( 100 );

	//iReCode = iChip8006->SetClkInFctMode( pCfg8006->stc_clk_div, false );
	//if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	//SysDelay( 20 );

	iReCode = iChip8006->SwitchMode( MODE_RAWDATA, iRawDataLen );
	if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	SysDelay( 20 );

	memset( baseSum, 0, sizeof(baseSum) );
	for( int index = 0; index < iRetry; index++ )
	{
		iReCode = iChip8006->GetRawData( baseTempBuffer, iRawDataLen );
		if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

		if(0 == index) continue;
		ArrayAddtion( baseSum, baseTempBuffer, iRawDataLen );
	}
	ArrayAverage( baseTempBuffer, baseSum, iRawDataLen, iRetry - 1);

	int ref_channel_num = min(pCfg8006->real_channel_num - pCfg8006->va_channel_num, pCfg8006->colsCnt);
	AnalyzeInfo info( pCfg8006->rowsCnt, pCfg8006->colsCnt, ref_channel_num, false );
	ReShappingData</*unsigned*/ short>( baseMatrix, (/*unsigned*/ short*)baseTempBuffer, G_XMLConfig->real_channel_num * 2, pCfg8006->rowsCnt, pCfg8006->colsCnt );
	//short baseMin[MAX_MCAP_ROW][MAX_MCAP_COL] = {0}, baseMax[MAX_MCAP_ROW][MAX_MCAP_COL] = {0};
	//FillArrayUseValue( baseMin, pCfg8006->base_min );
	//FillArrayUseValue( baseMax, pCfg8006->base_max );

	{
		NodeVal nodeOutRange;
		ColorText textTemp( _T("\r\nstc_rawdata:\r\n") );
		short baseMin[MAX_MCAP_ROW][MAX_MCAP_COL] = {0}, baseMax[MAX_MCAP_ROW][MAX_MCAP_COL] = {0};
		FillMatrixUseValue<short>( baseMax, 30000 );
		bool bResult = AnalyzeTestResult( baseMatrix, baseMin, baseMax, pCfg8006->invalid_node, info, textTemp, nodeOutRange, true );
		TestResultInfo( textTemp );
	}

	{
		NodeVal nodeOutRange;
		ColorText textTemp( _T("\r\nstc_deviation:\r\n") );
		for( int iRow = 0; iRow < pCfg8006->rowsCnt; iRow++ )
		{
			for( int iCol = 0; iCol < pCfg8006->colsCnt; iCol++ )
			{
				int deviation = 10 * abs( baseMatrix[iRow][iCol] - pCfg8006->stc_mean[iRow][iCol] );
				baseMatrix[iRow][iCol] = (short)(100 * deviation / (deviation + 3 * pCfg8006->stc_mse[iRow][iCol] + 0.001));
			}
		}
			
				
		short stcMin[MAX_MCAP_ROW][MAX_MCAP_COL] = {0}, stcMax[MAX_MCAP_ROW][MAX_MCAP_COL] = {0};
		FillMatrixUseValue( stcMin, pCfg8006->stc_min );
		FillMatrixUseValue( stcMax, pCfg8006->stc_max );
		bool bResult = AnalyzeTestResult( baseMatrix, stcMin, stcMax, pCfg8006->invalid_node, info, textTemp, nodeOutRange, true );
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
// 		CopyAndInvalid( uniformityHorInvalid, pCfg8006->invalid_node, 0, MAX_MCAP_COL );
// 		GenHorizontalConvolution( baseMatrix, uniformityHorMatrix, pCfg8006->rowsCnt, pCfg8006->colsCnt );
// 		bool bResult = AnalyzeTestResult( uniformityHorMatrix, uniformityMin, pCfg8006->stc_uniformity_h, uniformityHorInvalid, info, textTemp, nodeOutRange, true );
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
// 		CopyAndInvalid( uniformityVerInvalid, pCfg8006->invalid_node, MAX_MCAP_ROW, 0 );
// 		GenVerticalConvolution( baseMatrix, uniformityVerMatrix, pCfg8006->rowsCnt, pCfg8006->colsCnt );
// 		bool bResult = AnalyzeTestResult( uniformityVerMatrix, uniformityMin, pCfg8006->stc_uniformity_v, uniformityVerInvalid, info, textTemp, nodeOutRange, true );
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
unsigned int CTest8006::MCapRawData_Test( NativeTestItem& itemQuote )
{
	int failerCount = 0;
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );
	signed short baseTempBuffer[MAX_MCAP_CHANNEL * 2] = {0};
	signed int baseSum[MAX_MCAP_CHANNEL * 2] = {0};
	/*unsigned*/ short baseMatrix[MAX_MCAP_ROW][MAX_MCAP_COL], uniformityMin[MAX_MCAP_ROW][MAX_MCAP_COL];
	short NormalizationMatrix[MAX_MCAP_ROW][MAX_MCAP_COL];
	const unsigned int iRawDataLen = ((pCfg8006->rowsCnt) * (pCfg8006->colsCnt) * 2 + 3) & 0xfffffffc;
	const unsigned int iRetry = 20;

	TestResultInfo( _T("\r\n------------------------------MCap RawData Test------------------------------\r\n") );

	if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	ISMChip8006* iChip8006 = (ISMChip8006*)SM_ChipBase(m_deviceNo);

	int addRow = ( pCfg8006->real_channel_num - pCfg8006->va_channel_num ) ? 1 : 0;
	memset( uniformityMin, 0, sizeof(uniformityMin) );

	/*iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_CTP_RST );
	if( iReCode != ERROR_CODE_OK ) itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	SysDelay( 20 );

	iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_SWITCH_IIC );
	if( iReCode != ERROR_CODE_OK ) itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_IDENTITY );
	if( iReCode != ERROR_CODE_OK ) itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );*/

	iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_ROCKER_CALIB,(0), 0,0);
	if( iReCode != ERROR_CODE_OK ) itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	iReCode = iChip8006->SwitchMode( MODE_RAWDATA, iRawDataLen );
	if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	//SysDelay( 20 );

	memset( baseSum, 0, sizeof(baseSum) );
	for( int index = 0; index < iRetry; index++ )
	{
		iReCode = iChip8006->GetRawData( baseTempBuffer, iRawDataLen );
		if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

		if(0 == index) continue;
		ArrayAddtion( baseSum, baseTempBuffer, iRawDataLen );
	}
	ArrayAverage( baseTempBuffer, baseSum, iRawDataLen, iRetry - 1);

	int ref_channel_num = min(pCfg8006->real_channel_num - pCfg8006->va_channel_num, pCfg8006->colsCnt);
	AnalyzeInfo info( pCfg8006->rowsCnt, pCfg8006->colsCnt, ref_channel_num, false );
	ReShappingData</*unsigned*/ short>( baseMatrix, (/*unsigned*/ short*)baseTempBuffer, G_XMLConfig->real_channel_num * 2, pCfg8006->rowsCnt, pCfg8006->colsCnt );
	//short baseMin[MAX_MCAP_ROW][MAX_MCAP_COL] = {0}, baseMax[MAX_MCAP_ROW][MAX_MCAP_COL] = {0};
	//FillArrayUseValue( baseMin, pCfg8006->base_min );
	//FillArrayUseValue( baseMax, pCfg8006->base_max );

	ColorText textTempa( _T("\r\nmcap_rawdata:\r\n") );
	PrintMaxtrixValue( textTempa, baseMatrix,pCfg8006->invalid_node, info, true );
	TestResultInfo( textTempa );
	Copy_RawData<MAX_MCAP_ROW,MAX_MCAP_COL>(NormalizationMatrix, baseMatrix, pCfg8006->rowsCnt, pCfg8006->colsCnt);

	auto pioce = 1.0f;
	RawData_Normalization<MAX_MCAP_ROW,MAX_MCAP_COL>(NormalizationMatrix,pCfg8006->mcap_rawdata_min, pCfg8006->mcap_rawdata_max,pCfg8006->rowsCnt, pCfg8006->colsCnt,pCfg8006->macp_normalization_ratio_min,pCfg8006->macp_normalization_ratio_max,pioce);

	TestResultInfoR(_T("\r\nnormalization_constant = %.2f, min =%.2f, max= %.2f\r\n"),pioce,pCfg8006->macp_normalization_ratio_min,pCfg8006->macp_normalization_ratio_max );

	{
		NodeVal nodeOutRange;
		ColorText textTemp( _T("\r\nmcap_normalization:\r\n") );
		bool bResult = AnalyzeTestResult( NormalizationMatrix, pCfg8006->mcap_rawdata_min, pCfg8006->mcap_rawdata_max, pCfg8006->invalid_node, info, textTemp, nodeOutRange, true );
		TestResultInfo( textTemp );
		if( !bResult )
		{
			failerCount++;
			LPCTSTR strHead = _T("\r\n//========= Out of Threshold in MCap RawData Test: \r\n");
			PrintNodeValue( m_ColorText, &nodeOutRange, strHead );
		}
	}
	
	if(pCfg8006->check_uniformity_hor)
	{
		NodeVal nodeOutRange;
		ColorText textTemp( _T("\r\nmcap_uniformity_h:\r\n") );
		short uniformityHorMatrix[MAX_MCAP_ROW][MAX_MCAP_COL];
		unsigned char uniformityHorInvalid[MAX_MCAP_ROW][MAX_MCAP_COL];
		CopyAndInvalid( uniformityHorInvalid, pCfg8006->invalid_node, 0, MAX_MCAP_COL );
		GenHorizontalUniformity( NormalizationMatrix, uniformityHorMatrix, pCfg8006->rowsCnt, pCfg8006->colsCnt );
		bool bResult = AnalyzeTestResult( uniformityHorMatrix, uniformityMin, pCfg8006->mcap_uniformity_h, uniformityHorInvalid, info, textTemp, nodeOutRange, true );
		TestResultInfo( textTemp );
		if( !bResult )
		{
			failerCount++;
			LPCTSTR strHead = _T("\r\n//========= Out of Threshold in MCap Uniformity-H: \r\n");
			PrintNodeValue( m_ColorText, &nodeOutRange, strHead );
		}
	}

	if(pCfg8006->check_uniformity_ver)
	{
		NodeVal nodeOutRange;
		ColorText textTemp( _T("\r\nmcap_uniformity_v:\r\n") );
		short uniformityVerMatrix[MAX_MCAP_ROW][MAX_MCAP_COL];
		unsigned char uniformityVerInvalid[MAX_MCAP_ROW][MAX_MCAP_COL];
		CopyAndInvalid( uniformityVerInvalid, pCfg8006->invalid_node, MAX_MCAP_ROW, 0 );
		GenVerticalUniformity( NormalizationMatrix, uniformityVerMatrix, pCfg8006->rowsCnt, pCfg8006->colsCnt );
		bool bResult = AnalyzeTestResult( uniformityVerMatrix, uniformityMin, pCfg8006->mcap_uniformity_v, uniformityVerInvalid, info, textTemp, nodeOutRange, true );
		TestResultInfo( textTemp );
		if( !bResult )
		{
			failerCount++;
			LPCTSTR strHead = _T("\r\n//========= Out of Threshold in MCap Uniformity-V: \r\n");
			PrintNodeValue( m_ColorText, &nodeOutRange, strHead );
		}
	}

	auto sampling = Judge_RawData_sampling<MAX_MCAP_ROW,MAX_MCAP_COL>(pCfg8006->mcap_rawdata_min, pCfg8006->mcap_rawdata_max,pCfg8006->invalid_node,pCfg8006->rowsCnt, pCfg8006->colsCnt,pCfg8006->rawdata_min_value,pCfg8006->rawdata_max_value);
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
unsigned int CTest8006::Short_Test( NativeTestItem& itemQuote )
{
	
	int failerCount = 0;
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );
	const int max_short_adc_num = (20+42);
	unsigned short shortAdc[max_short_adc_num] = {0};
	unsigned short adcMatrix[2][MAX_MCAP_COL] = {0};
	AnalyzeInfo info( pCfg8006->rowsCnt, pCfg8006->colsCnt, 0, false );

	TestResultInfo( _T("\r\n------------------------------Short Test------------------------------\r\n") );

	if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	ISMChip8006* iChip8006 = (ISMChip8006*)SM_ChipBase(m_deviceNo);

	iReCode = iChip8006->IncokeCommand(CMD_CTP_RST);
	SysDelay( 500 );

	iReCode = iChip8006->GetShortData( shortAdc, max_short_adc_num * 2 );
	if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	unsigned short maxCols[] = { pCfg8006->colsCnt, pCfg8006->rowsCnt };
	ICArrayToSensorMatrix( adcMatrix, shortAdc, max_short_adc_num, 2, maxCols );

	NodeVal nodeOutRange;
	unsigned short adcMin[2][MAX_MCAP_COL] = {0};
	unsigned short adcMax[2][MAX_MCAP_COL] = {0}; 
	ColorText textTemp( _T("\r\nShort Data:\r\n") );
	FillMatrixUseValue( adcMin, (unsigned short)0 );
	FillMatrixRowUseValue( adcMax, pCfg8006->short_tx_max, 0 );
	FillMatrixRowUseValue( adcMax, pCfg8006->short_rx_max, 1 );
	adcMax[0][6] = 1300;
	bool bResult = AnalyzeTestResultMSCap<unsigned short>( adcMatrix, adcMin, adcMax, pCfg8006->invalid_node, info, textTemp, nodeOutRange, true );
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
		itemNotify.UpdateItemResult( ITEM_STA_PASS );
		TestResultInfo( "\r\n\r\n//Short Test is Pass\r\n", ITEM_STA_PASS );
	}

	return itemNotify;
}
unsigned int CTest8006::FRT_Test( NativeTestItem& itemQuote )
{
	int failerCnt = 0;
	unsigned int iReCode = ERROR_CODE_COMM_ERROR, errCode = 0;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );
	unsigned char retBuffer[20];
	//char tempBuffer[MAX_PATH];

	TestResultInfo( _T("\r\n------------------------------FRT Test------------------------------\r\n") );

	if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	ISMChip8006* iChip8006 = (ISMChip8006*)SM_ChipBase(m_deviceNo);

	iReCode = iChip8006->IncokeCommand( CMD_RAM_TST, 0, 0, 0, retBuffer );
	if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	errCode = *(unsigned int*)&retBuffer[2];
	if(0x54000000 != errCode)
	{
		failerCnt++;
		//transformat( tempBuffer, _T("ReadCoreSpace, Code = 0x%x\r\n"), errCode );
		//TestResultInfo( tempBuffer );
		TestResultInfoR( _T("ReadCoreSpace, Code = 0x%x\r\n"), errCode );
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
unsigned int CTest8006::IOVoltage_Test( NativeTestItem& itemQuote )
{
	int failerCnt = 0;
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );
	//TCHAR szTemp[MAX_PATH] = {0};

	TestResultInfo( _T("\r\n------------------------------IOVoltage Test------------------------------\r\n") );

	if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	ISMChip8006* iChip8006 = (ISMChip8006*)SM_ChipBase(m_deviceNo);

	unsigned int ioVols[2][10] = {0};
	iReCode = iChip8006->GetIoVoltage( ioVols );
	if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	if( PROTOCAL_IIC == pCfg8006->protocalType )
	{
		//transformat( szTemp, _T("pin = low,  int vol = %-6d,	sda vol = %-6d,	scl vol = %-6d\r\n"), ioVols[0][2], ioVols[0][0], ioVols[0][1] );
		//TestResultInfo( szTemp );
		TestResultInfoR( _T("pin = low,  int vol = %-6d,	sda vol = %-6d,	scl vol = %-6d\r\n"), ioVols[0][2], ioVols[0][0], ioVols[0][1] );
		//transformat( szTemp, _T("pin = high, int vol = %-6d,	sda vol = %-6d,	scl vol = %-6d\r\n"), ioVols[1][2], ioVols[1][0], ioVols[1][1] );
		//TestResultInfo( szTemp );
		TestResultInfoR( _T("pin = high, int vol = %-6d,	sda vol = %-6d,	scl vol = %-6d\r\n"), ioVols[1][2], ioVols[1][0], ioVols[1][1] );
	}
	else if( PROTOCAL_SPI == pCfg8006->protocalType )
	{
		//transformat( szTemp, _T("pin = low,  int vol = %-6d,	csn vol = %-6d,	mosi vol = %-6d,	miso = %-6d,	clk = %-6d\r\n"), ioVols[0][2], ioVols[0][3], ioVols[0][4], ioVols[0][5], ioVols[0][6] );
		//TestResultInfo( szTemp );
		TestResultInfoR( _T("pin = low,  int vol = %-6d,	csn vol = %-6d,	mosi vol = %-6d,	miso = %-6d,	clk = %-6d\r\n"), ioVols[0][2], ioVols[0][3], ioVols[0][4], ioVols[0][5], ioVols[0][6] );
		//transformat( szTemp, _T("pin = high, int vol = %-6d,	csn vol = %-6d,	mosi vol = %-6d,	miso = %-6d,	clk = %-6d\r\n"), ioVols[1][2], ioVols[1][3], ioVols[1][4], ioVols[1][5], ioVols[1][6] );
		//TestResultInfo( szTemp );
		TestResultInfoR( _T("pin = high, int vol = %-6d,	csn vol = %-6d,	mosi vol = %-6d,	miso = %-6d,	clk = %-6d\r\n"), ioVols[1][2], ioVols[1][3], ioVols[1][4], ioVols[1][5], ioVols[1][6] );
	}

	if( ioVols[0][2] < pCfg8006->int_low_min || ioVols[0][2] > pCfg8006->int_low_max )
	{
		failerCnt++;
		//transformat( szTemp, _T("int vol = %d, th = [%d - %d]\r\n"), ioVols[0][2], pCfg8006->int_low_min, pCfg8006->int_low_max );
		//TestResultInfo( szTemp );
		TestResultInfoR( _T("int vol = %d, th = [%d - %d]\r\n"), ioVols[0][2], pCfg8006->int_low_min, pCfg8006->int_low_max );
	}
	if( ioVols[1][2] < pCfg8006->int_high_min || ioVols[1][2] > pCfg8006->int_high_max )
	{
		failerCnt++;
		//transformat( szTemp, _T("int vol = %d, th = [%d - %d]\r\n"), ioVols[1][2], pCfg8006->int_high_min, pCfg8006->int_high_max );
		//TestResultInfo( szTemp );
		TestResultInfoR( _T("int vol = %d, th = [%d - %d]\r\n"), ioVols[1][2], pCfg8006->int_high_min, pCfg8006->int_high_max );
	}

	if( PROTOCAL_IIC == pCfg8006->protocalType )
	{
		if( ioVols[0][0] < pCfg8006->iic_low_min || ioVols[0][0] > pCfg8006->iic_low_max )
		{
			failerCnt++;
			//transformat( szTemp, _T("sda vol = %d, th = [%d - %d]\r\n"), ioVols[0][0], pCfg8006->iic_low_min, pCfg8006->iic_low_max );
			//TestResultInfo( szTemp );
			TestResultInfoR( _T("sda vol = %d, th = [%d - %d]\r\n"), ioVols[0][0], pCfg8006->iic_low_min, pCfg8006->iic_low_max);
		}
		if( ioVols[1][0] < pCfg8006->iic_high_min || ioVols[1][0] > pCfg8006->iic_high_max )
		{
			failerCnt++;
			//transformat( szTemp, _T("sda vol = %d, th = [%d - %d]\r\n"), ioVols[1][0], pCfg8006->iic_high_min, pCfg8006->iic_high_max );
			//TestResultInfo( szTemp );
			TestResultInfoR( _T("sda vol = %d, th = [%d - %d]\r\n"), ioVols[1][0], pCfg8006->iic_high_min, pCfg8006->iic_high_max );
		}

		if( ioVols[0][1] < pCfg8006->iic_low_min || ioVols[0][1] > pCfg8006->iic_low_max )
		{
			failerCnt++;
			//transformat( szTemp, _T("scl vol = %d, th = [%d - %d]\r\n"), ioVols[0][1], pCfg8006->iic_low_min, pCfg8006->iic_low_max );
			//TestResultInfo( szTemp );
			TestResultInfoR( _T("scl vol = %d, th = [%d - %d]\r\n"), ioVols[0][1], pCfg8006->iic_low_min, pCfg8006->iic_low_max );
		}
		if( ioVols[1][1] < pCfg8006->iic_high_min || ioVols[1][1] > pCfg8006->iic_high_max )
		{
			failerCnt++;
			//transformat( szTemp, _T("scl vol = %d, th = [%d - %d]\r\n"), ioVols[1][1], pCfg8006->iic_high_min, pCfg8006->iic_high_max );
			//TestResultInfo( szTemp );
			TestResultInfoR( _T("scl vol = %d, th = [%d - %d]\r\n"), ioVols[1][1], pCfg8006->iic_high_min, pCfg8006->iic_high_max );
		}
	}
	else if( PROTOCAL_SPI == pCfg8006->protocalType )
	{
		if( ioVols[0][3] < pCfg8006->spi_low_min || ioVols[0][3] > pCfg8006->spi_low_max )
		{
			failerCnt++;
			//transformat( szTemp, _T("csn vol = %d, th = [%d - %d]\r\n"), ioVols[0][3], pCfg8006->spi_low_min, pCfg8006->spi_low_max );
			//TestResultInfo( szTemp );
			TestResultInfoR( _T("csn vol = %d, th = [%d - %d]\r\n"), ioVols[0][3], pCfg8006->spi_low_min, pCfg8006->spi_low_max );
		}
		if( ioVols[1][3] < pCfg8006->spi_high_min || ioVols[1][3] > pCfg8006->spi_high_max )
		{
			failerCnt++;
			//transformat( szTemp, _T("csn vol = %d, th = [%d - %d]\r\n"), ioVols[1][3], pCfg8006->spi_high_min, pCfg8006->spi_high_max );
			//TestResultInfo( szTemp );
			TestResultInfoR( _T("csn vol = %d, th = [%d - %d]\r\n"), ioVols[1][3], pCfg8006->spi_high_min, pCfg8006->spi_high_max );
		}

		if( ioVols[0][4] < pCfg8006->spi_low_min || ioVols[0][4] > pCfg8006->spi_low_max )
		{
			failerCnt++;
			//transformat( szTemp, _T("mosi vol = %d, th = [%d - %d]\r\n"), ioVols[0][4], pCfg8006->spi_low_min, pCfg8006->spi_low_max );
			//TestResultInfo( szTemp );
			TestResultInfoR( _T("mosi vol = %d, th = [%d - %d]\r\n"), ioVols[0][4], pCfg8006->spi_low_min, pCfg8006->spi_low_max );
		}
		if( ioVols[1][4] < pCfg8006->spi_high_min || ioVols[1][4] > pCfg8006->spi_high_max )
		{
			failerCnt++;
			//transformat( szTemp, _T("mosi vol = %d, th = [%d - %d]\r\n"), ioVols[1][4], pCfg8006->spi_high_min, pCfg8006->spi_high_max );
			//TestResultInfo( szTemp );
			TestResultInfoR( _T("mosi vol = %d, th = [%d - %d]\r\n"), ioVols[1][4], pCfg8006->spi_high_min, pCfg8006->spi_high_max );
		}

		if( ioVols[0][5] < pCfg8006->spi_low_min || ioVols[0][5] > pCfg8006->spi_low_max )
		{
			failerCnt++;
			//transformat( szTemp, _T("miso vol = %d, th = [%d - %d]\r\n"), ioVols[0][5], pCfg8006->spi_low_min, pCfg8006->spi_low_max );
			//TestResultInfo( szTemp );
			TestResultInfoR(  _T("miso vol = %d, th = [%d - %d]\r\n"), ioVols[0][5], pCfg8006->spi_low_min, pCfg8006->spi_low_max );
		}
		if( ioVols[1][5] < pCfg8006->spi_high_min || ioVols[1][5] > pCfg8006->spi_high_max )
		{
			failerCnt++;
			//transformat( szTemp, _T("miso vol = %d, th = [%d - %d]\r\n"), ioVols[1][5], pCfg8006->spi_high_min, pCfg8006->spi_high_max );
			//TestResultInfo( szTemp );
			TestResultInfoR( _T("miso vol = %d, th = [%d - %d]\r\n"), ioVols[1][5], pCfg8006->spi_high_min, pCfg8006->spi_high_max );
		}

		if( ioVols[0][6] < pCfg8006->spi_low_min || ioVols[0][6] > pCfg8006->spi_low_max )
		{
			failerCnt++;
			//transformat( szTemp, _T("sclk vol = %d, th = [%d - %d]\r\n"), ioVols[0][6], pCfg8006->spi_low_min, pCfg8006->spi_low_max );
			//TestResultInfo( szTemp );
			TestResultInfoR( _T("sclk vol = %d, th = [%d - %d]\r\n"), ioVols[0][6], pCfg8006->spi_low_min, pCfg8006->spi_low_max );
		}
		if( ioVols[1][6] < pCfg8006->spi_high_min || ioVols[1][6] > pCfg8006->spi_high_max )
		{
			failerCnt++;
			//transformat( szTemp, _T("sclk vol = %d, th = [%d - %d]\r\n"), ioVols[1][6], pCfg8006->spi_high_min, pCfg8006->spi_high_max );
			//TestResultInfo( szTemp );
			TestResultInfoR(_T("sclk vol = %d, th = [%d - %d]\r\n"), ioVols[1][6], pCfg8006->spi_high_min, pCfg8006->spi_high_max );
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
unsigned int CTest8006::Noise_Test( NativeTestItem& itemQuote )
{
	int failerCount = 0;
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );
	signed short baseTempBuffer[MAX_MCAP_CHANNEL * 2] = {0};
	signed short MaxTempBuffer[MAX_MCAP_CHANNEL * 2] = {0};
	signed short MinTempBuffer[MAX_MCAP_CHANNEL * 2] = {0};
	signed short diffTempBuffer[MAX_MCAP_CHANNEL * 2] = {0};
	/*unsigned*/ short dataMatrix[MAX_MCAP_ROW][MAX_MCAP_COL];
	const unsigned int iRawDataLen = ((pCfg8006->rowsCnt + 1) * (pCfg8006->colsCnt + 1) * 2 + 3) & 0xfffffffc;
	const unsigned int iScapRawDataLen = pCfg8006->rowsCnt + pCfg8006->colsCnt;
	unsigned short readBuffer[128] = {0};

	TestResultInfo( _T("\r\n------------------------------Noise Test------------------------------\r\n") );

	if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	ISMChip8006* iChip8006 = (ISMChip8006*)SM_ChipBase(m_deviceNo);

	/*iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_CTP_RST );
	if( iReCode != ERROR_CODE_OK ) itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	SysDelay( 20 );

	iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_SWITCH_IIC );
	if( iReCode != ERROR_CODE_OK ) itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_IDENTITY );
	if( iReCode != ERROR_CODE_OK ) itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );*/

	iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( 0x07,(0), 0,0);
	if( iReCode != ERROR_CODE_OK ) itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	iReCode = iChip8006->SwitchMode( MODE_RAWDATA, iRawDataLen );
	if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	//SysDelay( 20 );

	for( int index = 0; index < 5; index++ )
	{
		iReCode = iChip8006->GetRawData( baseTempBuffer, iRawDataLen  );
		//if( iReCode == ERROR_CODE_OK ) break;
		if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	}

	memcpy(MaxTempBuffer,baseTempBuffer,sizeof(baseTempBuffer));
	memcpy(MinTempBuffer,baseTempBuffer,sizeof(baseTempBuffer));

	for(int index = 0; index < pCfg8006->noise_frame; index++)
	{
		iReCode = iChip8006->GetRawData( baseTempBuffer, iRawDataLen );
		if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
		for(int iCnt = 0; iCnt < (int)iRawDataLen;  iCnt++)
		{
			MaxTempBuffer[iCnt] = max(baseTempBuffer[iCnt] , MaxTempBuffer[iCnt]);
			MinTempBuffer[iCnt] = min(baseTempBuffer[iCnt] , MinTempBuffer[iCnt]);
			diffTempBuffer[iCnt] = MaxTempBuffer[iCnt] - MinTempBuffer[iCnt];
		}
	}

	int ref_channel_num = min(pCfg8006->real_channel_num - pCfg8006->va_channel_num, pCfg8006->colsCnt);
	AnalyzeInfo info( pCfg8006->rowsCnt, pCfg8006->colsCnt, ref_channel_num, false );
	ReShappingData</*unsigned*/ short>( dataMatrix, (/*unsigned*/ short*)diffTempBuffer, G_XMLConfig->real_channel_num * 2, pCfg8006->rowsCnt, pCfg8006->colsCnt );

	short noiseMin[MAX_MCAP_ROW][MAX_MCAP_COL], noiseMax[MAX_MCAP_ROW][MAX_MCAP_COL];
	FillMatrixUseValue( noiseMin, (short)0 );
	FillMatrixUseValue( noiseMax, (short)pCfg8006->noise_max_mcap );

	NodeVal nodeOutRange;
	ColorText textTemp( _T("\r\nNoise McapData:\r\n") );
	bool bResult = AnalyzeTestResult( dataMatrix, noiseMin, noiseMax, pCfg8006->invalid_node, info, textTemp, nodeOutRange, true );
	TestResultInfo( textTemp );
	if( !bResult )
	{
		failerCount++;
		LPCTSTR strHead = _T("\r\n//========= Out of Threshold in McapNoiseTest: \r\n");
		PrintNodeValue( m_ColorText, &nodeOutRange, strHead );
	}
	//NodeVal nodeOutRangeScap;
	//FillMatrixUseValue( dataMatrix, (short)0 );
	//FillMatrixUseValue( noiseMin, (short)0 );
	//FillMatrixUseValue( noiseMax, (short)pCfg8006->noise_max_scap );
	//unsigned short maxCols[] = { pCfg8006->colsCnt, pCfg8006->rowsCnt };
	//ReShappingData</*unsigned*/ short>( dataMatrix, (/*unsigned*/ short*)diffTempBuffer + pCfg8006->rowsCnt * pCfg8006->colsCnt, iScapRawDataLen, 2, maxCols );
	//ColorText textTempScap=( _T("\r\nNoise ScapData:\r\n") );
	//bResult = AnalyzeTestResultMSCap( dataMatrix, noiseMin, noiseMax, pCfg8006->invalid_node, info, textTempScap, nodeOutRangeScap, true );
	//TestResultInfo( textTempScap );
	//if( !bResult )
	//{
	//	failerCount++;
	//	LPCTSTR strHead = _T("\r\n//========= Out of Threshold in ScapNoiseTest: \r\n");
	//	PrintNodeValue( m_ColorText, &nodeOutRangeScap, strHead );
	//}

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

typedef struct _rockerCali
{
	short rocker_value[6];

	short center_OriginalCap[4];

	short x_min_OriginalCap[4];
	short x_max_OriginalCap[4];
	short y_min_OriginalCap[4];
	short y_max_OriginalCap[4];

	unsigned short tag;
	unsigned short crc;
	_rockerCali()
	{
		tag = 0x8006;
	}

}RockerCali;
unsigned int CTest8006::Base_Test( NativeTestItem& itemQuote )
{
	int failerCount = 0;
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );
	signed short baseTempBuffer[64] = {0};
	const unsigned int iRawDataLen = 64;
	const unsigned int iRetry = 3;
	signed int baseSum[64] = {0};
	CRockerCalibration RockerCalib;
	RockerCali rockerCali;
	rockerCali.tag = 0x8006;

	TestResultInfo( _T("\r\n------------------------------RockerCalib Test------------------------------\r\n") );

	if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	ISMChip8006* iChip8006 = (ISMChip8006*)SM_ChipBase(m_deviceNo);

	//iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_CTP_RST );
	//if( iReCode != ERROR_CODE_OK ) itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	//SysDelay( 30 );

	//iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_SWITCH_IIC );
	//if( iReCode != ERROR_CODE_OK ) itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	//iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_IDENTITY );
	//if( iReCode != ERROR_CODE_OK ) itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_ROCKER_CALIB,(0), 0,0);
	if( iReCode != ERROR_CODE_OK ) itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	iReCode = iChip8006->SwitchMode( MODE_RAWDATA, iRawDataLen );
	if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	//SysDelay( 20 );
	for( int index = 0; index < iRetry; index++ )
	{
		iReCode = iChip8006->GetRawData( baseTempBuffer, iRawDataLen );
		if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

		if(0 == index) continue;
		ArrayAddtion( baseSum, baseTempBuffer, iRawDataLen );
	}
	ArrayAverage( baseTempBuffer, baseSum, iRawDataLen, iRetry - 1);
	auto baserockercentre = RockerCalib.GetRockerData(baseTempBuffer,iRawDataLen);

	iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_ROCKER_CALIB,(baserockercentre.cap_value[0]<<16|baserockercentre.cap_value[1]), baserockercentre.cap_value[2],baserockercentre.cap_value[3]);
	if( iReCode != ERROR_CODE_OK ) itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	iReCode = iChip8006->SwitchMode( MODE_RAWDATA, iRawDataLen );
	if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	//SysDelay( 20 );

	memset(baseSum,0,sizeof(baseSum));
	memset(baseTempBuffer,0,sizeof(baseTempBuffer));

	for( int index = 0; index < iRetry; index++ )
	{
		iReCode = iChip8006->GetRawData( baseTempBuffer, iRawDataLen );
		if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

		if(0 == index) continue;
		ArrayAddtion( baseSum, baseTempBuffer, iRawDataLen );
	}
	ArrayAverage( baseTempBuffer, baseSum, iRawDataLen, iRetry - 1);
	auto rockercentre = RockerCalib.GetRockerData(baseTempBuffer,iRawDataLen);


	RockerCalib.SetCentreValue(rockercentre);
	int times = 0;
	short deffx = ((pCfg8006->base_x_difference+pCfg8006->base_x_difference_neg)*pCfg8006->base_ratio_num/100);
	short deffy = ((pCfg8006->base_y_difference+pCfg8006->base_y_difference_neg)*pCfg8006->base_ratio_num/100);
	short x_min = rockercentre.x_centerValue - deffx;
	short x_max = rockercentre.x_centerValue + deffx;

	short y_min = rockercentre.y_centerValue - deffy;
	short y_max = rockercentre.y_centerValue + deffy;
	int outframe =0;
	while(Tick(itemNotify,times))
	{
		times++;
		iReCode = iChip8006->GetRawData( baseTempBuffer, iRawDataLen );
		if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
		auto rockervalue = RockerCalib.GetRockerData(baseTempBuffer,iRawDataLen);
		if((rockervalue.x_centerValue >= x_min)
			&&(rockervalue.x_centerValue<=x_max)
			&&(abs(rockervalue.y_centerValue-rockercentre.y_centerValue)>200))
		{
			RockerCalib.Add_Y_MaxData(rockervalue);
		}
		if((rockervalue.y_centerValue>=y_min)
			&&(rockervalue.y_centerValue<=y_max)
			&&(abs(rockervalue.x_centerValue-rockercentre.x_centerValue)>200))
		{
			RockerCalib.Add_X_MaxData(rockervalue);
		}

		if ((RockerCalib.Get_X_Count()>0)&&(RockerCalib.Get_Y_Count()>0))
		{
			if((abs(rockervalue.y_centerValue-rockercentre.y_centerValue)<200) && (abs(rockervalue.x_centerValue-rockercentre.x_centerValue)<200))
			{
				outframe++;
				if(outframe>10)
				{
					outframe = 0;
					break;
				}
			}
		}

	}
	auto x_rockermin = RockerCalib.Get_X_MinData();
	auto x_rockermax = RockerCalib.Get_X_MaxData();
	auto y_rockermin = RockerCalib.Get_Y_MinData();
	auto y_rockermax = RockerCalib.Get_Y_MaxData();

	TestResultInfoR(_T("\r\nrange_x[%d,%d], range_y[%d,%d], sampling_times:%d \r\n"),x_min, x_max, y_min, y_max,times);

	if((x_rockermin.x_centerValue - rockercentre.x_centerValue) > (-pCfg8006->base_x_difference_neg)) 
	{
		TestResultInfoR(_T("\r\nxmin(%5d) - xcenter(%5d) = %d > neg_x(%5d)\r\n"),x_rockermin.x_centerValue,rockercentre.x_centerValue,(x_rockermin.x_centerValue - rockercentre.x_centerValue),-pCfg8006->base_x_difference_neg);
		failerCount++;
	}
	if((x_rockermax.x_centerValue-rockercentre.x_centerValue) < pCfg8006->base_x_difference)
	{
		TestResultInfoR(_T("\r\nxmax(%5d) - xcenter(%5d) = %d < pos_x(%5d)\r\n"),x_rockermax.x_centerValue,rockercentre.x_centerValue,(x_rockermax.x_centerValue-rockercentre.x_centerValue),pCfg8006->base_x_difference);
		failerCount++;
	}
	if((y_rockermin.y_centerValue-rockercentre.y_centerValue) > (-pCfg8006->base_y_difference_neg))
	{
		TestResultInfoR(_T("\r\nymin(%5d) - ycenter(%5d) = %d > neg_y(%5d)\r\n"),y_rockermin.y_centerValue,rockercentre.y_centerValue,(y_rockermin.y_centerValue-rockercentre.y_centerValue),-pCfg8006->base_y_difference_neg);
		failerCount++;
	}
	if((y_rockermax.y_centerValue-rockercentre.y_centerValue)<pCfg8006->base_y_difference)
	{
		TestResultInfoR(_T("\r\nymax(%5d) - ycenter(%5d) = %d < pos_y(%5d)\r\n"),y_rockermax.y_centerValue,rockercentre.y_centerValue,(y_rockermax.y_centerValue-rockercentre.y_centerValue),pCfg8006->base_y_difference);
		failerCount++;
	}
	if(failerCount==0)
	{

		unsigned char readBuffer[1024] = {0};
		short x_min = 0,x_centre = 0 ,x_max = 0 ,y_min = 0, y_centre = 0, y_max = 0;
		iReCode = SM_ChipBase(m_deviceNo)->ReadBurnSpace( TCP_CALIBA_ADDR_8006, readBuffer, sizeof(readBuffer) ); 
		if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

		//x_min = ((short)((x_rockermin.x_centerValue - rockercentre.x_centerValue) * pCfg8006->base_proportion_value)) + rockercentre.x_centerValue;
		//x_centre = rockercentre.x_centerValue;
		//x_max = ((short)((x_rockermax.x_centerValue - rockercentre.x_centerValue) * pCfg8006->base_proportion_value)) + rockercentre.x_centerValue;

		//y_min = ((short)((y_rockermin.y_centerValue - rockercentre.y_centerValue) * pCfg8006->base_proportion_value)) + rockercentre.y_centerValue;
		//y_centre = rockercentre.y_centerValue;
		//y_max = ((short)((y_rockermax.y_centerValue - rockercentre.y_centerValue) * pCfg8006->base_proportion_value)) + rockercentre.y_centerValue;
		unsigned short radradius = pCfg8006->resolution_x>>1;
		float pro = ((float)(radradius + pCfg8006->base_proportion_value)/radradius);
		x_min = (short)((x_rockermin.x_centerValue - rockercentre.x_centerValue) * pro) + rockercentre.x_centerValue;
		x_centre = rockercentre.x_centerValue;
		x_max = (short)((x_rockermax.x_centerValue - rockercentre.x_centerValue) * pro) + rockercentre.x_centerValue;

		y_min = (short)((y_rockermin.y_centerValue - rockercentre.y_centerValue) * pro) + rockercentre.y_centerValue;
		y_centre = rockercentre.y_centerValue;
		y_max = (short)((y_rockermax.y_centerValue - rockercentre.y_centerValue) * pro) + rockercentre.y_centerValue;

		rockerCali.rocker_value[0] = x_min;
		rockerCali.rocker_value[1] = x_centre;
		rockerCali.rocker_value[2] = x_max;

		rockerCali.rocker_value[3] = y_min;
		rockerCali.rocker_value[4] = y_centre;
		rockerCali.rocker_value[5] = y_max;

		for (int i=0; i<4; i++)
		{
			rockerCali.center_OriginalCap[i] = baserockercentre.cap_value[i];

			rockerCali.x_min_OriginalCap[i] = x_rockermin.cap_value[i];
			rockerCali.x_max_OriginalCap[i] = x_rockermax.cap_value[i];

			rockerCali.y_min_OriginalCap[i] = y_rockermin.cap_value[i];
			rockerCali.y_max_OriginalCap[i] = y_rockermax.cap_value[i];
		}
		

		rockerCali.crc = 1 + ~caculate_check_sum_u16( (unsigned short*)&rockerCali, sizeof(rockerCali) - 2 );

		memcpy(&readBuffer[512], &rockerCali, sizeof(rockerCali));

		iReCode = SM_ChipBase(m_deviceNo)->WriteBurnSpace( TCP_CALIBA_ADDR_8006, readBuffer, sizeof(readBuffer), OTP_W_CHK | TLK_DATACHK_EX1 );
		if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

		TestResultInfoR(_T("\r\nrocke calibration value:(%5d,%5d,%5d,%5d,%5d,%5d),base center data:(%5d,%5d,%5d,%5d) , reduce_value:(%d)\r\n"),rockerCali.rocker_value[0], rockerCali.rocker_value[1], rockerCali.rocker_value[2], rockerCali.rocker_value[3], rockerCali.rocker_value[4], rockerCali.rocker_value[5],rockerCali.center_OriginalCap[0], rockerCali.center_OriginalCap[1],rockerCali.center_OriginalCap[2],rockerCali.center_OriginalCap[3],pCfg8006->base_proportion_value);
	
	}


	TestResultInfoR(_T("\r\nx_min:(%5d,%5d),data:(%5d,%5d,%5d,%5d)\r\n"),x_rockermin.x_centerValue,x_rockermin.y_centerValue,x_rockermin.cap_value[0],x_rockermin.cap_value[1],x_rockermin.cap_value[2],x_rockermin.cap_value[3]);
	TestResultInfoR(_T("\r\nx_max:(%5d,%5d),data:(%5d,%5d,%5d,%5d)\r\n"),x_rockermax.x_centerValue,x_rockermax.y_centerValue,x_rockermax.cap_value[0],x_rockermax.cap_value[1],x_rockermax.cap_value[2],x_rockermax.cap_value[3]);

	TestResultInfoR(_T("\r\ny_min:(%5d,%5d),data:(%5d,%5d,%5d,%5d)\r\n"),y_rockermin.x_centerValue,y_rockermin.y_centerValue,y_rockermin.cap_value[0],y_rockermin.cap_value[1],y_rockermin.cap_value[2],y_rockermin.cap_value[3]);
	TestResultInfoR(_T("\r\ny_max:(%5d,%5d),data:(%5d,%5d,%5d,%5d)\r\n"),y_rockermax.x_centerValue,y_rockermax.y_centerValue,y_rockermax.cap_value[0],y_rockermax.cap_value[1],y_rockermax.cap_value[2],y_rockermax.cap_value[3]);

	TestResultInfoR(_T("\r\nxy_center:(%5d,%5d),data:(%5d,%5d,%5d,%5d)\r\n"),rockercentre.x_centerValue,rockercentre.y_centerValue,rockercentre.cap_value[0],rockercentre.cap_value[1],rockercentre.cap_value[2],rockercentre.cap_value[3]);
	TestResultInfoR(_T("\r\nxy_base_center:(%5d,%5d),data:(%5d,%5d,%5d,%5d)\r\n"),baserockercentre.x_centerValue,baserockercentre.y_centerValue,baserockercentre.cap_value[0],baserockercentre.cap_value[1],baserockercentre.cap_value[2],baserockercentre.cap_value[3]);

	int sum_ref1 = baserockercentre.cap_value[0] + baserockercentre.cap_value[1];
	int sum_ref2 = baserockercentre.cap_value[2] + baserockercentre.cap_value[3];

	short offset1=0, offset2 =0;

	offset1 = (baserockercentre.cap_value[0] - baserockercentre.cap_value[1]) > 0 ? baserockercentre.cap_value[1] : baserockercentre.cap_value[0];

	offset2 = (baserockercentre.cap_value[2] - baserockercentre.cap_value[3]) > 0 ? baserockercentre.cap_value[3] : baserockercentre.cap_value[2];

	TestResultInfoR(_T("\r\ncsum_ref:(%5d,%5d),offset:(%5d,%5d,%5d,%5d)\r\n"),sum_ref1,sum_ref2,(baserockercentre.cap_value[0] - offset1),(baserockercentre.cap_value[1] - offset1),(baserockercentre.cap_value[2] - offset2),(baserockercentre.cap_value[3] - offset2));

	TestResultInfoR(_T("\r\n------------------------------------------\r\n"));

	auto x_DataList = RockerCalib.Get_X_List();
	auto y_DataList = RockerCalib.Get_Y_List();
	if (x_DataList.size()!=0)
	{
		for(unsigned short i=0; i < x_DataList.size();i++)
		{
			TestResultInfoR(_T("\r\nx_datalist[%d]:(%5d,%5d)(%5d,%5d,%5d,%5d)\r\n"),i,x_DataList[i].x_centerValue,x_DataList[i].y_centerValue,x_DataList[i].cap_value[0],x_DataList[i].cap_value[1],x_DataList[i].cap_value[2],x_DataList[i].cap_value[3]);	
		}
	}

	if (y_DataList.size()!=0)
	{
		for(unsigned short i=0; i < y_DataList.size();i++)
		{
			TestResultInfoR(_T("\r\ny_datalist[%d]:(%5d,%5d)(%5d,%5d,%5d,%5d)\r\n"),i,y_DataList[i].x_centerValue,y_DataList[i].y_centerValue,y_DataList[i].cap_value[0],y_DataList[i].cap_value[1],y_DataList[i].cap_value[2],y_DataList[i].cap_value[3]);	
		}
	}



	if( failerCount )
	{
		itemNotify.UpdateItemResult( ITEM_STA_FAIL );
		TestResultInfo( "\r\n\r\n//RockerCalib Test is Fail\r\n", ITEM_STA_FAIL );
	}
	else
	{
		itemNotify.UpdateItemResult( ITEM_STA_PASS );
		TestResultInfo( "\r\n\r\n//RockerCalib Test is Pass\r\n", ITEM_STA_PASS );
	}

	return itemNotify;
}
unsigned int CTest8006::SetClkInFctMode( unsigned short clkDiv )
{
	return SM_ChipBase(m_deviceNo)->SetClkInFctMode(clkDiv, pCfg8006->filter_off);
}
unsigned int CTest8006::WorkForGraphMode( bool bEnterGraphing /*= false*/ )
{
	unsigned int iReCode = ERROR_CODE_OK;

	if( bEnterGraphing && !IsTestInGraphStep() )
	{
		if (pCfg8006->line_type>0)
		{
			iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_CTP_RST );
			CHECK_RETURN_IF_FAIL( iReCode );

			SysDelay( 200 );

			iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand(CMD_TYPE_LINE,0x130,pCfg8006->line_type<<8|pCfg8006->swich_addr_selected,pCfg8006->swaddr_slaveAddr1<<8|pCfg8006->swaddr_slaveAddr2);
			CHECK_RETURN_IF_FAIL( iReCode );
		}
		else
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

	}
	else
	{

	}

	bEnterGraphing ? SetTestStatusInGraphStep() : SetTestStatusInDataStep();

	return iReCode;
}

unsigned int CTest8006::TP_RemoveTest(NativeTestItem& itemQuote)
{
	unsigned int iReCode = ERROR_CODE_OK;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );

	while( IsLoopStillRun() )
	{
		if( !HaveTpLinked_8006()) break;

		itemNotify.UpdateItemResult( ITEM_STA_WAIT );
		::Sleep( 300 );

		if( !HaveTpLinked_8006() ) break;

		itemNotify.UpdateItemResult( ITEM_STA_START );
		::Sleep( 300 );
	}

	return itemNotify.UpdateItemResult( ITEM_STA_PASS );

}

unsigned int CTest8006::TP_WaitTest(NativeTestItem& itemQuote)
{
	unsigned int iReCode = ERROR_CODE_OK;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );

	while( IsLoopStillRun() )
	{
		if( HaveTpLinked_8006()) break;

		itemNotify.UpdateItemResult( ITEM_STA_WAIT );
		::Sleep( 300 );

		if( HaveTpLinked_8006() ) break;

		itemNotify.UpdateItemResult( ITEM_STA_START );
		::Sleep( 300 );
	}

	return itemNotify.UpdateItemResult( ITEM_STA_PASS );
}

bool CTest8006::HaveTpLinked_8006()
{
	unsigned int iReCode = 0;
	unsigned int buff_w = 0x11223344;
	bool ret = false;
	for (int k =0; k<5; k++)
	{
		iReCode = SM_ChipBase(m_deviceNo)->WriteCoreSpace( 0x20000000, (unsigned char*)&buff_w, 4 );
		if( iReCode != ERROR_CODE_OK )
		{
			ret = false;
		}
		else
		{
			break;
		}
	}
	if(iReCode == ERROR_CODE_OK)
	{
		ret = true;
	}
	else
	{
		ret = false;
	}

	return ret;

}

void CTest8006::PrepareSimulate( SimulateData& sm )
{
	unsigned char cmdID = sm.itemID & 0xff;
	unsigned char dataIndex = (sm.itemID >> 8) & 0xff;
	unsigned char sumCnt = 1;
	int iDesIndex = 0;

	//scap data
	if( sm.itemID == ((0xfa << 16) + 0x28) )
	{
		iDesIndex += pCfg8006->rowsCnt * pCfg8006->colsCnt;
		for( int iCol = 0; iCol <  pCfg8006->colsCnt; iCol++ )
			sm.itemArray[iDesIndex++] = sm.itemData[0][iCol] * sumCnt;
		for( int iCol = 0; iCol < pCfg8006->rowsCnt; iCol++ )
			sm.itemArray[iDesIndex++] = sm.itemData[1][iCol] * sumCnt;
	}
	else
	{
		for( int iRow = 0; iRow < sm.rows; iRow++ )
		{
			for( int iCol = 0; iCol < sm.cols; iCol++ )
			{
				if( iDesIndex >= sizeof(sm.itemArray)/sizeof(short) ) break;

				//int icPosition = pCfg8006->sensor_2_ic_map[index];
				sm.itemArray[iDesIndex++] = sm.itemData[iRow][iCol] * sumCnt;
			}
		}
	}
}
bool CTest8006::Tick(ItemNotifyer&itemNotify)
{
	LONGLONG sys_freq = 0;
	LONGLONG timer_tick = 0;

	QueryPerformanceFrequency( (LARGE_INTEGER*)&sys_freq );
	QueryPerformanceCounter( (LARGE_INTEGER*)&timer_tick );

	static LONGLONG prev_timer_tick = timer_tick;
	static short time = pCfg8006->base_test_time;
	if( (timer_tick - prev_timer_tick) / sys_freq > 0 )
	{
		prev_timer_tick = timer_tick;
		bool btimeLeft = ((time-=1)<=0? true : false);
		auto str = StrFormat( _T("%d"),time );
		if(time%2==0)
		{
			itemNotify.UpdateItemResult( ITEM_STA_WAIT, str );	
		}
		else
		{
			itemNotify.UpdateItemResult( ITEM_STA_START, str );	
		}
		
		if(btimeLeft==true)
		{
			time = pCfg8006->base_test_time;
			return false;
		}
		
		return true;
	}
	else
	{
		return true;
	}

} 

bool CTest8006::Tick(ItemNotifyer&itemNotify,int time)
{
	
	if(time > pCfg8006->base_test_time * 400)
	{
		Itick = 0;
		return false;
	}

	int num = time / 400;
	num = num + 1;
	if(time == 0)
	{
		Itick = 0;
	}
	if(num != Itick)
	{
		Itick = num;

		auto str = StrFormat( _T("%d"),num );

		if(num % 2==0)
		{
			itemNotify.UpdateItemResult( ITEM_STA_WAIT, str );	
		}
		else
		{
			itemNotify.UpdateItemResult( ITEM_STA_START, str );	
		}
	
	}
	return true;
	
}

bool CTest8006::Judgmentconditions(int pframes, int pcValue, int pldownValue, int plupValue,int psValue)
{
	if((pcValue <= plupValue) && (pcValue >= pldownValue))
	{
		
		if (Iframes==0)
		{
			IfristValue = pcValue;
		}

	}
	else
	{
		Iframes = 0;
		return false; 
	}
	if((abs(pcValue-IfristValue)<=psValue))
	{
		Iframes++;
	}
	else
	{
		Iframes = 0;
		return false; 
	}

	if(Iframes >= pframes)
	{
		Iframes = 0;
		return true;
	}

	return false; 

}

unsigned int CTest8006::MISC_Test( NativeTestItem& itemQuote )
{
	/*int failerCnt = 0;
	unsigned int iReCode = ERROR_CODE_COMM_ERROR, errCode = 0;*/
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );
	////char tempBuffer[MAX_PATH];

	//TestResultInfo( _T("\r\n------------------------------MISC Test------------------------------\r\n") );

	//if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	//ISMChip8006* iChip8006 = (ISMChip8006*)SM_ChipBase(m_deviceNo);

	//unsigned short rsp[8] = {0};
	//iReCode = iChip8006->IncokeCommand( CMD_MISC_TST, pCfg8006->misc_mode, 0, 0, (unsigned char*)rsp );
	//if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	//if(rsp[1])
	//{
	//	failerCnt++;
	//	//transformat( tempBuffer, _T("Misc(%d), Code = 0x%x\r\n"), rsp[1],  (rsp[2] << 16) + rsp[3]);
	//	//TestResultInfo( tempBuffer );
	//	TestResultInfoR( _T("Misc(%d), Code = 0x%x\r\n"), rsp[1],  (rsp[2] << 16) + rsp[3] );
	//}

	//if( failerCnt )
	//{
	//	itemNotify.UpdateItemResult( ITEM_STA_FAIL );
	//	TestResultInfo( "\r\n\r\n//MISC Test is Fail\r\n", ITEM_STA_FAIL );
	//}
	//else
	//{
	//	itemNotify.UpdateItemResult( ITEM_STA_PASS );
	//	TestResultInfo( "\r\n\r\n//MISC Test is Pass\r\n", ITEM_STA_PASS );
	//}

	return itemNotify;
}

unsigned int CTest8006::SDRockerCalib_Test(NativeTestItem& itemQuote)
{
	int failerCount = 0;
	unsigned int iReCode = ERROR_CODE_COMM_ERROR;
	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );
	signed short baseTempBuffer[64] = {0};
	const unsigned int iRawDataLen = 64;
	const unsigned int iRetry = 3;
	signed int baseSum[64] = {0};
	CRockerCalibration RockerCalib;
	RockerCali rockerCali;
	rockerCali.tag = 0x8006;

	TestResultInfo( _T("\r\n------------------------------RockerCalib Test------------------------------\r\n") );

	if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	ISMChip8006* iChip8006 = (ISMChip8006*)SM_ChipBase(m_deviceNo);

	iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_ROCKER_CALIB,(0), 0,0);
	if( iReCode != ERROR_CODE_OK ) itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	iReCode = iChip8006->SwitchMode( MODE_RAWDATA, iRawDataLen );
	if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	//SysDelay( 20 );
	for( int index = 0; index < iRetry; index++ )
	{
		iReCode = iChip8006->GetRawData( baseTempBuffer, iRawDataLen );
		if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

		if(0 == index) continue;
		ArrayAddtion( baseSum, baseTempBuffer, iRawDataLen );
	}
	ArrayAverage( baseTempBuffer, baseSum, iRawDataLen, iRetry - 1);
	auto baserockercentre = RockerCalib.GetRockerData(baseTempBuffer,iRawDataLen);

	iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_ROCKER_CALIB,(baserockercentre.cap_value[0]<<16|baserockercentre.cap_value[1]), baserockercentre.cap_value[2],baserockercentre.cap_value[3]);
	if( iReCode != ERROR_CODE_OK ) itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	iReCode = iChip8006->SwitchMode( MODE_RAWDATA, iRawDataLen );
	if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
	//SysDelay( 20 );

	memset(baseSum,0,sizeof(baseSum));
	memset(baseTempBuffer,0,sizeof(baseTempBuffer));

	for( int index = 0; index < iRetry; index++ )
	{
		iReCode = iChip8006->GetRawData( baseTempBuffer, iRawDataLen );
		if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

		if(0 == index) continue;
		ArrayAddtion( baseSum, baseTempBuffer, iRawDataLen );
	}
	ArrayAverage( baseTempBuffer, baseSum, iRawDataLen, iRetry - 1);
	auto rockercentre = RockerCalib.GetRockerData(baseTempBuffer,iRawDataLen);


	RockerCalib.SetCentreValue(rockercentre);
	int times = 0;
	short deffx = ((pCfg8006->sdrc_y_difference+pCfg8006->sdrc_y_difference_neg)*pCfg8006->sdrc_ratio_num/100);
	short x_min = rockercentre.x_centerValue - deffx;
	short x_max = rockercentre.x_centerValue + deffx;

	int outframe =0;
	bool pos = false;
	bool neg = false;
	while(Tick(itemNotify,times))
	{
		times++;
		iReCode = iChip8006->GetRawData( baseTempBuffer, iRawDataLen );
		if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
		auto rockervalue = RockerCalib.GetRockerData(baseTempBuffer,iRawDataLen);
		if((rockervalue.x_centerValue >= x_min)
			&&(rockervalue.x_centerValue<=x_max))
		{
			if(((rockervalue.y_centerValue-rockercentre.y_centerValue)>500))
			{
				pos = true;
			}
			if ((rockervalue.y_centerValue-rockercentre.y_centerValue)<(-500))
			{
				neg = true;
			}
			RockerCalib.Add_Y_MaxData(rockervalue);
		}

		if ((pos==true)&&(neg==true))
		{
			if((abs(rockervalue.y_centerValue-rockercentre.y_centerValue)<200))
			{
				outframe++;
				if(outframe>10)
				{
					outframe = 0;
					break;
				}
			}
		}

	}
	auto y_rockermin = RockerCalib.Get_Y_MinData();
	auto y_rockermax = RockerCalib.Get_Y_MaxData();

	//TestResultInfoR(_T("\r\nrange_x[%d,%d], range_y[%d,%d], sampling_times:%d \r\n"),x_min, x_max, y_min, y_max,times);

	if((y_rockermin.y_centerValue-rockercentre.y_centerValue) > (-pCfg8006->base_y_difference_neg))
	{
		TestResultInfoR(_T("\r\nymin(%5d) - ycenter(%5d) = %d > neg_y(%5d)\r\n"),y_rockermin.y_centerValue,rockercentre.y_centerValue,(y_rockermin.y_centerValue-rockercentre.y_centerValue),-pCfg8006->base_y_difference_neg);
		failerCount++;
	}
	if((y_rockermax.y_centerValue-rockercentre.y_centerValue)<pCfg8006->base_y_difference)
	{
		TestResultInfoR(_T("\r\nymax(%5d) - ycenter(%5d) = %d < pos_y(%5d)\r\n"),y_rockermax.y_centerValue,rockercentre.y_centerValue,(y_rockermax.y_centerValue-rockercentre.y_centerValue),pCfg8006->base_y_difference);
		failerCount++;
	}
	if(failerCount==0)
	{

		unsigned char readBuffer[1024] = {0};
		short x_min = 0,x_centre = 0 ,x_max = 0 ,y_min = 0, y_centre = 0, y_max = 0;
		iReCode = SM_ChipBase(m_deviceNo)->ReadBurnSpace( TCP_CALIBA_ADDR_8006, readBuffer, sizeof(readBuffer) ); 
		if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

		//x_min = ((short)((x_rockermin.x_centerValue - rockercentre.x_centerValue) * pCfg8006->base_proportion_value)) + rockercentre.x_centerValue;
		//x_centre = rockercentre.x_centerValue;
		//x_max = ((short)((x_rockermax.x_centerValue - rockercentre.x_centerValue) * pCfg8006->base_proportion_value)) + rockercentre.x_centerValue;

		//y_min = ((short)((y_rockermin.y_centerValue - rockercentre.y_centerValue) * pCfg8006->base_proportion_value)) + rockercentre.y_centerValue;
		//y_centre = rockercentre.y_centerValue;
		//y_max = ((short)((y_rockermax.y_centerValue - rockercentre.y_centerValue) * pCfg8006->base_proportion_value)) + rockercentre.y_centerValue;
		unsigned short radradius = pCfg8006->resolution_x>>1;
		float pro = ((float)(radradius + pCfg8006->sdrc_proportion_value)/radradius);
		x_min = 0;
		x_centre =0;
		x_max = 0;

		y_min = (short)((y_rockermin.y_centerValue - rockercentre.y_centerValue) * pro) + rockercentre.y_centerValue;
		y_centre = rockercentre.y_centerValue;
		y_max = (short)((y_rockermax.y_centerValue - rockercentre.y_centerValue) * pro) + rockercentre.y_centerValue;

		rockerCali.rocker_value[0] = x_min;
		rockerCali.rocker_value[1] = x_centre;
		rockerCali.rocker_value[2] = x_max;

		rockerCali.rocker_value[3] = y_min;
		rockerCali.rocker_value[4] = y_centre;
		rockerCali.rocker_value[5] = y_max;

		for (int i=0; i<4; i++)
		{
			rockerCali.center_OriginalCap[i] = baserockercentre.cap_value[i];

			rockerCali.x_min_OriginalCap[i] =0;
			rockerCali.x_max_OriginalCap[i] = 0;

			rockerCali.y_min_OriginalCap[i] = y_rockermin.cap_value[i];
			rockerCali.y_max_OriginalCap[i] = y_rockermax.cap_value[i];
		}


		rockerCali.crc = 1 + ~caculate_check_sum_u16( (unsigned short*)&rockerCali, sizeof(rockerCali) - 2 );

		memcpy(&readBuffer[512], &rockerCali, sizeof(rockerCali));

		iReCode = SM_ChipBase(m_deviceNo)->WriteBurnSpace( TCP_CALIBA_ADDR_8006, readBuffer, sizeof(readBuffer), OTP_W_CHK | TLK_DATACHK_EX1 );
		if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

		TestResultInfoR(_T("\r\nrocke calibration value:(%5d,%5d,%5d,%5d,%5d,%5d),base center data:(%5d,%5d,%5d,%5d) , reduce_value:(%d)\r\n"),rockerCali.rocker_value[0], rockerCali.rocker_value[1], rockerCali.rocker_value[2], rockerCali.rocker_value[3], rockerCali.rocker_value[4], rockerCali.rocker_value[5],rockerCali.center_OriginalCap[0], rockerCali.center_OriginalCap[1],rockerCali.center_OriginalCap[2],rockerCali.center_OriginalCap[3],pCfg8006->base_proportion_value);

	}


	/*TestResultInfoR(_T("\r\nx_min:(%5d,%5d),data:(%5d,%5d,%5d,%5d)\r\n"),x_rockermin.x_centerValue,x_rockermin.y_centerValue,x_rockermin.cap_value[0],x_rockermin.cap_value[1],x_rockermin.cap_value[2],x_rockermin.cap_value[3]);
	TestResultInfoR(_T("\r\nx_max:(%5d,%5d),data:(%5d,%5d,%5d,%5d)\r\n"),x_rockermax.x_centerValue,x_rockermax.y_centerValue,x_rockermax.cap_value[0],x_rockermax.cap_value[1],x_rockermax.cap_value[2],x_rockermax.cap_value[3]);*/

	TestResultInfoR(_T("\r\ny_min:(%5d,%5d),data:(%5d,%5d,%5d,%5d)\r\n"),y_rockermin.x_centerValue,y_rockermin.y_centerValue,y_rockermin.cap_value[0],y_rockermin.cap_value[1],y_rockermin.cap_value[2],y_rockermin.cap_value[3]);
	TestResultInfoR(_T("\r\ny_max:(%5d,%5d),data:(%5d,%5d,%5d,%5d)\r\n"),y_rockermax.x_centerValue,y_rockermax.y_centerValue,y_rockermax.cap_value[0],y_rockermax.cap_value[1],y_rockermax.cap_value[2],y_rockermax.cap_value[3]);

	TestResultInfoR(_T("\r\nxy_center:(%5d,%5d),data:(%5d,%5d,%5d,%5d)\r\n"),rockercentre.x_centerValue,rockercentre.y_centerValue,rockercentre.cap_value[0],rockercentre.cap_value[1],rockercentre.cap_value[2],rockercentre.cap_value[3]);
	TestResultInfoR(_T("\r\nxy_base_center:(%5d,%5d),data:(%5d,%5d,%5d,%5d)\r\n"),baserockercentre.x_centerValue,baserockercentre.y_centerValue,baserockercentre.cap_value[0],baserockercentre.cap_value[1],baserockercentre.cap_value[2],baserockercentre.cap_value[3]);

	int sum_ref1 = baserockercentre.cap_value[0] + baserockercentre.cap_value[1];
	int sum_ref2 = baserockercentre.cap_value[2] + baserockercentre.cap_value[3];

	short offset1=0, offset2 =0;

	offset1 = (baserockercentre.cap_value[0] - baserockercentre.cap_value[1]) > 0 ? baserockercentre.cap_value[1] : baserockercentre.cap_value[0];

	offset2 = (baserockercentre.cap_value[2] - baserockercentre.cap_value[3]) > 0 ? baserockercentre.cap_value[3] : baserockercentre.cap_value[2];

	TestResultInfoR(_T("\r\ncsum_ref:(%5d,%5d),offset:(%5d,%5d,%5d,%5d)\r\n"),sum_ref1,sum_ref2,(baserockercentre.cap_value[0] - offset1),(baserockercentre.cap_value[1] - offset1),(baserockercentre.cap_value[2] - offset2),(baserockercentre.cap_value[3] - offset2));

	TestResultInfoR(_T("\r\n------------------------------------------\r\n"));

	auto x_DataList = RockerCalib.Get_X_List();
	auto y_DataList = RockerCalib.Get_Y_List();
	if (x_DataList.size()!=0)
	{
		for(unsigned short i=0; i < x_DataList.size();i++)
		{
			TestResultInfoR(_T("\r\nx_datalist[%d]:(%5d,%5d)(%5d,%5d,%5d,%5d)\r\n"),i,x_DataList[i].x_centerValue,x_DataList[i].y_centerValue,x_DataList[i].cap_value[0],x_DataList[i].cap_value[1],x_DataList[i].cap_value[2],x_DataList[i].cap_value[3]);	
		}
	}

	if (y_DataList.size()!=0)
	{
		for(unsigned short i=0; i < y_DataList.size();i++)
		{
			TestResultInfoR(_T("\r\ny_datalist[%d]:(%5d,%5d)(%5d,%5d,%5d,%5d)\r\n"),i,y_DataList[i].x_centerValue,y_DataList[i].y_centerValue,y_DataList[i].cap_value[0],y_DataList[i].cap_value[1],y_DataList[i].cap_value[2],y_DataList[i].cap_value[3]);	
		}
	}



	if( failerCount )
	{
		itemNotify.UpdateItemResult( ITEM_STA_FAIL );
		TestResultInfo( "\r\n\r\n//RockerCalib Test is Fail\r\n", ITEM_STA_FAIL );
	}
	else
	{
		itemNotify.UpdateItemResult( ITEM_STA_PASS );
		TestResultInfo( "\r\n\r\n//RockerCalib Test is Pass\r\n", ITEM_STA_PASS );
	}

	return itemNotify;
}

unsigned int CTest8006::Graph_Test(NativeTestItem& itemQuote)
{	
	unsigned int iReCode = ERROR_CODE_INVALID_PARAM, failerCount = 0;

	WorkForGraphMode( true );

	m_iRealGraphIndex = itemQuote.testCode - TEST_ITEM_GRAPH_TEST_START;
	CGraphItemTest* pGraphTest = m_vecGraphTest[m_iRealGraphIndex];
	if( NULL == pGraphTest )
	{
		GraphParam param( m_deviceNo, m_GraphTestTool );
		pGraphTest = (CGraphItemTest*)RunTimeClassFactoryInstEx(GRAPH_TYPE).CreateObject( (GRAPH_TYPE)(itemQuote.testCode), (unsigned long)&param );
		m_vecGraphTest[m_iRealGraphIndex] = pGraphTest;
	}

	//ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );

	//pGraphTest->DoInit( m_deviceNo );

	ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );

	BOOL bResult = pGraphTest->LoopAndDone(  );

	itemNotify.UpdateItemResult( bResult ? ITEM_STA_PASS : ITEM_STA_FAIL );

	TCHAR chTemp[MAX_PATH] = {0};
	if( bResult )
	{
		transformat( chTemp, _T("\r\n\r\n%s Test is Pass\r\n"), itemQuote.testName );
		TestResultInfo( chTemp, ITEM_STA_PASS );
	}
	else
	{
		transformat( chTemp, _T("\r\n\r\n%s Test is Fail\r\n"), itemQuote.testName );
		TestResultInfo( chTemp, ITEM_STA_FAIL );
	}

	return itemNotify;

}

void CTest8006::ForcePaintFlow()
{
	SetTestFlowOnLine(  );
	SM_CommBase(m_deviceNo)->SetIoVoltage( G_XMLConfig->vddVotage, G_XMLConfig->ioVddVotage, G_XMLConfig->vihVotage );
	unsigned int iReCode = WorkForGraphMode( true );
	if( ERROR_CODE_OK != iReCode ) 
	{
		SetTestFlowOffLine(); 
		return;
	}

	CGraphItemTest* pGraphTest = NULL;
	m_iRealGraphIndex = TEST_ITEM_LINEARLY_ROCKER_TEST - TEST_ITEM_GRAPH_TEST_START;
	if( NULL == m_vecGraphTest[m_iRealGraphIndex] )
	{
		GraphParam param( m_deviceNo, m_GraphTestTool );
		pGraphTest = (CGraphItemTest*)RunTimeClassFactoryInstEx(GRAPH_TYPE).CreateObject( (GRAPH_TYPE)(TEST_ITEM_LINEARLY_ROCKER_TEST), (unsigned long)&param );
		m_vecGraphTest[m_iRealGraphIndex] = pGraphTest;
	}

	pGraphTest = m_vecGraphTest[m_iRealGraphIndex];
	if( NULL != pGraphTest ) 
	{
		pGraphTest->LoopAndDone( );
	}

	//if( 0 == pGraphTest->GetTimeLeft() )
	navCallBack.onOneTestOver( m_deviceNo, 0 );
	if(G_XMLConfig->heatbeatVotage > 0)
	{
		SM_CommBase(m_deviceNo)->SetIoVoltage( G_XMLConfig->heatbeatVotage, 0, 0 );
	}

	SetTestFlowOffLine( );

}

