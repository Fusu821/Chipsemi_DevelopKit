#include "stdafx.h"
#include "Helper.h"
#include "ProtocalHXD.h"
#include <stdlib.h>

CProtocal* GetProtocalHXD()
{
    static class CProtocalHXD proHXD;
    return &proHXD;
}
CProtocalHXD::CProtocalHXD()
{

}
CProtocalHXD::~CProtocalHXD()
{

}

unsigned char CProtocalHXD::SendResultUpToServer( const OpParam& param ) 
{
	unsigned char iReCode = ERROR_CODE_OK;

	return iReCode;
}

bool CProtocalHXD::ResponseOk( TCHAR* szContent, unsigned short len, int tag )
{
// 	bool rsp_ok = false;
// 
// 	if(NULL != findtext(szContent, "DONE"))
// 		rsp_ok = true;
// 	
// 	return rsp_ok;

	for(int index = 0; index < 2; index++)
	{
		if(TRUE == m_bWaitRsp) break;
		Sleep(3);
	}

	return true;
}

unsigned char CProtocalHXD::SendDataSerialy( const AutoWriteRead& wr )
{
    int iRet = ERROR_CODE_OK;
    if( wr.numOfWrite )
    {
		m_bWaitRsp = FALSE;
        //wr.context->HalClearDataQueueData();

        if( iRet == ERROR_CODE_OK )
            iRet = wr.context->Write( wr.pWrite, wr.numOfWrite );  
    }
    if( wr.numOfRead )
    {
        //if( iRet == ERROR_CODE_OK )
        //    iRet = wr.context->Read( wr.pRead, wr.numOfRead, (unsigned int*)&wr.numOfReaded );
    }

	LogIt(wr);

    return iRet;
}


void CProtocalHXD::LogIt(const AutoWriteRead& wr)
{
	int log_size_t = 256;
	TCHAR* szLog = new TCHAR[log_size_t];

	if( wr.numOfWrite )
	{
		copytextto( szLog, log_size_t, _T("WriteData: "), lengthof(_T("WriteData: ")) );
		CHAR* pByte = (CHAR*)wr.pWrite;

		copytextappend( szLog, log_size_t, pByte );
		if( logInfo.forceLog ) (*logInfo.forceLog)( _T("SrvLog"), szLog );
	}
	if( wr.numOfReaded )
	{
		copytextto( szLog, log_size_t, _T("ReadData:  "), lengthof(_T("ReadData:  ")) );
		CHAR* pByte = (CHAR*)wr.pRead;

		copytextappend( szLog, log_size_t, pByte );
		if( logInfo.forceLog ) (*logInfo.forceLog)( _T("SrvLog"), szLog );
	}

	delete[] szLog;
}

void CProtocalHXD::LogItEx(const AutoWriteRead& wr)
{
	int log_size_t = 256;
	TCHAR* szLog = new TCHAR[log_size_t];

	if( wr.numOfReaded )
	{
		copytextto( szLog, log_size_t, _T("ReadData:  "), lengthof(_T("ReadData:  ")) );
		CHAR* pByte = (CHAR*)wr.pRead;

		copytextappend( szLog, log_size_t, pByte );
		if( logInfo.forceLog ) (*logInfo.forceLog)( _T("SrvLog"), szLog );
	}

	if( wr.numOfWrite )
	{
		copytextto( szLog, log_size_t, _T("WriteData: "), lengthof(_T("WriteData: ")) );
		CHAR* pByte = (CHAR*)wr.pWrite;

		copytextappend( szLog, log_size_t, pByte );
		if( logInfo.forceLog ) (*logInfo.forceLog)( _T("SrvLog"), szLog );
	}

	delete[] szLog;
}

unsigned char CProtocalHXD::OnLine( const OpParam& param )  
{
	if(NULL == param.context) return ERROR_CODE_NO_DEVICE;

	return ERROR_CODE_OK;
}

