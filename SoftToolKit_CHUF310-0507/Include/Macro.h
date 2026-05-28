#ifndef __MACRO__
#define __MACRO__
/**************************************************************************************/
#if ((defined SM_CHIP_BASE) || (defined SM_TEST_BASE) || (defined SM_TEST_APP) || (defined ONLINE_SERVICE))
#include <windows.h>
#include <tchar.h>
#endif

#if (defined _MSC_VER) 
#define platform_required_sel 1
#define  MAX_DEVICE_NUM       8
#define  MAX_RD_STUMP_LEN     4
#define  MAX_HAL_WR_LEN       (128  + 8)
#define  MAX_HAL_RD_LEN       (1024 + 8)
#define  REAL_HAL_WR_LEN      (MAX_HAL_WR_LEN - 8)
#define  REAL_HAL_RD_LEN      (MAX_HAL_RD_LEN - 8)
#define  REAL_TCP_RD_LEN      4096
/*#define  HAL_LEN_EXTERN       8*/
#define	 USB_RW_TIMEOUT		  100
#define	 COM_RW_TIMEOUT		  300
#define  TCP_WR_TIMEOUT       500
#define  MIN_COM_RW_LEN       17
#define  MAX_PIPE_WR_LEN      256
#define  MAX_SOCKET_WR_LEN    2048
#define  thread_identity      HANDLE
#define  entry_type           UINT32
#define  cpx_create_thread(h, a, entry, p)   h = (thread_identity)_beginthreadex(a, 0, entry, p, 0, NULL)
#define  kill_thread(t, s)    TerminateThread(t, s)
#define  is_dir_exist(path)   (-1 != GetFileAttributes(path))
#define  create_dir(path)     CreateDirectory(path, NULL)

#else //_MSC_VER
#include <unistd.h>
#define platform_required_sel 1
#define  MAX_DEVICE_NUM       8
#define  MAX_RD_STUMP_LEN     4
#define  MAX_HAL_WR_LEN       (128 + 8)
#define  MAX_HAL_RD_LEN       (512 + 8)
#define  REAL_HAL_WR_LEN      (MAX_HAL_WR_LEN - 8)
#define  REAL_HAL_RD_LEN      (MAX_HAL_RD_LEN - 8)
/*#define  HAL_LEN_EXTERN       8*/
#define	 USB_RW_TIMEOUT		  100
#define	 COM_RW_TIMEOUT		  300
#define  TCP_WR_TIMEOUT       500
#define  MIN_COM_RW_LEN       17
#define  MAX_PIPE_WR_LEN      256
#define  MAX_SOCKET_WR_LEN    2048
#define  thread_identity      pthread_t
#define  entry_type           void*
#define  cpx_create_thread(h, a, entry, p)    pthread_create(&h, a, entry, p)
#define  kill_thread(t, s)    pthread_kill(t, s)
#define  is_dir_exist(path)   (0 == access(strTemp.c_str(), W_OK))
#define  create_dir(path)     mkdir(path, 0755)

typedef struct tagRECT
{
    long    left;
    long    top;
    long    right;
    long    bottom;
} RECT, *PRECT, *LPRECT;

typedef struct tagPOINT
{
    long  x;
    long  y;
} POINT, *PPOINT, *LPPOINT;

typedef struct _GUID {
    unsigned long  Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char  Data4[ 8 ];
} GUID;
typedef GUID IID;
#define REFIID const IID &

#define DECLARE_HANDLE(name) struct name##__; typedef struct name##__ *name
DECLARE_HANDLE(HBITMAP);
DECLARE_HANDLE(HDC);
DECLARE_HANDLE(HWND);

#define USHORT   unsigned short
#define TCHAR    char
#define LPCTSTR  const char*
#define HANDLE   unsigned int
#define BOOL     unsigned char
#define LPVOID   void*
#undef  NULL
#define NULL     __null
#define FALSE    0
#define TRUE     1
#define _T
#define __stdcall
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)>(b)?(b):(a))
#define MAX_PATH 256
#define UINT64   long long
//#define SYSTEMTIME long long
#define UINT32 unsigned int
#define WINAPI
#define COLORREF unsigned int
#define WORD   unsigned short
typedef  void*           HDEVNOTIFY;

