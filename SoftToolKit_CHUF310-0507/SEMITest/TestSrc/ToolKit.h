#pragma once
#include "Macro.h"
class CToolKit
{
public:
	CToolKit();
	virtual ~CToolKit();

public: 
	//the function below can not be used in multi-thread work
	static LPCTSTR GetExecutePath(int deepth = 2);

	static char* Wide2MultiBytes( const wchar_t* wsz, char* multiBuffer, int len );

	static wchar_t* MultiBytes2Wide( const char* msz, wchar_t* wideBuffer, int len );
	//static string Wide2MultiBytes( const tstring& input );

	static TCHAR* UTF8ToGBK( const char *szIn, TCHAR* mutiBuffer, int len );
};