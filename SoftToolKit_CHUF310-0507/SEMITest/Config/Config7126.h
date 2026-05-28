#pragma once
#include "Config.h"
class CConfig7126 : public CConfig
{
public:
	CConfig7126( unsigned short type );
	virtual ~CConfig7126();

	virtual BOOL Parse( const tinyxml2::XMLDocument& xmlDoc );
	virtual BOOL CheckCfgBinFile( unsigned char* pCfg, unsigned int byteSize ) override;

	BOOL SubParseFromConfig();
public:
	//config
	unsigned short ic_2_sensor_map[MAX_RX_NUM_7126 + MAX_TX_NUM_7126];
	unsigned short sensor_2_ic_map[MAX_RX_NUM_7126 + MAX_TX_NUM_7126];
	unsigned char  invalid_node[MAX_MCAP_ROW_710][MAX_MCAP_COL_710]; 

	//current test
	unsigned char current_selected;
	//unsigned short current_action;
	signed short deep_current_min;
	signed short deep_current_max;
	signed short sleep_current_min;
	signed short sleep_current_max;
	signed short active_current_min;//mA
	signed short active_current_max;//mA

	signed short vbus_deep_current_min;
	signed short vbus_deep_current_max;
	signed short vbus_sleep_current_min;
	signed short vbus_sleep_current_max;
	signed short vbus_active_current_min;//mA
	signed short vbus_active_current_max;//mA
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
	unsigned short offset_32k;

	unsigned int  tick_144m_standard;
	unsigned int  tick_144m_standardNo2;
	unsigned int  tick_144m_standardNo3;
	unsigned int  tick_144m_standardNo4;
	unsigned int  tick_144m_standardNo5;
	unsigned short trim_144m_min;
	unsigned short trim_144m_max;
	unsigned short offset_144m;

	unsigned int  tick_250m_standard;
	unsigned char trim_250m_min;
	unsigned char trim_250m_max;
	unsigned short offset_250m;

	unsigned char trim_speed_mode;

	unsigned char trim_only_check;
	//base test
	// 	unsigned char base_selected;
	// 	/*unsigned*/ short base_min[MAX_MCAP_ROW_710][MAX_MCAP_COL_710];
	// 	/*unsigned*/ short base_max[MAX_MCAP_ROW_710][MAX_MCAP_COL_710];

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
	//signed short vt_min;
	signed short vt_max;
	unsigned short vt_on[1][MAX_MCAP_ROW_710];
	unsigned short vt_off[1][MAX_MCAP_ROW_710];
	unsigned short vt_diff_max[1][MAX_MCAP_ROW_710];

	//noise test
	unsigned char noise_selected;
	signed short noise_frame;

	short noise_mcap_base[MAX_MCAP_ROW_710][MAX_MCAP_COL_710];
	short noise_scap_base[MAX_MCAP_ROW_710][MAX_MCAP_COL_710];

	signed short noise_max_mcap1;
	signed short noise_max_scap1;

	signed short noise_max_mcap2;
	signed short noise_max_scap2;

	signed short noise_max_mcap3;
	signed short noise_max_scap3;

	signed short noise_max_mcap4;
	signed short noise_max_scap4;

	signed short noise_max_mcap5;
	signed short noise_max_scap5;

	signed short noise_max_mcap6;
	signed short noise_max_scap6;

	signed short noise_max_mcap7;
	signed short noise_max_scap7;


	signed short noise_max_mcap8;
	signed short noise_max_scap8;

	//misc test
	unsigned char misc_selected;
	unsigned short misc_mode;

	//scap rawdata test
	unsigned char scap_rawdata_selected;
	unsigned short scap_rawdata_min[MAX_MCAP_ROW_710][MAX_MCAP_COL_710];
	unsigned short scap_rawdata_max[MAX_MCAP_ROW_710][MAX_MCAP_COL_710];

	//low freq rawdata test
	unsigned char stc_selected;
	unsigned short stc_clk_div;
	signed short   stc_min;
	signed short   stc_max;
	unsigned short stc_mean[MAX_MCAP_ROW_710][MAX_MCAP_COL_710];
	unsigned short stc_mse[MAX_MCAP_ROW_710][MAX_MCAP_COL_710];
	//unsigned short stc_min[MAX_MCAP_ROW_710][MAX_MCAP_COL_710];
	//unsigned short stc_max[MAX_MCAP_ROW_710][MAX_MCAP_COL_710];
	unsigned short stc_uniformity_h[MAX_MCAP_ROW_710][MAX_MCAP_COL_710];
	unsigned short stc_uniformity_v[MAX_MCAP_ROW_710][MAX_MCAP_COL_710];

