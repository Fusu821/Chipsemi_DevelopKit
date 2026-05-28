#pragma once
#include "GraphItemTest.h"
struct RectKey 
{
	RectTP rcKey;            //按键的绘图区域
	bool bValidKey;         //是否是有效按键 按键<=4
	bool bPressed;          //按键是否已经被按到
	bool bUseKey;           //是否使用Value
	union UKey{
		RECT rcKeyTouch;        //按键的TP报点区域
        int iKeyValue;          //按键的TP报点值
	} uKey;
	RectKey():bValidKey( false ),bPressed(false),bUseKey(false){} 
};
class CVirtualButtonTest : public CGraphItemTest
{
	#define MAX_KEY_RECT 48
public:
	CVirtualButtonTest( LPVOID lp );
	virtual ~CVirtualButtonTest();

	//virtual bool IsTestUseValue() const;
	virtual void DoInit( int iDeviceIndex = 0 );
	virtual void AddValue( int iValue );
	virtual void AddPoint( int index, int xPoint, int yPoint, unsigned char bStrength = 0 );   //hww add
	virtual void DoPaint( HDC dc, const RectTP& rc );
    virtual bool StartCaculate( UINT32& uCombineRest );
	virtual void ResultBack( UINT32& uCombineRest );

	static bool PointInRect( const RECT& rc, const POINT& pt );
private:
    RectKey m_ArrayKey[MAX_KEY_RECT];
	//打印坐标点
	tstring m_strKeyMsg;
	tstring m_strAllMsg;
	bool m_bFirstMsg;
};