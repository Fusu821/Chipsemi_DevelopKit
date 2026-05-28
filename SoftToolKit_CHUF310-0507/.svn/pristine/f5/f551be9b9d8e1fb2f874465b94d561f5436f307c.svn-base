#pragma once
#include "GraphItemTest.h"
#define MAX_RECT_IN_LINE_EXP      100
#define MAX_LINE_IN_LINEARITY_EXP 12

struct LineRect
{
    bool bValideRect;           //是否有效区域
    RECT rtypeRect;                //矩形区域
    UINT32 uPressedState;         //是否已经被按下
};

struct OneLinearity_Exp
{
    bool bHorizontal;   //水平划线
    bool bVertical;		//垂直划线
    bool bDiagonal_45; //45度斜线
    bool bDiagonal_135; //135度斜线
    bool bValideLine;	//是否为勾选的线条
    bool bAllPressed;	//这条线是否画完
    //bool bLinearity;
    bool bCurShow;		//是不是当前正在画的线
    int  lineEdge;		//小rect距离两边的距离
    RECT lineRc;		//用来保存小方格的，V：左右；H:上下
    LineRect arrayRect[MAX_RECT_IN_LINE_EXP];
};

class DLinearityTest : public CGraphItemTest
{
public:
    DLinearityTest( LPVOID lp );
    virtual ~DLinearityTest();

    virtual bool StartCaculate( UINT32& uCombineRest );
    virtual void ResultBack( UINT32& uCombineRest );

    virtual void DoInit( int iDeviceIndex = 0 );
    virtual void ResetData();
    void AddPoint( int index, int xPoint, int yPoint, unsigned char bStrength = 0 );  //hww add
    void DoPaint( HDC dc, const typeRect& rc );

private:
    void CalPaintRect( OneLinearity_Exp& line, const typeRect& rcPos, int index );
    void CalPaintRect( OneLinearity_Exp& line,  const typeRect& rcPos);
    void CalPaintRect_Diagonal( OneLinearity_Exp& line,  const typeRect& rcPos);
    void PaintLine( HDC dc, OneLinearity_Exp& line, int index );
    void ShowNextLine();
    bool CaculateLinearity( OneLinearity_Exp& line );
    bool CaculateEdgeRech( OneLinearity_Exp& line );
    bool CheckBound( OneLinearity_Exp& line );
    int TotalLineToShow();
    //bool AreaNeedPaint( int iDevice, int index );
    void PaintLimitLine( HDC dc, OneLinearity_Exp& line );
    static bool PointInRect( const RECT& rc, const POINT& pt );
private:
    OneLinearity_Exp m_ArrayLine[MAX_LINE_IN_LINEARITY_EXP];
    bool m_bDrawUpDown;
    tstring m_strMsgTip;
};