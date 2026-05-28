#include "framework.h"
#include "Config5816.h"
#include "checksum.h"
#include "../TestSrc/ToolKit.h"
REGIST_RUNTIME_CLASS_USHORT(CONFIG_TYPE, (CONFIG_TYPE)SEMI_IC_5816, CConfig5816)

typedef CConfig5816 CConfig1716;
REGIST_RUNTIME_CLASS_USHORT(CONFIG_TYPE, (CONFIG_TYPE)SEMI_IC_1716, CConfig1716)

typedef struct __ts5816_config_if
{
	unsigned short sig_fw;  // 01 signature:0x3535
	unsigned short ver_fw;  // 02 version_number of fw

	// @hardware configure
	unsigned short clk_ctl; // 03 tl_clk & int_clk
	unsigned short sample_ctl; // 04 sample count & scale
	unsigned short dvdd_out;
	unsigned short ctl5_intl; // 05 tl_clk & int_clk
	unsigned short ctl5_inth; // 06 tl_clk & int_clk
	unsigned short gp0_intl; // 07 tl_clk & int_clk
	unsigned short gp0_inth; // 08 tl_clk & int_clk
	unsigned short gp1_intl; // 09 tl_clk & int_clk
	unsigned short gp1_inth; // 10 tl_clk & int_clk
	unsigned short gp2_intl; // 11 tl_clk & int_clk
	unsigned short gp2_inth; // 12 tl_clk & int_clk
	unsigned short gp3_intl; // 13 tl_clk & int_clk
	unsigned short gp3_inth; // 14 tl_clk & int_clk

	// @todo: reduce configure data size: 18*2bytes: grp[7:4]idx[3:0]
	unsigned short gp0_0map; // 23 tl_clk & int_clk
	unsigned short gp0_1map; // 24 tl_clk & int_clk
	unsigned short gp0_2map; // 25 tl_clk & int_clk
	unsigned short gp0_3map; // 26 tl_clk & int_clk
	unsigned short gp0_4map; // 27 tl_clk & int_clk
	unsigned short gp1_0map; // 28 tl_clk & int_clk
	unsigned short gp1_1map; // 29 tl_clk & int_clk
	unsigned short gp1_2map; // 30 tl_clk & int_clk
	unsigned short gp1_3map; // 31 tl_clk & int_clk
	unsigned short gp1_4map; // 32 tl_clk & int_clk
	unsigned short gp2_0map; // 33 tl_clk & int_clk
	unsigned short gp2_1map; // 34 tl_clk & int_clk
	unsigned short gp2_2map; // 35 tl_clk & int_clk
	unsigned short gp2_3map; // 36 tl_clk & int_clk
	unsigned short gp2_4map; // 37 tl_clk & int_clk 
	unsigned short gp3_0map; // 38 tl_clk & int_clk
	unsigned short gp3_1map; // 39 tl_clk & int_clk
	unsigned short gp3_2map; // 40 tl_clk & int_clk
	unsigned short gp3_3map; // 41 tl_clk & int_clk
	unsigned short gp3_4map; // 42 tl_clk & int_clk  

	unsigned short tp_chain; // 63 all-channel & aa-channel & type &key 6:6:1:3
	unsigned short tp_phyx; // 64 width
	unsigned short tp_phyy; // 65 height
	unsigned short lcd_x; // 66 x-coord,  revert:[15]?
	unsigned short lcd_y; // 67 y-coord,  revert:[15]?

	// @key mapping
	unsigned short key0_x;  //68
	unsigned short key1_x;  //69
	unsigned short key2_x;  //70
	unsigned short key3_x;  //71
	unsigned short key0_y;  //72
	unsigned short key1_y;  //73
	unsigned short key2_y;  //74
	unsigned short key3_y;  //75
	unsigned short th_key;  // key noise [0,7], key threhold[7,15], use overlay as X2

	// @lock baseline
	unsigned short stable_fn; //77 tl_clk & int_clk

	unsigned short th_noise; //78 tl_clk & int_clk

	// @baseline tracking
	unsigned short trk_ratio; //80 p & n
	unsigned short trk_freq; //81 earlier & normal
	unsigned short trk_th; //82 earlier & normal
	unsigned short raw2buf; //83 cdsp & scaled base


	// @mdf
	unsigned short v_win_len;   //84 max[15:12]&min[11:8]&vlen[7:4]&shift[3:0]
	unsigned short v2_depth;    //85 C=[15..8] K= [7..0] 

	// @control bits
	unsigned short misc1_en;    //86

	// @ jitter
	unsigned short jitter;  //87 keep[7:4], make sure[3:0]
	unsigned short tp_tail1;  //88 y2[15:8], y1[7:0]
	unsigned short tp_tail2;  //89 y2[15:8], y1[7:0]
	unsigned short dly_rpt;  //90 [15:12], add:[11:8], mask:[7:4], select[3:0]
	unsigned short skip_rpt;  //91 dis[15:0]
	unsigned short tail_cut;  //[15:10][9:5][4:0]
	// @palm rejection
	unsigned short th_palm; // 92 [15:10]num, [9:0]th
	// @grade detection

	// @border

	unsigned short th1_on_edg;   // 99 [15:8]*4:heavy,  [7:0]*4:light
	unsigned short th2_on_edg;   // 99 [15:8]*4:heavy,  [7:0]*4:light

	// @merge
	unsigned short th_mrg_ab;   // 102


	unsigned short th3_on_edg;   // 103

	// @xy-driver
	unsigned short th_grp; //[15:6] minimum group signal, [5:0] relative signal ratio to max group    
	unsigned short th_sig_xy; //79 [15:8] minimum effective signal , [7:0] touch threshold
	unsigned short th_sig_critic;   // [15:8] group, [7:0] center
	unsigned short th_sig_delta;   // [15:8] group, [7:0] center
	unsigned short th_dis_delta;   // [15:8] group, [7:0] center

	unsigned short x_up_a1;
	unsigned short x_up_b1;
	unsigned short x_up_a2;
	unsigned short x_up_b2;

	unsigned short x_dn_a1;
	unsigned short x_dn_b1;
	unsigned short x_dn_a2;
	unsigned short x_dn_b2;

	unsigned short y_tail_fix; //[0:3][4][5:8][9][10:15]
	unsigned short x_exp_left; // [15:11] rate:x/64, [10:0] expand beginning
	unsigned short x_exp_right; // [15:11] rate:x/64, [10:0] expand beginning
	unsigned short y_exp_top;
	unsigned short y_exp_bot;
	unsigned short grade_help;
	unsigned short point_stable;
	// @mdf
	unsigned short mdf_depth; //79 normally & lightly
	unsigned short fast_mov;

	//a simpler version of whole panel calibration, a 4x4 matrix
	unsigned short xcal_01;
	unsigned short xcal_23;
	unsigned short ycal_01;
	unsigned short ycal_23;    

	unsigned short edg_left_up;
	unsigned short edg_left_dn;
	unsigned short edg_right_up;
	unsigned short edg_rigth_dn;

	unsigned short corner_fix_rct;  // [15:12]
	unsigned short corner_fix_sht;  // [15:12]

	unsigned short checksum;
}ts5816_config_if;
CConfig5816::CConfig5816( unsigned short type )
:CConfig(type)
{
	current_selected = 0;
	osctrim_selected = 0;

	short_selected = 0;
	frt_selected = 0;
	iovol_selected = 0;

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
	rowsCnt = 0;
	colsCnt = 0;
	memset( ic_2_sensor_map, 0, sizeof(ic_2_sensor_map) );
	memset( sensor_2_ic_map, 0, sizeof(sensor_2_ic_map) );
	memset( cfgBinBuffer, 0, sizeof(cfgBinBuffer) );
	memset( bootBinBuffer, 0, sizeof( bootBinBuffer ) );

	memset(invalid_node, 1, sizeof(invalid_node));
}
CConfig5816::~CConfig5816()
{

}
BOOL CConfig5816::Parse( const tinyxml2::XMLDocument& xmlDoc )
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
			deep_current_min = (short)pCurrentConfig->Int64Attribute("deep_current_min");
			deep_current_max = (short)pCurrentConfig->Int64Attribute("deep_current_max");
			sleep_current_min = (short)pCurrentConfig->Int64Attribute("sleep_current_min");
			sleep_current_max = (short)pCurrentConfig->Int64Attribute("sleep_current_max");
			active_current_min = (short)pCurrentConfig->Int64Attribute("active_current_min");
			active_current_max = (short)pCurrentConfig->Int64Attribute("active_current_max");
			idle_current_min = (short)pCurrentConfig->Int64Attribute("idle_current_min");
			idle_current_max = (short)pCurrentConfig->Int64Attribute("idle_current_max");
			power_supply = (unsigned short)pCurrentConfig->Int64Attribute("power_supply");
		}
		const XMLElement* pOSCTrimConfig = pWorkStation->FirstChildElement("osctrim_test");
		if( pOSCTrimConfig )
		{
			osctrim_selected = (unsigned char)pOSCTrimConfig->Int64Attribute("selected");
			tick_32k_standard = (unsigned int)pOSCTrimConfig->Int64Attribute("tick_32k_standard");
			trim_32k_min = (unsigned char)pOSCTrimConfig->Int64Attribute("trim_32k_min");
			trim_32k_max = (unsigned char)pOSCTrimConfig->Int64Attribute("trim_32k_max");

			tick_24m_standard = (unsigned int)pOSCTrimConfig->Int64Attribute("tick_24m_standard");
			trim_24m_min = (unsigned char)pOSCTrimConfig->Int64Attribute("trim_24m_min");
			trim_24m_max = (unsigned char)pOSCTrimConfig->Int64Attribute("trim_24m_max");
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

		const XMLElement* pVihConfig = pWorkStation->FirstChildElement("vih_test");
		if( pVihConfig )
		{
			vih_selected = (unsigned char)pVihConfig->Int64Attribute("selected");
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
			vdd_low_min = (unsigned int)pIoVolConfig->Int64Attribute("vdd_low_min", 2700);
			vdd_low_max = (unsigned int)pIoVolConfig->Int64Attribute("vdd_low_max", 2900);
			vdd_high_min = (unsigned int)pIoVolConfig->Int64Attribute("vdd_high_min", 2700);
			vdd_high_max = (unsigned int)pIoVolConfig->Int64Attribute("vdd_high_max", 2900);
		}

		const XMLElement* pScapRawDataConfig = pWorkStation->FirstChildElement("scap_rawdata_test");
		if( pScapRawDataConfig )
		{
			scap_rawdata_selected = (unsigned char)pScapRawDataConfig->Int64Attribute("selected");
			unsigned short defmin = (unsigned short)pScapRawDataConfig->Int64Attribute("scap_rawdata_min");
			unsigned short defmax = (unsigned short)pScapRawDataConfig->Int64Attribute("scap_rawdata_max");
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

		const XMLElement* pMiscConfig = pWorkStation->FirstChildElement("misc_test");
		if( pMiscConfig )
		{
			misc_selected = (unsigned char)pMiscConfig->Int64Attribute("selected");
			misc_mode = (unsigned short)pMiscConfig->Int64Attribute("misc_mode");
		}

		const XMLElement* pNoiseConfig = pWorkStation->FirstChildElement("noise_test");
		if( pNoiseConfig )
		{
			noise_selected = (unsigned char)pNoiseConfig->Int64Attribute("selected");
			noise_frame = (short)pNoiseConfig->Int64Attribute("noise_frames");
			noise_max = (short)pNoiseConfig->Int64Attribute("noise_max");
		}

	}
	return bRet;
}
BOOL CConfig5816::SubParseFromConfig()
{
	BOOL parseSuccess = FALSE;
	ISMChipNodeContainer* iContainer = GetContainerInterface();
	if(NULL == iContainer) return FALSE;

	if(NULL == szCfgBinPath || NULL == szBootBinPath)
		return parseSuccess;

	TCHAR szCfgTemp[MAX_PATH] = {0};
	TCHAR szBootTemp[MAX_PATH] = {0};
	//tstring szCfgFile = tstring( CToolKit::GetExecutePath() ) + "\\" + CToolKit::UTF8ToGBK( szCfgBinPath, szCfgTemp, MAX_PATH );
	tstring szBotFile = tstring( CToolKit::GetExecutePath() ) + "/" + CToolKit::UTF8ToGBK( szBootBinPath, szBootTemp, MAX_PATH );

	tstring szCfgTest = tstring( CToolKit::GetExecutePath( 1 ) ) + "/XBin/";
	szCfgTest += iContainer->GetIcName( IcType );
	szCfgTest += "_Cfg_OnlyTest.bin";

	parseSuccess = TRUE;


	rowsCnt = 8;
	colsCnt = 8;
	// 	real_channel_num = rowsCnt * colsCnt;
	// 	va_channel_num = real_channel_num;

	try
	{
		FILE* file = NULL;
		//  		fopen_s( &file, szCfgFile.c_str(), "rb" );
		//  		if( NULL != file )
		// 		{
		// 			fseek( file, 0, SEEK_END );
		// 			cfgBinSize = ftell( file );
		// 			fseek( file, 0, SEEK_SET );
		// 			if( (cfgBinSize <= MAX_CFG_BIN_SIZE) && (cfgBinSize == fread_s( cfgBinBuffer, MAX_CFG_BIN_SIZE, 1, cfgBinSize, file )) )
		// 			{
		// 				if( CheckCfgBinFile( cfgBinBuffer, cfgBinSize ) )
		// 				{
		// 					rowsCnt = cfgBinBuffer[0x1c];
		// 					colsCnt = cfgBinBuffer[0x1b];
		// 
		// 					real_channel_num = rowsCnt * colsCnt;
		// 					va_channel_num = real_channel_num;
		// 
		// 					for( int index = 0; index < MAX_TX_NUM_5816; index++ )
		// 					{
		// 						sensor_2_ic_map[index] = cfgBinBuffer[0x90 + index];
		// 						ic_2_sensor_map[cfgBinBuffer[0x90 + index]] = index + 1;
		// 					}
		// 					for( int index = 0; index < MAX_RX_NUM_5816; index++ )
		// 					{
		// 						sensor_2_ic_map[index + MAX_TX_NUM_5816] = cfgBinBuffer[0x9c + index];
		// 						ic_2_sensor_map[cfgBinBuffer[0x9c + index] + 0] = index + MAX_TX_NUM_5816 + 1;
		// 					}
		// 
		// 					resolution_x = (cfgBinBuffer[0x07] << 8) + cfgBinBuffer[0x06];
		// 					resolution_y = (cfgBinBuffer[0x09] << 8) + cfgBinBuffer[0x08];
		// 					
		// 					//project verion
		// 					unsigned short* pV = (unsigned short*)( &cfgBinBuffer[0] );
		// // 					sVersion = pV[1] >> 10;
		// // 					pVersion = pV[0] & 0x1ff;
		// // 					vVersion = pV[0] >> 9;
		// 					sVersion = cfgBinBuffer[0x01];
		// 					pVersion = (cfgBinBuffer[0x03] << 8) + cfgBinBuffer[0x02];
		// 					vVersion = cfgBinBuffer[0x04];
		// 
		// 					parseSuccess = TRUE;
		// 				}
		// 			}
		// 			fclose( file );
		// 		}

		fopen_s( &file, szBotFile.c_str(), "rb" );
		if( NULL != file )
		{
			fseek( file, 0, SEEK_END );
			bootBinSize = ftell( file );
			fseek( file, 0, SEEK_SET );
			if( (bootBinSize <= MAX_BOT_BIN_SIZE) && (bootBinSize == fread_s( bootBinBuffer, MAX_BOT_BIN_SIZE, 1, bootBinSize, file )) )
			{
				unsigned short cfgAddr = (bootBinBuffer[0x39] << 8) + bootBinBuffer[0x38];

				if( CheckCfgBinFile( bootBinBuffer + cfgAddr, 256 ) )
				{
					//gen burn time
					//SYSTEMTIME SysTime;
					//unsigned int* pIntData = (unsigned int*)&bootBinBuffer[bootBinSize];
					//::GetLocalTime(&SysTime);
					//pIntData[0] = (SysTime.wMonth << 22) + (SysTime.wDay << 17) + (SysTime.wHour << 12) + (SysTime.wMinute << 6) + SysTime.wSecond;
						
					memcpy_s( cfgBinBuffer, sizeof(cfgBinBuffer), bootBinBuffer + cfgAddr, 256 );
					rowsCnt = cfgBinBuffer[0x1c];
					colsCnt = cfgBinBuffer[0x1b];

					real_channel_num = rowsCnt * colsCnt;
					va_channel_num = real_channel_num;

					vid_pid = *((UINT64*)(cfgBinBuffer + 1));
					vid_pid = vid_pid & 0x000000ffffffffff;

					for( int index = 0; index < colsCnt/*MAX_TX_NUM_5816*/; index++ )
					{
						sensor_2_ic_map[index] = cfgBinBuffer[0x90 + index];
						ic_2_sensor_map[cfgBinBuffer[0x90 + index]] = index + 1;
					}
					for( int index = 0; index < rowsCnt/*MAX_RX_NUM_5816*/; index++ )
					{
						sensor_2_ic_map[index + MAX_TX_NUM_5816] = cfgBinBuffer[0x9c + index];
						ic_2_sensor_map[cfgBinBuffer[0x9c + index] + 0] = index + MAX_TX_NUM_5816 + 1;
					}

					resolution_x = (cfgBinBuffer[0x07] << 8) + cfgBinBuffer[0x06];
					resolution_y = (cfgBinBuffer[0x09] << 8) + cfgBinBuffer[0x08];

					//project verion
					unsigned short* pV = (unsigned short*)( &cfgBinBuffer[0] );
					// 					sVersion = pV[1] >> 10;
					// 					pVersion = pV[0] & 0x1ff;
					// 					vVersion = pV[0] >> 9;
					sVersion = cfgBinBuffer[0x01];
					pVersion = (cfgBinBuffer[0x03] << 8) + cfgBinBuffer[0x02];
					vVersion = (cfgBinBuffer[0x05] << 8) + cfgBinBuffer[0x04];

                    Set_Key_Num = key_setting_num = 1;//Temporarily fixed
                    keyarray[0][0] = 40;
                    keyarray[0][1] = 1000;
				}
				else
				{
					parseSuccess = FALSE;
				}
				fclose( file );
			}
		}

		const unsigned short cfg_len_5816 = 256;
		fopen_s( &file, szCfgTest.c_str(), "rb" );
		if( NULL != file )
		{
			fseek( file, 0, SEEK_END );
			int length = ftell( file );
			fseek( file, 0, SEEK_SET );
			if(length > MAX_CFG_BIN_SIZE)
			{
				fread_s( cfgTestBinBuffer, MAX_CFG_BIN_SIZE, 1, MAX_CFG_BIN_SIZE, file );
			}
			unsigned short cfgAddr = (cfgTestBinBuffer[0x39] << 8) + cfgTestBinBuffer[0x38];
			fseek( file, cfgAddr, SEEK_SET );
			if( (cfgAddr <= length) && (cfg_len_5816 == fread_s( cfgTestBinBuffer, MAX_CFG_BIN_SIZE, 1, cfg_len_5816, file )) )
			{
				if( CheckCfgBinFile( cfgTestBinBuffer, cfg_len_5816 ) )
				{
					cfgTestBinSize = cfg_len_5816;
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