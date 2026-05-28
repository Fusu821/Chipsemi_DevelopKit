#pragma once
#include "Config.h"
class CConfig3535 : public CConfig
{
public:
	CConfig3535( unsigned short type );
	virtual ~CConfig3535();

	virtual BOOL Parse( const tinyxml2::XMLDocument& xmlDoc );

	BOOL SubParseFromConfig();
public:
	//config
	unsigned short ic_2_sensor_map[MAX_SCAP_CHANNEL];
	unsigned short sensor_2_ic_map[MAX_SCAP_CHANNEL];
	unsigned char  invalid_node[MAX_SCAP_ROW][MAX_SCAP_COL]; 

	//otp
	unsigned char  otp_tail_cnt;
	unsigned int   otp_tail_buff[8];

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

	unsigned short fsd_base[MAX_SCAP_ROW][MAX_SCAP_COL];
	unsigned short fsd_fast[MAX_SCAP_ROW][MAX_SCAP_COL];
	unsigned short fsd_slow[MAX_SCAP_ROW][MAX_SCAP_COL];
	unsigned short fsd_deviation[MAX_SCAP_ROW][MAX_SCAP_COL];
	unsigned short fsd_delta_max[MAX_SCAP_ROW][MAX_SCAP_COL];
	unsigned short fsd_uniformity_left[MAX_SCAP_ROW][MAX_SCAP_COL];
	unsigned short fsd_uniformity_right[MAX_SCAP_ROW][MAX_SCAP_COL];
	/**************************************************************/
	//os test
	unsigned char os_selected;
	unsigned char integral;
	unsigned char scale_a;
	unsigned char scale_b;
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
	//base test
	unsigned char base_selected;
	signed short base_min;
	signed short base_max;
	/**************************************************************/
};