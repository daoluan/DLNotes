// DLShower.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DL��ǩ.h"
#include "DLShower.h"

#include "COLOR.h"
#include "DLMgr.h"


extern CWnd * globalMainWnd;
// CDLShower

WCHAR CLSNAME[5][20] = {L"DLSHOWER_PURPLE",
L"DLSHOWER_PINK",
L"DLSHOWER_BLUE",
L"DLSHOWER_GREEN",
L"DLSHOWER_ORANGE"};

const COLORREF colors[5] = {PURPLE,PINK,BLUE,GREEN,ORANGE};

static int m_nColorIndex = 0;

IMPLEMENT_DYNAMIC(CDLShower, CWnd)

CDLShower::CDLShower(DWORD color)
{
	m_menu = new CMenu();
	m_menu->LoadMenuW(IDR_MENU_SHOWER);
	m_menu = m_menu->GetSubMenu(0);

	m_alpha = 128;
	m_str = "�յı�ǩ";
	m_id = 0;
	m_mode = 0;
	m_bHover = false;
	m_bTrack = true;
	m_isTopMost = false;
	m_isTransParent = false;
	m_base = NULL;
}

CDLShower::~CDLShower()
{
	//	��destroy menu�Ϳ�����������˵�ָ����
	m_menu->DestroyMenu();
	if(m_base)
		m_base->CloseWindow(),
		delete m_base;
}

bool CDLShower::RegisterWndClass()
{
	m_nColorIndex %= 5;
	WNDCLASS wndclass;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	HBRUSH hb = ::CreateSolidBrush(RGB(0,0,0));
	//NULL;���ܼ򵥵�ΪNULL��Ȼ�ػ���ʱ��û�л�ˢ
	wndclass.hbrBackground = hb;
	wndclass.hCursor = ::AfxGetApp()->LoadStandardCursor(IDC_ARROW);
	wndclass.hIcon = NULL;
	wndclass.hInstance = ::AfxGetInstanceHandle();
	wndclass.lpfnWndProc = ::DefWindowProc;
	wndclass.lpszClassName = L"DLSHOWER";
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_HREDRAW | CS_VREDRAW |CS_DBLCLKS; //ֻ���������������Ӧ˫������

	m_nColorIndex += 1;

	if(!::AfxRegisterClass(&wndclass))
	{
		::AfxMessageBox(L"ע�ᴰ��ʧ��",1,0);
		return false;
	}
	return true;
}

BEGIN_MESSAGE_MAP(CDLShower, CWnd)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(IDM_ADD, &CDLShower::OnAdd)
	ON_COMMAND(IDM_DELETE, &CDLShower::OnDelete)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	ON_WM_LBUTTONDOWN()
	ON_WM_COPYDATA()
	ON_WM_MOUSEHOVER()
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_COMMAND(IDM_TRANSPARENT, &CDLShower::OnTransparent)
	ON_COMMAND(IDM_TOPMOST, &CDLShower::OnTopmost)
	ON_WM_MOVE()
END_MESSAGE_MAP()


// CDLShower ��Ϣ�������


void CDLShower::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//	�Ѿ�ȡ������������
	ASSERT(globalMainWnd!=NULL);
	::ShowWindow(globalMainWnd->m_hWnd,SW_SHOW);

	COPYDATASTRUCT cds;
	//	���cds���ݣ���ΪlpData����ռ�
	cds.cbData = NOTEMAXLEN;
	cds.lpData = new WCHAR[NOTEMAXLEN];
	ASSERT(cds.lpData);

	m_text.GetWindowTextW((LPTSTR)cds.lpData,NOTEMAXLEN);
	::SendMessage(globalMainWnd->m_hWnd,WM_COPYDATA,(WPARAM)m_hWnd,(LPARAM)&cds);

	delete cds.lpData;
	CWnd::OnLButtonDblClk(nFlags, point);
}

void CDLShower::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	this->ClientToScreen(&point);
	::TrackPopupMenu(m_menu->GetSafeHmenu(),TPM_LEFTALIGN,point.x,point.y,0,
		this->GetSafeHwnd(),NULL);
	CWnd::OnRButtonDown(nFlags, point);
}

int CDLShower::Getid()
{
	return m_id;
}

void CDLShower::Setid(int id)
{
	m_id = id;
}

//	�Ҽ������˵��������������������µĻ���ɾ���ɵ�
void CDLShower::OnAdd()
{
	// TODO: �ڴ���������������
	::SendMessage(globalMainWnd->m_hWnd,WM_ADD_SHOWER,0,0);
}
void CDLShower::OnDelete()
{
	// TODO: �ڴ���������������
	::SendMessage(globalMainWnd->m_hWnd,WM_DEL_SHOWER,m_id,0);
}
int CDLShower::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	CRect rect;
	this->GetWindowRect(&rect);
	this->ScreenToClient(&rect);

	rect.DeflateRect(::GetSystemMetrics(SM_CYFRAME),::GetSystemMetrics(SM_CYFRAME));
	m_text.Create(L"�յı�ǩ",WS_CHILD|WS_VISIBLE,rect,this,IDC_SHOWER_STATIC);
	return 0;
}

HBRUSH CDLShower::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CWnd::OnCtlColor(pDC, pWnd, nCtlColor);
	// TODO:  �ڴ˸��� DC ���κ�����
	CFont font;

	switch(nCtlColor)
	{
	case CTLCOLOR_STATIC:
		font.CreatePointFont(105,L"΢���ź�");
		pDC->SelectObject(&font);
		pDC->SetTextColor(RGB(255,255,0));
		pDC->SetBkMode(TRANSPARENT);//͸��     
		return (HBRUSH)::GetStockObject(NULL_BRUSH); //��ʹﵽ����Ի��򱳾����ݵ�Ч��
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

void CDLShower::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	SendMessage(WM_SYSCOMMAND,0xF012,0);  
	CWnd::OnLButtonDown(nFlags, point);
}

