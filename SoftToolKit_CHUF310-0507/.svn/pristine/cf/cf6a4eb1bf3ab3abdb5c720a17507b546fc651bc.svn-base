#include "stdafx.h"
#include "Helper.h"
#include "ProtocalStandard.h"
#include "checksum.h"
#include <stdlib.h>

#define DATA_POS_START     14
#define WORD_EVENT(ptr)    ( ((ptr)[8] << 8) | (ptr)[9] )
#define WORD_LEN(ptr)      ( ((ptr)[12] << 8) | (ptr)[13] )
#define POS_RESERVE1           10
#define POS_RESERVE2           11
#define BYTE_CHKSUM(ptr)   ( (ptr)[14] )
#define BYTE_ENDTAG1(ptr)  ( (ptr)[15] )
#define BYTE_ENDTAG2(ptr)  ( (ptr)[16] )

CProtocal* GetProtocalLikeStandard()
{
	static CProtocalStandard standard;
	return &standard;
}
CProtocalStandard::CProtocalStandard()
{
    TCHAR chName[50] = {0};
    for(int i = 0; i < MAX_DEVICE_NUM; i++)
    {
        transformat( chName, 50, _T("AMCommandEvent_%d"), i );
        m_hCommandEvent[i] = ::CreateEvent( NULL, TRUE, FALSE, chName );
        m_iCommand[i] = 0;
    }
}
CProtocalStandard::~CProtocalStandard()
{
    for(int i = 0; i < MAX_DEVICE_NUM; i++)
    {
        CloseHandle(m_hCommandEvent[i]);
        m_iCommand[i] = 0;
    }
}
unsigned char CProtocalStandard::AccountCheck( const OpParam& param )
{
	return ERROR_CODE_OK;
}
BOOL CProtocalStandard::AnalyzeRecvAndMark( const unsigned char* buffer, unsigned int len, srvMsg& mark )
{
    unsigned char  deviceNo     = 0xff;
    unsigned short commandEvent = 0xffff;
    if( len == MIN_COM_RW_LEN )
	{
        deviceNo     = buffer[POS_RESERVE1];
        commandEvent = WORD_EVENT(buffer);

        if( buffer[0] == 'F' && buffer[1] == 'T' && buffer[2] == 'R' )
		{
            unsigned char uCheckSum = caculate_check_sum_u8( (unsigned char*)buffer, MIN_COM_RW_LEN - 3 );
			if( uCheckSum == buffer[MIN_COM_RW_LEN - 3] )
			{
				if( WORD_EVENT( buffer ) == AUTO_LINE_START_TEST )
				{
					mark.type = PACKET_START_TEST;
					mark.sP0 = buffer[POS_RESERVE1];
					return FALSE;
				}
				else if( WORD_EVENT( buffer ) == AUTO_LINE_TRANSFER_SN && WORD_LEN( buffer ) == 0 )
				{
					mark.type = PACKET_USER_DATA;
					mark.sP0 = buffer[POS_RESERVE1];
					mark.sP1 = WORD_LEN( buffer );
					return FALSE;
				}
                else if( deviceNo < MAX_DEVICE_NUM && m_iCommand[deviceNo] == commandEvent )
                {
                    SetCommandEvent(deviceNo);
                    return FALSE;
                }
			}
			else
			{
				return TRUE;
			}
		}
	}

	return TRUE;
}
unsigned char CProtocalStandard::SendResultUpToServer( const OpParam& param )
{
	unsigned char writeData[4096] = {0};
    unsigned char *pData = NULL;
    int iDataLen = 0, iSubDataLen = 0;
	int iCounter = 0;
	writeData[iCounter++] = _T('F');
	writeData[iCounter++] = _T('T');
	writeData[iCounter++] = _T('S');
	writeData[iCounter++] = _T(':');
	writeData[iCounter++] = 0xff;
	writeData[iCounter++] = 0xff;
	writeData[iCounter++] = 0xff;
	writeData[iCounter++] = 0xff;
	writeData[iCounter++] = AUTO_LINE_TEST_FINISH>>8;
	writeData[iCounter++] = AUTO_LINE_TEST_FINISH>>0;
	writeData[iCounter++] = param.SendResult.pCollection->uDevice;
	writeData[iCounter++] = 0xff;
	//writeData[iCounter++] = sizeof(TransInfo_Collection) >> 8;
	//writeData[iCounter++] = sizeof(TransInfo_Collection) & 0xff;
	//memcpy_s( &writeData[iCounter], sizeof(TransInfo_Collection), param.SendResult.pCollection, sizeof(TransInfo_Collection) );
	//iCounter += sizeof(TransInfo_Collection);

    writeData[iCounter++] = 0;//total len H
    writeData[iCounter++] = 2;//Total len L
	writeData[iCounter++] = param.SendResult.pCollection->uDevice;
    writeData[iCounter++] = param.SendResult.pCollection->bTestResult;
    for(int i = 0; i <param.SendResult.pCollection->specData.packgeNum; i++)
    {   
        pData = param.SendResult.pCollection->specData.dataPackge[i].Buffer;
        iSubDataLen = param.SendResult.pCollection->specData.dataPackge[i].dataLen;
        iDataLen = (writeData[12] << 8) | writeData[13];

        if( ((iDataLen + 6 + iSubDataLen) > (4096 - 3 - 14)) )
        {
            break;
        }

        if( (iSubDataLen <= 0) || (NULL == pData) )
        {
            continue;
        }
        writeData[iCounter++] = param.SendResult.pCollection->specData.dataPackge[i].dataType >> 8;
        writeData[iCounter++] = param.SendResult.pCollection->specData.dataPackge[i].dataType >> 0;
        writeData[iCounter++] = 0xff;
        writeData[iCounter++] = 0xff;
        writeData[iCounter++] = iSubDataLen >> 8;
        writeData[iCounter++] = iSubDataLen >> 0;

        memcpy_s(writeData+iCounter, iSubDataLen, pData, iSubDataLen);
        iCounter += iSubDataLen;

        iDataLen = iDataLen + 6 + iSubDataLen;

        writeData[12] = (iDataLen >> 8) & 0xff;
        writeData[13] = iDataLen &0xff;
    }
	writeData[iCounter++] = caculate_check_sum_u8( writeData, iCounter );
	writeData[iCounter++] = _T('\r');
	writeData[iCounter++] = _T('\n');

	AutoWriteRead wr( param.context );
	wr.pWrite = writeData;
	wr.numOfWrite = iCounter;
	wr.pRead = 0;
	wr.numOfRead = 0;

	return ERROR_CODE_OK == SendDataSerialy( wr );
}
bool CProtocalStandard::NotifyTestStatus( const OpParam& param )
{
	unsigned char writeData[64] = {0};
	int iCounter = 0;
	writeData[iCounter++] = _T('F');
	writeData[iCounter++] = _T('T');
	writeData[iCounter++] = _T('S');
	writeData[iCounter++] = _T(':');
	writeData[iCounter++] = (param.NotifyStatus.testCode >> 24) & 0xff;
	writeData[iCounter++] = (param.NotifyStatus.testCode >> 16) & 0xff;
	writeData[iCounter++] = (param.NotifyStatus.testCode >> 8) & 0xff;
	writeData[iCounter++] = (param.NotifyStatus.testCode >> 0) & 0xff;
	writeData[iCounter++] = (param.NotifyStatus.status >> 8) & 0xff;
	writeData[iCounter++] = (param.NotifyStatus.status >> 0) & 0xff;
	writeData[iCounter++] = param.NotifyStatus.ucDevice;
	writeData[iCounter++] = param.NotifyStatus.result;
	writeData[iCounter++] = 0x00;
	writeData[iCounter++] = 0x00;
	writeData[iCounter++] = caculate_check_sum_u8( writeData, iCounter );
	writeData[iCounter++] = _T('\r');
	writeData[iCounter++] = _T('\n');

	AutoWriteRead wr( param.context );
	wr.pWrite = writeData;
	wr.numOfWrite = iCounter;
	wr.pRead = 0;
	wr.numOfRead = 0;

	return ERROR_CODE_OK == SendDataSerialy( wr );
}
unsigned char CProtocalStandard::OnLineDoHandShake( const OpParam& param )
{
	if( !param.context->IsConnected() )  return ERROR_CODE_DEVICE_CLOSED;

	unsigned char writeData[64] = {0};
	unsigned char readData[64] = {0};
	int iCounter = 0;
	writeData[iCounter++] = _T('F');
	writeData[iCounter++] = _T('T');
	writeData[iCounter++] = _T('S');
	writeData[iCounter++] = _T(':');
	writeData[iCounter++] = 0xff;
	writeData[iCounter++] = 0xff;
	writeData[iCounter++] = 0xff;
	writeData[iCounter++] = 0xff;
	writeData[iCounter++] = 0x00;
	writeData[iCounter++] = 0xFB;
	writeData[iCounter++] = 0xff;
	writeData[iCounter++] = 0xff;
	writeData[iCounter++] = 0x00;
	writeData[iCounter++] = 0x00;
	writeData[iCounter++] = caculate_check_sum_u8( writeData, iCounter );
	writeData[iCounter++] = _T('\r');
	writeData[iCounter++] = _T('\n');

	AutoWriteRead wr( param.context );
	wr.pWrite = writeData;
	wr.numOfWrite = iCounter;
	wr.pRead = readData;
	wr.numOfRead = iCounter;

	return SendDataSerialy( wr );
}
unsigned char CProtocalStandard::OnGetUserData( const OpParam& param )
{
	unsigned char ReCode = ERROR_CODE_OK;
	unsigned char* pReadBuffer = (unsigned char*)malloc( MIN_COM_RW_LEN );

	unsigned char writeData[64] = {0};
	int iCounter = 0;
	writeData[iCounter++] = _T('F');
	writeData[iCounter++] = _T('T');
	writeData[iCounter++] = _T('S');
	writeData[iCounter++] = _T(':');
	writeData[iCounter++] = 0xff;
	writeData[iCounter++] = 0xff;
	writeData[iCounter++] = 0xff;
	writeData[iCounter++] = 0xff;
	writeData[iCounter++] = (unsigned short)param.UserData.lparam >> 8;
	writeData[iCounter++] = (unsigned short)param.UserData.lparam & 0xff;
	writeData[iCounter++] = param.UserData.wparam;
	writeData[iCounter++] = 0xff;
	writeData[iCounter++] = 0x00;
	writeData[iCounter++] = 0x00;
	writeData[iCounter++] = caculate_check_sum_u8( writeData, iCounter );
	writeData[iCounter++] = _T('\r');
	writeData[iCounter++] = _T('\n');

	AutoWriteRead wr( param.context );
	wr.pWrite = writeData;
	wr.numOfWrite = iCounter;
	wr.pRead = pReadBuffer;
	wr.numOfRead = MIN_COM_RW_LEN;
	ReCode = SendDataSerialy( wr );

	if( ERROR_CODE_OK == ReCode )
	{
		int userLen = WORD_LEN( pReadBuffer );
		pReadBuffer = (unsigned char*)realloc( pReadBuffer, userLen + MIN_COM_RW_LEN );

		AutoWriteRead wr( param.context );
		wr.pWrite = NULL;
		wr.numOfWrite = 0;
		wr.pRead = pReadBuffer + MIN_COM_RW_LEN;
		wr.numOfRead = userLen;

		ReCode = SendDataSerialy( wr );
        if(param.UserData.wparam == pReadBuffer[10])
        {
            unsigned char uCheckSum = caculate_check_sum_u8( pReadBuffer, userLen + MIN_COM_RW_LEN - 3 );
            if( uCheckSum == pReadBuffer[userLen + MIN_COM_RW_LEN - 3] )
            {
                //*param.UserData.readed = userLen;
                //memcpy_s( param.UserData.buffer, param.UserData.lenth, pReadBuffer + DATA_POS_START, userLen );
            }
            else
            {
                ReCode = ERROR_CODE_CHECK_SUM_MISMATCH;
            }
        }
        else
        {
            ReCode = ERROR_CODE_COMM_ERROR;
        }

	}

	if( pReadBuffer ) free( pReadBuffer );

	return ReCode;
}
bool CProtocalStandard::SendUserData(const OpParam& param)
{
	unsigned char ReCode = ERROR_CODE_OK;
	//unsigned char* pReadBuffer = (unsigned char*)malloc( MIN_COM_RW_LEN );

	//unsigned char* writeData = (unsigned char*)malloc( MIN_COM_RW_LEN +  param.UserData.lparam);
	//int iCounter = 0;
	//writeData[iCounter++] = _T('F');
	//writeData[iCounter++] = _T('T');
	//writeData[iCounter++] = _T('S');
	//writeData[iCounter++] = _T(':');
	//writeData[iCounter++] = 0xff;
	//writeData[iCounter++] = 0xff;
	//writeData[iCounter++] = 0xff;
	//writeData[iCounter++] = 0xff;
	//writeData[iCounter++] = (unsigned short)param.UserData.lparam >> 8;
	//writeData[iCounter++] = (unsigned short)param.UserData.lparam & 0xff;
	//writeData[iCounter++] = param.UserData.wparam;
	//writeData[iCounter++] = 0xff;
	//writeData[iCounter++] = param.UserData.lparam >> 8;
	//writeData[iCounter++] = param.UserData.lparam & 0xff;
	//for(int index = 0; index < param.UserData.lparam; index++)
	//{
 //       //writeData[iCounter++] = param.UserData.buffer[index];
	//}
	//writeData[iCounter++] = caculate_check_sum_u8( writeData, iCounter );
	//writeData[iCounter++] = _T('\r');
	//writeData[iCounter++] = _T('\n');

	//AutoWriteRead wr( param.context );
	//wr.pWrite = writeData;
	//wr.numOfWrite = iCounter;
	//wr.pRead = NULL;
	//wr.numOfRead = 0;
	//ReCode = SendDataSerialy( wr );

	//if( writeData ) free( writeData );

	return ERROR_CODE_OK == ReCode;
}
bool CProtocalStandard::SendAckPacket( const OpParam& param )
{
    unsigned char ReCode = ERROR_CODE_OK;
	unsigned char writeData[64] = {0};

	int iCounter = 0;
	writeData[iCounter++] = _T('F');
	writeData[iCounter++] = _T('T');
	writeData[iCounter++] = _T('S');
	writeData[iCounter++] = _T(':');
	writeData[iCounter++] = 0xff;
	writeData[iCounter++] = 0xff;
	writeData[iCounter++] = 0xff;
	writeData[iCounter++] = 0xff;
	writeData[iCounter++] = ~(param.Ack.packetType >> 8);
	writeData[iCounter++] = ~(param.Ack.packetType & 0xff);
	writeData[iCounter++] = param.Ack.ucDevice;
	writeData[iCounter++] = 0xff;
	writeData[iCounter++] = 0;
	writeData[iCounter++] = 0;
	writeData[iCounter++] = caculate_check_sum_u8( writeData, iCounter );
	writeData[iCounter++] = _T('\r');
	writeData[iCounter++] = _T('\n');

	AutoWriteRead wr( param.context );
	wr.pWrite = writeData;
	wr.numOfWrite = iCounter;
	wr.pRead = NULL;
	wr.numOfRead = 0;
	bool bRet = ERROR_CODE_OK == SendDataSerialy( wr );

	return bRet;
}
bool CProtocalStandard::ReceiveAckPacket( const OpParam& param )
{
    int iRet = ERROR_CODE_OK;
	unsigned char buffer[64] = {0};

	AutoWriteRead wr( param.context );
	wr.pWrite = 0;
	wr.numOfWrite = 0;
	wr.pRead = buffer;
	wr.numOfRead = 17;
	iRet = SendDataSerialy( wr );

	unsigned char ackDevice = buffer[POS_RESERVE1];
	unsigned short ackEvent = ~WORD_EVENT(buffer);
	if( param.Ack.ucDevice == ackDevice && param.Ack.packetType == ackEvent )
	{
	}
	else
	{
        iRet = ERROR_CODE_CHECK_SUM_MISMATCH;
	}

	return ERROR_CODE_OK == iRet;
}
unsigned char CProtocalStandard::SendDataSerialy( const AutoWriteRead& wr )
{
	int iRet = ERROR_CODE_OK;
	if( wr.numOfWrite )
	{
		wr.context->HalClearDataQueueData();

		if( iRet == ERROR_CODE_OK )
			iRet = wr.context->Write( wr.pWrite, wr.numOfWrite );  
	}
	if( wr.numOfRead )
	{
		if( iRet == ERROR_CODE_OK )
			iRet = wr.context->Read( wr.pRead, wr.numOfRead );
	}

	return iRet;
}

unsigned int CProtocalStandard::ResetCommandEvent( unsigned char ucDevice, unsigned int iCommandEvent )
{
    if(ucDevice > MAX_DEVICE_NUM) return ERROR_CODE_OK;

    ResetEvent(m_hCommandEvent[ucDevice]);
    m_iCommand[ucDevice] = iCommandEvent;
    return ERROR_CODE_OK;
}

unsigned int CProtocalStandard::WaitCommandEvent( unsigned char ucDevice, unsigned int iCommandEvent ,unsigned int iwaitTime)
{
    if(ucDevice > MAX_DEVICE_NUM) return ERROR_CODE_OK;

    return WaitForSingleObject(m_hCommandEvent[ucDevice], iwaitTime);
}

unsigned int CProtocalStandard::SetCommandEvent( unsigned char ucDevice, unsigned int iCommandEvent )
{
    if(ucDevice > MAX_DEVICE_NUM) return ERROR_CODE_OK;

    SetEvent(m_hCommandEvent[ucDevice]);
    return ERROR_CODE_OK;
}