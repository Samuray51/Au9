#define WIN32_LEAN_AND_MEAN 
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winsock2.h> 
#include <ws2tcpip.h>
#include<SetupAPI.h>
#include <locale.h>

#pragma comment(lib, "ws2_32.lib")
#pragma comment (lib, "setupapi.lib")

int main() 
{
	setlocale(LC_ALL, "Russian");
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
	printf("Time: %.2d:%.2d\n", lt.wHour, lt.wMinute);
	printf("Date: %.2d.%.2d.%d\n", lt.wDay, lt.wMonth, lt.wYear);




	WSADATA wsaData;
	int iResult, i = 0;
	struct hostent *host_entry;
	char *host_name = NULL;
	struct in_addr addr;
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) 
	{
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}
	host_entry = gethostbyname(host_name);
	while (host_entry->h_addr_list[i] != 0) 
	{
		addr.s_addr = *(u_long *)host_entry->h_addr_list[i++];
		printf("IP: %s\n", inet_ntoa(addr));
	}


	HANDLE Handle;
	SP_DEVINFO_DATA DeviceInfoData;
	ZeroMemory(&DeviceInfoData, sizeof(SP_DEVINFO_DATA));
	DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
	DWORD DeviceIndex = 0;
	BYTE PropertyBuffer[1024] = { 0 };
	BYTE PropertyBuffer_cmp[1024] = { 0 };
	
	Handle = SetupDiGetClassDevsA(NULL, NULL, NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);
	printf("All devices:\n");
	while (SetupDiEnumDeviceInfo(Handle, DeviceIndex, &DeviceInfoData))
	{
		strcpy_s(PropertyBuffer_cmp, 1024, PropertyBuffer);
		SetupDiGetDeviceRegistryPropertyA(Handle, &DeviceInfoData, SPDRP_FRIENDLYNAME, NULL, PropertyBuffer, 1024, NULL);
		if (strcmp(PropertyBuffer, PropertyBuffer_cmp))
		{
			printf("%d. %s \n", DeviceIndex, PropertyBuffer);
		}
		DeviceIndex++;
	}
	getchar();
	return 0;
}