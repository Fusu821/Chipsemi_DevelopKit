#pragma once
#include "Config.h"

#define MAX_BOT_BIN_SIZE_310 199*1024

class CConfig310 : public CConfig
{
public:
    CConfig310( unsigned short type );
    virtual ~CConfig310();

    virtual BOOL Parse( const tinyxml2::XMLDocument& xmlDoc );
    virtual BOOL CheckCfgBinFile( unsigned char* pCfg, unsigned int byteSize ) override;

    BOOL SubParseFromConfig();
public:
    //config
    unsigned short ic_2_sensor_map[MAX_RX_NUM_5562 + MAX_TX_NUM_5562];
    unsigned short sensor_2_ic_map[MAX_RX_NUM_5562 + MAX_TX_NUM_5562];
    unsigned char  invalid_node[MAX_MCAP_ROW][MAX_MCAP_COL];

    //current test
    unsigned char current_selected;
    //unsigned short current_action;
    signed short idle_current_min;
    signed short idle_current_max;
    signed short sleep_current_min;
    signed short sleep_current_max;
    signed short active_current_min;//mA
    signed short active_current_max;//mA

    //signed short vbus_deep_current_min;
    //signed short vbus_deep_current_max;
    //signed short vbus_sleep_current_min;
    //signed short vbus_sleep_current_max;
    //signed short vbus_active_current_min;//mA
    //signed short vbus_active_current_max;//mA

    //os trim test
    unsigned char osctrim_selected;
    unsigned int  tick_32k_standard;
    unsigned char trim_32k_min;
    unsigned char trim_32k_max;
    unsigned short offset_32k;

    unsigned int  tick_52m_standard;
	unsigned int  tick_52m_standardNo1;
    unsigned int  tick_52m_standardNo2;
    unsigned int  tick_52m_standardNo3;
    unsigned short trim_52m_min;
    unsigned short trim_52m_max;
    unsigned short offset_52m;

    unsigned char trim_speed_mode;

    unsigned char trim_only_check;
    //base test
    // 	unsigned char base_selected;
    // 	/*unsigned*/ short base_min[MAX_MCAP_ROW][MAX_MCAP_COL];
    // 	/*unsigned*/ short base_max[MAX_MCAP_ROW][MAX_MCAP_COL];


	//SelfResonanceFreq test
	unsigned char srf_selected;
    double srfreq_max;
	double srfreq_min;

    //pixeldefect test
    unsigned char pixeldefect_selected;
    unsigned short pixel_raw_max;
    unsigned short pixel_raw_min;
    double gain1_0_max;
    double gain1_0_min;
    double gain2_1_max;
    double gain2_1_min;

    //frt test
    unsigned char frt_selected;

    //iovol test
    unsigned char iovol_selected;
    unsigned int int0_1p2_low_min;
    unsigned int int0_1p2_low_max;
	unsigned int int0_1p2_high_min;
    unsigned int int0_1p2_high_max;

	unsigned int int2_1p2_low_min;
    unsigned int int2_1p2_low_max;
    unsigned int int2_1p2_high_min;
    unsigned int int2_1p2_high_max;

    unsigned int int0_1p8_low_min;
    unsigned int int0_1p8_low_max;
    unsigned int int0_1p8_high_min;
    unsigned int int0_1p8_high_max;

    unsigned int int2_1p8_high_min;
    unsigned int int2_1p8_high_max;
    unsigned int int2_1p8_low_min;
    unsigned int int2_1p8_low_max;


    //noise test
    unsigned char noise_selected;
    signed short noise_max_time_A;
    signed short noise_max_space_A;
	signed short noise_max_time_P;
    signed short noise_max_space_P;
    signed short noise_frame;

    //Temperature Test
    unsigned char temperature_selected;

    //OTP Test
    unsigned char otp_selected;
	unsigned char otp_only_check;
	unsigned char simplelog;
	fct_osc_temp_trim_310 fo_trim;

    //Communication Test
    unsigned char communication_selected;

    //Pressure Contact Test
    unsigned char pressure_contact_selected;

    //ADC Test
    unsigned char adc_selected;
	short adc_tx_max;
    short adc_tx_min;
	short adc_notx_max;
    short adc_notx_min;

	//Fly Time Test;
	unsigned char flytime_selected;
    unsigned short flytime_code_max;
    unsigned short flytime_code_min;
	unsigned short flytime_val_max;
    unsigned short flytime_val_min;
    unsigned short flytime_std_max;
    unsigned short flytime_std_min;

	unsigned char tmp_num;
    /**************************************************************/
};