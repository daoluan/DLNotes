// DL便签Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DL便签.h"
#include "DL便签Dlg.h"
#include "XPButton.h"
#include "COLOR.h"
#include "CTrayIconDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CDL便签Dlg 对话框
CWnd * globalMainWnd = NULL;
CDL便签Dlg::CDL便签Dlg(CWnd* pParent /*=NULL*/)
: CDialog(CDL便签Dlg::IDD, pParent),m_text(L""),
m_texting(NULL),TrayIcon(IDR_MAINFRAME)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_image = Image::FromFile(L"res\\NCPAINT.bmp");
	m_edit = new CDLEdit();
	m_dlmgr = new DLMgr(this);
	m_bExbanded = false;
}

void CDL便签Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDL便签Dlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_NCPAINT()
	ON_WM_NCACTIVATE()
	ON_WM_NCHITTEST()
	ON_WM_LBUTTONUP()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_TEST+107,OnBnClickedTest)
	ON_BN_CLICKED(IDC_TEST+108,OnBnClickedAdd)
	ON_BN_CLICKED(IDC_TEST+100,OnBnLayoutUp)
	ON_BN_CLICKED(IDC_TEST+101,OnBnLayoutDown)
	ON_BN_CLICKED(IDC_TEST+102,OnBnLayoutLeft)
	ON_BN_CLICKED(IDC_TEST+106,OnBnLayoutRight)
	ON_MESSAGE(WM_MY_TRAY_NOTIFICATION,OnTrayNotification)
	ON_MESSAGE(WM_ADD_SHOWER, OnAddShower)
	ON_MESSAGE(WM_DEL_SHOWER,OnDelShower)
	ON_WM_COPYDATA()
	ON_COMMAND(IDM_CLOSEEX, &CDL便签Dlg::OnCloseex)
	ON_COMMAND(IDM_ABOUT, &CDL便签Dlg::OnAbout)
END_MESSAGE_MAP()

// CDL便签Dlg 消息处理程序

BOOL CDL便签Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	ShowWindow(SW_SHOW);	
	ControlInit();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDL便签Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{		
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDL便签Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDL便签Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	ReleaseCapture(); 
	this->SendMessage(WM_SYSCOMMAND,0xF012,0);
	CDialog::OnLButtonDown(nFlags, point);
}

int CDL便签Dlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO:  在此添加您专用的创建代码
	//初始化各个控件
	TrayIcon.SetNotificationWnd(this,WM_MY_TRAY_NOTIFICATION);
	TrayIcon.SetIcon(IDR_TRAYICON);

	m_dlmgr->InitShowers();
	globalMainWnd = this;
	return 0;
}

