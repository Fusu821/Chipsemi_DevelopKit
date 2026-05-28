#pragma once
#include "onlinelog.h"

namespace SOUI{

	template<class T>
	static tstring value_buffer_to_string( T* buffer, int len )
	{
		tstring sz;
		TCHAR temp[10] = {0};
		for( int index = 0; index < len; index++ )
		{
			transformat( temp, _T("%02x "), buffer[index] );
			sz += temp;
		}

		return sz;
	}

	class CTestPacket : public SWindow
	{
		SOUI_CLASS_NAME(CTestPacket,L"PacketWindow")
	public:
		CTestPacket(  )
		{
			m_devNo = 0;
			m_singleListAdp = NULL;
		}
		virtual ~CTestPacket()
		{
			if( m_singleListAdp ) delete m_singleListAdp;
		}

		void UpdateDeviceStatus( int dev, BOOL connected )
		{
			m_devNo = dev;

			if( m_singleListAdp )
			{
				NativeTestItem item;
				item.testCode = 0;
				item.testResult = connected  ? ITEM_STA_PASS : ITEM_STA_FAIL;
				copytextto( item.testName, _T("MTK"), lengthof( _T("MTK") ) );
				transformat( item.testMark, connected ? _T("MTK = %d") : _T(""), m_devNo + 1 );

				m_singleListAdp->UpDateListItem( &item );
			}

			InitTestContext( dev );
		}

		bool OnSnCodeUpdate( char chInput, unsigned char snMaxLen )
		{
			SEdit* pEditSn = (SEdit*)FindChildByName(_T("snCode"));
			if( pEditSn )
			{
				tstring sn = pEditSn->GetWindowText(0);
				if(sn.length() < snMaxLen)
				{
					sn.push_back(chInput);
					pEditSn->SetWindowText( sn.c_str() );
					sn = pEditSn->GetWindowText(0);
					if( sn.length() >= snMaxLen )
					{
						GetTestWapperInterface()->StartTest( m_devNo, sn.c_str() );
						pEditSn->EnableWindow(FALSE);
					}
				}
			}

			return true;
		}

		bool OnBtnStart( EventArgs* e )
		{
			GetTestWapperInterface()->StartTest( m_devNo );

			return true;
		}

		void SetAttributeOnSn()
		{
			FindChildByName(_T("resultlist"))->SetAttribute( L"pos", L"2,2,|0,-25" );
			FindChildByName(_T("imageGraph"))->SetAttribute( L"pos", L"2,2,|0,-25" );
			FindChildByName(_T("txtSn"))->SetAttribute( L"pos", L"2,-24,-40,-1" );
			FindChildByName(_T("snCode"))->SetAttribute( L"pos", L"31,-24,|0,-1" );
		}

		void OnSize(UINT32 nType, CSize size)
		{
			SMCListView* slist = (SMCListView*)FindChildByName( _T("resultlist") );
			if( slist )
			{
				SHeaderCtrl* sh =  (SHeaderCtrl*)slist->GetChild(0);
				//sh->SetAttribute( L"width", L"120" );
				slist->UpdateLayout(  );
			}

			
		}

		void InitTestContext( int devID )
		{
			m_devNo = devID;

			//if( NULL == m_fatherWin ) return;
			CImageGraph* pGraph = (CImageGraph*)FindChildByName( _T("imageGraph") );
			pGraph->SetDeviceNo( m_devNo );

			SButton* pButton = (SButton*)FindChildByName( _T("btnstart") );
			pButton->GetEventSet()->subscribeEvent( EVT_CMD, Subscriber( &CTestPacket::OnBtnStart, this ) );
		}

		void InitListCtrl()
		{
			//SMCListView* plistCtrl = FindChildByName2<SMCListView>( L"resultlist" );
			SMCListView* plistCtrl = (SMCListView*)FindChildByName( _T("resultlist") );
			if( plistCtrl )
			{
				m_singleListAdp = new CListAdapter( );
				plistCtrl->SetAdapter( m_singleListAdp );
			}

			int itemCnt = 0;
			NativeTestItem items[MAX_TEST_ITEMS];
			for( int index = 0; index < MAX_TEST_ITEMS; index++ )
			{
				NativeTestItem& item = GetTestWapperInterface()->GetNativeTestItemByIndex( 0, index );
				if( item.testCode < 0 )  continue;

				items[itemCnt++] = item;
			}

			if( m_singleListAdp )
			{
				m_singleListAdp->UpDateListItems( itemCnt, items );
			}
		}

