#include "framework.h"
#include "Config7449.h"
#include "checksum.h"
#include "../TestSrc/ToolKit.h"

#define MAX_BOT_BIN_SIZE_740 199*1024

REGIST_RUNTIME_CLASS_USHORT(CONFIG_TYPE, (CONFIG_TYPE)SEMI_IC_7449, CConfig7449)

typedef CConfig7449 CConfig7438;
REGIST_RUNTIME_CLASS_USHORT(CONFIG_TYPE, (CONFIG_TYPE)SEMI_IC_7438, CConfig7438)

typedef CConfig7449 CConfig7448;
REGIST_RUNTIME_CLASS_USHORT(CONFIG_TYPE, (CONFIG_TYPE)SEMI_IC_7448, CConfig7448)

typedef CConfig7449 CConfig7464;
REGIST_RUNTIME_CLASS_USHORT(CONFIG_TYPE, (CONFIG_TYPE)SEMI_IC_7464, CConfig7464)

CConfig7449::CConfig7449( unsigned short type )
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
	rowsCnt = 0;
	colsCnt = 0;
	boot_exist_bootloader = 0;
	version_set = 0;
	memset( ic_2_sensor_map, 0, sizeof(ic_2_sensor_map) );
	memset( sensor_2_ic_map, 0, sizeof(sensor_2_ic_map) );
	memset( cfgBinBuffer, 0, sizeof(cfgBinBuffer) );
	memset( bootBinBuffer, 0, sizeof( bootBinBuffer ) );

	memset(invalid_node, 1, sizeof(invalid_node));
}
CConfig7449::~CConfig7449()
{

}
BOOL CConfig7449::Parse( const tinyxml2::XMLDocument& xmlDoc )
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
		}
		const XMLElement* pOSCTrimConfig = pWorkStation->FirstChildElement("osctrim_test");
		if( pOSCTrimConfig )
		{
			osctrim_selected = (unsigned char)pOSCTrimConfig->Int64Attribute("selected");
			tick_32k_standard = (unsigned int)pOSCTrimConfig->Int64Attribute("tick_32k_standard");
			trim_32k_min = (unsigned char)pOSCTrimConfig->Int64Attribute("trim_32k_min");
			trim_32k_max = (unsigned char)pOSCTrimConfig->Int64Attribute("trim_32k_max");

			tick_48m_standard = (unsigned int)pOSCTrimConfig->Int64Attribute("tick_48m_standard");
			trim_48m_min = (unsigned char)pOSCTrimConfig->Int64Attribute("trim_48m_min");
			trim_48m_max = (unsigned char)pOSCTrimConfig->Int64Attribute("trim_48m_max");

			tick_64m_standard = (unsigned int)pOSCTrimConfig->Int64Attribute("tick_64m_standard");
			trim_64m_min = (unsigned char)pOSCTrimConfig->Int64Attribute("trim_64m_min");
			trim_64m_max = (unsigned char)pOSCTrimConfig->Int64Attribute("trim_64m_max");

			tick_150m_standard = (unsigned int)pOSCTrimConfig->Int64Attribute("tick_150m_standard");
			trim_150m_min = (unsigned char)pOSCTrimConfig->Int64Attribute("trim_150m_min");
			trim_150m_max = (unsigned char)pOSCTrimConfig->Int64Attribute("trim_150m_max");

			trim_speed_mode = (unsigned char)pOSCTrimConfig->Int64Attribute("speed_mode");
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

			mcap_ranks_allow_overrun_num = (unsigned short)pMCapRawDataConfig->Int64Attribute("ranks_allow_overrun_num", 0);
			mcap_allow_overrun_num = (unsigned short)pMCapRawDataConfig->Int64Attribute("allow_overrun_num", 0);
			mcap_allow_overrun_ratio = (unsigned short)pMCapRawDataConfig->Int64Attribute("allow_overrun_ratio", 0);

			macp_normalization_ratio_min = (float)pMCapRawDataConfig->Int64Attribute("normalization_ratio_min", 50)/100; 
			macp_normalization_ratio_max = (float)pMCapRawDataConfig->Int64Attribute("normalization_ratio_max", 150)/100; 

			rawdata_min_value = min;
			rawdata_max_value = max;
		}

		const XMLElement* pVTConfig = pWorkStation->FirstChildElement("vt_test");
		if( pVTConfig )
		{
			vt_selected = (unsigned char)pVTConfig->Int64Attribute("selected");
			vt_min = (short)pVTConfig->Int64Attribute("vt_min");
			vt_max = (short)pVTConfig->Int64Attribute("vt_max");
		}

		const XMLElement* pBaseConfig = pWorkStation->FirstChildElement("base_test");
		if( pBaseConfig )
		{
			base_selected = (unsigned char)pBaseConfig->Int64Attribute("selected");
			base_min = (unsigned short)pBaseConfig->Int64Attribute("base_min");
			base_max = (unsigned short)pBaseConfig->Int64Attribute("base_max");
		}

		const XMLElement* pNoiseConfig = pWorkStation->FirstChildElement("noise_test");
		if( pNoiseConfig )
		{
			noise_selected = (unsigned char)pNoiseConfig->Int64Attribute("selected");
			noise_frame = (short)pNoiseConfig->Int64Attribute("noise_frames");
			noise_max = (short)pNoiseConfig->Int64Attribute("noise_max");
		}
		const XMLElement* pMiscConfig = pWorkStation->FirstChildElement("misc_test");
		if( pMiscConfig )
		{
			misc_selected = (unsigned char)pMiscConfig->Int64Attribute("selected");
			misc_mode = (unsigned short)pMiscConfig->Int64Attribute("misc_mode");
		}
		const XMLElement* pEnPinConfig = pWorkStation->FirstChildElement("enpin_test");
		if( pMiscConfig )
		{
			enpin_selected = (unsigned char)pEnPinConfig->Int64Attribute("selected");
		}

		const XMLElement* pBootConfig = pWorkStation->FirstChildElement("boot_test");
		if( pBootConfig )
		{
			boot_exist_bootloader = (unsigned char)pBootConfig->Int64Attribute("exist_bootloader", 0);
			version_set = (unsigned int)pBootConfig->Int64Attribute("set_version");
		}
	}	
	return bRet;
}
BOOL CConfig7449::SubParseFromConfig()
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
						sensor_2_ic_map[index] = cfgBinBuffer[0x90 + index];
						ic_2_sensor_map[cfgBinBuffer[0x90 + index]] = index + 1;
					}
					for( int index = 0; index < rowsCnt/*MAX_RX_NUM_7449*/; index++ )
					{
						sensor_2_ic_map[index + MAX_TX_NUM_7449] = cfgBinBuffer[0xb0 + index];
						ic_2_sensor_map[cfgBinBuffer[0xb0 + index] + 0] = index + MAX_TX_NUM_7449 + 1;
					}

					if(cfgBinBuffer[0x0f] & 0x02)
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

					Set_Key_Num = key_setting_num = cfgBinBuffer[0x52];
					if((cfgBinBuffer[0x53] & 0x02) > 0)
					{
						int Key_x = (cfgBinBuffer[0x55] << 8) + cfgBinBuffer[0x54];

						if(Set_Key_Num<=5)
						{
							
							for(int i=0;i<Set_Key_Num;i++)
							{
								keyarray[i][0]=Key_x;
								keyarray[i][1]=(cfgBinBuffer[0x57 + 2 * i] << 8) + cfgBinBuffer[0x56 + 2 * i];
							}
							//keyarray[0][1] = (cfgBinBuffer[0x57] << 8) + cfgBinBuffer[0x56];
							//keyarray[1][1] = (cfgBinBuffer[0x59] << 8) + cfgBinBuffer[0x58];
							//keyarray[2][1] = (cfgBinBuffer[0x5b] << 8) + cfgBinBuffer[0x5a];
							//keyarray[3][1] = (cfgBinBuffer[0x5d] << 8) + cfgBinBuffer[0x5c];
							//keyarray[4][1] = (cfgBinBuffer[0x5f] << 8) + cfgBinBuffer[0x5e];
						}
						else
						{
							for(int i=0;i<Set_Key_Num;i++)
							{
								keyarray[i][0]=Key_x;
								keyarray[i][1]=i+1;
							}	
						}

						Set_Button_Num = cfgBinBuffer[0x188];
						if (Set_Button_Num > 0 && Set_Button_Num < 4)
						{
							int Button_x = (cfgBinBuffer[0x18a] << 8) + cfgBinBuffer[0x189];
							for (int i = 0; i< Set_Button_Num; i++)
							{
								keyarray[Set_Key_Num + i][0] = Button_x;
								keyarray[Set_Key_Num + i][1] = (cfgBinBuffer[0x18d + i * 2 + i] << 8) + cfgBinBuffer[0x18c + i * 2 + i];
							}
						}
						
					}
					else
					{
						int Key_y = (cfgBinBuffer[0x55] << 8) + cfgBinBuffer[0x54];
						if (Set_Key_Num<=5)
						{
							for(int i=0;i<Set_Key_Num;i++)
							{
								keyarray[i][1]=Key_y;
								keyarray[i][0]=(cfgBinBuffer[0x57 + 2 * i] << 8) + cfgBinBuffer[0x56 + 2 * i];
							}
							//keyarray[0][0] = (cfgBinBuffer[0x57] << 8) + cfgBinBuffer[0x56];
							//keyarray[1][0] = (cfgBinBuffer[0x59] << 8) + cfgBinBuffer[0x58];
							//keyarray[2][0] = (cfgBinBuffer[0x5b] << 8) + cfgBinBuffer[0x5a];
							//keyarray[3][0] = (cfgBinBuffer[0x5d] << 8) + cfgBinBuffer[0x5c];
							//keyarray[4][0] = (cfgBinBuffer[0x5f] << 8) + cfgBinBuffer[0x5e];
						} 
						else
						{
							for(int i=0;i<Set_Key_Num;i++)
							{
								keyarray[i][0]=i+1;
								keyarray[i][1]=Key_y;
							}	
						}

						Set_Button_Num = cfgBinBuffer[0x188];
						if (Set_Button_Num > 0 && Set_Button_Num < 4)
						{
							int Button_y = (cfgBinBuffer[0x18a] << 8) + cfgBinBuffer[0x189];
							for (int i = 0; i< Set_Button_Num; i++)
							{
								keyarray[Set_Key_Num + i][1] = Button_y;
								keyarray[Set_Key_Num + i][0] = (cfgBinBuffer[0x18d + i * 2 + i] << 8) + cfgBinBuffer[0x18c + i * 2 + i];
							}
						}
						
					}										
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
			if( (bootBinSize <= MAX_BOT_BIN_SIZE_740) && (bootBinSize == fread_s( bootBinBuffer, MAX_BOT_BIN_SIZE_740, 1, bootBinSize, file )) )
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