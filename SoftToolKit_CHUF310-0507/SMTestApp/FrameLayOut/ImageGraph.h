#pragma once
#include <WinDef.h>
// class CGraphMemDC
// {
// public:
// 	CGraphMemDC()
// 		:m_iSaveDC(0)
// 		,m_hNewBitmap(NULL)
// 		,m_dcMem(NULL)
// 		,m_hOldBitmap(NULL)
// 	{
// 
// 	}
// 	operator HDC&(  )
// 	{
// 		return m_dcMem;
// 	}
// 	void CreateMemoryDC( HDC hdc, const RECT& rect )
// 	{
// 		Clear();
// 		m_rect = rect;
// 		m_dcMem = ::CreateCompatibleDC( hdc );
// 		m_hNewBitmap = ::CreateCompatibleBitmap( hdc, rect.right-rect.left, rect.bottom-rect.top );
// 	}
// 	~CGraphMemDC()
// 	{
// 		::SelectObject( m_dcMem, m_hOldBitmap );
// 		Clear();
// 	}
// 	bool IsMemDcValid(  )
// 	{
// 		return m_dcMem != NULL || m_hNewBitmap != NULL;
// 	}
// 	void BitBlt( HDC dcDes, RECT& rect, int iXStart, int iYStart, WORD dwMode )
// 	{
// 		::BitBlt( dcDes, rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top, m_dcMem, iXStart, iYStart, dwMode );
// 	}
// 	int SaveMemDC()
// 	{
// 		m_hOldBitmap = (HBITMAP)::SelectObject( m_dcMem, m_hNewBitmap );
// 		return m_iSaveDC = ::SaveDC( m_dcMem );
// 	}
// 	void RestoreMemDC( int iSavedDC = 0 )
// 	{
// 		if( 0 == iSavedDC ) iSavedDC = m_iSaveDC;
// 		::RestoreDC( m_dcMem, iSavedDC );
// 	}
// 	void Clear()
// 	{
// 		if( NULL != m_dcMem ) ::DeleteDC( m_dcMem );
// 		if( NULL != m_hNewBitmap ) ::DeleteObject( m_hNewBitmap );
// 		m_dcMem = NULL;
// 		m_hNewBitmap = NULL;
// 	}
// private:
// 	HBITMAP m_hNewBitmap;
// 	HBITMAP m_hOldBitmap;
// 	RECT    m_rect;
// 	HDC     m_dcMem;
// 	int     m_iSaveDC;
// };

//////////////////////////////////////////////////////////////////////////
//  DCBuffer
//////////////////////////////////////////////////////////////////////////

HBITMAP CreateGDIBitmap( int nWid,int nHei,void ** ppBits )
{
	BITMAPINFO bmi;
	memset(&bmi, 0, sizeof(bmi));
	bmi.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth       = nWid;
	bmi.bmiHeader.biHeight      = -nHei; // top-down image 
	bmi.bmiHeader.biPlanes      = 1;
	bmi.bmiHeader.biBitCount    = 32;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biSizeImage   = 0;

	HDC hdc=GetDC(NULL);
	HBITMAP hBmp=CreateDIBSection(hdc,&bmi,DIB_RGB_COLORS,ppBits,0,0);
	ReleaseDC(NULL,hdc);
	return hBmp;
}

