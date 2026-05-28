#include "checksum.h"
#include "Test310.h"
#include "../Config/Config310.h"
#include "automaticInterface.h"
#include "Rolling.h"
#include <list>
#include <algorithm>

extern CConfig* G_XMLConfig;
#define pCfg310   (( const CConfig310*)G_XMLConfig)
REGIST_RUNTIME_CLASS(TEST_TYPE, (TEST_TYPE)SEMI_IC_CHUF310, CTest310)


CTest310::CTest310()
:CTestBase()
{

}
CTest310::~CTest310()
{

}
void CTest310::SetTestContext( unsigned char deviceNo, NativeTestInterface* native )
{
	memset(&m_FoTrim, 0xFF, sizeof(m_FoTrim));
    //m_listTestItems.clear();
    CTestBase::SetTestContext( deviceNo, native );

    int indexSel = 0;  //mtk = 0

    {
        InternalItemInfo& info = m_arrayItemInfo[indexSel++];
        info.item.ucDevice = m_deviceNo;
        info.item.testCode = TEST_ITEM_MTK_CONNECT;
        info.item.testResult = ITEM_STA_NONE;
        copytextto(info.item.testName, _T("MTK"), lengthof(_T("MTK")));
        info.bSelected = pCfg310->mtk_selected;
        info.jumpIfNG = false;
        if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTestBase>( this, &CTestBase::MTKConnectTest );
    }

    {
        InternalItemInfo& info = m_arrayItemInfo[indexSel++];
        info.item.ucDevice = m_deviceNo;
        info.item.testCode = TEST_ITEM_TP_WAIT;
        info.item.testResult = ITEM_STA_NONE;
        copytextto(info.item.testName, _T("Waiting"), lengthof(_T("Waiting")));
        info.bSelected = pCfg310->way_to_start == START_BY_AUTO;
        info.jumpIfNG = false;
        if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTestBase>( this, &CTestBase::TP_WaitTest );
    }

    //////////////////////////////////////////////////////////////////////////


    {
        InternalItemInfo& info = m_arrayItemInfo[indexSel++];
        info.item.ucDevice = m_deviceNo;
        info.item.testCode = TEST_ITEM_PROJECT_CODE;
        info.item.testResult = ITEM_STA_NONE;
        copytextto(info.item.testName, _T("Project"), lengthof(_T("Project")));
        info.bSelected = platform_required_sel;
        if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest310>( this, &CTest310::ProjectCode_Test );
    }

    {
        InternalItemInfo& info = m_arrayItemInfo[indexSel++];
        info.item.ucDevice = m_deviceNo;
        info.item.testCode = TEST_ITEM_RESET_TEST;
        info.item.testResult = ITEM_STA_NONE;
        copytextto(info.item.testName, _T("Reset"), lengthof(_T("Reset")));
        info.bSelected = pCfg310->reset_selected;
        if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest310>( this, &CTest310::Reset_Test );
    }

    {
        InternalItemInfo& info = m_arrayItemInfo[indexSel++];
        info.item.ucDevice = m_deviceNo;
        info.item.testCode = TEST_ITEM_OSCTRIM_TEST_310;
        info.item.testResult = ITEM_STA_NONE;
        copytextto(info.item.testName, _T("OSCTrim"), lengthof(_T("OSCTrim")));
        info.bSelected = pCfg310->osctrim_selected;
        if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest310>( this, &CTest310::OSCTrim_Test );
    }

    {
        InternalItemInfo& info = m_arrayItemInfo[indexSel++];
        info.item.ucDevice = m_deviceNo;
        info.item.testCode = TEST_ITEM_OTP_TEST_310;
        info.item.testResult = ITEM_STA_NONE;
        copytextto(info.item.testName, _T("Otp"), lengthof(_T("Otp")));
        info.bSelected = pCfg310->otp_selected;
        if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest310>( this, &CTest310::Otp_Test );
    }

    {
        InternalItemInfo& info = m_arrayItemInfo[indexSel++];
        info.item.ucDevice = m_deviceNo;
        info.item.testCode = TEST_ITEM_CURRENT_TEST;
        info.item.testResult = ITEM_STA_NONE;
        copytextto(info.item.testName, _T("Current"), lengthof(_T("Current")));
        info.bSelected = pCfg310->current_selected;
        if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest310>( this, &CTest310::Current_Test );
    }

    {
        InternalItemInfo& info = m_arrayItemInfo[indexSel++];
        info.item.ucDevice = m_deviceNo;
        info.item.testCode = TEST_ITEM_IOVOL_TEST_310;
        info.item.testResult = ITEM_STA_NONE;
        copytextto(info.item.testName, _T("IOVoltage"), lengthof(_T("IOVoltage")));
        info.bSelected = pCfg310->iovol_selected;
        if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest310>( this, &CTest310::IOVoltage_Test );
    }

    {
        InternalItemInfo& info = m_arrayItemInfo[indexSel++];
        info.item.ucDevice = m_deviceNo;
        info.item.testCode = TEST_ITEM_ADC_TEST_310;
        info.item.testResult = ITEM_STA_NONE;
        copytextto(info.item.testName, _T("ADC"), lengthof(_T("ADC")));
        info.bSelected = pCfg310->adc_selected;
        if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest310>( this, &CTest310::ADC_Test );
    }

    {
        InternalItemInfo& info = m_arrayItemInfo[indexSel++];
        info.item.ucDevice = m_deviceNo;
        info.item.testCode = TEST_ITEM_NOISE_TEST_310;
        info.item.testResult = ITEM_STA_NONE;
        copytextto(info.item.testName, _T("Noise"), lengthof(_T("Noise")));
        info.bSelected = pCfg310->noise_selected;
        if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest310>( this, &CTest310::Noise_Test );
    }

    {
        InternalItemInfo& info = m_arrayItemInfo[indexSel++];
        info.item.ucDevice = m_deviceNo;
        info.item.testCode = TEST_ITEM_OS_TEST_310;
        info.item.testResult = ITEM_STA_NONE;
        copytextto(info.item.testName, _T("PixelDefect"), lengthof(_T("PixelDefect")));
        info.bSelected = pCfg310->pixeldefect_selected;
        if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest310>( this, &CTest310::PixelDefect_Test );
    }

    {
        InternalItemInfo& info = m_arrayItemInfo[indexSel++];
        info.item.ucDevice = m_deviceNo;
        info.item.testCode = TEST_ITEM_FLYTIME_TEST_310;
        info.item.testResult = ITEM_STA_NONE;
        copytextto(info.item.testName, _T("FlyTime"), lengthof(_T("FlyTime")));
        info.bSelected = pCfg310->flytime_selected;
        if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest310>( this, &CTest310::FlyTime_Test );
    }

    {
        InternalItemInfo& info = m_arrayItemInfo[indexSel++];
        info.item.ucDevice = m_deviceNo;
        info.item.testCode = TEST_ITEM_SRF_TEST_310;
        info.item.testResult = ITEM_STA_NONE;
        copytextto(info.item.testName, _T("SRF"), lengthof(_T("SRF")));
        info.bSelected = pCfg310->srf_selected;
        if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest310>( this, &CTest310::SRF_Test );
    }

    {
        InternalItemInfo& info = m_arrayItemInfo[indexSel++];
        info.item.ucDevice = m_deviceNo;
        info.item.testCode = TEST_ITEM_FRT_TEST_310;
        info.item.testResult = ITEM_STA_NONE;
        copytextto(info.item.testName, _T("FRT"), lengthof(_T("FRT")));
        info.bSelected = pCfg310->frt_selected;
        if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest310>( this, &CTest310::FRT_Test );
    }

    {
        InternalItemInfo& info = m_arrayItemInfo[indexSel++];
        info.item.ucDevice = m_deviceNo;
        info.item.testCode = TEST_ITEM_BOOT_TEST;
        info.item.testResult = ITEM_STA_NONE;
        copytextto(info.item.testName, _T("Boot"), lengthof(_T("Boot")));
        info.bSelected = pCfg310->boot_selected;
        if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest310>( this, &CTest310::Boot_Test );
    }

    {
        InternalItemInfo& info = m_arrayItemInfo[indexSel++];
        info.item.ucDevice = m_deviceNo;
        info.item.testCode = TEST_ITEM_CFG_TEST;
        info.item.testResult = ITEM_STA_NONE;
        copytextto(info.item.testName, _T("Config"), lengthof(_T("Config")));
        info.bSelected = pCfg310->config_selected;
        if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest310>( this, &CTest310::Config_Test );
    }

    {
        InternalItemInfo& info = m_arrayItemInfo[indexSel++];
        info.item.ucDevice = m_deviceNo;
        info.item.testCode = TEST_ITEM_TEMPERATURE_TEST_310;
        info.item.testResult = ITEM_STA_NONE;
        copytextto(info.item.testName, _T("Temperature"), lengthof(_T("Temperature")));
        info.bSelected = pCfg310->temperature_selected;
        if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest310>( this, &CTest310::Temperature_Test );
    }


    {
        InternalItemInfo& info = m_arrayItemInfo[indexSel++];
        info.item.ucDevice = m_deviceNo;
        info.item.testCode = TEST_ITEM_COMMUNICATION_TEST_310;
        info.item.testResult = ITEM_STA_NONE;
        copytextto(info.item.testName, _T("Communication"), lengthof(_T("Communication")));
        info.bSelected = pCfg310->communication_selected;
        if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest310>( this, &CTest310::Communication_Test );
    }
    {
        InternalItemInfo& info = m_arrayItemInfo[indexSel++];
        info.item.ucDevice = m_deviceNo;
        info.item.testCode = TEST_ITEM_PRESSURE_CONTACT_IMPEDANCE_TEST_310;
        info.item.testResult = ITEM_STA_NONE;
        copytextto(info.item.testName, _T("Pressure"), lengthof(_T("Pressure")));
        info.bSelected = pCfg310->pressure_contact_selected;
        if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest310>( this, &CTest310::Pressure_Contact_Test );
    }

    {
        InternalItemInfo& info = m_arrayItemInfo[indexSel++];
        info.item.ucDevice = m_deviceNo;
        info.item.testCode = TEST_ITEM_INT_TEST;
        info.item.testResult = ITEM_STA_NONE;
        copytextto(info.item.testName, _T("INT"), lengthof(_T("INT")));
        info.bSelected = pCfg310->int_selected;
        if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest310>( this, &CTest310::INT_Test );
    }


    {
        InternalItemInfo& info = m_arrayItemInfo[indexSel++];
        info.item.ucDevice = m_deviceNo;
        info.item.testCode = TEST_ITEM_EXP_LINEARLY_TEST;
        info.item.testResult = ITEM_STA_NONE;
        copytextto(info.item.testName, _T("ExpLinearly"), lengthof(_T("ExpLinearly")));
        info.bSelected = pCfg310->EXP_LINEARITY_TEST;
        if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest310>( this, &CTest310::Graph_Test );
    }

    {
        InternalItemInfo& info = m_arrayItemInfo[indexSel++];
        info.item.ucDevice = m_deviceNo;
        info.item.testCode = TEST_ITEM_FREE_PAINT_TEST;
        info.item.testResult = ITEM_STA_NONE;
        copytextto(info.item.testName, _T("FreePaint"), lengthof(_T("FreePaint")));
        info.bSelected = pCfg310->FREEPAINT_TEST;
        if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest310>( this, &CTest310::Graph_Test );
    }

    //////////////////////////////////////////////////////////////////////////
    {
        InternalItemInfo& info = m_arrayItemInfo[indexSel++];
        info.item.ucDevice = m_deviceNo;
        info.item.testCode = TEST_ITEM_TP_REMOVE;
        info.item.testResult = ITEM_STA_NONE;
        copytextto(info.item.testName, _T("Removing"), lengthof(_T("Removing")));
        info.bSelected = (pCfg310->way_to_start == START_BY_AUTO || pCfg310->way_to_start == START_BY_SN) && (pCfg310->need_remove_ic != 1);
        info.jumpIfNG = false;
        if( !info.funAddr ) info.funAddr = new CRunTimeMethod<CTest310>( this, &CTest310::TP_RemoveTest );
    }

    if( SM_ChipBase(m_deviceNo) )
    {
        CtpHalCfg halCfg;
        halCfg.protocalType = (unsigned char)pCfg310->protocalType;
        halCfg.speed = pCfg310->Speed;
        halCfg.IIC.slaveAddr = pCfg310->I2cAddr;
        halCfg.vddVoltage = pCfg310->vddVotage;
        halCfg.iovddVotage = pCfg310->ioVddVotage;
        halCfg.vihVotage = pCfg310->vihVotage;
        halCfg.icType = pCfg310->IcType;
        SM_ChipBase(m_deviceNo)->SetCommContext( halCfg );
    }

    ActionToXmlConfig();
}
void CTest310::ICArrayToSensorMatrix( unsigned short (&dataMappinged)[2][MAX_MCAP_COL], unsigned short* const dataToMapping, unsigned int dataCnt, unsigned short maxRows, unsigned short* pMaxCols )
{
    for( int iTx = 0; iTx < pCfg310->colsCnt; iTx++ )
    {
        unsigned short icChannel = pCfg310->sensor_2_ic_map[iTx];
        dataMappinged[0][iTx] = dataToMapping[icChannel];
    }
    for( int iRx = 0; iRx < pCfg310->rowsCnt; iRx++ )
    {
        unsigned short icChannel = pCfg310->sensor_2_ic_map[iRx + MAX_TX_NUM_310];
        dataMappinged[1][iRx] = dataToMapping[icChannel + MAX_TX_NUM_310];
    }
}

