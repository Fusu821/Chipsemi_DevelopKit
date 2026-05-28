#include "framework.h"
#include "Config310.h"
#include "checksum.h"
#include "../TestSrc/ToolKit.h"

REGIST_RUNTIME_CLASS_USHORT(CONFIG_TYPE, (CONFIG_TYPE)SEMI_IC_CHUF310, CConfig310)

CConfig310::CConfig310( unsigned short type )
:CConfig(type)
{
	current_selected = 0;
	osctrim_selected = 0;

	pixeldefect_selected = 0;
	frt_selected = 0;
	iovol_selected = 0;


	noise_selected = 0;
	temperature_selected = 0;
    otp_selected = 0;
    communication_selected = 0;
    pressure_contact_selected = 0;
    adc_selected = 0;
	flytime_selected = 0;
	srf_selected = 0;

	va_channel_num = 0;
	harf_va_channel_num = 0;
	//key_num = 0;
	//all_channel_num =0;
	cfgBinSize = 0;
	bootBinSize = 0;
	cfgTestBinSize = 0;

	rowsCnt = 0;
	colsCnt = 0;

	memset( cfgBinBuffer, 0, sizeof(cfgBinBuffer) );
	memset( bootBinBuffer, 0, sizeof( bootBinBuffer ) );
	memset(invalid_node, 1, sizeof(invalid_node));
}

