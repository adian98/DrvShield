#include "stdafx.h"
#include "LoadDriver.h"

typedef struct _LSA_UNICODE_STRING
{
	USHORT Length;
	USHORT MaximumLength;
	PVOID Buffer;
} LSA_UNICODE_STRING, *PLSA_UNICODE_STRING;

typedef LSA_UNICODE_STRING UNICODE_STRING, *PUNICODE_STRING;

// ����ntdll��ʹ�õĺ���
typedef DWORD (CALLBACK* RTLANSISTRINGTOUNICODESTRING)(PVOID, PVOID,DWORD);
RTLANSISTRINGTOUNICODESTRING RtlAnsiStringToUnicodeString;
typedef DWORD (CALLBACK* RTLFREEUNICODESTRING)(PVOID);
RTLFREEUNICODESTRING RtlFreeUnicodeString;
typedef DWORD (CALLBACK* ZWLOADDRIVER)(PVOID);
ZWLOADDRIVER ZwLoadDriver;

static bool LoadDriverImpl(PCHAR szDrvName, PCHAR szDrvPath)
{
	//�޸�ע���������������
	char szSubKey[200], szDrvFullPath[256];
	LSA_UNICODE_STRING buf1;
	LSA_UNICODE_STRING buf2;
	int iBuffLen;
	HKEY hkResult;
	char Data[4];
	DWORD dwOK;
	iBuffLen = sprintf(szSubKey, "System\\CurrentControlSet\\Services\\%s", szDrvName);
	szSubKey[iBuffLen] = 0;
	dwOK = RegCreateKey(HKEY_LOCAL_MACHINE, szSubKey, &hkResult);
	if(dwOK != ERROR_SUCCESS)
	{	
		return false;
	}	
	Data[0] = 1;
	Data[1] = 0;
	Data[2] = 0;
	Data[3] = 0;
	dwOK = RegSetValueEx(hkResult, "Type", 0, 4, (const unsigned char *)Data, 4);
	dwOK = RegSetValueEx(hkResult, "ErrorControl", 0, 4, (const unsigned char *)Data, 4);
	dwOK = RegSetValueEx(hkResult, "Start", 0, 4, (const unsigned char *)Data, 4);
	GetFullPathName(szDrvPath, 256, szDrvFullPath, NULL);
	iBuffLen = sprintf(szSubKey, "\\??\\%s", szDrvFullPath);
	szSubKey[iBuffLen] = 0;
	dwOK = RegSetValueEx(hkResult, "ImagePath", 0, 1, (const unsigned char *)szSubKey, iBuffLen);
	RegCloseKey(hkResult); 
	iBuffLen = sprintf(szSubKey, "\\Registry\\Machine\\System\\CurrentControlSet\\Services\\%s", szDrvName);
	szSubKey[iBuffLen] = 0;
	buf2.Buffer = (PVOID)szSubKey;
	buf2.Length = iBuffLen;
	RtlAnsiStringToUnicodeString(&buf1, &buf2, 1);
	//������������
	dwOK = ZwLoadDriver(&buf1);
	RtlFreeUnicodeString(&buf1);
	iBuffLen = sprintf(szSubKey, "%s%s\\Enum", "System\\CurrentControlSet\\Services\\", szDrvName);
	szSubKey[iBuffLen] = 0;
	//ɾ��ע�����
	RegDeleteKey(HKEY_LOCAL_MACHINE, szSubKey);
	iBuffLen=sprintf(szSubKey, "%s%s\\Security", "System\\CurrentControlSet\\Services\\", szDrvName);
	szSubKey[iBuffLen] = 0;
	RegDeleteKey(HKEY_LOCAL_MACHINE, szSubKey);
	iBuffLen = sprintf(szSubKey, "%s%s", "System\\CurrentControlSet\\Services\\", szDrvName);
	szSubKey[iBuffLen] = 0;
	RegDeleteKey(HKEY_LOCAL_MACHINE, szSubKey);
	//iBuffLen = sprintf(szSubKey, "\\\\.\\%s", szDrvName);
	//szSubKey[iBuffLen] = 0;
	DeleteFile(szDrvFullPath);
	return true;
}

bool LoadDriver(PCHAR szDrvName, PCHAR szDrvPath)
{
	HMODULE hNtdll = NULL;
	hNtdll = LoadLibrary("ntdll.dll"); 
	//��ntdll.dll���ȡ����
	if (!hNtdll)
	{
		return false;
	}
	RtlAnsiStringToUnicodeString = (RTLANSISTRINGTOUNICODESTRING)GetProcAddress(hNtdll, "RtlAnsiStringToUnicodeString");
	RtlFreeUnicodeString = (RTLFREEUNICODESTRING)GetProcAddress(hNtdll, "RtlFreeUnicodeString");
	ZwLoadDriver = (ZWLOADDRIVER)GetProcAddress(hNtdll, "ZwLoadDriver");

	return LoadDriverImpl(szDrvName, szDrvPath);
}