void CDL便签Dlg::ControlInit()
{
	CRect rect;
	GetClientRect(&rect);

	int nClientWidth = rect.Width(),
		nClientHeight = rect.Height();

	CRect rectCtl;
	rectCtl.left = nClientWidth - 30;
	rectCtl.top = nClientHeight - 33;
	rectCtl.right = nClientWidth - 7;
	rectCtl.bottom = nClientHeight - 33;

	m_btnAdd.CreateExEx(L"测试按钮",BS_PUSHBUTTON |WS_CHILD | WS_VISIBLE ,
		rectCtl,
		this,IDC_TEST+108,
		L".//res//ADDBG.png",
		L".//res//ADDBG.png",
		L"./res//ADDBG.png");

	rectCtl.top = 5;
	rectCtl.bottom = 28;

	m_xpTest.CreateExEx(L"测试按钮",BS_PUSHBUTTON |WS_CHILD | WS_VISIBLE ,
		rectCtl,
		this,IDC_TEST+107,
		L".//res//BG.png",
		L".//res//BG.png",
		L"./res//BG.png");

	rectCtl.left = 8;
	rectCtl.top = 20;
	rectCtl.right = nClientWidth - 40;
	rectCtl.bottom = nClientHeight-8;
	m_edit->CreateEx(WS_EX_RIGHTSCROLLBAR,
		WS_CHILD|WS_VISIBLE|ES_MULTILINE|WS_VSCROLL|ES_WANTRETURN, 
		rectCtl,
		this,
		IDC_TEST+1);

	int nExbandWidth = (150 - EXBANDGAP)/3;
	int nExbandHeight = (nClientHeight - EXBANDGAP)/3;

	rectCtl.left = nClientWidth + EXBANDGAP + nExbandWidth;
	rectCtl.top = EXBANDGAP;
	rectCtl.right = rectCtl.left + nExbandWidth;
	rectCtl.bottom = nExbandHeight + EXBANDGAP;
	m_btnLayoutUp.CreateExEx(L"上",BS_PUSHBUTTON |WS_CHILD | WS_VISIBLE ,
		rectCtl,
		this,IDC_TEST+100,
		L".//res//LayoutButton//UpNormal.png",
		L".//res//LayoutButton//HoverBG.png",
		L".//res//LayoutButton//UpClick.png");

	rectCtl.top = nClientHeight - EXBANDGAP - nExbandHeight;
	rectCtl.bottom = nExbandHeight - EXBANDGAP;
	m_btnLayoutDown.CreateExEx(L"下",BS_PUSHBUTTON |WS_CHILD | WS_VISIBLE ,
		rectCtl,
		this,IDC_TEST+101,
		L".//res//LayoutButton//DownNormal.png",
		L".//res//LayoutButton//HoverBG.png",
		L".//res//LayoutButton//DownClick.png");

	rectCtl.left = nClientWidth + EXBANDGAP;
	rectCtl.top = EXBANDGAP + nExbandHeight;
	rectCtl.right = rectCtl.left + nExbandWidth;
	rectCtl.bottom = rectCtl.top + nExbandHeight;
	m_btnLayoutLeft.CreateExEx(L"左",BS_PUSHBUTTON |WS_CHILD | WS_VISIBLE ,
		rectCtl,
		this,IDC_TEST+102,
		L".//res//LayoutButton//LeftNormal.png",
		L".//res//LayoutButton//HoverBG.png",
		L".//res//LayoutButton//LeftClick.png");

	rectCtl.left = nClientWidth + EXBANDGAP + 2*nExbandWidth;
	rectCtl.right = rectCtl.left + nExbandWidth;
	m_btnLayoutRight.CreateExEx(L"右",BS_PUSHBUTTON |WS_CHILD | WS_VISIBLE ,
		rectCtl,
		this,IDC_TEST+106,
		L".//res//LayoutButton//RightNormal.png",
		L".//res//LayoutButton//HoverBG.png",
		L".//res//LayoutButton//RightClick.png");

	long lMask = m_edit->GetEventMask();
	lMask |= ENM_CHANGE;
	m_edit->SetEventMask(lMask);

	//以下是设计滚动条
	//::InitializeFlatSB(m_edit->m_hWnd);
	//m_edit->EnableScrollBar(SB_HORZ,FALSE);
	//m_edit->SetBackgroundColor(FALSE,RGB(255,255,255));


	//以下改变RichEdit内背景和字体颜色
	CHARFORMAT cf;
	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwMask = CFM_COLOR | CFM_FACE |CFM_ITALIC | CFM_SIZE ;   
	cf.dwEffects = CFE_UNDERLINE ;	 //CFE_BOLD(粗体)
	cf.yHeight = 12*20;
	cf.crTextColor = RGB(0,0,0);
	::lstrcpy(cf.szFaceName, L"宋体"); //Times New Roman(Terminal和CMD一样)
	cf.bCharSet = 0;
	cf.bPitchAndFamily = 0;
	m_edit->SetDefaultCharFormat(cf);
	m_edit->SetBackgroundColor(0,GetSysColor((COLOR_WINDOW)));

	CTime time;	
	CString s;
	time = CTime::GetCurrentTime();
	s = time.Format("%H:%M");
	rectCtl.left = 10;
	rectCtl.top = 2;
	rect.right = 70;
	rect.bottom = 20;
	m_timer.Create(s,WS_VISIBLE|WS_CHILD|SS_LEFT,rectCtl,this,IDC_TEST+2);
	m_timer.SetTimer(IDC_TEST+1000,1000,NULL);

	CFont * f; 
	f = new CFont;
	f->CreatePointFont(105,L"微软雅黑");
	GetDlgItem(IDC_TEST+2)->SetFont(f);

}

void CDL便签Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CString s;
	CTime time;

	switch(nIDEvent)
	{
	case IDC_TEST+3:
		OnNcPaint();
		KillTimer(IDC_TEST+3);
		break;
	}
	CDialog::OnTimer(nIDEvent);
}

