#pragma once
#include "GraphItemTest.h"
#include "lock.h"
struct CatchPoint 
{
    PointTP point;
    CatchPoint* nextPoint;
	CatchPoint( const PointTP& pt )
		:nextPoint( NULL )
		,point( pt )
	{

	}
	virtual ~CatchPoint()
	{
	    if( nextPoint ) delete nextPoint;
		nextPoint = NULL;
	}
	void AppendPoint( const PointTP& pt )
	{
        CatchPoint* next = this;
		while ( next->nextPoint )
		{
			next = next->nextPoint;
		}
        next->nextPoint = new CatchPoint( pt );
	}
};
struct CatchPointLine
{
    CatchPoint* PointInLine;
	CatchPointLine* lineNext;
    CatchPointLine()
		:PointInLine( NULL )
		,lineNext( NULL )
	{

	}
	virtual ~CatchPointLine()
	{
        Clear();
	}
	void Clear()
	{
		if( lineNext )    delete lineNext;
		lineNext    = NULL;
		if( PointInLine ) delete PointInLine;
		PointInLine = NULL;
	}
	void AddNewLine( CatchPointLine* newLine )
	{
        CatchPointLine* next = this;
		while ( next->lineNext )
		{
			next = next->lineNext;
		}
		next->lineNext = newLine;
	}
};
class CFreePaintTest : public CGraphItemTest
{
public:
	CFreePaintTest( LPVOID lp );
	virtual ~CFreePaintTest();

public:
	virtual void DoInit( int iDeviceIndex = 0 );
	virtual bool StartCaculate( UINT32& uCombineRest );
	virtual void ResultBack( UINT32& uCombineRest );

	void DoPaint( HDC dc, const typeRect& rc );
	void ResetData();

	BOOL AreYouOK();

private:
	CatchPointLine* m_ArrayCatchLine[MAX_NUM_POINT];

	CInterCriSec m_csLock;
};