		int GetCurrentDevice()
		{
			return m_devNo;
		}

		void SetCurrentStep( BOOL bGraph )
		{
			if(  bGraph )
			{
				FindChildByName( _T("resultlist") )->SetVisible( FALSE, TRUE );
				FindChildByName( _T("imageGraph") )->SetVisible( TRUE, TRUE );
			}
			else
			{
				FindChildByName( _T("resultlist") )->SetVisible( TRUE, TRUE );
				FindChildByName( _T("imageGraph") )->SetVisible( FALSE, TRUE );
			}
		}

		BOOL IsCurrentGraphStep()
		{
			BOOL bInGraphMode = FindChildByName( _T("imageGraph") )->IsVisible();

			return bInGraphMode;
		}

		LRESULT ActionOnListChange( UINT32 msg, WPARAM waprm, LPARAM lparam, BOOL& handled )
		{
			const NativeTestItem* nt = (const NativeTestItem*)lparam;

			m_singleListAdp->UpDateListItem( nt );

			if( nt->testCode >= TEST_ITEM_GRAPH_TEST_START )
			{
				FindChildByName( _T("resultlist") )->SetVisible( FALSE, TRUE );
				FindChildByName( _T("imageGraph") )->SetVisible( TRUE, TRUE );
			}

			return 0;
		}

		LRESULT ActionOnOver( UINT32 msg, WPARAM waprm, LPARAM lparam, BOOL& handled )
		{
			FindChildByName( _T("resultlist") )->SetVisible( TRUE, TRUE );
			FindChildByName( _T("imageGraph") )->SetVisible( FALSE, TRUE );

			int device = (int)waprm;
			int status = (int)lparam;
			SButton* sb = (SButton*)FindChildByName(_T("btnstart"));
			if( status == TEST_NONE ){
				sb->SetWindowText("START");
			}else if( status == TEST_PASS ){
				sb->SetWindowText("PASS");
				sb->SetAttribute( L"skin", L"StartBtnPASS" );
			}else if( status == TEST_NG ){
				sb->SetWindowText("NG");
				sb->SetAttribute( L"skin", L"StartBtnNG" );
			}else if( status == TEST_TBD ){
				sb->SetWindowText("TBD");
				sb->SetAttribute( L"skin", L"StartBtnTBD" );
			}else if( status == TEST_GOING ){
			}

			SRichEdit* pRichEdit = (SRichEdit*)FindChildByName(_T("richText"));

			if( NULL == pRichEdit )
			{
				SWindow* fatherWnd = GetParent()->GetParent();
				pRichEdit = (SRichEdit*)fatherWnd->FindChildByName(_T("richText"));

				SComboBox* sb = (SComboBox*)fatherWnd->FindChildByName( _T("cbx_test") );
				int sel = sb->GetCurSel();
				if( sel != (int)waprm ) return 0;
			}

			if( pRichEdit )
			{
				pRichEdit->SetWindowText(_T(""));
				ColorText& text =  GetTestWapperInterface()->GetTestMessage( (int)waprm );

				PrintRichMsg( pRichEdit, text );
			}

			SEdit* pEditSn = (SEdit*)FindChildByName(_T("snCode"));
			if(pEditSn)
			{
				pEditSn->EnableWindow(TRUE);
				pEditSn->SetWindowText("");
			}
			
		
			return 0;
		}