#define IN
#define OUT
#define RGB(r,g,b) ((unsigned int)(((unsigned char)(r)|((unsigned short)((unsigned char)(g))<<8))|(((unsigned short)(unsigned char)(b))<<16)))
#endif //_MSC_VER

#define  WM_SYNC_REQUEST      WM_USER + 0001
#define  WM_ASYN_REQUEST      WM_USER + 0002
#define  PARAM_NAME_LENTH     100
#define  VALIDATA_GATEBYTE    1
#define  THREAD_EXIT_FAILED   0
#define  THREAD_EXIT_SUCCESS  1
#define  TYPENAME(CLASSNAME)  _T(#CLASSNAME)

#define     PARAM_MARK_RESERVED                     0x00
/***********************************************************
command used by hid protocal
***********************************************************/
// #define CMD_SWITCH_REPORTMODE       0xA0
// #define	CMD_READ_REGISTER			0x50
// #define	CMD_WRITE_REGISTER			0x51
// #define CMD_READ_RAWDATA_ALL        0x52
// #define	CMD_READ_TXCAP_ALL			0x53
// #define	CMD_READ_RXCAP_ALL			0x54
// #define	CMD_READ_TXORDER_ALL		0x55
// #define	CMD_READ_RXORDER_ALL		0x56
// #define CMD_READ_CB_ALL             0x57
/***********************************************************
Error Code Define
***********************************************************/
#define	ERROR_CODE_OK						          0x0000
#define ERROR_CODE_LOOP_BEYOND_MAX_RETRY              0x0001    
#define ERROR_CODE_NO_DEVICE                          0x0002
#define ERROR_CODE_NO_KINDOF_IC                       0x0003
#define	ERROR_CODE_INVALID_PARAM			          0x0004
#define	ERROR_CODE_WRITE_USB_ERROR			          0x0005
#define	ERROR_CODE_WAIT_RESPONSE_TIMEOUT	          0x0006
#define	ERROR_CODE_READ_USB_ERROR			          0x0007
#define	ERROR_CODE_COMM_ERROR	    			      0x0008
#define ERROR_CODE_DEVICE_CLOSED		         	  0x0009
#define ERROR_CODE_CHECK_RESPONSE_FAILED              0x000A
#define ERROR_CODE_ONE_PROCESS_RUNING                 0x000B
#define	ERROR_CODE_INVALID_FILE			              0x000C
#define	ERROR_CODE_CHECK_SUM_MISMATCH			      0x000D
#define	ERROR_CODE_DEVICE_OPENED					  0x000E
          
#ifdef _MSC_VER
#ifndef  BSPR_SERVICE
#define  BSPR_SERVICE_API __declspec( dllimport )
#else  
#define  BSPR_SERVICE_API __declspec( dllexport )
#endif

#define HAL_SERVICE_API        __declspec( dllimport )
#define HAL_SERVICE_CSTYLE_API extern "C" __declspec( dllimport )

#ifndef HAL_USB_SERVICE
#define HAL_USB_SERVICE_API __declspec( dllimport )
#else 
#undef  HAL_SERVICE_API
#define HAL_SERVICE_API     __declspec( dllexport )
#undef  HAL_SERVICE_CSTYLE_API
#define HAL_SERVICE_CSTYLE_API  extern "C" __declspec( dllexport )
#define HAL_USB_SERVICE_API __declspec( dllexport )
#endif

#ifndef HAL_COM_SERVICE
#define HAL_COM_SERVICE_API __declspec( dllimport )
#else 
#undef  HAL_SERVICE_API
#define HAL_SERVICE_API     __declspec( dllexport )
#undef  HAL_SERVICE_CSTYLE_API
#define HAL_SERVICE_CSTYLE_API  extern "C" __declspec( dllexport )
#define HAL_COM_SERVICE_API __declspec( dllexport )
#endif


