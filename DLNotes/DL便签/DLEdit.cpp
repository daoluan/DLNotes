// DLEdit.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DL��ǩ.h"
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

// CDLEdit ��Ϣ�������

void CDLEdit::OnEnChange()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CRichEditCtrl::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������	
	CString str;
	GetWindowTextW(str);
	if(str.GetLength()>40)		{::MessageBeep(-1);	str = str.Left(40);}
	SetWindowTextW(str);
	//	���ù���λ�õ����
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

	// TODO:  �ڴ������ר�õĴ�������
	CWnd * parent = GetParent();
	GetWindowRect(&m_rct);
	parent->ScreenToClient(m_rct);
	return 0;
}