	//high freq rawdata test
	unsigned char mcap_rawdata_selected;
	unsigned short mcap_clk_div;
	unsigned char check_uniformity_hor;
	unsigned char check_uniformity_ver;
	unsigned short mcap_rawdata[MAX_MCAP_ROW_710][MAX_MCAP_COL_710];
	unsigned short mcap_rawdata_min[MAX_MCAP_ROW_710][MAX_MCAP_COL_710];
	unsigned short mcap_rawdata_max[MAX_MCAP_ROW_710][MAX_MCAP_COL_710];
	unsigned short mcap_uniformity_h[MAX_MCAP_ROW_710][MAX_MCAP_COL_710];
	unsigned short mcap_uniformity_v[MAX_MCAP_ROW_710][MAX_MCAP_COL_710];
	float macp_normalization_ratio_min; 
	float macp_normalization_ratio_max; 

	unsigned char uniformity_invalid_node[MAX_MCAP_ROW_710][MAX_MCAP_COL_710];
	float macp_h_v_over_limit_ratio; 
	unsigned short macp_h_v_over_limit_maxnum; 

	//jump tmp base
	unsigned char base_selected;
	unsigned short base_diff_max;
	unsigned short base_num_max;
	unsigned short base_all_diff_max;
	unsigned short base_all_num_max;
	//unsigned short base_cover_diff_max;
	unsigned char tmp_num;
	unsigned char  tmp_invalid_node[MAX_MCAP_ROW_710][MAX_MCAP_COL_710]; 

	//unsigned char base_save_data;
	//unsigned char base_simplifyA_algorithm;

	unsigned short tmp_1_mcapdata[MAX_MCAP_ROW_710][MAX_MCAP_COL_710];
	unsigned short tmp_2_mcapdata[MAX_MCAP_ROW_710][MAX_MCAP_COL_710];
	unsigned short tmp_3_mcapdata[MAX_MCAP_ROW_710][MAX_MCAP_COL_710];
	unsigned short tmp_4_mcapdata[MAX_MCAP_ROW_710][MAX_MCAP_COL_710];
	unsigned short tmp_5_mcapdata[MAX_MCAP_ROW_710][MAX_MCAP_COL_710];
	unsigned short tmp_6_mcapdata[MAX_MCAP_ROW_710][MAX_MCAP_COL_710];
	unsigned short tmp_7_mcapdata[MAX_MCAP_ROW_710][MAX_MCAP_COL_710];
	unsigned short tmp_8_mcapdata[MAX_MCAP_ROW_710][MAX_MCAP_COL_710];

	//fsd test
	unsigned char fsd_selected;
	unsigned short fsd_fast_div;
	unsigned short fsd_slow_div;
	unsigned short fsd_frames;
	unsigned short fsd_diff_max_default;

	unsigned char fsd_xy_num;
	unsigned char fsd_i2v_rfb;

	unsigned char fsd_lpf_sft;
	unsigned char fsd_dec_sft;

	unsigned char fsd_c2v_rfb;
	unsigned char fsd_rx_rin;

	unsigned short fsd_fast[MAX_MCAP_ROW_710][MAX_MCAP_COL_710];
	unsigned short fsd_slow[MAX_MCAP_ROW_710][MAX_MCAP_COL_710];
	unsigned short fsd_diff_max[MAX_MCAP_ROW_710][MAX_MCAP_COL_710];

	unsigned char fsd_fast_mcap_test;
	unsigned short fsd_fast_mcap_limit;

	unsigned short fsd_fast_min[MAX_MCAP_ROW_710][MAX_MCAP_COL_710];
	unsigned short fsd_fast_max[MAX_MCAP_ROW_710][MAX_MCAP_COL_710];

	//WBase
	unsigned char wbase_selected;

	unsigned short wbase_node33_diff_max;
	unsigned short wbase_node33_num_max;

	//unsigned short wbase_node55_diff_max;
	//unsigned short wbase_node55_num_max;

	unsigned short wbase_all_diff_max;
	unsigned short wbase_all_num_max;

	//unsigned short wbase_fast;
	//unsigned short wbase_slow;

	//float fator_HL[MAX_MCAP_ROW_710][MAX_MCAP_COL_710];

	//dog test
	unsigned char wdogt_selected;
	/**************************************************************/
};