#include "stdafx.h"
#include "DLMgr.h"
#include "DLShower.h"
#include "COLOR.H"

CRITICAL_SECTION cs;

DWORD dwModeTable[2] = 
{
	WS_EX_TRANSPARENT,
	WS_EX_TOPMOST
};

UINT __cdecl Showing( LPVOID pParam )
{
	ShowingInfo * si = (ShowingInfo *)pParam;
	si->p->wnd.SetLayeredWindowAttributes(0,0,LWA_ALPHA);
	si->p->wnd.SetWindowPos(&(CWnd::wndNoTopMost),si->left,si->top,0,0,SWP_NOSIZE);
	for(int i=0; i<2000; i++)
		si->p->wnd.SetLayeredWindowAttributes(0,i/10,LWA_ALPHA);
	delete pParam;
	return 1;
}

UINT __cdecl ShowerShowing( LPVOID pParam )
{
	
	CRect rect;
	int cxScreen,cyScreen,left,top;
	SystemParametersInfo(SPI_GETWORKAREA,0,&rect,0);
	cxScreen = rect.Width();
	cyScreen = rect.Height();
	ShowingInfo * si = (ShowingInfo *) pParam;
	int mode = si->mode,m_count = si->m_count;
	DLNode * p = si->p;

	switch(mode)
	{
	case LEFT_VERTICAL_LAYOUT:
		left = LEFT_LAYOUT_WIDTH;
		top = (cyScreen-m_count*SHOWER_HEIGHT)/2;
		break;
	case RIGHT_VERTICAL_LAYOUT:
		left = cxScreen - SHOWER_WIDTH - RIGHT_LAYOUT_WIDTH;
		top = (cyScreen-m_count*SHOWER_HEIGHT)/2;
		break;	
	case TOP_HORIZONTAL_LAYOUT:
		top = TOP_LAYOUT_WIDTH;
		left = (cxScreen - m_count*SHOWER_WIDTH)/2;
		break;
	case BOTTOM_HORIZONTAL_LAYOUT:
		top = cyScreen - SHOWER_HEIGHT - BOTTOM_LAYOUT_WIDTH;
		left = (cxScreen - m_count*SHOWER_WIDTH)/2;
		break;
	}// switch

	DWORD ExitCode = 0;
	CWinThread * pThread =  NULL;
    
	::EnterCriticalSection(&cs);
	while(p)
	{
		ShowingInfo * si;
		si = new ShowingInfo();
		si->left = left,si->top = top;
		si->p = p;
		pThread = ::AfxBeginThread(Showing,(LPVOID)si);
		top += (mode==LEFT_VERTICAL_LAYOUT||mode==RIGHT_VERTICAL_LAYOUT)
			?SHOWER_HEIGHT:0;
		left += (mode==TOP_HORIZONTAL_LAYOUT||mode==BOTTOM_HORIZONTAL_LAYOUT)
			?SHOWER_WIDTH:0;
		p = p->next;
	}// while

	//	需要提前指定在线程完成后不销毁pThread，以方便GetExitCodeThread判断
	pThread->m_bAutoDelete = false;
	while(::GetExitCodeThread(pThread->m_hThread,&ExitCode),ExitCode==STILL_ACTIVE);
	delete pThread;

	::LeaveCriticalSection(&cs);
	return 0;
}

DLMgr::DLMgr(CWnd * parent /*= NULL*/):	//	保留parent，以后可能有用
m_count(0)
{
	m_list = new DLNode();
	::InitializeCriticalSection(&cs);
}

DLMgr::~DLMgr(void)
{
	::DeleteCriticalSection(&cs);
}

bool DLMgr::Add(DWORD mode,BOOL isIni)
{
	if(m_count >= SHOWERMAX)			//		>=5
	{
		WCHAR buf[20] = {0};
		::wsprintf(buf,L"最多%d个便签",SHOWERMAX);
		::AfxMessageBox(buf,1,0);
		return false;
	}// if

	CRect rect = FindPosition();
	DLNode * newNode = new DLNode(),* p = NULL;
	ASSERT(newNode);

	if(m_list->next)			//如果链表非空，指向第一个节点
		p = m_list->next;

	m_list->next = newNode;

	if(p)	newNode->next = p;	
	else	newNode->next = NULL;
	
	DWORD  dwMode = 0;
	int i = 0;
	while(mode)
	{
		if(mode & 1)	dwMode |= dwModeTable[i];
		mode>>=1;
		i++;
	}

	//	附加“透明”属性
	dwMode |= WS_EX_LAYERED;

	//	创建并显示窗口
	//	这里细节问题，我搞了好久才发现出错在这里，

	newNode->wnd.CreateEx(	dwMode|WS_EX_TOOLWINDOW,L"DLSHOWER",L"DLSHOWER",
		WS_POPUP,rect,NULL,0);

	//	修改窗口的属性
	newNode->wnd.SetMode(mode);
	newNode->wnd.ModifyMenuItem();

	if(!isIni)	DLMgr::ShowShower(newNode);
	/*
	newNode->wnd.SetLayeredWindowAttributes(0,192,LWA_ALPHA);
	newNode->wnd.ShowWindow(SW_SHOW);
	//	修改窗口的属性
	newNode->wnd.SetMode(mode);
	newNode->wnd.ModifyMenuItem();*/
	this->m_count ++;
	this->AdjustID();
	newNode = NULL;
	return true;
}

void DLMgr::ShowShower(DLNode * newNode)
{
	newNode->wnd.ShowWindow(SW_SHOW);
	for(int i=0; i<1920; i++)	newNode->wnd.SetLayeredWindowAttributes(0,i/10,LWA_ALPHA);
}

