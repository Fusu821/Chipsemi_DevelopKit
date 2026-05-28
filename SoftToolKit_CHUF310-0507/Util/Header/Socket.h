#ifndef __SOCKET__
#define __SOCKET__
#include <WinSock2.h>
#include <MSTcpIP.h>
#include <MSWSock.h>
#include <ws2tcpip.h>
#include <mswsock.h>
#include <winsock2.h>
#include <ws2def.h>
#include <stddef.h>
/**************************************************************************************/
typedef LONG CONNID;

/* IOCP 命令 */
enum EnIocpCommand
{
	IOCP_CMD_EXIT		= 0x00000000,	// 退出程序
	IOCP_CMD_ACCEPT		= 0xFFFFFFF1,	// 接受连接
	IOCP_CMD_DISCONNECT	= 0xFFFFFFF2,	// 断开连接
	IOCP_CMD_SEND		= 0xFFFFFFF3	// 发送数据
};
enum EnIocpAction
{
	IOCP_ACT_GOON		= 0,	// 继续执行
	IOCP_ACT_CONTINUE	= 1,	// 重新执行
	IOCP_ACT_BREAK		= 2		// 中断执行
};
enum EnSocketOperation
{
	SO_UNKNOWN	= 0,	// Unknown
	SO_ACCEPT	= 1,	// Acccept
	SO_CONNECT	= 2,	// Connect
	SO_SEND		= 3,	// Send
	SO_RECEIVE	= 4,	// Receive
};
enum EnSendPolicy
{
	SP_PACK				= 0,	// 打包模式（默认）
	SP_SAFE				= 1,	// 安全模式
	SP_DIRECT			= 2,	// 直接模式
};
enum EnRecvPolicy
{
	RP_SERIAL			= 0,	// 串行模式（默认）
	RP_PARALLEL			= 1,	// 并行模式
};
enum EnSocketCloseFlag
{
	SCF_NONE	= 0,	// 不触发事件
	SCF_CLOSE	= 1,	// 触发 OnClose 事件
	SCF_ERROR	= 2		// 触发 OnError 事件
};
typedef enum EnReuseAddressPolicy
{
	RAP_NONE			= 0,	// 不重用
	RAP_ADDR_ONLY		= 1,	// 仅重用地址
	RAP_ADDR_AND_PORT	= 2,	// 重用地址和端口
} En_HP_ReuseAddressPolicy;
typedef enum EnOnSendSyncPolicy
{
	OSSP_NONE			= 0,	// 不同步（默认）
	OSSP_CLOSE			= 1,	// 同步 OnClose
	OSSP_RECEIVE		= 2,	// 同步 OnReceive（只用于 TCP 组件）	
} En_HP_OnSendSyncPolicy;

/* 检测 IOCP 操作返回值：NO_ERROR 则返回 TRUE */
#define IOCP_NO_ERROR(result)	(result == NO_ERROR)
/* 检测 IOCP 操作返回值：WSA_IO_PENDING 则返回 TRUE */
#define IOCP_PENDING(result)	(result == WSA_IO_PENDING)
/* 检测 IOCP 操作返回值：NO_ERROR 或 WSA_IO_PENDING 则返回 TRUE */
#define IOCP_SUCCESS(result)	(IOCP_NO_ERROR(result) || IOCP_PENDING(result))
/* 比较内存差异 */
#define EqualMemory(dest, src, len)		(!memcmp((dest), (src), (len)))

unsigned long GetIPv4InAddr( LPCTSTR pszAddress );
bool IsIPAddress( LPCTSTR lpszHost );
bool GetOptimalIPByHostName(LPCTSTR lpszHost, IN_ADDR& addr);
bool IN_ADDR_2_IP( const IN_ADDR& addr, LPTSTR lpszAddress, int& iAddressLen );
bool GetIPAddress( LPCTSTR lpszHost, LPTSTR lpszIP, int& iIPLen );
bool sockaddr_A_2_IN( SHORT usFamily, LPCTSTR pszAddress, USHORT usPort, SOCKADDR_IN& addr );
bool PostIocpAccept(HANDLE hIOCP);
BOOL PostIocpExit(HANDLE hIOCP);
int SSO_Linger(SOCKET sock, USHORT l_onoff, USHORT l_linger);
int SSO_ReuseAddress(SOCKET sock, BOOL bReuse);
int SSO_NoDelay(SOCKET sock, BOOL bNoDelay);
int SSO_NoBlock(SOCKET sock, BOOL bNoBlock = 1);
int SSO_UpdateAcceptContext(SOCKET soClient, SOCKET soBind);
int SSO_KeepAliveVals(SOCKET sock, u_long onoff, u_long time, u_long interval);
int ManualCloseSocket(SOCKET sock, int iShutdownFlag = 0xFF, bool bGraceful = true, bool bReuseAddress = false);
PVOID GetExtensionFuncPtr(SOCKET sock, GUID guid);
LPFN_ACCEPTEX Get_AcceptEx_FuncPtr( SOCKET sock );
LPFN_GETACCEPTEXSOCKADDRS Get_GetAcceptExSockaddrs_FuncPtr(SOCKET sock);
LPFN_CONNECTEX Get_ConnectEx_FuncPtr(SOCKET sock);
LPFN_DISCONNECTEX Get_DisconnectEx_FuncPtr(SOCKET sock);
CONNID GenerateConnectionID();
void SysGetSystemInfo( LPSYSTEM_INFO  pInfo );
unsigned int SysGetNumberOfProcessors();
unsigned int SysGetPageSize();


