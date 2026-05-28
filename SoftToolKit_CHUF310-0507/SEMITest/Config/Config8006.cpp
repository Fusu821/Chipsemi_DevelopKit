#include "framework.h"
#include "Config8006.h"
#include "checksum.h"
#include "../TestSrc/ToolKit.h"
REGIST_RUNTIME_CLASS_USHORT(CONFIG_TYPE, (CONFIG_TYPE)SEMI_IC_CHGA8006, CConfig8006)

CConfig8006::CConfig8006( unsigned short type )
:CConfig(type)
{

	current_selected = 0;
	short_selected = 0;
	frt_selected = 0;
	iovol_selected = 0;
	cvdiff_selected_y = 0;
	cvdiff_selected_x = 0;
	osctrim_selected = 0;
	base_selected = 0;
	noise_selected = 0;
	sdrc_selected =0;
	scap_rawdata_selected = 0;
	stc_selected = 0;
	mcap_rawdata_selected = 0;



	va_channel_num = 0;
	harf_va_channel_num = 0;
	//key_num = 0;
	//all_channel_num =0;
	cfgBinSize = 0;
	bootBinSize = 0;
	cfgTestBinSize = 0;
	rowsCnt = 0;
	colsCnt = 0;
	memset( ic_2_sensor_map, 0, sizeof(ic_2_sensor_map) );
	memset( sensor_2_ic_map, 0, sizeof(sensor_2_ic_map) );
	memset( cfgBinBuffer, 0, sizeof(cfgBinBuffer) );
	memset( bootBinBuffer, 0, sizeof( bootBinBuffer ) );

	memset(invalid_node, 1, sizeof(invalid_node));
}
CConfig8006::~CConfig8006()
{

}
BOOL CConfig8006::Parse( const tinyxml2::XMLDocument& xmlDoc )
{
	BOOL bRet = CConfig::Parse( xmlDoc );
	const XMLElement* pWorkStation = xmlDoc.RootElement()->FirstChildElement(szWorkStation);
	if( !pWorkStation )   return ERROR_CODE_INVALID_FILE;
	if( bRet )
	{
		const XMLElement* pInvalidConfig = pWorkStation->FirstChildElement("invalidnode");
		if( pInvalidConfig )
		{
			ParseDetailData( pInvalidConfig, "invalid", invalid_node, rowsCnt, colsCnt, 1 );
		}
		const XMLElement* pCurrentConfig = pWorkStation->FirstChildElement("current_test");
		if( pCurrentConfig )
		{
			current_selected = (unsigned char)pCurrentConfig->Int64Attribute("selected");
			//current_action = (unsigned short)pCurrentConfig->Int64Attribute("action");
			deep_current_min = 0;//(short)pCurrentConfig->Int64Attribute("deep_current_min");
			deep_current_max = 0;//(short)pCurrentConfig->Int64Attribute("deep_current_max");
			sleep_current_min = (short)pCurrentConfig->Int64Attribute("sleep_current_min");
			sleep_current_max = (short)pCurrentConfig->Int64Attribute("sleep_current_max");
			active_current_min = (short)pCurrentConfig->Int64Attribute("active_current_min");
			active_current_max = (short)pCurrentConfig->Int64Attribute("active_current_max");

			vbus_deep_current_min   = 0;//(short)pCurrentConfig->Int64Attribute("vbus_deep_current_min");
			vbus_deep_current_max   = 0;//(short)pCurrentConfig->Int64Attribute("vbus_deep_current_max");
			vbus_sleep_current_min  = 0;//(short)pCurrentConfig->Int64Attribute("vbus_sleep_current_min");
			vbus_sleep_current_max  = 0;//(short)pCurrentConfig->Int64Attribute("vbus_sleep_current_max");
			vbus_active_current_min = 0;//(short)pCurrentConfig->Int64Attribute("vbus_active_current_min");
			vbus_active_current_max = 0;//(short)pCurrentConfig->Int64Attribute("vbus_active_current_max");

		}
		const XMLElement* pOSCTrimConfig = pWorkStation->FirstChildElement("osctrim_test");
		if( pOSCTrimConfig )
		{
			osctrim_selected = (unsigned char)pOSCTrimConfig->Int64Attribute("selected");
			tick_32k_standard = (unsigned int)pOSCTrimConfig->Int64Attribute("tick_32k_standard");
			trim_32k_min = (unsigned char)pOSCTrimConfig->Int64Attribute("trim_32k_min");
			trim_32k_max = (unsigned char)pOSCTrimConfig->Int64Attribute("trim_32k_max");

			tick_64m_standard = (unsigned int)pOSCTrimConfig->Int64Attribute("tick_64m_standard");
			trim_64m_min = (unsigned short)pOSCTrimConfig->Int64Attribute("trim_64m_min");
			trim_64m_max = (unsigned short)pOSCTrimConfig->Int64Attribute("trim_64m_max");

		}
		//const XMLElement* pBaseConfig = pWorkStation->FirstChildElement("base_test");
		//if( pBaseConfig )
		//{
		//	base_selected = (unsigned char)pBaseConfig->Int64Attribute("selected");
		//	signed short min = (signed short)pBaseConfig->Int64Attribute("base_min");
		//	signed short max = (signed short)pBaseConfig->Int64Attribute("base_max");
		//	ParseDetailData( pBaseConfig, "base_min", base_min, rowsCnt, colsCnt, min );
		//	ParseDetailData( pBaseConfig, "base_max", base_max, rowsCnt, colsCnt, max );
		//}
		const XMLElement* pShortConfig = pWorkStation->FirstChildElement("short_test");
		if( pShortConfig )
		{
			short_selected = (unsigned char)pShortConfig->Int64Attribute("selected");
			short_tx_max = (unsigned short)pShortConfig->Int64Attribute("short_tx_max");
			short_rx_max = (unsigned short)pShortConfig->Int64Attribute("short_rx_max");
		}

		const XMLElement* pFrtConfig = pWorkStation->FirstChildElement("frt_test");
		if( pFrtConfig )
		{
			frt_selected = (unsigned char)pFrtConfig->Int64Attribute("selected");
		}

		const XMLElement* pIoVolConfig = pWorkStation->FirstChildElement("iovol_test");
		if( pIoVolConfig )
		{
			iovol_selected = (unsigned char)pIoVolConfig->Int64Attribute("selected");
			int_low_min = (unsigned int)pIoVolConfig->Int64Attribute("int_low_min", 0);
			int_low_max = (unsigned int)pIoVolConfig->Int64Attribute("int_low_max", 300);
			int_high_min = (unsigned int)pIoVolConfig->Int64Attribute("int_high_min", 1700);
			int_high_max = (unsigned int)pIoVolConfig->Int64Attribute("int_high_max", 1900);
			iic_low_min = (unsigned int)pIoVolConfig->Int64Attribute("iic_low_min", 300);
			iic_low_max = (unsigned int)pIoVolConfig->Int64Attribute("iic_low_max", 300);
			iic_high_min = (unsigned int)pIoVolConfig->Int64Attribute("iic_high_min", 1700);
			iic_high_max = (unsigned int)pIoVolConfig->Int64Attribute("iic_high_max", 1900);
			spi_low_min = (unsigned int)pIoVolConfig->Int64Attribute("spi_low_min", 0);
			spi_low_max = (unsigned int)pIoVolConfig->Int64Attribute("spi_low_max", 300);
			spi_high_min = (unsigned int)pIoVolConfig->Int64Attribute("spi_high_min", 1700);
			spi_high_max = (unsigned int)pIoVolConfig->Int64Attribute("spi_high_max", 1900);
		}

		//const XMLElement* pScapRawDataConfig = pWorkStation->FirstChildElement("scap_rawdata_test");
		//if( pScapRawDataConfig )
		//{
		//	scap_rawdata_selected = (unsigned char)pScapRawDataConfig->Int64Attribute("selected");
		//	unsigned short defmin = (unsigned short)pScapRawDataConfig->Int64Attribute("scap_rawdata_min");
		//	unsigned short defmax = (unsigned short)pScapRawDataConfig->Int64Attribute("scap_rawdata_max");
		//	ParseDetailData( pScapRawDataConfig, "scap_rawdata_min", scap_rawdata_min, rowsCnt, max(rowsCnt, colsCnt), defmin );
		//	ParseDetailData( pScapRawDataConfig, "scap_rawdata_max", scap_rawdata_max, rowsCnt, max(rowsCnt, colsCnt), defmax );
		//}

		//const XMLElement* pStcConfig = pWorkStation->FirstChildElement("stc_test");
		//if( pStcConfig )
		//{
		//	stc_selected = (unsigned char)pStcConfig->Int64Attribute("selected");
		//	stc_clk_div = (unsigned short)pStcConfig->Int64Attribute("clk_div", 20);
		//	stc_min = (signed short)pStcConfig->Int64Attribute("stc_min");
		//	stc_max = (signed short)pStcConfig->Int64Attribute("stc_max");
		//	unsigned short uniformity_h = (unsigned short)pStcConfig->Int64Attribute("uniformity_hor_max");
		//	unsigned short uniformity_v = (unsigned short)pStcConfig->Int64Attribute("uniformity_ver_max");
		//	//ParseDetailData( pStcConfig, "stc_min", stc_min, rowsCnt, colsCnt, min );
		//	//ParseDetailData( pStcConfig, "stc_max", stc_max, rowsCnt, colsCnt, max );
		//	ParseDetailData( pStcConfig, "uniformity_hor_max", stc_uniformity_h, rowsCnt, colsCnt, uniformity_h );
		//	ParseDetailData( pStcConfig, "uniformity_ver_max", stc_uniformity_v, rowsCnt, colsCnt, uniformity_v );
		//	ParseDetailData( pStcConfig, "stc_mean", stc_mean, rowsCnt, colsCnt, 0 );
		//	ParseDetailData( pStcConfig, "stc_mse", stc_mse, rowsCnt, colsCnt, 10 );
		//}

		const XMLElement* pMCapRawDataConfig = pWorkStation->FirstChildElement("mcap_rawdata_test");
		if( pMCapRawDataConfig )
		{
			mcap_rawdata_selected = (unsigned char)pMCapRawDataConfig->Int64Attribute("selected");
			mcap_clk_div = (unsigned short)pMCapRawDataConfig->Int64Attribute("clk_div", 12);
			check_uniformity_hor = (unsigned char)pMCapRawDataConfig->Int64Attribute("check_uniformity_hor", 0);
			check_uniformity_ver = (unsigned char)pMCapRawDataConfig->Int64Attribute("check_uniformity_ver", 0);
			unsigned short min = (unsigned short)pMCapRawDataConfig->Int64Attribute("mcap_rawdata_min");
			unsigned short max = (unsigned short)pMCapRawDataConfig->Int64Attribute("mcap_rawdata_max");
			unsigned short uniformity_h = (unsigned short)pMCapRawDataConfig->Int64Attribute("uniformity_hor_max");
			unsigned short uniformity_v = (unsigned short)pMCapRawDataConfig->Int64Attribute("uniformity_ver_max");
			ParseDetailData( pMCapRawDataConfig, "mcap_rawdata_min", mcap_rawdata_min, rowsCnt, colsCnt, min );
			ParseDetailData( pMCapRawDataConfig, "mcap_rawdata_max", mcap_rawdata_max, rowsCnt, colsCnt, max );
			ParseDetailData( pMCapRawDataConfig, "uniformity_hor_max", mcap_uniformity_h, rowsCnt, colsCnt, uniformity_h );
			ParseDetailData( pMCapRawDataConfig, "uniformity_ver_max", mcap_uniformity_v, rowsCnt, colsCnt, uniformity_v );
			ParseDetailData( pMCapRawDataConfig, "mcap_rawdata", mcap_rawdata, rowsCnt, colsCnt, 6000 );

			macp_normalization_ratio_min = (float)pMCapRawDataConfig->Int64Attribute("normalization_ratio_min", 50)/100; 
			macp_normalization_ratio_max = (float)pMCapRawDataConfig->Int64Attribute("normalization_ratio_max", 150)/100; 

			rawdata_min_value = min;
			rawdata_max_value = max;
		}

		const XMLElement* pCVDiffYConfig = pWorkStation->FirstChildElement("cvdiff_y_test");
		if( pCVDiffYConfig )
		{
			cvdiff_selected_y = (unsigned char)pCVDiffYConfig->Int64Attribute("selected");
			point_range_y = (unsigned short)pCVDiffYConfig->Int64Attribute("point_range_y",100);
			cv_diff_ratio_y = (unsigned short)pCVDiffYConfig->Int64Attribute("c_value_diff_ratio_y",3);
			shake_range_y = (unsigned short)pCVDiffYConfig->Int64Attribute("shake_range_y",10);
			time_out_frames_y = (unsigned short)pCVDiffYConfig->Int64Attribute("time_out_frames_y",2000);
			stabl_frames_y = (unsigned short)pCVDiffYConfig->Int64Attribute("stabl_frames_y",10);

			p_min_y = (unsigned short)pCVDiffYConfig->Int64Attribute("p_min_y",0);
			p_max_y = (unsigned short)pCVDiffYConfig->Int64Attribute("p_max_y",8192);
		}

		const XMLElement* pCVDiffXConfig = pWorkStation->FirstChildElement("cvdiff_x_test");
		if( pCVDiffXConfig )
		{
			cvdiff_selected_x = (unsigned char)pCVDiffXConfig->Int64Attribute("selected");
			point_range_x = (unsigned short)pCVDiffXConfig->Int64Attribute("point_range_x",100);
			cv_diff_ratio_x = (unsigned short)pCVDiffXConfig->Int64Attribute("c_value_diff_ratio_x",3);
			shake_range_x = (unsigned short)pCVDiffXConfig->Int64Attribute("shake_range_x",10);
			time_out_frames_x = (unsigned short)pCVDiffXConfig->Int64Attribute("time_out_frames_x",2000);
			stabl_frames_x = (unsigned short)pCVDiffXConfig->Int64Attribute("stabl_frames_x",10);

			p_min_x = (unsigned short)pCVDiffXConfig->Int64Attribute("p_min_x",0);
			p_max_x = (unsigned short)pCVDiffXConfig->Int64Attribute("p_max_x",8192);
		}

		const XMLElement* pBaseConfig = pWorkStation->FirstChildElement("base_test");
		if( pBaseConfig )
		{
			base_selected = (unsigned char)pBaseConfig->Int64Attribute("selected");
			base_x_difference = (unsigned short)pBaseConfig->Int64Attribute("x_difference",1000);
			base_y_difference = (unsigned short)pBaseConfig->Int64Attribute("y_difference",1000);
			base_x_difference_neg = (unsigned short)pBaseConfig->Int64Attribute("x_difference_neg",1000);
			base_y_difference_neg = (unsigned short)pBaseConfig->Int64Attribute("y_difference_neg",1000);
			base_test_time = (unsigned short)pBaseConfig->Int64Attribute("test_time",5);
			base_ratio_num = (unsigned short)pBaseConfig->Int64Attribute("ratio_num",5);
			base_proportion_value = (unsigned short)pBaseConfig->Int64Attribute( "proportion_value", 40 );
		}

		const XMLElement* pNoiseConfig = pWorkStation->FirstChildElement("noise_test");
		if( pNoiseConfig )
		{
			noise_selected = (unsigned char)pNoiseConfig->Int64Attribute("selected");
			noise_frame = (short)pNoiseConfig->Int64Attribute("noise_frames");
			noise_max_mcap = (short)pNoiseConfig->Int64Attribute("noise_max_mcap");
			//noise_max_scap = (short)pNoiseConfig->Int64Attribute("noise_max_scap");
		}
		const XMLElement* pSDRockerCalibConfig = pWorkStation->FirstChildElement("sd_rocker_calib_test");
		if( pSDRockerCalibConfig )
		{
			sdrc_selected = (unsigned char)pSDRockerCalibConfig->Int64Attribute("selected");
			sdrc_y_difference = (unsigned short)pSDRockerCalibConfig->Int64Attribute("y_difference", 1000);
			sdrc_y_difference_neg = (unsigned short)pSDRockerCalibConfig->Int64Attribute("y_difference_neg", 1000);
			sdrc_test_time = (unsigned short)pSDRockerCalibConfig->Int64Attribute("test_time", 5);
			sdrc_ratio_num = (unsigned short)pSDRockerCalibConfig->Int64Attribute("ratio_num", 5);
			sdrc_proportion_value = (unsigned short)pSDRockerCalibConfig->Int64Attribute( "proportion_value", 40 );
		}
		const XMLElement* pFreePaintConfig = pWorkStation->FirstChildElement("freepaint_test");
		if( pFreePaintConfig )
		{
			swich_addr_selected = (unsigned char)pFreePaintConfig->Int64Attribute("swaddr_selected",0);
			swaddr_slaveAddr1 = (unsigned char)pFreePaintConfig->Int64Attribute("swaddr_slaveAddr1",0xff);
			swaddr_slaveAddr2 = (unsigned char)pFreePaintConfig->Int64Attribute("swaddr_slaveAddr2",0xff);
			line_type = (unsigned short)pFreePaintConfig->Int64Attribute("line_type",0);
		}
	}	
	return bRet;
}
BOOL CConfig8006::CheckCfgBinFile( unsigned char* pCfg, unsigned int byteSize )
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
BOOL CConfig8006::SubParseFromConfig()
{
	BOOL parseSuccess = FALSE;
	ISMChipNodeContainer* iContainer = GetContainerInterface();
	if(NULL == iContainer) return FALSE;

	if(NULL == szCfgBinPath || NULL == szBootBinPath)
		return parseSuccess;

	TCHAR szCfgTemp[MAX_PATH] = {0};
	TCHAR szBootTemp[MAX_PATH] = {0};
	tstring szCfgFile = tstring( CToolKit::GetExecutePath() ) + "/" + CToolKit::UTF8ToGBK( szCfgBinPath, szCfgTemp, MAX_PATH );
	tstring szBotFile = tstring( CToolKit::GetExecutePath() ) + "/" + CToolKit::UTF8ToGBK( szBootBinPath, szBootTemp, MAX_PATH );

	tstring szCfgTest = tstring( CToolKit::GetExecutePath( 1 ) ) + "/XBin/";
	szCfgTest += iContainer->GetIcName( IcType );
	szCfgTest += "_Cfg_OnlyTest.bin";

	parseSuccess = TRUE;


	rowsCnt = 22;
	colsCnt = 12;
// 	real_channel_num = rowsCnt * colsCnt;
// 	va_channel_num = real_channel_num;

	try
	{
 		FILE* file = NULL;
 		fopen_s( &file, szCfgFile.c_str(), "rb" );
 		if( NULL != file )
		{
			fseek( file, 0, SEEK_END );
			cfgBinSize = ftell( file );
			fseek( file, 0, SEEK_SET );
			if( (cfgBinSize <= MAX_CFG_BIN_SIZE) && (cfgBinSize == fread_s( cfgBinBuffer, MAX_CFG_BIN_SIZE, 1, cfgBinSize, file )) )
			{
				if( CheckCfgBinFile( cfgBinBuffer, cfgBinSize ) )
				{

					memset( ic_2_sensor_map, 0, sizeof(ic_2_sensor_map) );
					memset( sensor_2_ic_map, 0, sizeof(sensor_2_ic_map) );
					unsigned short* ps = (unsigned short*)( &cfgBinBuffer[70] );
					va_channel_num = ( ( *ps ) >> 4 ) & 0x3f;

					harf_va_channel_num = va_channel_num >> 1;
					real_channel_num = 4;
					key_setting_num =0;
					if( real_channel_num - va_channel_num > key_setting_num )
						key_setting_num = real_channel_num - va_channel_num;

					for( int index = 0; index < 4; index++ )
					{
						ic_2_sensor_map[index] = cfgBinBuffer[22 + index];
						if( ic_2_sensor_map[index] )
						{
							sensor_2_ic_map[ic_2_sensor_map[index] - 1] = index;
						}
					}

					//fix
					if( real_channel_num >= rowsCnt * colsCnt )
					{
						//key_setting_num = real_channel_num - rowsCnt * colsCnt;
						va_channel_num = rowsCnt * colsCnt;
						harf_va_channel_num = rowsCnt * colsCnt >> 1;
					}

					//resolution x y key
					//unsigned short misc = ( cfgBinBuffer[57 * 2 + 1] << 8 ) + cfgBinBuffer[57 * 2 + 0];
					//if( misc & 0x08 )
					//{
					//	resolution_x = ( cfgBinBuffer[39 * 2 + 1] << 8 ) + cfgBinBuffer[39 * 2 + 0];
					//	resolution_y = resolution_x; //( cfgBinBuffer[38 * 2 + 1] << 8 ) + cfgBinBuffer[38 * 2 + 0];
					//}
					//else
					//{
					//	resolution_x = ( cfgBinBuffer[38 * 2 + 1] << 8 ) + cfgBinBuffer[38 * 2 + 0];
					//	resolution_y = resolution_x; //( cfgBinBuffer[39 * 2 + 1] << 8 ) + cfgBinBuffer[39 * 2 + 0];
					//}

					resolution_x = ( cfgBinBuffer[38 * 2 + 1] << 8 ) + cfgBinBuffer[38 * 2 + 0];
					resolution_y = resolution_x; //( cfgBinBuffer[39 * 2 + 1] << 8 ) + cfgBinBuffer[39 * 2 + 0];

					//project verion
					unsigned short* pV = (unsigned short*)( &cfgBinBuffer[0] );
					sVersion = pV[1] >> 10;
					pVersion = (((pV[1] >> 4) & 0x03) << 9) | (pV[0] & 0x1ff);
					vVersion = (((pV[1] >> 6) & 0x03) << 7) | (pV[0] >> 9);

					vid_pid = (vVersion << 24) | (pVersion << 8) | sVersion;



					rowsCnt = 2;
					colsCnt = 2;
					
				}
				else
				{
					parseSuccess = FALSE;
				}
			}
			fclose( file );
		}

		fopen_s( &file, szBotFile.c_str(), "rb" );
		if( NULL != file )
		{
			fseek( file, 0, SEEK_END );
			bootBinSize = ftell( file );
			fseek( file, 0, SEEK_SET );
			if( (bootBinSize <= MAX_BOT_BIN_SIZE) && (bootBinSize == fread_s( bootBinBuffer, MAX_BOT_BIN_SIZE, 1, bootBinSize, file )) )
			{
				//check sum 
				unsigned int buildCheck = caculate_check_sum_ex( bootBinBuffer, bootBinSize - 4 );
				unsigned int fileCheckSum = *(unsigned int*)&bootBinBuffer[bootBinSize - 4];
				if(buildCheck == fileCheckSum)
				{

				}
				else
				{
					parseSuccess = FALSE;
				}
			}
			fclose( file );
		}

		fopen_s( &file, szCfgTest.c_str(), "rb" );
		if( NULL != file )
		{
			fseek( file, 0, SEEK_END );
			int length = ftell( file );
			fseek( file, 0, SEEK_SET );
			if( (length <= MAX_CFG_BIN_SIZE) && (length == fread_s( cfgTestBinBuffer, MAX_CFG_BIN_SIZE, 1, length, file )) )
			{
				if( CheckCfgBinFile( cfgTestBinBuffer, length ) )
				{
					cfgTestBinSize = length;
				}
				else
				{
					cfgTestBinSize = 0;
					parseSuccess = FALSE;
				}
			}
			fclose( file );
		}
	}
	catch (...)
	{
		parseSuccess = FALSE;
	}
	return parseSuccess;
}