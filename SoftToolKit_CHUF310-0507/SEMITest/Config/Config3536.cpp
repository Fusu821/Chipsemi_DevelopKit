#include "framework.h"
#include "Config3536.h"
#include "checksum.h"
#include "../TestSrc/ToolKit.h"
REGIST_RUNTIME_CLASS_USHORT(CONFIG_TYPE, (CONFIG_TYPE)SEMI_IC_3536, CConfig3536)

typedef CConfig3536  CConfig6440;
REGIST_RUNTIME_CLASS_USHORT(CONFIG_TYPE, (CONFIG_TYPE)SEMI_IC_6440, CConfig6440)
typedef CConfig3536  CConfig6448;
REGIST_RUNTIME_CLASS_USHORT(CONFIG_TYPE, (CONFIG_TYPE)SEMI_IC_6448, CConfig6448)
typedef CConfig3536  CConfig6413;
REGIST_RUNTIME_CLASS_USHORT(CONFIG_TYPE, (CONFIG_TYPE)SEMI_IC_6413, CConfig6413)
typedef CConfig3536  CConfig6417;
REGIST_RUNTIME_CLASS_USHORT(CONFIG_TYPE, (CONFIG_TYPE)SEMI_IC_6417, CConfig6417)
typedef CConfig3536  CConfig6540;
REGIST_RUNTIME_CLASS_USHORT(CONFIG_TYPE, (CONFIG_TYPE)SEMI_IC_6540, CConfig6540)
typedef CConfig3536  CConfig6545;
REGIST_RUNTIME_CLASS_USHORT(CONFIG_TYPE, (CONFIG_TYPE)SEMI_IC_6545, CConfig6545)
typedef CConfig3536  CConfig6410;
REGIST_RUNTIME_CLASS_USHORT(CONFIG_TYPE, (CONFIG_TYPE)SEMI_IC_6410, CConfig6410)
typedef CConfig3536  CConfig6430;
REGIST_RUNTIME_CLASS_USHORT(CONFIG_TYPE, (CONFIG_TYPE)SEMI_IC_6430, CConfig6430)
typedef CConfig3536  CConfig6448S;
REGIST_RUNTIME_CLASS_USHORT(CONFIG_TYPE, (CONFIG_TYPE)SEMI_IC_6448S, CConfig6448S)

