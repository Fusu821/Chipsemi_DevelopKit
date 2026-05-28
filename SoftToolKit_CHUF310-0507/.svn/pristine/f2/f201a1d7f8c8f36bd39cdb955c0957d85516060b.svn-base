#include "ToolKit.h"
#ifdef _MSC_VER
#include <tchar.h>
#else
#include <string>
#endif

CToolKit::CToolKit()
{

}
CToolKit::~CToolKit()
{

}
LPCTSTR CToolKit::GetExecutePath(int deepth/* = 2*/)
{
	static TCHAR chPath[MAX_PATH] = {0};

#ifdef _MSC_VER
	::GetModuleFileName( GetModuleHandle( _T("SEMITest.dll") ), chPath, MAX_PATH );
	while(deepth--)
	{
		*(_tcsrchr( chPath, _T('\\') )) = 0;
	}
#else
	copytextto( chPath, "data/data/com.chsc.semitouchtester", lengthof("data/data/com.chsc.semitouchtester") );
#endif

	return chPath;
}
char* CToolKit::Wide2MultiBytes( const wchar_t* wsz, char* multiBuffer, int len )
{
#ifdef _MSC_VER
	int width = wcslen( wsz );
	len = min( len - 1, width );
	WideCharToMultiByte( CP_ACP, 0, (LPCWSTR)wsz, -1, multiBuffer, len, NULL, NULL );
	multiBuffer[len] = 0;
#else
	//copytextto(multiBuffer, wsz, lengthof(wsz));
#endif
	return multiBuffer;
}
wchar_t* CToolKit::MultiBytes2Wide( const char* msz, wchar_t* wideBuffer, int len )
{
#ifdef _MSC_VER
	int width = strlen( msz );
	len = min( len - 1, width );
	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)msz, len, wideBuffer, len);
	wideBuffer[len] = 0;
#else
	//copytextto(wideBuffer, msz, lengthof(msz));
#endif

	return wideBuffer;
}
TCHAR* CToolKit::UTF8ToGBK( const char *szIn, TCHAR* mutiBuffer, int len )
{
	if( szIn )
	{
#ifdef _MSC_VER
		wchar_t *wszUTF16;
		int szlen = MultiByteToWideChar( CP_UTF8, 0, ( LPCSTR )szIn, -1, NULL, 0 );
		wszUTF16 = new wchar_t[szlen + 1];
		memset( wszUTF16, 0, szlen * 2 + 2 );
		MultiByteToWideChar( CP_UTF8, 0, ( LPCSTR )szIn, -1, ( LPWSTR )wszUTF16, szlen );

		memset( mutiBuffer, 0, sizeof(TCHAR) * len );
		WideCharToMultiByte( CP_ACP, 0, wszUTF16, -1, mutiBuffer, min( len, szlen * 2 + 2 ), NULL, NULL );

		delete []wszUTF16;
#else
		copytextto(mutiBuffer, szIn, lengthof(szIn));
#endif
	}

	return mutiBuffer;
}


// void GBKToUTF8(char* &szOut)
// {
// 	char* strGBK = szOut;
// 
// 	int len=MultiByteToWideChar(CP_ACP, 0, (LPCSTR)strGBK, -1, NULL,0);
// 	unsigned short * wszUtf8 = new unsigned short[len+1];
// 	memset(wszUtf8, 0, len * 2 + 2);
// 	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)strGBK, -1, (LPWSTR)wszUtf8, len);
// 
// 	len = WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)wszUtf8, -1, NULL, 0, NULL, NULL);
// 	char *szUtf8=new char[len + 1];
// 	memset(szUtf8, 0, len + 1);
// 	WideCharToMultiByte (CP_UTF8, 0, (LPWSTR)wszUtf8, -1, szUtf8, len, NULL,NULL);
// 
// 	//szOut = szUtf8;
// 	memset(szOut,'/0',strlen(szUtf8)+1);
// 	memcpy(szOut,szUtf8,strlen(szUtf8)+1);
// 
// 	delete[] szUtf8;
// 	delete[] wszUtf8;
// }

