#ifndef __PROTOCAL_LAYER__
#define __PROTOCAL_LAYER__
/**************************************************************************************/
#include "Macro.h"
#include <Windows.h>
#include "Helper.h"
#include "Wait.h"
#define PROT_TYPE_IIC       0
#define PROT_TYPE_SPI       1
#define PROT_TYPE_USB       2
#define PROT_TYPE_OLED_SPI  3
#define PROT_TYPE_SOCKET    4

#define MAX_RETRY_FRAME             2
#define MAX_SIU_DATA_LEN            50

#define PACKET_CLEAR_FLAG  0x8000
enum PacketType{ PACKET_NORMAL = 0x0001, PACKET_TOUCH = 0x0002, PACKET_AUTOREPORT = 0x0004, PACKET_LEVEL = 0x0008 };

class  IHalServiceInterface;
struct stuReadWriteSr
{
	unsigned char  cmdCode;
    unsigned char* pWrite;
	unsigned short numOfWrite;
	unsigned char* pRead;
	unsigned short numOfRead;
	unsigned short numOfReaded;
	LPVOID         ptrEx;
	IHalServiceInterface* context;
	stuReadWriteSr(IHalServiceInterface* thisContext):context(thisContext),numOfReaded(0),ptrEx(0){}
	virtual ~stuReadWriteSr(){}
};
struct stuReadWriteSrEx : public stuReadWriteSr
{
    stuReadWriteSrEx( IHalServiceInterface* thisContext, SpinLock& locked )
		:stuReadWriteSr( thisContext )
		,lock(locked)
	{
        lock.Lock();
	}
	~stuReadWriteSrEx()
	{
        lock.Unlock();
	}
private:
	SpinLock& lock;
};
// struct stuWriteBmp
// {
// 	unsigned char  cmdCode;
// 	unsigned char* pWrite;
// 	int numOfWrite;
// 	unsigned char bSram;
// 	int* pos;
// 	IHalServiceInterface* context;
// 	stuWriteBmp( IHalServiceInterface* thisContext ):context(thisContext){}
// 	virtual ~stuWriteBmp(){}
// };
// struct stuWriteBmpEx : public stuWriteBmp
// {
//     stuWriteBmpEx( IHalServiceInterface* thisContext, SpinLock& locked )
// 		:stuWriteBmp(thisContext)
// 		,lock(locked)
// 	{
// 		lock.Lock();
// 	}
// 	~stuWriteBmpEx()
// 	{
// 		lock.Unlock();
// 	}
// private:
// 	SpinLock& lock;
// };

struct stuRead
{
	unsigned char  cmdCode;
	unsigned char* pRead;
	unsigned short numOfRead;
	unsigned short numOfReaded;
};
struct stuWrite
{
	unsigned char  cmdCode;
	unsigned char* pWrite;
	unsigned short numOfWrite;
};
struct stuReadAutoReport
{
	unsigned char* pRead;
	unsigned short numOfRead;
	unsigned short numOfReaded;
	IHalServiceInterface* context;
	stuReadAutoReport(IHalServiceInterface* thisContext):context(thisContext){}
	virtual ~stuReadAutoReport(){}
};
struct stuReadAutoReportEx : public stuReadAutoReport
{
	stuReadAutoReportEx( IHalServiceInterface* thisContext, SpinLock& locked )
		:stuReadAutoReport(thisContext)
		,lock(locked)
	{
		lock.Lock();
	}
	~stuReadAutoReportEx()
	{
		lock.Unlock();
	}
private:
	SpinLock& lock;
};

class FT_PROTOCAL_API CProtocalLayer
{
public:
	CProtocalLayer(  );
	virtual ~CProtocalLayer();

	virtual unsigned char PROT_WR_SYNC( const stuReadWriteSr& wr ){ return ERROR_CODE_INVALID_COMMAND; }

	virtual inline unsigned char GetIoCommand() { return ERROR_CODE_INVALID_COMMAND; }

	virtual unsigned char GetAutoReport( stuReadAutoReport& autoReport ) { return ERROR_CODE_INVALID_COMMAND; }

	virtual BOOL AnalyzeRecvAndMark( const unsigned char* buffer, int iLength, unsigned int& kindofPacket ) { return FALSE; }
};

FT_PROTOCAL_API CProtocalLayer* GetProtocalByType( unsigned char type );

/**************************************************************************************/
#endif