		LRESULT ActionOnStart( UINT32 msg, WPARAM waprm, LPARAM lparam, BOOL& handled )
		{
			m_singleListAdp->Reset();

			SButton* sb = (SButton*)FindChildByName(_T("btnstart"));

			sb->SetWindowText("TESTING");
			sb->SetAttribute( L"skin", L"StartBtnTEST" );

// 			int device = lparam >> 16;
// 			unsigned int status = lparam & 0xffff;
// 			if( status == TEST_NONE ){
// 				sb->SetWindowText("START");
// 			}else if( status == TEST_PASS ){
// 				sb->SetWindowText("PASS");
// 				sb->SetAttribute( L"skin", L"StartBtnPASS" );
// 			}else if( status == TEST_NG ){
// 				sb->SetWindowText("NG");
// 				sb->SetAttribute( L"skin", L"StartBtnNG" );
// 			}else if( status == TEST_TBD ){
// 				sb->SetWindowText("TBD");
// 				sb->SetAttribute( L"skin", L"StartBtnTBD" );
// 			}else if( status == TEST_GOING ){
// 				
// 			}

			SRichEdit* pRichEdit = FindChildByName2<SRichEdit>(_T("richText"));

			if( NULL == pRichEdit )
			{
				SWindow* fatherWnd = GetParent()->GetParent();
				pRichEdit = (SRichEdit*)fatherWnd->FindChildByName(_T("richText"));
			}

			if( pRichEdit )
			{
				pRichEdit->SetWindowText(_T(""));
			}

			return 0;
		}

		LRESULT ActionOnProcess( UINT32 msg, WPARAM waprm, LPARAM lparam, BOOL& handled )
		{
			SProgress* sp = (SProgress*)FindChildByName(_T("progress"));
			sp->SetRange( 0, max(1, lparam >> 16) );
			sp->SetValue( lparam & 0xffff );

			return 0;
		}

		LRESULT ActionOnTouchData( UINT32 msg, WPARAM waprm, LPARAM lparam, BOOL& handled )
		{
			FindChildByName( _T("imageGraph") )->Invalidate();

			return 0;
		}

		static void PrintRichMsg( SRichEdit* pRichEdit, const ColorText& sz )
		{
			static CHARFORMAT cf;  
			ZeroMemory( &cf, sizeof(CHARFORMAT) );
			cf.cbSize = sizeof(CHARFORMAT);
			cf.dwMask = CFM_COLOR | CFM_BOLD | CFM_SIZE;

			//OnLineLogApp.AppendLogMessage( GetWrapperAddr()->GetIDMark(), value_buffer_to_string<unsigned char>( buffer, onceLen ).c_str() );
			//OnLineLogApp.AppendLogMessage( _T("ok") );

		    //tstring st = value_buffer_to_string<wchar_t>( &w_sz[0], 100 );

			//OnLineLogApp.AppendLogMessage( st.c_str() );



			//long start = 0, end = 0;
 			CHARRANGE range;
 			const int max_width = 2048;
 			wchar_t w_sz[max_width] = {0};
 			ColorText* pText = const_cast<ColorText*>( &sz );
 			while ( pText )
 			{
 				range.cpMin = range.cpMax = -1;
 				pRichEdit->SSendMessage( EM_EXSETSEL, 0, (LPARAM)&range );
 				pRichEdit->SSendMessage( EM_EXGETSEL, 0, (LPARAM)&range );
 				int iSel1 = range.cpMax;
 
 				for( int index = 0; index < (int)pText->strText.length() && index < max_width; index++ )
 					w_sz[index] = pText->strText.at(index);
 				w_sz[pText->strText.length()] = 0;
 
 				pRichEdit->SSendMessage( EM_REPLACESEL, 0, (LPARAM)w_sz );
 
 				range.cpMin = range.cpMax = -1;
 				pRichEdit->SSendMessage( EM_EXSETSEL, 0, (LPARAM)&range );
 				pRichEdit->SSendMessage( EM_EXGETSEL, 0, (LPARAM)&range );
 				int iSel2 = range.cpMax;
 
 				cf.crTextColor = pText->dwColor;
 				cf.yHeight     = pText->iHeight;
 				if( pText->bBold )    cf.dwMask |=  (CFM_BOLD);
 				else                  cf.dwMask &=  (~CFM_BOLD);
 
 				range.cpMin = iSel1;
 				range.cpMax = iSel2;
 				pRichEdit->SSendMessage( EM_EXSETSEL, 0, (LPARAM)&range );
 				pRichEdit->SSendMessage( EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf );
 				pText = pText->next;
 			}

			pRichEdit->SetScrollPos( TRUE, 10000, FALSE );
		}


	private:
		int m_devNo;
		//SWindow* m_fatherWin;
		CListAdapter*   m_singleListAdp;
	};
}