#pragma once


// CDLStatic

class CDLStatic : public CStatic
{
	DECLARE_DYNAMIC(CDLStatic)

public:
	CDLStatic();
	virtual ~CDLStatic();

protected:
	DECLARE_MESSAGE_MAP()
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


