// DL便签.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CDL便签App:
// 有关此类的实现，请参阅 DL便签.cpp
//

#define ULONG_PTR ULONG 
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")

class CDL便签App : public CWinApp
{
	HANDLE m_hMutex;
public:
	CDL便签App();
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;

// 重写
	public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CDL便签App theApp;