void CDL便签Dlg::OnNcPaint()
{
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnNcPaint()
	//Default();
	CDC * pDC;
	pDC = this->GetWindowDC();

	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_NCPAINT);
	CBitmap * oldbitmap;
	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);
	oldbitmap = MemDC.SelectObject(&bitmap);

	CRect rect;
	this->GetWindowRect(rect);
	pDC->StretchBlt(0,0,
		rect.Width(),GetSystemMetrics(SM_CYCAPTION)+ GetSystemMetrics(SM_CYFRAME),
		&MemDC,
		10,10,200,GetSystemMetrics(SM_CYCAPTION)+ GetSystemMetrics(SM_CYFRAME),
		SRCCOPY);

	CRect rectClient;
	this->GetClientRect(rectClient);

	m_rcLEdge.left = 0;
	m_rcLEdge.right = GetSystemMetrics(SM_CYFRAME);
	m_rcLEdge.top = GetSystemMetrics(SM_CYCAPTION)+ GetSystemMetrics(SM_CYFRAME);
	m_rcLEdge.bottom = rect.Height();

	m_rcREdge.left = rect.Width() - GetSystemMetrics(SM_CYFRAME);
	m_rcREdge.right = rect.Width();
	m_rcREdge.top = m_rcLEdge.top;
	m_rcREdge.bottom = m_rcLEdge.bottom;

	m_rcBEdge.left = GetSystemMetrics(SM_CYFRAME);
	m_rcBEdge.right = rect.Width() - GetSystemMetrics(SM_CYFRAME);
	m_rcBEdge.top = rect.Height() - GetSystemMetrics(SM_CYFRAME);
	m_rcBEdge.bottom = rect.Height();

	pDC->StretchBlt(m_rcLEdge.left,m_rcLEdge.top,
		m_rcLEdge.Width(),m_rcLEdge.Height(),
		&MemDC,
		10-GetSystemMetrics(SM_CYFRAME),
		10+GetSystemMetrics(SM_CYCAPTION)+GetSystemMetrics(SM_CYFRAME),
		m_rcLEdge.Width(),
		100,
		SRCCOPY);

	pDC->StretchBlt(m_rcREdge.left,m_rcREdge.top,
		m_rcREdge.Width(),m_rcREdge.Height(),
		&MemDC,
		10+GetSystemMetrics(SM_CYFRAME)+200,
		10+GetSystemMetrics(SM_CYCAPTION)+GetSystemMetrics(SM_CYFRAME),
		m_rcREdge.Width(),
		100,
		SRCCOPY);

	pDC->StretchBlt(m_rcBEdge.left,m_rcBEdge.top,
		m_rcBEdge.Width(),m_rcBEdge.Height(),
		&MemDC,
		10,
		10+GetSystemMetrics(SM_CYCAPTION)+GetSystemMetrics(SM_CYFRAME)+rectClient.Height(),
		200+GetSystemMetrics(SM_CYFRAME)*2,
		m_rcBEdge.Height(),
		SRCCOPY);

	CRect closeRect;
	closeRect.left = rect.right - rect.left - 20;
	closeRect.top = GetSystemMetrics(SM_CYFRAME);
	closeRect.right = rect.right - rect.left - 5;
	closeRect.bottom = GetSystemMetrics( SM_CYSIZE ) ;

	/*
	pDC->DrawFrameControl(closeRect,
	DFC_CAPTION,
	DFCS_CAPTIONCLOSE );
	*/
	this->ReleaseDC(pDC);
	MemDC.SelectObject(oldbitmap);
	m_rcClose = closeRect;
}

BOOL CDL便签Dlg::OnNcActivate(BOOL bActive)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	OnNcPaint(); 
	return true;
}

void CDL便签Dlg::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// Coords are relative to screen
	CPoint pt=point;
	// Convert for relative to client area
	ScreenToClient(&pt);
	// Adjust for client area
	pt.y += GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYFRAME);
	pt.x += 5;

	// Now test for button
	DWORD hitTest = HitTest(pt);

	switch(hitTest)
	{
	case DHT_CLOSE:
		{
			CWindowDC dc(this);

			/*
			DrawFrameControl(dc.m_hDC,
			m_rcClose,
			DFC_CAPTION,
			DFCS_CAPTIONCLOSE | DFCS_PUSHED);
			*/

			dc.FillSolidRect(m_rcClose,RGB(255,255,0));
			m_LastHit = hitTest;
			m_ButtonDown = hitTest;
			// Set capture for mouse events
			SetCapture();
		}
		break;
	default:
		Default(); 
		break;
	}
}

DWORD CDL便签Dlg::HitTest(CPoint pt)
{
	CRect rect=m_rcClose;
	if(rect.PtInRect(pt))
		return (DWORD) DHT_CLOSE;
	else
		return (DWORD) DHT_CAPTION;
	return 0;
}

