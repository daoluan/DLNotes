#pragma once

// ShowerBase

class CShowerBase : public CWnd
{
	DECLARE_DYNAMIC(CShowerBase)

public:
//Êó±êÐüÍ£²ÎÊý
	bool m_bTrack;
	bool m_bHover;
	CBrush m_gndBrush;
	CShowerBase();
	virtual ~CShowerBase();

	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMoving(UINT fwSide, LPRECT pRect);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


