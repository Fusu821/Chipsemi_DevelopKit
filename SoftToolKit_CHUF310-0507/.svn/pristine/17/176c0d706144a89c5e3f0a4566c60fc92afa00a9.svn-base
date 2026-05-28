#pragma once

#include <windows.h>

#include <imagehlp.h>

#include <stdlib.h>

#pragma comment(lib, "dbghelp.lib")


inline void CreateMiniDump(EXCEPTION_POINTERS* pep, LPCTSTR strFileName)

{

  HANDLE hFile = CreateFile(strFileName, GENERIC_READ | GENERIC_WRITE,

     0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

 

  if((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE))

  {
	  MINIDUMP_EXCEPTION_INFORMATION dumpInfo;  
	  dumpInfo.ExceptionPointers = pep;  
	  dumpInfo.ThreadId = GetCurrentThreadId();  
	  dumpInfo.ClientPointers = TRUE;  

	  // 写入Dump文件内容  
	  //  
	  MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hFile, MiniDumpNormal, &dumpInfo, NULL, NULL );

      CloseHandle(hFile);

  }

}