#include "FreePaintRockerTest.h"
#include "../TestBase.h"

extern CConfig* G_XMLConfig;


REGIST_RUNTIME_CLASS_PVOID(GRAPH_TYPE, (GRAPH_TYPE)TEST_ITEM_LINEARLY_ROCKER_TEST, FreePaintRockerTest)
FreePaintRockerTest::FreePaintRockerTest( LPVOID lp )
:CGraphItemTest( lp )
{
}
FreePaintRockerTest::~FreePaintRockerTest()
{

}
void FreePaintRockerTest::DoInit( int iDeviceIndex /*= 0 */)
{
	CGraphItemTest::DoInit( iDeviceIndex );
	m_iTimeLeft = G_XMLConfig->FreePaint_LimiteTime;
}
bool FreePaintRockerTest::StartCaculate( UINT32& uCombineRest )
{
    ResultBack( uCombineRest );
	return true;
}
void FreePaintRockerTest::ResultBack( UINT32& uCombineRest )
{
	//判断是否所有的步骤已经完成
	uCombineRest = ResultCombine( 0, RESULT_NULL );

	//时间超出范围  测试完成 结果PASS
	if( G_XMLConfig->FreePaint_LimiteTime && m_iTimeLeft <= 0 )  
	{
		uCombineRest = ResultCombine( 1, RESULT_PASS );
	}
}

BOOL FreePaintRockerTest::AreYouOK()
{
	return SM_ChipBase(m_deviceNo)->HaveTpLinked( 1 );
}

void FreePaintRockerTest::DoPaint( HDC dc, const typeRect& rc )
{
	CGraphItemTest::DoPaint( dc, rc );	

	DoPaintInit(dc, rc );
}

void FreePaintRockerTest::DoPaintInit(HDC dc, const typeRect& rc)
{
	typeRect rcTp(0, 0, G_XMLConfig->resolution_x, G_XMLConfig->resolution_y);
	CUIRenderEx::DrawEmptyRound( dc, rc, m_paintTool.GetPenByType( TypePen( PS_SOLID, 1, RGB( 255, 255, 255 ) ) ) );

	POINT x1 = {0,G_XMLConfig->resolution_x/2};
	POINT x2 = {G_XMLConfig->resolution_y,G_XMLConfig->resolution_x/2};
	ScreenXYChange( x1.x, x1.y, x1.x, x1.y, rcTp, rc );
	ScreenXYChange( x2.x, x2.y, x2.x, x2.y, rcTp, rc );

	CUIRenderEx::DrawLine(dc,x1,x2,m_paintTool.GetPenByType( TypePen( PS_SOLID, 1, RGB( 255, 255, 255 ) ) ));

	POINT y1 = {G_XMLConfig->resolution_y/2,0};
	POINT y2 = {G_XMLConfig->resolution_y/2,G_XMLConfig->resolution_x};
	ScreenXYChange( y1.x, y1.y, y1.x, y1.y, rcTp, rc );
	ScreenXYChange( y2.x, y2.y, y2.x, y2.y, rcTp, rc );

	CUIRenderEx::DrawLine(dc,y1,y2,m_paintTool.GetPenByType( TypePen( PS_SOLID, 1, RGB( 255, 255, 255 ) ) ));	

	PointTP& pt = m_PointReceive[0].ArrayPoint[m_PointReceive[0].iPointNum-1];

	typeRect rcBody(  rc.right-9*18, rc.top, rc.right,  rc.top+20);
	CUIRenderEx::DrawRectangle( dc, rcBody, m_paintTool.GetSolidBrushByType( (UINT32)RGB( 0, 0, 0 ) ) );
	

	TypeFont typefont = TypeFont( 18, 18, FW_NORMAL, false, _T("宋体") ); 
	TCHAR msg[10] = {0};
	transformat( msg, _T("%4d,%4d"), pt.x,pt.y );

	CUIRenderEx::DrawText( dc, rc, m_paintTool.GetFontByType( typefont ), RGB( 255, 255, 255 ),msg,DT_RIGHT|DT_TOP);
}