BOOL CTest310::CheckTpBootSame( )
{
    BOOL bCheckBootOk = FALSE;
    unsigned int iReCode = ERROR_CODE_OK;
    ISMChip310* iChip310 = (ISMChip310*)SM_ChipBase(m_deviceNo);
    if( NULL == iChip310 )   return FALSE;

    unsigned int crc_from_tp = 0, otm_time = 0, crc_bootloader = 0;
    iReCode = iChip310->GetNewBootCheckSum( &crc_from_tp, &otm_time ,&crc_bootloader);
    if( iReCode != ERROR_CODE_OK )  return FALSE;

    //TCHAR szBuffer[MAX_PATH] = {0};
    //transformat( szBuffer, _T("ID = 0x%x,   %d-%d, %d:%d:%d"), otm_time, (otm_time>>22)&0xf, (otm_time>>17)&0x1f,(otm_time>>12)&0x1f, (otm_time>>6)&0x3f, otm_time&0x3f );
    //TestResultInfo( szBuffer );
    TestResultInfoR( _T("ID = 0x%x,   %d-%d, %d:%d:%d"), otm_time, (otm_time>>22)&0xf, (otm_time>>17)&0x1f,(otm_time>>12)&0x1f, (otm_time>>6)&0x3f, otm_time&0x3f );

    if( (crc_from_tp == pCfg310->boot_check_sum) && (crc_bootloader == pCfg310->boot_loader_check_sum))
        return TRUE;

    return FALSE;
}
BOOL CTest310::CheckFlashEraseOk()
{
    unsigned int iReCode = ERROR_CODE_OK;
    ISMChip310* iChip310 = (ISMChip310*)SM_ChipBase(m_deviceNo);
    if( NULL == iChip310 )  return FALSE;

    unsigned char readBuffer[4096] = {0};
    unsigned int writeData = 0x5ee5e55e, readData = 0x00000000;
    iReCode = iChip310->WriteBurnSpace( 0xd000, (const unsigned char*)&writeData, sizeof(writeData), OTP_W_CHK | TLK_DATACHK_EX1 );
    if( iReCode != ERROR_CODE_OK ) return FALSE;

    iReCode = iChip310->ReadBurnSpace( 0xd000, (unsigned char*)&readData, sizeof(writeData) );
    if( iReCode != ERROR_CODE_OK ) return FALSE;

    if( writeData != readData )
    {
        TestResultInfo( _T("Check Erase Falsh step 1 Failed\r\n") );
        return FALSE;
    }

    writeData = 0xe55e5ee5, readData = 0x00000000;
    iReCode = iChip310->WriteBurnSpace( 0xd000, (const unsigned char*)&writeData, sizeof(writeData), OTP_W_CHK | TLK_DATACHK_EX1 );
    if( iReCode != ERROR_CODE_OK ) return FALSE;

    iReCode = iChip310->ReadBurnSpace( 0xd000, (unsigned char*)&readData, sizeof(writeData) );
    if( iReCode != ERROR_CODE_OK ) return FALSE;

    if( writeData != readData )
    {
        TestResultInfo( _T("Check Erase Falsh step 2 Failed\r\n") );
        return false;
    }

    writeData = 0xffffffff;
    iReCode = iChip310->WriteBurnSpace( 0xd000, (const unsigned char*)&writeData, sizeof(writeData), OTP_W_CHK | TLK_DATACHK_EX1 );
    if( iReCode != ERROR_CODE_OK ) return FALSE;

    iReCode = iChip310->ReadBurnSpace( 0xd000, readBuffer, sizeof(readBuffer) );
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
    iReCode = iChip310->ReadBurnSpace( 0xc000, readBuffer, 8 );
    if( iReCode != ERROR_CODE_OK ) return FALSE;

    UINT32* pIntData = (UINT32*)readBuffer;
    if( 0xffffffff == pIntData[0] && 0xffffffff == pIntData[1] )
    {
        SYSTEMTIME SysTime;
        ::GetLocalTime(&SysTime);
        pIntData[0] = (SysTime.wMonth << 22) + (SysTime.wDay << 17) + (SysTime.wHour << 12) + (SysTime.wMinute << 6) + SysTime.wSecond;
        pIntData[1] = GetTickCount();
        iChip310->WriteBurnSpace( 0xc000, readBuffer, 8, OTP_W_CHK | TLK_DATACHK_EX1 );
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

unsigned int CTest310::Temperature_Test( NativeTestItem& itemQuote )
{
    unsigned int iReCode = ERROR_CODE_COMM_ERROR;
    ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );
	int failedCount  = 0;
	TestResultInfo( _T("\r\n------------------------------Temperature Test------------------------------\r\n") );

    ISMChip310* iChip310 = (ISMChip310*)SM_ChipBase(m_deviceNo);
    if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	unsigned short tempraw[4] = {0};
	signed short tempdata[4] = {0};

    iReCode = iChip310->GetTempData( &tempraw[0], &tempraw[1], &tempraw[2], &tempraw[3]);
    if( ERROR_CODE_OK != iReCode )  return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

    iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_CTP_RST );
    SysDelay( 50 );

	for(int index = 0;index < 4;index++)
	{
		if (tempraw[index] & 0x1000)
			tempdata[index] = tempraw[index] - 0x2000;
	}
	
	TestResultInfoR( _T("Temp1 %d\tTemp2 %d\tTemp3 %d\tTemp4 %d\t\r\n"),tempdata[0],tempdata[1],tempdata[2],tempdata[3] );

	//写入OTP
	//后续添加...

    if( failedCount )
    {
        itemNotify.UpdateItemResult( ITEM_STA_FAIL );
        TestResultInfo( "\r\n\r\n//Temperature Test is Fail\r\n", ITEM_STA_FAIL );
    }
    else
    {
        itemNotify.UpdateItemResult( ITEM_STA_PASS );
        TestResultInfo( "\r\n\r\n//Temperature Test is Pass\r\n", ITEM_STA_PASS );
    }
    return itemNotify;
}

unsigned int CTest310::Otp_Test( NativeTestItem& itemQuote )
{
    unsigned int iReCode = ERROR_CODE_COMM_ERROR;
    ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );
	TestResultInfo( _T("\r\n------------------------------OTP Test------------------------------\r\n") );
	const unsigned short fct_addr = 0x28;
	const unsigned short fct_len = 24;
	unsigned int failerCount = 0;
	unsigned int ATE_Flag = 0;
	unsigned int FCT_Flag = 0;

	int log = pCfg310->simplelog;
	int log1 = pCfg310->otp_only_check;
	int log2 = pCfg310->trim_only_check;
	int ready = m_FoTrim.ate_ready;
	int ready1 = m_FoTrim.fct_ready;
	int ready2 = m_FoTrim.ate_ready;

	ISMChip310* iChip310 = (ISMChip310*)SM_ChipBase(m_deviceNo);
    if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );


    iReCode = iChip310->GetOTPStatus(&ATE_Flag,&FCT_Flag);
    if( ERROR_CODE_OK != iReCode )  return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	if((ATE_Flag == 0) && (FCT_Flag == 0)){
		failerCount = 0;
	}else if((ATE_Flag > 1) || (FCT_Flag > 1)){
		failerCount++;
		TestResultInfo( _T("Check OTP Failed\r\n") );
	}

	if(pCfg310->otp_only_check){
		if((ATE_Flag == 1) || (FCT_Flag == 1)){
			TestResultInfo( _T("ATE/FCT is free & Only check \r\n") );
			failerCount++;
		}

	}else{
		if(ATE_Flag == 1){
			if(m_FoTrim.ate_ready == 1){
				int a = 0;
				unsigned int data1 = m_FoTrim.osc52m_trim;
				unsigned int data2 = m_FoTrim.osc32k_trim;
				TestResultInfoR( _T("Write ATE 32K trim =  %d\t52M trim = %d\t\r\n"),m_FoTrim.osc52m_trim,m_FoTrim.osc32k_trim );
				iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( 0X35,m_FoTrim.osc52m_trim,m_FoTrim.osc32k_trim );
				if( iReCode != ERROR_CODE_OK ) itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
			}else{
				TestResultInfo( _T("ATE data invalid \r\n") );
				failerCount++;
			}
		}
		if(FCT_Flag == 1){
			if(m_FoTrim.fct_ready == 1){
				unsigned int fct_package[6] = {0};
				unsigned char ver_num = 0xA;
				fct_package[0] = ((uint32_t)(m_FoTrim.osc52m_freqs[2] & 0x1FF) << 22) | ((uint32_t)(m_FoTrim.osc52m_freqs[1] & 0x1FF) << 13)
							   | ((uint32_t)(m_FoTrim.osc52m_freqs[0] & 0x1FF) << 4)  | ((uint32_t)(ver_num & 0x0F));
				fct_package[1] = ((uint32_t)(m_FoTrim.temp_data[1] & 0xFFFF) << 16) |
								 ((uint32_t)(m_FoTrim.temp_data[0] & 0xFFFF));
				fct_package[2] = ((uint32_t)(m_FoTrim.temp_data[3] & 0xFFFF) << 16) |
								 ((uint32_t)(m_FoTrim.temp_data[2] & 0xFFFF));
				fct_package[3] = 0;
				fct_package[4] = 0;
				fct_package[5] = 0;
				uint8_t *pdata = (uint8_t *)fct_package;

				uint8_t checksum = 0;

				for(int i = 0; i < 23; i++) {
					checksum += pdata[i];
				}

				pdata[23] = (uint8_t)(0 - checksum);
				iReCode = iChip310->WriteBurnSpace(fct_addr,(unsigned char*)&fct_package, sizeof(fct_package),0);
				if( ERROR_CODE_OK != iReCode )  return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

			}else{
				TestResultInfo( _T("FCT data invalid \r\n") );
				failerCount++;
			}
		}


	}
	auto szBuffer = TestResultInfoR( _T("Fail = %d "),failerCount );
    if( failerCount )
    {
        TestResultInfo( "\r\n\r\n//OTP Test is Fail\r\n", ITEM_STA_FAIL );
		itemNotify.UpdateItemResult( ITEM_STA_FAIL, szBuffer);
    }
    else
    {
        TestResultInfo( "\r\n\r\n//OTP Test is Pass\r\n", ITEM_STA_PASS );
		itemNotify.UpdateItemResult( ITEM_STA_PASS, szBuffer);
    }

    return itemNotify;
}

unsigned int CTest310::Communication_Test( NativeTestItem& itemQuote )
{
    unsigned int iReCode = ERROR_CODE_COMM_ERROR;
    ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );

    return itemNotify;
}

unsigned int CTest310::Pressure_Contact_Test( NativeTestItem& itemQuote )
{
    unsigned int iReCode = ERROR_CODE_COMM_ERROR;
    ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );

    return itemNotify;
}

unsigned int CTest310::ADC_Test( NativeTestItem& itemQuote )
{
    unsigned int iReCode = ERROR_CODE_COMM_ERROR;
    ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );

	int failerCount = 0;
	TestResultInfo( _T("\r\n------------------------------ADC Test------------------------------\r\n") );

	const int readLen = CHUF310_X * CHUF310_X * 2;
    std::vector<int16_t> readBuf_tx(readLen/2 );
	std::vector<int16_t> readBuf_notx(readLen/2 );
	//std::vector<int16_t> readBuf2(CHUF310_X );
	std::vector<std::vector<short>> rawdata_tx(CHUF310_X, std::vector<short>(CHUF310_Y, 0));
	std::vector<std::vector<short>> rawdata_notx(CHUF310_X, std::vector<short>(CHUF310_Y, 0));
	//std::vector<std::vector<short>> rawdata_2(CHUF310_X, std::vector<short>(CHUF310_Y, 0));

    if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
    ISMChip310* iChip310 = (ISMChip310*)SM_ChipBase(m_deviceNo);

    iReCode = iChip310->IncokeCommand(CMD_CTP_RST);
    SysDelay( 50 );

    iReCode = iChip310->GetADCData( readBuf_tx.data(), readLen, 1);
    if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	for (int row = 0; row < CHUF310_X; row++)
	{
		for (int col = 0; col < CHUF310_Y; col++)
		{
			const int pixelIndex = row * CHUF310_Y + col;
			rawdata_tx[row][col] = readBuf_tx[pixelIndex];
		}
	}

	ColorText texttx;
	NodeVal nodetx;

	std::vector<std::vector<short>> ADC_tx_Min( CHUF310_X, std::vector<short>(CHUF310_X, pCfg310->adc_tx_min));
	std::vector<std::vector<short>> ADC_tx_Max( CHUF310_X, std::vector<short>(CHUF310_X, pCfg310->adc_tx_max));

	bool bPasstx = AnalyzeMatrixResult( rawdata_tx, ADC_tx_Min, ADC_tx_Max, texttx, nodetx, true);
	TestResultInfo( texttx );
    if( !bPasstx )
    {
        failerCount++;
        LPCTSTR strHead = _T("\r\n//========= Out of Threshold in ADC tx Test: \r\n");
        PrintNodeValue( m_ColorText, &nodetx, strHead, 0 );
    }


    iReCode = iChip310->GetADCData( readBuf_notx.data(), readLen, 0);
    if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	for (int row = 0; row < CHUF310_X; row++)
	{
		for (int col = 0; col < CHUF310_Y; col++)
		{
			const int pixelIndex = row * CHUF310_Y + col;
			rawdata_notx[row][col] = readBuf_notx[pixelIndex];
		}
	}

	ColorText textnotx;
	NodeVal nodenotx;

	std::vector<std::vector<short>> ADC_notx_Min( CHUF310_X, std::vector<short>(CHUF310_X, pCfg310->adc_notx_min));
	std::vector<std::vector<short>> ADC_notx_Max( CHUF310_X, std::vector<short>(CHUF310_X, pCfg310->adc_notx_max));

	bool bPassnotx = AnalyzeMatrixResult( rawdata_notx, ADC_notx_Min, ADC_notx_Max, textnotx, nodenotx, true);
	TestResultInfo( textnotx );
    if( !bPassnotx )
    {
        failerCount++;
        LPCTSTR strHead = _T("\r\n//========= Out of Threshold in ADC notx Test: \r\n");
        PrintNodeValue( m_ColorText, &nodenotx, strHead, 0 );
    }



    if( failerCount )
    {
        itemNotify.UpdateItemResult( ITEM_STA_FAIL );
        TestResultInfo( "\r\n\r\n//ADC Test is Fail\r\n", ITEM_STA_FAIL );
    }
    else
    {
        itemNotify.UpdateItemResult( ITEM_STA_PASS );
        TestResultInfo( "\r\n\r\n//ADC Test is Pass\r\n", ITEM_STA_PASS );
    }





    return itemNotify;
}

