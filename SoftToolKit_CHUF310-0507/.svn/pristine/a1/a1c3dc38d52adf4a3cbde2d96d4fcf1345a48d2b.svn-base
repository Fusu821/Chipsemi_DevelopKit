#include "helper.h"

LoopTicker::LoopTicker(int maxTick)
	:m_tickTime( maxTick )
{

}
LoopTicker::~LoopTicker()
{

}
bool LoopTicker::TickOnce()
{
	return ( --m_tickTime ) > 0;
}
bool LoopTicker::CheckTickAndMark( unsigned int& iResult )
{
	//ERROR_CODE_LOOP_BEYOND_MAX_RETRY = 0x0001 

	if( m_tickTime > 0 )
		iResult = iResult;
	else
		iResult = 0x0001;

	return m_tickTime > 0;
}
int LoopTicker::TimeLeft()
{
	return m_tickTime;
}



// void ReShappingData( unsigned short (&dataMappinged)[MAX_MCAP_ROW][MAX_MCAP_COL], unsigned short* dataToShapping, unsigned int dataCnt, unsigned short maxRows, unsigned short maxCols )
// {
// 
// }
// void ReShappingData( unsigned short (&dataMappinged)[MAX_SCAP_ROW][MAX_SCAP_COL], unsigned short* dataToShapping, unsigned int dataCnt, unsigned short maxRows, unsigned short maxCols )
// {
// }
// void ReShappingData( unsigned short (&dataMappinged)[MAX_SCAP_ROW][MAX_SCAP_COL], unsigned short* dataToShapping, unsigned int dataCnt, unsigned short maxRows, unsigned char* pCols )
// {
// 	int index = 0;
// 	memset( dataMappinged, 0, sizeof(dataMappinged) );
// 
// 	for( int iRow = 0; iRow < maxRows; iRow++ )
// 	{
// 		for( int iCol = 0; iCol < (int)pCols[iRow]; iCol++ )
// 		{
// 			if( index >= (int)dataCnt )   continue;
// 
// 			dataMappinged[iRow][iCol] = dataToShapping[index];
// 
// 			index += 1;
// 		}
// 	}
// }
// void CopyAndInvalid( unsigned char (&invalidCopy)[MAX_SCAP_ROW][MAX_SCAP_COL], const unsigned char (&invalid)[MAX_SCAP_ROW][MAX_SCAP_COL], int invalidRow /*= MAX_SCAP_ROW*/, int invalidCol /*= MAX_SCAP_COL*/ )
// {
// 	memcpy_s( invalidCopy, sizeof(invalidCopy), invalid, sizeof(invalid) );
// 
// 	if( (invalidRow >= 0) && (invalidRow < MAX_SCAP_ROW) )
// 	{
// 		for( int iCol = 0; iCol < MAX_SCAP_COL; iCol++ )
// 		{
// 			invalidCopy[invalidRow][iCol] = NODE_INVALID_TYPE;
// 		}
// 	}
// 	if( (invalidCol >= 0) && (invalidCol < MAX_SCAP_COL) )
// 	{
// 		for( int iRow = 0; iRow < MAX_SCAP_ROW; iRow++ )
// 		{
// 			invalidCopy[iRow][invalidCol] = NODE_INVALID_TYPE;
// 		}
// 	}
// }
int PrintNodeValue( IN ColorText& text, NodeVal* nodeList,  LPCTSTR strHeader/* = NULL*/, int iPrecision/* = 0*/  )
{
	if( NULL == nodeList ) return 0;
	int iCount = 0;
	tstring strPrintMessage = _T("");
	if( strHeader ) 
		strPrintMessage += strHeader; 

	TCHAR strTemp[128] = {0}, strValue[20] = {0}, strCompare[20] = {0}, strFormat[20] = {};
	for ( NodeVal* node = nodeList->Next; node != NULL; node = node->Next )
	{
		++iCount;
		transformat( strFormat, _T("%%.%df"), iPrecision );
		transformat( strValue, strFormat, node->Value );
		transformat( strCompare, strFormat, node->compareValue );
		transformat( strTemp, _T("Point(%-2d,%-2d): %5s(%s%4s)	"), 
			node->iRow, node->iCol, strValue, 
			node->errorType == NodeVal::NODE_GRATER ? _T(">") : _T("<"), 
			strCompare );
		strPrintMessage += strTemp;
		if( 0 == ( iCount % 3 ) )  strPrintMessage += _T("\r\n");
	}
	if( iCount > 0 )
	{
		strPrintMessage += _T("\r\n");
		text += strPrintMessage;
	}

	return iCount;
}
int PrintBaseNodeValue( IN ColorText& text, NodeVal* nodeList,  LPCTSTR strHeader/* = NULL*/, int iPrecision/* = 0*/  )
{
	if( NULL == nodeList ) return 0;
	int iCount = 0;
	tstring strPrintMessage = _T("");
	if( strHeader ) 
		strPrintMessage += strHeader; 

	TCHAR strTemp[128] = {0}, strValue[20] = {0}, strCompare[20] = {0}, strFormat[20] = {};
	for ( NodeVal* node = nodeList->Next; node != NULL; node = node->Next )
	{
		++iCount;
		transformat( strFormat, _T("%%.%df"), iPrecision );
		transformat( strValue, strFormat, node->Value );
		transformat( strCompare, strFormat, node->compareValue );
		if (node->errorType == NodeVal::NODE_NODE33)
		{
			transformat( strFormat, _T("%s"), ("node3*3 "));
		}
		else if(node->errorType == NodeVal::NODE_NODE55)
		{
			transformat( strFormat, _T("%s"), ("node5*5 "));
		}
		else if(node->errorType == NodeVal::NODE_ALL)
		{
			transformat( strFormat, _T("%s"), ("all "));
		}
		transformat( strTemp, _T("Point(%-2d,%-2d): %5s(%s%4s)	"), 
			node->iRow, node->iCol, strValue, 
			strFormat, 
			strCompare );
		strPrintMessage += strTemp;
		if( 0 == ( iCount % 3 ) )  strPrintMessage += _T("\r\n");
	}
	if( iCount > 0 )
	{
		strPrintMessage += _T("\r\n");
		text += strPrintMessage;
	}

	return iCount;
}
int JudgeNodeOutRangeAgain( IN ColorText& text, NodeVal* nodeList, LPCTSTR strHeader, unsigned short RanksNum, unsigned short MaxNum, unsigned short OverrunRatio )
{
	if( NULL == nodeList ) return 0;
	int iCount = 0,ret=0,OverrunCount=0;
	tstring strPrintMessage = _T("");
	if( strHeader ) 
		strPrintMessage += strHeader; 

	TCHAR strTemp[128] = {0}, strValue[20] = {0}, strCompare[20] = {0}, strFormat[20] = {};
	unsigned char info[50][50]={0};

	bool OverrunRanksNum = false;
	for ( NodeVal* node = nodeList->Next; node != NULL; node = node->Next )
	{
		++iCount;

		info[(node->iRow-1)][(node->iCol-1)] = 1;

		double pmax = (node->compareValue*(100+OverrunRatio))/100;
		double pmin = (node->compareValue*(100-OverrunRatio))/100;
		if(node->Value >pmax||node->Value < pmin)
		{
			OverrunCount++;
			node->errorType = node->Value >pmax ? NodeVal::NODE_GRATER :NodeVal::NODE_SMALLER;
			transformat( strFormat, _T("%%.%df"), 0 );
			transformat( strValue, strFormat, node->Value );
			transformat( strCompare, strFormat, node->errorType==NodeVal::NODE_GRATER ? pmax : pmin);
			transformat( strTemp, _T("Point(%-2d,%-2d): %5s(%s%4s)	"), 
				node->iRow, node->iCol, strValue, 
				node->errorType == NodeVal::NODE_GRATER ? _T(">") : _T("<"), 
				strCompare );

			strPrintMessage += strTemp;
			if( 0 == ( OverrunCount % 3 ) )  strPrintMessage += _T("\r\n");
		}	
	}
	RanksNum = RanksNum>20 ? 20 : RanksNum;

	for (int iRow = 0;(iRow < 50)&&(OverrunRanksNum==false); iRow ++)
	{
		for (int iCol = 0;iCol < 50-(RanksNum+1); iCol ++)
		{
			unsigned char sum = 0;

			for(int i = 0; i < RanksNum+1; i ++)
			{	
				sum += info[iRow][iCol+i];
				if (sum > RanksNum)
				{
					OverrunRanksNum = true;
					break;
				}
			}

			if(OverrunRanksNum==true) break;
		}

		if(OverrunRanksNum==true) break;
	}

	for (int iCol = 0;iCol < 50&&(OverrunRanksNum==false); iCol ++)
	{
		for (int iRow = 0;iRow < 50-(RanksNum+1); iRow ++)
		{
			unsigned char sum = 0;

			for(int i = 0; i < RanksNum+1; i ++)
			{
				sum += info[iRow+i][iCol];
				if (sum > RanksNum)
				{
					OverrunRanksNum = true;
					break;
				}
			}

			if(OverrunRanksNum==true) break;
		}

		if(OverrunRanksNum==true) break;
	}

	if( iCount > 0 )
	{
		strPrintMessage += _T("\r\n");
	}
	if ((OverrunRanksNum == true) && (ret == 0))
	{
		strPrintMessage += _T("Exceeding Max Ranks Number\r\n");
		ret++;
	}
	if(iCount>MaxNum && (ret == 0))
	{
		strPrintMessage += _T("Exceeding Max Number\r\n");
		ret++;
	}
	if(OverrunCount > 0 && (ret == 0))
	{
		ret++;
	}
	if(ret == 0)
	{
		strPrintMessage += _T("Judge MCap RawData Again Pass\r\n");
	}

	text += strPrintMessage;

	return ret;
}

#ifndef _MSC_VER
void GetLocalTime(SYSTEMTIME* time)
{
	timespec times;
	tm nowTime;

	clock_gettime(CLOCK_REALTIME, &times);
	localtime_r(&times.tv_sec, &nowTime);

	time->wYear  = nowTime.tm_year + 1900;
	time->wMonth = nowTime.tm_mon + 1;
	time->wDay   = nowTime.tm_mday;
	time->wHour  = nowTime.tm_hour;
	time->wMinute  = nowTime.tm_min;
	time->wSecond = nowTime.tm_sec;
}

unsigned long GetTickCount()
{
    struct timespec ts;

    clock_gettime(CLOCK_MONOTONIC, &ts);

    return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}
void Sleep(unsigned int ms)
{
    usleep(ms * 1000);
}
#endif