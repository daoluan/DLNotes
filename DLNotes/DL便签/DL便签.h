// DL��ǩ.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDL��ǩApp:
// �йش����ʵ�֣������ DL��ǩ.cpp
//

#define ULONG_PTR ULONG 
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")

class CDL��ǩApp : public CWinApp
{
	HANDLE m_hMutex;
public:
	CDL��ǩApp();
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CDL��ǩApp theApp;