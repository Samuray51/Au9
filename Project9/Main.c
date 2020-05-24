#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
int main() 
{
	SYSTEMTIME lt;
	char buf1[260];
	char buf2[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD size = sizeof(buf1);
	GetUserName(buf1, &size);
	printf("Username: %s\n", buf1);
	size = sizeof(buf2);
	GetComputerName(buf2, &size);
	printf("Computeername: %s\n", buf2);
	GetLocalTime(&lt);
	printf("Time: %d:%d\n", lt.wHour, lt.wMinute);
	printf("Date: %d.%d.%d\n", lt.wDay, lt.wMonth, lt.wYear);
	getchar();
	return 0;
}