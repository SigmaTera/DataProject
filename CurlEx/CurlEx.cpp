// CurlEx.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <atlstr.h>
#include <iostream>

using namespace std;

BOOL IsFileExists(LPCTSTR lpFilePath);

int _tmain(int argc, LPTSTR argv[])
{
	CString strUrl;
	CString strCurlPath;
	CString strFilePath;
	CString strOpMode;
	CString strFileName;

	DWORD dwCode = 0;
	int nStart = 0;
	int nCount = 0;

	TCHAR szCurlPath[MAX_PATH] = { 0 };
	TCHAR szParam[256] = { 0 };

	SHELLEXECUTEINFO sShellExeInfo = { sizeof(SHELLEXECUTEINFO) };

	sShellExeInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	sShellExeInfo.hwnd = NULL;
	sShellExeInfo.lpVerb = NULL;
	sShellExeInfo.lpDirectory = NULL;
	sShellExeInfo.nShow = SW_HIDE;
	sShellExeInfo.hInstApp = NULL;
	sShellExeInfo.lpFile = szCurlPath;
	sShellExeInfo.lpParameters = szParam;

	strCurlPath = TEXT("C:\\Windows\\curl.exe");

	GetModuleFileName(NULL, strCurlPath.GetBuffer(MAX_PATH), MAX_PATH);
	strCurlPath.ReleaseBuffer();
	PathRemoveFileSpec(strCurlPath.GetBuffer(MAX_PATH));
	strCurlPath.ReleaseBuffer();

	strCurlPath += TEXT("\\curl.exe");

	if (argc < 4)
		return -1;
	strFilePath = argv[1];
	nStart = _ttoi(argv[2]);
	nCount = _ttoi(argv[3]);
	strOpMode = argv[4];

	lstrcpyn(szCurlPath, strCurlPath, MAX_PATH);

	if (strOpMode == TEXT("+"))
	{
		for (int i = nStart; i < nStart + nCount; i++)
		{
			strFileName.Format(TEXT("%s\\%07d.html"),strFilePath,i);
			if (IsFileExists(strFileName))
			{
				cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
				cout << i << " 跳过";
				continue;
			}

			HANDLE hFile = CreateFile(strFileName, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
			CloseHandle(hFile);

			strUrl.Format(TEXT("http://quotes.money.163.com/f10/ggmx_000000_%07d.html"), i);
			wsprintf(szParam, TEXT("-o %s\\%07d.html %s"), (LPCTSTR)strFilePath, i, (LPCTSTR)strUrl);
			ShellExecuteEx(&sShellExeInfo);
			WaitForSingleObject(sShellExeInfo.hProcess, INFINITE);
			GetExitCodeProcess(sShellExeInfo.hProcess,&dwCode);
			//Sleep(500);
			cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
			cout << i << " " << ((dwCode == 0) ? "成功" : "失败");
			if (dwCode != 0)
			{
				DeleteFile(strFileName);
			}

		}
	}
	else
	{
		for (int i = nStart; i > nStart - nCount; i--)
		{
			strFileName.Format(TEXT("%s\\%07d.html"), strFilePath, i);
			if (IsFileExists(strFileName))
			{
				cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
				cout << i << " 跳过";
				continue;
			}
			
			HANDLE hFile = CreateFile(strFileName, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
			CloseHandle(hFile);

			strUrl.Format(TEXT("http://quotes.money.163.com/f10/ggmx_000000_%07d.html"), i);
			wsprintf(szParam, TEXT("-o F:\\Data\\%07d.html %s"), i, (LPCTSTR)strUrl);
			ShellExecuteEx(&sShellExeInfo);
			WaitForSingleObject(sShellExeInfo.hProcess, INFINITE);
			GetExitCodeProcess(sShellExeInfo.hProcess, &dwCode);
			//Sleep(500);
			cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
			cout << i << " " << ((dwCode == 0) ? "成功" : "失败");
			if (dwCode != 0)
			{
				DeleteFile(strFileName);
			}
		}
	}
	
	
	return 0;
}



BOOL IsFileExists(LPCTSTR lpFilePath)
{
	HANDLE hFile = CreateFile(lpFilePath,
		GENERIC_READ,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (INVALID_HANDLE_VALUE == hFile)
		return FALSE;
	CloseHandle(hFile);
	return TRUE;
}