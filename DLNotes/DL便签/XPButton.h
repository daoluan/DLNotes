#pragma once

// XPButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CXPButton window

class CXPButton : public CButton
{
	// Construction
public:
	CXPButton();
	virtual ~CXPButton();

private:
	//Image * m_ImageHover;
	Image * m_ImageNormal;
	Image * m_ImageSelected;
	//CBitmap m_Bk;

	CDC m_dcHover;
	CDC m_dcNormal;
	CDC m_dcSelected;
	CDC m_dcBkgnd;
	CDC * m_dcCurr;

	//	按钮的状态
	BOOL m_bOver;		//	鼠标位于按钮之上时该值为true，反之为flase
	BOOL m_bTracking;
	BOOL m_bSelected;	//	按钮被按下是该值为true
	BOOL m_bFocus;		//	按钮为当前焦点所在时该值为true

	CString m_pngNormal;
	//CString m_pngHover;
	//CString m_pngClick;

public:
	DECLARE_DYNAMIC(CXPButton)

protected:
	DECLARE_MESSAGE_MAP()

public:
	virtual void PreSubclassWindow();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMouseHover(WPARAM wParam, LPARAM lParam);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

public:
	virtual bool CreateExEx(LPCTSTR lpszCaption,
		DWORD dwStyle,
		RECT& rect,
		CWnd* pParentWnd,
		UINT nID,
		LPCTSTR lpPngNormalFileName,
		LPCTSTR lpPngHoverFileName = NULL,
		LPCTSTR lpPngClickFileName = NULL);

private:
	void RePaintParent(bool flag = 1);
	void PaintBk(CDC * pDC);
	void PaintBtn(CDC * pDC);
};