CConfig310::~CConfig310()
{

}
BOOL CConfig310::Parse( const tinyxml2::XMLDocument& xmlDoc )
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
			idle_current_min = (short)pCurrentConfig->Int64Attribute("idle_current_min",0);
			idle_current_max = (short)pCurrentConfig->Int64Attribute("idle_current_max",100);
			sleep_current_min = (short)pCurrentConfig->Int64Attribute("sleep_current_min",0);
			sleep_current_max = (short)pCurrentConfig->Int64Attribute("sleep_current_max",240);
			active_current_min = (short)pCurrentConfig->Int64Attribute("active_current_min",5);
			active_current_max = (short)pCurrentConfig->Int64Attribute("active_current_max",60);

			//vbus_deep_current_min = (short)pCurrentConfig->Int64Attribute("vbus_deep_current_min",0);
			//vbus_deep_current_max = (short)pCurrentConfig->Int64Attribute("vbus_deep_current_max",100);
			//vbus_sleep_current_min = (short)pCurrentConfig->Int64Attribute("vbus_sleep_current_min",0);
			//vbus_sleep_current_max = (short)pCurrentConfig->Int64Attribute("vbus_sleep_current_max",240);
			//vbus_active_current_min = (short)pCurrentConfig->Int64Attribute("vbus_active_current_min",10);
			//vbus_active_current_max = (short)pCurrentConfig->Int64Attribute("vbus_active_current_max",60);

		}
		const XMLElement* pOSCTrimConfig = pWorkStation->FirstChildElement("osctrim_test");
		if( pOSCTrimConfig )
		{
			osctrim_selected = (unsigned char)pOSCTrimConfig->Int64Attribute("selected");
			tick_32k_standard = (unsigned int)pOSCTrimConfig->Int64Attribute("tick_32k_standard");
			trim_32k_min = (unsigned char)pOSCTrimConfig->Int64Attribute("trim_32k_min");
			trim_32k_max = (unsigned char)pOSCTrimConfig->Int64Attribute("trim_32k_max");
			offset_32k = (unsigned short)pOSCTrimConfig->Int64Attribute("offset_32k");

			tick_52m_standard = (unsigned int)pOSCTrimConfig->Int64Attribute("tick_52m_standard");
			tick_52m_standardNo1 = (unsigned int)pOSCTrimConfig->Int64Attribute("tick_52m_standardNo1");
			tick_52m_standardNo2 = (unsigned int)pOSCTrimConfig->Int64Attribute("tick_52m_standardNo2");
			tick_52m_standardNo3 = (unsigned int)pOSCTrimConfig->Int64Attribute("tick_52m_standardNo3");

			trim_52m_min = (unsigned short)pOSCTrimConfig->Int64Attribute("trim_52m_min");
			trim_52m_max = (unsigned short)pOSCTrimConfig->Int64Attribute("trim_52m_max");
			offset_52m = (unsigned short)pOSCTrimConfig->Int64Attribute("offset_52m");

			//tick_250m_standard = (unsigned int)pOSCTrimConfig->Int64Attribute("tick_250m_standard");
			//trim_250m_min = (unsigned char)pOSCTrimConfig->Int64Attribute("trim_250m_min");
			//trim_250m_max = (unsigned char)pOSCTrimConfig->Int64Attribute("trim_250m_max");
			//offset_250m = (unsigned short)pOSCTrimConfig->Int64Attribute("offset_250m");

			trim_speed_mode = (unsigned char)pOSCTrimConfig->Int64Attribute("speed_mode");

			trim_only_check = (unsigned char)pOSCTrimConfig->Int64Attribute("only_check", 0);
		}

		const XMLElement* pPixelDefectConfig = pWorkStation->FirstChildElement("pixeldefect_test");
		if( pPixelDefectConfig )
		{
			pixeldefect_selected = (unsigned char)pPixelDefectConfig->Int64Attribute("selected");
			pixel_raw_max = (unsigned short)pPixelDefectConfig->Int64Attribute("pixel_raw_max", 1000);
			pixel_raw_min = (unsigned short)pPixelDefectConfig->Int64Attribute("pixel_raw_min", 30);
			gain1_0_max = (double)pPixelDefectConfig->DoubleAttribute("gain1_0_max", 1.8);
			gain1_0_min = (double)pPixelDefectConfig->DoubleAttribute("gain1_0_min", 1);
			gain2_1_max = (double)pPixelDefectConfig->DoubleAttribute("gain2_1_max", 1.5);
			gain2_1_min = (double)pPixelDefectConfig->DoubleAttribute("gain2_1_min", 1);

		}

		//const XMLElement* pFrtConfig = pWorkStation->FirstChildElement("frt_test");
		//if( pFrtConfig )
		//{
		//	frt_selected = (unsigned char)pFrtConfig->Int64Attribute("selected");
		//}

		const XMLElement* pIoVolConfig = pWorkStation->FirstChildElement("iovol_test");
		if( pIoVolConfig )
		{
			iovol_selected = (unsigned char)pIoVolConfig->Int64Attribute("selected");
			int0_1p2_low_min = (unsigned int)pIoVolConfig->Int64Attribute("int0_1p2_low_min", 0);
			int0_1p2_low_max = (unsigned int)pIoVolConfig->Int64Attribute("int0_1p2_low_max", 100);
			int0_1p2_high_min = (unsigned int)pIoVolConfig->Int64Attribute("int0_1p2_high_min", 1000);
			int0_1p2_high_max = (unsigned int)pIoVolConfig->Int64Attribute("int0_1p2_high_max", 1400);
			int2_1p2_low_min = (unsigned int)pIoVolConfig->Int64Attribute("int2_1p2_low_min", 0);
			int2_1p2_low_max = (unsigned int)pIoVolConfig->Int64Attribute("int2_1p2_low_max", 100);
			int2_1p2_high_min = (unsigned int)pIoVolConfig->Int64Attribute("int2_1p2_high_min", 1000);
			int2_1p2_high_max = (unsigned int)pIoVolConfig->Int64Attribute("int2_1p2_high_max", 1400);

			int0_1p8_low_min = (unsigned int)pIoVolConfig->Int64Attribute("int0_1p8_low_min", 0);
			int0_1p8_low_max = (unsigned int)pIoVolConfig->Int64Attribute("int0_1p8_low_max", 100);
			int0_1p8_high_min = (unsigned int)pIoVolConfig->Int64Attribute("int0_1p8_high_min", 1600);
			int0_1p8_high_max = (unsigned int)pIoVolConfig->Int64Attribute("int0_1p8_high_max", 2000);
			int2_1p8_low_min = (unsigned int)pIoVolConfig->Int64Attribute("int2_1p8_low_min", 0);
			int2_1p8_low_max = (unsigned int)pIoVolConfig->Int64Attribute("int2_1p8_low_max", 100);
			int2_1p8_high_min = (unsigned int)pIoVolConfig->Int64Attribute("int2_1p8_high_min", 1600);
			int2_1p8_high_max = (unsigned int)pIoVolConfig->Int64Attribute("int2_1p8_high_max", 1800);

		}


		const XMLElement* pNoiseConfig = pWorkStation->FirstChildElement("noise_test");
		if( pNoiseConfig )
		{
			noise_selected = (unsigned char)pNoiseConfig->Int64Attribute("selected");
            noise_frame = (short)pNoiseConfig->Int64Attribute("noise_frames");

            noise_max_time_A = (short)pNoiseConfig->Int64Attribute("noise_max_time_A");
		    noise_max_time_P = (short)pNoiseConfig->Int64Attribute("noise_max_time_P");
		    noise_max_space_A = (short)pNoiseConfig->Int64Attribute("noise_max_space_A");
		    noise_max_space_P = (short)pNoiseConfig->Int64Attribute("noise_max_space_P");
		}

		const XMLElement* pSrfConfig = pWorkStation->FirstChildElement("srf_test");
		if( pSrfConfig )
		{
			srf_selected = (unsigned char)pSrfConfig->Int64Attribute("selected");
            

            srfreq_max = pSrfConfig->DoubleAttribute("srfreq_max");
			srfreq_min = pSrfConfig->DoubleAttribute("srfreq_min");

		}



		const XMLElement* pFlytimeConfig = pWorkStation->FirstChildElement("flytime_test");
		if( pFlytimeConfig )
		{
			flytime_selected = (unsigned char)pFlytimeConfig->Int64Attribute("selected");
            

            flytime_code_max = (short)pFlytimeConfig->Int64Attribute("flytime_code_max");
			flytime_code_min = (short)pFlytimeConfig->Int64Attribute("flytime_code_min");
			flytime_val_max = (short)pFlytimeConfig->Int64Attribute("flytime_val_max");
			flytime_val_min = (short)pFlytimeConfig->Int64Attribute("flytime_val_min");
			flytime_std_max = (short)pFlytimeConfig->Int64Attribute("flytime_std_max");
			flytime_std_min = (short)pFlytimeConfig->Int64Attribute("flytime_std_min");

		}

        const XMLElement* pTemperatureConfig = pWorkStation->FirstChildElement("temperature_test");
        if( pTemperatureConfig )
        {
            temperature_selected = (unsigned char)pTemperatureConfig->Int64Attribute("selected");
            //...
        }

        const XMLElement* pOtpConfig = pWorkStation->FirstChildElement("otp_test");
        if( pOtpConfig )
        {
            otp_selected = (unsigned char)pOtpConfig->Int64Attribute("selected");
            otp_only_check = (unsigned char)pOtpConfig->Int64Attribute("only_check", 0);
			simplelog = (unsigned char)pOtpConfig->Int64Attribute("simplelog", 0);
        }

        const XMLElement* pCommunicationConfig = pWorkStation->FirstChildElement("communication_test");
        if( pCommunicationConfig )
        {
            communication_selected = (unsigned char)pCommunicationConfig->Int64Attribute("selected");
            //...
        }

        const XMLElement* pPressureContactConfig = pWorkStation->FirstChildElement("pressure_contact_test");
        if( pPressureContactConfig )
        {
            pressure_contact_selected = (unsigned char)pPressureContactConfig->Int64Attribute("selected");
            //...
        }

        const XMLElement* pAdcContactConfig = pWorkStation->FirstChildElement("adc_test");
        if( pAdcContactConfig )
        {
            adc_selected = (unsigned char)pAdcContactConfig->Int64Attribute("selected");
            
            adc_tx_max = (short)pAdcContactConfig->Int64Attribute("adc_tx_max");
			adc_tx_min = (short)pAdcContactConfig->Int64Attribute("adc_tx_min");

			adc_notx_max = (short)pAdcContactConfig->Int64Attribute("adc_notx_max");
			adc_notx_min = (short)pAdcContactConfig->Int64Attribute("adc_notx_min");

        }

	}
	return bRet;
}
BOOL CConfig310::CheckCfgBinFile( unsigned char* pCfg, unsigned int byteSize )
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
BOOL CConfig310::SubParseFromConfig()
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
						sensor_2_ic_map[index + MAX_TX_NUM_5562] = cfgBinBuffer[0x64 + index];
						ic_2_sensor_map[cfgBinBuffer[0x64 + index] + 0] = index + MAX_TX_NUM_5562 + 1;
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
			if( (bootBinSize <= MAX_BOT_BIN_SIZE_310) && (bootBinSize == fread_s( bootBinBuffer, MAX_BOT_BIN_SIZE_310, 1, bootBinSize, file )) )
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