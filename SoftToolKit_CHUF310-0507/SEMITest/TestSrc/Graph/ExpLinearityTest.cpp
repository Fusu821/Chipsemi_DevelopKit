#include "ExpLinearityTest.h"
#include "../TestBase.h"
extern CConfig* G_XMLConfig;

REGIST_RUNTIME_CLASS_PVOID(GRAPH_TYPE, (GRAPH_TYPE)TEST_ITEM_EXP_LINEARLY_TEST, DLinearityTest)
    DLinearityTest::DLinearityTest( LPVOID lp )
    :CGraphItemTest( lp )
    ,m_bDrawUpDown( false )
    ,m_strMsgTip( _T("") )
{

}
DLinearityTest::~DLinearityTest()
{

}

void DLinearityTest::DoInit( int iDeviceIndex /*= 0*/ )
{
    CGraphItemTest::DoInit( iDeviceIndex );
    memset( m_ArrayLine, 0, sizeof( m_ArrayLine ) );
    m_iStepFinished = 0;
    m_iNgCount = 0;
    m_iTimeLeft = G_XMLConfig->Exp_iLinearityLimitTime;

    bool bHasShowLine = false;
    for ( int index = 0; index < 5; ++index )
    {
        if( G_XMLConfig->Exp_Position_Linearity & ( 1 << index ) ){
            //if( !AreaNeedPaint( iDeviceIndex, index ) )    continue;
            m_ArrayLine[index].bCurShow    = !bHasShowLine;
            m_ArrayLine[index].bValideLine = true;
            m_ArrayLine[index].bHorizontal = true;
            m_ArrayLine[index].bVertical   = false;
            m_ArrayLine[index].bDiagonal_45 = false;
            m_ArrayLine[index].bDiagonal_135 = false;
            if( !bHasShowLine ) bHasShowLine = true;
        }
    }

    if( G_XMLConfig->Exp_Position_Linearity & 0x1F)
    {
        bHasShowLine = true;
    }
    else
    {
        bHasShowLine = false;
    }

    for ( int index = 5; index < 10; ++index )
    {
        if( G_XMLConfig->Exp_Position_Linearity & ( 1 << index ) ){
            //if( !AreaNeedPaint( iDeviceIndex, index ) )    continue;
            m_ArrayLine[index].bCurShow    = !bHasShowLine;
            m_ArrayLine[index].bValideLine = true;
            m_ArrayLine[index].bHorizontal = false;
            m_ArrayLine[index].bVertical   = true;
            m_ArrayLine[index].bDiagonal_45 = false;
            m_ArrayLine[index].bDiagonal_135 = false;
            if( !bHasShowLine ) bHasShowLine = true;
        }
    }

    if( G_XMLConfig->Exp_Position_Linearity & 0x3FF)
    {
        bHasShowLine = true;
    }
    else
    {
        bHasShowLine = false;
    }

    for ( int index = 10; index < 12; ++index )
    {
        if( G_XMLConfig->Exp_Position_Linearity & ( 1 << index ) ){
            //if( !AreaNeedPaint( iDeviceIndex, index ) )    continue;
            m_ArrayLine[index].bCurShow    = !bHasShowLine;
            m_ArrayLine[index].bValideLine = true;
            m_ArrayLine[index].bHorizontal = false;
            m_ArrayLine[index].bVertical   = false;
            m_ArrayLine[index].bDiagonal_45 = (index == 10) ? true : false;
            m_ArrayLine[index].bDiagonal_135 = (index == 11) ? true : false;
            if( !bHasShowLine ) bHasShowLine = true;
        }
    }

    ResetData();
}
void DLinearityTest::ResetData()
{
    CGraphItemTest::ResetData();
    m_bDrawUpDown = false;
    m_strMsgTip = _T("");
    for ( int index = 0; index < MAX_LINE_IN_LINEARITY_EXP; ++index )
    {
        if( !m_ArrayLine[index].bValideLine )  continue;
        if( !m_ArrayLine[index].bCurShow )     continue;
        //m_ArrayLine[index].bLinearity  = false;
        m_ArrayLine[index].bAllPressed = false;
        for ( int iCount = 0; iCount < MAX_RECT_IN_LINE_EXP; ++iCount )
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
bool DLinearityTest::CaculateLinearity( OneLinearity_Exp& line )
{
    bool bLinearity = false;
    if( !line.bValideLine )    return false;
    if( !line.bCurShow )       return false;
    if( !line.bAllPressed )    return false;//画完才计算
    //遍历所有的数据点 取最大 最小 以及差值
    int iMax = 0, iMin = 1000000, iDiff = 0;
    for ( int index = 0; index < m_PointReceive[0].iPointNum; ++index )
    { 
        PointTP& pt = m_PointReceive[0].ArrayPoint[index];
        int value = 0;
        if( line.bVertical )
        {
            value = pt.x;
        }
        else if(line.bHorizontal ){
            value = pt.y;
        }
        else if(line.bDiagonal_45)
        {
            value = pt.y - pt.x;
        }
        else if(line.bDiagonal_135)
        {
            value = pt.y + pt.x;
        }
        iMax = max( iMax, pt.x );
        iMin = min( iMin, pt.x );
    }

    int threshold = G_XMLConfig->Distance_Linearity;
    // 如果需要为对角线单独设置阈值
    // if (line.eLineType == LINE_DIAGONAL_45 || line.eLineType == LINE_DIAGONAL_135)
    // {
    //     // 对角线的阈值可以适当放大（因为是y-x或y+x的差值）
    //     threshold = G_XMLConfig->Distance_Linearity_Diagonal;
    // }

    if( iDiff <= threshold )
        bLinearity = true;

    return bLinearity;
}
bool DLinearityTest::CaculateEdgeRech( OneLinearity_Exp& line )//暂时屏蔽了
{
    if( !line.bValideLine )    return false;
    if( !line.bCurShow )       return false;
    if( !line.bAllPressed )    return false;//画完才计算

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
    else if( line.bHorizontal ){
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
    else if( line.bDiagonal_45 || line.bDiagonal_135 ){
        bRichEdge1 = true;
        bRichEdge2 = true;
    }
    return (bRichEdge1 && bRichEdge2);
}
bool DLinearityTest::CheckBound( OneLinearity_Exp& line )
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
        else if ( line.bHorizontal ){
            if( yScreen < line.lineRc.top || yScreen > line.lineRc.bottom ) return false;
        }
    }
    return true;
}
bool DLinearityTest::StartCaculate( UINT32& uCombineRest )
{
    m_bDrawUpDown = true;
    //计算之前 已经完成的画线
    int iLineFinished = m_iStepFinished;

    //计算测试之后新增的画线
    for ( int index = 0; index < MAX_LINE_IN_LINEARITY_EXP; ++index )
    {
        if( !m_ArrayLine[index].bValideLine ) continue;
        if( m_ArrayLine[index].bAllPressed )  continue;
        if( !m_ArrayLine[index].bCurShow )    continue;
        m_ArrayLine[index].bAllPressed = true;
        for ( int iCount = 0; iCount < MAX_RECT_IN_LINE_EXP; ++iCount )
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
#if 0
        else if( !CaculateEdgeRech( m_ArrayLine[index] ) ){
            m_strMsgTip = _T("Didn't Reach Edge");
        }

        else if( !CheckBound( m_ArrayLine[index] ) ){
            m_strMsgTip = _T("Out Of Bound");
        }
        else if( !CaculateLinearity( m_ArrayLine[index] ) ){
            m_strMsgTip = _T("Linearity Check Failed");
        }
#endif

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
void DLinearityTest::ResultBack( UINT32& uCombineRest )
{
    //判断是否所有的步骤已经完成
    uCombineRest = ResultCombine( 0, RESULT_NULL );

    //超过最大NG次数 测试完成 结果NG
    if( G_XMLConfig->Exp_iLinerityMaxNG && m_iNgCount >= G_XMLConfig->Exp_iLinerityMaxNG )  
    {
        uCombineRest = ResultCombine( 1, RESULT_NG );
    }
    //时间超出范围  测试完成 结果NG
    else if( G_XMLConfig->Exp_iLinearityLimitTime && m_iTimeLeft <= 0 )  
    {
        uCombineRest = ResultCombine( 1, RESULT_NG );
    }
    //完成的步骤 
    else if( m_iStepFinished == TotalLineToShow() ) 
    {
        uCombineRest = ResultCombine( 1, RESULT_PASS );
    }
}
void DLinearityTest::AddPoint( int index, int xPoint, int yPoint, unsigned char bStrength )
{
#if 0  //这段实际也没有启用
    if( G_XMLConfig->Shielded_Pixels_H ){
        if( yPoint < G_XMLConfig->Shielded_Pixels_H ) return;
        if( yPoint > G_XMLConfig->resolution_y - G_XMLConfig->Shielded_Pixels_H ) return;
    }
    if( G_XMLConfig->Shielded_Pixels ){
        if( xPoint < G_XMLConfig->Shielded_Pixels ) return;
        if( xPoint > G_XMLConfig->resolution_x - G_XMLConfig->Shielded_Pixels )   return;
    }
#endif

    CGraphItemTest::AddPoint( index, xPoint, yPoint );
    long xScreen = 0, yScreen  = 0;
    typeRect rcTp(0, 0, G_XMLConfig->resolution_x, G_XMLConfig->resolution_y);
    ScreenXYChange( xPoint, yPoint, xScreen, yScreen, rcTp, m_paintRect );
    for ( int index = 0; index < MAX_LINE_IN_LINEARITY_EXP; ++index )
    {
        if( !m_ArrayLine[index].bValideLine )  continue;
        if( !m_ArrayLine[index].bCurShow )     continue;
        for ( int iCount = 0; iCount < MAX_RECT_IN_LINE_EXP; ++iCount )
        {
            LineRect& rectItem = m_ArrayLine[index].arrayRect[iCount];
            if( !rectItem.bValideRect ) break;
            if( PointInRect( rectItem.rtypeRect, TypePoint( xScreen, yScreen ) ) )
                rectItem.uPressedState = RESULT_PASS;
        }
    }
}
void DLinearityTest::DoPaint( HDC dc, const typeRect& rc )
{
    for ( int index = 0; index < MAX_LINE_IN_LINEARITY_EXP; ++index )
    {
        OneLinearity_Exp& line = m_ArrayLine[index];
        if( !line.bValideLine ) continue;
        if( !line.bCurShow )    continue;
        CalPaintRect( line, rc, index );

        PaintLine( dc, line, index );
        //划完再出现和线性度相关的限定线--初步意向是取消

#if 0 //这个不启用
        if(0 != G_XMLConfig->Exp_Distance_Linearity )
        {
            PaintLimitLine( dc, line );
        }
#endif

    }

    //如果有错误信息 就打印错误信息
    TypeFont typefont = TypeFont( 12, 8, FW_NORMAL, false, _T("宋体") );
    typeRect rcMsg( rc.left, rc.bottom - 100, rc.right, rc.bottom - 50 );
    CUIRenderEx::DrawText( dc, rcMsg, m_paintTool.GetFontByType( typefont ), RGB( 255, 255, 255 ), m_strMsgTip.c_str() );

    CGraphItemTest::DoPaint( dc, rc );//单纯的绘制报点
}
//限定线，划线新出现的界定线
void DLinearityTest::PaintLimitLine( HDC dc, OneLinearity_Exp& line )
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
void DLinearityTest::PaintLine( HDC dc, OneLinearity_Exp& line, int i)
{
    if(line.bVertical){
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
    else if(line.bHorizontal){
        TypePoint ptStart1( line.lineRc.left, line.lineRc.top );
        TypePoint ptEnd1( line.lineRc.right, line.lineRc.top );
        TypePoint ptStart2( line.lineRc.left, line.lineRc.bottom );
        TypePoint ptEnd2( line.lineRc.right, line.lineRc.bottom );

        TypePen typepen = TypePen( PS_SOLID, 1, RGB( 0, 255, 255 ) );
        CUIRenderEx::DrawLine( dc, ptStart1, ptEnd1, m_paintTool.GetPenByType( typepen ) ); // -
        CUIRenderEx::DrawLine( dc, ptStart2, ptEnd2, m_paintTool.GetPenByType( typepen ) );

        //绘制Edge
        typepen = TypePen( PS_DASH, 1, RGB( 0, 255, 255 ) );
        CUIRenderEx::DrawLine( dc, TypePoint( line.lineRc.left + line.lineEdge, line.lineRc.top  ), TypePoint( line.lineRc.left + line.lineEdge, line.lineRc.bottom ), m_paintTool.GetPenByType( typepen ) );// |
        CUIRenderEx::DrawLine( dc, TypePoint( line.lineRc.right - line.lineEdge, line.lineRc.top ), TypePoint( line.lineRc.right - line.lineEdge, line.lineRc.bottom ), m_paintTool.GetPenByType( typepen ) );
    }

    //绘制一系列的gap rect
    for ( int index = 0; index < MAX_RECT_IN_LINE_EXP; ++index )
    {
        LineRect& rect = line.arrayRect[index];
        if( !rect.bValideRect ) continue;
        if( RESULT_NULL == rect.uPressedState ){
            CUIRenderEx::DrawRectangle( dc, rect.rtypeRect, m_paintTool.GetSolidBrushByType( STATE_NULL ) );//银灰色
        }
        else if( RESULT_NG == rect.uPressedState ){
            CUIRenderEx::DrawRectangle( dc, rect.rtypeRect, m_paintTool.GetSolidBrushByType( STATE_NG ) );//红色
        }
        else if( RESULT_PASS == rect.uPressedState ){
            //CUIRenderEx::DrawRectangle( dc, rect.rtypeRect, m_paintTool.GetSolidBrushByType( STATE_PASS ) );
            CUIRenderEx::DrawRectangle( dc, rect.rtypeRect, m_paintTool.GetSolidBrushByType( RGB(0,0,0) ) );//纯黑色
        }
    }
}
void DLinearityTest::CalPaintRect( OneLinearity_Exp& line, const typeRect& rcPos, int index )
{
    double dwXScal = (double)rcPos.Width() / G_XMLConfig->resolution_x;
    double dwYScal = (double)rcPos.Height() / G_XMLConfig->resolution_y;

    if(line.bHorizontal ){
        line.lineRc.left   = rcPos.left;
        line.lineRc.right  = rcPos.right;
        if( 0 == index ){
            line.lineRc.top    = (int)(G_XMLConfig->Exp_Upper_Limit_H1 * dwYScal) + rcPos.top;
            line.lineRc.bottom = (int)(G_XMLConfig->Exp_Lower_Limit_H1 * dwYScal) + rcPos.top; 
        }
        else if( 1 == index ){
            line.lineRc.top    = (int)(G_XMLConfig->Exp_Upper_Limit_H2 * dwYScal) + rcPos.top;
            line.lineRc.bottom = (int)(G_XMLConfig->Exp_Lower_Limit_H2 * dwYScal) + rcPos.top; 
        }
        else if( 2 == index ){
            line.lineRc.top    = (int)(G_XMLConfig->Exp_Upper_Limit_H3 * dwYScal) + rcPos.top;
            line.lineRc.bottom = (int)(G_XMLConfig->Exp_Lower_Limit_H3 * dwYScal) + rcPos.top; 
        }
        else if( 3 == index ){
            line.lineRc.top    = (int)(G_XMLConfig->Exp_Upper_Limit_H4 * dwYScal) + rcPos.top;
            line.lineRc.bottom = (int)(G_XMLConfig->Exp_Lower_Limit_H4 * dwYScal) + rcPos.top; 
        }
        else if( 4 == index ){
            line.lineRc.top    = (int)(G_XMLConfig->Exp_Upper_Limit_H5 * dwYScal) + rcPos.top;
            line.lineRc.bottom = (int)(G_XMLConfig->Exp_Lower_Limit_H5 * dwYScal) + rcPos.top; 
        }
    }
    else if(line.bVertical) {
        line.lineRc.top   = rcPos.top;
        line.lineRc.bottom  = rcPos.bottom;
        if( 5 == index ){
            line.lineRc.left    = (int)(G_XMLConfig->Exp_Upper_Limit_V1 * dwXScal) + rcPos.left;
            line.lineRc.right   = (int)(G_XMLConfig->Exp_Lower_Limit_V1 * dwXScal) + rcPos.left; 
        }
        else if( 6 == index ){
            line.lineRc.left    = (int)(G_XMLConfig->Exp_Upper_Limit_V2 * dwXScal) + rcPos.left;
            line.lineRc.right   = (int)(G_XMLConfig->Exp_Lower_Limit_V2 * dwXScal) + rcPos.left; 
        }
        else if( 7 == index ){
            line.lineRc.left    = (int)(G_XMLConfig->Exp_Upper_Limit_V3 * dwXScal) + rcPos.left;
            line.lineRc.right   = (int)(G_XMLConfig->Exp_Lower_Limit_V3 * dwXScal) + rcPos.left; 
        }
        else if( 8 == index ){
            line.lineRc.left    = (int)(G_XMLConfig->Exp_Upper_Limit_V4 * dwXScal) + rcPos.left;
            line.lineRc.right   = (int)(G_XMLConfig->Exp_Lower_Limit_V4 * dwXScal) + rcPos.left; 
        }
        else if( 9 == index ){
            line.lineRc.left    = (int)(G_XMLConfig->Exp_Upper_Limit_V5 * dwXScal) + rcPos.left;
            line.lineRc.right   = (int)(G_XMLConfig->Exp_Lower_Limit_V5 * dwXScal) + rcPos.left; 
        }
    }

    if(index < 10) {
        CalPaintRect( line, rcPos);
    }
    else
    {
        CalPaintRect_Diagonal( line, rcPos);
    }
}
void DLinearityTest::CalPaintRect( OneLinearity_Exp& line,  const typeRect& rcPos)
{
    double dwXScal = (double)rcPos.Width() / G_XMLConfig->resolution_x;
    double dwYScal = (double)rcPos.Height() / G_XMLConfig->resolution_y;
    int iEdgeScreen = 0; 

    if( line.bVertical ){
        iEdgeScreen = (int)(G_XMLConfig->Exp_Edge_Linearity * dwYScal);
        int iLineGAP = (int)(G_XMLConfig->Exp_Length_Linearity * dwYScal);
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
            rcItem.rtypeRect.left    =  (int)(line.lineRc.left + 3 * dwXScal);
            rcItem.rtypeRect.right   =  line.lineRc.right; 
        }
        line.arrayRect[ 0 ].rtypeRect.top;
        line.arrayRect[ iContRect - 1 ].rtypeRect.bottom = line.lineRc.bottom - iEdgeScreen;
    }
    else {
        iEdgeScreen = (int)(G_XMLConfig->Exp_Edge_Linearity * dwXScal);
        int iLineGAP = (int)(G_XMLConfig->Exp_Length_Linearity * dwXScal);
        int iContRect = ( rcPos.Width() - 2 * iEdgeScreen ) / iLineGAP;//小矩形块的个数
        if( ( rcPos.Width() -  2 * iEdgeScreen ) % iLineGAP > iLineGAP * 0.8 ) ++iContRect;//原来的代码有bug
        int iSplite = ( rcPos.Width() - 2 * iEdgeScreen - iContRect * iLineGAP ) / ( iLineGAP + 1 );//方块的间隙
        line.lineEdge = iEdgeScreen;
        for ( int index = 0; index < iContRect; ++index )
        {
            LineRect& rcItem = line.arrayRect[ index ];
            rcItem.bValideRect   = true;
            rcItem.rtypeRect.left   =  ( index + 1 ) * iSplite + index * iLineGAP + line.lineRc.left + iEdgeScreen + 1; 
            rcItem.rtypeRect.right  =  ( index + 1 ) * ( iSplite + iLineGAP ) + line.lineRc.left + iEdgeScreen + 1;
            rcItem.rtypeRect.top    =  (int)(line.lineRc.top + 3 * dwYScal);
            rcItem.rtypeRect.bottom =  line.lineRc.bottom; 
        }
        line.arrayRect[ 0 ].rtypeRect.left;
        line.arrayRect[ iContRect - 1 ].rtypeRect.right = line.lineRc.right - iEdgeScreen;
    }

}
 
void DLinearityTest::CalPaintRect_Diagonal( OneLinearity_Exp& line,  const typeRect& rcPos)
{
    double dwXScal = (double)rcPos.Width() / G_XMLConfig->resolution_x;
    double dwYScal = (double)rcPos.Height() / G_XMLConfig->resolution_y;

    int baseRectLength =  G_XMLConfig->Exp_DiagLength_Linearity;
    int baseRectWidth = G_XMLConfig->Exp_DiagWidth_Linearity;
    int rectLength = (int)(baseRectLength * dwXScal);
    int rectWidth = (int)(baseRectWidth * dwYScal);

    const float diagonalSlope = (float)G_XMLConfig->resolution_y / G_XMLConfig->resolution_x; 
    int rectCount = 0; 

    if(line.bDiagonal_45)
    {
        int maxResX = (int)(rcPos.Width() / dwXScal); 
        for (int resX = 0; resX < maxResX && rectCount < MAX_RECT_IN_LINE_EXP; resX += (int)(baseRectLength))
        {
            LineRect& rcItem = line.arrayRect[ rectCount ];
            rcItem.bValideRect   = true;

            int resX1 = resX;
            int resY1 = (int)(resX1 * diagonalSlope);
            int resX2 = resX1 + baseRectLength;
            int resY2 = (int)(resX2 * diagonalSlope);

            int canvasX1 = rcPos.left + (int)(resX1 * dwXScal);
            int canvasY1 = rcPos.top + (int)(resY1 * dwYScal);
            int canvasX2 = rcPos.left + (int)(resX2 * dwXScal);
            int canvasY2 = rcPos.top + (int)(resY2 * dwYScal);

            canvasX1 -= rectWidth / 2;
            //canvasY1 -= rectWidth / 2;
            canvasX2 += rectWidth / 2;
            //canvasY2 += rectWidth / 2;

            rcItem.rtypeRect.left = max(rcPos.left, canvasX1);
            rcItem.rtypeRect.top = max(rcPos.top, canvasY1);
            rcItem.rtypeRect.right = min(rcPos.right, canvasX2);
            rcItem.rtypeRect.bottom = min(rcPos.bottom, canvasY2);
            rectCount++;
        }
    }
    else
    {
        int maxResX = (int)(rcPos.Width() / dwXScal);
        for (int resX = 0; resX < maxResX && rectCount < MAX_RECT_IN_LINE_EXP; resX += (int)(baseRectLength))
        {
            LineRect& rcItem = line.arrayRect[ rectCount ];
            rcItem.bValideRect = true;

            int resX1 = resX;
            int resY1 = G_XMLConfig->resolution_y - (int)(resX1 * diagonalSlope);
            int resX2 = resX1 + baseRectLength;
            int resY2 = G_XMLConfig->resolution_y - (int)(resX2 * diagonalSlope);

            int canvasX1 = rcPos.left + (int)(resX1 * dwXScal);
            int canvasY1 = rcPos.top + (int)(resY1 * dwYScal);
            int canvasX2 = rcPos.left + (int)(resX2 * dwXScal);
            int canvasY2 = rcPos.top + (int)(resY2 * dwYScal);

            canvasX1 -= rectWidth / 2;
            //canvasY1 -= rectWidth / 2;
            canvasX2 += rectWidth / 2;

            rcItem.rtypeRect.left = max(rcPos.left, canvasX1);
            rcItem.rtypeRect.top = max(rcPos.top, canvasY2);
            rcItem.rtypeRect.right = min(rcPos.right, canvasX2);
            rcItem.rtypeRect.bottom = min(rcPos.bottom, canvasY1);
            rectCount++;
        }
    }
}

void DLinearityTest::ShowNextLine()
{
    bool bFindCurShow = false;
    for ( int index = 0; index < MAX_LINE_IN_LINEARITY_EXP; ++index )
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
int DLinearityTest::TotalLineToShow()
{
    int iCount = 0;
    for ( int index = 0; index < MAX_LINE_IN_LINEARITY_EXP; ++index )
    {
        if( m_ArrayLine[index].bValideLine ) ++iCount;
    }
    return iCount;
}
bool DLinearityTest::PointInRect( const RECT& rc, const POINT& pt )
{
    if( pt.x < rc.left )   return false;
    if( pt.x > rc.right )  return false;
    if( pt.y < rc.top )    return false;
    if( pt.y > rc.bottom ) return false;
    return true;
}
