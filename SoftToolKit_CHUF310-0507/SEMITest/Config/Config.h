#pragma once
#include <string>
//#include <tchar.h>
#include "SEMITouch.h"
#include "NativeTestInterface.h"
#include "tinyxml.h"

#include "helper.h"

using namespace tinyxml2;
using namespace std;

enum sensor_type { sensor_ver_triangle = 1, sensor_ver_triangle_ab, sensor_full_keys, sensor_circle_9_8, sensor_circle_9_12, sensor_circle_16_8 };

class CConfig
{
public:
	CConfig( unsigned short type );
	virtual ~CConfig();

	virtual BOOL Parse( const tinyxml2::XMLDocument& xmlDoc );

	virtual BOOL CheckCfgBinFile( unsigned char* pCfg, unsigned int byteSize );

    virtual BOOL SubParseFromConfig();

	LPCTSTR GetMtkAppBinPath();
template<class T>
    void ParseArrayValFromStream( const char* szArray, T *buffer, int maxLen, unsigned char radix = 10 )
	{
		const char *first = szArray;
		char *next = const_cast<char*>( szArray );
		for( int index = 0; index < maxLen; index++ )
		{
			first = next;
			long iRet = strtol( first, &next, radix );
			if( first == next )
			{
				next++;
				continue;
			}

			buffer[index] = (T)iRet;
		}
	}
template<class T, const int M, const int N>
void ParseDetailData( const XMLElement* pFatherElement, const char* detailName, T (&outBuffer)[M][N], int rows, int cols, int defaultVal = 0 )
	{
		if( NULL == pFatherElement ) return;

		for( int iRow = 0; iRow < rows; iRow++ )
		{
			char nodeName[128] = {0};
			transformat( nodeName, _T("%s_%d"), detailName, iRow );
			const XMLElement* pElementDetail = pFatherElement->FirstChildElement(nodeName);
			if( NULL != pElementDetail )
			{
				const char* sz_detail = pElementDetail->GetText();
				if(NULL != sz_detail)
				{
					ParseArrayValFromStream<T>( sz_detail, outBuffer[iRow], cols );
				}
			}
			else
			{
				for( int iCol = 0; iCol < cols; iCol++ )
					outBuffer[iRow][iCol] = defaultVal;
			}
        }

		
	}
private:
	void BootSvnTextToBootSvn( const char* str_boot_svn, unsigned int& boot_svn );
public:
	float VIH;
	unsigned short protocal;
	unsigned char ioVddVotage;
	unsigned char vddVotage;
	unsigned short agent;
	unsigned char eLog;
	unsigned short vihVotage;//char
	unsigned char heatbeatVotage;
	unsigned char protocalType;
	unsigned char  I2cAddr;
	unsigned short Speed;
	unsigned short IcType;
	const char* szWorkStation;
	const char* szProjectName;
	const char* szCfgBinPath;
	const char* szBootBinPath;
    unsigned int boot_check_sum;
	unsigned int config_check_sum;
	 unsigned int boot_loader_check_sum;
	unsigned short w_clk;
	unsigned char filter_off;
	unsigned char key_thr;
	//unsigned short boot_len;
	unsigned short config_len;
	unsigned int   boot_svn;
	unsigned char  Full_Screen;
	/**************************************************************/

	/**************************************************************/
	//config from cfg file
	unsigned char  bVerticalTriangle;
	unsigned short va_channel_num;
	unsigned short harf_va_channel_num;
	unsigned char  key_setting_num;
	//unsigned short all_channel_num;
	unsigned short real_channel_num;
	unsigned short rowsCnt;
	unsigned short colsCnt;
	
	unsigned int   cfgBinSize;
	unsigned char  cfgBinBuffer[MAX_CFG_BIN_SIZE];
	unsigned int   bootBinSize;
	unsigned char  bootBinBuffer[MAX_BOT_BIN_BUFFER_SIZE];//MAX_BOT_BIN_SIZE

	//test config
	unsigned int   cfgTestBinSize;
	unsigned char  cfgTestBinBuffer[MAX_CFG_BIN_SIZE];
	
	
	unsigned short  sVersion;
	unsigned short  pVersion;
	unsigned short  vVersion;
	UINT64    vid_pid;
	/**************************************************************/

	//INT Test
	unsigned char int_selected;
	//RESET Test
	unsigned char reset_selected;
	//BOOT
	unsigned char boot_selected;
    unsigned char boot_only_check;
	//CONfIG
	unsigned char config_selected;
	unsigned char config_only_check;

	//misc
	unsigned short test_mode;
	unsigned char way_to_start;
	unsigned char selected_format;
	unsigned char sn_length;
	unsigned char need_click_start;
	unsigned char need_remove_ic;
	unsigned short hold_up;
	const char* szUserRecord;
	const char* szLogPath;

	//online
	unsigned short link_type;
	unsigned short server_port_num;
	const char* server_ip_addr;
	unsigned short source_port_num;

	//custom
	const char* custom_line_id;
	const char* custom_account;
	const char* custom_password;

	//customv2
	const char* customv2_device_id;
	const char* customv2_process_name;

	//costom_ofilm
	
