// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include "MiniDump.h"

LONG WINAPI SMUnhandledExceptionFilter(PEXCEPTION_POINTERS pExceptionInfo)
{
	CreateMiniDump( pExceptionInfo, "SmTest-Exception.dmp" );

	exit(pExceptionInfo->ExceptionRecord->ExceptionCode);

	return EXCEPTION_EXECUTE_HANDLER;  // 程序停止运行
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		 SetUnhandledExceptionFilter(SMUnhandledExceptionFilter);
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

