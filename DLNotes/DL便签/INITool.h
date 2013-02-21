#pragma once

class INITool
{
private:
	CString strFileName;
	int mode;
	WCHAR note[NOTEMAXLEN];
public:
	INITool(void);
	//void GetKeyString(LPCWSTR lpAppName,lpKeyName,
	~INITool(void);
};