typedef struct __ts3536_config_if
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
}ts3536_config_if;
CConfig3536::CConfig3536( unsigned short type )
:CConfig(type)
{
	current_selected = 0;
	memset( fsd.fsd_base, 0, sizeof(fsd.fsd_base) );
	memset( fsd.fsd_fast, 0, sizeof(fsd.fsd_fast) );
	memset( fsd.fsd_slow, 0, sizeof(fsd.fsd_slow) );
	memset( fsd.fsd_deviation, 0, sizeof(fsd.fsd_deviation) );
	memset( fsd.fsd_delta_max, 0, sizeof(fsd.fsd_delta_max) );
	memset( fsd.fsd_uniformity_left, 0, sizeof(fsd.fsd_uniformity_left) );
	memset( fsd.fsd_uniformity_right, 0, sizeof(fsd.fsd_uniformity_right) );

	os_selected = 0;
	integral = 0;
	scale_a = 0;
	scale_b = 0;
	memset( os_base, 0, sizeof(os_base) );

	rawdata_selected = 0;

	noise_selected = 0;

	va_channel_num = 0;
	harf_va_channel_num = 0;
	//key_num = 0;
	//all_channel_num =0;
	cfgBinSize = 0;
	bootBinSize = 0;
	rowsCnt = 0;
	colsCnt = 0;
	memset( ic_2_sensor_map, 0, sizeof(ic_2_sensor_map) );
	memset( sensor_2_ic_map, 0, sizeof(sensor_2_ic_map) );
	memset( cfgBinBuffer, 0, sizeof(cfgBinBuffer) );
	memset( bootBinBuffer, 0, sizeof( bootBinBuffer ) );

	for( int iRow = 0; iRow < MAX_SCAP_ROW; iRow++ )
	{
		for( int iCol = 0; iCol < MAX_SCAP_COL; iCol++ )
		{
			invalid_node[iRow][iCol] = 1;
		}
	}
	//memset( invalid_node, 0, sizeof(invalid_node) );
}
CConfig3536::~CConfig3536()
{

}
BOOL CConfig3536::Parse( const tinyxml2::XMLDocument& xmlDoc )
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
			work_current_min = (short)pCurrentConfig->Int64Attribute("work_current_min");
			work_current_max = (short)pCurrentConfig->Int64Attribute("work_current_max");
			sleep_current_min = (short)pCurrentConfig->Int64Attribute("sleep_current_min");
			sleep_current_max = (short)pCurrentConfig->Int64Attribute("sleep_current_max");
			delta_current_min = (short)pCurrentConfig->Int64Attribute("delta_current_min");
			delta_current_max = (short)pCurrentConfig->Int64Attribute("delta_current_max");
			active_current_min = (short)pCurrentConfig->Int64Attribute("active_current_min");
			active_current_max = (short)pCurrentConfig->Int64Attribute("active_current_max");
		}
		//FSD test
		fsd.fsdT.fsd_selected = 0;
		const XMLElement* pFSDConfig = pWorkStation->FirstChildElement("fsd_test");
		if( pFSDConfig && pFSDConfig->Int64Attribute("selected") )
		{
			fsd.fsdT.fsd_selected = (unsigned char)pFSDConfig->Int64Attribute("selected");
			fsd.fsdT.f_clk = (unsigned short)pFSDConfig->Int64Attribute("f_clk");
			fsd.fsdT.s_clk = (unsigned short)pFSDConfig->Int64Attribute("s_clk");
			fsd.fsdT.cmp_max = (unsigned short)pFSDConfig->Int64Attribute("cmp_max");
			fsd.fsdT.fsd_min = (int)pFSDConfig->Int64Attribute("fsd_min", 10);
			fsd.fsdT.fsd_recheck = (unsigned char)pFSDConfig->Int64Attribute("recheck");
			fsd.fsdT.fsd_triger_min = (short)pFSDConfig->Int64Attribute("triger_min");
			fsd.fsdT.fsd_triger_max = (short)pFSDConfig->Int64Attribute("triger_max");
			fsd.fsdT.fsd_critical_slow_min = (short)pFSDConfig->Int64Attribute("slow_critical_min");
			fsd.fsdT.fsd_critical_slow_max = (short)pFSDConfig->Int64Attribute("slow_critical_max");
			fsd.fsdT.fsd_besides_min = (short)pFSDConfig->Int64Attribute("fsd_besides_min");
			fsd.fsdT.fsd_critical_fast_max = (short)pFSDConfig->Int64Attribute("fast_critical_max");
			fsd.fsdT.fsd_plus_check = (unsigned char)pFSDConfig->Int64Attribute("pluscheck");
			fsd.fsdT.fsd_plus_t1 = (short)pFSDConfig->Int64Attribute("fsd_t1");
			fsd.fsdT.fsd_plus_t2 = (short)pFSDConfig->Int64Attribute("fsd_t2");
			fsd.fsdT.fsd_plus_t3 = (short)pFSDConfig->Int64Attribute("fsd_t3");
			fsd.fsdT.fsd_plus_t4 = (short)pFSDConfig->Int64Attribute("fsd_t4");
			fsd.fsdT.fb_check = (unsigned char)pFSDConfig->Int64Attribute("fbcheck");
			fsd.fsdT.fb_base = (short)pFSDConfig->Int64Attribute("fb_base");
			fsd.fsdT.fb_min = (short)pFSDConfig->Int64Attribute("fb_min");
			fsd.fsdT.fb_max = (short)pFSDConfig->Int64Attribute("fb_max");
			fsd.fsdT.scale_check = (unsigned char)pFSDConfig->Int64Attribute("scale_check", 1);
			fsd.fsdT.integral = (unsigned char)pFSDConfig->Int64Attribute("integral", 1);

			ParseDetailData( pFSDConfig, "fsd_base", fsd.fsd_base, rowsCnt, colsCnt );
			ParseDetailData( pFSDConfig, "fsd_fast", fsd.fsd_fast, rowsCnt, colsCnt );
			ParseDetailData( pFSDConfig, "fsd_slow", fsd.fsd_slow, rowsCnt, colsCnt );
			ParseDetailData( pFSDConfig, "fsd_delta_max", fsd.fsd_delta_max, rowsCnt, colsCnt );
			//ParseDetailData( pFSDConfig, "fsd_delta_max", fsd.fsd_delta_max, rowsCnt + 1, colsCnt );
			ParseDetailData( pFSDConfig, "fsd_uniformity_left", fsd.fsd_uniformity_left, rowsCnt, colsCnt );
			ParseDetailData( pFSDConfig, "fsd_uniformity_right", fsd.fsd_uniformity_right, rowsCnt, colsCnt );
			ParseDetailData( pFSDConfig, "fsd_deviation", fsd.fsd_deviation, rowsCnt, colsCnt );	
		}	
		//FSDBK test
		fsd.fsdB.fsd_selected = 0;
		const XMLElement* pFSDBKConfig = pWorkStation->FirstChildElement("fsdbk_test");
		if( pFSDBKConfig && pFSDBKConfig->Int64Attribute("selected") )
		{
			fsd.fsdB.fsd_selected = (unsigned char)pFSDBKConfig->Int64Attribute("selected");
			fsd.fsdB.f_clk = (unsigned short)pFSDBKConfig->Int64Attribute("f_clk");
			fsd.fsdB.s_clk = (unsigned short)pFSDBKConfig->Int64Attribute("s_clk");
			fsd.fsdB.fsd_min = (int)pFSDBKConfig->Int64Attribute("fsd_min", 10);
			fsd.fsdB.fsd_recheck = (unsigned char)pFSDBKConfig->Int64Attribute("recheck");
			fsd.fsdB.fsd_triger_min = (short)pFSDBKConfig->Int64Attribute("triger_min");
			fsd.fsdB.fsd_triger_max = (short)pFSDBKConfig->Int64Attribute("triger_max");
			fsd.fsdB.fsd_critical_slow_min = (short)pFSDBKConfig->Int64Attribute("slow_critical_min");
			fsd.fsdB.fsd_critical_slow_max = (short)pFSDBKConfig->Int64Attribute("slow_critical_max");
			fsd.fsdB.fsd_besides_min = (short)pFSDBKConfig->Int64Attribute("fsd_besides_min");
			fsd.fsdB.fsd_critical_fast_max = (short)pFSDBKConfig->Int64Attribute("fast_critical_max");
			fsd.fsdB.fb_check = (unsigned char)pFSDBKConfig->Int64Attribute("fbcheck");
			fsd.fsdB.fb_base = (short)pFSDBKConfig->Int64Attribute("fb_base");
			fsd.fsdB.fb_min = (short)pFSDBKConfig->Int64Attribute("fb_min");
			fsd.fsdB.fb_max = (short)pFSDBKConfig->Int64Attribute("fb_max");
			fsd.fsdB.scale_check = (unsigned char)pFSDBKConfig->Int64Attribute("scale_check", 1);
			fsd.fsdB.integral = (unsigned char)pFSDBKConfig->Int64Attribute("integral", 1);

			ParseDetailData( pFSDBKConfig, "fsd_base", fsd.fsd_base, rowsCnt + 1, colsCnt );
			ParseDetailData( pFSDBKConfig, "fsd_fast", fsd.fsd_fast, rowsCnt + 1, colsCnt );
			ParseDetailData( pFSDBKConfig, "fsd_slow", fsd.fsd_slow, rowsCnt + 1, colsCnt );
			ParseDetailData( pFSDBKConfig, "fsd_delta_max", fsd.fsd_delta_max, rowsCnt + 1, colsCnt );
			//ParseDetailData( pFSDBKConfig, "fsd_delta_max", fsd.fsd_delta_max, rowsCnt + 1, colsCnt );
			ParseDetailData( pFSDBKConfig, "fsd_uniformity_left", fsd.fsd_uniformity_left, rowsCnt, colsCnt );
			ParseDetailData( pFSDBKConfig, "fsd_uniformity_right", fsd.fsd_uniformity_right, rowsCnt, colsCnt );
			ParseDetailData( pFSDBKConfig, "fsd_deviation", fsd.fsd_deviation, rowsCnt + 1, colsCnt );	
		}	
		const XMLElement* pOSConfig = pWorkStation->FirstChildElement("os_test");
		if( pOSConfig )
		{
			os_selected = (unsigned char)pOSConfig->Int64Attribute("selected");
			integral = (unsigned char)pOSConfig->Int64Attribute("integral");
			scale_a = (unsigned char)pOSConfig->Int64Attribute("scale_a");
			scale_b = (unsigned char)pOSConfig->Int64Attribute("scale_b");
			os_clk = (unsigned short)pOSConfig->Int64Attribute("os_clk", 0x6302);
			m2_ratio = (unsigned char)pOSConfig->Int64Attribute("m2_ratio");
			m1_ratio_upper_va = (unsigned char)pOSConfig->Int64Attribute("m1_ratio_upper_va");
			m1_ratio_lower_va = (unsigned char)pOSConfig->Int64Attribute("m1_ratio_lower_va");
			m1_ratio_upper_ref = (unsigned char)pOSConfig->Int64Attribute("m1_ratio_upper_ref");
			m1_ratio_lower_ref = (unsigned char)pOSConfig->Int64Attribute("m1_ratio_lower_ref");
			m3_delta_va_max = (int)pOSConfig->Int64Attribute("m3_delta_va_max");
			m3_delta_ref_max = (int)pOSConfig->Int64Attribute("m3_delta_ref_max");
			m3_delta_level1 = (int)pOSConfig->Int64Attribute("m3_delta_level1");
			m3_delta_level2 = (int)pOSConfig->Int64Attribute("m3_delta_level2");

			unsigned short addRow = (real_channel_num > rowsCnt * colsCnt) ? 1 : 0;
			ParseDetailData( pOSConfig, "os_base",  os_base, rowsCnt + addRow, colsCnt );
		}
		const XMLElement* pOSCTrimConfig = pWorkStation->FirstChildElement("osctrim_test");
		if( pOSCTrimConfig )
		{
			osctrim_selected = (unsigned char)pOSCTrimConfig->Int64Attribute("selected");
			tick_standard = (unsigned int)pOSCTrimConfig->Int64Attribute("tick_standard");
			osctrim_min = (unsigned char)pOSCTrimConfig->Int64Attribute("osctrim_min");
			osctrim_max = (unsigned char)pOSCTrimConfig->Int64Attribute("osctrim_max");
			offset_tick = (unsigned int)pOSCTrimConfig->Int64Attribute("offset_tick");
            must_test = (unsigned int)pOSCTrimConfig->Int64Attribute("must_test");
		}
		const XMLElement* pRawDataConfig = pWorkStation->FirstChildElement("rawdata_test");
		if( pRawDataConfig )
		{
			unsigned short addRow = (real_channel_num > rowsCnt * colsCnt) ? 1 : 0;
			rawdata_selected = (unsigned char)pRawDataConfig->Int64Attribute("selected");
			unsigned short defmin = (unsigned short)pRawDataConfig->Int64Attribute("rawdata_min");
			unsigned short defmax = (unsigned short)pRawDataConfig->Int64Attribute("rawdata_max");
			ParseDetailData( pRawDataConfig, "rawdata_min", rawdata_min, rowsCnt + addRow, colsCnt, defmin );
			ParseDetailData( pRawDataConfig, "rawdata_max", rawdata_max, rowsCnt + addRow, colsCnt, defmax );
		}
		const XMLElement* noiseConfig = pWorkStation->FirstChildElement("noise_test");
		if( noiseConfig )
		{
			noise_selected = (unsigned char)noiseConfig->Int64Attribute("selected");
			noise_max = (signed short)noiseConfig->Int64Attribute("noise_max");
			noise_frame = (signed short)noiseConfig->Int64Attribute("noise_frame");
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
			//int_low = (unsigned int)pIoVolConfig->Int64Attribute("int_low", 500);
			//int_high = (unsigned int)pIoVolConfig->Int64Attribute("int_high", 1650);
			//iic_low = (unsigned int)pIoVolConfig->Int64Attribute("iic_low", 500);
			//iic_high = (unsigned int)pIoVolConfig->Int64Attribute("iic_high", 1650);
		}
		const XMLElement* pVpConfig = pWorkStation->FirstChildElement("vp_test");
		if( pVpConfig )
		{
			vp_selected = (unsigned char)pVpConfig->Int64Attribute("selected");
			vp_trigger = (signed int)pVpConfig->Int64Attribute("vp_trigger");
			vp_min = (signed int)pVpConfig->Int64Attribute("vp_min");
			vp_out_time = (signed int)pVpConfig->Int64Attribute("vp_out_time",15);
		}
		const XMLElement* pAlgorithmConfig = pWorkStation->FirstChildElement("algorithm_test");
		if( pAlgorithmConfig )
		{
			algorithm_selected = (unsigned char)pAlgorithmConfig->Int64Attribute("selected");
		}

		const XMLElement* pMiscConfig = pWorkStation->FirstChildElement("misc_test");
		if( pMiscConfig )
		{
			misc_selected = (unsigned char)pMiscConfig->Int64Attribute("selected");
		}
	}
	return bRet;
}
BOOL CConfig3536::SubParseFromConfig()
{
	BOOL parseSuccess = FALSE;

	if(NULL == szCfgBinPath || NULL == szBootBinPath)
		return parseSuccess;

	TCHAR szCfgTemp[MAX_PATH] = {0};
	TCHAR szBootTemp[MAX_PATH] = {0};
	tstring szCfgFile = tstring( CToolKit::GetExecutePath() ) + "/" + CToolKit::UTF8ToGBK( szCfgBinPath, szCfgTemp, MAX_PATH );
	tstring szBotFile = tstring( CToolKit::GetExecutePath() ) + "/" + CToolKit::UTF8ToGBK( szBootBinPath, szBootTemp, MAX_PATH );

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
					ts3536_config_if* pCfg3536 = (ts3536_config_if*)cfgBinBuffer;
					sensor_type = (cfgBinBuffer[0x6B] >> 4);
					va_channel_num = ( ( *ps ) >> 4 ) & 0x3f;
					//				va_channel_num = va_channel_num >> 1;
					// 				if( *ps & 0x08 )
					// 				{
					// 					harf_va_channel_num = va_channel_num >> 1;
					// 				}
					harf_va_channel_num = va_channel_num >> 1;
					real_channel_num = ( pCfg3536->tp_chain >> 10 );
					key_setting_num = pCfg3536->tp_chain & 0x07;
					if( real_channel_num - va_channel_num > key_setting_num )
						key_setting_num = real_channel_num - va_channel_num;

					for( int index = 0; index < MAX_SCAP_CHANNEL; index++ )
					{
						ic_2_sensor_map[index] = cfgBinBuffer[22 + index];
						if( ic_2_sensor_map[index] )
						{
							sensor_2_ic_map[ic_2_sensor_map[index] - 1] = index;
						}
					}

					if( pCfg3536->tp_chain & 0x8 )
					{
						//rowsCnt = 4;
						//colsCnt = ( (pCfg3536->tp_chain >> 10) & 0x3f ) >> 2;
						bVerticalTriangle = 1;
					}
					else
					{
						//rowsCnt = 2;
						//colsCnt = ( (pCfg3536->tp_chain >> 4) & 0x3f ) >> 1;
						bVerticalTriangle = 0;
					}

					//if(7 == sensor_type)  // huawei 6 * 6//菱形搭桥在按键取消
					//{
					//	//rowsCnt = 6;
					//	//colsCnt = 6;
					//	va_channel_num = real_channel_num;
					//	key_setting_num = 0;
					//}

					//fix
					if( real_channel_num >= rowsCnt * colsCnt )
					{
						//key_setting_num = real_channel_num - rowsCnt * colsCnt;
						va_channel_num = rowsCnt * colsCnt;
						harf_va_channel_num = rowsCnt * colsCnt >> 1;
					}

// 					if( sensor_circle_9_8 == sensor_type )
// 					{
// 						rowsCnt = 4;
// 						colsCnt = 4;
// 						va_channel_num = real_channel_num - 1;
// 						//va_channel_num = real_channel_num - 1;
// 					}

					//resolution x y key
					unsigned short misc = ( cfgBinBuffer[57 * 2 + 1] << 8 ) + cfgBinBuffer[57 * 2 + 0];
					if( misc & 0x08 )
					{
						resolution_x = ( cfgBinBuffer[39 * 2 + 1] << 8 ) + cfgBinBuffer[39 * 2 + 0];
						resolution_y = ( cfgBinBuffer[38 * 2 + 1] << 8 ) + cfgBinBuffer[38 * 2 + 0];
					}
					else
					{
						resolution_x = ( cfgBinBuffer[38 * 2 + 1] << 8 ) + cfgBinBuffer[38 * 2 + 0];
						resolution_y = ( cfgBinBuffer[39 * 2 + 1] << 8 ) + cfgBinBuffer[39 * 2 + 0];
					}

					Set_Key_Num = key_setting_num;
					if(Set_Key_Num>4)
					{
						int key_y = ( cfgBinBuffer[44 * 2 + 1] << 8 ) + cfgBinBuffer[44 * 2 + 0];
						for(int i=0;i<Set_Key_Num;i++)
						{
						  keyarray[i][0]=i+1;
						  keyarray[i][1]=key_y;
						}					
					}
					//if(Set_Key_Num > 15)
					//{
					//	Key1_x = 1;
					//	Key2_x = 2;
					//	Key3_x = 3;
					//	Key4_x = 4;
					//	Key5_x = 5;
					//	Key6_x = 6;
					//	Key7_x = 7;
					//	Key8_x = 8;
					//	Key9_x = 9;
					//	Key10_x = 10;
					//	Key11_x = 11;
					//	Key12_x = 12;
					//	Key13_x = 13;
					//	Key14_x = 14;
					//	Key15_x = 15;
					//	Key16_x = 16;
					//	Key17_x = 17;
					//	Key18_x = 18;
					//	Key19_x = 19;
					//	Key20_x = 20;
					//	Key21_x = 21;
					//	Key22_x = 22;
					//	Key23_x = 23;
					//	Key24_x = 24;
					//	Key1_y = ( cfgBinBuffer[44 * 2 + 1] << 8 ) + cfgBinBuffer[44 * 2 + 0];
					//	Key16_y = Key17_y = Key18_y = Key19_y = Key20_y = Key21_y = Key22_y = Key23_y = Key24_y = Key1_y;
					//	Key2_y = Key3_y = Key4_y = Key5_y = Key6_y = Key7_y = Key8_y = Key9_y = Key10_y = Key11_y = Key12_y = Key13_y = Key14_y = Key15_y = Key1_y;
					//}
					//else if( Set_Key_Num > 4 )
					//{
					//	Key1_x = cfgBinBuffer[40 * 2 + 0] & 0x0f;
					//	Key2_x = ( cfgBinBuffer[40 * 2 + 0] & 0xf0 ) >> 4;
					//	Key3_x = cfgBinBuffer[40 * 2 + 1] & 0x0f;
					//	Key4_x = ( cfgBinBuffer[40 * 2 + 1] & 0xf0 ) >> 4;
					//	Key5_x = cfgBinBuffer[41 * 2 + 0] & 0x0f;
					//	Key6_x = ( cfgBinBuffer[41 * 2 + 0] & 0xf0 ) >> 4;
					//	Key7_x = cfgBinBuffer[41 * 2 + 1] & 0x0f;
					//	Key8_x = ( cfgBinBuffer[41 * 2 + 1] & 0xf0 ) >> 4;
					//	Key9_x = cfgBinBuffer[42 * 2 + 0] & 0x0f;
					//	Key10_x = ( cfgBinBuffer[42 * 2 + 0] & 0xf0 ) >> 4;
					//	Key11_x = cfgBinBuffer[42 * 2 + 1] & 0x0f;
					//	Key12_x = ( cfgBinBuffer[42 * 2 + 1] & 0xf0 ) >> 4;
					//	Key13_x = cfgBinBuffer[43 * 2 + 0] & 0x0f;
					//	Key14_x = ( cfgBinBuffer[43 * 2 + 0] & 0xf0 ) >> 4;
					//	Key15_x = cfgBinBuffer[43 * 2 + 1] & 0x0f;

					//	Key1_y = ( cfgBinBuffer[44 * 2 + 1] << 8 ) + cfgBinBuffer[44 * 2 + 0];
					//	Key2_y = Key3_y = Key4_y = Key5_y = Key6_y = Key7_y = Key8_y = Key9_y = Key10_y = Key11_y = Key12_y = Key13_y = Key14_y = Key15_y = Key1_y;

					//	if( Set_Key_Num > 15 )
					//	{
					//		Key16_x = 16;
					//		Key17_x = 17;
					//		Key18_x = 18;
					//		Key19_x = 19;
					//		Key20_x = 20;
					//		Key21_x = 21;
					//		Key22_x = 22;
					//		Key23_x = 23;
					//		Key24_x = 24;
					//		Key16_y = Key17_y = Key18_y = Key19_y = Key20_y = Key21_y = Key22_y = Key23_y = Key24_y = Key1_y;
					//	}
					//}
					else
					{
						/*Key1_x = ( cfgBinBuffer[40 * 2 + 1] << 8 ) + cfgBinBuffer[40 * 2 + 0];
						Key2_x = ( cfgBinBuffer[41 * 2 + 1] << 8 ) + cfgBinBuffer[41 * 2 + 0];
						Key3_x = ( cfgBinBuffer[42 * 2 + 1] << 8 ) + cfgBinBuffer[42 * 2 + 0];
						Key4_x = ( cfgBinBuffer[43 * 2 + 1] << 8 ) + cfgBinBuffer[43 * 2 + 0];
						Key1_y = ( cfgBinBuffer[44 * 2 + 1] << 8 ) + cfgBinBuffer[44 * 2 + 0];
						Key2_y = Key3_y = Key4_y = Key1_y;*/

						int Key_y=( cfgBinBuffer[44 * 2 + 1] << 8 ) + cfgBinBuffer[44 * 2 + 0];
						keyarray[0][0] = ( cfgBinBuffer[40 * 2 + 1] << 8 ) + cfgBinBuffer[40 * 2 + 0];
						keyarray[0][1] = Key_y;
						keyarray[1][0] = ( cfgBinBuffer[41 * 2 + 1] << 8 ) + cfgBinBuffer[41 * 2 + 0];
						keyarray[1][1] = Key_y;
						keyarray[2][0] = ( cfgBinBuffer[42 * 2 + 1] << 8 ) + cfgBinBuffer[42 * 2 + 0];
						keyarray[2][1] = Key_y;
						keyarray[3][0] = ( cfgBinBuffer[43 * 2 + 1] << 8 ) + cfgBinBuffer[43 * 2 + 0];
						keyarray[3][1] = Key_y;			
					}

					//project verion
					unsigned short* pV = (unsigned short*)( &cfgBinBuffer[0] );
					sVersion = pV[1] >> 10;
					pVersion = (((pV[1] >> 4) & 0x03) << 9) | (pV[0] & 0x1ff);
					vVersion = (((pV[1] >> 6) & 0x03) << 7) | (pV[0] >> 9);

					vid_pid = (vVersion << 24) | (pVersion << 8) | sVersion;

					parseSuccess = TRUE;
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
				//add check sum 
				unsigned int buildCheck = caculate_check_sum_ex( bootBinBuffer, bootBinSize );
				bootBinBuffer[bootBinSize++] = (unsigned char)buildCheck;
				bootBinBuffer[bootBinSize++] = (unsigned char)(buildCheck>>8);
				bootBinBuffer[bootBinSize++] = (unsigned char)(buildCheck>>16);
				bootBinBuffer[bootBinSize++] = (unsigned char)(buildCheck>>24);
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