	const char* costom_ofilm_userId;
	const char* costom_ofilm_fixtureId;
	const char* costom_ofilm_eqpId;
	const char* costom_ofilm_mesUrl;
	const char* costom_ofilm_stepId;
	const char* costom_ofilm_testStepId;
	const char* costom_ofilm_macAddress;
	const char* costom_snFilter;

	//costom_pbh

	const char* costom_pbh_mesUrl;      //上传地址
	const char* costom_pbh_fixtureId;   //治具编号
	const char* costom_pbh_testStepId;  //工单编号
	const char* costom_pbh_stationId;   //站号
	const char* costom_pbh_userId;      //工号
	const char* costom_pbh_passWord;    //密码

	//ftp
	unsigned short ftp_type;
	unsigned short ftp_port;
	const char* ftp_ip_addr;
	const char* ftp_account;
	const char* ftp_password;
	const char* ftp_relative_path;


	//costom_ChuangWei
	const char* costom_ChuangWei_mesUrl;
	const char* costom_ChuangWei_usercode; 
	const char* costom_ChuangWei_processcode; 
	const char* costom_ChuangWei_linecode; 
	const char* costom_ChuangWei_message; 
	const char* costom_ChuangWei_orderno; 
	const char* costom_ChuangWei_macAddress; 
	const char* costom_ChuangWei_simulationUp; 

    //costom_Hes
    const char* costom_Hes_mesUrl;
    const char* costom_Hes_machine_no;
    const char* costom_Hes_lot_no;
    const char* costom_Hes_subop_no;
    const char* costom_Hes_person;

    //costom_Ls
    const char* costom_Ls_mesUrl;
    const char* costom_Ls_resource_no;
    const char* costom_Ls_special_code;
    const char* costom_Ls_operator;
    const char* costom_Ls_device_num;
    unsigned char costom_Ls_displaytest;

	int resolution_x;
	int resolution_y;

	//mtk version test
	unsigned char mtk_selected;
	unsigned int mtk_version;
	unsigned int sync_length;
	unsigned char sync_type;
	unsigned char mtk_auto_update;
	unsigned char mtk_app_bin[MAX_MTK_APP_SIZE];
	unsigned int mtk_app_size;

	//Graph Item
	int Max_NG_Num;
	//Virtual Button Test
	unsigned char button_selected;
	unsigned char Set_Key_Num;
	unsigned char Set_Button_Num ;
	unsigned int  LimitTime_Key;
	int keyarray[48][2];
	//linearly
	unsigned char LINEARITY_TEST;
	int iLinerityMaxNG;
	int iLinearityLimitTime;
	unsigned char LinearityWhenCritical;
	//bool LinearityShowDot;
	//int LinearityLineWidth;
	int Distance_Linearity;
	int Edge_Linearity;
	int Length_Linearity;
	int Position_Linearity;
	int Upper_Limit_H1;
	int Lower_Limit_H1;
	int Upper_Limit_H2;
	int Lower_Limit_H2;
	int Upper_Limit_H3;
	int Lower_Limit_H3;
	int Upper_Limit_H4;
	int Lower_Limit_H4;
	int Upper_Limit_H5;
	int Lower_Limit_H5;
	int Upper_Limit_H6;
	int Lower_Limit_H6;
	int Upper_Limit_V1;
	int Lower_Limit_V1;
	int Upper_Limit_V2;
	int Lower_Limit_V2;
	int Upper_Limit_V3;
	int Lower_Limit_V3;
	int Upper_Limit_V4;
	int Lower_Limit_V4;
	int Upper_Limit_V5;
	int Lower_Limit_V5;
	int Upper_Limit_V6;
	int Lower_Limit_V6;
	int Shielded_Pixels;
	int Shielded_Pixels_H;

	//exp linearly
	unsigned char EXP_LINEARITY_TEST;
    int Exp_iLinerityMaxNG;
    int Exp_iLinearityLimitTime;
    int Exp_Distance_Linearity;
    int Exp_Edge_Linearity;
    int Exp_Length_Linearity;
    int Exp_Position_Linearity;
    int Exp_Upper_Limit_H1;
    int Exp_Lower_Limit_H1;
    int Exp_Upper_Limit_H2;
    int Exp_Lower_Limit_H2;
    int Exp_Upper_Limit_H3;
    int Exp_Lower_Limit_H3;
    int Exp_Upper_Limit_H4;
    int Exp_Lower_Limit_H4;
    int Exp_Upper_Limit_H5;
    int Exp_Lower_Limit_H5;
    int Exp_Upper_Limit_V1;
    int Exp_Lower_Limit_V1;
    int Exp_Upper_Limit_V2;
    int Exp_Lower_Limit_V2;
    int Exp_Upper_Limit_V3;
    int Exp_Lower_Limit_V3;
    int Exp_Upper_Limit_V4;
    int Exp_Lower_Limit_V4;
    int Exp_Upper_Limit_V5;
    int Exp_Lower_Limit_V5;
    int Exp_DiagLength_Linearity;
    int Exp_DiagWidth_Linearity;

    //free paint
    unsigned char FREEPAINT_TEST;
    int FreePaint_LimiteTime;
	unsigned char   isOnce;

	unsigned char   is_xy_reverse;
	unsigned char   is_x_reverse;
	unsigned char   is_y_reverse;
	/**************************************************************/

	unsigned short rawdata_min_value;
	unsigned short rawdata_max_value;
};