// XPButton.cpp : 实现文件
//

#include "stdafx.h"
#include "DL便签.h"
#include "XPButton.h"
#include "GdiPlus.h"

// CXPButton

IMPLEMENT_DYNAMIC(CXPButton, CButton)

CXPButton::CXPButton()
{
	m_dcCurr = NULL;
//	m_ImageHover = NULL;
	m_ImageNormal = NULL;
	m_ImageSelected = NULL;
	m_bOver = m_bSelected = m_bTracking = m_bFocus = FALSE;
	m_bTracking = true;
}

CXPButton::~CXPButton()
{
}

BEGIN_MESSAGE_MAP(CXPButton, CButton)
	//{{AFX_MSG_MAP(CXPButton)
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
	//}}AFX_MSG_MAP
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()

void CXPButton::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	CButton::PreSubclassWindow();

	//自绘
	ModifyStyle(0, BS_OWNERDRAW, SWP_FRAMECHANGED);
}

void CXPButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_bTracking)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE | TME_HOVER;
		tme.dwHoverTime = HOVER_DEFAULT;
		_TrackMouseEvent(&tme);
		m_bTracking = false;
	}
	CButton::OnMouseMove(nFlags, point);
}

LRESULT CXPButton::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	m_bOver = FALSE;
	m_bTracking = true;
	Invalidate();
	return 0;
}

LRESULT CXPButton::OnMouseHover(WPARAM wParam, LPARAM lParam)
{
	m_bOver = TRUE;
	//InvalidateRect(NULL,1);多余的
	/*CWnd * parent;
	parent = GetParent();
	CRect rect;
	this->GetWindowRect(&rect);
	parent->ScreenToClient(&rect);
	parent->InvalidateRect(&rect,1);*/
	Invalidate();
	TRACE(L"hover!\n"); 
	return 0;
}

bool CXPButton::CreateExEx(LPCTSTR lpszCaption,
						   DWORD dwStyle,
						   RECT& rect,
						   CWnd* pParentWnd,
						   UINT nID,
						   LPCTSTR lpPngNormalFileName,
						   LPCTSTR lpPngHoverFileName,
						   LPCTSTR lpPngClickFileName)
{
	m_pngNormal.SetString(lpPngNormalFileName,lstrlen(lpPngNormalFileName));
	//m_pngHover.SetString(lpPngHoverFileName,lstrlen(lpPngHoverFileName));
	//m_pngClick.SetString(lpPngClickFileName,lstrlen(lpPngClickFileName));

	m_ImageNormal = Image::FromFile(lpPngNormalFileName);
	//m_ImageHover= Image::FromFile(lpPngHoverFileName);
	//m_ImageSelected = Image::FromFile(lpPngClickFileName);

	rect.bottom = rect.top + rect.right - rect.left;
	return Create(lpszCaption,
		dwStyle,
		rect,
		pParentWnd,
		nID);
}

void CXPButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CButton::OnLButtonDown(nFlags, point);
}

void CXPButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//m_bSelected = false;
	CButton::OnLButtonUp(nFlags, point);
}

void CXPButton::PaintBk(CDC * pDC)
{
	CRect rect;
	GetClientRect(&rect);
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),
		&m_dcBkgnd,0,0,SRCCOPY);
}

void CXPButton::PaintBtn(CDC * pDC)
{
	CRect rect;
	GetClientRect(&rect);
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),
		m_dcCurr,0,0,SRCCOPY);
}

