#pragma once

#include "DLStatic.h"
// CDLShower

#include "ShowerBase.h"

class CDLShower : public CWnd
{
	DECLARE_DYNAMIC(CDLShower)

public:
	CDLShower(DWORD color = NULL);
	virtual ~CDLShower();
	static bool RegisterWndClass();

private:
	CDLStatic m_text;
	int m_alpha;
	CString m_str;
	int m_id;

	DWORD m_mode;
	CMenu * m_menu;

	CRect m_rcClose;					//标题栏close按钮
	DWORD m_LastHit;				//上一次“击中测试”
	DWORD m_ButtonDown;		//close按钮按下

//	是否最顶层
	bool m_isTopMost;
	bool m_isTransParent;
//鼠标悬停参数
	bool m_bTrack;
	bool m_bHover;

	CShowerBase * m_base;

protected:
	DECLARE_MESSAGE_MAP()

public:
	int Getid();
	void Setid(int id);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnAdd();
	afx_msg void OnDelete();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnTransparent();
	afx_msg void OnTopmost();

	void ModifyMenuItem();

	void SetNote(LPCTSTR str)
	{m_text.SetWindowText(str);}

	void GetNote(LPTSTR str)
	{m_text.GetWindowText(str,NOTEMAXLEN);}

	void SetMode(DWORD mode)
	{m_mode = mode;}

	DWORD GetMode()
	{return m_mode;}

	void AttachBase();
	afx_msg void OnMove(int x, int y);
};