LRESULT CDL便签Dlg::OnNcHitTest(CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	/*if(this != GetCapture())
	return CDialog::OnNcHitTest(point); // The default handler*/

	// Coords are relative to screen
	CPoint pt=point;
	// Convert for relative to client area
	ScreenToClient(&pt);
	// Adjust for client area
	pt.y += GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYFRAME);
	pt.x += 5;
	// Now test for button
	DWORD hitTest = HitTest(pt);

	if(hitTest == m_LastHit)
		return CDialog::OnNcHitTest(point);

	m_LastHit = hitTest;

	UINT pushed = 0;
	if(m_ButtonDown == hitTest)
		pushed = DFCS_PUSHED;

	CWindowDC dc(this);
	switch(hitTest)
	{
	case DHT_CLOSE:
		{
			/*
			DrawFrameControl(dc.m_hDC,
			m_rcClose,
			DFC_CAPTION,
			DFCS_CAPTIONCLOSE | pushed);
			*/
			KillTimer(IDC_TEST+3);
			dc.FillSolidRect(m_rcClose,RGB(255,255,0));
			SetTimer(IDC_TEST+3,1000,NULL);
		}
		break;

	default:
		//OnNcPaint();

		/*
		DrawFrameControl(dc.m_hDC,
		m_rcClose,
		DFC_CAPTION,
		DFCS_CAPTIONCLOSE);
		*/
		break;
	}
	// return value	
	return hitTest;
}

void CDL便签Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(this != GetCapture())
		return;

	// Coords are relative to window now
	CPoint pt=point;
	// Adjust for client area
	point.y += GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYFRAME);
	point.x += 5;

	// Now test for button
	DWORD hitTest = HitTest(point);

	CWindowDC dc(this);
	switch(m_ButtonDown) // Release the pressed button
	{
	case DHT_CLOSE:
		dc.FillSolidRect(m_rcClose,RGB(255,255,0));
		/*
		DrawFrameControl(dc.m_hDC,
		m_rcClose,
		DFC_CAPTION,
		DFCS_CAPTIONCLOSE);
		*/
		break;
	default:
		Default();
		break;
	}

	switch(hitTest)		// Process command if released at on a button
	{
	case 1:
		SendMessage(WM_CLOSE, 0,0);
		break;
	default:
		break;
	}
	m_ButtonDown = 0;
	// Release mouse capture
	ReleaseCapture();
}

HBRUSH CDL便签Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性
	int CtlID = pWnd->GetDlgCtrlID();
	switch(CtlID)
	{
	case IDC_TEST+2:
		//	设置背景透明，以和主窗口融合
		pDC->SetBkMode(TRANSPARENT);
		return HBRUSH(GetStockObject(NULL_BRUSH));
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

BOOL CDL便签Dlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//CRect rect;
	//GetWindowRect(&rect);
	//Graphics graphics(pDC->m_hDC);
	//CDC MemDC;
	//CBitmap bitmap;
	//MemDC.CreateCompatibleDC(pDC);
	//bitmap.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	//MemDC.SelectObject(&bitmap);

	//Graphics MemGraphics(MemDC.GetSafeHdc());

	//if(!m_image)
	//	m_image = Image::FromFile(L"res\\NCPAINT.bmp");
	//MemGraphics.DrawImage(m_image,0,0,rect.Width(),rect.Height());

	//CDialog::OnEraseBkgnd(pDC);
	CRect rect;
	GetClientRect(&rect);

	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	MemDC.SelectObject(bitmap);

	Graphics graphics(MemDC.m_hDC);
	m_image = Image::FromFile(L"res\\NCPAINT.png");
	graphics.DrawImage(m_image,10,10,rect.Width(),rect.Height());

	/*pDC->StretchBlt(//客户区和标题栏有点绘图错误，问题在这里
	0,-10,rect.Width(),rect.Height()+10,
	&MemDC,10,10+GetSystemMetrics(SM_CYCAPTION)+ GetSystemMetrics(SM_CYFRAME),
	rect.Width()-10,rect.Height()-10,SRCCOPY);*/

	pDC->StretchBlt(//客户区和标题栏有点绘图错误，问题在这里
		0,0,rect.Width(),rect.Height()+10,
		&MemDC,
		10+GetSystemMetrics(SM_CYFRAME),
		10+GetSystemMetrics(SM_CYCAPTION)+ GetSystemMetrics(SM_CYFRAME),
		200-GetSystemMetrics(SM_CYFRAME)*2,
		rect.Height()-10-GetSystemMetrics(SM_CYCAPTION)+ GetSystemMetrics(SM_CYFRAME),
		SRCCOPY);
	return 1;
}

