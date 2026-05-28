#include "stdafx.h"
#include "Helper.h"
#include "ProtocalEDO.h"
#include <stdlib.h>

CProtocal* GetProtocalEDO()
{
    static class CProtocalEDO proEDO;
    return &proEDO;
}
CProtocalEDO::CProtocalEDO()
	:m_HalTclServerInterface(NULL)
{

}
CProtocalEDO::~CProtocalEDO()
{

}

bool CProtocalEDO::Initalize( LinkParam& param )
{
	typedef IHalServiceInterface* ( *funAllocInterface )(  );

	HMODULE hDllLib = ::LoadLibrary( _T("HalTcpServerSrv.dll") );
	funAllocInterface fun = (funAllocInterface)::GetProcAddress( hDllLib, "AllocateHalSrvInterface" );
	if( fun )  m_HalTclServerInterface = (*fun)();

	if( m_HalTclServerInterface )
	{
		//m_HalServiceInterface->RegistAnalyzer( dynamic_cast<IComplexHalListener*>(this) );
		return ERROR_CODE_OK == m_HalTclServerInterface->HalTryAttachLink( PARAM_MARK_RESERVED, NULL, param.tcp.nport );
	}

	return false;
}

void CProtocalEDO::UnInitalize()
{
	typedef void ( *funRestoreInterface )( IHalServiceInterface*& ptr );

	if( m_HalTclServerInterface ) m_HalTclServerInterface->HalTryDetachLink( PARAM_MARK_RESERVED );

	HMODULE hDllLib = ::LoadLibrary( _T("HalTcpServerSrv.dll") );
	funRestoreInterface fun = (funRestoreInterface)::GetProcAddress( hDllLib, "RestoreHalSrvInterface" );
	if( fun ) (*fun)( m_HalTclServerInterface );
}

bool CProtocalEDO::ResponseOk( TCHAR* szContent, unsigned short len, int tag )
{
	bool rsp_ok = false;

	TCHAR* rsp_pos = szContent;
	while (tag-- >= 0 && nullptr != rsp_pos)
		rsp_pos = findtext( rsp_pos + 1, _T("[") );

	if(rsp_pos)
	{
		rsp_pos++;
		rsp_ok = true;
		for(int index = 0; index < 10; index++, rsp_pos++)
		{
			if(*rsp_pos == ']') break;
			if(*rsp_pos == ' ') continue;
			if(*rsp_pos != '0') rsp_ok = false;
		}
	}
	
	return rsp_ok;
}

unsigned char CProtocalEDO::SendDataSerialy( const AutoWriteRead& wr )
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
        if( iRet == ERROR_CODE_OK && m_HalTclServerInterface )
            iRet = m_HalTclServerInterface->Read( wr.pRead, wr.numOfRead, (unsigned int*)&wr.numOfReaded );
    }

	LogIt(wr);

    return iRet;
}

void CProtocalEDO::LogIt(const AutoWriteRead& wr)
{
	int log_size_t = 256;
	TCHAR* szLog = new TCHAR[log_size_t];

	if( wr.numOfWrite )
	{
		copytextto( szLog, log_size_t, _T("WriteData: "), lengthof(_T("WriteData: ")) );
		BYTE* pByte = (BYTE*)wr.pWrite;

		for ( int index = 0; index < (int)wr.numOfWrite; ++index )
		{
			TCHAR chTemp[6] = {0};
			transformat( chTemp, _T("%c"), (char)(*(pByte+index)) );
			copytextappend( szLog, log_size_t, chTemp );
		}
		if( logInfo.forceLog ) (*logInfo.forceLog)( _T("SrvLog"), szLog );
	}
	if( wr.numOfReaded )
	{
		copytextto( szLog, log_size_t, _T("ReadData:  "), lengthof(_T("ReadData:  ")) );
		BYTE* pByte = (BYTE*)wr.pRead;

		for ( int index = 0; index < (int)wr.numOfReaded; ++index )
		{
			TCHAR chTemp[6] = {0};
			transformat( chTemp, _T("%c"), (char)(*(pByte+index)) );
			copytextappend( szLog, log_size_t, chTemp );
		}

		if( logInfo.forceLog ) (*logInfo.forceLog)( _T("SrvLog"), szLog );
	}

	delete[] szLog;
}