HBRUSH CXPButton::CtlColor(CDC* pDC, UINT nCtlColor)
{	
	/*Image * m_ImageHover;
	Image * m_ImageNormal;
	Image * m_ImageSelected;

	CDC m_dcHover;
	CDC m_dcNormal;
	CDC m_dcSelected;
	CDC m_dcBkgnd;*/
	CRect crect;
	CDC dc;
	CBitmap bmp, memBmp,*pOldBitmap;
	/*
	在这里dc是内存DC，同时m_dcNormal..也是内存DC，对于dc和m_dcNormal都要选择
	一个位图对象。
	dc						选择的位图对象：	memBmp
	m_dcNormal		选择的位图对象：	bmp
	在绘图完毕之后，两者选择的对象都可以DeleteObject()；
	*/
	GetClientRect(&crect);

	dc.CreateCompatibleDC(pDC);

	if(!memBmp.GetSafeHandle())
		memBmp.CreateCompatibleBitmap(pDC,crect.Width(),crect.Height());

	pOldBitmap = (CBitmap *)dc.SelectObject(&memBmp);
	dc.BitBlt(0,0,crect.Width(),crect.Height(),pDC,0,0,SRCCOPY);

	Graphics graphics(dc.GetSafeHdc());

	if(!m_dcBkgnd.m_hDC)
	{
		CRect crect,rect;
		CClientDC cdc(GetParent());

		GetClientRect(&crect);
		GetWindowRect(rect);

		GetParent()->ScreenToClient(rect);
		m_dcBkgnd.CreateCompatibleDC(&cdc);
		bmp.CreateCompatibleBitmap(&cdc, crect.Width(), crect.Height());

		pOldBitmap = m_dcBkgnd.SelectObject(&bmp);
		m_dcBkgnd.BitBlt(0, 0, crect.Width(), crect.Height(), &cdc, rect.left, rect.top, SRCCOPY);
		bmp.DeleteObject();

		/*
		CPen pen(PS_SOLID,1,RGB(0,0,0));
		m_dcBkgnd.SelectObject(&pen);
		m_dcBkgnd.TextOutW(0,0,L"思愿",lstrlen(L"思愿"));
		pen.DeleteObject();*/
	}// if

	if(!m_dcNormal.m_hDC)
	{
		PaintBk(&dc);
		graphics.DrawImage(m_ImageNormal,0,0,crect.Width(),crect.Height());

		m_dcNormal.CreateCompatibleDC(pDC);
		bmp.CreateCompatibleBitmap(pDC, crect.Width(), crect.Height());
		//在这里，会写成下面这句话，这里m_dcNormal刚刚创建，里面没有任何位图的信息，
		//所以也就无所谓创建与m_dcNormal相兼容的位图。
		//bmp.CreateCompatibleBitmap(m_dcNormal, crect.Width(), crect.Height());
		m_dcNormal.SelectObject(&bmp);

		m_dcNormal.BitBlt(0, 0, crect.Width(), crect.Height(), &dc, 0, 0, SRCCOPY);
		bmp.DeleteObject();		

		/*
		下面是画字的核心代码
		*/
		/*Graphics g(m_dcNormal.m_hDC);
		Font f(L"宋体",12);
		StringFormat stringformat;  
		stringformat.SetAlignment(StringAlignmentCenter);  
		SolidBrush brush(Color(255, 0, 0, 0));  

		CRect rcClient ;  
		GetClientRect(rcClient);  
		g.SetTextRenderingHint(TextRenderingHintAntiAlias); 

		g.DrawString(TEXT("思愿"), -1, &f,  
		RectF(0, 0, rcClient.Width(), rcClient.Height()), &stringformat, &brush); */
	}// if

	if(!m_dcHover.m_hDC)
	{
		PaintBk(&dc);		
		CRect crect;
		GetClientRect(&crect);

		m_dcHover.CreateCompatibleDC(pDC);
		pOldBitmap = (CBitmap *)m_dcHover.SelectObject(&bmp);
		m_dcHover.BitBlt(0,0,crect.Width(),crect.Height(),pDC,0,0,SRCCOPY);
		m_dcHover.SelectObject(pOldBitmap);

		ColorMatrix HotMat = 
		{	
			1.05f, 0.00f, 0.00f, 0.00f, 0.00f,
			0.00f, 1.05f, 0.00f, 0.00f, 0.00f,
			0.00f, 0.00f, 1.05f, 0.00f, 0.00f,
			0.00f, 0.00f, 0.00f, 1.00f, 0.00f,
			0.05f, 0.05f, 0.05f, 0.00f, 1.00f	
		};

		/*
		ColorMatrix HotMat = {	
		0.299f, 0.299f, 0.299f, 0.299f,0.299f,
		0.587f, 0.587f, 0.587f, 0.587f,0.587f,
		0.144f, 0.144f, 0.144f, 0.144f,0.144f,
		0.00f,   0.00f,   0.00f,  1.00f,   0.00f,
		0.00f, 0.00f, 0.00f, 0.00f, 1.00f	};
		*/

		ImageAttributes ia;
		ia.SetColorMatrix(&HotMat);

		float width = (float)m_ImageNormal->GetWidth();
		float height = (float)m_ImageNormal->GetHeight();

		RectF grect; grect.X=0, grect.Y=0; grect.Width = crect.Width(); grect.Height = crect.Height();

		graphics.DrawImage(m_ImageNormal,
			grect,0,0,width,height, UnitPixel, &ia);

		bmp.CreateCompatibleBitmap(&dc,crect.Width(), crect.Height());
		m_dcHover.SelectObject(&bmp);
		m_dcHover.BitBlt(0, 0, crect.Width(), crect.Height(), &dc, 0, 0, SRCCOPY);
		bmp.DeleteObject();
		/*
		下面是画字的核心代码
		*/
		/*Graphics g(m_dcHover.m_hDC);
		Font f(L"宋体",12);
		StringFormat stringformat;  
		stringformat.SetAlignment(StringAlignmentCenter);  
		SolidBrush brush(Color(255, 0, 0, 0));  

		CRect rcClient ;  
		GetClientRect(rcClient);  
		g.SetTextRenderingHint(TextRenderingHintAntiAlias); 

		g.DrawString(TEXT("思愿"), -1, &f,  
		RectF(0, 0, rcClient.Width()+2, rcClient.Height()), &stringformat, &brush);  */
	}// if

	if(!m_dcSelected.m_hDC)
	{
		PaintBk(&dc);
		graphics.DrawImage(m_ImageNormal,1,1,crect.Width(),crect.Height());

		bmp.CreateCompatibleBitmap(pDC,crect.Width(),crect.Height());
		m_dcSelected.CreateCompatibleDC(pDC);
		m_dcSelected.SelectObject(&bmp);
		m_dcSelected.BitBlt(0,0,crect.Width(),crect.Height(),&dc,0,0,SRCCOPY);
		bmp.DeleteObject();
	}

	if(!m_dcCurr)
		m_dcCurr = &m_dcNormal;
	return NULL;
}

void CXPButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	UINT state = lpDrawItemStruct->itemState;
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

	if (state & ODS_SELECTED)
	{
		m_bSelected = TRUE;
		TRACE(L"Select!\n"); 
	}// if
	else
		m_bSelected = false;

	if(m_bSelected)
	{
		m_dcCurr = &m_dcSelected;
	}// if
	else if(m_bOver)
		m_dcCurr = &m_dcHover;
	else m_dcCurr = &m_dcNormal;
	PaintBtn(pDC);
}
