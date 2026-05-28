#include "Config.h"
#include "../TestSrc/ToolKit.h"
#include "checksum.h"

CConfig::CConfig( unsigned short type )
	:I2cAddr(0x5c)
	,IcType(type)
	,szWorkStation(NULL)
	,szProjectName(NULL)
	,szCfgBinPath(NULL)
	,szBootBinPath(NULL)
	,costom_snFilter(NULL)
	,int_selected(0)
	,reset_selected(0)
	,Full_Screen(0)
	,boot_selected(0)
	,config_selected(0)
	,button_selected(0)
	,LINEARITY_TEST(0)
	,EXP_LINEARITY_TEST(0)
	,FREEPAINT_TEST(0)
	,filter_off(0)
	,bVerticalTriangle(1)
	,mtk_version(0x50924)
	,sync_length(122)
	,mtk_auto_update(0)
	,mtk_app_size(0)
	,protocalType(PROTOCAL_IIC)
	,Speed(5)
	,vddVotage(0x6E)
	,agent(0x01)
	,ioVddVotage(0x47)
	,vihVotage(0x2e)
	,FreePaint_LimiteTime(100)
	,heatbeatVotage(0x00)
	,ftp_type(0)
	,link_type(0)
	,Set_Key_Num(0)
{

}
CConfig::~CConfig()
{

}
BOOL CConfig::CheckCfgBinFile( unsigned char* pCfg, unsigned int byteSize )
{
	if( !pCfg ) return FALSE;
	if( byteSize > MAX_CFG_BIN_SIZE )  return FALSE;
	if( byteSize < 64 )  return FALSE;
	if( byteSize & 1 )   return FALSE;

	unsigned short check = 0;
	//check = caculate_check_sum_u16((unsigned short*)pCfg,byteSize);

	unsigned short *ps = (unsigned short*)pCfg;
	byteSize = byteSize >> 1;
	check = *ps++;
	for( int index = 1; index < (int)byteSize; index++ )
	{
		check += *ps++; 
	}
	if(check)
	{
		return FALSE;
	}
	return TRUE;
}
void CConfig::BootSvnTextToBootSvn( const char* str_boot_svn, unsigned int& boot_svn )
{
	boot_svn = 0;
	if( NULL == str_boot_svn )    return;
	int k = 0, i = 0;
	
	if(0 == (('0'>=str_boot_svn[0]) && ('9'<=str_boot_svn[0]))){
		k = str_boot_svn[0]<<24;
		i = sscanf_s(&str_boot_svn[1], "%d", &boot_svn);
	}else{
		k = 0;
		i = sscanf_s(str_boot_svn, "%d", &boot_svn);
	}
	if(0 == i){
		boot_svn = 0;
	}else{
		if(0 == (boot_svn & 0xFF000000)){
			boot_svn |= k;
		}
	}
}
LPCTSTR CConfig::GetMtkAppBinPath()
{
#ifdef _MSC_VER
	static TCHAR szMtkBin[MAX_PATH] = {0};
	::GetModuleFileName( GetModuleHandle( _T("SEMITest.dll") ), szMtkBin, MAX_PATH );
	*(_tcsrchr( szMtkBin, _T('\\') ) + 1) = 0;

	WIN32_FIND_DATA fd;
	HANDLE fFind = ::FindFirstFile((tstring(szMtkBin) + _T("\\mtk\\Stm32_MtkAppV*.bin")).c_str(), &fd);
	if( INVALID_HANDLE_VALUE == fFind ) return NULL;
	FindClose(fFind);

	copytextappend(szMtkBin, _T("mtk\\"));
	copytextappend( szMtkBin, fd.cFileName );

	return szMtkBin;
#else
	return NULL;
#endif
}
BOOL CConfig::Parse( const tinyxml2::XMLDocument& xmlDoc )
{
	const XMLElement* pRoot = xmlDoc.RootElement();
	if( !pRoot )            return FALSE;
	const XMLElement* pElementCommon = (const XMLElement*)pRoot->FirstChildElement("common");
	if( !pElementCommon )   return FALSE;
	const XMLElement* pElementFirmware = (const XMLElement*)pRoot->FirstChildElement("firmware");
    if( pElementFirmware )
	{
		boot_check_sum = (unsigned int)pElementFirmware->Int64Attribute("boot_crc");
		config_check_sum = (unsigned int)pElementFirmware->Int64Attribute("config_crc");

		boot_loader_check_sum = (unsigned int)pElementFirmware->Int64Attribute("boot_loader_crc");
		
		//boot_len = (unsigned short)pElementFirmware->Int64Attribute("boot_len");
		//config_len = (unsigned short)pElementFirmware->Int64Attribute("config_len");
		const char* str_boot_svn = pElementFirmware->Attribute("boot_svn");
		BootSvnTextToBootSvn( str_boot_svn, boot_svn );
		w_clk = (unsigned short)pElementFirmware->Int64Attribute("w_clk", 0x2601);
		filter_off = (unsigned char)pElementFirmware->Int64Attribute("filter_off", 0);
		rowsCnt = (unsigned char)pElementFirmware->Int64Attribute("rows", 0);
		colsCnt = (unsigned char)pElementFirmware->Int64Attribute("cols", 0);
	}

	protocalType = (unsigned char)pElementCommon->Int64Attribute( "protocal", 0 );
	if(PROTOCAL_SPI == protocalType)
		Speed = (unsigned short)pElementCommon->Int64Attribute( "spi_speed", 3 << 3 );	
	else
		Speed = (unsigned short)pElementCommon->Int64Attribute( "i2c_speed", 5 );

	vddVotage = (unsigned char)pElementCommon->Int64Attribute( "vdd_votage", 0x6E );
	ioVddVotage = (unsigned char)pElementCommon->Int64Attribute( "iovdd_votage", 0x47 );

	agent = (unsigned char)pElementCommon->Int64Attribute( "agent", 0x01 );
    VIH = pElementCommon->FloatAttribute( "vih_votage", 1.3f );
	//vihVotage = (unsigned char)ceil(38.7455f * VIH + -0.85997f);
	vihVotage = static_cast<unsigned short>(VIH*1000);
	//I2cSpeed = (unsigned short)pElementCommon->Int64Attribute("i2c_speed", 5);

	//IcType;
	I2cAddr = (unsigned char)pElementCommon->Int64Attribute( "i2c_addr", 0x00 );
	szWorkStation = pElementCommon->Attribute("work_station");
	szProjectName = pElementCommon->Attribute("project_name");
	szCfgBinPath  = pElementCommon->Attribute("configure_bin");
	szBootBinPath = pElementCommon->Attribute("boot_bin");

	const XMLElement* pWorkStation = xmlDoc.RootElement()->FirstChildElement(szWorkStation);
	if( pWorkStation )
	{
		//misc
		const XMLElement* pMiscConfig = pWorkStation->FirstChildElement("misc");
		if(pMiscConfig)
		{
			test_mode = (unsigned short)pMiscConfig->Int64Attribute("test_mode", 1);
			way_to_start = (unsigned char)pMiscConfig->Int64Attribute( "way_to_start", 2 );
			sn_length = (unsigned char)pMiscConfig->Int64Attribute( "sn_length", 10 );
			need_click_start = (unsigned char)pMiscConfig->Int64Attribute( "need_click_start", 0 );

			need_remove_ic = (unsigned char)pMiscConfig->Int64Attribute( "need_remove_ic", 0 );

			selected_format = (unsigned char)pMiscConfig->Int64Attribute( "selected_format" );
			szUserRecord = (const char*)pMiscConfig->Attribute("user_record");
			heatbeatVotage = (unsigned char)pMiscConfig->Int64Attribute("heatbeat_voltage", 0x00);
			szLogPath = (const char*)pMiscConfig->Attribute("log_path");
			hold_up = (unsigned short)pMiscConfig->Int64Attribute("hold_up", 10);
			costom_snFilter    = (const char*)pMiscConfig->Attribute("snFilter");
		}

		//online
		const XMLElement* pOnlineConfig = pWorkStation->FirstChildElement("online");
		if(pOnlineConfig)
		{
			link_type = (unsigned short)pOnlineConfig->Int64Attribute("link_type", 0);
			server_port_num = (unsigned short)pOnlineConfig->Int64Attribute("port_num", 0);
			server_ip_addr = (const char*)pOnlineConfig->Attribute("ip_addr");
			source_port_num = (unsigned short)pOnlineConfig->Int64Attribute("port_source", 0);
		}

		//custom
		const XMLElement* pCustomConfig = pWorkStation->FirstChildElement("custom");
		if(pCustomConfig)
		{
			custom_line_id = (const char*)pCustomConfig->Attribute("line_id");
			custom_account = (const char*)pCustomConfig->Attribute("account");
			custom_password = (const char*)pCustomConfig->Attribute("password");
		}

		//customv2
		const XMLElement* pCustomv2Config = pWorkStation->FirstChildElement("customv2");
		if(pCustomv2Config)
		{
			customv2_device_id = (const char*)pCustomv2Config->Attribute("device_id");
			customv2_process_name = (const char*)pCustomv2Config->Attribute("process_name");
		}

		const XMLElement* pCustomOfilmConfig = pWorkStation->FirstChildElement("custom_ofilm");
		if(pCustomOfilmConfig)
		{
			costom_ofilm_userId      = (const char*)pCustomOfilmConfig->Attribute("userId");
			costom_ofilm_fixtureId   = (const char*)pCustomOfilmConfig->Attribute("fixtureId");
			costom_ofilm_eqpId       = (const char*)pCustomOfilmConfig->Attribute("eqpId");
			costom_ofilm_mesUrl      = (const char*)pCustomOfilmConfig->Attribute("mesUrl");
			costom_ofilm_stepId      = (const char*)pCustomOfilmConfig->Attribute("stepId");
			costom_ofilm_testStepId  = (const char*)pCustomOfilmConfig->Attribute("testStepId");
			costom_ofilm_macAddress  = (const char*)pCustomOfilmConfig->Attribute("macAddress");
		}

		const XMLElement* pCustomPbhConfig = pWorkStation->FirstChildElement("custom_pbh");
		if(pCustomPbhConfig)
		{
			costom_pbh_mesUrl        = (const char*)pCustomPbhConfig->Attribute("mesUrl");
			costom_pbh_fixtureId	 = (const char*)pCustomPbhConfig->Attribute("fixtureId");
			costom_pbh_testStepId	 = (const char*)pCustomPbhConfig->Attribute("testStepId");
			costom_pbh_stationId	 = (const char*)pCustomPbhConfig->Attribute("station");
			costom_pbh_userId		 = (const char*)pCustomPbhConfig->Attribute("userId");
			costom_pbh_passWord	     = (const char*)pCustomPbhConfig->Attribute("passWord");
		}						

		//ftp
		const XMLElement* pFtpConfig = pWorkStation->FirstChildElement("uploader");
		if(pFtpConfig)
		{
			ftp_type = (unsigned short)pFtpConfig->Int64Attribute("ftp_type", 0);
			ftp_port = (unsigned short)pFtpConfig->Int64Attribute("port_num", 21);
			ftp_ip_addr = (const char*)pFtpConfig->Attribute("ip_addr");
			ftp_account = (const char*)pFtpConfig->Attribute("account");
			ftp_password = (const char*)pFtpConfig->Attribute("password");
			ftp_relative_path = (const char*)pFtpConfig->Attribute("relative_path");
		}
		const XMLElement* pCustomChuangWeiConfig = pWorkStation->FirstChildElement("custom_chuangwei");
		if(pCustomChuangWeiConfig)
		{
			//costom_ChuangWei
			costom_ChuangWei_mesUrl       = (const char*)pCustomChuangWeiConfig->Attribute("mesUrl");
			costom_ChuangWei_usercode     = (const char*)pCustomChuangWeiConfig->Attribute("userId");
			costom_ChuangWei_processcode  = (const char*)pCustomChuangWeiConfig->Attribute("processcode");
			costom_ChuangWei_linecode     = (const char*)pCustomChuangWeiConfig->Attribute("line_id");
			costom_ChuangWei_message      = (const char*)pCustomChuangWeiConfig->Attribute("message");

			costom_ChuangWei_orderno      = (const char*)pCustomChuangWeiConfig->Attribute("orderno");
			costom_ChuangWei_simulationUp = ((unsigned char)pCustomChuangWeiConfig->Int64Attribute("simulationUp", 0) >=1 ) ? "1":"0";
			costom_ChuangWei_macAddress   = (const char*)pCustomChuangWeiConfig->Attribute("macAddress"); 
		}

        //costom_Hes
        const XMLElement* pCustomHesConfig = pWorkStation->FirstChildElement("custom_hes");
        if(pCustomHesConfig)
        {
            costom_Hes_mesUrl       = (const char*)pCustomHesConfig->Attribute("mesUrl");
            costom_Hes_machine_no     = (const char*)pCustomHesConfig->Attribute("machine_no");
            costom_Hes_lot_no  = (const char*)pCustomHesConfig->Attribute("lot_no");
            costom_Hes_subop_no     = (const char*)pCustomHesConfig->Attribute("subop_no");
            costom_Hes_person      = (const char*)pCustomHesConfig->Attribute("person");
        }

        //costom_Ls
        const XMLElement* pCustomLsConfig = pWorkStation->FirstChildElement("custom_ls");
        if(pCustomLsConfig)
        {
            costom_Ls_mesUrl       = (const char*)pCustomLsConfig->Attribute("mesUrl");
            costom_Ls_resource_no     = (const char*)pCustomLsConfig->Attribute("resource_no");
            costom_Ls_special_code  = (const char*)pCustomLsConfig->Attribute("special_code");
            costom_Ls_operator     = (const char*)pCustomLsConfig->Attribute("operator");
            costom_Ls_device_num      = (const char*)pCustomLsConfig->Attribute("device_num");
            costom_Ls_displaytest = (unsigned char)pCustomLsConfig->Int64Attribute("display_test");
        }

		const XMLElement* pIntConfig = pWorkStation->FirstChildElement("int_test");
		if( pIntConfig )
		{
			int_selected = (unsigned char)pIntConfig->Int64Attribute("selected");
		}
		const XMLElement* pResetConfig = pWorkStation->FirstChildElement("reset_test");
		if( pResetConfig )
		{
			reset_selected = (unsigned char)pResetConfig->Int64Attribute("selected");
		}
		const XMLElement* pButtonConfig = pWorkStation->FirstChildElement("button_test");
		if( pButtonConfig )
		{
			button_selected = (unsigned char)pButtonConfig->Int64Attribute("selected");
			//Set_Key_Num = (unsigned char)pButtonConfig->Int64Attribute("key_num");
			LimitTime_Key = (unsigned int)pButtonConfig->Int64Attribute("limited_time");
			Max_NG_Num = (unsigned int)pButtonConfig->Int64Attribute("max_ng");
			key_thr = (unsigned char)pButtonConfig->Int64Attribute("key_thr");
		}
		const XMLElement* pFreePaintConfig = pWorkStation->FirstChildElement("freepaint_test");
		if( pFreePaintConfig )
		{
			FREEPAINT_TEST = (unsigned char)pFreePaintConfig->Int64Attribute("selected");
			isOnce = (unsigned char)pFreePaintConfig->Int64Attribute("once");
			FreePaint_LimiteTime = (unsigned int)pFreePaintConfig->Int64Attribute("limited_time");

			is_xy_reverse = (unsigned char)pFreePaintConfig->Int64Attribute("xy_reverse",0);
			is_x_reverse = (unsigned char)pFreePaintConfig->Int64Attribute("x_reverse",0);
			is_y_reverse = (unsigned char)pFreePaintConfig->Int64Attribute("y_reverse",0);
		}
		const XMLElement* pCfgLinearly = pWorkStation->FirstChildElement("linearly_test");
		if( pCfgLinearly )
		{
			LINEARITY_TEST = (unsigned char)pCfgLinearly->Int64Attribute("selected");
			iLinerityMaxNG = (unsigned int)pCfgLinearly->Int64Attribute("max_ng");
			iLinearityLimitTime = (unsigned int)pCfgLinearly->Int64Attribute("limited_time");
			LinearityWhenCritical = (unsigned char)pCfgLinearly->Int64Attribute("critical_triger");
			Distance_Linearity = (unsigned int)pCfgLinearly->Int64Attribute("distance");
			Edge_Linearity = (unsigned int)pCfgLinearly->Int64Attribute("edge");
			Length_Linearity = (unsigned int)pCfgLinearly->Int64Attribute("lenth");
			Position_Linearity = (unsigned int)pCfgLinearly->Int64Attribute("postion");
			Upper_Limit_H1 = (unsigned int)pCfgLinearly->Int64Attribute("upper_limite_h1");
			Lower_Limit_H1 = (unsigned int)pCfgLinearly->Int64Attribute("lower_limite_h1");
			Upper_Limit_H2 = (unsigned int)pCfgLinearly->Int64Attribute("upper_limite_h2");
			Lower_Limit_H2 = (unsigned int)pCfgLinearly->Int64Attribute("lower_limite_h2");
			Upper_Limit_H3 = (unsigned int)pCfgLinearly->Int64Attribute("upper_limite_h3");
			Lower_Limit_H3 = (unsigned int)pCfgLinearly->Int64Attribute("lower_limite_h3");
			Upper_Limit_H4 = (unsigned int)pCfgLinearly->Int64Attribute("upper_limite_h4");
			Lower_Limit_H4 = (unsigned int)pCfgLinearly->Int64Attribute("lower_limite_h4");
			Upper_Limit_H5 = (unsigned int)pCfgLinearly->Int64Attribute("upper_limite_h5");
			Lower_Limit_H5 = (unsigned int)pCfgLinearly->Int64Attribute("lower_limite_h5");
			Upper_Limit_H6 = (unsigned int)pCfgLinearly->Int64Attribute("upper_limite_h6");
			Lower_Limit_H6 = (unsigned int)pCfgLinearly->Int64Attribute("lower_limite_h6");

			Upper_Limit_V1 = (unsigned int)pCfgLinearly->Int64Attribute("upper_limite_v1");
			Lower_Limit_V1 = (unsigned int)pCfgLinearly->Int64Attribute("lower_limite_v1");
			Upper_Limit_V2 = (unsigned int)pCfgLinearly->Int64Attribute("upper_limite_v2");
			Lower_Limit_V2 = (unsigned int)pCfgLinearly->Int64Attribute("lower_limite_v2");
			Upper_Limit_V3 = (unsigned int)pCfgLinearly->Int64Attribute("upper_limite_v3");
			Lower_Limit_V3 = (unsigned int)pCfgLinearly->Int64Attribute("lower_limite_v3");
			Upper_Limit_V4 = (unsigned int)pCfgLinearly->Int64Attribute("upper_limite_v4");
			Lower_Limit_V4 = (unsigned int)pCfgLinearly->Int64Attribute("lower_limite_v4");
			Upper_Limit_V5 = (unsigned int)pCfgLinearly->Int64Attribute("upper_limite_v5");
			Lower_Limit_V5 = (unsigned int)pCfgLinearly->Int64Attribute("lower_limite_v5");
			Upper_Limit_V6 = (unsigned int)pCfgLinearly->Int64Attribute("upper_limite_v6");
			Lower_Limit_V6 = (unsigned int)pCfgLinearly->Int64Attribute("lower_limite_v6");
		}

        const XMLElement* pCfgExpLinearly = pWorkStation->FirstChildElement("exp_linearly_test");
        if( pCfgExpLinearly )
        {
            EXP_LINEARITY_TEST = (unsigned char)pCfgExpLinearly->Int64Attribute("selected");
            Exp_iLinerityMaxNG = (unsigned int)pCfgExpLinearly->Int64Attribute("max_ng");
            Exp_iLinearityLimitTime = (unsigned int)pCfgExpLinearly->Int64Attribute("limited_time");
            Exp_Distance_Linearity = (unsigned int)pCfgExpLinearly->Int64Attribute("distance");
            Exp_Edge_Linearity = (unsigned int)pCfgExpLinearly->Int64Attribute("edge");
            Exp_Length_Linearity = (unsigned int)pCfgExpLinearly->Int64Attribute("lenth");
            Exp_Position_Linearity = (unsigned int)pCfgExpLinearly->Int64Attribute("postion");
            Exp_Upper_Limit_H1 = (unsigned int)pCfgExpLinearly->Int64Attribute("upper_limite_h1");
            Exp_Lower_Limit_H1 = (unsigned int)pCfgExpLinearly->Int64Attribute("lower_limite_h1");
            Exp_Upper_Limit_H2 = (unsigned int)pCfgExpLinearly->Int64Attribute("upper_limite_h2");
            Exp_Lower_Limit_H2 = (unsigned int)pCfgExpLinearly->Int64Attribute("lower_limite_h2");
            Exp_Upper_Limit_H3 = (unsigned int)pCfgExpLinearly->Int64Attribute("upper_limite_h3");
            Exp_Lower_Limit_H3 = (unsigned int)pCfgExpLinearly->Int64Attribute("lower_limite_h3");
            Exp_Upper_Limit_H4 = (unsigned int)pCfgExpLinearly->Int64Attribute("upper_limite_h4");
            Exp_Lower_Limit_H4 = (unsigned int)pCfgExpLinearly->Int64Attribute("lower_limite_h4");
            Exp_Upper_Limit_H5 = (unsigned int)pCfgExpLinearly->Int64Attribute("upper_limite_h5");
            Exp_Lower_Limit_H5 = (unsigned int)pCfgExpLinearly->Int64Attribute("lower_limite_h5");

            Exp_Upper_Limit_V1 = (unsigned int)pCfgExpLinearly->Int64Attribute("upper_limite_v1");
            Exp_Lower_Limit_V1 = (unsigned int)pCfgExpLinearly->Int64Attribute("lower_limite_v1");
            Exp_Upper_Limit_V2 = (unsigned int)pCfgExpLinearly->Int64Attribute("upper_limite_v2");
            Exp_Lower_Limit_V2 = (unsigned int)pCfgExpLinearly->Int64Attribute("lower_limite_v2");
            Exp_Upper_Limit_V3 = (unsigned int)pCfgExpLinearly->Int64Attribute("upper_limite_v3");
            Exp_Lower_Limit_V3 = (unsigned int)pCfgExpLinearly->Int64Attribute("lower_limite_v3");
            Exp_Upper_Limit_V4 = (unsigned int)pCfgExpLinearly->Int64Attribute("upper_limite_v4");
            Exp_Lower_Limit_V4 = (unsigned int)pCfgExpLinearly->Int64Attribute("lower_limite_v4");
            Exp_Upper_Limit_V5 = (unsigned int)pCfgExpLinearly->Int64Attribute("upper_limite_v5");
            Exp_Lower_Limit_V5 = (unsigned int)pCfgExpLinearly->Int64Attribute("lower_limite_v5");

            Exp_DiagLength_Linearity = (unsigned int)pCfgExpLinearly->Int64Attribute("diagnol_length");
            Exp_DiagWidth_Linearity = (unsigned int)pCfgExpLinearly->Int64Attribute("diagnol_width");
        }

		const XMLElement* pBootConfig = pWorkStation->FirstChildElement("boot_test");
		if( pBootConfig )
		{
			boot_selected = (unsigned char)pBootConfig->Int64Attribute("selected");
			boot_only_check = (unsigned char)pBootConfig->Int64Attribute("only_check", 0);
		}
		const XMLElement* pCfgConfig = pWorkStation->FirstChildElement("config_test");
		if( pCfgConfig )
		{
			config_selected = (unsigned char)pCfgConfig->Int64Attribute("selected");
			config_only_check = (unsigned char)pCfgConfig->Int64Attribute("only_check", 0);
		}

		const XMLElement* pMtkVersionConfig = pWorkStation->FirstChildElement("mtkversion_test");
		if( pMtkVersionConfig )
		{
			mtk_selected = (unsigned char)pMtkVersionConfig->Int64Attribute("selected");
			mtk_version = (unsigned int)pMtkVersionConfig->Int64Attribute("mtk_version");
			sync_length = (unsigned int)pMtkVersionConfig->Int64Attribute("sync_length", 122);
			sync_type = (unsigned char)pMtkVersionConfig->Int64Attribute("sync_type", 0);
			mtk_auto_update = (unsigned char)pMtkVersionConfig->Int64Attribute("auto_update");
			try
			{
				FILE* file = NULL;
				LPCTSTR szMtkBin = GetMtkAppBinPath();
				if(szMtkBin != NULL)
				{
					fopen_s( &file, szMtkBin, "rb" );
					if(NULL != file)
					{
						fseek( file, 0, SEEK_END );
						mtk_app_size = ftell( file );
						fseek( file, 0, SEEK_SET );
						fread_s(mtk_app_bin, MAX_MTK_APP_SIZE, 1, mtk_app_size, file);
						fclose( file );
					}
				}
			}
			catch (...)
			{
			}
		}
	}

	return SubParseFromConfig();
}
BOOL CConfig::SubParseFromConfig()
{
	return FALSE;
}