#include "framework.h"
#include "Config3535.h"
#include "checksum.h"
#include "../TestSrc/ToolKit.h"

REGIST_RUNTIME_CLASS_USHORT(CONFIG_TYPE, (CONFIG_TYPE)SEMI_IC_3535, CConfig3535)

typedef struct __ts3535_config_if
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
}ts3535_config_if;
CConfig3535::CConfig3535( unsigned short type )
:CConfig(type)
{
	fsd_selected = 0;
	current_selected = 0;
	f_clk = 0;
	s_clk = 0;
	cmp_max = 0;
	memset( fsd_base, 0, sizeof(fsd_base) );
	memset( fsd_fast, 0, sizeof(fsd_fast) );
	memset( fsd_slow, 0, sizeof(fsd_slow) );
	memset( fsd_deviation, 0, sizeof(fsd_deviation) );
	memset( fsd_delta_max, 0, sizeof(fsd_delta_max) );
	memset( fsd_uniformity_left, 0, sizeof(fsd_uniformity_left) );
	memset( fsd_uniformity_right, 0, sizeof(fsd_uniformity_right) );

	os_selected = 0;
	integral = 0;
	scale_a = 0;
	scale_b = 0;
	memset( os_base, 0, sizeof(os_base) );

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
CConfig3535::~CConfig3535()
{

}
BOOL CConfig3535::Parse( const tinyxml2::XMLDocument& xmlDoc )
{
	BOOL bRet = CConfig::Parse( xmlDoc );
	const tinyxml2::XMLElement* pWorkStation = xmlDoc.RootElement()->FirstChildElement(szWorkStation);
	if( !pWorkStation )   return ERROR_CODE_INVALID_FILE;
	if( bRet )
	{
		const tinyxml2::XMLElement* pCurrentConfig = pWorkStation->FirstChildElement("current_test");
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
		const XMLElement* pFSDConfig = pWorkStation->FirstChildElement("fsd_test");
		if( pFSDConfig )
		{
			fsd_selected = (unsigned char)pFSDConfig->Int64Attribute("selected");
			f_clk = (unsigned short)pFSDConfig->Int64Attribute("f_clk");
			s_clk = (unsigned short)pFSDConfig->Int64Attribute("s_clk");
			cmp_max = (unsigned short)pFSDConfig->Int64Attribute("cmp_max");
			fsd_min = (int)pFSDConfig->Int64Attribute("fsd_min", 10);
			fsd_recheck = (unsigned char)pFSDConfig->Int64Attribute("recheck");
			fsd_triger_min = (short)pFSDConfig->Int64Attribute("triger_min");
			fsd_triger_max = (short)pFSDConfig->Int64Attribute("triger_max");
			fsd_critical_slow_min = (short)pFSDConfig->Int64Attribute("slow_critical_min");
			fsd_critical_slow_max = (short)pFSDConfig->Int64Attribute("slow_critical_max");
			fsd_besides_min = (short)pFSDConfig->Int64Attribute("fsd_besides_min", 5);
			fsd_critical_fast_max = (short)pFSDConfig->Int64Attribute("fast_critical_max");
			fsd_plus_check = (unsigned char)pFSDConfig->Int64Attribute("pluscheck");
			fsd_plus_t1 = (short)pFSDConfig->Int64Attribute("fsd_t1");
			fsd_plus_t2 = (short)pFSDConfig->Int64Attribute("fsd_t2");
			fsd_plus_t3 = (short)pFSDConfig->Int64Attribute("fsd_t3");
			fsd_plus_t4 = (short)pFSDConfig->Int64Attribute("fsd_t4");

			ParseDetailData( pFSDConfig, "fsd_base", fsd_base, rowsCnt, colsCnt );
			ParseDetailData( pFSDConfig, "fsd_fast", fsd_fast, rowsCnt, colsCnt );
			ParseDetailData( pFSDConfig, "fsd_slow", fsd_slow, rowsCnt, colsCnt );
			ParseDetailData( pFSDConfig, "fsd_delta_max", fsd_delta_max, rowsCnt, colsCnt );
			ParseDetailData( pFSDConfig, "fsd_delta_max", fsd_delta_max, rowsCnt, colsCnt );
			ParseDetailData( pFSDConfig, "fsd_uniformity_left", fsd_uniformity_left, rowsCnt, colsCnt );
			ParseDetailData( pFSDConfig, "fsd_uniformity_right", fsd_uniformity_right, rowsCnt, colsCnt );
			ParseDetailData( pFSDConfig, "fsd_deviation", fsd_deviation, rowsCnt, colsCnt );	
		}	
		const XMLElement* pOSConfig = pWorkStation->FirstChildElement("os_test");
		if( pOSConfig )
		{
			os_selected = (unsigned char)pOSConfig->Int64Attribute("selected");
			integral = (unsigned char)pOSConfig->Int64Attribute("integral");
			scale_a = (unsigned char)pOSConfig->Int64Attribute("scale_a");
			scale_b = (unsigned char)pOSConfig->Int64Attribute("scale_b");
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
		const XMLElement* pBaseConfig = pWorkStation->FirstChildElement("base_test");
		if( pBaseConfig )
		{
			base_selected = (unsigned char)pBaseConfig->Int64Attribute("selected");
			base_min = (signed short)pBaseConfig->Int64Attribute("base_min");
			base_max = (signed short)pBaseConfig->Int64Attribute("base_max");
		}
	}
	return bRet;
}
BOOL CConfig3535::SubParseFromConfig()
{
	BOOL parseSuccess = FALSE;

	if(NULL == szCfgBinPath || NULL == szBootBinPath)
		return parseSuccess;

	TCHAR szCfgTemp[MAX_PATH] = {0};
	TCHAR szBootTemp[MAX_PATH] = {0};
	tstring szCfgFile = tstring( CToolKit::GetExecutePath() ) + "\\" + CToolKit::UTF8ToGBK( szCfgBinPath, szCfgTemp, MAX_PATH );
	tstring szBotFile = tstring( CToolKit::GetExecutePath() ) + "\\" + CToolKit::UTF8ToGBK( szBootBinPath, szBootTemp, MAX_PATH );

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
					ts3535_config_if* pCfg3535 = (ts3535_config_if*)cfgBinBuffer;
					va_channel_num = ( ( *ps ) >> 4 ) & 0x3f;
					//				va_channel_num = va_channel_num >> 1;
					// 				if( *ps & 0x08 )
					// 				{
					// 					harf_va_channel_num = va_channel_num >> 1;
					// 				}
					harf_va_channel_num = va_channel_num >> 1;
					real_channel_num = ( pCfg3535->tp_chain >> 10 );
					key_setting_num = pCfg3535->tp_chain & 0x07;
					if( real_channel_num - va_channel_num > key_setting_num )
						key_setting_num = real_channel_num - va_channel_num;

					unsigned short* pGroupStart = (unsigned short*)&cfgBinBuffer[14]; 
					unsigned char* channelInfo = (unsigned char*)&cfgBinBuffer[30];

					unsigned char channeIndex[] = {0, 8, 16, 26};
					for( int iGroup = 0; iGroup < MAX_CHANNEL_ONE_GROUP; iGroup++ )
					{
						unsigned char whichGroup = 0;
						unsigned int iGroupInfo = (unsigned int)(pGroupStart[iGroup * 2 + 1] << 16) | pGroupStart[iGroup * 2];
						for( int iter = 0; iter < MAX_IX_NUM_3535; iter++ )
						{
							if( iter < 8 )
							{
								whichGroup = iGroupInfo & 0x03;
								iGroupInfo = iGroupInfo >> 2;
							}
							else
							{
								whichGroup = (iGroupInfo & 0x01) ? 3 : 2;
								iGroupInfo = iGroupInfo >> 2;
							}	

							if( channelInfo[iGroup * MAX_IX_NUM_3535 + iter] )
							{
								unsigned char channelStart = channeIndex[whichGroup];
								ic_2_sensor_map[channelStart + iter] = channelInfo[iGroup * MAX_IX_NUM_3535 + iter];
								sensor_2_ic_map[channelInfo[iGroup * MAX_IX_NUM_3535 + iter] - 1] = channelStart + iter;
							}
							
						}
					}

					if( pCfg3535->tp_chain & 0x8 )
					{
						rowsCnt = 4;
						colsCnt = ( (pCfg3535->tp_chain >> 4) & 0x3f ) >> 2;
						bVerticalTriangle = 1;
					}
					else
					{
						rowsCnt = 2;
						colsCnt = ( (pCfg3535->tp_chain >> 4) & 0x3f ) >> 1;
						bVerticalTriangle = 0;
					}

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
					if( Set_Key_Num > 4 )
					{
						int key_y = ( cfgBinBuffer[44 * 2 + 1] << 8 ) + cfgBinBuffer[44 * 2 + 0];
						keyarray[0][0] = cfgBinBuffer[40 * 2 + 0] & 0x0f;
						keyarray[1][0] = ( cfgBinBuffer[40 * 2 + 0] & 0xf0 ) >> 4;
						keyarray[2][0] = cfgBinBuffer[40 * 2 + 1] & 0x0f;
						keyarray[3][0] = ( cfgBinBuffer[40 * 2 + 1] & 0xf0 ) >> 4;
						keyarray[4][0] = cfgBinBuffer[41 * 2 + 0] & 0x0f;
						keyarray[5][0] = ( cfgBinBuffer[41 * 2 + 0] & 0xf0 ) >> 4;
						keyarray[6][0] = cfgBinBuffer[41 * 2 + 1] & 0x0f;
						keyarray[7][0] = ( cfgBinBuffer[41 * 2 + 1] & 0xf0 ) >> 4;
						keyarray[8][0] = cfgBinBuffer[42 * 2 + 0] & 0x0f;
						for (int i=0 ;i<9 ;i++)
						{
							keyarray[i][1]=key_y;
						}

					}
					else
					{
						int key_y = ( cfgBinBuffer[44 * 2 + 1] << 8 ) + cfgBinBuffer[44 * 2 + 0];
						keyarray[0][0] = ( cfgBinBuffer[40 * 2 + 1] << 8 ) + cfgBinBuffer[40 * 2 + 0];
						keyarray[0][1] = key_y;
						keyarray[1][0] = ( cfgBinBuffer[41 * 2 + 1] << 8 ) + cfgBinBuffer[41 * 2 + 0];
						keyarray[1][1] = key_y;
						keyarray[2][0] = ( cfgBinBuffer[42 * 2 + 1] << 8 ) + cfgBinBuffer[42 * 2 + 0];
						keyarray[2][1] = key_y;
						keyarray[3][0] = ( cfgBinBuffer[43 * 2 + 1] << 8 ) + cfgBinBuffer[43 * 2 + 0];
					    keyarray[3][1] = key_y;
			
					}

					otp_tail_cnt = 5 - 1;
					unsigned int tempTail[8] = {0x7fec, 0x060298bf, 0x00014cbf, 0x060301bf, 0x0003d43f, 0xffffffff, 0xffffffff, 0xffffffff};
					memcpy_s( otp_tail_buff, sizeof(otp_tail_buff), tempTail, sizeof(tempTail) );
					for( int index = 0; index < 6; index++ )
					{
						int tail = otp_tail_buff[index];
						if( ( tail & 0xffff00ff ) == 0x100bf )
						{
							tail = tail & 0xffff00ff;
							tail |= ( I2cAddr << 8 );
						}
						otp_tail_buff[index] = tail;
					}
					
					//project verion
					unsigned short* pV = (unsigned short*)( &cfgBinBuffer[0] );
					sVersion = pV[1] >> 10;
					pVersion = pV[0] & 0x1ff;
					vVersion = pV[0] >> 9;

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