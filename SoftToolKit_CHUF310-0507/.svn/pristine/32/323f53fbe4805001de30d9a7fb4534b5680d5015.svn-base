#pragma once
#include "GraphItemTest.h"
#define MAX_RECT_IN_LINE      100
#define MAX_LINE_IN_LINEARITY 12

struct RectKey 
{
	RectTP rcKey;            //按键的绘图区域
	bool bValidKey;         //是否是有效按键 按键<=4
	bool bPressed;          //按键是否已经被按到
	bool bUseKey;           //是否使用Value
	unsigned short state;   //状态
	unsigned short num;     //编号
	union UKey{
		RECT rcKeyTouch;        //按键的TP报点区域
		int iKeyValue;          //按键的TP报点值
	} uKey;
	RectKey():bValidKey( false ),bPressed(false),bUseKey(false),state(0), num(0){} 
};

class CLinearityTPadTest : public CGraphItemTest
{
public:
	CLinearityTPadTest( LPVOID lp );
	virtual ~CLinearityTPadTest();

	virtual bool StartCaculate( UINT32& uCombineRest );
	virtual void ResultBack( UINT32& uCombineRest ) override;

	virtual void DoInit( int iDeviceIndex = 0 );
	//virtual void ResetData();
	void AddPoint( int index, int xPoint, int yPoint, unsigned char bStrength = 0 );
	void DoPaint( HDC dc, const typeRect& rc );

private:
	static bool PointInRect( const RECT& rc, const POINT& pt );
	void DrawSquares(HDC dc, const typeRect& rc );
	void Rule();
	void KeyInit();
private:
	bool m_bDrawUpDown;
	tstring m_strMsgTip;

	RectKey m_ArrayKey[8];
	unsigned short step;

};