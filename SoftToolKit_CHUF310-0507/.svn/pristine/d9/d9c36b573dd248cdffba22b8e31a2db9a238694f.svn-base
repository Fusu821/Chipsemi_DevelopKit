#include "framework.h"
#include "Config7126.h"
#include "checksum.h"
#include "../TestSrc/ToolKit.h"

#define MAX_BOT_BIN_SIZE_550 199*1024

REGIST_RUNTIME_CLASS_USHORT(CONFIG_TYPE, (CONFIG_TYPE)SEMI_IC_7126, CConfig7126)

CConfig7126::CConfig7126( unsigned short type )
:CConfig(type)
{
	current_selected = 0;
	osctrim_selected = 0;

	short_selected = 0;
	frt_selected = 0;
	iovol_selected = 0;
	vt_selected = 0;

	base_selected = 0;
	noise_selected = 0;
	misc_selected =0;
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
	tmp_num=1;
	base_diff_max = 100;
	base_num_max = 3;
	rowsCnt = 0;
	colsCnt = 0;
	memset( ic_2_sensor_map, 0, sizeof(ic_2_sensor_map) );
	memset( sensor_2_ic_map, 0, sizeof(sensor_2_ic_map) );
	memset( cfgBinBuffer, 0, sizeof(cfgBinBuffer) );
	memset( bootBinBuffer, 0, sizeof( bootBinBuffer ) );

	memset(invalid_node, 1, sizeof(invalid_node));
	memset(tmp_invalid_node, 1, sizeof(tmp_invalid_node));

	noise_max_mcap1 = 0;
	noise_max_scap1 = 0;
					  0;
	noise_max_mcap2 = 0;
	noise_max_scap2 = 0;
					  0;
	noise_max_mcap3 = 0;
	noise_max_scap3 = 0;
					  0;
	noise_max_mcap4 = 0;
	noise_max_scap4 = 0;
					  0;
	noise_max_mcap5 = 0;
	noise_max_scap5 = 0;
					  0;
	noise_max_mcap6 = 0;
	noise_max_scap6 = 0;
					  0;
	noise_max_mcap7 = 0;
	noise_max_scap7 = 0;
					  0;
	noise_max_mcap8 = 0;
	noise_max_scap8 = 0;

	fsd_frames = 20;

	
}
CConfig7126::~CConfig7126()
{

}
BOOL CConfig7126::Parse( const tinyxml2::XMLDocument& xmlDoc )
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
			deep_current_min = (short)pCurrentConfig->Int64Attribute("deep_current_min",0);
			deep_current_max = (short)pCurrentConfig->Int64Attribute("deep_current_max",100);
			sleep_current_min = (short)pCurrentConfig->Int64Attribute("sleep_current_min",0);
			sleep_current_max = (short)pCurrentConfig->Int64Attribute("sleep_current_max",240);
			active_current_min = (short)pCurrentConfig->Int64Attribute("active_current_min",5);
			active_current_max = (short)pCurrentConfig->Int64Attribute("active_current_max",60);

			vbus_deep_current_min = (short)pCurrentConfig->Int64Attribute("vbus_deep_current_min",0);
			vbus_deep_current_max = (short)pCurrentConfig->Int64Attribute("vbus_deep_current_max",100);
			vbus_sleep_current_min = (short)pCurrentConfig->Int64Attribute("vbus_sleep_current_min",0);
			vbus_sleep_current_max = (short)pCurrentConfig->Int64Attribute("vbus_sleep_current_max",240);
			vbus_active_current_min = (short)pCurrentConfig->Int64Attribute("vbus_active_current_min",10);
			vbus_active_current_max = (short)pCurrentConfig->Int64Attribute("vbus_active_current_max",60);

		}
		const XMLElement* pOSCTrimConfig = pWorkStation->FirstChildElement("osctrim_test");
		if( pOSCTrimConfig )
		{
			osctrim_selected = (unsigned char)pOSCTrimConfig->Int64Attribute("selected");
			tick_32k_standard = (unsigned int)pOSCTrimConfig->Int64Attribute("tick_32k_standard");
			trim_32k_min = (unsigned char)pOSCTrimConfig->Int64Attribute("trim_32k_min");
			trim_32k_max = (unsigned char)pOSCTrimConfig->Int64Attribute("trim_32k_max");
			offset_32k = (unsigned short)pOSCTrimConfig->Int64Attribute("offset_32k");

			tick_144m_standard = (unsigned int)pOSCTrimConfig->Int64Attribute("tick_144m_standard");
			tick_144m_standardNo2 = (unsigned int)pOSCTrimConfig->Int64Attribute("tick_144m_standardNo2");
			tick_144m_standardNo3 = (unsigned int)pOSCTrimConfig->Int64Attribute("tick_144m_standardNo3");
			tick_144m_standardNo4 = (unsigned int)pOSCTrimConfig->Int64Attribute("tick_144m_standardNo4");
			tick_144m_standardNo5 = (unsigned int)pOSCTrimConfig->Int64Attribute("tick_144m_standardNo5");
			trim_144m_min = (unsigned short)pOSCTrimConfig->Int64Attribute("trim_144m_min");
			trim_144m_max = (unsigned short)pOSCTrimConfig->Int64Attribute("trim_144m_max");
			offset_144m = (unsigned short)pOSCTrimConfig->Int64Attribute("offset_144m");

			tick_250m_standard = (unsigned int)pOSCTrimConfig->Int64Attribute("tick_250m_standard");
			trim_250m_min = (unsigned char)pOSCTrimConfig->Int64Attribute("trim_250m_min");
			trim_250m_max = (unsigned char)pOSCTrimConfig->Int64Attribute("trim_250m_max");
			offset_250m = (unsigned short)pOSCTrimConfig->Int64Attribute("offset_250m");

			trim_speed_mode = (unsigned char)pOSCTrimConfig->Int64Attribute("speed_mode");

			trim_only_check = (unsigned char)pOSCTrimConfig->Int64Attribute("only_check", 0);
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
			short_tx_max = (unsigned short)pShortConfig->Int64Attribute("short_tx_max", 400);
			short_rx_max = (unsigned short)pShortConfig->Int64Attribute("short_rx_max", 400);
		}

		const XMLElement* pFrtConfig = pWorkStation->FirstChildElement("frt_test");
		if( pFrtConfig )
		{
			frt_selected = (unsigned char)pFrtConfig->Int64Attribute("selected");
		}

		const XMLElement* pWDogTConfig = pWorkStation->FirstChildElement("wdogt_test");
		if( pWDogTConfig )
		{
			wdogt_selected = (unsigned char)pWDogTConfig->Int64Attribute("selected");
		}

		const XMLElement* pIoVolConfig = pWorkStation->FirstChildElement("iovol_test");
		if( pIoVolConfig )
		{
			iovol_selected = (unsigned char)pIoVolConfig->Int64Attribute("selected");
			int_low_min = (unsigned int)pIoVolConfig->Int64Attribute("int_low_min", 0);
			int_low_max = (unsigned int)pIoVolConfig->Int64Attribute("int_low_max", 300);
			int_high_min = (unsigned int)pIoVolConfig->Int64Attribute("int_high_min", 1600);
			int_high_max = (unsigned int)pIoVolConfig->Int64Attribute("int_high_max", 2000);
			iic_low_min = (unsigned int)pIoVolConfig->Int64Attribute("iic_low_min", 0);
			iic_low_max = (unsigned int)pIoVolConfig->Int64Attribute("iic_low_max", 300);
			iic_high_min = (unsigned int)pIoVolConfig->Int64Attribute("iic_high_min", 1600);
			iic_high_max = (unsigned int)pIoVolConfig->Int64Attribute("iic_high_max", 2000);
			spi_low_min = (unsigned int)pIoVolConfig->Int64Attribute("spi_low_min", 0);
			spi_low_max = (unsigned int)pIoVolConfig->Int64Attribute("spi_low_max", 300);
			spi_high_min = (unsigned int)pIoVolConfig->Int64Attribute("spi_high_min", 1600);
			spi_high_max = (unsigned int)pIoVolConfig->Int64Attribute("spi_high_max", 2000);
		}

		const XMLElement* pScapRawDataConfig = pWorkStation->FirstChildElement("scap_rawdata_test");
		if( pScapRawDataConfig )
		{
			scap_rawdata_selected = (unsigned char)pScapRawDataConfig->Int64Attribute("selected");
			unsigned short defmin = (unsigned short)pScapRawDataConfig->Int64Attribute("scap_rawdata_min", 3000);
			unsigned short defmax = (unsigned short)pScapRawDataConfig->Int64Attribute("scap_rawdata_max", 16000);
			ParseDetailData( pScapRawDataConfig, "scap_rawdata_min", scap_rawdata_min, rowsCnt, max(rowsCnt, colsCnt), defmin );
			ParseDetailData( pScapRawDataConfig, "scap_rawdata_max", scap_rawdata_max, rowsCnt, max(rowsCnt, colsCnt), defmax );
		}

		const XMLElement* pStcConfig = pWorkStation->FirstChildElement("stc_test");
		if( pStcConfig )
		{
			stc_selected = (unsigned char)pStcConfig->Int64Attribute("selected");
			stc_clk_div = (unsigned short)pStcConfig->Int64Attribute("clk_div", 20);
			stc_min = (signed short)pStcConfig->Int64Attribute("stc_min");
			stc_max = (signed short)pStcConfig->Int64Attribute("stc_max");
			unsigned short uniformity_h = (unsigned short)pStcConfig->Int64Attribute("uniformity_hor_max");
			unsigned short uniformity_v = (unsigned short)pStcConfig->Int64Attribute("uniformity_ver_max");
			//ParseDetailData( pStcConfig, "stc_min", stc_min, rowsCnt, colsCnt, min );
			//ParseDetailData( pStcConfig, "stc_max", stc_max, rowsCnt, colsCnt, max );
			ParseDetailData( pStcConfig, "uniformity_hor_max", stc_uniformity_h, rowsCnt, colsCnt, uniformity_h );
			ParseDetailData( pStcConfig, "uniformity_ver_max", stc_uniformity_v, rowsCnt, colsCnt, uniformity_v );
			ParseDetailData( pStcConfig, "stc_mean", stc_mean, rowsCnt, colsCnt, 0 );
			ParseDetailData( pStcConfig, "stc_mse", stc_mse, rowsCnt, colsCnt, 10 );
		}

		const XMLElement* pMCapRawDataConfig = pWorkStation->FirstChildElement("mcap_rawdata_test");
		if( pMCapRawDataConfig )
		{
			mcap_rawdata_selected = (unsigned char)pMCapRawDataConfig->Int64Attribute("selected");
			mcap_clk_div = (unsigned short)pMCapRawDataConfig->Int64Attribute("clk_div", 12);
			check_uniformity_hor = (unsigned char)pMCapRawDataConfig->Int64Attribute("check_uniformity_hor", 1);
			check_uniformity_ver = (unsigned char)pMCapRawDataConfig->Int64Attribute("check_uniformity_ver", 1);
			unsigned short min = (unsigned short)pMCapRawDataConfig->Int64Attribute("mcap_rawdata_min", 3000);
			unsigned short max = (unsigned short)pMCapRawDataConfig->Int64Attribute("mcap_rawdata_max", 16000);
			unsigned short uniformity_h = (unsigned short)pMCapRawDataConfig->Int64Attribute("uniformity_hor_max", 20);
			unsigned short uniformity_v = (unsigned short)pMCapRawDataConfig->Int64Attribute("uniformity_ver_max", 20);
			ParseDetailData( pMCapRawDataConfig, "mcap_rawdata_min", mcap_rawdata_min, rowsCnt, colsCnt, min );
			ParseDetailData( pMCapRawDataConfig, "mcap_rawdata_max", mcap_rawdata_max, rowsCnt, colsCnt, max );
			ParseDetailData( pMCapRawDataConfig, "uniformity_hor_max", mcap_uniformity_h, rowsCnt, colsCnt, uniformity_h );
			ParseDetailData( pMCapRawDataConfig, "uniformity_ver_max", mcap_uniformity_v, rowsCnt, colsCnt, uniformity_v );
			ParseDetailData( pMCapRawDataConfig, "mcap_rawdata", mcap_rawdata, rowsCnt, colsCnt, 6000 );

			macp_normalization_ratio_min = (float)pMCapRawDataConfig->Int64Attribute("normalization_ratio_min", 100)/100; 
			macp_normalization_ratio_max = (float)pMCapRawDataConfig->Int64Attribute("normalization_ratio_max", 100)/100; 

			ParseDetailData( pMCapRawDataConfig, "uniformity_invalid", uniformity_invalid_node, rowsCnt, colsCnt, 1 );
			macp_h_v_over_limit_ratio = (float)pMCapRawDataConfig->Int64Attribute("h_v_over_limit_ratio", 100)/100; 
			macp_h_v_over_limit_maxnum = (unsigned short)pMCapRawDataConfig->Int64Attribute("h_v_over_limit_maxnum", 10); 
			
			rawdata_min_value = min;
			rawdata_max_value = max;
		}

		//const XMLElement* pVTConfig = pWorkStation->FirstChildElement("vt_test");
		//if( pVTConfig )
		//{
		//	vt_selected = (unsigned char)pVTConfig->Int64Attribute("selected");
		//	//vt_min = (short)pVTConfig->Int64Attribute("vt_min");
		//	vt_max = (short)pVTConfig->Int64Attribute("vt_max",100);
		//	ParseDetailData( pVTConfig, "vt_on", vt_on, 1, rowsCnt,1000);
		//	ParseDetailData( pVTConfig, "vt_off", vt_off, 1, rowsCnt,0);
		//	ParseDetailData( pVTConfig, "vt_diff_max", vt_diff_max, 1, rowsCnt, vt_max);
		//}

		const XMLElement* pWBaseConfig = pWorkStation->FirstChildElement("wbase_test");
		if( pWBaseConfig )
		{
			wbase_selected = (unsigned char)pWBaseConfig->Int64Attribute("selected");

			wbase_node33_diff_max = (unsigned short)pWBaseConfig->Int64Attribute("wbase_node33_diff_max", 400);
			wbase_node33_num_max = (unsigned short)pWBaseConfig->Int64Attribute("wbase_node33_num_max", 8);

			//wbase_node55_diff_max = (unsigned short)pWBaseConfig->Int64Attribute("wbase_node55_diff_max", 300);
			//wbase_node55_num_max = (unsigned short)pWBaseConfig->Int64Attribute("wbase_node55_num_max", 15);

			wbase_all_diff_max = (unsigned short)pWBaseConfig->Int64Attribute("wbase_all_diff_max", 600);
			wbase_all_num_max = (unsigned short)pWBaseConfig->Int64Attribute("wbase_all_num_max", 10);

			if (1 == wbase_selected)
			{
				ParseDetailData( pWBaseConfig, "tmp_invalid", tmp_invalid_node, rowsCnt, colsCnt, 1 );

				ParseDetailData( pWBaseConfig, "tmp_1_mcapdata", tmp_1_mcapdata, rowsCnt, colsCnt, 1 );
				tmp_data_normalization<unsigned short, unsigned short, MAX_MCAP_ROW_710, MAX_MCAP_COL_710>(tmp_1_mcapdata,tmp_1_mcapdata,rowsCnt, colsCnt,1);

				ParseDetailData( pWBaseConfig, "tmp_2_mcapdata", tmp_2_mcapdata, rowsCnt, colsCnt, 1 );
				tmp_data_normalization<unsigned short, unsigned short, MAX_MCAP_ROW_710, MAX_MCAP_COL_710>(tmp_2_mcapdata,tmp_2_mcapdata,rowsCnt, colsCnt,1);

				ParseDetailData( pWBaseConfig, "tmp_3_mcapdata", tmp_3_mcapdata, rowsCnt, colsCnt, 1 );
				tmp_data_normalization<unsigned short, unsigned short, MAX_MCAP_ROW_710, MAX_MCAP_COL_710>(tmp_3_mcapdata,tmp_3_mcapdata,rowsCnt, colsCnt,1);

				ParseDetailData( pWBaseConfig, "tmp_4_mcapdata", tmp_4_mcapdata, rowsCnt, colsCnt, 1 );
				tmp_data_normalization<unsigned short, unsigned short, MAX_MCAP_ROW_710, MAX_MCAP_COL_710>(tmp_4_mcapdata,tmp_4_mcapdata,rowsCnt, colsCnt,1);

				ParseDetailData( pWBaseConfig, "tmp_5_mcapdata", tmp_5_mcapdata, rowsCnt, colsCnt, 1 );
				tmp_data_normalization<unsigned short, unsigned short, MAX_MCAP_ROW_710, MAX_MCAP_COL_710>(tmp_5_mcapdata,tmp_5_mcapdata,rowsCnt, colsCnt,1);

				ParseDetailData( pWBaseConfig, "tmp_6_mcapdata", tmp_6_mcapdata, rowsCnt, colsCnt, 1 );
				tmp_data_normalization<unsigned short, unsigned short, MAX_MCAP_ROW_710, MAX_MCAP_COL_710>(tmp_6_mcapdata,tmp_6_mcapdata,rowsCnt, colsCnt,1);

				ParseDetailData( pWBaseConfig, "tmp_7_mcapdata", tmp_7_mcapdata, rowsCnt, colsCnt, 1 );
				tmp_data_normalization<unsigned short, unsigned short, MAX_MCAP_ROW_710, MAX_MCAP_COL_710>(tmp_7_mcapdata,tmp_7_mcapdata,rowsCnt, colsCnt,1);

				ParseDetailData( pWBaseConfig, "tmp_8_mcapdata", tmp_8_mcapdata, rowsCnt, colsCnt, 1 );
				tmp_data_normalization<unsigned short, unsigned short, MAX_MCAP_ROW_710, MAX_MCAP_COL_710>(tmp_8_mcapdata,tmp_8_mcapdata,rowsCnt, colsCnt,1);

				//unsigned short (*tmp_base[8])[MAX_MCAP_COL_710] ={tmp_1_mcapdata,tmp_2_mcapdata,tmp_3_mcapdata,tmp_4_mcapdata,tmp_5_mcapdata,tmp_6_mcapdata,tmp_7_mcapdata,tmp_8_mcapdata};

				//[&](){
				//	for (int i =0; i < rowsCnt; i++)
				//	{
				//		for (int j =0; j < colsCnt; j++)
				//		{

				//			float df = (float)(tmp_base[wbase_fast][i][j])/ (float)(tmp_base[wbase_slow][i][j]);
				//			df = df==0 ? 10000: df;
				//			fator_HL[i][j] = df;
				//		}
				//	}
				//}();
			}


		}

		const XMLElement* pBaseConfig = pWorkStation->FirstChildElement("base_test");
		if( pBaseConfig )
		{
			base_selected = (unsigned char)pBaseConfig->Int64Attribute("selected");
			base_diff_max = (unsigned short)pBaseConfig->Int64Attribute("base_diff_max", 400);
			base_num_max = (unsigned short)pBaseConfig->Int64Attribute("base_num_max", 8);
			base_all_diff_max = (unsigned short)pBaseConfig->Int64Attribute("base_all_diff_max", 600);
			base_all_num_max = (unsigned short)pBaseConfig->Int64Attribute("base_all_num_max", 10);
			//base_cover_diff_max =  (unsigned short)pBaseConfig->Int64Attribute("base_cover_diff_max");

			//base_save_data = (unsigned char)pBaseConfig->Int64Attribute("base_save_data",0);
			//base_simplifyA_algorithm = (unsigned char)pBaseConfig->Int64Attribute("base_simplifyA_algorithm",0);
			if (1 == base_selected)
			{
				ParseDetailData( pBaseConfig, "tmp_invalid", tmp_invalid_node, rowsCnt, colsCnt, 1 );

				ParseDetailData( pBaseConfig, "tmp_1_mcapdata", tmp_1_mcapdata, rowsCnt, colsCnt, 1 );
				tmp_data_normalization<unsigned short, unsigned short, MAX_MCAP_ROW_710, MAX_MCAP_COL_710>(tmp_1_mcapdata,tmp_1_mcapdata,rowsCnt, colsCnt,1);

				ParseDetailData( pBaseConfig, "tmp_2_mcapdata", tmp_2_mcapdata, rowsCnt, colsCnt, 1 );
				tmp_data_normalization<unsigned short, unsigned short, MAX_MCAP_ROW_710, MAX_MCAP_COL_710>(tmp_2_mcapdata,tmp_2_mcapdata,rowsCnt, colsCnt,1);

				ParseDetailData( pBaseConfig, "tmp_3_mcapdata", tmp_3_mcapdata, rowsCnt, colsCnt, 1 );
				tmp_data_normalization<unsigned short, unsigned short, MAX_MCAP_ROW_710, MAX_MCAP_COL_710>(tmp_3_mcapdata,tmp_3_mcapdata,rowsCnt, colsCnt,1);

				ParseDetailData( pBaseConfig, "tmp_4_mcapdata", tmp_4_mcapdata, rowsCnt, colsCnt, 1 );
				tmp_data_normalization<unsigned short, unsigned short, MAX_MCAP_ROW_710, MAX_MCAP_COL_710>(tmp_4_mcapdata,tmp_4_mcapdata,rowsCnt, colsCnt,1);

				ParseDetailData( pBaseConfig, "tmp_5_mcapdata", tmp_5_mcapdata, rowsCnt, colsCnt, 1 );
				tmp_data_normalization<unsigned short, unsigned short, MAX_MCAP_ROW_710, MAX_MCAP_COL_710>(tmp_5_mcapdata,tmp_5_mcapdata,rowsCnt, colsCnt,1);

				ParseDetailData( pBaseConfig, "tmp_6_mcapdata", tmp_6_mcapdata, rowsCnt, colsCnt, 1 );
				tmp_data_normalization<unsigned short, unsigned short, MAX_MCAP_ROW_710, MAX_MCAP_COL_710>(tmp_6_mcapdata,tmp_6_mcapdata,rowsCnt, colsCnt,1);

				ParseDetailData( pBaseConfig, "tmp_7_mcapdata", tmp_7_mcapdata, rowsCnt, colsCnt, 1 );
				tmp_data_normalization<unsigned short, unsigned short, MAX_MCAP_ROW_710, MAX_MCAP_COL_710>(tmp_7_mcapdata,tmp_7_mcapdata,rowsCnt, colsCnt,1);

				ParseDetailData( pBaseConfig, "tmp_8_mcapdata", tmp_8_mcapdata, rowsCnt, colsCnt, 1 );
				tmp_data_normalization<unsigned short, unsigned short, MAX_MCAP_ROW_710, MAX_MCAP_COL_710>(tmp_8_mcapdata,tmp_8_mcapdata,rowsCnt, colsCnt,1);
			}

		}

		const XMLElement* pNoiseConfig = pWorkStation->FirstChildElement("noise_test");
		if( pNoiseConfig )
		{
			noise_selected = (unsigned char)pNoiseConfig->Int64Attribute("selected");
			noise_frame = (short)pNoiseConfig->Int64Attribute("noise_frames",60);

			unsigned short defscap_base = (unsigned short)pNoiseConfig->Int64Attribute("noise_scap_base_value_default",160);
			ParseDetailData( pNoiseConfig, "noise_scap_base", noise_scap_base, rowsCnt, max(rowsCnt, colsCnt), defscap_base );

			unsigned short defmcap_base = (unsigned short)pNoiseConfig->Int64Attribute("noise_mcap_base_value_default",160);
			ParseDetailData( pNoiseConfig, "noise_mcap_base", noise_mcap_base, rowsCnt, colsCnt, defmcap_base );

			noise_max_mcap1 = (short)pNoiseConfig->Int64Attribute("noise_max_mcap1",100);
			noise_max_scap1 = (short)pNoiseConfig->Int64Attribute("noise_max_scap1",100);
																				 
			noise_max_mcap2 = (short)pNoiseConfig->Int64Attribute("noise_max_mcap2",100);
			noise_max_scap2 = (short)pNoiseConfig->Int64Attribute("noise_max_scap2",100);
																				 
			noise_max_mcap3 = (short)pNoiseConfig->Int64Attribute("noise_max_mcap3",100);
			noise_max_scap3 = (short)pNoiseConfig->Int64Attribute("noise_max_scap3",100);
																				
			noise_max_mcap4 = (short)pNoiseConfig->Int64Attribute("noise_max_mcap4",100);
			noise_max_scap4 = (short)pNoiseConfig->Int64Attribute("noise_max_scap4",100);
																				
			noise_max_mcap5 = (short)pNoiseConfig->Int64Attribute("noise_max_mcap5",100);
			noise_max_scap5 = (short)pNoiseConfig->Int64Attribute("noise_max_scap5",100);
																				
			noise_max_mcap6 = (short)pNoiseConfig->Int64Attribute("noise_max_mcap6",100);
			noise_max_scap6 = (short)pNoiseConfig->Int64Attribute("noise_max_scap6",100);
																				
			noise_max_mcap7 = (short)pNoiseConfig->Int64Attribute("noise_max_mcap7",100);
			noise_max_scap7 = (short)pNoiseConfig->Int64Attribute("noise_max_scap7",100);
																				 
			noise_max_mcap8 = (short)pNoiseConfig->Int64Attribute("noise_max_mcap8",100);
			noise_max_scap8 = (short)pNoiseConfig->Int64Attribute("noise_max_scap8",100);
		}
		const XMLElement* pMiscConfig = pWorkStation->FirstChildElement("misc_test");
		if( pMiscConfig )
		{
			misc_selected = (unsigned char)pMiscConfig->Int64Attribute("selected");
			misc_mode = (unsigned short)pMiscConfig->Int64Attribute("misc_mode");
		}
		const XMLElement* pfsdConfig = pWorkStation->FirstChildElement("fsd_test");
		if( pfsdConfig )
		{
			fsd_selected = (unsigned char)pfsdConfig->Int64Attribute("selected");
			fsd_fast_div = (unsigned short)pfsdConfig->Int64Attribute("fsd_fast_div", 4);
			fsd_slow_div = (unsigned short)pfsdConfig->Int64Attribute("fsd_slow_div", 10);
			fsd_frames = (unsigned short)pfsdConfig->Int64Attribute("fsd_frames", 20);
			fsd_diff_max_default = (unsigned short)pfsdConfig->Int64Attribute("fsd_diff_max_default", 600);

			fsd_xy_num = (unsigned char)pfsdConfig->Int64Attribute("fsd_xy_num", 0x15);
			fsd_i2v_rfb = (unsigned char)pfsdConfig->Int64Attribute("fsd_i2v_rfb", 0x20);

			fsd_lpf_sft = (unsigned char)pfsdConfig->Int64Attribute("fsd_lpf_sft", 0x06);
			fsd_dec_sft = (unsigned char)pfsdConfig->Int64Attribute("fsd_dec_sft", 0x03);

			fsd_c2v_rfb = (unsigned char)pfsdConfig->Int64Attribute("fsd_c2v_rfb", 0x4);
			fsd_rx_rin = (unsigned char)pfsdConfig->Int64Attribute("fsd_rx_rin", 0x00);

			ParseDetailData( pfsdConfig, "fsd_diff_max", fsd_diff_max, rowsCnt, colsCnt, fsd_diff_max_default );
			ParseDetailData( pfsdConfig, "fsd_fast", fsd_fast, rowsCnt, colsCnt, 1000 );
			ParseDetailData( pfsdConfig, "fsd_slow", fsd_slow, rowsCnt, colsCnt, 0 );

			fsd_fast_mcap_test = (unsigned char)pfsdConfig->Int64Attribute("fsd_fast_mcap_test", 0);
			fsd_fast_mcap_limit = (unsigned short)pfsdConfig->Int64Attribute("fsd_fast_mcap_limit", 30);
			if (fsd_fast_mcap_test == 1)
			{
				MatrixMultiplication<unsigned short,unsigned short,float,MAX_MCAP_ROW_710, MAX_MCAP_COL_710>(fsd_fast_min, fsd_fast,((float)(100 - fsd_fast_mcap_limit))/100, MAX_MCAP_ROW_710, MAX_MCAP_COL_710);

				MatrixMultiplication<unsigned short,unsigned short,float,MAX_MCAP_ROW_710, MAX_MCAP_COL_710>(fsd_fast_max, fsd_fast,((float)(100 + fsd_fast_mcap_limit))/100, MAX_MCAP_ROW_710, MAX_MCAP_COL_710);
			}
		}
	}	
	return bRet;
}
BOOL CConfig7126::CheckCfgBinFile( unsigned char* pCfg, unsigned int byteSize )
{
	if( !pCfg ) return FALSE;
	if( byteSize > MAX_CFG_BIN_SIZE )  return FALSE;
	if( byteSize < 64 )  return FALSE;
	if( byteSize & 1 )   return FALSE;

	unsigned int check = 0;
	check = caculate_check_sum_u32((unsigned int*)pCfg,byteSize);

	//unsigned short *ps = (unsigned short*)pCfg;
	//byteSize = byteSize >> 1;
	//check = *ps++;
	//for( int index = 1; index < (int)byteSize; index++ )
	//{
	//	check += *ps++; 
	//}
	if(check)
	{
		return FALSE;
	}
	return TRUE;
}
BOOL CConfig7126::SubParseFromConfig()
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
					rowsCnt = cfgBinBuffer[0x1a];
					colsCnt = cfgBinBuffer[0x19];

					real_channel_num = rowsCnt * colsCnt;
					va_channel_num = real_channel_num;

					vid_pid = *((UINT64*)(cfgBinBuffer + 1));
					vid_pid = vid_pid & 0x000000ffffffffff;

					for( int index = 0; index < colsCnt/*MAX_TX_NUM_7449*/; index++ )
					{
						sensor_2_ic_map[index] = cfgBinBuffer[0x50 + index];
						ic_2_sensor_map[cfgBinBuffer[0x50 + index]] = index + 1;
					}
					for( int index = 0; index < rowsCnt/*MAX_RX_NUM_7449*/; index++ )
					{
						sensor_2_ic_map[index + MAX_TX_NUM_7126] = cfgBinBuffer[0x64 + index];
						ic_2_sensor_map[cfgBinBuffer[0x64 + index] + 0] = index + MAX_TX_NUM_7126 + 1;
					}

					if(cfgBinBuffer[0x33] & 0x01)
					{
						resolution_x = (cfgBinBuffer[0x09] << 8) + cfgBinBuffer[0x08];
						resolution_y = (cfgBinBuffer[0x07] << 8) + cfgBinBuffer[0x06];
					}
					else
					{
						resolution_x = (cfgBinBuffer[0x07] << 8) + cfgBinBuffer[0x06];
						resolution_y = (cfgBinBuffer[0x09] << 8) + cfgBinBuffer[0x08];
					}
					
					//project verion
					unsigned short* pV = (unsigned short*)( &cfgBinBuffer[0] );