void  DLMgr::Delete(int id)
{
	DLNode * q;
	DLNode * p = Find(id-1);			//找到前一个节点

	q = p->next;

	if(q->next)		p->next = q->next;							//如果删除节点下一个节点有效
	else	p->next = NULL;

	q->next = NULL;
	::SendMessage(q->wnd.m_hWnd,WM_CLOSE,0,0);
	delete q;
	//调整id
	AdjustID();		
	m_count--;
}

void DLMgr::DeleteAll()
{
	DLNode * p = m_list->next;
	while(p)	::SendMessage(p->wnd.GetSafeHwnd(),WM_CLOSE,0,0),p = p->next;
}

DLNode * DLMgr::Find(int id)
{
	DLNode * p = m_list;			//指向头节点

	if(id==0)	return p;
	while(id != p->wnd.Getid() && p != NULL)	p = p->next;

	if(p)	return p;
	else	return NULL;
}

void DLMgr::AdjustID()
{
	int i = 1;
	DLNode * p = m_list->next;			//指向第一个节点
	while(p)
	{
		p->wnd.Setid(i);
		p = p->next;
		i++;
	}
}

CRect DLMgr::FindPosition()
{

	DLNode * p;
	p = m_list->next;

	int cxScreen,cyScreen;
	cxScreen = ::GetSystemMetrics(SM_CXSCREEN);
	cyScreen = ::GetSystemMetrics(SM_CYSCREEN);

	CRect rect(
		CPoint(cxScreen-RIGHT_LAYOUT_WIDTH-SHOWER_WIDTH,
		TOP_LAYOUT_WIDTH),

		CSize(SHOWER_WIDTH,SHOWER_HEIGHT));

	while(p)
	{
		p->wnd.GetWindowRect(&rect);
		//优先从左侧进行查找
		if((rect.left - SHOWER_WIDTH) > 0 && rect.top > 0 && rect.bottom < cyScreen)
		{
			rect.left -= SHOWER_WIDTH;
			rect.right -= SHOWER_WIDTH;
			return rect;
		}

		//再是右侧
		else if((rect.right + SHOWER_WIDTH) < cxScreen && rect.top > 0 && rect.bottom < cyScreen)
		{
			rect.right += SHOWER_WIDTH;
			rect.left += SHOWER_WIDTH; 
			return rect;
		}

		//再是上边
		else if((rect.top - SHOWER_HEIGHT) > 0 && rect.left > 0 && rect.right < cxScreen)
		{
			rect.bottom -= SHOWER_HEIGHT;
			rect.top -= SHOWER_HEIGHT;
			return rect;
		}

		//再是下边
		else if((rect.bottom + SHOWER_HEIGHT) < cyScreen && rect.left > 0 && rect.right < cxScreen)
		{
			rect.bottom -= SHOWER_HEIGHT;
			rect.top -= SHOWER_HEIGHT; 
			return rect;
		}// if
		p = p->next;
	}// while
	return rect;
}

void DLMgr::Layout(int mode)
{
	ShowingInfo * si = new ShowingInfo();
	si->mode = mode;
	si->p = m_list->next;
	si->m_count = m_count;
	::AfxBeginThread(ShowerShowing,(LPVOID)si);
}


struct INISHOWERSSTRUCT
{
	DLNode * p;
};

UINT __cdecl InitShowersThread( LPVOID pParam )
{
	INISHOWERSSTRUCT * iss = (INISHOWERSSTRUCT *)pParam;
	DLNode * p = iss->p;
	DLMgr::ShowShower(p);
	return 0;
}

void DLMgr::InitShowers()
{	
	int mode,i = 1;
	WCHAR note[NOTEMAXLEN] = {0};
	CString strFileName = L".//DL.ini";
	WCHAR strAppName[20] = L"DL SHOWER0";

	while(::GetPrivateProfileStringW(strAppName,L"note",L"null",note,NOTEMAXLEN,strFileName),
		::lstrcmp(note,L"null"))
	{
		mode = ::GetPrivateProfileInt(strAppName,L"mode",-1,strFileName);
		int ij = ::lstrlen(note);
		Add(mode,TRUE);
		m_list->next->wnd.SetNote(note);
		strAppName[9]++;
		ZeroMemory(note,NOTEMAXLEN);
	}// while
	
	DLNode * p = m_list->next;
	while(p)
	{
		INISHOWERSSTRUCT * iss;
		iss = new INISHOWERSSTRUCT();
		iss->p = p;
		::AfxBeginThread(InitShowersThread,(LPVOID)iss);
		p = p->next;
	}// while
}

void DLMgr::BeforeExit()
{
	DLNode * p = m_list->next;
	int i = 0;
	WCHAR note[NOTEMAXLEN] = {0},mode[5] = {0};
	CString strFileName = L".//DL.ini";
	WCHAR strAppName[20] = L"DL SHOWER0";

	while(p)
	{
		p->wnd.GetNote(note);
		::wsprintf(mode,L"%ld",p->wnd.GetMode());
		WritePrivateProfileStringW(strAppName,L"mode",mode,strFileName);
		WritePrivateProfileStringW(strAppName,L"note",note,strFileName);
		mode[0]++;strAppName[9]++;i++;	p = p->next;
	}// while

	while(i<SHOWERMAX)	//将剩余的空的便签也写入，方便下次打开程序
	{
		WritePrivateProfileStringW(strAppName,L"mode",L"0",strFileName);
		WritePrivateProfileStringW(strAppName,L"note",L"null",strFileName);
		mode[0]++;
		strAppName[9]++;
		i++;
	}// while
}
