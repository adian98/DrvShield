// stdafx.cpp : source file that includes just the standard includes
//	DrvShield.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

BOOL ExpandResource(int nId, PCHAR lpResType, PCHAR lpFileName)
{
	PCHAR Name = MAKEINTRESOURCE(nId);
	HRSRC res = ::FindResource(NULL, Name, lpResType);
	if (res == NULL)
	{
		return FALSE;
	}
	HGLOBAL gl = ::LoadResource(NULL,res);
	if (gl == NULL)
	{
		return FALSE;
	}
	LPVOID lp = ::LockResource(gl);					//����ָ����Դ�ڴ�ĵ�ַ��ָ�롣
	if (lp == NULL)
	{
		return FALSE;	
	}
	HANDLE hFile = CreateFile(lpFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;	
	}
	DWORD dwSizeRes = SizeofResource(NULL, res);	//�õ���Դ�ļ��Ĵ�С
	if (dwSizeRes == 0)
	{
		return FALSE;
	}
	DWORD Out = 0;
	if(!WriteFile(hFile, lp, dwSizeRes, &Out, NULL))
	{
		return FALSE;	
	}
	CloseHandle(hFile);								//�رվ��
	FreeResource(gl);								//�ͷ��ڴ�
	return TRUE;
}