unsigned int CTest310::SRF_Test( NativeTestItem& itemQuote )
{
    unsigned int iReCode = ERROR_CODE_COMM_ERROR;
    ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );
	int failerCount = 0;
	TestResultInfo( _T("\r\n------------------------------SRF Test------------------------------\r\n") );

	const int readLen = 20 * 2;
	std::vector<int16_t> valueBuf(readLen / 2);
	std::vector<int16_t> codeBuf(readLen / 2);
	std::vector<int16_t> readBuf(readLen );

    if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
    ISMChip310* iChip310 = (ISMChip310*)SM_ChipBase(m_deviceNo);

    iReCode = iChip310->IncokeCommand(CMD_CTP_RST);
    SysDelay( 50 );

    iReCode = iChip310->GetSRFData( readBuf.data(), readLen * 2);
    if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	for (int i = 0; i < readLen / 2; i++)
	{
		codeBuf[i]  = readBuf[2 * i];
		valueBuf[i] = readBuf[2 * i + 1];
	}

	ColorText textcode;
	NodeVal nodecode;
	std::vector<int16_t> Code_Min( readLen / 2, 30);
	std::vector<int16_t> Code_Max( readLen / 2, 70);

	bool bPassCode = AnalyzeArrayResult( codeBuf, Code_Min, Code_Max, textcode, nodecode, false);
	TestResultInfo( textcode );

	ColorText textval;
	NodeVal nodeval;
	std::vector<int16_t> Val_Min( readLen / 2, 7000);
	std::vector<int16_t> Val_Max( readLen / 2, 12000);

	bool bPassValue = AnalyzeArrayResult( valueBuf, Val_Min, Val_Max, textval, nodeval, false);
	TestResultInfo( textval );
	
	int maxIndex = 0; 
	if (!valueBuf.empty())
	{
		auto maxIt = std::max_element(valueBuf.begin(), valueBuf.end());
		maxIndex = std::distance(valueBuf.begin(), maxIt);
	}

	const double baseFreq = 9.0;
	double srFreq = baseFreq + maxIndex * 0.25;

	TestResultInfoR( _T("\r\nSelfResonance Freq = %.2f M\r\n"), srFreq);
	if(srFreq < pCfg310->srfreq_min || srFreq > pCfg310->srfreq_max){
		failerCount++;
		TestResultInfoR( _T("srFreq = %d, th = [%d - %d]\r\n"), srFreq, pCfg310->srfreq_min, pCfg310->srfreq_max );
	}

    if( failerCount )
    {
        itemNotify.UpdateItemResult( ITEM_STA_FAIL );
        TestResultInfo( "\r\n\r\n//SRF Test is Fail\r\n", ITEM_STA_FAIL );
    }
    else
    {
        itemNotify.UpdateItemResult( ITEM_STA_PASS );
        TestResultInfo( "\r\n\r\n//SRF Test is Pass\r\n", ITEM_STA_PASS );
    }
    return itemNotify;
}

unsigned int CTest310::FlyTime_Test( NativeTestItem& itemQuote )
{
    unsigned int iReCode = ERROR_CODE_COMM_ERROR;
    ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );
	int failerCount = 0;
	TestResultInfo( _T("\r\n------------------------------FlyTime Test------------------------------\r\n") );

    const int readLen = CHUF310_X * 4;

	std::vector<int16_t> valueBuf(CHUF310_X);
	std::vector<int16_t> codeBuf(CHUF310_X);
	std::vector<int16_t> readBuf(readLen );


    if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
    ISMChip310* iChip310 = (ISMChip310*)SM_ChipBase(m_deviceNo);

    iReCode = iChip310->IncokeCommand(CMD_CTP_RST);
    SysDelay( 50 );

    iReCode = iChip310->GetFlyTimeData( readBuf.data(), readLen);
    if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	for (int i = 0; i < CHUF310_X; i++)
	{
		codeBuf[i]  = readBuf[2 * i];
		valueBuf[i] = readBuf[2 * i + 1];
	}

	double mean_code = 0.0, std_code = 0.0;
	double mean_val  = 0.0, std_val  = 0.0;

	double sum_code = 0.0, sum_val = 0.0;
	for (int i = 0; i < CHUF310_X; i++) {
		sum_code += codeBuf[i];
		sum_val  += valueBuf[i];
	}

	mean_code = sum_code / CHUF310_X;
	mean_val  = sum_val  / CHUF310_X;

	double var_code = 0.0, var_val = 0.0;
	for (int i = 0; i < CHUF310_X; i++) {
		var_code += pow(codeBuf[i] - mean_code, 2);
		var_val  += pow(valueBuf[i] - mean_val, 2);
	}

	std_code = sqrt(var_code / CHUF310_X);
	std_val  = sqrt(var_val  / CHUF310_X);


    if( std_val > (double) pCfg310->flytime_std_max )
    {
        failerCount++;
        TestResultInfoR( _T( "\r\nstd_val(%.2f) > setting max(%.2f)\r\n"), std_val, (double)pCfg310->flytime_std_max );
    }
	if( std_val < pCfg310->flytime_std_min )
    {
        failerCount++;
        TestResultInfoR( _T( "\r\nstd_val(%d) < setting min(%d)\r\n"), std_val, pCfg310->flytime_std_min );
    }

	ColorText textcode;
	NodeVal nodecode;
	std::vector<int16_t> Code_Min( CHUF310_X, 0);
	std::vector<int16_t> Code_Max( CHUF310_X, pCfg310->flytime_code_max);

	bool bPassCode = AnalyzeArrayResult( codeBuf, Code_Min, Code_Max, textcode, nodecode, false);
	TestResultInfo( textcode );
    if( !bPassCode )
    {
        failerCount++;
        LPCTSTR strHead = _T("\r\n//========= Out of Threshold in Flytime code Test: \r\n");
        PrintNodeValue( m_ColorText, &nodecode, strHead, 2 );
    }

	ColorText textvalue;
	NodeVal nodevalue;
	std::vector<int16_t> Value_Min( CHUF310_X, pCfg310->flytime_val_min);
	std::vector<int16_t> Value_Max( CHUF310_X, pCfg310->flytime_val_max);

	bool bPassValue = AnalyzeArrayResult( valueBuf, Value_Min, Value_Max, textvalue, nodevalue, false);
	TestResultInfo( textvalue );
    if( !bPassValue )
    {
        failerCount++;
        LPCTSTR strHead = _T("\r\n//========= Out of Threshold in Flytime value Test: \r\n");
        PrintNodeValue( m_ColorText, &nodevalue, strHead, 2 );
    }

    if( failerCount )
    {
        itemNotify.UpdateItemResult( ITEM_STA_FAIL );
        TestResultInfo( "\r\n\r\n//FlyTime Test is Fail\r\n", ITEM_STA_FAIL );
    }
    else
    {
        itemNotify.UpdateItemResult( ITEM_STA_PASS );
        TestResultInfo( "\r\n\r\n//FlyTime Test is Pass\r\n", ITEM_STA_PASS );
    }

	return itemNotify;
}



