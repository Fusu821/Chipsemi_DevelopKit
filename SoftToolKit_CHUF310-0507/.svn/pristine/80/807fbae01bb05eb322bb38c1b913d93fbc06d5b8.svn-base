#pragma once
#include "Config.h"
class CConfig3536 : public CConfig
{
public:
	CConfig3536( unsigned short type );
	virtual ~CConfig3536();

	virtual BOOL Parse( const tinyxml2::XMLDocument& xmlDoc );

	BOOL SubParseFromConfig();
public:
	//config
	unsigned char sensor_type;
	unsigned short ic_2_sensor_map[MAX_SCAP_CHANNEL];
	unsigned short sensor_2_ic_map[MAX_SCAP_CHANNEL];
	unsigned char  invalid_node[MAX_SCAP_ROW][MAX_SCAP_COL]; 

	//current test
	unsigned char current_selected;
	//unsigned short current_action;
	signed short work_current_min;
	signed short work_current_max;
	signed short sleep_current_min;
	signed short sleep_current_max;
	signed short delta_current_min;
	signed short delta_current_max;
	signed short active_current_min;
	signed short active_current_max;
	/**************************************************************/
	//FSD Test

	struct
	{
		struct ffsdT
		{
			unsigned char  fsd_selected;
			unsigned short f_clk;
			unsigned short s_clk;
			unsigned short cmp_max;
			int            fsd_min;
			unsigned char  fsd_recheck;
			short          fsd_triger_min;
			short          fsd_triger_max;
			short          fsd_critical_slow_min;
			short          fsd_critical_slow_max;
			short          fsd_besides_min;
			short          fsd_critical_fast_max;
			unsigned char  fsd_plus_check;
			short          fsd_plus_t1;
			short          fsd_plus_t2;
			short          fsd_plus_t3;
			short          fsd_plus_t4;
			unsigned char  fb_check;
			short          fb_base;
			short          fb_min;
			short          fb_max;
			unsigned short integral;
			unsigned char  scale_check;
		}fsdT;
		struct ffsdB
		{
			unsigned char  fsd_selected;
			unsigned short f_clk;
			unsigned short s_clk;
			int            fsd_min;
			unsigned char  fsd_recheck;
			short          fsd_triger_min;
			short          fsd_triger_max;
			short          fsd_critical_slow_min;
			short          fsd_critical_slow_max;
			short          fsd_besides_min;
			short          fsd_critical_fast_max;
			unsigned char  fb_check;
			short          fb_base;
			short          fb_min;
			short          fb_max;
			unsigned short integral;
			unsigned char  scale_check;
		}fsdB;

		unsigned short fsd_base[MAX_SCAP_ROW][MAX_SCAP_COL];
		unsigned short fsd_fast[MAX_SCAP_ROW][MAX_SCAP_COL];
		unsigned short fsd_slow[MAX_SCAP_ROW][MAX_SCAP_COL];
		unsigned short fsd_deviation[MAX_SCAP_ROW][MAX_SCAP_COL];
		unsigned short fsd_delta_max[MAX_SCAP_ROW][MAX_SCAP_COL];
		unsigned short fsd_uniformity_left[MAX_SCAP_ROW][MAX_SCAP_COL];
		unsigned short fsd_uniformity_right[MAX_SCAP_ROW][MAX_SCAP_COL];
	}fsd;

	/**************************************************************/
	//os test
	unsigned char os_selected;
	unsigned char integral;
	unsigned char scale_a;
	unsigned char scale_b;
	unsigned short os_clk;
	unsigned char m2_ratio;
	unsigned char m1_ratio_upper_va;
	unsigned char m1_ratio_lower_va;
	unsigned char m1_ratio_upper_ref;
	unsigned char m1_ratio_lower_ref;
	int m3_delta_va_max;
	int m3_delta_ref_max;
	int m3_delta_level1;
	int m3_delta_level2;
	unsigned short os_base[MAX_SCAP_ROW][MAX_SCAP_COL];
	/**************************************************************/
	//os trim test
	unsigned char osctrim_selected;
    unsigned int  tick_standard;
	unsigned char osctrim_min;
	unsigned char osctrim_max;
    unsigned char must_test;
	unsigned int offset_tick;
	//base test
	unsigned char rawdata_selected;
	unsigned short rawdata_min[MAX_SCAP_ROW][MAX_SCAP_COL];
	unsigned short rawdata_max[MAX_SCAP_ROW][MAX_SCAP_COL];
	//noise test
	unsigned char noise_selected;
	signed short noise_max;
	signed short noise_frame;

	//iovol test
	unsigned char iovol_selected;
	//unsigned int int_low;
	//unsigned int int_high;
	//unsigned int iic_low;
	//unsigned int iic_high;

	unsigned int int_low_min;
	unsigned int int_low_max;
	unsigned int int_high_min;
	unsigned int int_high_max;
	unsigned int iic_low_min;
	unsigned int iic_low_max;
	unsigned int iic_high_min;
	unsigned int iic_high_max;

	//vp test
	unsigned char vp_selected;
	unsigned int vp_trigger;
	unsigned int vp_min;
	unsigned int vp_out_time;

	//Algorithm test
	unsigned char algorithm_selected;

	//misc test
	unsigned char misc_selected;
	/**************************************************************/
};