struct CInitSocket
{
public:
	CInitSocket( BYTE minorVer = 2, BYTE majorVer = 2 )
	{
		WSADATA wsaData;
		::WSAStartup( MAKEWORD( minorVer, majorVer ), &wsaData );
	}
	~CInitSocket()
	{
		::WSACleanup();
	}
};

typedef struct hp_sockaddr
{
	union
	{
		ADDRESS_FAMILY	family;
		SOCKADDR		addr;
		SOCKADDR_IN		addr4;
		SOCKADDR_IN6	addr6;
	};

	inline int AddrSize() const
	{
		return AddrSize(family);
	}

	inline static int AddrSize(ADDRESS_FAMILY f)
	{
		if(f == AF_INET)
			return sizeof(SOCKADDR_IN);

		return sizeof(SOCKADDR_IN6);
	}

	inline int EffectAddrSize() const
	{
		return EffectAddrSize(family);
	}

	inline static int EffectAddrSize(ADDRESS_FAMILY f)
	{
		//return (f == AF_INET) ? offsetof(SOCKADDR_IN, sin_zero) : sizeof(SOCKADDR_IN6);

		return (f == AF_INET) ? offsetof(SOCKADDR_IN, sin_zero) : sizeof(SOCKADDR_IN6);
	}

	inline static const hp_sockaddr& AnyAddr(ADDRESS_FAMILY f)
	{
		static const hp_sockaddr s_any_addr4(AF_INET, TRUE);
		static const hp_sockaddr s_any_addr6(AF_INET6, TRUE);

		if(f == AF_INET)
			return s_any_addr4;

		return s_any_addr6;
	}

	inline static int AddrMinStrLength(ADDRESS_FAMILY f)
	{
		if(f == AF_INET)
			return 16;

		return 46;
	}

	inline BOOL IsIPv4()			const	{return family == AF_INET;}
	inline BOOL IsIPv6()			const	{return family == AF_INET6;}
	inline BOOL IsSpecified()		const	{return IsIPv4() || IsIPv6();}
	inline USHORT Port()			const	{return ntohs(addr4.sin_port);}
	inline void SetPort(USHORT usPort)		{addr4.sin_port = htons(usPort);}
	inline void* SinAddr()			const	{return IsIPv4() ? (void*)&addr4.sin_addr : (void*)&addr6.sin6_addr;}
	inline void* SinAddr()					{return IsIPv4() ? (void*)&addr4.sin_addr : (void*)&addr6.sin6_addr;}

	inline const SOCKADDR* Addr()	const	{return &addr;}
	inline SOCKADDR* Addr()					{return &addr;}
	inline void ZeroAddr()					{::ZeroMemory(((char*)this) + sizeof(family), sizeof(*this) - sizeof(family));}
	inline void Reset()						{::ZeroMemory(this, sizeof(*this));}

	inline hp_sockaddr& Copy(hp_sockaddr& other) const
	{
		if(this != &other)
			memcpy(&other, this, AddrSize());

		return other;
	}

	size_t Hash() const
	{
		ASSERT(IsSpecified());

		size_t _Val		  = 2166136261U;
		const int size	  = EffectAddrSize();
		const BYTE* pAddr = (const BYTE*)Addr();

		for(int i = 0; i < size; i++)
			_Val = 16777619U * _Val ^ (size_t)pAddr[i];

		return (_Val);
	}

	bool EqualTo(const hp_sockaddr& other) const
	{
		ASSERT(IsSpecified() && other.IsSpecified());

		return EqualMemory(this, &other, EffectAddrSize());
	}

	hp_sockaddr(ADDRESS_FAMILY f = AF_UNSPEC, BOOL bZeroAddr = FALSE)
	{
		family = f;

		if(bZeroAddr) ZeroAddr();
	}

} HP_SOCKADDR, *HP_PSOCKADDR;

/**************************************************************************************/
#endif