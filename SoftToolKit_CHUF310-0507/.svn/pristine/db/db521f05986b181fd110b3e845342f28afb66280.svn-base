#pragma once
#include "Macro.h"


//////////////////////////////////////////////////////////////////////////
struct One_Record
{
	unsigned int time;
	UINT64 vid_pid;
	unsigned short record_crc;
	unsigned short reserve;
	unsigned short sz_crc;
	unsigned short szlen;
	One_Record()
		:time(0)
		,vid_pid(0)
		,reserve(0)
		,szlen(0)
		,sz_crc(0)
	{

	}
};
struct Trace_Info
{
	unsigned char trace_cnt;
	unsigned char reverse;
	unsigned short tlen;
};

struct RecordData_V1
{
	unsigned short Header[4];
	unsigned short DataLen;
	unsigned short Version;
	unsigned short ChipType;
	unsigned int TestRet;
	unsigned char ucDevice;
	unsigned char sn[100];
	union
	{
		struct  
		{
			unsigned short TestType;
			unsigned short StaticRdy;
			unsigned short RealSize;
			unsigned short keyNum;
			unsigned int   ReleaseID;
			unsigned char  Ic2Sensor_map[MAX_SCAP_CHANNEL];
			unsigned char  Sensor2Ic_map[MAX_SCAP_CHANNEL];
			unsigned short OS_test_buff[MAX_SCAP_CHANNEL];
			unsigned short Base_test_buff[MAX_SCAP_CHANNEL];
			short          fsd_test_buff[MAX_SCAP_CHANNEL];
			unsigned short fsd_fast_buff[MAX_SCAP_CHANNEL];
			unsigned short fsd_slow_buff[MAX_SCAP_CHANNEL];

		}Scap;
		struct  
		{

		}Mcap;

		unsigned short CRC16;
	};

public:
	RecordData_V1()
	{
		memset(this, 0, sizeof(RecordData_V1));
		DoInit();
	}
	void DoInit()
	{
		Header[0] = 'S';
		Header[1] = 'E';
		Header[2] = 'M';
		Header[3] = 'I';
		memset(sn, 0, sizeof(sn));

		Version = 0x0001;
		DataLen = sizeof(RecordData_V1) - 4 - 2;
	}
};
//////////////////////////////////////////////////////////////////////////
struct ResultBaseMap 
{
	char baseName[20];
	unsigned short offset;
	unsigned short size;
};
struct RecordData
{
	unsigned short ucDevice;
	unsigned short Header[4];
	unsigned short DataLen;
	unsigned short Version;
	unsigned short ChipType;
	unsigned short RealSize;
	unsigned short VaChannelNum;
	unsigned short channelX;
	unsigned short channelY;
	unsigned short TestResult;
	unsigned char workStation[50];
	ResultBaseMap mapofResult[30]; 
	unsigned char Reserve[100];
	unsigned char snCode[100];

