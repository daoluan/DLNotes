// DLEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "DL便签.h"
#include "DLEdit.h"

// CDLEdit

IMPLEMENT_DYNAMIC(CDLEdit, CRichEditCtrl)

CDLEdit::CDLEdit()
{
}

CDLEdit::~CDLEdit()
{
}


BEGIN_MESSAGE_MAP(CDLEdit, CRichEditCtrl)
	ON_CONTROL_REFLECT(EN_CHANGE, &CDLEdit::OnEnChange)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CDLEdit 消息处理程序

void CDLEdit::OnEnChange()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CRichEditCtrl::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码	
	CString str;
	GetWindowTextW(str);
	if(str.GetLength()>40)		{::MessageBeep(-1);	str = str.Left(40);}
	SetWindowTextW(str);
	//	设置光标的位置到最后
	this->SetSel(-1,-1);
	/*if(::GetKeyState(VK_BACK)<0)
	{
		CWnd * parent = GetParent();
		parent->InvalidateRect(&m_rct,true);
	}*/
}

int CDLEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CRichEditCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	CWnd * parent = GetParent();
	GetWindowRect(&m_rct);
	parent->ScreenToClient(m_rct);
	return 0;
}