#ifndef HAL_PIPE_SERVICE
#define HAL_PIPE_SERVICE_API __declspec( dllimport )
#else 
#undef  HAL_SERVICE_API
#define HAL_SERVICE_API     __declspec( dllexport )
#undef  HAL_SERVICE_CSTYLE_API
#define HAL_SERVICE_CSTYLE_API  extern "C" __declspec( dllexport )
#define HAL_PIPE_SERVICE_API __declspec( dllexport )
#endif

#ifndef HAL_TCPCLIENT_SERVICE
#define HAL_TCPCLIENT_SERVICE_API __declspec( dllimport )
#else 
#undef  HAL_SERVICE_API
#define HAL_SERVICE_API     __declspec( dllexport )
#undef  HAL_SERVICE_CSTYLE_API
#define HAL_SERVICE_CSTYLE_API  extern "C" __declspec( dllexport )
#define HAL_TCPCLIENT_SERVICE_API __declspec( dllexport )
#endif

#ifndef HAL_TCPSERVER_SERVICE
#define HAL_TCPSERVER_SERVICE_API __declspec( dllimport )
#else 
#undef  HAL_SERVICE_API
#define HAL_SERVICE_API     __declspec( dllexport )
#undef  HAL_SERVICE_CSTYLE_API
#define HAL_SERVICE_CSTYLE_API  extern "C" __declspec( dllexport )
#define HAL_TCPSERVER_SERVICE_API __declspec( dllexport )
#endif

#ifndef SM_PROTOCAL
#define SM_PROTOCAL_API __declspec( dllimport )
#else 
#define SM_PROTOCAL_API __declspec( dllexport )
#endif

#ifndef SM_CHIP_BASE
#define SM_CHIP_API __declspec( dllimport )
#define SM_CHIP_CSTYLE_API extern "C" __declspec( dllimport )
#define SM_CHIP_INTERFACE extern "C" interface _declspec(dllimport) 
#else 
#define SM_CHIP_API __declspec( dllexport )
#define SM_CHIP_CSTYLE_API extern "C" __declspec( dllexport )
#define SM_CHIP_INTERFACE extern "C" interface _declspec(dllexport) 
#endif

#ifndef SM_TEST_BASE
#define SM_TEST_API __declspec( dllimport )
#define SM_TEST_CSTYLE_API extern "C" __declspec( dllimport )
#define SM_TEST_INTERFACE extern "C" interface _declspec(dllimport) 
#else 
#define SM_TEST_API __declspec( dllexport )
#define SM_TEST_CSTYLE_API extern "C" __declspec( dllexport )
#define SM_TEST_INTERFACE extern "C" interface _declspec(dllexport) 
#endif

#ifndef ONLINE_SERVICE
#define ONLINE_SERVICE_API __declspec( dllimport )
#define ONLINE_SERVICE_CSTYLE_API extern "C" __declspec( dllimport )
#else 
#define ONLINE_SERVICE_API __declspec( dllexport )
#define ONLINE_SERVICE_CSTYLE_API extern "C" __declspec( dllexport )
#endif

#ifndef ALGORITHM_EXPORTS
#define SM_ALGORITHM_API __declspec( dllimport )
#define SM_ALGORITHM_CSTYLE_API extern "C" __declspec( dllimport )
#define SM_ALGORITHM_INTERFACE extern "C" interface _declspec(dllimport)
#else
#define SM_ALGORITHM_API __declspec( dllexport )
#define SM_ALGORITHM_CSTYLE_API extern "C" __declspec( dllexport )
#define SM_ALGORITHM_INTERFACE extern "C" interface _declspec(dllexport)
#endif
#else //_MSC_VER
#ifndef  BSPR_SERVICE
#define  BSPR_SERVICE_API //__declspec( dllimport )
#else
#define  BSPR_SERVICE_API //__declspec( dllexport )
#endif