unsigned char CProtocalHXD::LogOffMessage( const OpParam& param )
{
	unsigned char ReCode = ERROR_CODE_OK;

	char msg[MAX_PATH] = {0};
	char rsp[MAX_PATH] = {0};

	if(TEST_PASS == param.LogOff.result)
		transformat(msg, MAX_PATH, _T("FTRESULT:DEV%d,%s;\r\n"), param.LogOff.nDevice + 1, _T("PASS"));
	else
		transformat(msg, MAX_PATH, _T("FTRESULT:DEV%d,%s;\r\n"), param.LogOff.nDevice + 1, _T("FAIL"));

	AutoWriteRead wr( param.context );
	wr.pWrite = (unsigned char*)msg;
	wr.numOfWrite = lengthof(msg);
	wr.pRead = (unsigned char*)rsp;
	//wr.numOfRead = sizeof(rsp);
	wr.numOfRead = 0;
	wr.numOfReaded = 0;

	if(is_success_likely(SendDataSerialy( wr )))
	{
		if(ResponseOk( rsp, lengthof(rsp), 1 ))
		{

		}
		else
		{
			::Sleep( 500 );
			if(is_success_likely(SendDataSerialy( wr )))
			{
				if(ResponseOk( rsp, lengthof(rsp), 1 ))
				{

				}
				else
				{
					transformat(m_szMsg, sizeof(m_szMsg), _T("rsponse error, message = \r\n%s"), (LPCTSTR)rsp);
					ReCode = ERROR_CODE_CHECK_RESPONSE_FAILED;
				}
			}
		}
	}
	else
	{
		transformat(m_szMsg, sizeof(m_szMsg), _T("communication error"));
		ReCode = ERROR_CODE_COMM_ERROR;
	}

	return ReCode;
}

unsigned char CProtocalHXD::ActionToOnLineMessage(const OpParam& param)
{
	unsigned char ReCode = ERROR_CODE_OK;
	if(NULL == param.context || NULL == param.UserData.pcallBack) return ERROR_CODE_NO_DEVICE;

	char msg[MAX_PATH] = {0};
	char rsp[MAX_PATH] = {0};
	char szTemp[20] = {0};
	memset(msg, 0, sizeof(msg));

	if(param.UserData.lparam > 0)
	{
		unsigned int readed = 0;
		if(is_success_likely(param.context->Read((unsigned char*)rsp, MAX_PATH, &readed)))
		{
			if(NULL != findtext(rsp, "STATUS?"))
			{
				transformat(szTemp, 20, "STATUS:");
				copytextto(msg, MAX_PATH, szTemp, lengthof(szTemp));
				for(int index = 0; index < MAX_DEVICE_NUM; index++)
				{
					if(param.UserData.pcallBack->CheckReadyForTest( index ))
					{
						transformat(szTemp, 20, "DEV%d,%s;", index + 1, "OK");
						copytextappend(msg, MAX_PATH, szTemp);
					}
					else
					{
						transformat(szTemp, 20, "DEV%d,%s;", index + 1, "NC");
						copytextappend(msg, MAX_PATH, szTemp);
					}
				}

				copytextappend(msg, MAX_PATH, "\r\n");
				param.context->Write( (unsigned char*)msg, lengthof(msg) );
			}
			if(NULL != findtext(rsp, "STARTFT:"))
			{
				transformat(szTemp, 20, "STARTFT:");
				copytextto(msg, MAX_PATH, szTemp, lengthof(szTemp));

				char* szPos = findtext(rsp, "STARTFT:") + lengthof("STARTFT:");
				char szSN[20]  = {0};
				for(int index = 0; index < MAX_DEVICE_NUM; index++)
				{
					memset(szSN, 0, sizeof(szSN));
					szPos = findtext(szPos, "DEV");
					if(NULL == szPos) break;
					szPos += lengthof("DEV");
					char nDevice = *szPos - '1';

					szPos++;
					if(*szPos == ',' )
					{
						szPos++;

						for(int iter = 0; iter < sizeof(szSN); iter++)
						{
							if(*szPos == ';') break;
							szSN[iter] = *szPos;

							szPos++;
						}
					}

					if(0 == param.UserData.pcallBack->StartTest( nDevice, szSN ))
					{
						transformat(szTemp, 20, "DEV%d,%s;", nDevice + 1, "DONE");
						copytextappend(msg, MAX_PATH, szTemp);
					}
					else
					{
						transformat(szTemp, 20, "DEV%d,%s;", nDevice + 1, "ERR");
						copytextappend(msg, MAX_PATH, szTemp);
					}
				}

				copytextappend(msg, MAX_PATH, "\r\n");
				param.context->Write( (unsigned char*)msg, lengthof(msg) );
			}
			if(NULL != findtext(rsp, "FTRESULT:"))
			{
				m_bWaitRsp = TRUE;
			}
		}

		AutoWriteRead wr( param.context );
		wr.pWrite = (unsigned char*)msg;
		wr.numOfWrite = lengthof(msg);
		wr.pRead = (unsigned char*)rsp;
		wr.numOfReaded = readed;

		LogItEx( wr );
	}

	return ReCode;
}

BOOL CProtocalHXD::AnalyzeRecvAndMark( const unsigned char* buffer, unsigned int len, srvMsg& mark )
{
	if(len > 0)
	{
		mark.type = PACKET_USER_DATA;
		mark.sP0 = 0;
		mark.sP1 = len;
		return TRUE;
	}

    return TRUE;
}