unsigned int CTest310::Boot_Test( NativeTestItem& itemQuote )
{
    unsigned int iReCode = ERROR_CODE_COMM_ERROR;
    ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );

    TestResultInfo( _T("\r\n------------------------------BOOT Test------------------------------\r\n") );

    ISMChip310* iChip310 = (ISMChip310*)SM_ChipBase(m_deviceNo);
    if( NULL == iChip310 )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

    // 	if( !CheckFlashEraseOk() )
    // 	{
    // 		TestResultInfo( _T("Check Erase Falsh Failed\r\n") );
    // 		return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( ERROR_CODE_CHECK_SUM_MISMATCH ) );
    // 	}

    unsigned short booVerFromTp = 0;
    iReCode = iChip310->GetBootVersion( &booVerFromTp );
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
        if( pCfg310->boot_only_check )
        {
            TestResultInfo( _T("\r\nBoot from tp is differant from setting\r\n") );
            //TestResultInfo( szBootVer );
            auto szBootVer = TestResultInfoR( _T("Ver=0x%x"), booVerFromTp );
            TestResultInfo( "\r\n\r\n//BOOT Test is Fail\r\n", ITEM_STA_FAIL );
            itemNotify.UpdateItemResult( ITEM_STA_FAIL, szBootVer );
        }
        else
        {
            //SM_CommBase(m_deviceNo)->SetIoVoltage(0x6E, pCfg310->vddVotage == pCfg310->ioVddVotage ? 0x6E : pCfg310->ioVddVotage);
            //SysDelay(50);

            TestResultInfo( _T("\r\nDownlad new boot bin...\r\n") );
            iReCode = iChip310->BurnBootBin( pCfg310->bootBinSize, pCfg310->boot_svn, m_stOneRecord.Mcap.oscTrim );
            if( iReCode == ERROR_CODE_OK )   
            {
                /*unsigned short */booVerFromTp = 0;
                iReCode = iChip310->GetBootVersion( &booVerFromTp );
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

            //SM_CommBase(m_deviceNo)->SetIoVoltage(pCfg310->vddVotage, pCfg310->ioVddVotage);
            //SysDelay(50);
        }
    }

    return itemNotify;
}
BOOL CTest310::CheckConfigSame( const unsigned char* pCfg, unsigned short len )
{
    if( len != pCfg310->cfgBinSize ) return FALSE;

    unsigned int iReCode = ERROR_CODE_OK;
    ISMChip310* iChip310 = (ISMChip310*)SM_ChipBase(m_deviceNo);
    if( NULL == iChip310 )   return FALSE;

    unsigned int check = caculate_check_sum_u32( (unsigned int*)pCfg, len );
    if( check != pCfg310->config_check_sum )
    {
        return FALSE;
    }

    for( int index = 0; index < len; index++ ) 
    {
        if( pCfg[index] != pCfg310->cfgBinBuffer[index] )
            return FALSE;
    }

    return TRUE;
}
unsigned int CTest310::MakeTraceRecord()
{
    unsigned int iReCode = ERROR_CODE_OK;
#ifdef _MSC_VER
    ISMChip310* iChip310 = (ISMChip310*)SM_ChipBase(m_deviceNo);
    //char szBuffer[MAX_PATH] = {0};
    unsigned char record_buffer[3*1024] = {0};
    //auto record_buffer = new unsigned char[2*1024];
    Trace_Info* traceInfo = (Trace_Info*)record_buffer;
    One_Record* record = (One_Record*)(record_buffer + sizeof(Trace_Info));
    tstring userInfo = pCfg310->szUserRecord ? tstring(pCfg310->szUserRecord) : _T("");
    unsigned short crc = caculate_check_sum_ex( (unsigned char*)userInfo.c_str(), userInfo.length() + 1 ) >> 16;

    iReCode = iChip310->ReadBurnSpace( AddrMakeTraceRecord, record_buffer, sizeof(Trace_Info) );
    if(iReCode != ERROR_CODE_OK) return iReCode;

    BOOL bExitSameUserRecord = FALSE;
    if(traceInfo->trace_cnt + traceInfo->reverse == 0xff)
    {
        traceInfo->tlen =  traceInfo->tlen >= 0x800 ? 0x800 : traceInfo->tlen ;
        iReCode = iChip310->ReadBurnSpace( AddrMakeTraceRecord + sizeof(Trace_Info), (unsigned char*)record, traceInfo->tlen );
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
        record->vid_pid = pCfg310->vid_pid;
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

        iReCode = iChip310->WriteBurnSpace(AddrMakeTraceRecord, record_buffer, traceInfo->tlen + sizeof(Trace_Info), OTP_W_CHK | TLK_DATACHK_EX1);
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
unsigned int CTest310::ProjectCode_Test( NativeTestItem& itemQuote )
{
    unsigned int iReCode = ERROR_CODE_OK;
    ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );

    TestResultInfo( _T("\r\n------------------------------Project Test------------------------------\r\n") );

    //MakeTraceRecord();暂时不需要屏蔽

    ISMChip310* iChip310 = (ISMChip310*)SM_ChipBase(m_deviceNo);
    if( NULL == iChip310 )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

    //iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_CTP_RST );
    //if( iReCode != ERROR_CODE_OK ) itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

    //SysDelay( 200 );

    //iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_SWITCH_IIC );
    //if( iReCode != ERROR_CODE_OK ) itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

    //iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_IDENTITY );
    //if( iReCode != ERROR_CODE_OK ) itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

    //unsigned char cfgBuffer[MAX_CFG_5562_BIN_SIZE] = {0};
    //iReCode = SM_ChipBase(m_deviceNo)->ReadCoreSpace( 0x20000000 + 0x80, (unsigned char*)cfgBuffer, pCfg310->cfgBinSize );
    //if( iReCode != ERROR_CODE_OK ) itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

    TCHAR chTemp[MAX_PATH] = {0};
    //unsigned short s = cfgBuffer[1];
    //unsigned short p = (cfgBuffer[3] << 8) + cfgBuffer[2];
    //unsigned short v = (cfgBuffer[5] << 8) + cfgBuffer[4];
    //transformat( chTemp, _T("SoftWare Ver = %d, ProjectCode = %d, VenderID = %d\r\n"), s, p, v );
    //TestResultInfo( chTemp );
    //TestResultInfoR( _T("SoftWare Ver = %d, ProjectCode = %d, VenderID = %d\r\n"), s, p, v );

    //transformat( chTemp, _T("S=%d, P=%d, V=%d"), s, p, v );

    //if( pCfg310->sVersion == s && pCfg310->pVersion == p && pCfg310->vVersion == v )
    //{
    //    if(pCfg310->cfgTestBinSize)
    //    {
    //        iReCode = iChip310->SetConfigInFctMode( (unsigned char*)pCfg310->cfgTestBinBuffer, pCfg310->cfgTestBinSize );
    //        if(iReCode != ERROR_CODE_OK)
    //        {
    //            TestResultInfo( _T("\r\nSet Config dynamic failed\r\n") );
    //            return itemNotify.UpdateItemResult( ITEM_STA_FAIL );
    //        }
    //        else
    //        {
    //            TestResultInfo( _T("\r\nSet Config dynamic succesed\r\n") );
    //        }
    //    }

    //    //frequecy lockdown
    //    iReCode = iChip310->IncokeCommand(CMD_CTP_FREQ, 3, 1);
    //    itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

    //    TestResultInfo( "\r\n\r\n//Project Test is Pass\r\n", ITEM_STA_PASS );
    //    itemNotify.UpdateItemResult( ITEM_STA_PASS, chTemp );
    //}
    //else
    //{
    //    TestResultInfo( "\r\n\r\n//Project Test is Fail\r\n", ITEM_STA_FAIL );
    //    itemNotify.UpdateItemResult( ITEM_STA_FAIL, chTemp );
    //}
	auto szBuffer = TestResultInfoR( _T("Project = %d"), 310 );
	TestResultInfo( "\r\n\r\n//Project Test is Pass\r\n", ITEM_STA_PASS );
    itemNotify.UpdateItemResult( ITEM_STA_PASS, szBuffer );

    return itemNotify;
}
unsigned int CTest310::Config_Test( NativeTestItem& itemQuote )
{
    unsigned int iReCode = ERROR_CODE_COMM_ERROR;
    ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );

    TestResultInfo( _T("\r\n------------------------------CONFIG Test------------------------------\r\n") );

    ISMChip310* iChip310 = (ISMChip310*)SM_ChipBase(m_deviceNo);
    if( NULL == iChip310 )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

    unsigned short cfgVerFromTp = 0;
    unsigned char configBuffer[MAX_CFG_5562_BIN_SIZE] = {0};
    iReCode = iChip310->GetFirmWareConfig( configBuffer, pCfg310->cfgBinSize );
    if( ERROR_CODE_OK != iReCode )  return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

    cfgVerFromTp = configBuffer[1];
    //TCHAR szConfigVer[MAX_PATH] = {0};
    //transformat( szConfigVer, _T("Ver=0x%x"), cfgVerFromTp );

    BOOL bSameConfig = CheckConfigSame( configBuffer, pCfg310->cfgBinSize );

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
        if( pCfg310->config_only_check )
        {
            TestResultInfo( _T("\r\nConfig from tp is differant from setting\r\n") );
            //TestResultInfo( szConfigVer );
            auto szConfigVer = TestResultInfoR( _T("Ver=0x%x"), cfgVerFromTp );
            TestResultInfo( "\r\n\r\n//Config Test is Fail\r\n", ITEM_STA_FAIL );
            itemNotify.UpdateItemResult( ITEM_STA_FAIL, szConfigVer );
        }
        else
        {
            //SM_CommBase(m_deviceNo)->SetIoVoltage(0x6E, pCfg310->vddVotage == pCfg310->ioVddVotage ? 0x6E : pCfg310->ioVddVotage);
            //SysDelay(50);

            TestResultInfo( _T("\r\nDownlad new config bin...\r\n") );
            iReCode = iChip310->BurnConfigBin( pCfg310->cfgBinBuffer, pCfg310->cfgBinSize );
            if( iReCode == ERROR_CODE_OK )   
            {
                memset( configBuffer, 0, sizeof(configBuffer) );
                iChip310->GetFirmWareConfig( configBuffer, pCfg310->cfgBinSize );
                BOOL bSameConfig2 = CheckConfigSame( configBuffer, pCfg310->cfgBinSize );

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

            //SM_CommBase(m_deviceNo)->SetIoVoltage(pCfg310->vddVotage, pCfg310->ioVddVotage);
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

unsigned int CTest310::OSCTrim_Test( NativeTestItem& itemQuote )
{
    int failerCnt = 0;
    unsigned int iReCode = ERROR_CODE_OK;
    
    ISMChip310* iChip310 = (ISMChip310*)SM_ChipBase(m_deviceNo);
    ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );

	TestResultInfo( _T("\r\n------------------------------OSC Trim Test------------------------------\r\n") );

	unsigned int osTrim32k = 0, osTrim52m = 0 ,rsv1 = 0,rsv2 = 0;
	unsigned int osTrim52mNo1 = 0,osTrim52mNo2 = 0,osTrim52mNo3 = 0;
    unsigned char readBuffer[64] = {0}, markBuffer[4] = {0};
    unsigned int crc;

	int log = pCfg310->simplelog;
	int log1 = pCfg310->otp_only_check;
	int log2 = pCfg310->trim_only_check;

	double value52mNo1 = pCfg310->tick_52m_standardNo1 / 1000.0;
	double value52mNo2 = pCfg310->tick_52m_standardNo2 / 1000.0;
	double value52mNo3 = pCfg310->tick_52m_standardNo3 / 1000.0;
	//fct_osc_temp_trim_310 fo_trim;

    iReCode = iChip310->GetOSCTrim( m_FoTrim, pCfg310->tick_52m_standardNo1, pCfg310->tick_52m_standardNo2, pCfg310->tick_52m_standardNo3, pCfg310->trim_only_check );
    if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

    int offset32k = (pCfg310->offset_32k) * pCfg310->tick_32k_standard;
    int offset52m = (pCfg310->offset_52m) * pCfg310->tick_52m_standard;
	int offset52mNo1 = (pCfg310->offset_52m) * pCfg310->tick_52m_standardNo1;
    int offset52mNo2 = (pCfg310->offset_52m) * pCfg310->tick_52m_standardNo2;
    int offset52mNo3 = (pCfg310->offset_52m) * pCfg310->tick_52m_standardNo3;


    int err32k = m_FoTrim.osc32k_freq - pCfg310->tick_32k_standard*1000;
    int err52m = m_FoTrim.osc52m_freq - pCfg310->tick_52m_standard*1000;
    int err52mNo1 = m_FoTrim.osc52m_meter[0] - pCfg310->tick_52m_standardNo1*1000;
    int err52mNo2 = m_FoTrim.osc52m_meter[1] - pCfg310->tick_52m_standardNo2*1000;
    int err52mNo3 = m_FoTrim.osc52m_meter[2] - pCfg310->tick_52m_standardNo3*1000;

	 TestResultInfoR( _T("Target No1=%d  No2=%d  No3=%d \r\n"),pCfg310->tick_52m_standardNo1,pCfg310->tick_52m_standardNo3,pCfg310->tick_52m_standardNo3);

    TestResultInfoR( _T("osc32k trim = %d value = %d\tosc52m trim = %d value = %d\r\n"),m_FoTrim.osc32k_trim,m_FoTrim.osc32k_freq,m_FoTrim.osc52m_trim,m_FoTrim.osc52m_freq);

    TestResultInfoR( _T("osc%.2fm trim = %d\tvalue = %d \r\nosc%.2fm trim = %d\tvalue = %d\r\nosc%.2fm trim = %d\tvalue  = %d\r\n"),
		value52mNo1,m_FoTrim.osc52m_freqs[0],m_FoTrim.osc52m_meter[0],
		value52mNo2,m_FoTrim.osc52m_freqs[1],m_FoTrim.osc52m_meter[1],
		value52mNo3,m_FoTrim.osc52m_freqs[2],m_FoTrim.osc52m_meter[2]);


	if (std::abs(err32k) > offset32k)
	{
		failerCnt++;

		TestResultInfoR(
			_T("[32K][FAIL] meter=%d target=%d err=%d limit=%d proportion=%d‰\r\n"),m_FoTrim.osc32k_freq,pCfg310->tick_32k_standard * 1000,
			std::abs(err32k),offset32k,pCfg310->offset_32k);
	}
	if (std::abs(err52m) > offset52m)
	{
		failerCnt++;

		TestResultInfoR(
			_T("[52M][FAIL] meter=%d target=%d err=%d limit=%d proportion=%d‰\r\n"),m_FoTrim.osc52m_freq,pCfg310->tick_52m_standard * 1000,
			std::abs(err52m),offset52m,pCfg310->offset_52m);
	}

	if (std::abs(err52mNo1) > offset52mNo1)
	{
		failerCnt++;

		TestResultInfoR(
			_T("[52M_NO1][FAIL] freq=%.2fM meter=%d target=%d err=%d limit=%d proportion=%d‰\r\n"),value52mNo1,m_FoTrim.osc52m_meter[0],pCfg310->tick_52m_standardNo1 * 1000,
			std::abs(err52mNo1),offset52mNo1,pCfg310->offset_52m);
	}
	if (std::abs(err52mNo2) > offset52mNo2)
	{
		failerCnt++;

		TestResultInfoR(
			_T("[52M_NO2][FAIL] freq=%.2fM meter=%d target=%d err=%d limit=%d proportion=%d‰\r\n"),value52mNo2,m_FoTrim.osc52m_meter[1],pCfg310->tick_52m_standardNo2 * 1000,
			std::abs(err52mNo2),offset52mNo2,pCfg310->offset_52m);
	}
	if (std::abs(err52mNo3) > offset52mNo3)
	{
		failerCnt++;

		TestResultInfoR(
			_T("[52M_NO3][FAIL] freq=%.2fM meter=%d target=%d err=%d limit=%d proportion=%d‰\r\n"),value52mNo3,m_FoTrim.osc52m_meter[2],pCfg310->tick_52m_standardNo3 * 1000,
			std::abs(err52mNo3),offset52mNo3,pCfg310->offset_52m);
	}

	unsigned short temprature[4] = {0};
	temprature[0] = m_FoTrim.temp_data[0];
	temprature[1] = m_FoTrim.temp_data[1];
	temprature[2] = m_FoTrim.temp_data[2];
	temprature[3] = m_FoTrim.temp_data[3];

	TestResultInfoR( _T("Temp1 %d\tTemp2 %d\tTemp3 %d\tTemp4 %d\t\r\n"),temprature[0],temprature[1],temprature[2],temprature[3] );

	auto szBuffer = TestResultInfoR( _T("32K = 0x%02x, 52M=0x%02x "), m_FoTrim.osc32k_trim, m_FoTrim.osc52m_trim );
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

 //   if(1 )//检查otp内容
 //   {
 //       if (pCfg310->trim_only_check)
 //       {
 //           failerCnt++;
 //           TestResultInfo( _T("\r\nOSCtrim only check error\r\n") );
 //           TestResultInfoR( _T("32K = 0x%02x, 52M=0x%02x \r\n"), osTrim32k, osTrim52m );

 //           TestResultInfo( "\r\n\r\n//OSCTrim Test is Fail\r\n", ITEM_STA_FAIL );
 //           itemNotify.UpdateItemResult( ITEM_STA_FAIL );
 //           return itemNotify;
 //       }
	//	else
	//	{
 //           TestResultInfo( _T("Start Trim \r\n") );
 //           SysDelay( 10 );
 //           iReCode = iChip310->GetOSCTrim( (unsigned char*)&rsv1, (unsigned char*)&osTrim52m,(unsigned char*) &osTrim32k, pCfg310->trim_speed_mode, pCfg310->tick_32k_standard, pCfg310->tick_52m_standard, rsv2 );
 //           if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
 //           testTrim.d[0][0] = osTrim52m;
 //           testTrim.d[0][1] = pCfg310->tick_52m_standard*1000;
 //           if( osTrim32k < pCfg310->trim_32k_min )
 //               failerCnt++;
 //           else if( osTrim32k > pCfg310->trim_32k_max )
 //               failerCnt++;
 //           else if( osTrim52m < pCfg310->trim_52m_min )
 //               failerCnt++;
 //           else if( osTrim52m > pCfg310->trim_52m_max )
 //               failerCnt++;

	//		if(failerCnt == 0){
 //               iReCode = iChip310->GetOSCTrim( (unsigned char*)&rsv1, (unsigned char*)&osTrim52mNo1,(unsigned char*) &rsv1, pCfg310->trim_speed_mode,0, pCfg310->tick_52m_standard, 0);
 //               if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
 //               testTrim.d[1][0] = osTrim52mNo1;
 //               testTrim.d[1][1] = pCfg310->tick_52m_standard * 1000;
 //               TestResultInfoR( _T("%.2fM=0x%02x\r\n"),pCfg310->tick_52m_standard/1000.0,osTrim52mNo1);

 //               iReCode = iChip310->GetOSCTrim( (unsigned char*)&rsv1, (unsigned char*)&osTrim52mNo2,(unsigned char*) &rsv1, pCfg310->trim_speed_mode, 0, pCfg310->tick_52m_standardNo2, 0);
 //               if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
 //               testTrim.d[2][0] = osTrim52mNo2;
 //               testTrim.d[2][1] = pCfg310->tick_52m_standardNo2 * 1000;
 //               TestResultInfoR( _T("%.2fM=0x%02x\r\n"),pCfg310->tick_52m_standardNo2/1000.0,osTrim52mNo2);

 //               iReCode = iChip310->GetOSCTrim( (unsigned char*)&rsv1, (unsigned char*)&osTrim52mNo3,(unsigned char*) &rsv1, pCfg310->trim_speed_mode,0 , pCfg310->tick_52m_standardNo3, 0);
 //               if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
 //               testTrim.d[3][0] = osTrim52mNo3;
 //               testTrim.d[3][1] = pCfg310->tick_52m_standardNo3 * 1000;
 //               TestResultInfoR( _T("%.2fM=0x%02x\r\n"),pCfg310->tick_52m_standardNo3/1000.0,osTrim52mNo3);

	//		}
	//	}


	//}
 //   fct_osc_trim_310 fo_trim;

 //   int offset32k = (pCfg310->offset_32k) * pCfg310->tick_32k_standard;
 //   int offset52m = (pCfg310->offset_52m) * pCfg310->tick_52m_standard;
	//int offset52mNo1 = (pCfg310->offset_52m) * pCfg310->tick_52m_standard;
 //   int offset52mNo2 = (pCfg310->offset_52m) * pCfg310->tick_52m_standardNo2;
 //   int offset52mNo3 = (pCfg310->offset_52m) * pCfg310->tick_52m_standardNo3;

 //   iReCode = iChip310->GetTrimeDosc(fo_trim);
 //   if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

 //   int err32k = fo_trim.osc32k_freq - pCfg310->tick_32k_standard*1000;
 //   int err52m = fo_trim.osc52m_meter[0] - pCfg310->tick_52m_standard*1000;
	//int err52mNo1 = fo_trim.osc52m_meter[1] - pCfg310->tick_52m_standard*1000;
 //   int err52mNo2 = fo_trim.osc52m_meter[2] - pCfg310->tick_52m_standardNo2*1000;
 //   int err52mNo3 = fo_trim.osc52m_meter[3] - pCfg310->tick_52m_standardNo3*1000;





 //   return itemNotify;

#if 0
    int failerCnt = 0;
    unsigned int iReCode = ERROR_CODE_OK;
    osc_trim_t testTrim;
    ISMChip310* iChip310 = (ISMChip310*)SM_ChipBase(m_deviceNo);
    ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );

    TestResultInfo( _T("\r\n------------------------------OSC Trim Test------------------------------\r\n") );

    unsigned int osTrim32k = 0, osTrim52m = 0, osTrim250m = 0,osTrimother = 0;
    unsigned char readBuffer[1024] = {0}, markBuffer[4] = {0};
    unsigned int crc;

    testTrim.sig = 0x46726530;

    iReCode = SM_ChipBase(m_deviceNo)->ReadBurnSpace( FCT_ROM_VNM_REGION, readBuffer, sizeof(readBuffer) );
    if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

    iReCode = SM_ChipBase(m_deviceNo)->ReadCoreSpace( 0x40008034, markBuffer, sizeof(markBuffer) );
    if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

    osTrim32k  = (unsigned int)readBuffer[0];
    osTrim52m  = (unsigned int)readBuffer[2];
    osTrim52m  = (osTrim52m<<8) + (unsigned int)readBuffer[1];
    osTrim250m  = (unsigned int)readBuffer[03];
    m_stOneRecord.ReleaseID = *(UINT64*)&readBuffer[8];

    crc = caculate_check_sum_u32((unsigned int*)&readBuffer[32], sizeof(osc_trim_t));

    if( 0xff != (readBuffer[1] + readBuffer[5]) 
        || 0xff != (readBuffer[2] + readBuffer[6])
        || 0xff != (readBuffer[3] + readBuffer[7])
        || osTrim250m < pCfg310->trim_250m_min 
        || osTrim250m > pCfg310->trim_250m_max
        || osTrim52m < pCfg310->trim_52m_min
        || osTrim52m > pCfg310->trim_52m_max 
        || osTrim32k < pCfg310->trim_32k_min
        || osTrim32k > pCfg310->trim_32k_max
        || (0 != crc))
    {
        if (pCfg310->trim_only_check)
        {
            failerCnt++;
            TestResultInfo( _T("\r\nOSCtrim only check error\r\n") );
            TestResultInfoR( _T("32K = 0x%02x, 96M=0x%02x, 250M=0x%02x, mark=0x%08x, crc=0x%08x"), osTrim32k, osTrim52m, osTrim250m, *(unsigned int*)markBuffer, crc);

            TestResultInfo( "\r\n\r\n//OSCTrim Test is Fail\r\n", ITEM_STA_FAIL );
            itemNotify.UpdateItemResult( ITEM_STA_FAIL );
            return itemNotify;
        }
        else
        {
            TestResultInfo( _T("Start Trim And Refresh Trim Value\r\n") );
            SysDelay( 10 );

            iReCode = iChip310->GetOSCTrim( (unsigned char*)&osTrim32k, (unsigned char*)&osTrim52m,(unsigned char*) &osTrim250m, pCfg310->trim_speed_mode, pCfg310->tick_32k_standard, pCfg310->tick_52m_standard, pCfg310->tick_250m_standard );
            if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
            testTrim.d[2][0] = osTrim52m;
            testTrim.d[2][1] = pCfg310->tick_52m_standard*1000;

            if( osTrim32k < pCfg310->trim_32k_min )
                failerCnt++;
            else if( osTrim32k > pCfg310->trim_32k_max )
                failerCnt++;
            else if( osTrim52m < pCfg310->trim_52m_min )
                failerCnt++;
            else if( osTrim52m > pCfg310->trim_52m_max )
                failerCnt++;
            else if( osTrim250m < pCfg310->trim_250m_min )
                failerCnt++;
            else if( osTrim250m > pCfg310->trim_250m_max )
                failerCnt++;

            if(failerCnt == 0){
                iReCode = iChip310->GetOSCTrim( (unsigned char*)&osTrimother, (unsigned char*)&osTrim52m,(unsigned char*) &osTrimother, pCfg310->trim_speed_mode, pCfg310->tick_32k_standard, pCfg310->tick_52m_standardNo2, 0);//88000
                if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
                testTrim.d[0][0] = osTrim52m;
                testTrim.d[0][1] = pCfg310->tick_52m_standardNo2 * 1000;
                TestResultInfoR( _T("88M=0x%02x\r\n"),osTrim52m);

                iReCode = iChip310->GetOSCTrim( (unsigned char*)&osTrimother, (unsigned char*)&osTrim52m,(unsigned char*) &osTrimother, pCfg310->trim_speed_mode, pCfg310->tick_32k_standard, pCfg310->tick_52m_standardNo3, 0);//92000
                if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
                testTrim.d[1][0] = osTrim52m;
                testTrim.d[1][1] = pCfg310->tick_52m_standardNo3 * 1000;
                TestResultInfoR( _T("92M=0x%02x\r\n"),osTrim52m);

                iReCode = iChip310->GetOSCTrim( (unsigned char*)&osTrimother, (unsigned char*)&osTrim52m,(unsigned char*) &osTrimother, pCfg310->trim_speed_mode, pCfg310->tick_32k_standard, pCfg310->tick_52m_standardNo4, 0);//100000
                if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
                testTrim.d[3][0] = osTrim52m;
                testTrim.d[3][1] = pCfg310->tick_52m_standardNo4 * 1000;
                TestResultInfoR( _T("100M=0x%02x\r\n"),osTrim52m);

                iReCode = iChip310->GetOSCTrim( (unsigned char*)&osTrimother, (unsigned char*)&osTrim52m,(unsigned char*) &osTrimother, pCfg310->trim_speed_mode, pCfg310->tick_32k_standard, pCfg310->tick_52m_standardNo5, 0);//104000
                if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
                testTrim.d[4][0] = osTrim52m;
                testTrim.d[4][1] = pCfg310->tick_52m_standardNo5 * 1000;
                TestResultInfoR( _T("104M=0x%02x\r\n"),osTrim52m);

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

                osTrim52m = testTrim.d[2][0];

                readBuffer[0] = osTrim32k;
                readBuffer[1] = osTrim52m;
                readBuffer[2] = osTrim52m>>8;
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
            *p_vid_pid = pCfg310->vid_pid;

            memcpy(&readBuffer[32], &testTrim, sizeof(testTrim));
            iReCode = SM_ChipBase(m_deviceNo)->WriteBurnSpace( FCT_ROM_VNM_REGION, readBuffer, sizeof(readBuffer), OTP_W_CHK | TLK_DATACHK_EX1 );
            if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

        }

    }
    fct_osc_trim_310 fo_trim;

    int offset32k = (pCfg310->offset_32k) * pCfg310->tick_32k_standard;
    int offset96m = (pCfg310->offset_52m) * pCfg310->tick_52m_standard;
    int offset88m = (pCfg310->offset_52m) * pCfg310->tick_52m_standardNo2;
    int offset92m = (pCfg310->offset_52m) * pCfg310->tick_52m_standardNo3;
    int offset100m = (pCfg310->offset_52m) * pCfg310->tick_52m_standardNo4;
    int offset104m = (pCfg310->offset_52m) * pCfg310->tick_52m_standardNo5;



    iReCode = iChip310->GetTrimeDosc(fo_trim);
    if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

    int err32k = fo_trim.osc32k_freq - pCfg310->tick_32k_standard*1000;
    int err88m = fo_trim.osc52m_meter[0] - pCfg310->tick_52m_standardNo2*1000;
    int err92m = fo_trim.osc52m_meter[1] - pCfg310->tick_52m_standardNo3*1000;
    int err96m = fo_trim.osc52m_meter[2] - pCfg310->tick_52m_standard*1000;
    int err100m = fo_trim.osc52m_meter[3] - pCfg310->tick_52m_standardNo4*1000;
    int err104m = fo_trim.osc52m_meter[4] - pCfg310->tick_52m_standardNo5*1000;



    TestResultInfoR( _T("osc32k = %d, osc88m = %d, osc92m = %d, osc96m = %d, osc100m = %d, osc104m = %d, osc250m = %d\r\n"),
        fo_trim.osc32k_freq,fo_trim.osc52m_meter[0],fo_trim.osc52m_meter[1],fo_trim.osc52m_meter[2],fo_trim.osc52m_meter[3],fo_trim.osc52m_meter[4],fo_trim.osc250m_freq);
    if(abs(err32k) > offset32k )
    {
        failerCnt++;
        TestResultInfoR( _T("error 32k:Actual offset(%d), offset(%d), proportion(‰)(%d)\r\n"),abs(err32k),offset32k, pCfg310->offset_32k);
    }
    if((abs(err88m) > offset88m) ||(abs(err92m) > offset92m) || (abs(err96m) > offset96m) || (abs(err100m) > offset100m) || (abs(err104m) > offset104m))
    {
        failerCnt++;
        TestResultInfoR( _T("error 96m:Actual offset(%d, %d, %d, %d, %d), offset(%d, %d, %d, %d, %d), proportion(‰)(%d)\r\n")
            ,abs(err88m),abs(err92m),abs(err96m),abs(err100m),abs(err104m),offset88m,offset92m,offset96m,offset100m,offset104m, pCfg310->offset_52m);
    }
    if(abs(err250m) > offset250m )
    {
        failerCnt++;
        TestResultInfoR( _T("error 250m:Actual offset(%d), offset(%d), proportion(‰)(%d)\r\n"),abs(err250m),offset250m, pCfg310->offset_250m);
    }

    m_stOneRecord.ReleaseID = *(UINT64*)&readBuffer[8];
    UINT32 otm_time = *(UINT32*)&m_stOneRecord.ReleaseID;
    //transformat( szBuffer, _T("ICID = 0x%llx,   %d-%d, %d:%d:%d\r\n"), m_stOneRecord.ReleaseID, (otm_time>>22)&0xf, (otm_time>>17)&0x1f,(otm_time>>12)&0x1f, (otm_time>>6)&0x3f, otm_time&0x3f );
    //TestResultInfo( szBuffer );
    TestResultInfoR( _T("ICID = 0x%llx,   %d-%d, %d:%d:%d\r\n"), m_stOneRecord.ReleaseID, (otm_time>>22)&0xf, (otm_time>>17)&0x1f,(otm_time>>12)&0x1f, (otm_time>>6)&0x3f, otm_time&0x3f );

    m_stOneRecord.Mcap.oscTrim = *((unsigned int*)readBuffer);
    //transformat( szBuffer, _T("32K = h%02x, 96M=h%02x, 250M=h%02x, mark=0x%08x"), osTrim32k, osTrim52m, osTrim250m, *(unsigned int*)markBuffer );
    //TestResultInfo( szBuffer );
    auto szBuffer = TestResultInfoR( _T("32K = 0x%02x, 96M=0x%02x, 250M=0x%02x, mark=0x%08x"), osTrim32k, osTrim52m, osTrim250m, *(unsigned int*)markBuffer );

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
#endif
}
unsigned int CTest310::Current_Test( NativeTestItem& itemQuote )
{
    TEST_ITEM_STATUS itemStatus = ITEM_STA_NONE;
    for( int index = 0; index < 3; index++ )
    {
        itemStatus = (TEST_ITEM_STATUS)Current_TestEx( itemQuote );
        if( itemStatus == ITEM_STA_PASS ) break;
    }
    return itemStatus;
}
unsigned int CTest310::Current_TestEx( NativeTestItem& itemQuote )
{
    int failedCount = 0;
    unsigned int iReCode = ERROR_CODE_COMM_ERROR;
    ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );

    TestResultInfo( _T("\r\n------------------------------Current Test------------------------------\r\n") );

    ISMChip310* iChip310 = (ISMChip310*)SM_ChipBase(m_deviceNo);
    if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

    iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand(CMD_CTP_RST);
    if (iReCode != ERROR_CODE_OK) return itemNotify.UpdateItemResult(ITEM_STA_EXCEPTION, GetErrorMessage(iReCode));
    SysDelay(50);

    short deepCurrent = 0, sleepCurrent = 0, activeCurrent = 0, idleCurrent = 0;
    short vbus_deepCurrent = 0, vbus_sleepCurrent = 0, vbus_activeCurrent = 0;
    short level[2][3] = {
        pCfg310->active_current_min, pCfg310->sleep_current_min, pCfg310->idle_current_min,
        pCfg310->active_current_max, pCfg310->sleep_current_max, pCfg310->idle_current_max,
    };
    //iReCode = iChip310->GetCurrent( level, (unsigned short*)&activeCurrent, (unsigned short*)&sleepCurrent, (unsigned short*)&deepCurrent, (unsigned short*)&idleCurrent );
    iReCode = iChip310->GetCurrent310( level, (unsigned short*)&idleCurrent, (unsigned short*)&sleepCurrent, (unsigned short*)&activeCurrent,(unsigned short*)&vbus_activeCurrent, (unsigned short*)&vbus_sleepCurrent, (unsigned short*)&vbus_deepCurrent);
    if( ERROR_CODE_OK != iReCode )  return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

    iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_CTP_RST );
    SysDelay( 50 );

    //TCHAR szTmep[MAX_PATH] = {0};

    {
        m_stOneRecord.current_mode1 = activeCurrent;
        m_stOneRecord.current_mode2 = sleepCurrent;
        m_stOneRecord.current_mode3 = deepCurrent;
        //transformat( szTmep, _T("\r\nactive = %d(mA), sleep = %d(uA), deep = %d(uA)\r\n"), activeCurrent, sleepCurrent, deepCurrent );
        //TestResultInfo( szTmep );
        TestResultInfoR( _T("\r\navdd_active = %d(uA), avdd_idle = %d(uA)，  avdd_sleep = %d(uA)\r\n"), activeCurrent, idleCurrent, sleepCurrent);
        //TestResultInfoR( _T("\r\nvbus_active = %d(mA), vbus_sleep = %d(uA), vbus_deep = %d(uA)\r\n"), vbus_activeCurrent, vbus_sleepCurrent, vbus_deepCurrent);
    }
    if( activeCurrent < pCfg310->active_current_min )
    {
        failedCount++;
        //transformat( szTmep, _T( "\r\nactive(%d) < setting min(%d)\r\n"), activeCurrent, pCfg310->active_current_min );
        //TestResultInfo( szTmep );
        TestResultInfoR( _T( "\r\nactive(%d) < setting min(%d)\r\n"), activeCurrent, pCfg310->active_current_min );
    }
    if( activeCurrent > pCfg310->active_current_max )
    {
        failedCount++;
        //transformat( szTmep, _T( "\r\nactive(%d) > setting max(%d)\r\n"), activeCurrent, pCfg310->active_current_max );
        //TestResultInfo( szTmep );
        TestResultInfoR( _T( "\r\nactive(%d) > setting max(%d)\r\n"), activeCurrent, pCfg310->active_current_max );
    }
    if( idleCurrent < pCfg310->idle_current_min )
    {
        failedCount++;
        //transformat( szTmep, _T( "\r\ndeep(%d) < setting min(%d)\r\n"), deepCurrent, pCfg310->deep_current_min );
        //TestResultInfo( szTmep );
        TestResultInfoR( _T( "\r\nidle(%d) < setting min(%d)\r\n"), idleCurrent, pCfg310->idle_current_min );
    }
    if( idleCurrent > pCfg310->idle_current_max )
    {
        failedCount++;
        //transformat( szTmep, _T( "\r\ndeep(%d) > setting max(%d)\r\n"), deepCurrent, pCfg310->deep_current_max );
        //TestResultInfo( szTmep );
        TestResultInfoR( _T( "\r\nidle(%d) > setting max(%d)\r\n"), idleCurrent, pCfg310->idle_current_max );
    }
    if( sleepCurrent < pCfg310->sleep_current_min )
    {
        failedCount++;
        //transformat( szTmep, _T( "\r\nsleep(%d) < setting min(%d)\r\n"), sleepCurrent, pCfg310->sleep_current_min );
        //TestResultInfo( szTmep );
        TestResultInfoR( _T( "\r\nsleep(%d) < setting min(%d)\r\n"), sleepCurrent, pCfg310->sleep_current_min );
    }
    if( sleepCurrent > pCfg310->sleep_current_max )
    {
        failedCount++;
        //transformat( szTmep, _T( "\r\nsleep(%d) > setting max(%d)\r\n"), sleepCurrent, pCfg310->sleep_current_max );
        //TestResultInfo( szTmep );
        TestResultInfoR( _T( "\r\nsleep(%d) > setting max(%d)\r\n"), sleepCurrent, pCfg310->sleep_current_max );
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

unsigned int CTest310::PixelDefect_Test( NativeTestItem& itemQuote )
{
    bool isCsv = false;
    int failerCount = 0;
    unsigned int iReCode = ERROR_CODE_COMM_ERROR;
    ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );

	const int oneFrameLen = CHUF310_N * 2;

		// 单次读取缓冲区
    std::vector<int16_t> readBuf0(oneFrameLen );
	std::vector<int16_t> readBuf1(oneFrameLen );
	std::vector<int16_t> readBuf2(oneFrameLen );
	std::vector<std::vector<short>> rawdata_0(CHUF310_X, std::vector<short>(CHUF310_Y, 0));
	std::vector<std::vector<short>> rawdata_1(CHUF310_X, std::vector<short>(CHUF310_Y, 0));
	std::vector<std::vector<short>> rawdata_2(CHUF310_X, std::vector<short>(CHUF310_Y, 0));

	std::vector<std::vector<double>> gian_1_0(CHUF310_X, std::vector<double>(CHUF310_Y, 0));
	std::vector<std::vector<double>> gian_2_1(CHUF310_X, std::vector<double>(CHUF310_Y, 0));


	TestResultInfo( _T("\r\n------------------------------PixelDefect Test------------------------------\r\n") );

    if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
    ISMChip310* iChip310 = (ISMChip310*)SM_ChipBase(m_deviceNo);

    iReCode = iChip310->IncokeCommand(CMD_CTP_RST);
    SysDelay( 500 );

    iReCode = iChip310->GetPixelDefectData( readBuf0.data(),readBuf1.data(),readBuf2.data(), oneFrameLen );
    if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	for (int row = 0; row < CHUF310_X; row++)
	{
		for (int col = 0; col < CHUF310_Y; col++)
		{
			const int pixelIndex =
				row * CHUF310_Y + col;

			rawdata_0[row][col] = readBuf0[pixelIndex];
			rawdata_1[row][col] = readBuf1[pixelIndex];
			rawdata_2[row][col] = readBuf2[pixelIndex];

			gian_1_0[row][col] = (double)rawdata_1[row][col] / rawdata_0[row][col];
			gian_2_1[row][col] = (double)rawdata_2[row][col] / rawdata_1[row][col];
		}
	}

	ColorText text1_0;
	NodeVal node1_0;

	std::vector<std::vector<double>> gian_1_0_Min( CHUF310_X, std::vector<double>(CHUF310_X, pCfg310->gain1_0_min));
	std::vector<std::vector<double>> gian_1_0_Max( CHUF310_X, std::vector<double>(CHUF310_X, pCfg310->gain1_0_max));

	bool bPass1_0 = AnalyzeMatrixResult( gian_1_0, gian_1_0_Min, gian_1_0_Max, text1_0, node1_0, true);
	if(true){
		TestResultInfo( text1_0 );
	}
	
    if( !bPass1_0 )
    {
        failerCount++;
        LPCTSTR strHead = _T("\r\n//========= Out of Threshold in Gain 1-0 Test: \r\n");
        PrintNodeValue( m_ColorText, &node1_0, strHead, 2 );
    }

	ColorText text2_1;
	NodeVal node2_1;

	std::vector<std::vector<double>> gian_2_1_Min( CHUF310_X, std::vector<double>(CHUF310_X, pCfg310->gain2_1_min));
	std::vector<std::vector<double>> gian_2_1_Max( CHUF310_X, std::vector<double>(CHUF310_X, pCfg310->gain2_1_max));

	bool bPass2_1 = AnalyzeMatrixResult( gian_2_1, gian_2_1_Min, gian_2_1_Max, text2_1, node2_1, true);
	if(true){
		TestResultInfo( text2_1 );
	}
    if( !bPass2_1 )
    {
        failerCount++;
        LPCTSTR strHead = _T("\r\n//========= Out of Threshold in Gain 2 1 Test: \r\n");
        PrintNodeValue( m_ColorText, &node2_1, strHead, 2 );
    }

	std::vector<std::vector<short>> raw_Min( CHUF310_X, std::vector<short>(CHUF310_X, pCfg310->pixel_raw_min));
	std::vector<std::vector<short>> raw_Max( CHUF310_X, std::vector<short>(CHUF310_X, pCfg310->pixel_raw_max));

	ColorText textraw0;
	NodeVal noderaw0;
	bool bPassraw0 = AnalyzeMatrixResult( rawdata_0, raw_Min, raw_Max, textraw0, noderaw0, true);
	if(true){
		TestResultInfo( textraw0 );
	}
    if( !bPassraw0 )
    {
        failerCount++;
        LPCTSTR strHead = _T("\r\n//========= Out of Threshold in Raw0 Test: \r\n");
        PrintNodeValue( m_ColorText, &noderaw0, strHead, 0 );
    }

	ColorText textraw1;
	NodeVal noderaw1;
	bool bPassraw1 = AnalyzeMatrixResult( rawdata_0, raw_Min, raw_Max, textraw1, noderaw1, true);
	if(true){
		TestResultInfo( textraw1 );
	}
    if( !bPassraw1 )
    {
        failerCount++;
        LPCTSTR strHead = _T("\r\n//========= Out of Threshold in Raw1 Test: \r\n");
        PrintNodeValue( m_ColorText, &noderaw1, strHead, 0 );
    }

	ColorText textraw2;
	NodeVal noderaw2;
	bool bPassraw2 = AnalyzeMatrixResult( rawdata_2, raw_Min, raw_Max, textraw2, noderaw2, true);
	if(true){
		TestResultInfo( textraw2 );
	}
    if( !bPassraw2 )
    {
        failerCount++;
        LPCTSTR strHead = _T("\r\n//========= Out of Threshold in Raw2 Test: \r\n");
        PrintNodeValue( m_ColorText, &noderaw2, strHead, 0 );
    }


    if( failerCount )
    {
        itemNotify.UpdateItemResult( ITEM_STA_FAIL );
        TestResultInfo( "\r\n\r\n//PixelDefect Test is Fail\r\n", ITEM_STA_FAIL );
    }
    else
    {
        itemNotify.UpdateItemResult( ITEM_STA_PASS );
        TestResultInfo( "\r\n\r\n//PixelDefect Test is Pass\r\n", ITEM_STA_PASS );
    }

	return itemNotify;
#if 0
    const int max_short_adc_num = (20+42);
    unsigned short shortAdc[max_short_adc_num] = {0};
    unsigned short adcMatrix[2][MAX_MCAP_COL] = {0};
    AnalyzeInfo info( pCfg310->rowsCnt, pCfg310->colsCnt, 0, false );

    

    if(OP_LIKE_YY == G_XMLConfig->selected_format || OP_LIKE_XY == G_XMLConfig->selected_format)
    {
        isCsv = true;
    }

    iReCode = iChip310->IncokeCommand(CMD_CTP_RST);
    SysDelay( 500 );

    iReCode = iChip310->GetShortData( shortAdc, max_short_adc_num * 2 );
    if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

    unsigned short maxCols[] = { pCfg310->colsCnt, pCfg310->rowsCnt };
    ICArrayToSensorMatrix( adcMatrix, shortAdc, max_short_adc_num, 2, maxCols );

    NodeVal nodeOutRange;
    NodeVal nodeOutRange_add;
    unsigned short adcMin[2][MAX_MCAP_COL] = {0};
    unsigned short adcMax[2][MAX_MCAP_COL] = {0}; 
    ColorText textTemp( _T("\r\nShort Data:\r\n") );
    ColorText textTemp_add( _T("\r\nAdditional Short Data:\r\n") );
    FillMatrixUseValue( adcMin, (unsigned short)0 );
    FillMatrixRowUseValue( adcMax, pCfg310->short_tx_max, 0 );
    FillMatrixRowUseValue( adcMax, pCfg310->short_rx_max, 1 );
    adcMax[0][6] = 1300;
    bool bResult = AnalyzeTestResultMSCapJudge<unsigned short>( adcMatrix, adcMin, adcMax, pCfg310->invalid_node, info, textTemp, nodeOutRange, isCsv );
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
#endif
}


unsigned int CTest310::FRT_Test( NativeTestItem& itemQuote )
{
    int failerCnt = 0;
    unsigned int iReCode = ERROR_CODE_COMM_ERROR, errCode = 0;
    ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );
    unsigned char retBuffer[20];
    //char tempBuffer[MAX_PATH];

    TestResultInfo( _T("\r\n------------------------------FRT Test------------------------------\r\n") );

    if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
    ISMChip310* iChip310 = (ISMChip310*)SM_ChipBase(m_deviceNo);

    iReCode = iChip310->IncokeCommand( CMD_RAM_TST, 0, 0, 0, retBuffer );
    if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

    errCode = *(unsigned int*)&retBuffer[2];
    if(0x54000000 != errCode)
    {
        failerCnt++;
        //transformat( tempBuffer, _T("ReadCoreSpace, Code = 0x%x\r\n"), errCode );
        //TestResultInfo( tempBuffer );
        TestResultInfoR( _T("ReadCoreSpace, Code = 0x%x\r\n"), errCode );
    }


    iReCode = iChip310->IncokeCommand( CMD_FLASH_TST, 0, 0, 0, retBuffer );
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
unsigned int CTest310::IOVoltage_Test( NativeTestItem& itemQuote )
{
	int failerCnt = 0;
    unsigned int iReCode = ERROR_CODE_COMM_ERROR;
    ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );

	TestResultInfo( _T("\r\n------------------------------IOVoltage Test------------------------------\r\n") );

	if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
    ISMChip310* iChip310 = (ISMChip310*)SM_ChipBase(m_deviceNo);

    unsigned int ioVols[2][10] = {0};
    iReCode = iChip310->GetIoVoltage( ioVols );
    if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

	TestResultInfoR( _T("\r\n"));
	TestResultInfoR( _T("IOV = 1.8V  High : int0 vol = %-6d,	int2 vol = %-6d\r\n"), ioVols[0][1], ioVols[0][0] );
	TestResultInfoR( _T("IOV = 1.8V  Low  : int0 vol = %-6d,	int2 vol = %-6d\r\n"), ioVols[0][3], ioVols[0][2] );

	TestResultInfoR( _T("IOV = 1.2V  High : int0 vol = %-6d,	int2 vol = %-6d\r\n"), ioVols[1][1], ioVols[1][0] );
	TestResultInfoR( _T("IOV = 1.2V  Low  : int0 vol = %-6d,	int2 vol = %-6d\r\n"), ioVols[1][3], ioVols[1][2] );

	TestResultInfoR( _T("\r\n"));
	if(ioVols[0][1] < pCfg310->int0_1p8_high_min || ioVols[0][1] > pCfg310->int0_1p8_high_max){
        failerCnt++;
        TestResultInfoR( _T("int0 vol = %d, th = [%d - %d]\r\n"), ioVols[0][1], pCfg310->int0_1p8_high_min, pCfg310->int0_1p8_high_max );
	}
	if(ioVols[0][0] < pCfg310->int2_1p8_high_min || ioVols[0][0] > pCfg310->int2_1p8_high_max){
        failerCnt++;
        TestResultInfoR( _T("int2 vol = %d, th = [%d - %d]\r\n"), ioVols[0][0], pCfg310->int2_1p8_high_min, pCfg310->int2_1p8_high_max );
	}

	if(ioVols[0][3] < pCfg310->int0_1p8_low_min || ioVols[0][3] > pCfg310->int0_1p8_low_max){
        failerCnt++;
        TestResultInfoR( _T("int0 vol = %d, th = [%d - %d]\r\n"), ioVols[0][3], pCfg310->int0_1p8_low_min, pCfg310->int0_1p8_low_max );
	}
	if(ioVols[0][2] < pCfg310->int2_1p8_low_min || ioVols[0][2] > pCfg310->int2_1p8_high_max){
        failerCnt++;
        TestResultInfoR( _T("int2 vol = %d, th = [%d - %d]\r\n"), ioVols[0][2], pCfg310->int2_1p8_low_min, pCfg310->int2_1p8_low_max );
	}


	if(ioVols[1][1] < pCfg310->int0_1p2_high_min || ioVols[1][1] > pCfg310->int0_1p2_high_max){
        failerCnt++;
        TestResultInfoR( _T("int0 vol = %d, th = [%d - %d]\r\n"), ioVols[1][1], pCfg310->int0_1p2_high_min, pCfg310->int0_1p2_high_max );
	}
	if(ioVols[1][0] < pCfg310->int2_1p2_high_min || ioVols[1][0] > pCfg310->int2_1p2_high_max){
        failerCnt++;
        TestResultInfoR( _T("int2 vol = %d, th = [%d - %d]\r\n"), ioVols[1][0], pCfg310->int2_1p2_high_min, pCfg310->int2_1p2_high_max );
	}

	if(ioVols[1][3] < pCfg310->int0_1p2_low_min || ioVols[1][3] > pCfg310->int0_1p2_low_max){
        failerCnt++;
        TestResultInfoR( _T("int0 vol = %d, th = [%d - %d]\r\n"), ioVols[1][3], pCfg310->int0_1p2_low_min, pCfg310->int0_1p2_low_max );
	}
	if(ioVols[1][2] < pCfg310->int2_1p2_low_min || ioVols[1][2] > pCfg310->int2_1p2_high_max){
        failerCnt++;
        TestResultInfoR( _T("int2 vol = %d, th = [%d - %d]\r\n"), ioVols[1][2], pCfg310->int2_1p2_low_min, pCfg310->int2_1p2_low_max );
	}

	if(ioVols[0][4] != 0 || ioVols[1][4] != 0){
        failerCnt++;
        TestResultInfoR( _T("IOV 1.62V ret = %d , 1.08V ret = %d\r\n"), ioVols[0][4],ioVols[1][4] );
	}else{

		TestResultInfoR( _T("IOV 1.62V  & 1.08V trans test PASS\r\n"));
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
#if 0
    int failerCnt = 0;
    unsigned int iReCode = ERROR_CODE_COMM_ERROR;
    ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );
    //TCHAR szTemp[MAX_PATH] = {0};

    TestResultInfo( _T("\r\n------------------------------IOVoltage Test------------------------------\r\n") );

    if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
    ISMChip310* iChip310 = (ISMChip310*)SM_ChipBase(m_deviceNo);

    unsigned int ioVols[2][10] = {0};
    iReCode = iChip310->GetIoVoltage( ioVols );
    if( iReCode != ERROR_CODE_OK ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

    if( PROTOCAL_IIC == pCfg310->protocalType )
    {
        //transformat( szTemp, _T("pin = low,  int vol = %-6d,	sda vol = %-6d,	scl vol = %-6d\r\n"), ioVols[0][2], ioVols[0][0], ioVols[0][1] );
        //TestResultInfo( szTemp );
        TestResultInfoR( _T("pin = low,  int vol = %-6d,	sda vol = %-6d,	scl vol = %-6d\r\n"), ioVols[0][2], ioVols[0][0], ioVols[0][1] );
        //transformat( szTemp, _T("pin = high, int vol = %-6d,	sda vol = %-6d,	scl vol = %-6d\r\n"), ioVols[1][2], ioVols[1][0], ioVols[1][1] );
        //TestResultInfo( szTemp );
        TestResultInfoR( _T("pin = high, int vol = %-6d,	sda vol = %-6d,	scl vol = %-6d\r\n"), ioVols[1][2], ioVols[1][0], ioVols[1][1] );
    }
    else if( PROTOCAL_SPI == pCfg310->protocalType )
    {
        //transformat( szTemp, _T("pin = low,  int vol = %-6d,	csn vol = %-6d,	mosi vol = %-6d,	miso = %-6d,	clk = %-6d\r\n"), ioVols[0][2], ioVols[0][3], ioVols[0][4], ioVols[0][5], ioVols[0][6] );
        //TestResultInfo( szTemp );
        TestResultInfoR( _T("pin = low,  int vol = %-6d,	csn vol = %-6d,	mosi vol = %-6d,	miso = %-6d,	clk = %-6d\r\n"), ioVols[0][2], ioVols[0][3], ioVols[0][4], ioVols[0][5], ioVols[0][6] );
        //transformat( szTemp, _T("pin = high, int vol = %-6d,	csn vol = %-6d,	mosi vol = %-6d,	miso = %-6d,	clk = %-6d\r\n"), ioVols[1][2], ioVols[1][3], ioVols[1][4], ioVols[1][5], ioVols[1][6] );
        //TestResultInfo( szTemp );
        TestResultInfoR( _T("pin = high, int vol = %-6d,	csn vol = %-6d,	mosi vol = %-6d,	miso = %-6d,	clk = %-6d\r\n"), ioVols[1][2], ioVols[1][3], ioVols[1][4], ioVols[1][5], ioVols[1][6] );
    }

    if( ioVols[0][2] < pCfg310->int_low_min || ioVols[0][2] > pCfg310->int_low_max )
    {
        failerCnt++;
        //transformat( szTemp, _T("int vol = %d, th = [%d - %d]\r\n"), ioVols[0][2], pCfg310->int_low_min, pCfg310->int_low_max );
        //TestResultInfo( szTemp );
        TestResultInfoR( _T("int vol = %d, th = [%d - %d]\r\n"), ioVols[0][2], pCfg310->int_low_min, pCfg310->int_low_max );
    }
    if( ioVols[1][2] < pCfg310->int_high_min || ioVols[1][2] > pCfg310->int_high_max )
    {
        failerCnt++;
        //transformat( szTemp, _T("int vol = %d, th = [%d - %d]\r\n"), ioVols[1][2], pCfg310->int_high_min, pCfg310->int_high_max );
        //TestResultInfo( szTemp );
        TestResultInfoR( _T("int vol = %d, th = [%d - %d]\r\n"), ioVols[1][2], pCfg310->int_high_min, pCfg310->int_high_max );
    }

    if( PROTOCAL_IIC == pCfg310->protocalType )
    {
        if( ioVols[0][0] < pCfg310->iic_low_min || ioVols[0][0] > pCfg310->iic_low_max )
        {
            failerCnt++;
            //transformat( szTemp, _T("sda vol = %d, th = [%d - %d]\r\n"), ioVols[0][0], pCfg310->iic_low_min, pCfg310->iic_low_max );
            //TestResultInfo( szTemp );
            TestResultInfoR( _T("sda vol = %d, th = [%d - %d]\r\n"), ioVols[0][0], pCfg310->iic_low_min, pCfg310->iic_low_max);
        }
        if( ioVols[1][0] < pCfg310->iic_high_min || ioVols[1][0] > pCfg310->iic_high_max )
        {
            failerCnt++;
            //transformat( szTemp, _T("sda vol = %d, th = [%d - %d]\r\n"), ioVols[1][0], pCfg310->iic_high_min, pCfg310->iic_high_max );
            //TestResultInfo( szTemp );
            TestResultInfoR( _T("sda vol = %d, th = [%d - %d]\r\n"), ioVols[1][0], pCfg310->iic_high_min, pCfg310->iic_high_max );
        }

        if( ioVols[0][1] < pCfg310->iic_low_min || ioVols[0][1] > pCfg310->iic_low_max )
        {
            failerCnt++;
            //transformat( szTemp, _T("scl vol = %d, th = [%d - %d]\r\n"), ioVols[0][1], pCfg310->iic_low_min, pCfg310->iic_low_max );
            //TestResultInfo( szTemp );
            TestResultInfoR( _T("scl vol = %d, th = [%d - %d]\r\n"), ioVols[0][1], pCfg310->iic_low_min, pCfg310->iic_low_max );
        }
        if( ioVols[1][1] < pCfg310->iic_high_min || ioVols[1][1] > pCfg310->iic_high_max )
        {
            failerCnt++;
            //transformat( szTemp, _T("scl vol = %d, th = [%d - %d]\r\n"), ioVols[1][1], pCfg310->iic_high_min, pCfg310->iic_high_max );
            //TestResultInfo( szTemp );
            TestResultInfoR( _T("scl vol = %d, th = [%d - %d]\r\n"), ioVols[1][1], pCfg310->iic_high_min, pCfg310->iic_high_max );
        }
    }
    else if( PROTOCAL_SPI == pCfg310->protocalType )
    {
        if( ioVols[0][3] < pCfg310->spi_low_min || ioVols[0][3] > pCfg310->spi_low_max )
        {
            failerCnt++;
            //transformat( szTemp, _T("csn vol = %d, th = [%d - %d]\r\n"), ioVols[0][3], pCfg310->spi_low_min, pCfg310->spi_low_max );
            //TestResultInfo( szTemp );
            TestResultInfoR( _T("csn vol = %d, th = [%d - %d]\r\n"), ioVols[0][3], pCfg310->spi_low_min, pCfg310->spi_low_max );
        }
        if( ioVols[1][3] < pCfg310->spi_high_min || ioVols[1][3] > pCfg310->spi_high_max )
        {
            failerCnt++;
            //transformat( szTemp, _T("csn vol = %d, th = [%d - %d]\r\n"), ioVols[1][3], pCfg310->spi_high_min, pCfg310->spi_high_max );
            //TestResultInfo( szTemp );
            TestResultInfoR( _T("csn vol = %d, th = [%d - %d]\r\n"), ioVols[1][3], pCfg310->spi_high_min, pCfg310->spi_high_max );
        }

        if( ioVols[0][4] < pCfg310->spi_low_min || ioVols[0][4] > pCfg310->spi_low_max )
        {
            failerCnt++;
            //transformat( szTemp, _T("mosi vol = %d, th = [%d - %d]\r\n"), ioVols[0][4], pCfg310->spi_low_min, pCfg310->spi_low_max );
            //TestResultInfo( szTemp );
            TestResultInfoR( _T("mosi vol = %d, th = [%d - %d]\r\n"), ioVols[0][4], pCfg310->spi_low_min, pCfg310->spi_low_max );
        }
        if( ioVols[1][4] < pCfg310->spi_high_min || ioVols[1][4] > pCfg310->spi_high_max )
        {
            failerCnt++;
            //transformat( szTemp, _T("mosi vol = %d, th = [%d - %d]\r\n"), ioVols[1][4], pCfg310->spi_high_min, pCfg310->spi_high_max );
            //TestResultInfo( szTemp );
            TestResultInfoR( _T("mosi vol = %d, th = [%d - %d]\r\n"), ioVols[1][4], pCfg310->spi_high_min, pCfg310->spi_high_max );
        }

        if( ioVols[0][5] < pCfg310->spi_low_min || ioVols[0][5] > pCfg310->spi_low_max )
        {
            failerCnt++;
            //transformat( szTemp, _T("miso vol = %d, th = [%d - %d]\r\n"), ioVols[0][5], pCfg310->spi_low_min, pCfg310->spi_low_max );
            //TestResultInfo( szTemp );
            TestResultInfoR(  _T("miso vol = %d, th = [%d - %d]\r\n"), ioVols[0][5], pCfg310->spi_low_min, pCfg310->spi_low_max );
        }
        if( ioVols[1][5] < pCfg310->spi_high_min || ioVols[1][5] > pCfg310->spi_high_max )
        {
            failerCnt++;
            //transformat( szTemp, _T("miso vol = %d, th = [%d - %d]\r\n"), ioVols[1][5], pCfg310->spi_high_min, pCfg310->spi_high_max );
            //TestResultInfo( szTemp );
            TestResultInfoR( _T("miso vol = %d, th = [%d - %d]\r\n"), ioVols[1][5], pCfg310->spi_high_min, pCfg310->spi_high_max );
        }

        if( ioVols[0][6] < pCfg310->spi_low_min || ioVols[0][6] > pCfg310->spi_low_max )
        {
            failerCnt++;
            //transformat( szTemp, _T("sclk vol = %d, th = [%d - %d]\r\n"), ioVols[0][6], pCfg310->spi_low_min, pCfg310->spi_low_max );
            //TestResultInfo( szTemp );
            TestResultInfoR( _T("sclk vol = %d, th = [%d - %d]\r\n"), ioVols[0][6], pCfg310->spi_low_min, pCfg310->spi_low_max );
        }
        if( ioVols[1][6] < pCfg310->spi_high_min || ioVols[1][6] > pCfg310->spi_high_max )
        {
            failerCnt++;
            //transformat( szTemp, _T("sclk vol = %d, th = [%d - %d]\r\n"), ioVols[1][6], pCfg310->spi_high_min, pCfg310->spi_high_max );
            //TestResultInfo( szTemp );
            TestResultInfoR(_T("sclk vol = %d, th = [%d - %d]\r\n"), ioVols[1][6], pCfg310->spi_high_min, pCfg310->spi_high_max );
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
#endif
}
unsigned int CTest310::Noise_Test( NativeTestItem& itemQuote )
{
    unsigned int iReCode = ERROR_CODE_COMM_ERROR;
    ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );
	int failerCount = 0;

    const int oneFrameLen = CHUF310_N * 2;
	unsigned int framecount = pCfg310->noise_frame;

	std::vector<std::vector<std::vector<int16_t>>> I_Data(
		framecount,
		std::vector<std::vector<int16_t>>(
			CHUF310_X,
			std::vector<int16_t>(CHUF310_Y)));

	std::vector<std::vector<std::vector<int16_t>>> Q_Data(
		framecount,
		std::vector<std::vector<int16_t>>(
			CHUF310_X,
			std::vector<int16_t>(CHUF310_Y)));

	// 单次读取缓冲区
    std::vector<int16_t> readBuf(oneFrameLen);

    const unsigned int iRawDataLen = oneFrameLen * 2;

    TestResultInfo(_T("\r\n------------------------------Noise Test------------------------------\r\n"));

    if (NULL == SM_ChipBase(m_deviceNo))
        return itemNotify.UpdateItemResult(ITEM_STA_EXCEPTION, GetErrorMessage(iReCode));
    ISMChip310* iChip310 = (ISMChip310*)SM_ChipBase(m_deviceNo);

    iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand(CMD_CTP_RST);
    if (iReCode != ERROR_CODE_OK) return itemNotify.UpdateItemResult(ITEM_STA_EXCEPTION, GetErrorMessage(iReCode));
    SysDelay(50);

    iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand(CMD_SWITCH_IIC);
    if (iReCode != ERROR_CODE_OK) return itemNotify.UpdateItemResult(ITEM_STA_EXCEPTION, GetErrorMessage(iReCode));

    iReCode = iChip310->SwitchMode(MODE_RAWDATA, iRawDataLen);
    if (ERROR_CODE_OK != iReCode) return itemNotify.UpdateItemResult(ITEM_STA_EXCEPTION, GetErrorMessage(iReCode));
    SysDelay(20);

    for (unsigned int frame = 0; frame < framecount; frame++)
    {
        iReCode = iChip310->GetRawData(readBuf.data(), iRawDataLen);
        if (ERROR_CODE_OK != iReCode)
            return itemNotify.UpdateItemResult(ITEM_STA_EXCEPTION, GetErrorMessage(iReCode));

		for (int row = 0; row < CHUF310_X; row++)
		{
			for (int col = 0; col < CHUF310_Y; col++)
			{
				const int pixelIndex =
					row * CHUF310_Y + col;

				I_Data[frame][row][col] =
					readBuf[pixelIndex * 2];

				Q_Data[frame][row][col] =
					readBuf[pixelIndex * 2 + 1];
			}
		}
    }

	// 时间噪声
	std::vector<std::vector<double>> I_TimeNoise(CHUF310_X, std::vector<double>(CHUF310_Y, 0.0));
	std::vector<std::vector<double>> Q_TimeNoise(CHUF310_X, std::vector<double>(CHUF310_Y, 0.0));

	// 空间噪声
	std::vector<double> I_SpatialNoise(framecount, 0.0);
	std::vector<double> Q_SpatialNoise(framecount, 0.0);

	// -----------------------------------------------------------------------------
	// Calculate Time Noise
	// 每个点 across 32 frames 的标准差
	// -----------------------------------------------------------------------------
	for (int row = 0; row < CHUF310_X; row++)
	{
		for (int col = 0; col < CHUF310_Y; col++)
		{
			// -------------------------
			// I Channel
			// -------------------------

			double meanI = 0.0;

			for (unsigned int frame = 0; frame < framecount; frame++)
			{
				meanI +=
					static_cast<double>(
						I_Data[frame][row][col]);
			}

			meanI /= framecount;

			double varianceI = 0.0;

			for (unsigned int frame = 0; frame < framecount; frame++)
			{
				double diff =
					static_cast<double>(
						I_Data[frame][row][col]) - meanI;

				varianceI += diff * diff;
			}

			varianceI /= framecount;

			I_TimeNoise[row][col] =
				std::sqrt(varianceI);

			// -------------------------
			// Q Channel
			// -------------------------

			double meanQ = 0.0;

			for (unsigned int frame = 0; frame < framecount; frame++)
			{
				meanQ +=
					static_cast<double>(
						Q_Data[frame][row][col]);
			}

			meanQ /= framecount;

			double varianceQ = 0.0;

			for (unsigned int frame = 0; frame < framecount; frame++)
			{
				double diff =
					static_cast<double>(
						Q_Data[frame][row][col]) - meanQ;

				varianceQ += diff * diff;
			}

			varianceQ /= framecount;

			Q_TimeNoise[row][col] =
				std::sqrt(varianceQ);
		}
	}

	// -----------------------------------------------------------------------------
	// Calculate Spatial Noise
	// 每帧内部6400个点的标准差
	// -----------------------------------------------------------------------------

	for (unsigned int frame = 0; frame < framecount; frame++)
	{
		// -------------------------
		// I Channel
		// -------------------------

		double meanI = 0.0;

		for (int row = 0; row < CHUF310_X; row++)
		{
			for (int col = 0; col < CHUF310_Y; col++)
			{
				meanI += static_cast<double>(I_Data[frame][row][col]);
			}
		}

		meanI /= static_cast<double>(CHUF310_N);

		double varianceI = 0.0;

		for (int row = 0; row < CHUF310_X; row++)
		{
			for (int col = 0; col < CHUF310_Y; col++)
			{
				double diff = static_cast<double>(I_Data[frame][row][col]) - meanI;

				varianceI += diff * diff;
			}
		}
		varianceI /= static_cast<double>(CHUF310_N);

		I_SpatialNoise[frame] = std::sqrt(varianceI);

		// -------------------------
		// Q Channel
		// -------------------------

		double meanQ = 0.0;

		for (int row = 0; row < CHUF310_X; row++)
		{
			for (int col = 0; col < CHUF310_Y; col++)
			{
				meanQ += static_cast<double>(Q_Data[frame][row][col]);
			}
		}

		meanQ /= static_cast<double>(CHUF310_N);

		double varianceQ = 0.0;

		for (int row = 0; row < CHUF310_X; row++)
		{
			for (int col = 0; col < CHUF310_Y; col++)
			{
				double diff = static_cast<double>(Q_Data[frame][row][col]) - meanQ;

				varianceQ += diff * diff;
			}
		}

		varianceQ /= static_cast<double>(CHUF310_N);

		Q_SpatialNoise[frame] = std::sqrt(varianceQ);
	}

	ColorText textI;
	NodeVal nodeI;

	std::vector<std::vector<double>> I_TimeNoise_Min( CHUF310_X, std::vector<double>(CHUF310_X, 0.0));
	std::vector<std::vector<double>> I_TimeNoise_Max( CHUF310_X, std::vector<double>(CHUF310_X, pCfg310->noise_max_time_A));

	bool bPassI = AnalyzeMatrixResult( I_TimeNoise, I_TimeNoise_Min, I_TimeNoise_Max, textI, nodeI, true);
	TestResultInfo( textI );
    if( !bPassI )
    {
        failerCount++;
        LPCTSTR strHead = _T("\r\n//========= Out of Threshold in ITimeNoiseTest: \r\n");
        PrintNodeValue( m_ColorText, &nodeI, strHead, 2 );
    }

	ColorText textSpatial;
	NodeVal nodeSpatial;
	std::vector<double> I_Spatial_Min( framecount, 0.0);
	std::vector<double> I_Spatial_Max( framecount, pCfg310->noise_max_space_A);

	bool bPassSpatial = AnalyzeArrayResult( I_SpatialNoise, I_Spatial_Min, I_Spatial_Max, textSpatial, nodeSpatial, false);
	TestResultInfo( textSpatial );
    if( !bPassSpatial )
    {
        failerCount++;
        LPCTSTR strHead = _T("\r\n//========= Out of Threshold in ISpatialNoiseTest: \r\n");
        PrintNodeValue( m_ColorText, &nodeSpatial, strHead, 2 );
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

#if 0
    int failerCount = 0;
	short* pReadBufferI = NULL;
	short* pReadBufferQ = NULL;
	short* pReadBuffer = NULL;
    unsigned int iReCode = ERROR_CODE_COMM_ERROR;
    ItemNotifyer itemNotify( m_pNativeIntr, itemQuote );
    signed short baseTempBuffer[CHUF310_N * 2] = {0};
    signed short MaxTempBuffer[CHUF310_N * 2] = {0};
    signed short MinTempBuffer[CHUF310_N * 2] = {0};
    signed short diffTempBuffer[CHUF310_N * 2] = {0};
    /*unsigned*/ short dataMatrix[MAX_MCAP_ROW][MAX_MCAP_COL];
    const unsigned int iRawDataLen = CHUF310_N*4;
    const unsigned int iScapRawDataLen = pCfg310->rowsCnt + pCfg310->colsCnt;
    unsigned short readBuffer[128] = {0};

    TestResultInfo( _T("\r\n------------------------------Noise Test------------------------------\r\n") );

    if( NULL == SM_ChipBase(m_deviceNo) )   return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
    ISMChip310* iChip310 = (ISMChip310*)SM_ChipBase(m_deviceNo);

    iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_CTP_RST );
    if( iReCode != ERROR_CODE_OK ) itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

    SysDelay( 50 );

    iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_SWITCH_IIC );
    if( iReCode != ERROR_CODE_OK ) itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

    //iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_IDENTITY );
    //if( iReCode != ERROR_CODE_OK ) itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );

    iReCode = iChip310->SwitchMode( MODE_RAWDATA, iRawDataLen );
    if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
    SysDelay( 20 );

	pReadBuffer = (short*)malloc( CHUF310_N*4 );
	pReadBufferI = (short*)malloc( CHUF310_N*2*32 );
	pReadBufferQ = (short*)malloc( CHUF310_N*2*32 );

    for( int index = 0; index < 5; index++ )
    {
        iReCode = iChip310->GetRawData( pReadBuffer, iRawDataLen  );
        //if( iReCode == ERROR_CODE_OK ) break;
        if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
    }

    memcpy(MaxTempBuffer,baseTempBuffer,sizeof(baseTempBuffer));
    memcpy(MinTempBuffer,baseTempBuffer,sizeof(baseTempBuffer));

    for(int index = 0; index < pCfg310->noise_frame; index++)
    {
        iReCode = iChip310->GetRawData( baseTempBuffer, iRawDataLen );
        if( ERROR_CODE_OK != iReCode ) return itemNotify.UpdateItemResult( ITEM_STA_EXCEPTION, GetErrorMessage( iReCode ) );
        for(int iCnt = 0; iCnt < (int)iRawDataLen/2;  iCnt++)
        {
            MaxTempBuffer[iCnt] = max(baseTempBuffer[iCnt] , MaxTempBuffer[iCnt]);
            MinTempBuffer[iCnt] = min(baseTempBuffer[iCnt] , MinTempBuffer[iCnt]);
            diffTempBuffer[iCnt] = MaxTempBuffer[iCnt] - MinTempBuffer[iCnt];
        }
    }

    for(int i=0;i<5;i++)
    {
        diffTempBuffer[0] =  max(diffTempBuffer[0] , diffTempBuffer[0 + i*16]);
        diffTempBuffer[1] =  max(diffTempBuffer[1] , diffTempBuffer[1 + i*16]);
        diffTempBuffer[2] =  max(diffTempBuffer[2] , diffTempBuffer[2 + i*16]);
        diffTempBuffer[3] =  max(diffTempBuffer[3] , diffTempBuffer[3 + i*16]);
    }

    int ref_channel_num = min(pCfg310->real_channel_num - pCfg310->va_channel_num, pCfg310->colsCnt);
    AnalyzeInfo info( pCfg310->rowsCnt, pCfg310->colsCnt, ref_channel_num, false );
    ReShappingData</*unsigned*/ short>( dataMatrix, (/*unsigned*/ short*)diffTempBuffer, G_XMLConfig->real_channel_num * 2, pCfg310->rowsCnt, pCfg310->colsCnt );

    short noiseMin[MAX_MCAP_ROW][MAX_MCAP_COL], noiseMax[MAX_MCAP_ROW][MAX_MCAP_COL];
    FillMatrixUseValue( noiseMin, (short)0 );
    FillMatrixUseValue( noiseMax, (short)pCfg310->noise_max_mcap );

    NodeVal nodeOutRange;
    ColorText textTemp( _T("\r\nNoise McapData:\r\n") );
    bool bResult = AnalyzeTestResult( dataMatrix, noiseMin, noiseMax, pCfg310->invalid_node, info, textTemp, nodeOutRange, true );
    TestResultInfo( textTemp );
    if( !bResult )
    {
        failerCount++;
        LPCTSTR strHead = _T("\r\n//========= Out of Threshold in McapNoiseTest: \r\n");
        PrintNodeValue( m_ColorText, &nodeOutRange, strHead );
    }

	failerCount = 0;
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
	if(pReadBuffer )free(pReadBuffer);
	if(pReadBufferI)free(pReadBufferI);
	if(pReadBufferQ)free(pReadBufferQ);

    return itemNotify;
#endif

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


unsigned int CTest310::SetClkInFctMode( unsigned short clkDiv )
{
    return SM_ChipBase(m_deviceNo)->SetClkInFctMode(clkDiv, pCfg310->filter_off);
}
unsigned int CTest310::WorkForGraphMode( bool bEnterGraphing /*= false*/ )
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

void CTest310::PrepareSimulate( SimulateData& sm )
{
    unsigned char cmdID = sm.itemID & 0xff;
    unsigned char dataIndex = (sm.itemID >> 8) & 0xff;
    unsigned char sumCnt = 1;
    int iDesIndex = 0;

    //scap data
    if( sm.itemID == ((0xfa << 16) + 0x28) )
    {
        iDesIndex += pCfg310->rowsCnt * pCfg310->colsCnt;
        for( int iCol = 0; iCol <  pCfg310->colsCnt; iCol++ )
            sm.itemArray[iDesIndex++] = sm.itemData[0][iCol] * sumCnt;
        for( int iCol = 0; iCol < pCfg310->rowsCnt; iCol++ )
            sm.itemArray[iDesIndex++] = sm.itemData[1][iCol] * sumCnt;
    }
    else
    {
        for( int iRow = 0; iRow < sm.rows; iRow++ )
        {
            for( int iCol = 0; iCol < sm.cols; iCol++ )
            {
                if( iDesIndex >= sizeof(sm.itemArray)/sizeof(short) ) break;

                //int icPosition = pCfg310->sensor_2_ic_map[index];
                sm.itemArray[iDesIndex++] = sm.itemData[iRow][iCol] * sumCnt;
            }
        }
    }
}


unsigned int CTest310::AverageData(short* buff, int len)
{
    int sum =0;
    short* data = (short*)buff;

    for (int i = 0; i< len; i++)
    {
        sum = sum + data[i];
    }

    return sum/len;
}


