// DL��ǩ.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "DL��ǩ.h"
#include "DL��ǩDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDL��ǩApp

BEGIN_MESSAGE_MAP(CDL��ǩApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CDL��ǩApp ����

CDL��ǩApp::CDL��ǩApp():m_hMutex(NULL)
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CDL��ǩApp ����

CDL��ǩApp theApp;

// CDL��ǩApp ��ʼ��

BOOL CDL��ǩApp::InitInstance()
{
	//	���Ƴ���ʵ��
	m_hMutex = ::CreateMutex(NULL,TRUE,L"DL��ǩ");
	if(ERROR_ALREADY_EXISTS == GetLastError ())
		return false;

	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	CDLShower::RegisterWndClass();
	CDL��ǩDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

int CDL��ǩApp::ExitInstance()
{
	// TODO: �ڴ����ר�ô����/����û���
	 GdiplusShutdown(gdiplusToken);
	 ASSERT(m_hMutex);
	::ReleaseMutex(m_hMutex);
	return CWinApp::ExitInstance();
}
