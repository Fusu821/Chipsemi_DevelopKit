#pragma once 
#include "GraphTool.h"
#include "onlinelog.h"
#include "../../Config/Config.h"
#include <tchar.h>
#define MAX_NUM_POINT       10
#define MAX_POINT_NUM       10000

#define	RESULT_NULL			0
#define	RESULT_PASS			1
#define	RESULT_NG		    2
#define	RESULT_TESTING		3
#define	RESULT_TBD			4
#define	RESULT_REPLACE		5
#define	RESULT_CONNECTING	6

#define ResultCombine( x, y ) (((x) << 16) | (y))
#define ResultFinished( x )   (((x) & 0xFFFF0000) >> 16)
#define ResultState( x )      ((x) & 0x0000FFFF)

typedef TypePoint PointTP;
typedef typeRect  RectTP;
struct TypePointReceive
{
public:
	PointTP ArrayPoint[MAX_POINT_NUM];
	int iPointNum;
	TypePointReceive():iPointNum(0){}
	void DoInit() { iPointNum = 0; }
	void AddPoint( int x, int y ) 
	{ 
		if( x == 0xffff )                  return;
		if( y == 0xffff )                  return;
		if( iPointNum >= MAX_POINT_NUM ||iPointNum < 0)
		{
			iPointNum=0;
			return;
		}
		else
		{
			ArrayPoint[iPointNum++] = PointTP( x, y );
		}
	} 
};
struct GraphGDI
{
	HDC dc;
	int width;
	int height;
	GraphGDI( HDC hdc, int iWidth, int iHeight )
		:dc( hdc )
		,width( iWidth )
		,height( iHeight )
	{

	}
};
struct GraphParam 
{
	int dev;
    CGraphTool& tool;
	GraphParam( int idev, CGraphTool& ctool )
		:dev(idev)
		,tool(ctool)
	{

	}
};
class CGraphItemTest
{
public:
	CGraphItemTest( LPVOID lp );
	virtual ~CGraphItemTest();
public:
	virtual BOOL LoopAndDone(  );

	virtual void Exit(  );

	virtual void DoInit( int iDeviceIndex = 0 );

	virtual void AddPoint( int index, int xPoint, int yPoint, unsigned char bStrength = 0 );

	virtual void DoPaint( HDC dc, const RectTP& rc );

	void GraphRefresh( HDC dcMem, const RectTP& rect );

	virtual void ResetData();

	StateType GetCurrentTestState(  ) const;

	void SetCurrentStatte( StateType state );

	int GetTimeLeft();

	bool DeCreaseOneSecond(  );

	bool Tick();

	virtual bool StartCaculate( UINT32& uCombineRest ) = 0;

	virtual void ResultBack( UINT32& uCombineRest )    = 0;

	virtual BOOL AreYouOK();
protected:
	//是否停止测试
	bool m_bExitLoop;
	//设备号
	unsigned char m_deviceNo;
	//当前测试状态 NG PASS NULL
	StateType m_stateTest;
	//最大NG次数
	int m_iNgCount;
	//测试时间限制
	int m_iTimeLeft;
	//已经完成的步骤
	int m_iStepFinished;
	//接受到的数据
	TypePointReceive m_PointReceive[MAX_NUM_POINT];
	//绘图区域
	RectTP m_paintRect;
	//绘图工具
	CGraphTool& m_paintTool;
	//记录上一次报点标记 用于下次对比
	unsigned char m_lastMask;
};

class ctp_report_parse
{
public:
	ctp_report_parse( unsigned short icSubType, unsigned char* buffer );
	~ctp_report_parse();

public:
	unsigned short msk();

	unsigned char tcnt();

	bool valid();

	unsigned short X( int index );
	
	unsigned short Y( int index );

	unsigned short ID( int index );

private:
	unsigned short subType;
	unsigned char* bufferAddrCopy;

};