#define HAL_SERVICE_API        //__declspec( dllimport )
#define HAL_SERVICE_CSTYLE_API //extern "C" __declspec( dllimport )

#ifndef HAL_USB_SERVICE
#define HAL_USB_SERVICE_API //__declspec( dllimport )
#else
#undef  HAL_SERVICE_API
#define HAL_SERVICE_API     //__declspec( dllexport )
#undef  HAL_SERVICE_CSTYLE_API
#define HAL_SERVICE_CSTYLE_API  //extern "C" __declspec( dllexport )
#define HAL_USB_SERVICE_API //__declspec( dllexport )
#endif

#ifndef HAL_COM_SERVICE
#define HAL_COM_SERVICE_API //__declspec( dllimport )
#else
#undef  HAL_SERVICE_API
#define HAL_SERVICE_API     //__declspec( dllexport )
#undef  HAL_SERVICE_CSTYLE_API
#define HAL_SERVICE_CSTYLE_API  //extern "C" __declspec( dllexport )
#define HAL_COM_SERVICE_API //__declspec( dllexport )
#endif

#ifndef HAL_PIPE_SERVICE
#define HAL_PIPE_SERVICE_API //__declspec( dllimport )
#else
#undef  HAL_SERVICE_API
#define HAL_SERVICE_API     //__declspec( dllexport )
#undef  HAL_SERVICE_CSTYLE_API
#define HAL_SERVICE_CSTYLE_API  //extern "C" __declspec( dllexport )
#define HAL_PIPE_SERVICE_API //__declspec( dllexport )
#endif

#ifndef HAL_TCPCLIENT_SERVICE
#define HAL_TCPCLIENT_SERVICE_API //__declspec( dllimport )
#else
#undef  HAL_SERVICE_API
#define HAL_SERVICE_API     //__declspec( dllexport )
#undef  HAL_SERVICE_CSTYLE_API
#define HAL_SERVICE_CSTYLE_API  //extern "C" __declspec( dllexport )
#define HAL_TCPCLIENT_SERVICE_API //__declspec( dllexport )
#endif

#ifndef SM_PROTOCAL
#define SM_PROTOCAL_API //__declspec( dllimport )
#else
#define SM_PROTOCAL_API //__declspec( dllexport )
#endif

#ifndef SM_CHIP_BASE
#define SM_CHIP_API //__declspec( dllimport )
#define SM_CHIP_CSTYLE_API  //extern "C" __declspec( dllimport )
#define SM_CHIP_INTERFACE //extern "C" interface _declspec(dllimport)
#else
#define SM_CHIP_API //__declspec( dllexport )
#define SM_CHIP_CSTYLE_API //extern "C" __declspec( dllexport )
#define SM_CHIP_INTERFACE //extern "C" interface _declspec(dllexport)
#endif

#ifndef SM_TEST_BASE
#define SM_TEST_API// __declspec( dllimport )
#define SM_TEST_CSTYLE_API //extern "C" __declspec( dllimport )
#define SM_TEST_INTERFACE //extern "C" interface _declspec(dllimport)
#else
#define SM_TEST_API //__declspec( dllexport )
#define SM_TEST_CSTYLE_API //extern "C" __declspec( dllexport )
#define SM_TEST_INTERFACE //extern "C" interface _declspec(dllexport)
#endif

#ifndef ONLINE_SERVICE
#define ONLINE_SERVICE_API //__declspec( dllimport )
#define ONLINE_SERVICE_CSTYLE_API //extern "C" __declspec( dllimport )
#else 
#define ONLINE_SERVICE_API //__declspec( dllexport )
#define ONLINE_SERVICE_CSTYLE_API //extern "C" __declspec( dllexport )
#endif

