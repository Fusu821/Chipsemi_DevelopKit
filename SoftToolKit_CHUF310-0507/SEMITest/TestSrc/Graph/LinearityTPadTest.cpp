#include "LinearityTPadTest.h"
#include "../TestBase.h"
extern CConfig* G_XMLConfig;

#define  SIZEPRO 0.1
#define  KEYHEIGHT (LONG)((rc.right-rc.left) * SIZEPRO)
#define  KEYHTOUCHEIGHT (LONG)(G_XMLConfig->resolution_x  * SIZEPRO)

REGIST_RUNTIME_CLASS_PVOID(GRAPH_TYPE, (GRAPH_TYPE)TEST_ITEM_LINEARLY_TPAD_TEST, CLinearityTPadTest)
CLinearityTPadTest::CLinearityTPadTest( LPVOID lp )
:CGraphItemTest( lp )
,m_bDrawUpDown( false )
,m_strMsgTip( _T("") )
,step(1)
{

}
CLinearityTPadTest::~CLinearityTPadTest()
{

}
void CLinearityTPadTest::DoInit( int iDeviceIndex /*= 0*/ )
{
	CGraphItemTest::DoInit( iDeviceIndex );
	memset( m_ArrayKey, 0, sizeof( m_ArrayKey ) );
	m_iStepFinished = 0;
	m_iNgCount = 0;
	m_iTimeLeft = G_XMLConfig->iLinearityLimitTime;


}

bool CLinearityTPadTest::StartCaculate( UINT32& uCombineRest )
{
	bool bPointInRect = true;
	if(step <= 8)
	{
		bPointInRect = false;
		++m_iNgCount;
		
	}
	else
	{
		for (int index = 0; index<8; index++)
		{
			RectKey& curKey = m_ArrayKey[index];

			if ( curKey.state !=1)
			{
				bPointInRect = false;

				break;
			}
		}
		if(bPointInRect == false)
		{

			++m_iNgCount;
		
		}

	}


	ResultBack( uCombineRest );

	KeyInit();

	return bPointInRect;
}
void CLinearityTPadTest::ResultBack( UINT32& uCombineRest )
{
	uCombineRest = ResultCombine( 0, RESULT_NULL );

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
	else if( step>8) 
	{
		uCombineRest = ResultCombine( 1, RESULT_PASS );
	}



}
void CLinearityTPadTest::AddPoint( int index, int xPoint, int yPoint, unsigned char bStrength )
{
	for ( int indexs = 0; indexs < 4; indexs++ )
	{
		int i = 0;
		if(step>5)
		{
			i=4;	
		}
		else if(step>4)
		{
			i=3;	
		}
		else
		{
			i=0;	
		}
		i = i + indexs;
		RectKey& curKey = m_ArrayKey[i];
		if( PointInRect( curKey.uKey.rcKeyTouch, TypePoint( xPoint, yPoint ) ) )
		{
			curKey.bPressed = true;
			break;
		}
		else
		{
			curKey.bPressed = false;
		}
	}
	CGraphItemTest::AddPoint( index, xPoint, yPoint );
	
}
void CLinearityTPadTest::DoPaint( HDC dc, const typeRect& rc )
{
	CGraphItemTest::DoPaint( dc, rc );
	DrawSquares( dc, rc );
	Rule();
}
//限定线，划线新出现的界定线
bool CLinearityTPadTest::PointInRect( const RECT& rc, const POINT& pt )
{
	if( pt.x < rc.left )   return false;
	if( pt.x > rc.right )  return false;
	if( pt.y < rc.top )    return false;
	if( pt.y > rc.bottom ) return false;
	return true;
}