class DCBuffer
{
public:
	DCBuffer(HDC hdc,LPCRECT pRect,BYTE byAlpha,BOOL bCopyBits=TRUE)
		:m_hdc(hdc)
		,m_byAlpha(byAlpha)
		,m_pRc(pRect)
		,m_bCopyBits(bCopyBits)
	{
		m_nWid = pRect->right-pRect->left;
		m_nHei = pRect->bottom-pRect->top;
		m_hBmp = CreateGDIBitmap(m_nWid,m_nHei,(void**)&m_pBits);
		m_hMemDC = ::CreateCompatibleDC(hdc);
		::SetBkMode(m_hMemDC,TRANSPARENT);
		::SelectObject(m_hMemDC,m_hBmp);
		::SetViewportOrgEx(m_hMemDC,-pRect->left,-pRect->top,NULL);
		//从原DC中获得画笔，画刷，字体，颜色等
		m_hCurPen = ::SelectObject(hdc,GetStockObject(BLACK_PEN));
		m_hCurBrush = ::SelectObject(hdc,GetStockObject(BLACK_BRUSH));
		m_hCurFont = ::SelectObject(hdc,GetStockObject(DEFAULT_GUI_FONT));
		COLORREF crCur = ::GetTextColor(hdc);

		//将画笔，画刷，字体设置到memdc里
		::SelectObject(m_hMemDC,m_hCurPen);
		::SelectObject(m_hMemDC,m_hCurBrush);
		::SelectObject(m_hMemDC,m_hCurFont);
		::SetTextColor(m_hMemDC,crCur);

		if(m_bCopyBits) ::BitBlt(m_hMemDC,pRect->left,pRect->top,m_nWid,m_nHei,m_hdc,pRect->left,pRect->top,SRCCOPY);
		//将alpha全部强制修改为0xFF。
		BYTE * p= m_pBits+3;
		for(int i=0;i<m_nHei;i++)for(int j=0;j<m_nWid;j++,p+=4) *p=0xFF;
	}

	~DCBuffer()
	{
		//将alpha为0xFF的改为0,同时将rgb值也清0(XP系统下不清0会导致背景变成白色）,为0的改为0xFF
		BYTE * p= m_pBits+3;
		for(int i=0;i<m_nHei;i++)for(int j=0;j<m_nWid;j++,p+=4)
		{
			if(*p==0) *p=0xff;
			else
			{
				memset(p-3,0,4);
			}
		}
		BLENDFUNCTION bf={AC_SRC_OVER,0,m_byAlpha,AC_SRC_ALPHA };
		BOOL bRet=::AlphaBlend(m_hdc,m_pRc->left,m_pRc->top,m_nWid,m_nHei,m_hMemDC,m_pRc->left,m_pRc->top,m_nWid,m_nHei,bf);
		(void)bRet;
		::DeleteDC(m_hMemDC);
		::DeleteObject(m_hBmp);

		//恢复原DC的画笔，画刷，字体
		::SelectObject(m_hdc,m_hCurPen);
		::SelectObject(m_hdc,m_hCurBrush);
		::SelectObject(m_hdc,m_hCurFont);
	}

	operator HDC()
	{
		return m_hMemDC;
	}

protected:
	HDC m_hdc;
	HDC m_hMemDC;
	HBITMAP m_hBmp; 
	LPBYTE  m_pBits;
	BYTE    m_byAlpha;
	LPCRECT m_pRc;
	int     m_nWid,m_nHei;
	BOOL    m_bCopyBits;

	HGDIOBJ m_hCurPen;
	HGDIOBJ m_hCurBrush;
	HGDIOBJ m_hCurFont;
};

namespace SOUI{
	class CImageGraph : public SRadioBox
	{
		SOUI_CLASS_NAME(CImageGraph,L"graph")
	public:
		CImageGraph()
			:m_deivceNo(0)
		{

		}
		virtual ~CImageGraph()
		{

		}

		void SetDeviceNo( int deviceNo )
		{
			m_deivceNo = deviceNo;
		}
	protected:       
		void OnPaint(IRenderTarget *pRT)
		{
			CRect rect = GetClientRect();
			DCBuffer dcBuf( pRT->GetDC(), rect, 255, FALSE );

			GetTestWapperInterface()->SetContextForGraphTest( m_deivceNo, dcBuf, rect );

			//::BitBlt( pRT->GetDC(), 0, 0, rect.right - rect.left, rect.bottom - rect.top, memDC, 0, 0, SRCCOPY );
		}

		SOUI_MSG_MAP_BEGIN()
			MSG_WM_PAINT_EX(OnPaint)
		SOUI_MSG_MAP_END()

	private:
		int m_deivceNo;
	};
}