// 					sVersion = pV[1] >> 10;
// 					pVersion = pV[0] & 0x1ff;
// 					vVersion = pV[0] >> 9;
					sVersion = cfgBinBuffer[0x01];
					pVersion = (cfgBinBuffer[0x03] << 8) + cfgBinBuffer[0x02];
					vVersion = (cfgBinBuffer[0x05] << 8) + cfgBinBuffer[0x04];

					tmp_num = cfgBinBuffer[0x501];

					/*Set_Key_Num = key_setting_num = cfgBinBuffer[0x52];//7126暂不支持按键
					if((cfgBinBuffer[0x53] & 0x02) > 0)
					{
						int Key_x = (cfgBinBuffer[0x55] << 8) + cfgBinBuffer[0x54];
						for (int i=0;i<5;i++)
						{
							keyarray[i][0]=Key_x;
						}
						keyarray[0][1] = (cfgBinBuffer[0x57] << 8) + cfgBinBuffer[0x56];
						keyarray[1][1] = (cfgBinBuffer[0x59] << 8) + cfgBinBuffer[0x58];
						keyarray[2][1] = (cfgBinBuffer[0x5b] << 8) + cfgBinBuffer[0x5a];
						keyarray[3][1] = (cfgBinBuffer[0x5d] << 8) + cfgBinBuffer[0x5c];
						keyarray[4][1] = (cfgBinBuffer[0x5f] << 8) + cfgBinBuffer[0x5e];
					}
					else
					{
						int Key_y = (cfgBinBuffer[0x55] << 8) + cfgBinBuffer[0x54];
						for (int i=0;i<5;i++)
						{
							keyarray[i][1]=Key_y;
						}
						keyarray[0][0] = (cfgBinBuffer[0x57] << 8) + cfgBinBuffer[0x56];
						keyarray[1][0] = (cfgBinBuffer[0x59] << 8) + cfgBinBuffer[0x58];
						keyarray[2][0] = (cfgBinBuffer[0x5b] << 8) + cfgBinBuffer[0x5a];
						keyarray[3][0] = (cfgBinBuffer[0x5d] << 8) + cfgBinBuffer[0x5c];
						keyarray[4][0] = (cfgBinBuffer[0x5f] << 8) + cfgBinBuffer[0x5e];
					}*/

					//[&]()->void{

					//	char *cdsp;
					//	char *cdspNow;

					//	unsigned char gDeFhGroupMax = 0;
					//	unsigned char freq = 0;
					//	unsigned char div = 0;

					//	unsigned short freqGetBuf[8]={0};
					//	unsigned short freqSortIndex[8]={0};
					//	unsigned short xy_div = 0;
					//	
					//	short v = 0;

					//	unsigned char mcu_freq = 0;
					//	unsigned char mcu_freq_index = 0;
					//	unsigned char muc_freq_buf[5]={104,100,96,92,88};

					//	gDeFhGroupMax=*(unsigned char *)(cfgBinBuffer+0x500+1);

					//	for (freq = 0; freq < gDeFhGroupMax; freq++) 
					//	{
					//		cdsp = (char *)(cfgBinBuffer+0x0100);
					//		cdspNow = cdsp + (unsigned short)freq * 3 * 0x20;

					//		xy_div = *(unsigned short *)(cdspNow+0);
					//		mcu_freq_index = *(unsigned char *)(cdspNow+0x1F);

					//		mcu_freq=muc_freq_buf[mcu_freq_index];

					//		div = xy_div + 1;
					//		v = (short)div * 96;
					//		freqGetBuf[freq] = ((unsigned int)1500 * 10 * mcu_freq + (v >> 1)) / v;
					//	}

					//	[](unsigned short *srcBuf, unsigned short len, unsigned short *pIndex)->void{

					//		unsigned short i = 0;
					//		unsigned short j = 0;
					//		unsigned short temp = 0;

					//		for (i = 0; i < len; i++) 
					//		{
					//			pIndex[i] = i;
					//		}

					//		for (i = 0; i < (len - 1); i++) 
					//		{
					//			for (j = 0; j < (len - 1 - i); j++) 
					//			{
					//				if (srcBuf[pIndex[j]] > srcBuf[pIndex[j + 1]]) 
					//				{
					//					temp = pIndex[j];
					//					pIndex[j] = pIndex[j + 1];
					//					pIndex[j + 1] = temp;
					//				}
					//			}
					//		}
					//	}(freqGetBuf, gDeFhGroupMax, freqSortIndex);
					//	//SortIndexS16(freqGetBuf, gDeFhGroupMax, freqSortIndex);
					//	wbase_slow = freqSortIndex[0];
					//	wbase_fast = freqSortIndex[gDeFhGroupMax - 1];
					//}();
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
			if( (bootBinSize <= MAX_BOT_BIN_SIZE_550) && (bootBinSize == fread_s( bootBinBuffer, MAX_BOT_BIN_SIZE_550, 1, bootBinSize, file )) )
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