BOOL CDLShower::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_str.Empty();
	m_str.SetString((WCHAR *)pCopyDataStruct->lpData,pCopyDataStruct->cbData);
	m_text.SetWindowTextW(m_str);
	return CWnd::OnCopyData(pWnd, pCopyDataStruct);
}

void CDLShower::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_bHover = true;
	Invalidate();
	CWnd::OnMouseHover(nFlags, point);
}

void CDLShower::OnMouseLeave()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_bTrack = true;
	m_bHover = false;
	Invalidate();
	CWnd::OnMouseLeave();
}

void CDLShower::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(m_bTrack)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(TRACKMOUSEEVENT);
		tme.dwFlags = TME_LEAVE|TME_HOVER;
		tme.dwHoverTime = HOVER_DEFAULT;
		tme.hwndTrack = this->GetSafeHwnd();
		::TrackMouseEvent(&tme);
		m_bTrack = false;
	}// if
	CWnd::OnMouseMove(nFlags, point);
}

void CDLShower::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CWnd::OnPaint()
	if(m_bHover)
	{
		CRect rect;
		this->GetWindowRect(&rect);

		CBrush brush;
		brush.CreateStockObject(NULL_BRUSH);

		CPen pen;
		pen.CreatePen(PS_SOLID,2,RGB(255,255,0));

		CPen * OldPen = dc.SelectObject(&pen);
		CBrush * OldBrush = dc.SelectObject(&brush);

		this->ScreenToClient(&rect);
		rect.InflateRect(-1,-1);
		dc.Rectangle(&rect);

		dc.SelectObject(OldPen);
		dc.SelectObject(OldBrush);
	}
}

void CDLShower::OnTransparent()
{
	// TODO: �ڴ���������������
	if(m_isTransParent)
	{
		m_base->SendMessage(WM_DESTROY,0,0);
		delete m_base;
		m_base = NULL;
		ModifyStyleEx(WS_EX_TRANSPARENT,0);
		m_menu->ModifyMenuW(IDM_TRANSPARENT,MF_STRING,IDM_TRANSPARENT,_T ("͸��"));
		m_mode &= ~(SHOWERTRANS);
	}
	else
	{
		AttachBase();
		ModifyStyleEx(0,WS_EX_TRANSPARENT);
		m_menu->ModifyMenuW(IDM_TRANSPARENT,MF_STRING,IDM_TRANSPARENT,_T ("ȡ��͸��"));
		m_mode |= (SHOWERTRANS);
	}// if
	m_isTransParent = !m_isTransParent;
}

//	�򿪳��򣬸���mode��ʼ���˵���
void CDLShower::ModifyMenuItem()
{
	DWORD style = ::GetWindowLong(m_hWnd,GWL_EXSTYLE);
	if(style & WS_EX_TOPMOST)
		m_isTopMost = true,
		m_menu->ModifyMenuW(IDM_TOPMOST,MF_STRING,IDM_TOPMOST,_T ("ȡ���ö�"));
	else
		m_menu->ModifyMenuW(IDM_TOPMOST,MF_STRING,IDM_TOPMOST,_T ("�ö�"));

	if(style & WS_EX_TRANSPARENT)
				AttachBase(),

		m_isTransParent = true,
		m_menu->ModifyMenuW(IDM_TRANSPARENT,MF_STRING,IDM_TRANSPARENT,_T ("ȡ��͸��"));
	else
		m_menu->ModifyMenuW(IDM_TRANSPARENT,MF_STRING,IDM_TRANSPARENT,_T ("͸��"));
}

void CDLShower::OnTopmost()
{
	// TODO: �ڴ���������������
	if(m_isTopMost)
	{
		this->SetWindowPos(&wndNoTopMost,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE|SWP_NOACTIVATE);
		m_menu->ModifyMenuW(IDM_TOPMOST,MF_STRING,IDM_TOPMOST,_T ("�ö�"));
		m_mode &= ~(SHOWERTRANS);
	}
	else
	{
		this->SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
		m_menu->ModifyMenuW(IDM_TOPMOST,MF_STRING,IDM_TOPMOST,_T ("ȡ���ö�"));
		m_mode |= (SHOWERTRANS);
	}// if
	m_isTopMost = !m_isTopMost;
}

void CDLShower::AttachBase()
{
	CRect rect;
	GetWindowRect(&rect);
	int width = rect.Width(),
		height = rect.Height();

	rect.left += width;
	rect.right += 10;

	m_base = new CShowerBase();
	m_base->CreateEx(WS_EX_LAYERED,L"DLSHOWER",L"BASE",WS_POPUP,
		rect,this,0);
	m_base->SetLayeredWindowAttributes(0,10,LWA_ALPHA);
	m_base->SetWindowPos(&CWnd::wndBottom,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
		m_base->ShowWindow(SW_SHOW);
}

void CDLShower::OnMove(int x, int y)
{
	CWnd::OnMove(x, y);
	// TODO: �ڴ˴������Ϣ����������
	if(m_base)
	{
		CRect rect;
		GetWindowRect(&rect);
		m_base->MoveWindow(x+rect.Width(),y,10,rect.Height(),true);
	}// if
}