	short    current_mode1;
	short    current_mode2;
	short    current_mode3;
	short    current_delta;
	UINT64   ReleaseID;
	unsigned int mtkVerson;
	union
	{
		struct  
		{
			unsigned short Reserved;
			unsigned short oscTrim;
			unsigned short Reserved2;
			unsigned int   Reserved3;
			unsigned char  Ic2Sensor_map[MAX_SCAP_ROW][MAX_SCAP_COL];
			unsigned char  Sensor2Ic_map[MAX_SCAP_ROW][MAX_SCAP_COL];
			unsigned short OS_test_buff[MAX_SCAP_ROW][MAX_SCAP_COL];
			unsigned short Base_test_buff[MAX_SCAP_ROW][MAX_SCAP_COL];
			short          fsd_test_buff[MAX_SCAP_ROW][MAX_SCAP_COL];
			unsigned short fsd_fast_buff[MAX_SCAP_ROW][MAX_SCAP_COL];
			unsigned short fsd_slow_buff[MAX_SCAP_ROW][MAX_SCAP_COL];

		}Scap;
		struct  
		{
			unsigned short Reserved;
			unsigned int   oscTrim;
			unsigned short Reserved2;
			unsigned int   Reserved3;
		}Mcap;
	};
	unsigned short CRC16;

public:
	RecordData()
	{
		memset(this, 0, sizeof(RecordData));
		DoInit();
	}
	void DoInit( LPCTSTR szCode = NULL )
	{
		Header[0] = 'S';
		Header[1] = 'E';
		Header[2] = 'M';
		Header[3] = 'I';
		memset(Reserve, 0, sizeof(Reserve));
		memset(snCode, 0, sizeof(snCode));

		Version = 0x0500;
		DataLen = sizeof(RecordData) - 4 - 2;
		ReleaseID = 0;

		memset( mapofResult, 0, sizeof(mapofResult) );
		copytextto( mapofResult[0].baseName, _T("os_base"), lengthof(_T("os_base")) );
		mapofResult[0].offset = (unsigned int)(unsigned long)(((RecordData*)(0))->Scap.OS_test_buff) - 0;
		mapofResult[0].size = sizeof(unsigned short) * MAX_SCAP_ROW * MAX_SCAP_COL;

		copytextto( mapofResult[1].baseName, _T("fsd_base"), lengthof(_T("fsd_base")) );
		mapofResult[1].offset = (unsigned int)(unsigned long)(((RecordData*)(0))->Scap.fsd_test_buff) - 0;
		mapofResult[1].size = sizeof(unsigned short) * MAX_SCAP_ROW * MAX_SCAP_COL;

		copytextto( mapofResult[2].baseName, _T("fsd_fast"), lengthof(_T("fsd_fast")) );
		mapofResult[2].offset = (unsigned int)(unsigned long)(((RecordData*)(0))->Scap.fsd_fast_buff) - 0;
		mapofResult[2].size = sizeof(unsigned short) * MAX_SCAP_ROW * MAX_SCAP_COL;

		copytextto( mapofResult[3].baseName, _T("fsd_slow"), lengthof(_T("fsd_slow")) );
		mapofResult[3].offset = (unsigned int)(unsigned long)(((RecordData*)(0))->Scap.fsd_slow_buff) - 0;
		mapofResult[3].size = sizeof(unsigned short) * MAX_SCAP_ROW * MAX_SCAP_COL;

		if( szCode ) memcpy_s( &snCode[0], sizeof(snCode), szCode, lengthof(szCode) * sizeof(TCHAR) );

		CRC16 = 0x1234;
	}
};
//////////////////////////////////////////////////////////////////////////

static BOOL ParseRecordV1( unsigned char* content, unsigned int len, TCHAR* szName, unsigned short (&lpMatrix)[MAX_SCAP_ROW][MAX_SCAP_COL] )
{
	RecordData_V1* pRecord = (RecordData_V1*)content;
	if( pRecord->Header[0] != 'S' || pRecord->Header[3] != 'I' ) 
		return FALSE;

	if( pRecord->Version < 0x0002 )
		return FALSE;

	bool needMapping = false;
	unsigned short* dp = NULL;
	if( 0 == icomparetext( szName, _T("os_base") ) ){
		dp = pRecord->Scap.OS_test_buff;
		needMapping = true;
	}
	else if( 0 == icomparetext( szName, _T("fsd_base") ) )
		dp = (unsigned short*)pRecord->Scap.fsd_test_buff;
	else if( 0 == icomparetext( szName, _T("fsd_fast") ) )
		dp = pRecord->Scap.fsd_fast_buff;
	else if( 0 == icomparetext( szName, _T("fsd_slow") ) )
		dp = pRecord->Scap.fsd_slow_buff;
	else
		dp = NULL;

	if( NULL == dp )  return FALSE;

	int Rows = 4, Cols = pRecord->Scap.RealSize / Rows; 
	for( int iRow = 0; iRow < Rows; iRow++ )
	{
		for( int iCol = 0; iCol < Cols; iCol++ )
		{
			int index = iRow * Cols + iCol;
			lpMatrix[iRow][iCol] = dp[needMapping ? pRecord->Scap.Sensor2Ic_map[index] : index];
		}
	}

	return TRUE;
		
}
static BOOL ParseRecordV4( unsigned char* content, unsigned int len, TCHAR* szName, unsigned short (&lpMatrix)[MAX_SCAP_ROW][MAX_SCAP_COL] )
{
	//lpMatrix = NULL;
	if( len < sizeof(RecordData) ) 
		return FALSE;

	RecordData* pRecord = (RecordData*)content;
	if( pRecord->Header[0] != 'S' || pRecord->Header[3] != 'I' ) 
		return FALSE;

	if( pRecord->Version < 0x0400 )
		return FALSE;

	ResultBaseMap* baseMap = pRecord->mapofResult;
	for( int index = 0; index < 30; index++ )
	{
		if( NULL == baseMap ) continue;
		if( 0 == icomparetext( baseMap->baseName, szName ) )
		{
			//lpMatrix = (content + baseMap->offset);
			memcpy_s( lpMatrix, sizeof(unsigned short) * MAX_SCAP_ROW * MAX_SCAP_COL, (content + baseMap->offset), baseMap->size );

			return TRUE;
		}
		baseMap++;
	}

	return FALSE;
}