// DL��ǩDlg.h : ͷ�ļ�
//

#pragma once

#include "XPButton.h"
#include "DLEdit.h"
#include "DLShower.h"
#include "DLMgr.h"

#include "DLStatic.h"
#include "CTrayIconDef.h"

#define DHT_CLOSE			1		//close����				
#define DHT_CAPTION		2		//����������


// CDL��ǩDlg �Ի���
class CDL��ǩDlg : public CDialog
{
// ����
public:
	CDL��ǩDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	virtual BOOL OnInitDialog();

// ʵ��
private:
	CTrayIcon TrayIcon;
	HICON m_hIcon;

	CXPButton m_xpTest;			//	xp��ť����
	CXPButton	 m_btnAdd;
	CDLEdit  * m_edit;				//	�๦�ܱ༭��
	CDLStatic m_timer;				//	timer��̬�ı���

//����ػر߿������
private:
	CRect m_rcClose;					//	������close��ť
	DWORD m_LastHit;				//	��һ�Ρ����в��ԡ�
	DWORD m_ButtonDown;		//	close��ť����
	CRect m_rcLEdge;					//	��߱߿�
	CRect m_rcREdge;				//	�ұ߱߿�
	CRect m_rcBEdge;				//	�ײ��߿�
	Image * m_image;				//	��ͼ

	DLMgr * m_dlmgr;				//	���ڵ�����
	CString m_text;						//	��ǰ�༭�ı�
	CWnd *  m_texting;	
	bool m_bExbanded;

	CXPButton m_btnLayoutUp;
	CXPButton m_btnLayoutDown;
	CXPButton m_btnLayoutLeft;
	CXPButton m_btnLayoutRight;

// ���ɵ���Ϣӳ�亯��
public:
	
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();

	afx_msg void OnNcPaint();
	afx_msg BOOL OnNcActivate(BOOL bActive);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();

	afx_msg LRESULT OnAddShower(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDelShower(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnTrayNotification(WPARAM uID,LPARAM lEvent);
	afx_msg void OnAbout();
	afx_msg void OnCloseex();

	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedTest();
	void OnBnLayoutUp();
	void OnBnLayoutDown();
	void OnBnLayoutLeft();
	void OnBnLayoutRight();

protected:
	DWORD HitTest(CPoint pt);			//�Զ��塰���в��ԡ�
	DECLARE_MESSAGE_MAP()

public:
	void ControlInit();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