void CLinearityTPadTest::DrawSquares(HDC dc, const typeRect& rc)
{

	RectKey& curKey = m_ArrayKey[0];
	curKey.bValidKey = true;
	curKey.rcKey.left = rc.left;
	curKey.rcKey.right = curKey.rcKey.left + KEYHEIGHT;
	curKey.rcKey.top = rc.top;
	curKey.rcKey.bottom = curKey.rcKey.top + KEYHEIGHT;

	curKey.uKey.rcKeyTouch.left   = 0;
	curKey.uKey.rcKeyTouch.right  = curKey.uKey.rcKeyTouch.left + KEYHTOUCHEIGHT;
	curKey.uKey.rcKeyTouch.top    = 0;
	curKey.uKey.rcKeyTouch.bottom = curKey.uKey.rcKeyTouch.top + KEYHTOUCHEIGHT;

	curKey.num =  2;


	RectKey& curKey1 = m_ArrayKey[1];
	curKey1.bValidKey = true;
	curKey1.rcKey.left = rc.left;
	curKey1.rcKey.right = curKey1.rcKey.left + KEYHEIGHT;
	curKey1.rcKey.top = rc.bottom - KEYHEIGHT;
	curKey1.rcKey.bottom = rc.bottom;
	

	curKey1.uKey.rcKeyTouch.left   = 0;
	curKey1.uKey.rcKeyTouch.right  = curKey1.uKey.rcKeyTouch.left + KEYHTOUCHEIGHT;
	curKey1.uKey.rcKeyTouch.top    = G_XMLConfig->resolution_y - KEYHTOUCHEIGHT;
	curKey1.uKey.rcKeyTouch.bottom = curKey1.uKey.rcKeyTouch.top + KEYHTOUCHEIGHT;

	curKey1.num =  1;

	RectKey& curKey2 = m_ArrayKey[2];
	curKey2.bValidKey = true;
	curKey2.rcKey.left = rc.right-KEYHEIGHT;
	curKey2.rcKey.right =  rc.right;
	curKey2.rcKey.top = rc.top;
	curKey2.rcKey.bottom = curKey.rcKey.top + KEYHEIGHT;

	curKey2.uKey.rcKeyTouch.left   = G_XMLConfig->resolution_x - KEYHTOUCHEIGHT;
	curKey2.uKey.rcKeyTouch.right  = curKey2.uKey.rcKeyTouch.left + KEYHTOUCHEIGHT;
	curKey2.uKey.rcKeyTouch.top    = 0;
	curKey2.uKey.rcKeyTouch.bottom = curKey2.uKey.rcKeyTouch.top + KEYHTOUCHEIGHT;

	curKey2.num =  3;
		 
	RectKey& curKey3 = m_ArrayKey[3];
	curKey3.bValidKey = true;
	curKey3.rcKey.left = rc.right-KEYHEIGHT;
	curKey3.rcKey.right =  rc.right;
	curKey3.rcKey.top = rc.bottom - KEYHEIGHT;
	curKey3.rcKey.bottom = rc.bottom;

	curKey3.uKey.rcKeyTouch.left   = G_XMLConfig->resolution_x - KEYHTOUCHEIGHT;
	curKey3.uKey.rcKeyTouch.right  = curKey3.uKey.rcKeyTouch.left + KEYHTOUCHEIGHT;
	curKey3.uKey.rcKeyTouch.top    = G_XMLConfig->resolution_y - KEYHTOUCHEIGHT;
	curKey3.uKey.rcKeyTouch.bottom = curKey3.uKey.rcKeyTouch.top + KEYHTOUCHEIGHT;

	curKey3.num =  4;

	RectKey& curKey4 = m_ArrayKey[4];
	curKey4.bValidKey = true;
	curKey4.rcKey.left = rc.left;
	curKey4.rcKey.right = curKey4.rcKey.left + KEYHEIGHT;
	curKey4.rcKey.top = rc.top;
	curKey4.rcKey.bottom = curKey4.rcKey.top + KEYHEIGHT;

	curKey4.uKey.rcKeyTouch.left   = 0;
	curKey4.uKey.rcKeyTouch.right  = curKey4.uKey.rcKeyTouch.left + KEYHTOUCHEIGHT;
	curKey4.uKey.rcKeyTouch.top    = 0;
	curKey4.uKey.rcKeyTouch.bottom = curKey4.uKey.rcKeyTouch.top + KEYHTOUCHEIGHT;

	curKey4.num =  7;


	RectKey& curKey5 = m_ArrayKey[5];
	curKey5.bValidKey = true;
	curKey5.rcKey.left = rc.left;
	curKey5.rcKey.right = curKey5.rcKey.left + KEYHEIGHT;
	curKey5.rcKey.top = rc.bottom - KEYHEIGHT;
	curKey5.rcKey.bottom = rc.bottom;

	curKey5.uKey.rcKeyTouch.left   = 0;
	curKey5.uKey.rcKeyTouch.right  = curKey5.uKey.rcKeyTouch.left + KEYHTOUCHEIGHT;
	curKey5.uKey.rcKeyTouch.top    = G_XMLConfig->resolution_y - KEYHTOUCHEIGHT;
	curKey5.uKey.rcKeyTouch.bottom = curKey5.uKey.rcKeyTouch.top + KEYHTOUCHEIGHT;
	
	curKey5.num =  5 ;

	RectKey& curKey6 = m_ArrayKey[6];
	curKey6.bValidKey = true;
	curKey6.rcKey.left = rc.right-KEYHEIGHT;
	curKey6.rcKey.right =  rc.right;
	curKey6.rcKey.top = rc.top;
	curKey6.rcKey.bottom = curKey.rcKey.top + KEYHEIGHT;

	curKey6.uKey.rcKeyTouch.left   = G_XMLConfig->resolution_x - KEYHTOUCHEIGHT;
	curKey6.uKey.rcKeyTouch.right  = curKey6.uKey.rcKeyTouch.left + KEYHTOUCHEIGHT;
	curKey6.uKey.rcKeyTouch.top    = 0;
	curKey6.uKey.rcKeyTouch.bottom = curKey6.uKey.rcKeyTouch.top + KEYHTOUCHEIGHT;

	curKey6.num =  6;

	RectKey& curKey7 = m_ArrayKey[7];
	curKey7.bValidKey = true;
	curKey7.rcKey.left = rc.right-KEYHEIGHT;
	curKey7.rcKey.right =  rc.right;
	curKey7.rcKey.top = rc.bottom - KEYHEIGHT;
	curKey7.rcKey.bottom = rc.bottom;

	curKey7.uKey.rcKeyTouch.left   = G_XMLConfig->resolution_x - KEYHTOUCHEIGHT;
	curKey7.uKey.rcKeyTouch.right  = curKey7.uKey.rcKeyTouch.left + KEYHTOUCHEIGHT;
	curKey7.uKey.rcKeyTouch.top    = G_XMLConfig->resolution_y - KEYHTOUCHEIGHT;
	curKey7.uKey.rcKeyTouch.bottom = curKey7.uKey.rcKeyTouch.top + KEYHTOUCHEIGHT;

	curKey7.num =  8;
	
	for (int index = 0; index<4; index++)
	{
		int i = 0;
		if(step>5)
		{
			i=4;	
		}
		else if(step>4)
		{
			i=3;	
		}
		else
		{
			i=0;	
		}
		i = i + index;
		RectKey& curKey = m_ArrayKey[i];
		if( curKey.state == 1 ) 
		{
			CUIRenderEx::DrawRectangle( dc, curKey.rcKey, m_paintTool.GetSolidBrushByType( STATE_PASS ) );
		}			
		else
		{
			CUIRenderEx::DrawRectangle( dc, curKey.rcKey, m_paintTool.GetSolidBrushByType( STATE_READY) );
		}
		int size = curKey.rcKey.right-curKey.rcKey.left;
		TypeFont typefont = TypeFont( size, size, FW_NORMAL, false, _T("宋体") ); 
		TCHAR msg[10] = {0};
		transformat( msg, _T("%d"),curKey.num );
		CUIRenderEx::DrawText( dc, curKey.rcKey, m_paintTool.GetFontByType( typefont ), RGB( 255, 0, 255 ),msg);
			
	}

}

void CLinearityTPadTest::Rule()
{
	for (int index = 0; index<8; index++)
	{
		RectKey& curKey = m_ArrayKey[index];
		if(curKey.num == step)
		{
			if(curKey.bPressed && curKey.num==step)
			{
				curKey.state = 1;
				step++;
				break;
			}
		}
	}



}

void CLinearityTPadTest::KeyInit()
{
	step = 1;
	for (int index = 0; index<8; index++)
	{
		RectKey& curKey = m_ArrayKey[index];
		curKey.state = 0;
	}

}
