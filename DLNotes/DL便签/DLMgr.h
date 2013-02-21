#pragma once
#include "DLShower.h"

struct DLNode
{
	CDLShower wnd;
	DLNode * next;
	DLNode():next(NULL){}
};

struct ShowingInfo
{
	int left,top;
	DLNode * p;
	int mode;
	int m_count;
};


class DLMgr
{
public:
	DLMgr(CWnd * parent = NULL);
	~DLMgr(void);

	bool Add(DWORD mode = NULL,BOOL isIni = false);
	void Delete(int id);
	void DeleteAll();
	DLNode * Find(int id);
	void AdjustID(); 
	CRect FindPosition();
	void Layout(int mode);

	//	程序打开和关闭之后
	void InitShowers();
	void BeforeExit();
	static void ShowShower(DLNode * newNode);

private:
	int m_count;
	DLNode * m_list;			//头接点
};	