BOOL FreePaintRockerTest::LoopAndDone()
{
	unsigned short touchLen = 122;
	unsigned char touchBuffer[84] = {0};
	unsigned char iReCode = ERROR_CODE_OK;
	ctp_report_parse report = ctp_report_parse( GetContainerInterface()->GetSubType( G_XMLConfig->IcType ), touchBuffer );
	//static unsigned char lastMask = 0;

	DoInit( m_deviceNo );

	m_bExitLoop = false;
	iReCode = SM_ChipBase(m_deviceNo)->GetTouchPoint( touchBuffer, &touchLen );
	//scap_rpt_data_t* report = (scap_rpt_data_t*)touchBuffer;
	m_lastMask = (unsigned char)report.msk();

	while( !m_bExitLoop ) 
	{
		if( !Tick() )
		{ 
			SetCurrentStatte( STATE_NG ); 
			break; 
		}
		if( ERROR_CODE_OK !=  iReCode ) 
		{ 
			//trick
			iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_CTP_RST );
			SysDelay( 150 );

			iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( CMD_SWITCH_IIC );
			CHECK_RETURN_IF_FAIL( iReCode );
			SysDelay( 50 );

			iReCode = SM_ChipBase(m_deviceNo)->IncokeCommand( 0x05,0x02,0x5c);
			CHECK_RETURN_IF_FAIL( iReCode );             
			SysDelay( 50 );

			iReCode = SM_ChipBase(m_deviceNo)->SwitchMode( MODE_TOUCH, G_XMLConfig->sync_length );
			if( !SM_ChipBase(m_deviceNo)->HaveTpLinked( 1 ) ) 
			{
				SetCurrentStatte( STATE_NG ); 
				break;
			}
		}
		iReCode = SM_ChipBase(m_deviceNo)->GetTouchPoint( touchBuffer, &touchLen );//按钮
		if( ERROR_CODE_OK != iReCode )
		{ 
			SetCurrentStatte( STATE_NG );
			break; 
		}
		if( !touchLen )  continue;
		//scap_rpt_data_t* report = (scap_rpt_data_t*)touchBuffer;
		if(!report.valid()) continue;
		if( !report.tcnt() && !m_lastMask )  continue;

		//sm_pt_t* sp = report->pts;
		for( int index = 0; index < MAX_NUM_POINT; index++ )
		{
			UINT32 uCombineResult = 0;
			unsigned char ucPosition = 0x01 << index;
			if( 0 == (m_lastMask & ucPosition) && (report.msk() & ucPosition) > 0 )
			{
				//event down
				ResetData();
				SetCurrentStatte( STATE_TESTING );
				unsigned short x = report.X(index);
				unsigned short y = report.Y(index);

				if (1 == G_XMLConfig->is_xy_reverse)
				{
					unsigned short tmp = x;
					x = y;
					y = tmp;
				}

				if (1 == G_XMLConfig->is_x_reverse)
				{
					
					x = G_XMLConfig->resolution_x - x;
		
				}

				if (1 == G_XMLConfig->is_y_reverse)
				{

					y = G_XMLConfig->resolution_y - y;

				}

				AddPoint( report.ID(index), x, y );
			}
			else if( (m_lastMask & ucPosition) > 0 && 0 == (report.msk() & ucPosition) )
			{
				//event up
				bool bTestResult = false;
				//if( STATE_NULL == pItemTest->GetCurrentTestState() ) continue;
				bool bValide = StartCaculate( uCombineResult );
				if( !bValide ) 
				{
					SetCurrentStatte( STATE_NG );	
				}
				else if( RESULT_PASS == ResultState( uCombineResult ) )
				{
					SetCurrentStatte( STATE_PASS );

					return AreYouOK();
				}
				//某些平台一直都没有按下事件 不Reset则会连线
				else SetCurrentStatte(STATE_UPFTOUCH);

				if( RESULT_NG == ResultState( uCombineResult ) )
					return AreYouOK();
				else if( STATE_NULL == GetCurrentTestState() )
					continue;

				break;
			}
			else if( (report.msk() & ucPosition) > 0 )
			{
				//event contact
				unsigned short x = report.X(index);
				unsigned short y = report.Y(index);

				if (1 == G_XMLConfig->is_xy_reverse)
				{
					unsigned short tmp = x;
					x = y;
					y = tmp;
				}

				if (1 == G_XMLConfig->is_x_reverse)
				{

					x = G_XMLConfig->resolution_x - x;

				}

				if (1 == G_XMLConfig->is_y_reverse)
				{

					y = G_XMLConfig->resolution_y - y;

				}

				AddPoint( report.ID(index), x, y );
			}
		}

		m_lastMask = (unsigned char)report.msk();
		GetTestWapperInterface()->GetCallBack().onTouchReport( m_deviceNo );
	}

	return AreYouOK();
}
