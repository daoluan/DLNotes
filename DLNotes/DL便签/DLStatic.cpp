// DLStatic.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DL��ǩ.h"
#include "DLStatic.h"


// CDLStatic

IMPLEMENT_DYNAMIC(CDLStatic, CStatic)

CDLStatic::CDLStatic()
{

}

CDLStatic::~CDLStatic()
{
}


BEGIN_MESSAGE_MAP(CDLStatic, CStatic)
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
END_MESSAGE_MAP()



// CDLStatic ��Ϣ�������



LRESULT CDLStatic::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: �ڴ����ר�ô����/����û���

	//��ֹ�����ص�����д
	CRect rect;  
	switch(message)
	{
	case WM_SETTEXT:
		GetWindowRect(&rect);  
		CWnd* pParent = GetParent();  
		if(pParent) 
		{
			pParent->ScreenToClient(&rect);  
			pParent->InvalidateRect(&rect);
		}  
		break;
	}
	return CStatic::WindowProc(message, wParam, lParam);
}

BOOL CDLStatic::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	return CStatic::OnEraseBkgnd(pDC);
}

void CDLStatic::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CTime time;
	CString s;
	time = CTime::GetCurrentTime();
		s = time.Format("%H:%M");

		this->SetWindowTextW(s);
	CStatic::OnTimer(nIDEvent);
}
