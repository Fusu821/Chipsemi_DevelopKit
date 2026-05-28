#pragma once
#include "Macro.h"
#include <map>
using namespace std;
#define PI 3.14159
enum StateType
{
	STATE_NULL     = RGB(192,192,192),
	STATE_PASS     = RGB(0,200,0),
	STATE_NG       = RGB(250,0,0),
	STATE_TESTING  = RGB(250,125,0),
	STATE_UPFTOUCH = RGB(250,125,10),
	STATE_READY    = RGB(255, 255 ,0),   //hww add 准备测试时颜色为黄色
};

struct TypePen 
{
	int style; 
	int width;
	COLORREF color;
	TypePen(){}
	TypePen( int iStyle, int iWidth, int iColor ) 
		:style( iStyle )
		,width( iWidth )
		,color( iColor )
	{

	}
	bool operator < ( const TypePen& pen ) const
	{
        if( style < pen.style )       return true;
		else if( style > pen.style )  return false;
		else if( width < pen.width )  return true;
		else if( width > pen.width )  return false;
		else if( color < pen.color )  return true;
		else if( color > pen.color )  return false;
		return false;
	}
};
struct TypeFont
{
	int iHeight;
	int iWidth;
	bool bLine;
    int iWeight;
	tstring strName;
	TypeFont() {}
	TypeFont( int height, int width, int weight, bool line, LPCTSTR name )
		:iHeight( height ),iWidth(width),bLine(line),iWeight(weight),strName(name)
	{
	}
	bool operator < ( const TypeFont& type ) const
	{
		if( iHeight < type.iHeight )       return true;
		else if( iHeight > type.iHeight )  return false;
		if( iWidth < type.iWidth )         return true;
		else if( iWidth > type.iWidth )    return false;
		if( iWeight < type.iWeight )       return true;
		else if( iWeight > type.iWeight )  return false;
		if( bLine < type.bLine )           return true;
		else if( bLine > type.bLine )      return false;
		if( icomparetext( strName.c_str(), type.strName.c_str() ) < 0 )       return true;
		else if( icomparetext( strName.c_str(), type.strName.c_str() ) > 0 )  return false;
		else return false;
	}
};
struct TypePoint : public POINT
{
	TypePoint()
	{
		this->x = 0;
		this->y = 0;
	}
	TypePoint( LONG xp, LONG yp )
	{
		this->x = xp;
		this->y = yp;
	}
};
struct typeRect : public RECT 
{
	typeRect()
	{
		this->left = 0;
		this->top = 0;
		this->right = 0;
		this->bottom = 0;
	}
	typeRect( long left, LONG top, LONG right, LONG bottom )
	{
		this->left = left;
		this->top = top;
		this->right = right;
		this->bottom = bottom;
	}
	typeRect( const RECT& rc )
	{
		this->left = rc.left;
		this->top = rc.top;
		this->right = rc.right;
		this->bottom = rc.bottom;
	}
	int Width() const
	{
		return right - left;
	}
	int Height() const
	{
		return bottom - top;
	}
};

class CGraphMemDC
{
public:
	CGraphMemDC()
		:m_iSaveDC(0)
		,m_hNewBitmap(NULL)
		,m_dcMem(NULL)
		,m_hOldBitmap(NULL)
	{

	}
	operator HDC&(  )
	{
		return m_dcMem;
	}
	void CreateMemoryDC( HDC hdc, const RECT& rect )
	{
		Clear();
		m_rect = rect;
		m_dcMem = ::CreateCompatibleDC( hdc );
		m_hNewBitmap = ::CreateCompatibleBitmap( hdc, rect.right-rect.left, rect.bottom-rect.top );
	}
	~CGraphMemDC()
	{
		::SelectObject( m_dcMem, m_hOldBitmap );
		Clear();
	}
	RECT GetRect()
	{
		return m_rect;
	}
	bool IsMemDcValid(  )
	{
		return m_dcMem != NULL || m_hNewBitmap != NULL;
	}
	void BitBlt( HDC dcDes, RECT& rect, int iXStart, int iYStart, WORD dwMode )
	{
		::BitBlt( dcDes, rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top, m_dcMem, iXStart, iYStart, dwMode );
	}
	int SaveMemDC()
	{
		m_hOldBitmap = (HBITMAP)::SelectObject( m_dcMem, m_hNewBitmap );
		return m_iSaveDC = ::SaveDC( m_dcMem );
	}
	void RestoreMemDC( int iSavedDC = 0 )
	{
		if( 0 == iSavedDC ) iSavedDC = m_iSaveDC;
		::RestoreDC( m_dcMem, iSavedDC );
	}
	void Clear()
	{
		if( NULL != m_dcMem ) ::DeleteDC( m_dcMem );
		if( NULL != m_hNewBitmap ) ::DeleteObject( m_hNewBitmap );
		m_dcMem = NULL;
		m_hNewBitmap = NULL;
	}
private:
	HBITMAP m_hNewBitmap;
	HBITMAP m_hOldBitmap;
	RECT    m_rect;
	HDC     m_dcMem;
	int     m_iSaveDC;
};
class CGraphTool
{
public:
	CGraphTool(){};
	virtual ~CGraphTool();
private:
	CGraphTool( const CGraphTool& );

public:
	HBRUSH GetSolidBrushByType( UINT32 iType );
	HPEN GetPenByType( const TypePen& type );
	HFONT GetFontByType( const TypeFont& type );
    CGraphMemDC& CreateMemDC( HDC pDC, const typeRect& rect );
    CGraphMemDC& GetMemDc();
	typeRect& GetPaintRect();
	tstring GetStringByState( StateType state );
private:
	map<UINT32, HBRUSH> m_mapBrush;
	map<TypePen, HPEN>   m_mapPen; 
	map<TypeFont, HFONT> m_mapFont;
	CGraphMemDC m_memDC;
	typeRect m_rc;
};
class CUIRenderEx 
{
public:
    static void DrawRectangle( HDC& hDC, const RECT& rc, HBRUSH hBrush );
	static void DrawRectangle( HDC& hDC, const RECT& rc, HPEN pen );
	static void DrawText( HDC& hDC, const RECT& rc, HFONT hFont, COLORREF color, LPCTSTR pText, DWORD dwStyle = DT_CENTER|DT_VCENTER );
	static void DrawLine( HDC& hDC, const POINT& ptStart, const POINT& ptEnd, HPEN pen );
	//static void DrawRount( HDC& hDC, const RECT& rc, HBRUSH hBrush );
	static void DrawEllipse( HDC& hDC, const RECT& rc, HBRUSH hBrush );
    static void DrawEllipse( HDC& hDC, int x, int y, int r, HBRUSH hBrush, HPEN hPen );
	static void DrawEmptyRound( HDC& hDC, const RECT& rc, HPEN hPen );
	static void DrawSector( HDC& hDC, POINT ptCenter, double dwAngStart, double dwAngEnd, int dwRadiusFrom, int dwRadiusTo, HPEN hPen, HBRUSH hBrush );
	static void DrawEmptySector( HDC& hDC, POINT ptCenter, double dwAngStart, double dwAngEnd, int dwRadiusFrom, int dwRadiusTo, HPEN hPen );
};