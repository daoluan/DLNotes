// DL便签Dlg.h : 头文件
//

#pragma once

#include "XPButton.h"
#include "DLEdit.h"
#include "DLShower.h"
#include "DLMgr.h"

#include "DLStatic.h"
#include "CTrayIconDef.h"

#define DHT_CLOSE			1		//close击中				
#define DHT_CAPTION		2		//标题栏击中


// CDL便签Dlg 对话框
class CDL便签Dlg : public CDialog
{
// 构造
public:
	CDL便签Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	virtual BOOL OnInitDialog();

// 实现
private:
	CTrayIcon TrayIcon;
	HICON m_hIcon;

	CXPButton m_xpTest;			//	xp按钮测试
	CXPButton	 m_btnAdd;
	CDLEdit  * m_edit;				//	多功能编辑框
	CDLStatic m_timer;				//	timer静态文本框

//完成重回边框的数据
private:
	CRect m_rcClose;					//	标题栏close按钮
	DWORD m_LastHit;				//	上一次“击中测试”
	DWORD m_ButtonDown;		//	close按钮按下
	CRect m_rcLEdge;					//	左边边框
	CRect m_rcREdge;				//	右边边框
	CRect m_rcBEdge;				//	底部边框
	Image * m_image;				//	底图

	DLMgr * m_dlmgr;				//	窗口单链表
	CString m_text;						//	当前编辑文本
	CWnd *  m_texting;	
	bool m_bExbanded;

	CXPButton m_btnLayoutUp;
	CXPButton m_btnLayoutDown;
	CXPButton m_btnLayoutLeft;
	CXPButton m_btnLayoutRight;

// 生成的消息映射函数
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
	DWORD HitTest(CPoint pt);			//自定义“击中测试”
	DECLARE_MESSAGE_MAP()

public:
	void ControlInit();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
