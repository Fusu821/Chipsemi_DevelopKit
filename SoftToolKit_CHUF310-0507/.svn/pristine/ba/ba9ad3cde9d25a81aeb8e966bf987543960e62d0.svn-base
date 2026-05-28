#pragma once
#ifndef __HAL_HID_IIC_SERVICE_PARAM__
#define __HAL_HID_IIC_SERVICE_PARAM__
/**************************************************************************************/
#pragma warning( disable:4311 )
#pragma warning( disable:4312 )
enum HAL_BSPR_REQUESTID
{
	HAL_BSPR_CONNECTED,
	HAL_BSPR_SET_ALLOCATED,
	HAL_BSPR_GETINDEX_BYNAME,
	HAL_BSPR_OPENDEVICE,
	HAL_BSPR_CLOSE_DEVICE,
	HAL_BSPR_WRITE,
	HAL_BSPR_READ,
	HAL_BSPR_IOCTRL,
	HAL_BSPR_REACATCH,
	HAL_BSPR_SET_BACKGROUND,
	HAL_BSPR_REGIST_ANALYZER,
	HAL_BSPR_SETDEVICEMANULY,
	HAL_BSPR_CLEAR_DATA_QUEUE,
};

struct HAL_SRV_WR_PARAM
{
	DECLEAR_REQUEST_PARAM( HAL_SRV_WR_PARAM )
		int bResult;
	union{
		struct _WRITE 
		{ 
			//unsigned long  completed;
			unsigned short writeLen;
			unsigned char* writeBuffer;
			//unsigned char writeBuffer[MAX_HAL_WR_LEN];
		}WRITE, *PWRITE;
		struct _READ 
		{
			unsigned long  completed;
			unsigned short readLen;
			unsigned char* readBuffer;
			//unsigned char readBuffer[MAX_HAL_RD_LEN];
		}READ, PREAD;
		struct _IOCTRL
		{
			unsigned long  completed;
			unsigned short writeLen;
			unsigned short readLen;
			unsigned char* writeBuffer;
			unsigned char* readBuffer;
			//unsigned char writeBuffer[MAX_HAL_WR_LEN];
			//unsigned char readBuffer[MAX_HAL_RD_LEN];
		}IOCTRL;
	}un;
};
struct HAL_SRV_SYNC_PARAM
{
	DECLEAR_REQUEST_PARAM( HAL_SRV_SYNC_PARAM )
	int bResult;
	union{
		struct _BACKGROUND
		{
			bool            bBackGroundRequied;
			bool            bOldRequiedState;
		}BACKGROUND, PBACKGROUND;
		struct _SETANALYZER
		{
			LPVOID          pHandler;
			//LPVOID          pFunAnalyzer;
		}SETANALYZER, PSETANALYZER;
		struct _DEVICESTATE
		{
			BOOL connected;
		}DEVICESTATE, PDEVICESTATE;
		struct _OPENDEVICE
		{
			LPCTSTR strName;
		}OPENDEVICE, POPENDEVICE;
		struct _CLOSEDEVICE
		{
			LPCTSTR strName;
		}CLOSEDEVICE, PCLOSEDEVICE;
		struct _SETDEVICE
		{
			int index;
			HANDLE hDevice;
		}SETDEVICE, PSETDEVICE;
		struct _CHECKDATACOME
		{
			bool bHasDataComming;
		}CHECKDATACOME;
	}un;
};

#pragma warning( default:4311 )
#pragma warning( default:4312 )
/**************************************************************************************/
#endif