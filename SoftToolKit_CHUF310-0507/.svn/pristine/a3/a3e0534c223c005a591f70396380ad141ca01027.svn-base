#include "FreePaintTest.h"
#include "../TestBase.h"
extern CConfig* G_XMLConfig;


REGIST_RUNTIME_CLASS_PVOID(GRAPH_TYPE, (GRAPH_TYPE)TEST_ITEM_FREE_PAINT_TEST, CFreePaintTest)
CFreePaintTest::CFreePaintTest( LPVOID lp )
:CGraphItemTest( lp )
{
    memset( m_ArrayCatchLine, 0, sizeof(m_ArrayCatchLine) );
}
CFreePaintTest::~CFreePaintTest()
{

}
void CFreePaintTest::DoInit( int iDeviceIndex /*= 0 */)
{
	CCriSecLock lock( m_csLock );
	CGraphItemTest::DoInit( iDeviceIndex );
	m_iTimeLeft = G_XMLConfig->FreePaint_LimiteTime;
	for ( int index = 0; index < MAX_NUM_POINT; ++index )
	{
		if( m_ArrayCatchLine[index] )  delete m_ArrayCatchLine[index];
	}
	memset( m_ArrayCatchLine, 0, sizeof(m_ArrayCatchLine) );
}
bool CFreePaintTest::StartCaculate( UINT32& uCombineRest )
{
    ResultBack( uCombineRest );
	return true;
}
void CFreePaintTest::ResultBack( UINT32& uCombineRest )
{
	//判断是否所有的步骤已经完成
	uCombineRest = ResultCombine( 0, RESULT_NULL );

	//时间超出范围  测试完成 结果PASS
	if( G_XMLConfig->FreePaint_LimiteTime && m_iTimeLeft <= 0 )  
	{
		uCombineRest = ResultCombine( 1, RESULT_PASS );
	}
}

BOOL CFreePaintTest::AreYouOK()
{
	return SM_ChipBase(m_deviceNo)->HaveTpLinked( 1 );
}

void CFreePaintTest::DoPaint( HDC dc, const typeRect& rc )
{
	CGraphItemTest::DoPaint( dc, rc );

	//绘制缓存区的点
	TypePoint pcPrev;
	CCriSecLock lock( m_csLock );
	TypePen typepen = TypePen( PS_SOLID, 2, RGB( 255, 0, 0 ) );
	for ( int index = 0; index < MAX_NUM_POINT; ++index )
	{
		if( NULL == m_ArrayCatchLine[index] )  continue;
		CatchPointLine* lineCur = m_ArrayCatchLine[index];
		for ( lineCur; lineCur != NULL; lineCur = lineCur->lineNext )
		{
			CatchPoint* pointCur = lineCur->PointInLine;
			for ( pointCur; pointCur != NULL; pointCur = pointCur->nextPoint )
			{
                TypePoint pc;
				typeRect rcTp(0, 0, G_XMLConfig->resolution_x, G_XMLConfig->resolution_y);
                ScreenXYChange( pointCur->point.x, pointCur->point.y, pc.x, pc.y, rcTp, rc );
				if (pointCur->point.x != 0xFFFF)
				{
					if( pointCur != lineCur->PointInLine )  CUIRenderEx::DrawLine( dc, pcPrev, pc, m_paintTool.GetPenByType( typepen ) );
				}
				pcPrev = pc;
			}
		}
	}
}


void CFreePaintTest::ResetData()
{
	if (G_XMLConfig->isOnce)
	{
		for ( int index = 0; index < MAX_NUM_POINT; ++index )
		{
			m_PointReceive[index].DoInit();
		}
	}else{
		CCriSecLock lock( m_csLock );
        //非Once模式下 每一次Reset时会将上一次有效的数据保存起来
		for ( int index = 0; index < MAX_NUM_POINT; ++index )
		{
             TypePointReceive& lineReceive = m_PointReceive[index];
			 if( lineReceive.iPointNum <= 0 )  continue;

			 CatchPointLine* newCatchLine = new CatchPointLine;
			
			 for ( int iCount = 0; iCount < lineReceive.iPointNum; ++iCount )
			 {
				 PointTP& ptTemp = lineReceive.ArrayPoint[iCount];
				 if( ptTemp.x == 0xFFFF )  continue;
				 if( ptTemp.y == 0xFFFF )  continue;

				 if( newCatchLine->PointInLine )
					 newCatchLine->PointInLine->AppendPoint( ptTemp );
				 else
					 newCatchLine->PointInLine = new CatchPoint( ptTemp );
			 }

			 if( m_ArrayCatchLine[index] )
				 m_ArrayCatchLine[index]->AddNewLine( newCatchLine );
			 else
				 m_ArrayCatchLine[index] = newCatchLine;

			 m_PointReceive[index].DoInit();
		}
	}
}