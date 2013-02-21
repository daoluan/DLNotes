#pragma once


// CDLEdit

class CDLEdit : public CRichEditCtrl
{
	DECLARE_DYNAMIC(CDLEdit)

public:
	CDLEdit();
	virtual ~CDLEdit();
	afx_msg void OnEnChange();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

public:
	CRect m_rct;

protected:
	DECLARE_MESSAGE_MAP()
};


