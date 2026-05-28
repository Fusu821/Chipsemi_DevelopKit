#pragma once
#include "Config.h"
class CConfig7449 : public CConfig
{
public:
	CConfig7449( unsigned short type );
	virtual ~CConfig7449();

	virtual BOOL Parse( const tinyxml2::XMLDocument& xmlDoc );

	BOOL SubParseFromConfig();
public:
	//config
	unsigned short ic_2_sensor_map[MAX_RX_NUM_7449 + MAX_TX_NUM_7449];
	unsigned short sensor_2_ic_map[MAX_RX_NUM_7449 + MAX_TX_NUM_7449];
	unsigned char  invalid_node[MAX_MCAP_ROW][MAX_MCAP_COL]; 

	//current test
	unsigned char current_selected;
	//unsigned short current_action;
	signed short deep_current_min;
	signed short deep_current_max;
	signed short sleep_current_min;
	signed short sleep_current_max;
	signed short active_current_min;
	signed short active_current_max;
	/**************************************************************/
	//FSD Test
//     unsigned char  fsd_selected;
// 	unsigned short f_clk;
// 	unsigned short s_clk;
// 	unsigned short cmp_max;
// 	int            fsd_min;
// 	unsigned char  fsd_recheck;
// 	short          fsd_triger_min;
// 	short          fsd_triger_max;
// 	short          fsd_critical_slow_min;
// 	short          fsd_critical_slow_max;
// 	short          fsd_besides_min;
// 	short          fsd_critical_fast_max;
// 	unsigned char  fsd_plus_check;
// 	short          fsd_plus_t1;
// 	short          fsd_plus_t2;
// 	short          fsd_plus_t3;
// 	short          fsd_plus_t4;
// 
// 	unsigned short fsd_base[MAX_SCAP_ROW][MAX_SCAP_COL];
// 	unsigned short fsd_fast[MAX_SCAP_ROW][MAX_SCAP_COL];
// 	unsigned short fsd_slow[MAX_SCAP_ROW][MAX_SCAP_COL];
// 	unsigned short fsd_deviation[MAX_SCAP_ROW][MAX_SCAP_COL];
// 	unsigned short fsd_delta_max[MAX_SCAP_ROW][MAX_SCAP_COL];
// 	unsigned short fsd_uniformity_left[MAX_SCAP_ROW][MAX_SCAP_COL];
// 	unsigned short fsd_uniformity_right[MAX_SCAP_ROW][MAX_SCAP_COL];
// 	/**************************************************************/
	//os test
//	unsigned char os_selected;
// 	unsigned char integral;
// 	unsigned char scale_a;
// 	unsigned char scale_b;
// 	unsigned short os_clk;
// 	unsigned char m2_ratio;
// 	unsigned char m1_ratio_upper_va;
// 	unsigned char m1_ratio_lower_va;
// 	unsigned char m1_ratio_upper_ref;
// 	unsigned char m1_ratio_lower_ref;
// 	int m3_delta_va_max;
// 	int m3_delta_ref_max;
// 	int m3_delta_level1;
// 	int m3_delta_level2;
// 	unsigned short os_base[MAX_SCAP_ROW][MAX_SCAP_COL];
	/**************************************************************/
	//os trim test
	unsigned char osctrim_selected;
    unsigned int  tick_32k_standard;
	unsigned char trim_32k_min;
	unsigned char trim_32k_max;

	unsigned int  tick_48m_standard;
	unsigned char trim_48m_min;
	unsigned char trim_48m_max;

	unsigned int  tick_64m_standard;
	unsigned char trim_64m_min;
	unsigned char trim_64m_max;

	unsigned int  tick_150m_standard;
	unsigned char trim_150m_min;
	unsigned char trim_150m_max;
	unsigned char trim_speed_mode;
	//base test
// 	unsigned char base_selected;
// 	/*unsigned*/ short base_min[MAX_MCAP_ROW][MAX_MCAP_COL];
// 	/*unsigned*/ short base_max[MAX_MCAP_ROW][MAX_MCAP_COL];

	//short test
	unsigned char short_selected;
	unsigned short short_tx_max;
	unsigned short short_rx_max;

	//frt test
	unsigned char frt_selected;

	//iovol test
    unsigned char iovol_selected;
	unsigned int int_low_min;
	unsigned int int_low_max;
	unsigned int int_high_min;
	unsigned int int_high_max;
    unsigned int iic_low_min;
	unsigned int iic_low_max;
	unsigned int iic_high_min;
	unsigned int iic_high_max;
	unsigned int spi_low_min;
	unsigned int spi_low_max;
	unsigned int spi_high_min;
	unsigned int spi_high_max;

	//vp test
	unsigned char vt_selected;
	signed short vt_min;
	signed short vt_max;

	//base_test
	unsigned char base_selected;
	unsigned short base_min;
	unsigned short base_max;

	//noise test
	unsigned char noise_selected;
	signed short noise_max;
	signed short noise_frame;

	//misc test
	unsigned char misc_selected;
	unsigned short misc_mode;

	//scap rawdata test
	unsigned char scap_rawdata_selected;
	unsigned short scap_rawdata_min[MAX_MCAP_ROW][MAX_MCAP_COL];
	unsigned short scap_rawdata_max[MAX_MCAP_ROW][MAX_MCAP_COL];

	//low freq rawdata test
	unsigned char stc_selected;
	unsigned short stc_clk_div;
	signed short   stc_min;
	signed short   stc_max;
	unsigned short stc_mean[MAX_MCAP_ROW][MAX_MCAP_COL];
	unsigned short stc_mse[MAX_MCAP_ROW][MAX_MCAP_COL];
	//unsigned short stc_min[MAX_MCAP_ROW][MAX_MCAP_COL];
	//unsigned short stc_max[MAX_MCAP_ROW][MAX_MCAP_COL];
	unsigned short stc_uniformity_h[MAX_MCAP_ROW][MAX_MCAP_COL];
	unsigned short stc_uniformity_v[MAX_MCAP_ROW][MAX_MCAP_COL];

	//high freq rawdata test
	unsigned char mcap_rawdata_selected;
	unsigned short mcap_clk_div;
	unsigned char check_uniformity_hor;
	unsigned char check_uniformity_ver;
	unsigned short mcap_rawdata[MAX_MCAP_ROW][MAX_MCAP_COL];
	unsigned short mcap_rawdata_min[MAX_MCAP_ROW][MAX_MCAP_COL];
	unsigned short mcap_rawdata_max[MAX_MCAP_ROW][MAX_MCAP_COL];
	unsigned short mcap_uniformity_h[MAX_MCAP_ROW][MAX_MCAP_COL];
	unsigned short mcap_uniformity_v[MAX_MCAP_ROW][MAX_MCAP_COL];

	unsigned short mcap_ranks_allow_overrun_num;
	unsigned short mcap_allow_overrun_num;
	unsigned short mcap_allow_overrun_ratio;
	float macp_normalization_ratio_min; 
	float macp_normalization_ratio_max; 

	//EnPin test
	unsigned char enpin_selected; 

	//exist_bootloader
	unsigned char boot_exist_bootloader;
	unsigned int version_set;
	/**************************************************************/
};