#ifndef ALGORITHM_EXPORTS
#define SM_ALGORITHM_API// __declspec( dllimport )
#define SM_ALGORITHM_CSTYLE_API //extern "C" __declspec( dllimport )
#define SM_ALGORITHM_INTERFACE //extern "C" interface _declspec(dllimport)
#else
#define SM_ALGORITHM_API //__declspec( dllexport )
#define SM_ALGORITHM_CSTYLE_API //extern "C" __declspec( dllexport )
#define SM_ALGORITHM_INTERFACE //extern "C" interface _declspec(dllexport)
#endif
#endif //_MSC_VER


#define USBPRINT_IOCTL_INDEX    0x0000
#define FILE_DEVICE_UNKNOWN     0x00000022

#define HID_IIC_COMMAND 0x0B0195    

//0x0B0195

#define HID_IIC_Read_COMMAND    0x0B01A2

//0x0B01A2

#define IOCTL_USBPRINT_VENDOR_SET_COMMAND CTL_CODE(FILE_DEVICE_UNKNOWN,  \
	USBPRINT_IOCTL_INDEX+14,\
	METHOD_BUFFERED,  \
	FILE_ANY_ACCESS)                                                           

#define IOCTL_USBPRINT_VENDOR_GET_COMMAND CTL_CODE(FILE_DEVICE_UNKNOWN,  \
	USBPRINT_IOCTL_INDEX+15,\
	METHOD_BUFFERED,  \
	FILE_ANY_ACCESS)   

#define IOCTL_USBPRINT_VENDOR_GET_COMMAND CTL_CODE(FILE_DEVICE_UNKNOWN,  \
	USBPRINT_IOCTL_INDEX+15,\
	METHOD_BUFFERED,  \
	FILE_ANY_ACCESS)     

/************************************************************************/
/* Define Chip ID                                                       */
/************************************************************************/
#define IC_TYPE_SCAP                             0x01
#define IC_TYPE_MCAP                             0x02
#define IC_TYPE_ROCKER                           0x03

#define IC_TYPE_ROCKER_810                       0x04

#define IC_TYPE_FINGERPRINT                      0x06

#define SEMI_IC_3535                             0x0100

#define SEMI_IC_3536                             0x0200
#define SEMI_IC_6440                             0X0201
#define SEMI_IC_6448                             0X0202
#define SEMI_IC_6413                             0X0203
#define SEMI_IC_6417                             0X0204
#define SEMI_IC_6540                             0X0205
#define SEMI_IC_6545                             0X0206
#define SEMI_IC_6410                             0X0207
#define SEMI_IC_6430                             0X0208
#define SEMI_IC_6448S                            0X0209

#define SEMI_IC_5472                             0X0400
#define SEMI_IC_5448                             0X0401
#define SEMI_IC_5448A                            0X0402
#define SEMI_IC_5460                             0X0403
#define SEMI_IC_5468                             0X0404
#define SEMI_IC_5428                             0X0405
#define SEMI_IC_5432                             0X0406
#define SEMI_IC_8328                             0X0407
#define SEMI_IC_5448C                            0X0408
#define SEMI_IC_5448D                            0X0409
#define SEMI_IC_5448E                            0X040A

#define SEMI_IC_5816                             0X0500
#define SEMI_IC_1716                             0X0501

#define SEMI_IC_7449                             0x0600
#define SEMI_IC_7438                             0x0601
#define SEMI_IC_7448                             0x0602
#define SEMI_IC_7464                             0x0603

#define SEMI_IC_5562                             0X0700
#define SEMI_IC_5460S                            0X0701
#define SEMI_IC_5560                             0X0702
#define SEMI_IC_7562                             0X0703

#define SEMI_IC_CHGA8006                         0X0800

#define SEMI_IC_CHGA810                          0X0901

#define SEMI_IC_7126                             0X0A00

#define SEMI_IC_570                              0X0B00

#define SEMI_IC_CHUF310                          0X0D01

#define TEXT_SIZE_SMALL                          250
#define TEXT_SIZE_LARGE                          361
#define MAX_SCAP_ROW                             7
#define MAX_SCAP_COL                             24

#define MAX_MCAP_ROW                             50
#define MAX_MCAP_COL                             50
#define MAX_MCAP_CHANNEL                         (50*50)

