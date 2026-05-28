#include "GraphTool.h"
#include <math.h>
#include <tchar.h>
CGraphTool::~CGraphTool()
{
	for ( map<UINT32, HBRUSH>::iterator it = m_mapBrush.begin(); it != m_mapBrush.end(); ++it )
	{
		if( NULL != it->second ) ::DeleteObject( it->second );
	}
}
HBRUSH CGraphTool::GetSolidBrushByType( UINT32 iType )
{
	map<UINT32, HBRUSH>::iterator it = m_mapBrush.find( iType );
	if( it == m_mapBrush.end() )  
	{
		//创建新的BRUSH
		HBRUSH brush = ::CreateSolidBrush( (COLORREF)iType );
		m_mapBrush[iType] = brush;
		it = m_mapBrush.find( iType );
	}

	return it->second;
}
HPEN CGraphTool::GetPenByType( const TypePen& type )
{
	map<TypePen, HPEN>::iterator it = m_mapPen.find( type );
	if( it == m_mapPen.end() )  
	{
		//创建新的PEN
		HPEN pen = ::CreatePen( type.style, type.width, type.color );
		m_mapPen[type] = pen;
		it = m_mapPen.find( type );
	}

	return it->second;
}
HFONT CGraphTool::GetFontByType( const TypeFont& type )
{
	map<TypeFont, HFONT>::iterator it = m_mapFont.find( type );
	if( it == m_mapFont.end() )  
	{
		//创建新的PEN
		HFONT hFont = ::CreateFont( type.iHeight,
			                     type.iWidth,
								 0,                         // nEscapement
								 0,                         // nOrientation
								 type.iWeight,              // nWeight
								 FALSE,                     // bItalic
								 type.bLine,                // bUnderline
								 0,                         // cStrikeOut
								 ANSI_CHARSET,              // nCharSet
								 OUT_DEFAULT_PRECIS,        // nOutPrecision
								 CLIP_DEFAULT_PRECIS,       // nClipPrecision
								 DEFAULT_QUALITY,           // nQuality
								 DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
								 type.strName.c_str() );
		m_mapFont[type] = hFont;
		it = m_mapFont.find( type );
	}

	return it->second;
}
CGraphMemDC& CGraphTool::CreateMemDC( HDC pDC, const typeRect& rect )
{
	m_rc = rect;

	m_memDC.CreateMemoryDC( pDC, rect );

	return m_memDC;
}
CGraphMemDC& CGraphTool::GetMemDc()
{
     return m_memDC;
}
typeRect& CGraphTool::GetPaintRect()
{
	return m_rc;
}
tstring CGraphTool::GetStringByState( StateType state )
{
    if( state == STATE_NULL )          return _T("");
	else if( state == STATE_PASS )     return _T("PASS");
	else if( state == STATE_NG )       return _T("NG");
	else if( state == STATE_TESTING )  return _T("TESTING");
	else if( state == STATE_UPFTOUCH ) return _T("UP FROM TOUCH");

	return _T("UnKnow");
}


