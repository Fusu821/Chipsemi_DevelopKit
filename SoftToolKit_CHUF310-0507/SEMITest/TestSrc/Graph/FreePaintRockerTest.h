#pragma once
#include "GraphItemTest.h"
#include "lock.h"

class FreePaintRockerTest : public CGraphItemTest
{
public:
	FreePaintRockerTest( LPVOID lp );
	virtual ~FreePaintRockerTest();

public:
	virtual void DoInit( int iDeviceIndex = 0 );
	virtual bool StartCaculate( UINT32& uCombineRest );
	virtual void ResultBack( UINT32& uCombineRest );

	void DoPaint( HDC dc, const typeRect& rc );
	void DoPaintInit( HDC dc, const typeRect& rc );

	BOOL AreYouOK();

	virtual BOOL LoopAndDone(  ) override;

private:

};