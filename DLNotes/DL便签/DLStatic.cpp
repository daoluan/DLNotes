// DLStatic.cpp : 实现文件
//

#include "stdafx.h"
#include "DL便签.h"
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



// CDLStatic 消息处理程序



LRESULT CDLStatic::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类

	//防止文字重叠而重写
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return CStatic::OnEraseBkgnd(pDC);
}

void CDLStatic::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CTime time;
	CString s;
	time = CTime::GetCurrentTime();
		s = time.Format("%H:%M");

		this->SetWindowTextW(s);
	CStatic::OnTimer(nIDEvent);
}