void CUIRenderEx::DrawRectangle( HDC& hDC, const RECT& rc, HBRUSH hBrush )
{
	HBRUSH oldBrush = (HBRUSH)::SelectObject( hDC, hBrush );
	Rectangle( hDC, rc.left, rc.top, rc.right, rc.bottom );
	::SelectObject( hDC, oldBrush );
}
void CUIRenderEx::DrawRectangle( HDC& hDC, const RECT& rc, HPEN pen )
{
	DrawLine( hDC, TypePoint( rc.left, rc.top ), TypePoint( rc.right, rc.top ), pen );
	DrawLine( hDC, TypePoint( rc.right, rc.top ), TypePoint( rc.right, rc.bottom ), pen );
	DrawLine( hDC, TypePoint( rc.right, rc.bottom  ), TypePoint( rc.left, rc.bottom ), pen );
	DrawLine( hDC, TypePoint( rc.left, rc.bottom ), TypePoint( rc.left, rc.top ), pen );
}
void CUIRenderEx::DrawText( HDC& hDC, const RECT& rc, HFONT hFont, COLORREF color, LPCTSTR pText, DWORD dwStyle /*= DT_CENTER|DT_VCENTER*/ )
{
    if( NULL == pText )  return;
	HFONT oldFont = (HFONT)::SelectObject( hDC, hFont );
	::SetBkMode( hDC, TRANSPARENT );
	::SetTextColor( hDC, color );
	::DrawText( hDC, pText, (int)_tcslen( pText ), (LPRECT)&rc, dwStyle );
	::SelectObject( hDC, oldFont );
}
void CUIRenderEx::DrawLine( HDC& hDC, const POINT& ptStart, const POINT& ptEnd, HPEN pen )
{
	HPEN oldPen = (HPEN)::SelectObject( hDC, pen );
	::MoveToEx( hDC, ptStart.x, ptStart.y, (LPPOINT)&ptStart );
	::LineTo( hDC, ptEnd.x, ptEnd.y );
	::SelectObject( hDC, oldPen );
}
// void CUIRenderEx::DrawRount( HDC& hDC, const RECT& rc, HBRUSH hBrush )
// {
// 	HBRUSH oldBrush = (HBRUSH)::SelectObject( hDC, hBrush );
// 	RoundRect( hDC, rc.left, rc.top, rc.right, rc.bottom, rc.right - rc.left, rc.bottom - rc.top );
// 	::SelectObject( hDC, oldBrush );
// }
void CUIRenderEx::DrawEllipse( HDC& hDC, const RECT& rc, HBRUSH hBrush )
{
	HBRUSH oldBrush = (HBRUSH)::SelectObject( hDC, hBrush );
	Ellipse( hDC, rc.left, rc.top, rc.right, rc.bottom );
	::SelectObject( hDC, oldBrush );
}
void CUIRenderEx::DrawEllipse( HDC& hDC, int x, int y, int r, HBRUSH hBrush, HPEN hPen )
{
    HBRUSH oldBrush = (HBRUSH)::SelectObject(hDC, hBrush);
    HPEN oldPen = (HPEN)::SelectObject(hDC, hPen);
    Ellipse(hDC,x-r,y-r,x+r,y+r);
    ::SelectObject(hDC, oldBrush);
    ::SelectObject(hDC, oldPen);
}
void CUIRenderEx::DrawEmptyRound( HDC& hDC, const RECT& rc, HPEN hPen )
{
	HPEN oldPen = (HPEN)::SelectObject( hDC, hPen );
	Arc( hDC, rc.left, rc.top, rc.right, rc.bottom, rc.left, rc.top, rc.right, rc.bottom );
	Arc( hDC, rc.right, rc.bottom, rc.left, rc.top, rc.right, rc.bottom, rc.left, rc.top );
	::SelectObject( hDC, oldPen );
}
void CUIRenderEx::DrawSector( HDC& hDC, POINT ptCenter, double dwAngStart, double dwAngEnd, int dwRadiusFrom, int dwRadiusTo, HPEN hPen, HBRUSH hBrush )
{
    HBRUSH oldBrush = (HBRUSH)::SelectObject( hDC, hBrush );

	POINT pt;

	BeginPath( hDC );
	pt.x = ptCenter.x + (int)(dwRadiusFrom * cos(dwAngStart * PI / 180));
	pt.y = ptCenter.y + (int)(-dwRadiusFrom * sin(dwAngStart * PI / 180));
    MoveToEx( hDC, pt.x, pt.y, &pt );
	AngleArc( hDC, ptCenter.x, ptCenter.y, dwRadiusFrom, (float)dwAngStart, (float)(dwAngEnd-dwAngStart) );
    //pt.x = ptCenter.x + (int)(dwRadiusFrom * cos(dwAngEnd * PI / 180));
	//pt.y = ptCenter.y + (int)(-dwRadiusFrom * sin(dwAngEnd * PI / 180));
	//MoveToEx( hDC, pt.x, pt.y, &pt );
	pt.x = ptCenter.x + (int)(dwRadiusTo * cos(dwAngEnd * PI / 180));
	pt.y = ptCenter.y + (int)(-dwRadiusTo * sin(dwAngEnd * PI / 180));
	LineTo( hDC, pt.x, pt.y );
    AngleArc( hDC, ptCenter.x, ptCenter.y, dwRadiusTo, (float)dwAngEnd, (float)(dwAngStart-dwAngEnd) );
	//pt.x = ptCenter.x + (int)(dwRadiusTo * cos(dwAngStart * PI / 180));
	//pt.y = ptCenter.y + (int)(-dwRadiusTo * sin(dwAngStart * PI / 180));
	//MoveToEx( hDC, pt.x, pt.y, &pt );
	pt.x = ptCenter.x + (int)(dwRadiusFrom * cos(dwAngStart * PI / 180));
	pt.y = ptCenter.y + (int)(-dwRadiusFrom * sin(dwAngStart * PI / 180));
	LineTo( hDC, pt.x, pt.y );
	EndPath( hDC );
	
 	HRGN region;  
 	region = PathToRegion( hDC );

	PaintRgn( hDC, region ); 
	DeleteObject( region );

	::SelectObject( hDC, oldBrush );

 	HPEN oldPen = (HPEN)::SelectObject( hDC, hPen );
 	pt.x = ptCenter.x + (int)(dwRadiusFrom * cos(dwAngEnd * PI / 180));
 	pt.y = ptCenter.y + (int)(-dwRadiusFrom * sin(dwAngEnd * PI / 180));
 	MoveToEx( hDC, pt.x, pt.y, &pt );
 	pt.x = ptCenter.x + (int)(dwRadiusTo * cos(dwAngEnd * PI / 180));
 	pt.y = ptCenter.y + (int)(-dwRadiusTo * sin(dwAngEnd * PI / 180));
 	LineTo( hDC, pt.x, pt.y );
 
 	pt.x = ptCenter.x + (int)(dwRadiusTo * cos(dwAngStart * PI / 180));
 	pt.y = ptCenter.y + (int)(-dwRadiusTo * sin(dwAngStart * PI / 180));
 	MoveToEx( hDC, pt.x, pt.y, &pt );
 	pt.x = ptCenter.x + (int)(dwRadiusFrom * cos(dwAngStart * PI / 180));
 	pt.y = ptCenter.y + (int)(-dwRadiusFrom * sin(dwAngStart * PI / 180));
 	LineTo( hDC, pt.x, pt.y );
 	
 	::SelectObject( hDC, oldPen );
}
void CUIRenderEx::DrawEmptySector( HDC& hDC, POINT ptCenter, double dwAngStart, double dwAngEnd, int dwRadiusFrom, int dwRadiusTo, HPEN hPen )
{
	HPEN oldPen = (HPEN)::SelectObject( hDC, hPen );

	POINT pt;

	pt.x = ptCenter.x + (int)(dwRadiusFrom * cos(dwAngStart * PI / 180));
	pt.y = ptCenter.y + (int)(-dwRadiusFrom * sin(dwAngStart * PI / 180));
	MoveToEx( hDC, pt.x, pt.y, &pt );
	AngleArc( hDC, ptCenter.x, ptCenter.y, dwRadiusFrom, (float)dwAngStart, (float)(dwAngEnd-dwAngStart) );
	pt.x = ptCenter.x + (int)(dwRadiusTo * cos(dwAngEnd * PI / 180));
	pt.y = ptCenter.y + (int)(-dwRadiusTo * sin(dwAngEnd * PI / 180));
	LineTo( hDC, pt.x, pt.y );
	AngleArc( hDC, ptCenter.x, ptCenter.y, dwRadiusTo, (float)dwAngEnd, (float)(dwAngStart-dwAngEnd) );
	pt.x = ptCenter.x + (int)(dwRadiusFrom * cos(dwAngStart * PI / 180));
	pt.y = ptCenter.y + (int)(-dwRadiusFrom * sin(dwAngStart * PI / 180));
	LineTo( hDC, pt.x, pt.y );

	::SelectObject( hDC, oldPen );
}

SM_TEST_CSTYLE_API void ScreenXYChange( long x, long y, long& outX, long& outY, const RECT& tp, const RECT& pc )
{
	if( 0 == tp.right - tp.left ) return;
	if( 0 == tp.bottom - tp.top)  return;
	outX = (x - 0) * (pc.right - pc.left) / (tp.right - tp.left) + pc.left;
	outY = (y - 0) * (pc.bottom - pc.top) / (tp.bottom - tp.top) + pc.top;
}