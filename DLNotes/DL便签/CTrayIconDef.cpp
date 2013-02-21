#include <windows.h>
#include "stdafx.h"
#include "CTrayIconDef.h"
#include "shellapi.h"

IMPLEMENT_DYNAMIC(CTrayIcon, CCmdTarget)

WCHAR szTip[128] = TEXT("dl便签");

CTrayIcon::CTrayIcon(UINT uID):m_pMenu(NULL)
{
	//初始化数据
	::memset(&m_nid,0,sizeof(m_nid));
	m_nid.cbSize = sizeof(m_nid);
	m_nid.uID = uID;
	lstrcpy(m_nid.szTip, szTip);
}

CTrayIcon::~CTrayIcon()
{
	m_pMenu->DestroyMenu();
	this->SetIcon(0);
}

void CTrayIcon::SetNotificationWnd(CWnd* pNotifyWnd, UINT uCbMsg)
{
	ASSERT(pNotifyWnd==NULL
		||::IsWindow(pNotifyWnd->GetSafeHwnd()));

	m_nid.hWnd = pNotifyWnd->m_hWnd;

	ASSERT(uCbMsg == 0||uCbMsg>=WM_USER);

	m_nid.uCallbackMessage = uCbMsg;
}

BOOL CTrayIcon::SetIcon(UINT uID)
{
	//记得进行初始化
	HICON hIcon = NULL;
	if(uID)
	{
		hIcon = AfxGetApp()->LoadIconW(uID);
	}
	return this->SetIcon(hIcon,NULL);
}

BOOL CTrayIcon::SetIcon(HICON hicon, LPCSTR lpTip)
{
	UINT uMsg;
	m_nid.uFlags = 0;

	if(hicon)
	{
		uMsg = m_nid.hIcon?NIM_MODIFY:NIM_ADD;
		m_nid.hIcon = hicon;
		m_nid.uFlags = NIF_ICON;
	}
	else
	{
		if(m_nid.hIcon==NULL)
			return true;
		uMsg = NIM_DELETE;	
		m_nid.hIcon = NULL;
	}

	/*
	if(lpTip)
	{
		::lstrcpyn(m_nid.szTip,(LPCWSTR)lpTip,sizeof(m_nid.szTip));
	}
	*/

	if(m_nid.szTip[0])
		m_nid.uFlags |= NIF_TIP;

	if(m_nid.uCallbackMessage && m_nid.hWnd)
		m_nid.uFlags |= NIF_MESSAGE;

	BOOL bRet = ::Shell_NotifyIcon(uMsg,&m_nid);
	if(!bRet)
		m_nid.hIcon = NULL;

	 /*ShowBalloonTip();*/

	return bRet;
}

LRESULT CTrayIcon::OnTrayNotification(WPARAM uID, LPARAM lEvent)
{
	if(uID != m_nid.uID || (lEvent != WM_RBUTTONUP && lEvent != WM_LBUTTONDBLCLK &&
		lEvent != WM_LBUTTONDOWN))	return 0;

	//	先注释，日后更新
	CPoint mouse;
	if(!m_pMenu)
	{
		m_pMenu = new CMenu();
		if(!m_pMenu->LoadMenuW(m_nid.uID))		return 0;
		m_pMenu = m_pMenu->GetSubMenu(0);
		if(!m_pMenu)	return 0;
	}// if

	switch(lEvent)
	{
	case WM_RBUTTONUP:		
		::GetCursorPos(&mouse);
		::SetForegroundWindow(m_nid.hWnd);
		::TrackPopupMenu(m_pMenu->m_hMenu,TRUE,mouse.x,mouse.y,0,
			m_nid.hWnd,NULL);
		break;

	case WM_LBUTTONDOWN:
		ShowWindow(m_nid.hWnd,SW_SHOW);
		break;
	}// switch

	/*给菜单项发送消息，日后有用
	{
		::SendMessage(m_nid.hWnd,WM_COMMAND,
			pSubMenu->GetMenuItemID(0),0);
	}
	*/
	return 1;
}

/*显示泡泡提示，日后有用*/
/*
BOOL CTrayIcon::ShowBalloonTip()
{
	m_nid.uFlags = NIF_INFO;
	lstrcpy(m_nid.szInfo,szTip);
	lstrcpy(m_nid.szInfoTitle ,szTip);
	m_nid.uTimeout = 2000;
	m_nid.dwInfoFlags = NIIF_INFO;
	return Shell_NotifyIcon(NIM_MODIFY, &m_nid);
}
*/