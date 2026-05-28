#include "LinearityTest.h"
#include "../TestBase.h"
extern CConfig* G_XMLConfig;

REGIST_RUNTIME_CLASS_PVOID(GRAPH_TYPE, (GRAPH_TYPE)TEST_ITEM_LINEARLY_TEST, CLinearityTest)
CLinearityTest::CLinearityTest( LPVOID lp )
:CGraphItemTest( lp )
,m_bDrawUpDown( false )
,m_strMsgTip( _T("") )
{

}
CLinearityTest::~CLinearityTest()
{

}
void CLinearityTest::DoInit( int iDeviceIndex /*= 0*/ )
{
	CGraphItemTest::DoInit( iDeviceIndex );
	memset( m_ArrayLine, 0, sizeof( m_ArrayLine ) );
	m_iStepFinished = 0;
	m_iNgCount = 0;
	m_iTimeLeft = G_XMLConfig->iLinearityLimitTime;

	bool bHasShowLine = false;
	for ( int index = 0; index < 6; ++index )
	{
		if( G_XMLConfig->Position_Linearity & ( 1 << index ) ){
			//if( !AreaNeedPaint( iDeviceIndex, index ) )    continue;
			m_ArrayLine[index].bCurShow    = !bHasShowLine;
			m_ArrayLine[index].bValideLine = true;
			m_ArrayLine[index].bVertical   = false;
			if( !bHasShowLine ) bHasShowLine = true;
		}
	}
	for ( int index = 6; index < 12; ++index )
	{
		//index以6开头 实际数据存储下标以6开头
		if( G_XMLConfig->Position_Linearity & ( 1 << index ) ){
			m_ArrayLine[index].bCurShow    = !bHasShowLine;
			m_ArrayLine[index].bValideLine = true;
			m_ArrayLine[index].bVertical   = true;
			if( !bHasShowLine ) bHasShowLine = true;
		}
	}
	ResetData();
}
void CLinearityTest::ResetData()
{
	CGraphItemTest::ResetData();
	m_bDrawUpDown = false;
	m_strMsgTip = _T("");
	for ( int index = 0; index < MAX_LINE_IN_LINEARITY; ++index )
	{
		if( !m_ArrayLine[index].bValideLine )  continue;
		if( !m_ArrayLine[index].bCurShow )     continue;
		//m_ArrayLine[index].bLinearity  = false;
		m_ArrayLine[index].bAllPressed = false;
		for ( int iCount = 0; iCount < MAX_RECT_IN_LINE; ++iCount )
		{
			LineRect& rcItem = m_ArrayLine[index].arrayRect[iCount];
			if( !rcItem.bValideRect ) break;
			rcItem.uPressedState = RESULT_NULL;
		}
	}
}
// bool CLinearityTest::AreaNeedPaint( int iDevice, int index )
// {
// 	if( 0 == index ){
// 		if( 1 == G_XMLConfig->Area_H1 ) return g_stLinearityTest[iDevice].bArea1Test;
// 		else                                 return g_stLinearityTest[iDevice].bArea2Test;
// 	}
// 	else if( 1 == index ){
// 		if( 1 == G_XMLConfig->Area_H2 ) return g_stLinearityTest[iDevice].bArea1Test;
// 		else                                 return g_stLinearityTest[iDevice].bArea2Test;
// 	}
// 	else if( 2 == index ){
// 		if( 1 == G_XMLConfig->Area_H3 ) return g_stLinearityTest[iDevice].bArea1Test;
// 		else                                 return g_stLinearityTest[iDevice].bArea2Test;
// 	}
// 	else if( 3 == index ){
// 		if( 1 == G_XMLConfig->Area_H4 ) return g_stLinearityTest[iDevice].bArea1Test;
// 		else                                 return g_stLinearityTest[iDevice].bArea2Test;
// 	}
// 	else if( 4 == index ){
// 		if( 1 == G_XMLConfig->Area_H5 ) return g_stLinearityTest[iDevice].bArea1Test;
// 		else                                 return g_stLinearityTest[iDevice].bArea2Test;
// 	}
// 	else if( 5 == index ){
// 		if( 1 == G_XMLConfig->Area_H6 ) return g_stLinearityTest[iDevice].bArea1Test;
// 		else                                 return g_stLinearityTest[iDevice].bArea2Test;
// 	}
// 
// 	return true;
// }
//最大最小点卡在Distance_Linearity中间
bool CLinearityTest::CaculateLinearity( OneLinearity& line )
{
	bool bLinearity = false;
    if( !line.bValideLine )    return false;
	if( !line.bCurShow )       return false;
	if( !line.bAllPressed )    return false;
	//遍历所有的数据点 去最大 最小 以及差值
	int iMax = 0, iMin = 1000000, iDiff = 0;
	for ( int index = 0; index < m_PointReceive[0].iPointNum; ++index )
	{ 
		PointTP& pt = m_PointReceive[0].ArrayPoint[index];
		if( line.bVertical ){
			iMax = max( iMax, pt.x );
			iMin = min( iMin, pt.x );
		}
		else{
			iMax = max( iMax, pt.y );
			iMin = min( iMin, pt.y );
		}
	}
	iDiff = iMax - iMin;
	if( iDiff <= G_XMLConfig->Distance_Linearity )  bLinearity = true;

	return bLinearity;
}
bool CLinearityTest::CaculateEdgeRech( OneLinearity& line )
{
	if( !line.bValideLine )    return false;
	if( !line.bCurShow )       return false;
	if( !line.bAllPressed )    return false;

	bool bRichEdge1 = false, bRichEdge2 = false;
	if( line.bVertical ){
		typeRect rcEdge1( line.lineRc.left, m_paintRect.top + line.lineEdge, line.lineRc.right, m_paintRect.bottom );
		typeRect rcEdge2( line.lineRc.left, m_paintRect.bottom - line.lineEdge, line.lineRc.right, m_paintRect.bottom );
		for ( int index = 0; index < m_PointReceive[0].iPointNum; ++index )
		{
			long xScreen = 0, yScreen = 0;
			PointTP& pt = m_PointReceive[0].ArrayPoint[index];
			typeRect rcTp(0, 0, G_XMLConfig->resolution_x, G_XMLConfig->resolution_y);
			ScreenXYChange( pt.x, pt.y, xScreen, yScreen, rcTp, m_paintRect );
			if( PointInRect( rcEdge1, TypePoint( xScreen, yScreen ) ) )
				bRichEdge1 = true;
			if( PointInRect( rcEdge2, TypePoint( xScreen, yScreen ) ) )
				bRichEdge2 = true;
		}
	}
	else{
        typeRect rcEdge1( m_paintRect.left, line.lineRc.top, m_paintRect.left + line.lineEdge, line.lineRc.bottom );
        typeRect rcEdge2( m_paintRect.right - line.lineEdge, line.lineRc.top, m_paintRect.right, line.lineRc.bottom );
		for ( int index = 0; index < m_PointReceive[0].iPointNum; ++index )
		{
			long xScreen = 0, yScreen = 0;
			PointTP& pt = m_PointReceive[0].ArrayPoint[index];
			typeRect rcTp(0, 0, G_XMLConfig->resolution_x, G_XMLConfig->resolution_y);
			ScreenXYChange( pt.x, pt.y, xScreen, yScreen, rcTp, m_paintRect );
			if( PointInRect( rcEdge1, TypePoint( xScreen, yScreen ) ) )
				bRichEdge1 = true;
			if( PointInRect( rcEdge2, TypePoint( xScreen, yScreen ) ) )
				bRichEdge2 = true;
		}
	}
    
	return (bRichEdge1 && bRichEdge2);
}
bool CLinearityTest::CheckBound( OneLinearity& line )
{
	if( !line.bValideLine )    return false;
	if( !line.bCurShow )       return false;
	if( !line.bAllPressed )    return false;
	for ( int index = 0; index < m_PointReceive[0].iPointNum; ++index )
	{
		long xScreen = 0, yScreen = 0;
		PointTP& pt = m_PointReceive[0].ArrayPoint[index];
		typeRect rcTp(0, 0, G_XMLConfig->resolution_x, G_XMLConfig->resolution_y);
		ScreenXYChange( pt.x, pt.y, xScreen, yScreen, rcTp, m_paintRect );
		if( line.bVertical ){
			if( xScreen < line.lineRc.left || xScreen > line.lineRc.right ) return false;
		}
		else{
			if( yScreen < line.lineRc.top || yScreen > line.lineRc.bottom ) return false;
		}
	}
	return true;
}
bool CLinearityTest::StartCaculate( UINT32& uCombineRest )
{
	m_bDrawUpDown = true;
    //计算之前 已经完成的画线
	int iLineFinished = m_iStepFinished;

	//计算测试之后新增的画线
	for ( int index = 0; index < MAX_LINE_IN_LINEARITY; ++index )
	{
		if( !m_ArrayLine[index].bValideLine ) continue;
		if( m_ArrayLine[index].bAllPressed )  continue;
		if( !m_ArrayLine[index].bCurShow )    continue;
		m_ArrayLine[index].bAllPressed = true;
		for ( int iCount = 0; iCount < MAX_RECT_IN_LINE; ++iCount )
		{
			LineRect& tcItem = m_ArrayLine[index].arrayRect[iCount];
			if( !tcItem.bValideRect ) break;
			if( RESULT_PASS == tcItem.uPressedState ) continue;
			m_ArrayLine[index].bAllPressed = false;
			break;
		}
		if( !m_ArrayLine[index].bAllPressed ){
			m_strMsgTip = _T("Didn't Paint All Gap");
		}
		else if( !CaculateEdgeRech( m_ArrayLine[index] ) ){
            m_strMsgTip = _T("Didn't Reach Edge");
		}
		else if( !CheckBound( m_ArrayLine[index] ) ){
            m_strMsgTip = _T("Out Of Bound");
		}
		else if( !CaculateLinearity( m_ArrayLine[index] ) ){
            m_strMsgTip = _T("Linearity Check Failed");
		}
		else{
			++m_iStepFinished;
		}
	}

	if( m_iStepFinished <= iLineFinished ) {
		++m_iNgCount;
	}
	else{
        ShowNextLine();
	}

	ResultBack( uCombineRest );

	return m_iStepFinished > iLineFinished;
}
void CLinearityTest::ResultBack( UINT32& uCombineRest )
{
	//判断是否所有的步骤已经完成
	uCombineRest = ResultCombine( 0, RESULT_NULL );

	//超过最大NG次数 测试完成 结果NG
	if( G_XMLConfig->iLinerityMaxNG && m_iNgCount >= G_XMLConfig->iLinerityMaxNG )  
	{
		uCombineRest = ResultCombine( 1, RESULT_NG );
	}
	//时间超出范围  测试完成 结果NG
	else if( G_XMLConfig->iLinearityLimitTime && m_iTimeLeft <= 0 )  
	{
		uCombineRest = ResultCombine( 1, RESULT_NG );
	}
	//完成的步骤 
	else if( m_iStepFinished == TotalLineToShow() ) 
	{
		uCombineRest = ResultCombine( 1, RESULT_PASS );
	}
}
void CLinearityTest::AddPoint( int index, int xPoint, int yPoint, unsigned char bStrength )
{
	if( G_XMLConfig->Shielded_Pixels_H ){
		if( yPoint < G_XMLConfig->Shielded_Pixels_H ) return;
		if( yPoint > G_XMLConfig->resolution_y - G_XMLConfig->Shielded_Pixels_H ) return;
	}
	if( G_XMLConfig->Shielded_Pixels ){
		if( xPoint < G_XMLConfig->Shielded_Pixels ) return;
		if( xPoint > G_XMLConfig->resolution_x - G_XMLConfig->Shielded_Pixels )   return;
	}

	CGraphItemTest::AddPoint( index, xPoint, yPoint );
	long xScreen = 0, yScreen  = 0;
	typeRect rcTp(0, 0, G_XMLConfig->resolution_x, G_XMLConfig->resolution_y);
	ScreenXYChange( xPoint, yPoint, xScreen, yScreen, rcTp, m_paintRect );
	for ( int index = 0; index < MAX_LINE_IN_LINEARITY; ++index )
	{
		if( !m_ArrayLine[index].bValideLine )  continue;
		if( !m_ArrayLine[index].bCurShow )     continue;
		for ( int iCount = 0; iCount < MAX_RECT_IN_LINE; ++iCount )
		{
			LineRect& rectItem = m_ArrayLine[index].arrayRect[iCount];
			if( !rectItem.bValideRect ) break;
			if( PointInRect( rectItem.rtypeRect, TypePoint( xScreen, yScreen ) ) )
				rectItem.uPressedState = RESULT_PASS;
		}
	}
}
void CLinearityTest::DoPaint( HDC dc, const typeRect& rc )
{
    for ( int index = 0; index < MAX_LINE_IN_LINEARITY; ++index )
    {
		OneLinearity& line = m_ArrayLine[index];
		if( !line.bValideLine ) continue;
        if( !line.bCurShow )    continue;
		CalPaintRect( line, rc, index );
		
		PaintLine( dc, line );
        if(0 != G_XMLConfig->Distance_Linearity )
        {
		    PaintLimitLine( dc, line );
        }
    }

	//如果有错误信息 就打印错误信息
	TypeFont typefont = TypeFont( 12, 8, FW_NORMAL, false, _T("宋体") );
	typeRect rcMsg( rc.left, rc.bottom - 100, rc.right, rc.bottom - 50 );
	CUIRenderEx::DrawText( dc, rcMsg, m_paintTool.GetFontByType( typefont ), RGB( 255, 255, 255 ), m_strMsgTip.c_str() );

	CGraphItemTest::DoPaint( dc, rc );
}
//限定线，划线新出现的界定线
void CLinearityTest::PaintLimitLine( HDC dc, OneLinearity& line )
{
    //绘制线性度的上下限虚线
	if( !m_bDrawUpDown )   return;
	if( !line.bCurShow )   return;
	int iMax = 0, iMin = 100000, iDiff = 0, iMid = 0;
	for ( int index = 0; index < m_PointReceive[0].iPointNum; ++index )
	{ 
		PointTP& pt = m_PointReceive[0].ArrayPoint[index];
		if( line.bVertical ){
			iMax = max( iMax, pt.x );
			iMin = min( iMin, pt.x );
		}
		else{
			iMax = max( iMax, pt.y );
			iMin = min( iMin, pt.y );
		}
	}

	iMid = ( iMin + iMax ) / 2;
	if( line.bVertical ){
		//double dwXScal = (double)m_paintRect.Width() / g_ScreenSetParam.ixMaxPixel;
		TypePen penType( PS_DOT, 1, RGB( 200, 255, 255 ) );
		TypePoint pt1, pt2;
		typeRect rcTp(0, 0, G_XMLConfig->resolution_x, G_XMLConfig->resolution_y);
		ScreenXYChange( iMid - G_XMLConfig->Distance_Linearity/2, 0, pt1.x, pt1.y, rcTp, m_paintRect );
		ScreenXYChange( iMid - G_XMLConfig->Distance_Linearity/2, G_XMLConfig->resolution_y, pt2.x, pt2.y, rcTp, m_paintRect );
		CUIRenderEx::DrawLine( dc, pt1, pt2, m_paintTool.GetPenByType( penType ) );
		TypePoint pt3, pt4;
		ScreenXYChange( iMid + G_XMLConfig->Distance_Linearity/2, 0, pt3.x, pt3.y, rcTp, m_paintRect );
		ScreenXYChange( iMid + G_XMLConfig->Distance_Linearity/2, G_XMLConfig->resolution_y, pt4.x, pt4.y, rcTp, m_paintRect );
		CUIRenderEx::DrawLine( dc, pt3, pt4, m_paintTool.GetPenByType( penType ) );	
	}
	else{
		//double dwYScal = (double)m_paintRect.Height() / g_ScreenSetParam.iyMaxPixel;
		TypePen penType( PS_DOT, 1, RGB( 200, 255, 255 ) );
		TypePoint pt1, pt2;
		typeRect rcTp(0, 0, G_XMLConfig->resolution_x, G_XMLConfig->resolution_y);
		ScreenXYChange( 0, iMid - G_XMLConfig->Distance_Linearity/2, pt1.x, pt1.y, rcTp, m_paintRect );
		ScreenXYChange( G_XMLConfig->resolution_x, iMid - G_XMLConfig->Distance_Linearity/2, pt2.x, pt2.y, rcTp, m_paintRect );
		CUIRenderEx::DrawLine( dc, pt1, pt2, m_paintTool.GetPenByType( penType ) );
		TypePoint pt3, pt4;
		ScreenXYChange( 0, iMid + G_XMLConfig->Distance_Linearity/2, pt3.x, pt3.y, rcTp, m_paintRect );
		ScreenXYChange( G_XMLConfig->resolution_x, iMid + G_XMLConfig->Distance_Linearity/2, pt4.x, pt4.y, rcTp, m_paintRect );
        CUIRenderEx::DrawLine( dc, pt3, pt4, m_paintTool.GetPenByType( penType ) );
	}
}
//上下边沿线
void CLinearityTest::PaintLine( HDC dc, OneLinearity& line )
{
	if( line.bVertical ){
		 //先绘制上下限的两条线
		TypePoint ptStart1( line.lineRc.left, line.lineRc.top );
		TypePoint ptEnd1( line.lineRc.left, line.lineRc.bottom );
		TypePoint ptStart2( line.lineRc.right, line.lineRc.top );
		TypePoint ptEnd2( line.lineRc.right, line.lineRc.bottom );
		
		TypePen typepen = TypePen( PS_SOLID, 1, RGB( 0, 255, 255 ) );
		CUIRenderEx::DrawLine( dc, ptStart1, ptEnd1, m_paintTool.GetPenByType( typepen ) );
		CUIRenderEx::DrawLine( dc, ptStart2, ptEnd2, m_paintTool.GetPenByType( typepen ) );

		//绘制Edge
        typepen = TypePen( PS_DASH, 1, RGB( 0, 255, 255 ) );
		CUIRenderEx::DrawLine( dc, TypePoint( line.lineRc.left, line.lineRc.top + line.lineEdge ), TypePoint( line.lineRc.right, line.lineRc.top + line.lineEdge ), m_paintTool.GetPenByType( typepen ) );
		CUIRenderEx::DrawLine( dc, TypePoint( line.lineRc.left, line.lineRc.bottom - line.lineEdge ), TypePoint( line.lineRc.right, line.lineRc.bottom - line.lineEdge ), m_paintTool.GetPenByType( typepen ) );
	}
	else{
		TypePoint ptStart1( line.lineRc.left, line.lineRc.top );
		TypePoint ptEnd1( line.lineRc.right, line.lineRc.top );
		TypePoint ptStart2( line.lineRc.left, line.lineRc.bottom );
		TypePoint ptEnd2( line.lineRc.right, line.lineRc.bottom );

		TypePen typepen = TypePen( PS_SOLID, 1, RGB( 0, 255, 255 ) );
		CUIRenderEx::DrawLine( dc, ptStart1, ptEnd1, m_paintTool.GetPenByType( typepen ) );
		CUIRenderEx::DrawLine( dc, ptStart2, ptEnd2, m_paintTool.GetPenByType( typepen ) );

		//绘制Edge
		typepen = TypePen( PS_DASH, 1, RGB( 0, 255, 255 ) );
		CUIRenderEx::DrawLine( dc, TypePoint( line.lineRc.left + line.lineEdge, line.lineRc.top  ), TypePoint( line.lineRc.left + line.lineEdge, line.lineRc.bottom ), m_paintTool.GetPenByType( typepen ) );
		CUIRenderEx::DrawLine( dc, TypePoint( line.lineRc.right - line.lineEdge, line.lineRc.top ), TypePoint( line.lineRc.right - line.lineEdge, line.lineRc.bottom ), m_paintTool.GetPenByType( typepen ) );
	}
	
	//绘制一系列的gap rect
	for ( int index = 0; index < MAX_RECT_IN_LINE; ++index )
	{
		LineRect& rect = line.arrayRect[index];
		if( !rect.bValideRect ) continue;
		if( RESULT_NULL == rect.uPressedState ){
			CUIRenderEx::DrawRectangle( dc, rect.rtypeRect, m_paintTool.GetSolidBrushByType( STATE_NULL ) );
		}
		else if( RESULT_NG == rect.uPressedState ){
            CUIRenderEx::DrawRectangle( dc, rect.rtypeRect, m_paintTool.GetSolidBrushByType( STATE_NG ) );
		}
		else if( RESULT_PASS == rect.uPressedState ){
			//CUIRenderEx::DrawRectangle( dc, rect.rtypeRect, m_paintTool.GetSolidBrushByType( STATE_PASS ) );
            CUIRenderEx::DrawRectangle( dc, rect.rtypeRect, m_paintTool.GetSolidBrushByType( RGB(0,0,0) ) );
		}
	}
}
void CLinearityTest::CalPaintRect( OneLinearity& line, const typeRect& rcPos, int index )
{
    double dwXScal = (double)rcPos.Width() / G_XMLConfig->resolution_x;
	double dwYScal = (double)rcPos.Height() / G_XMLConfig->resolution_y;
	if( !line.bVertical ){
		line.lineRc.left   = rcPos.left;
		line.lineRc.right  = rcPos.right;
		if( 0 == index ){
			line.lineRc.top    = (int)(G_XMLConfig->Upper_Limit_H1 * dwYScal) + rcPos.top;
			line.lineRc.bottom = (int)(G_XMLConfig->Lower_Limit_H1 * dwYScal) + rcPos.top; 
		}
		else if( 1 == index ){
			line.lineRc.top    = (int)(G_XMLConfig->Upper_Limit_H2 * dwYScal) + rcPos.top;
			line.lineRc.bottom = (int)(G_XMLConfig->Lower_Limit_H2 * dwYScal) + rcPos.top; 
		}
		else if( 2 == index ){
			line.lineRc.top    = (int)(G_XMLConfig->Upper_Limit_H3 * dwYScal) + rcPos.top;
			line.lineRc.bottom = (int)(G_XMLConfig->Lower_Limit_H3 * dwYScal) + rcPos.top; 
		}
		else if( 3 == index ){
			line.lineRc.top    = (int)(G_XMLConfig->Upper_Limit_H4 * dwYScal) + rcPos.top;
			line.lineRc.bottom = (int)(G_XMLConfig->Lower_Limit_H4 * dwYScal) + rcPos.top; 
		}
		else if( 4 == index ){
			line.lineRc.top    = (int)(G_XMLConfig->Upper_Limit_H5 * dwYScal) + rcPos.top;
			line.lineRc.bottom = (int)(G_XMLConfig->Lower_Limit_H5 * dwYScal) + rcPos.top; 
		}
		else if( 5 == index ){
			line.lineRc.top    = (int)(G_XMLConfig->Upper_Limit_H6 * dwYScal) + rcPos.top;
			line.lineRc.bottom = (int)(G_XMLConfig->Lower_Limit_H6 * dwYScal) + rcPos.top; 
		}
	}
	else {
		line.lineRc.top   = rcPos.top;
		line.lineRc.bottom  = rcPos.bottom;
		if( 6 == index ){
			line.lineRc.left    = (int)(G_XMLConfig->Upper_Limit_V1 * dwXScal) + rcPos.left;
			line.lineRc.right   = (int)(G_XMLConfig->Lower_Limit_V1 * dwXScal) + rcPos.left; 
		}
		else if( 7 == index ){
			line.lineRc.left    = (int)(G_XMLConfig->Upper_Limit_V2 * dwXScal) + rcPos.left;
			line.lineRc.right   = (int)(G_XMLConfig->Lower_Limit_V2 * dwXScal) + rcPos.left; 
		}
		else if( 8 == index ){
			line.lineRc.left    = (int)(G_XMLConfig->Upper_Limit_V3 * dwXScal) + rcPos.left;
			line.lineRc.right   = (int)(G_XMLConfig->Lower_Limit_V3 * dwXScal) + rcPos.left; 
		}
		else if( 9 == index ){
			line.lineRc.left    = (int)(G_XMLConfig->Upper_Limit_V4 * dwXScal) + rcPos.left;
			line.lineRc.right   = (int)(G_XMLConfig->Lower_Limit_V4 * dwXScal) + rcPos.left; 
		}
		else if( 10 == index ){
			line.lineRc.left    = (int)(G_XMLConfig->Upper_Limit_V5 * dwXScal) + rcPos.left;
			line.lineRc.right   = (int)(G_XMLConfig->Lower_Limit_V5 * dwXScal) + rcPos.left; 
		}
		else if( 11 == index ){
			line.lineRc.left    = (int)(G_XMLConfig->Upper_Limit_V6 * dwXScal) + rcPos.left;
			line.lineRc.right   = (int)(G_XMLConfig->Lower_Limit_V6 * dwXScal) + rcPos.left; 
		}
	}

	CalPaintRect( line, rcPos );
}
void CLinearityTest::CalPaintRect( OneLinearity& line,  const typeRect& rcPos )
{
	double dwXScal = (double)rcPos.Width() / G_XMLConfig->resolution_x;
	double dwYScal = (double)rcPos.Height() / G_XMLConfig->resolution_y;
	int iEdgeScreen = 0;
	if( line.bVertical ){
		iEdgeScreen = (int)(G_XMLConfig->Edge_Linearity * dwYScal);
        int iLineGAP = (int)(G_XMLConfig->Length_Linearity * dwYScal);
        int iContRect = ( rcPos.Height() -  2 * iEdgeScreen ) / iLineGAP;
		if( ( rcPos.Height() -  2 * iEdgeScreen ) % iLineGAP > iLineGAP * 0.8 ) ++iContRect;
		int iSplite = ( rcPos.Height() -  2 * iEdgeScreen - iContRect * iLineGAP ) / ( iLineGAP + 1 ); 
		line.lineEdge = iEdgeScreen;
		for ( int index = 0; index < iContRect; ++index )
		{
            LineRect& rcItem = line.arrayRect[ index ];
			rcItem.bValideRect    = true;
			rcItem.rtypeRect.top     =  ( index + 1 ) * iSplite + index * iLineGAP + line.lineRc.top + iEdgeScreen + 1; 
			rcItem.rtypeRect.bottom  =  ( index + 1 ) * ( iSplite + iLineGAP ) + line.lineRc.top + iEdgeScreen + 1;
			rcItem.rtypeRect.left    =  line.lineRc.left;
			rcItem.rtypeRect.right   =  line.lineRc.right; 
		}
		line.arrayRect[ 0 ].rtypeRect.top;
		line.arrayRect[ iContRect - 1 ].rtypeRect.bottom = line.lineRc.bottom - iEdgeScreen;
	}
	else{
		iEdgeScreen = (int)(G_XMLConfig->Edge_Linearity * dwXScal);
		int iLineGAP = (int)(G_XMLConfig->Length_Linearity * dwXScal);
		int iContRect = ( rcPos.Width() - 2 * iEdgeScreen ) / iLineGAP;
		if( ( rcPos.Width() -  2 * iEdgeScreen ) % iLineGAP > iLineGAP * 0.8 ) ++iContRect; //modify
		int iSplite = ( rcPos.Width() - 2 * iEdgeScreen - iContRect * iLineGAP ) / ( iLineGAP + 1 ); 
		line.lineEdge = iEdgeScreen;
		for ( int index = 0; index < iContRect; ++index )
		{
			LineRect& rcItem = line.arrayRect[ index ];
			rcItem.bValideRect   = true;
			rcItem.rtypeRect.left   =  ( index + 1 ) * iSplite + index * iLineGAP + line.lineRc.left + iEdgeScreen + 1; 
			rcItem.rtypeRect.right  =  ( index + 1 ) * ( iSplite + iLineGAP ) + line.lineRc.left + iEdgeScreen + 1;
			rcItem.rtypeRect.top    =  line.lineRc.top;
			rcItem.rtypeRect.bottom =  line.lineRc.bottom; 
		}
		line.arrayRect[ 0 ].rtypeRect.left;
		line.arrayRect[ iContRect - 1 ].rtypeRect.right = line.lineRc.right - iEdgeScreen;
	}

}
void CLinearityTest::ShowNextLine()
{
	bool bFindCurShow = false;
	for ( int index = 0; index < MAX_LINE_IN_LINEARITY; ++index )
	{
		if( !m_ArrayLine[index].bValideLine ) continue;
		if( m_ArrayLine[index].bCurShow ){
			bFindCurShow = true;
			m_ArrayLine[index].bCurShow = false;
			continue;
		}
		if( bFindCurShow ){
			m_ArrayLine[index].bCurShow = true;
			break;
		}
	}

	CGraphItemTest::ResetData();
}
int CLinearityTest::TotalLineToShow()
{
	int iCount = 0;
    for ( int index = 0; index < MAX_LINE_IN_LINEARITY; ++index )
    {
		if( m_ArrayLine[index].bValideLine ) ++iCount;
    }
	return iCount;
}
bool CLinearityTest::PointInRect( const RECT& rc, const POINT& pt )
{
	if( pt.x < rc.left )   return false;
	if( pt.x > rc.right )  return false;
	if( pt.y < rc.top )    return false;
	if( pt.y > rc.bottom ) return false;
	return true;
}