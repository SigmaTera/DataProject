// CurlExLauncher.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int main()
{
	CString strParam;
	int nStep = 40000;
	int n = 2040000;//4783821;
	for (int i = 0; i < 1; i++)
	{
		
		strParam.Format(TEXT("D:\\DataFile %d %d +"),n,nStep);
		n += nStep;
		ShellExecute(NULL, TEXT("Open"), TEXT("CurlEx.exe"), strParam, NULL, SW_SHOW);
	}
	return 0;
}

