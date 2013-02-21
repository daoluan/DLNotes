// ShowerBase.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DL��ǩ.h"
#include "ShowerBase.h"

// ShowerBase

IMPLEMENT_DYNAMIC(CShowerBase, CWnd)

CShowerBase::CShowerBase()
{
	m_gndBrush.CreateSolidBrush(RGB(255,255,0));
}

CShowerBase::~CShowerBase()
{
}


BEGIN_MESSAGE_MAP(CShowerBase, CWnd)
	ON_WM_MOUSEHOVER()
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOVING()
	ON_WM_LBUTTONUP()
	ON_WM_MOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// ShowerBase ��Ϣ�������
void CShowerBase::OnMouseHover(UINT nFlags, CPoint point)
{
	m_bHover = true;
	Invalidate();
	SetLayeredWindowAttributes(0,255,LWA_ALPHA);
	CWnd::OnMouseHover(nFlags, point);
}

void CShowerBase::OnMouseLeave()
{
	m_bTrack = true;
	m_bHover = false;
	Invalidate();
	SetLayeredWindowAttributes(0,100,LWA_ALPHA);
	CWnd::OnMouseLeave();
}

void CShowerBase::OnMouseMove(UINT nFlags, CPoint point)
{
	if(m_bTrack)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(TRACKMOUSEEVENT);
		tme.dwFlags = TME_LEAVE|TME_HOVER;
		tme.dwHoverTime = HOVER_DEFAULT;
		tme.hwndTrack = this->GetSafeHwnd();
		::TrackMouseEvent(&tme);
		m_bTrack = false;
	}// if
	CWnd::OnMouseMove(nFlags, point);
}

int CShowerBase::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	/*
	::SetClassLong(GetSafeHwnd(),GCL_HBRBACKGROUND,
		(LONG)::CreateSolidBrush(RGB(255,0,0)));
	*/
	return 0;
}

void CShowerBase::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CWnd * pParent = GetParent();
	pParent->ModifyStyleEx(WS_EX_TRANSPARENT,0);
	SendMessage(WM_SYSCOMMAND,0xF012,0); 
	CWnd::OnLButtonDown(nFlags, point);
}

void CShowerBase::OnMoving(UINT fwSide, LPRECT pRect)
{
	CWnd::OnMoving(fwSide, pRect);
	CWnd * pParent = GetParent();
	CRect rect;
	pParent->GetWindowRect(&rect);
	pParent->MoveWindow(pRect->left-rect.Width(),pRect->top,rect.Width(),rect.Height(),true);
	// TODO: �ڴ˴������Ϣ����������
}

void CShowerBase::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CWnd::OnLButtonUp(nFlags, point);
}

void CShowerBase::OnMove(int x, int y)
{
	CWnd::OnMove(x, y);
	CWnd * pParent = GetParent();
	pParent->ModifyStyleEx(0,WS_EX_TRANSPARENT);
	// TODO: �ڴ˴������Ϣ����������
}

void CShowerBase::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	ClientToScreen(&point);
	CWnd * pParent = GetParent();
	pParent->ScreenToClient(&point);
	pParent->SendMessage(WM_RBUTTONDOWN,MK_LBUTTON,MAKELPARAM(point.x, point.y));
	CWnd::OnRButtonDown(nFlags, point);
}

BOOL CShowerBase::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CRect rect;
	GetClientRect(&rect);
	pDC->FillRect(&rect,&m_gndBrush);
	return 1;
}
