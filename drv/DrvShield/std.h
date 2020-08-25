#ifndef __STD_H__
#define __STD_H__

#ifdef  __cplusplus
extern "C" 
{
#endif

#include <ntddk.h>
#include <ntimage.h>
#include <stdio.h>

NTSYSAPI
	NTSTATUS
	NTAPI
	ZwCreateEvent (
	OUT PHANDLE EventHandle,
	IN ACCESS_MASK DesiredAccess,
	IN POBJECT_ATTRIBUTES ObjectAttributes OPTIONAL,
	IN EVENT_TYPE EventType,
	IN BOOLEAN InitialState
	);

NTSYSAPI
	NTSTATUS
	NTAPI
	ZwWaitForSingleObject(
	IN HANDLE Handle,
	IN BOOLEAN Alertable,
	IN PLARGE_INTEGER Timeout OPTIONAL
	);

NTSYSAPI
	PIMAGE_NT_HEADERS
	NTAPI
	RtlImageNtHeader(
	IN PVOID ImageBase
	);

int __cdecl _snwprintf(wchar_t *, size_t, const wchar_t *, ...);
int __cdecl _snprintf(char *, size_t, const char *, ...);

#ifdef  __cplusplus
}
#endif

#include "common.h"

#define DELAY_ONE_MICROSECOND				(-10)
#define DELAY_ONE_MILLISECOND				(DELAY_ONE_MICROSECOND*1000)
#define DELAY_ONE_SECOND					(DELAY_ONE_MILLISECOND*1000)

#define MAX_PROCESS_PROTECT_COUNT 256

typedef struct _PROCESS_PROTECT
{
	ULONG Count;
	ULONG ProcessID[MAX_PROCESS_PROTECT_COUNT];
} PROCESS_PROTECT, *PPROCESS_PROTECT;

typedef struct _DEVICE_EXTENSION
{
	KSPIN_LOCK       SpinLock;
	PDRIVER_OBJECT   DriverObject;
	PKEVENT          obDriverEntryEvent;
	HANDLE           hDriverEntryEvent;
	PKEVENT          obDriverProcessedEvent;
	HANDLE           hDriverProcessedEvent;
	PKEVENT          obDriverClearedEvent;
	HANDLE           hDriverClearedEvent;
	PPHYSICAL_MEMORY_RANGE PhysicalMemoryRange;
	PROCESS_PROTECT	 ProcessProtectList;		//Ҫ�����Ľ���ID�б�
	PDRV_ANTI_DATA   DrvAntiData;				//������ص�����������
	BOOLEAN          DeviceOpen;				//�豸�Ƿ��
	BOOLEAN          StartSysMon;				//�Ƿ�ʼ�������
	BOOLEAN          StartHook;					//�Ƿ�����HOOK��SSDT����
	PVOID            ImageFileBuffer;			//���Ҫ���ݵ������ļ�������
	ULONG            ImageFileSize;				//�����ļ�����
	WCHAR            WorkSavePath[MAX_PATH];	//����Ŀ¼
	CHAR             CaptureDriverPathName[MAX_PATH]; //����Ӧ�ó����ѯ�ı����ص���������ȫ·����
} DEVICE_EXTENSION, *PDEVICE_EXTENSION;

#ifdef  DECLARE_UNICODE_STRING
#undef  DECLARE_UNICODE_STRING
#endif
#define DECLARE_UNICODE_STRING(_variablename, _string) \
	WCHAR          _variablename ## _buffer[] = _string; \
	UNICODE_STRING _variablename = { sizeof(_string) - sizeof(WCHAR), sizeof(_string), (PWSTR)_variablename ## _buffer };

EXTERN_C PDEVICE_OBJECT GlobalDeviceObject;

#endif
