#include "VirtualButtonTest.h"
#include "../TestBase.h"

extern CConfig* G_XMLConfig;

REGIST_RUNTIME_CLASS_PVOID(GRAPH_TYPE, (GRAPH_TYPE)TEST_ITEM_BUTTON_TEST, CVirtualButtonTest)
CVirtualButtonTest::CVirtualButtonTest( LPVOID lp )
:CGraphItemTest( lp )
{

}
CVirtualButtonTest::~CVirtualButtonTest()
{
	//CString tmp =m_strAllMsg;

}
void CVirtualButtonTest::DoInit( int iDeviceIndex/* = 0*/ )
{
	CGraphItemTest::DoInit( iDeviceIndex );
	m_strKeyMsg  = _T("");
	m_strAllMsg  = _T("");
	m_iNgCount  = 0;
	m_iTimeLeft = (int)G_XMLConfig->LimitTime_Key;
	memset( m_ArrayKey, 0, sizeof( m_ArrayKey ) );
	m_bFirstMsg = true;
}
// bool CVirtualButtonTest::IsTestUseValue() const
// {
//     return G_XMLConfig->Use_Key_Value;
// }
void CVirtualButtonTest::ResultBack( UINT32& uCombineRest )
{
	unsigned char chipFamily = GetContainerInterface()->GetChipFamily( G_XMLConfig->IcType );
	int Key_Num = chipFamily==0x06 ? G_XMLConfig->Set_Key_Num + G_XMLConfig->Set_Button_Num : G_XMLConfig->Set_Key_Num;
	uCombineRest = ResultCombine( 0, RESULT_NULL );
	//超过最大NG次数 测试完成 结果NG
    if( G_XMLConfig->Max_NG_Num && m_iNgCount >= G_XMLConfig->Max_NG_Num )  
	{
        uCombineRest = ResultCombine( 1, RESULT_NG );
	}
	//时间超出范围  测试完成 结果NG
	else if( G_XMLConfig->LimitTime_Key && m_iTimeLeft <= 0 )  
	{
		uCombineRest = ResultCombine( 1, RESULT_NG );
	}
	//完成的步骤 等于按键数量 所有按键被按下
    else if( m_iStepFinished ==Key_Num) 
	{
	    uCombineRest = ResultCombine( 1, RESULT_PASS );
	}
}
bool CVirtualButtonTest::StartCaculate( UINT32& uCombineRest )
{
	bool bPointInRect = false;

	int iKeyPressed = 0;
	unsigned char chipFamily = GetContainerInterface()->GetChipFamily( G_XMLConfig->IcType );
	int Key_Num = chipFamily==0x06 ? G_XMLConfig->Set_Key_Num + G_XMLConfig->Set_Button_Num : G_XMLConfig->Set_Key_Num;
    for ( int index = 0; index <Key_Num; ++index )
	{
        RectKey& curKey = m_ArrayKey[index];
        if( curKey.bPressed ) ++iKeyPressed;
	}

	if( iKeyPressed == m_iStepFinished )
	{
        //本次与上次完成的按键数相同 本次操作无效
		bPointInRect = false;
		++m_iNgCount;
	}
	else
	{
		//本次比上次多按了一些按键 本次操作有效
		bPointInRect = true;
		m_iStepFinished = iKeyPressed;			
	}

	ResultBack( uCombineRest );

	return bPointInRect;
}
void CVirtualButtonTest::DoPaint( HDC dc, const RectTP& rc )
{
	//计算每个按键之间的间隙
	 int iKeyHeight = 50, iKeyWidth = 50;
	//if(G_XMLConfig->Set_Key_Num<=20)
	//{
	//   iKeyHeight = 50, iKeyWidth = 50;
	//}
	if (G_XMLConfig->Set_Key_Num>20)
	{
		iKeyHeight = 20, iKeyWidth = 20;
	}
	unsigned char chipFamily = GetContainerInterface()->GetChipFamily( G_XMLConfig->IcType );
	int Key_Num = chipFamily==0x06 ? G_XMLConfig->Set_Key_Num + G_XMLConfig->Set_Button_Num : G_XMLConfig->Set_Key_Num;
	int ikeySpliteNum = Key_Num > 4 ? 4 : Key_Num;
	int iSplite = ( rc.Width() - ikeySpliteNum * iKeyWidth ) / ( ikeySpliteNum + 1 );

    for ( int index = 0; index < Key_Num; ++index )
    {
		int iTopWise = ((index / 4) * iKeyHeight * 7 >> 2) + rc.top; //index < 4 ? 0 : iKeyHeight * 2;
        RectKey& curKey = m_ArrayKey[index];
		curKey.bValidKey = true;
		curKey.rcKey.left = rc.left + iSplite * (index % 4 + 1) + iKeyWidth * (index % 4);
		curKey.rcKey.right = curKey.rcKey.left + iKeyWidth;
        curKey.rcKey.top = ( rc.bottom - rc.top - 6 * (iKeyHeight + 28)) / 2 + iTopWise;
		curKey.rcKey.bottom = curKey.rcKey.top + iKeyHeight;

		curKey.uKey.rcKeyTouch.left   = G_XMLConfig->keyarray[index][0];
		curKey.uKey.rcKeyTouch.top    = G_XMLConfig->keyarray[index][1];
		curKey.uKey.rcKeyTouch.right  = G_XMLConfig->keyarray[index][0];
		curKey.uKey.rcKeyTouch.bottom = G_XMLConfig->keyarray[index][1];
		if( curKey.bPressed ) 
			CUIRenderEx::DrawRectangle( dc, curKey.rcKey, m_paintTool.GetSolidBrushByType( STATE_PASS ) );
		else
			CUIRenderEx::DrawRectangle( dc, curKey.rcKey, m_paintTool.GetSolidBrushByType( (UINT32)RGB( 255, 250, 250 ) ) );
    }
	//打印坐标点
	TypeFont typefont = TypeFont( 12, 8, FW_NORMAL, false, _T("宋体") );
	typeRect rcKeyMsg( rc.left, rc.bottom - 60, rc.right, rc.bottom );
	CUIRenderEx::DrawText( dc, rcKeyMsg, m_paintTool.GetFontByType( typefont ), RGB( 255, 255, 255 ), m_strKeyMsg.c_str() );
}
void CVirtualButtonTest::AddPoint( int index, int xPoint, int yPoint, unsigned char bStrength )
{
// 	CString str = "", strTmp = "";
// 	SYSTEMTIME st = {0};
	unsigned char chipFamily = GetContainerInterface()->GetChipFamily( G_XMLConfig->IcType );
	int Key_Num = chipFamily==0x06 ? G_XMLConfig->Set_Key_Num + G_XMLConfig->Set_Button_Num : G_XMLConfig->Set_Key_Num;
	CGraphItemTest::AddPoint( index, xPoint, yPoint );
	for ( int indexs = 0; indexs < Key_Num; ++indexs )
	{
        RectKey& curKey = m_ArrayKey[indexs];
		if( PointInRect( curKey.uKey.rcKeyTouch, TypePoint( xPoint, yPoint ) ) ){
             curKey.bPressed = true;
			 break;
		}
	}

// 	GetLocalTime(&st);//获得当前本地时间，作测试开始时间
// 	str.Format("%02d.%02d.%02d %02d:%02d:%02d\n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

// 	m_strKeyMsg.Format( _T("Point(%d, %d)"), xPoint, yPoint );
// 
// 	if (m_bFirstMsg)
// 	{		
// 		m_strAllMsg = "First:" + str + m_strKeyMsg + "\n\n";
// 		m_bFirstMsg = false;
// 	}	
// 	m_strKeyMsg = m_strAllMsg + "Final:" + str + m_strKeyMsg;

}
void CVirtualButtonTest::AddValue( int iValue )
{
	unsigned char chipFamily = GetContainerInterface()->GetChipFamily( G_XMLConfig->IcType );
	int Key_Num = chipFamily==0x06 ? G_XMLConfig->Set_Key_Num + G_XMLConfig->Set_Button_Num : G_XMLConfig->Set_Key_Num;
	for ( int index = 0; index < Key_Num; ++index ){
		RectKey& curKey = m_ArrayKey[index];
		if( curKey.bUseKey && curKey.uKey.iKeyValue == iValue ){
             curKey.bPressed = true;
			 break;
		}
	}
}
bool CVirtualButtonTest::PointInRect( const RECT& rc, const POINT& pt )
{
    if( pt.x < rc.left )   return false;
	if( pt.x > rc.right )  return false;
	if( pt.y < rc.top )    return false;
	if( pt.y > rc.bottom ) return false;
	return true;
}