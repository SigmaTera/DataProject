// CurlExLauncher.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int _tmain(int argc, LPTSTR argv[])
{
	CString strParam;
	CString strCurlPath;
	CString strFilePath;

	int nStep = 100000;
	int n = 2000000;//4783821;
	int nProcesses = 10;

	strFilePath = TEXT("I:\\DataFile");

	if (argc > 4)
	{
		strFilePath = argv[1];
		n = _ttoi(argv[2]);
		nStep = _ttoi(argv[3]);
		nProcesses = _ttoi(argv[4]);
	}
	
	

	GetModuleFileName(NULL, strCurlPath.GetBuffer(MAX_PATH), MAX_PATH);
	strCurlPath.ReleaseBuffer();
	PathRemoveFileSpec(strCurlPath.GetBuffer(MAX_PATH));
	strCurlPath.ReleaseBuffer();

	strCurlPath += TEXT("\\CurlEx.exe");

	for (int i = 0; i < 10; i++)
	{
		
		strParam.Format(TEXT("%s %d %d +"),strFilePath,n,nStep);
		n += nStep;
		ShellExecute(NULL, TEXT("Open"), strCurlPath, strParam, NULL, SW_SHOW);
	}
	return 0;
}

