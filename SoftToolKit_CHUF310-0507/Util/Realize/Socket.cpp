#include "Socket.h"
#include "Basic.h"

#include <tchar.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32")
#define _WIN32_WINNT_VISTA 0x0600
unsigned long GetIPv4InAddr( LPCTSTR pszAddress )
{
	if (!pszAddress || pszAddress[0] == '\0')
		return INADDR_NONE;
#if _WIN32_WINNT >= _WIN32_WINNT_VISTA
	IN_ADDR addr;
	if (::InetPton (AF_INET, pszAddress, &addr.s_addr) == 1)
		return addr.s_addr;

	return INADDR_NONE;
#else
#ifdef _UNICODE
	int len = (int)WideCharToMultiByte( CP_ACP, 0, pszAddress, (int)wcslen(pszAddress), NULL,0, NULL, NULL );  
	char* ptrAddress = new char[len + 1];
	WideCharToMultiByte( CP_ACP, 0, pszAddress, (int)wcslen(pszAddress), ptrAddress, len, NULL, NULL );   
	ptrAddress[len] = 0;
	unsigned long uAddr = ::inet_addr(ptrAddress);
	delete[] ptrAddress;
	return uAddr;
#else
    return ::inet_addr(pszAddress);
#endif
#endif
}
bool IsIPAddress( LPCTSTR lpszHost )
{
	return GetIPv4InAddr( lpszHost ) != INADDR_NONE;
}
bool GetOptimalIPByHostName(LPCTSTR lpszHost, IN_ADDR& addr)
{
	addr.s_addr	= 0;

	addrinfo*	pInfo = NULL;
	addrinfo	hints = {0};

	hints.ai_flags	= AF_MAX;
	hints.ai_family	= AF_INET;

#ifdef _UNICODE
	int len = (int)WideCharToMultiByte( CP_ACP, 0, lpszHost, (int)wcslen(lpszHost), NULL,0, NULL, NULL );  
	char* ptrHost = new char[len + 1];
	WideCharToMultiByte( CP_ACP, 0, lpszHost, (int)wcslen(lpszHost), ptrHost, len, NULL, NULL );  
	ptrHost[len] = 0;
	int rs = ::getaddrinfo( ptrHost, NULL, &hints, &pInfo );
	delete[] ptrHost;
#else
	int rs = ::getaddrinfo( lpszHost, NULL, &hints, &pInfo );
#endif

	

	if(rs == NO_ERROR)
	{
		IN_ADDR inAddr;
		ULONG addrs[3]  = {0};
		char** pptr		= NULL;

		for(addrinfo* pCur = pInfo; pCur != NULL; pCur = pCur->ai_next)
		{
			if(pCur->ai_family == AF_INET)
			{
				inAddr	= ((SOCKADDR_IN*)(pCur->ai_addr))->sin_addr;
				UCHAR a	= inAddr.s_net;
				UCHAR b	= inAddr.s_host;

				if(addrs[0] == 0 && a == 127)
				{
					addrs[0] = inAddr.s_addr;
					break;
				}
				else if(	addrs[1] == 0							&& 
					(
					(a == 10)							||
					(a == 172 && b >= 16 && b <= 31)	||
					(a == 192 && b == 168)
					)
					)
					addrs[1] = inAddr.s_addr;
				else if(addrs[2] == 0)
					addrs[2] = inAddr.s_addr;
			}
		}

		::freeaddrinfo(pInfo);

		for(int i = 0; i < 3; i++)
		{
			if(addrs[i] != 0)
			{
				addr.s_addr = addrs[i];
				break;
			}
		}
	}

	return addr.s_addr != 0;
}
bool IN_ADDR_2_IP( const IN_ADDR& addr, LPTSTR lpszAddress, int& iAddressLen )
{
	bool bOK = true;

	TCHAR szAddr[16];
	wsprintf(szAddr, _T("%hu.%hu.%hu.%hu"), addr.s_net, addr.s_host, addr.s_lh, addr.s_impno);

	int iIPLen = lstrlen(szAddr) + 1;

	if(iAddressLen >= iIPLen)
		memcpy(lpszAddress, szAddr, iIPLen * sizeof(TCHAR));
	else
		bOK = false;

	iAddressLen = iIPLen;

	return bOK;
}
bool GetIPAddress( LPCTSTR lpszHost, LPTSTR lpszIP, int& iIPLen )
{
	bool bOK = true;

	if( IsIPAddress( lpszHost ) )
	{
		int iHostLen = (int)_tcslen( lpszHost );

		if( iHostLen > 0 ) ++iHostLen;

		if( iHostLen > 0 && iIPLen >= iHostLen )
			_tcscpy_s( lpszIP, iIPLen, lpszHost );
		else bOK = false;

		iIPLen = iHostLen;
	}
	else
	{
		IN_ADDR addr;

		if( GetOptimalIPByHostName( lpszHost, addr ) )
			bOK = IN_ADDR_2_IP( addr, lpszIP, iIPLen );
		else 
			bOK = false;
	}

	return bOK;
}
bool sockaddr_A_2_IN( SHORT usFamily, LPCTSTR pszAddress, USHORT usPort, SOCKADDR_IN& addr )
{
	assert( usFamily == AF_INET );

	addr.sin_family = usFamily;
	addr.sin_port = htons( usPort );
	addr.sin_addr.s_addr = GetIPv4InAddr( pszAddress );

	return addr.sin_addr.s_addr != INADDR_NONE;
}
bool PostIocpAccept(HANDLE hIOCP)
{
	return TRUE == ::PostQueuedCompletionStatus(hIOCP, IOCP_CMD_ACCEPT, 0, NULL);
}
BOOL PostIocpExit(HANDLE hIOCP)
{
	return ::PostQueuedCompletionStatus(hIOCP, IOCP_CMD_EXIT, 0, NULL);
}
int SSO_Linger(SOCKET sock, USHORT l_onoff, USHORT l_linger)
{
	linger ln = {l_onoff, l_linger};
	return setsockopt(sock, SOL_SOCKET, SO_LINGER, (CHAR*)&ln, sizeof(linger));
}
int SSO_ReuseAddress(SOCKET sock, BOOL bReuse)
{
	return setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (CHAR*)&bReuse, sizeof(BOOL));
}
int SSO_NoDelay(SOCKET sock, BOOL bNoDelay)
{
	return setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (CHAR*)&bNoDelay, sizeof(BOOL));
}
int SSO_NoBlock(SOCKET sock, BOOL bNoBlock)
{
	return ioctlsocket(sock, FIONBIO, (ULONG*)&bNoBlock);
}
int SSO_UpdateAcceptContext(SOCKET soClient, SOCKET soBind)
{
	return setsockopt(soClient, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT, (CHAR*)&soBind, sizeof(SOCKET));
}
int SSO_KeepAliveVals(SOCKET sock, u_long onoff, u_long time, u_long interval)
{
	int result		 = NO_ERROR;
	tcp_keepalive in = {onoff, time, interval};
	DWORD dwBytes;

	if(::WSAIoctl	(
		sock, 
		SIO_KEEPALIVE_VALS, 
		(LPVOID)&in, 
		sizeof(in), 
		NULL, 
		0, 
		&dwBytes, 
		NULL, 
		NULL
		) == SOCKET_ERROR)
	{
		result = ::WSAGetLastError();
		if(result == WSAEWOULDBLOCK)
			result = NO_ERROR;
	}

	return result;
}
int ManualCloseSocket(SOCKET sock, int iShutdownFlag /*= 0xFF*/, bool bGraceful /*= true*/, bool bReuseAddress /*= false*/)
{
	if( !bGraceful )            SSO_Linger(sock, 1, 0);
	if( bReuseAddress )         SSO_ReuseAddress(sock, bReuseAddress);
	if( iShutdownFlag != 0xFF ) shutdown( sock, iShutdownFlag );

	return closesocket( sock );
}
PVOID GetExtensionFuncPtr(SOCKET sock, GUID guid)
{
	DWORD dwBytes;
	PVOID pfn = NULL;

	::WSAIoctl	(
		sock,
		SIO_GET_EXTENSION_FUNCTION_POINTER,
		&guid,
		sizeof(guid),
		&pfn,
		sizeof(pfn),
		&dwBytes,
		NULL,
		NULL
		);

	return pfn;
}
LPFN_ACCEPTEX Get_AcceptEx_FuncPtr( SOCKET sock )
{
	GUID guid = WSAID_ACCEPTEX;
	return (LPFN_ACCEPTEX)GetExtensionFuncPtr( sock, guid );
}
LPFN_GETACCEPTEXSOCKADDRS Get_GetAcceptExSockaddrs_FuncPtr(SOCKET sock)
{
	GUID guid = WSAID_GETACCEPTEXSOCKADDRS;
	return (LPFN_GETACCEPTEXSOCKADDRS)GetExtensionFuncPtr( sock, guid );
}
LPFN_CONNECTEX Get_ConnectEx_FuncPtr(SOCKET sock)
{
	GUID guid = WSAID_CONNECTEX;
	return (LPFN_CONNECTEX)GetExtensionFuncPtr( sock, guid );
}
LPFN_DISCONNECTEX Get_DisconnectEx_FuncPtr	(SOCKET sock)
{
	GUID guid = WSAID_DISCONNECTEX;
	return (LPFN_DISCONNECTEX)GetExtensionFuncPtr( sock, guid );
}
CONNID GenerateConnectionID()
{
	static volatile CONNID s_dwConnID = 0;

	CONNID dwConnID	= ::InterlockedIncrement(&s_dwConnID);

	if(dwConnID == 0)
		dwConnID = ::InterlockedIncrement(&s_dwConnID);

	return dwConnID;
}
void SysGetSystemInfo( LPSYSTEM_INFO  pInfo )
{
	assert(pInfo != NULL);

	GetNativeSystemInfo( pInfo );
}
unsigned int SysGetNumberOfProcessors()
{
	SYSTEM_INFO si;

	SysGetSystemInfo(&si);

	return si.dwNumberOfProcessors;
}
unsigned int SysGetPageSize()
{
	SYSTEM_INFO si;
	SysGetSystemInfo(&si);

	return si.dwPageSize;
}