unsigned char CProtocalEDO::OnLine( const OpParam& param )  
{
	unsigned char ReCode = ERROR_CODE_OK;

	char msg[MAX_PATH] = {0};
	char rsp[MAX_PATH] = {0};

	transformat(msg, MAX_PATH, _T("{%s}{EH17}{[%s]}{END}"), param.SwitchMode.lineID, param.SwitchMode.option ? "ONLINE" : "OFFLINE");
	AutoWriteRead wr( param.context );
	wr.pWrite = (unsigned char*)msg;
	wr.numOfWrite = lengthof(msg);
	wr.pRead = (unsigned char*)rsp;
	wr.numOfRead = sizeof(rsp);

	if(is_success_likely(SendDataSerialy( wr )))
	{
		if(ResponseOk( rsp, lengthof(rsp), 0 ))
		{
			
		}
		else
		{
			transformat(m_szMsg, sizeof(m_szMsg), _T("rsponse error, message = \r\n%s"), (LPCTSTR)rsp);
			ReCode = ERROR_CODE_CHECK_RESPONSE_FAILED;
		}
	}
	else
	{
		transformat(m_szMsg, sizeof(m_szMsg), _T("communication error"));
		ReCode = ERROR_CODE_COMM_ERROR;
	}

	return ReCode;
}

unsigned char CProtocalEDO::AccountCheck( const OpParam& param )
{
	unsigned char ReCode = ERROR_CODE_OK;

	char msg[MAX_PATH] = {0};
	char rsp[MAX_PATH] = {0};

	transformat(msg, MAX_PATH, _T("{%s}{EH04}{[%s][%s]}{END}"), param.AccountCheck.lineID, param.AccountCheck.account, param.AccountCheck.password);
	AutoWriteRead wr( param.context );
	wr.pWrite = (unsigned char*)msg;
	wr.numOfWrite = lengthof(msg);
	wr.pRead = (unsigned char*)rsp;
	wr.numOfRead = sizeof(rsp);

	if(is_success_likely(SendDataSerialy( wr )))
	{
		if(ResponseOk( rsp, lengthof(rsp), 0 ))
		{
			//m_szLineID = tstring(param.SwitchMode.lineID);
			m_szAccount = tstring(param.AccountCheck.account);
			m_szPassword = tstring(param.AccountCheck.password);
		}
		else
		{
			transformat(m_szMsg, sizeof(m_szMsg), _T("rsponse error, message = \r\n%s"), (LPCTSTR)rsp);
			ReCode = ERROR_CODE_CHECK_RESPONSE_FAILED;
		}
	}
	else
	{
		transformat(m_szMsg, sizeof(m_szMsg), _T("communication error"));
		ReCode = ERROR_CODE_COMM_ERROR;
	}

	return ReCode;
}

unsigned char CProtocalEDO::LogOnMessage( const OpParam& param )
{
	unsigned char ReCode = ERROR_CODE_OK;

	char msg[MAX_PATH] = {0};
	char rsp[MAX_PATH] = {0};

	transformat(msg, MAX_PATH, _T("{%s}{EH62}{[%s][%s]}{END}"), param.LogOn.lineID, param.LogOn.pannelID, m_szAccount.c_str());
	AutoWriteRead wr( param.context );
	wr.pWrite = (unsigned char*)msg;
	wr.numOfWrite = lengthof(msg);
	wr.pRead = (unsigned char*)rsp;
	wr.numOfRead = sizeof(rsp);

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
	else
	{
		transformat(m_szMsg, sizeof(m_szMsg), _T("communication error"));
		ReCode = ERROR_CODE_COMM_ERROR;
	}

	return ReCode;
}

unsigned char CProtocalEDO::LogOffMessage( const OpParam& param )
{
	unsigned char ReCode = ERROR_CODE_OK;

	char msg[MAX_PATH] = {0};
	char rsp[MAX_PATH] = {0};

	if(TEST_PASS == param.LogOff.result)
		transformat(msg, MAX_PATH, _T("{%s}{EH30}{[%s][%s][1][2][][%s]}{END}"), param.LogOff.lineID, param.LogOff.pannelID, _T("OK"), m_szAccount.c_str());
	else
		transformat(msg, MAX_PATH, _T("{%s}{EH30}{[%s][%s][2][3][ABC58,R,ABC]}{END}"), param.LogOff.lineID, param.LogOff.pannelID, _T("NG"));

	AutoWriteRead wr( param.context );
	wr.pWrite = (unsigned char*)msg;
	wr.numOfWrite = lengthof(msg);
	wr.pRead = (unsigned char*)rsp;
	wr.numOfRead = sizeof(rsp);

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
	else
	{
		transformat(m_szMsg, sizeof(m_szMsg), _T("communication error"));
		ReCode = ERROR_CODE_COMM_ERROR;
	}

	return ReCode;
}

BOOL CProtocalEDO::AnalyzeRecvAndMark( const unsigned char* buffer, unsigned int len, srvMsg& mark )
{
    return TRUE;
}
