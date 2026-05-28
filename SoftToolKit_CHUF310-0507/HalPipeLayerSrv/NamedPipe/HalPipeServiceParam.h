#ifndef __HAL_PIPE_SERVICE_PARAM__
#define __HAL_PIPE_SERVICE_PARAM__
/**************************************************************************************/
#pragma warning( disable:4311 )
#pragma warning( disable:4312 )
enum HAL_BSPR_REQUESTID
{
	HAL_BSPR_CONNECTED,
	HAL_BSPR_OPENDEVICE,
	HAL_BSPR_CLOSE_DEVICE,
	HAL_BSPR_WRITE,
	HAL_BSPR_READ,
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
			const unsigned char* writeBuffer;
			unsigned int   writeLen;
		}WRITE, *PWRITE;
		struct _READ 
		{
			unsigned char* readBuffer;
			unsigned int   readLen;
			unsigned int   readed;
		}READ, PREAD;
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
			LPCTSTR ptrName;
		}OPENDEVICE, POPENDEVICE;
		struct _CLOSEDEVICE
		{
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