void CDL便签Dlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	this->ShowWindow(SW_HIDE);
	m_texting = NULL;
	m_edit->SetWindowTextW(L"");
	//CDialog::OnClose();
}

LRESULT CDL便签Dlg::OnAddShower(WPARAM wParam, LPARAM lParam)
{
	m_dlmgr->Add();
	return 1;
}

LRESULT CDL便签Dlg::OnDelShower(WPARAM wParam, LPARAM lParam)
{
	m_dlmgr->Delete((int)wParam);
	return 1;
}

BOOL CDL便签Dlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rect;
	m_texting = pWnd;
	m_text.SetString((WCHAR *)pCopyDataStruct->lpData,pCopyDataStruct->cbData);
	m_edit->GetWindowRect(&rect);
	this->ScreenToClient(&rect);
	m_edit->SetWindowTextW(L"");
	this->InvalidateRect(&rect,true);
	m_edit->SetWindowTextW(m_text);
	return CDialog::OnCopyData(pWnd, pCopyDataStruct);
}


void CDL便签Dlg::OnBnClickedTest()
{
	CRect rct1;
	this->GetWindowRect(&rct1);

	this->SetWindowPos(&wndNoTopMost,
		0,0,
		!m_bExbanded?rct1.Width()+150:rct1.Width()-150,
		rct1.Height(),
		SWP_NOMOVE);
	m_bExbanded = !m_bExbanded;

	CRect rct2;
	this->GetWindowRect(&rct2);
	InvalidateRect(CRect(rct1.Width()-10,0,rct2.Width(),rct2.Height()));
}
void CDL便签Dlg::OnBnClickedAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	CString  str;
	COPYDATASTRUCT cds;
	cds.cbData = NOTEMAXLEN + 5;

	m_edit->GetWindowTextW(str);
	//如果正在编辑的窗口无效，那就要新增便签窗口
	if(!m_texting)
	{
		if(str.GetLength()==0)
			str = L"空的便签";
		cds.lpData = str.GetBuffer();
		if (!(m_dlmgr->Add(0,FALSE)))	{m_edit->SetWindowTextW(L"");	return;}
		DLNode * shower = m_dlmgr->Find(1);			//因为是用头插法来出入新的便签，所以找到第一个节点就好了
		shower->wnd.SendMessage(WM_COPYDATA,(WPARAM)m_hWnd,(LPARAM)&cds);
	}
	else	
	{
		cds.lpData = str.GetBuffer();
		if(!m_texting->GetSafeHwnd())
		{
			m_dlmgr->Add(0,FALSE);
			DLNode * shower = m_dlmgr->Find(1);
			m_texting = &shower->wnd;
		}// if
			m_texting->SendMessage(WM_COPYDATA,(WPARAM)m_hWnd,(LPARAM)&cds);
	}// if

	m_edit->SetWindowTextW(L"");
	m_text = L"";
	m_texting = NULL;
	m_text.ReleaseBuffer();
}
void CDL便签Dlg::OnBnLayoutUp()
{
	this->m_dlmgr->Layout(TOP_HORIZONTAL_LAYOUT);
}

void CDL便签Dlg::OnBnLayoutDown()
{
	this->m_dlmgr->Layout(BOTTOM_HORIZONTAL_LAYOUT);
}

void CDL便签Dlg::OnBnLayoutLeft()
{
	this->m_dlmgr->Layout(LEFT_VERTICAL_LAYOUT);
}

void CDL便签Dlg::OnBnLayoutRight()
{
	this->m_dlmgr->Layout(RIGHT_VERTICAL_LAYOUT);
}

LRESULT CDL便签Dlg::OnTrayNotification(WPARAM uID,LPARAM lEvent)
{
	return TrayIcon.OnTrayNotification(uID,lEvent);
}

void CDL便签Dlg::OnCloseex()
{
	// TODO: 在此添加命令处理程序代码
	m_dlmgr->BeforeExit();
	this->m_dlmgr->DeleteAll();
	CDialog::DestroyWindow();
}

void CDL便签Dlg::OnAbout()
{
	// TODO: 在此添加命令处理程序代码
	CString args;
	HINSTANCE result;
	args.Format(_T("url.dll,FileProtocolHandler %s"),L"http://daoluanxiaozi.cnblogs.com/");
	result = ShellExecute(NULL, _T("open"), _T("rundll32.exe"), args, NULL, SW_SHOW);
}

BOOL CDL便签Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg -> message == WM_KEYDOWN)
	{
		if(pMsg -> wParam == VK_ESCAPE)
			return ShowWindow(SW_HIDE);
		if(pMsg -> wParam == VK_RETURN)
			return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}
