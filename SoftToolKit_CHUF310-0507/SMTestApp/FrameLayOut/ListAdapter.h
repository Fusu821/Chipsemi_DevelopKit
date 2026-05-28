#pragma once
#include <helper/SAdapterBase.h>
#include "../Include/SEMITouch.h"
#include "../Include/NativeTestInterface.h"
// struct TestResult 
// {
// 	TCHAR szName[100];
// 	TCHAR szResult[100];
// 	TCHAR szMark[100];
// };

#define WM_UPDATE_CONTENT     WM_USER + 1000
#define WM_ON_TEST_START      WM_USER + 1001
#define WM_ON_TEST_OVER       WM_USER + 1002
#define WM_ON_LIST_CHANGE     WM_USER + 1003
#define WM_ON_PROCESS_UPDATE  WM_USER + 1004
#define WM_ON_TOUCH_DATA      WM_USER + 1005

class CListAdapter : public SMcAdapterBase
{
public:
	CListAdapter( )
		:m_ItemCount( 0 )
	{
	}

	virtual ~CListAdapter()
	{

	}

	virtual int getCount()
	{
		return m_ItemCount;
	}

	void UpDateListItem( const NativeTestItem* item )
	{
		for( int index = 0; index < m_ItemCount; index++ )
		{
			NativeTestItem& itemRef = m_arrayTestResult[index];
			if( itemRef.testCode != item->testCode ) continue;

			itemRef = *item;
			break;
		}

		notifyDataSetInvalidated();
		//::SendMessage( m_nofitywnd, WM_UPDATE_CONTENT, 1, 0 );
	}

	void UpDateListItems( int itemCount, const NativeTestItem (&items)[MAX_TEST_ITEMS] )
	{
		m_ItemCount = itemCount;
		memcpy( m_arrayTestResult, items, sizeof(m_arrayTestResult) );
	}

	SStringW GetColumnName(int iCol) const
	{
		return SStringW().Format(L"col%d", iCol + 1);
	}

// 	SStringT getSizeText(DWORD dwSize)
// 	{
// 		int num1 = dwSize / (1 << 20);
// 		dwSize -= num1 * (1 << 20);
// 		int num2 = dwSize * 100 / (1 << 20);
// 		return SStringT().Format(_T("%d.%02dM"), num1, num2);
// 	}

	void Reset()
	{
		for( int index = 0; index < m_ItemCount; index++ )
		{
			NativeTestItem&  item = m_arrayTestResult[index];
			memset( item.testMark, 0, sizeof(item.testMark) );
			item.testResult = ITEM_STA_NONE;
		}

		::SendMessage( m_nofitywnd, WM_UPDATE_CONTENT, 1, 0 );
	}

	virtual void getView(int position, SWindow * pItem, pugi::xml_node xmlTemplate)
	{
		if (pItem->GetChildrenCount() == 0)
		{
			pItem->InitFromXml(xmlTemplate);
		}

		NativeTestItem& itemRef = m_arrayTestResult[position];

		pItem->FindChildByName(_T("name"))->SetWindowText(itemRef.testName);
		//pItem->FindChildByName(_T("result"))->SetWindowText(m_arrayTestResult[position].szResult);
		pItem->FindChildByName(_T("mark"))->SetWindowText(itemRef.testMark);

		if( itemRef.testResult == ITEM_STA_NONE ){
			pItem->FindChildByName(_T("result"))->SetWindowText( _T("") );
			pItem->FindChildByName(_T("result"))->SetAttribute( L"colorBkgnd", L"#F3F3F3" );
		}else if( itemRef.testResult == ITEM_STA_PASS ){
			pItem->FindChildByName(_T("result"))->SetWindowText( _T("PASS") );
			pItem->FindChildByName(_T("result"))->SetAttribute( L"colorBkgnd", L"#00FF00" );
		}else if( itemRef.testResult == ITEM_STA_FAIL ){
			pItem->FindChildByName(_T("result"))->SetWindowText( _T("FAIL") );
			pItem->FindChildByName(_T("result"))->SetAttribute( L"colorBkgnd", L"#FF0000" );
		}else if( itemRef.testResult == ITEM_STA_TBD ){
			pItem->FindChildByName(_T("result"))->SetWindowText( _T("TBD") );
			pItem->FindChildByName(_T("result"))->SetAttribute( L"colorBkgnd", L"#FFFF00" );
		}else if( itemRef.testResult == ITEM_STA_START ){
			pItem->FindChildByName(_T("result"))->SetWindowText( _T("TESTING") );
			pItem->FindChildByName(_T("result"))->SetAttribute( L"colorBkgnd", L"#FFFF00" );
		}else if( itemRef.testResult == ITEM_STA_WAIT ){
			pItem->FindChildByName(_T("result"))->SetWindowText( _T("WAITING") );
			pItem->FindChildByName(_T("result"))->SetAttribute( L"colorBkgnd", L"#0000FF" );
		}else if( itemRef.testResult == ITEM_STA_EXCEPTION ){
			pItem->FindChildByName(_T("result"))->SetWindowText( _T("EXCEPTION") );
			pItem->FindChildByName(_T("result"))->SetAttribute( L"colorBkgnd", L"#F01000" );
		}
	}

private:
	int m_ItemCount;
	HWND m_nofitywnd;
	NativeTestItem m_arrayTestResult[MAX_TEST_ITEMS];
};
			 