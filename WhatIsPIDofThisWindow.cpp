// WhatIsPIDofThisWindow.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <tlhelp32.h>

using namespace std;

#define SAVE_WND_SIZE 500
#define DELAY 100

int save_flag = 1;

UINT FindProcessName(DWORD pid, WCHAR* out, int len)
{
	DWORD dwPID = -1;
	HANDLE hSnapShot = INVALID_HANDLE_VALUE;
	PROCESSENTRY32 pe;

	pe.dwSize = sizeof(PROCESSENTRY32);
	hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);

	Process32First(hSnapShot, &pe);
	do
	{
		if (pe.th32ProcessID == pid)
		{
			wcscpy_s(out, len, pe.szExeFile);
			break;
		}
	} while (Process32Next(hSnapShot, &pe));

	CloseHandle(hSnapShot);
	return wcslen(out);
}
int main()
{
	HWND saveWnd[SAVE_WND_SIZE];
	int SAVE_WND_LEN = 0;

	while (1)
	{
		int i;
		HWND hWnd = GetForegroundWindow();
		for (i = 0; i < SAVE_WND_LEN; i++)
		{
			if (saveWnd[i] == hWnd)
				break;
		}
		if (i >= SAVE_WND_LEN) // HWND 리스트에서 발견되지 않았으면
		{
			DWORD pid;
			GetWindowThreadProcessId(hWnd, &pid);

			WCHAR process_name[100] = L"";
			FindProcessName(pid, process_name, 100);
			wcout << L"This is " << process_name << L" pid : " << pid << endl;
			if (SAVE_WND_LEN < SAVE_WND_SIZE)
				saveWnd[SAVE_WND_LEN++] = hWnd; // HWND 리스트에 추가
		}

	}
}