#define MAX_MCAP_ROW_710                         100
#define MAX_MCAP_COL_710                         100
#define MAX_MCAP_CHANNEL_710                     (80*60)


#define MAX_TX_NUM_5472                          32
#define MAX_RX_NUM_5472                          40

#define MAX_TX_NUM_7449                          32  //??
#define MAX_RX_NUM_7449                          40  //??

#define MAX_TX_NUM_5816                          20
#define MAX_RX_NUM_5816                          42

#define MAX_TX_NUM_5562                          20
#define MAX_RX_NUM_5562                          42

#define MAX_TX_NUM_570                          20
#define MAX_RX_NUM_570                          40

#define MAX_TX_NUM_7126                          52
#define MAX_RX_NUM_7126                          74

#define MAX_TX_NUM_8XX                           20
#define MAX_RX_NUM_8XX                           42

#define MAX_TX_NUM_310                          20 //--
#define MAX_RX_NUM_310                          42

#define MAX_SCAP_CHANNEL                         48
#define MAX_SCAP_BUFFER_CNT                      (MAX_SCAP_CHANNEL+3)

#define MAX_IX_NUM_3535                          10
#define MAX_IX_NUM_3536                          12
#define MAX_CHANNEL_ONE_GROUP                    4

enum NodeType { NODE_INVALID_TYPE = 0, NODE_VALID_TYPE = 1, NODE_KEY_TYPE = 2, NODE_AST_TYPE = 3, };


#define arraycount(x)          (sizeof(x)/sizeof((x)[0]))

#if (defined _MSC_VER) 
#ifdef _UNICODE
#define   tstring            wstring
#define   lengthof           wcslen
#define   copytextto         wcsncpy_s
#define   copytextappend     wcscat_s
#define   comparetext        wcscmp
#define   icomparetext       _wcsicmp
#define   struper( x )       _wcsupr_s( (wchar_t*)(x), lengthof(x)+1 )
#define   strlower( x )      _wcslwr_s( (wchar_t*)(x), lengthof(x)+1 )
#define   findtext           wcsstr
#define   rfindtext          wcsrchr
//#define   sprintf            wvsprintfW
#define   transformat        swprintf_s
#define   trancstrtoval      wcstoul
#define   trancstrtoint      _wtoi
#else
#define   tstring            string
#define   lengthof           strlen
#define   copytextto         strncpy_s
#define   copytextappend     strcat_s
#define   comparetext        strcmp
#define   icomparetext       _stricmp
#define   struper( x )       _strupr_s( (char*)(x), lengthof(x)+1 )
#define   strlower( x )      _strlwr_s( (char*)(x), lengthof(x)+1 )
#define   findtext           strstr
#define   rfindtext          strrchr
//#define   sprintf            wvsprintfA
#define   transformat        sprintf_s
#define   trancstrtoval      strtoul
#define   trancstrtoint      atoi
#endif
#else //_MSC_VER
#define   tstring            string
#define   lengthof           strlen
#define   copytextto(x, y, l)       strcpy(x, y)
#define   copytextappend     strcat
#define   comparetext        strcmp
#define   icomparetext       strcmp
#define   struper( x )       _strupr_s( (char*)(x), lengthof(x)+1 )
#define   strlower( x )      _strlwr_s( (char*)(x), lengthof(x)+1 )
#define   findtext           strstr
#define   rfindtext          strrchr
//#define   sprintf            wvsprintfA
#define   transformat(sz, fmt, ...)        sprintf(sz, fmt, ##__VA_ARGS__)
#define   trancstrtoval      strtoul
#define   trancstrtoint      atoi
#define memcpy_s(x, xl, y, yl) memcpy(x, y, yl)
#define sscanf_s sscanf
#define fopen_s(pf, p, m) *pf = fopen(p, m)
#define fread_s(b, s, e, c, f) fread(b, e, c, f)
#endif //_MSC_VER
/**************************************************************************************/
#endif