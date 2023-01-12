#include "plugin.h"

#ifdef _UNICODE
#error "USE ASCII CODE PAGE"
#endif

using namespace Script::Module;
using namespace Script::Symbol;
using namespace Script::Debug;
using namespace Script::Register;

// make sure only one window exists
bool bIsMainWindowShow = false;


/*
 * Add API Breakpoint here.
 * You can change display text language here if you want.
 * Dll name are not necessary so far cause we are using "bp" rather than SetBPX()
 * If the function name appears in multiple dlls, the behavior depends on the bp instruction
 */
ApiGroup Groups[TAB_COUNT] =
{
	{
		"���öϵ�",
		{
			ApiBreakPointInfo("Kernel32.dll","FindFirstFileA","�����ļ�"),
			ApiBreakPointInfo("Kernel32.dll","ExitProcess","�����˳�"),
			ApiBreakPointInfo("Kernel32.dll","GetStartupInfoA","��ȡ������Ϣ"),
			ApiBreakPointInfo("Kernel32.dll","GetFileSize","��ȡ�ļ���С"),
			ApiBreakPointInfo("Kernel32.dll","VirtualProtect","Vmp�ѿ�"),
			ApiBreakPointInfo("User32.dll","ExitWindowsEx","�ػ��ϵ�"),
			ApiBreakPointInfo("Kernel32.dll","CreateFileA","��У��"),
			ApiBreakPointInfo("Kernel32.dll","GetVersion","�������ѿ�"),
			ApiBreakPointInfo("Ws2_32.dll","send","���ͷ��"),
			ApiBreakPointInfo("Ws2_32.dll","WSASend","���ͷ��"),
			ApiBreakPointInfo("Ws2_32.dll","recv","���շ��"),
			ApiBreakPointInfo("ntdll.dll","RtlAdjustPrivilege","�����Կ��ٹػ�"),
			ApiBreakPointInfo("Shell32.dll","SHFormatDrive","����API"),
			ApiBreakPointInfo("Kernel32.dll","RemoveDirectoryA","ɾ��Ŀ¼"),
			ApiBreakPointInfo("Kernel32.dll","DeleteFileA","ɾ���ļ�"),
			ApiBreakPointInfo("","GetLastError","���ش�����"),
		}
	},
	{
		"�Ի���",
		{
			ApiBreakPointInfo("","MessageBoxA","���Ի���"),
			ApiBreakPointInfo("","MessageBoxW",""),
			ApiBreakPointInfo("","MessageBoxExA",""),
			ApiBreakPointInfo("","MessageBoxExW",""),
			ApiBreakPointInfo("","MessageBoxIndirectA",""),
			ApiBreakPointInfo("","MessageBoxIndirectW",""),
			ApiBreakPointInfo("","GetWindowTextA","ȡ�ؼ��ı�"),
			ApiBreakPointInfo("","GetWindowTextW",""),
			ApiBreakPointInfo("","SetWindowTextA","���ÿؼ��ı�"),
			ApiBreakPointInfo("","SetWindowTextW",""),
			ApiBreakPointInfo("","GetDlgItemTextA","ȡ�ؼ��ı�"),
			ApiBreakPointInfo("","GetDlgItemTextW",""),
			ApiBreakPointInfo("","SetDlgItemTextA","���ÿؼ��ı�"),
			ApiBreakPointInfo("","SetDlgItemTextW",""),
			ApiBreakPointInfo("","GetDlgItemInt","ȡ�ؼ�������"),
			ApiBreakPointInfo("","SetDlgItemInt","���ÿؼ�������"),
			ApiBreakPointInfo("","SendMessageA","����Ϣ"),
			ApiBreakPointInfo("","SendMessageW","����Ϣ"),
			ApiBreakPointInfo("","SendDlgItemMessage","����Ϣ"),
			ApiBreakPointInfo("","IsDialogMessageA",""),
			ApiBreakPointInfo("","IsDialogMessageW",""),
			ApiBreakPointInfo("","DispatchMessageA","��Ϣ�ɷ�"),
			ApiBreakPointInfo("","DispatchMessageW",""),
			ApiBreakPointInfo("","CallWindowProcA","���ô��ڹ���"),
			ApiBreakPointInfo("","CallWindowProcW",""),
			ApiBreakPointInfo("","DefWindowProcA","Ĭ����Ϣ����"),
			ApiBreakPointInfo("","DefWindowProcW",""),
			ApiBreakPointInfo("","MessageBeep","ϵͳ������"),
			ApiBreakPointInfo("","DrawTextA","�ı���浽������"),
			ApiBreakPointInfo("","DrawTextW",""),
			ApiBreakPointInfo("","DrawTextExA",""),
			ApiBreakPointInfo("","DrawTextExW",""),
			ApiBreakPointInfo("","FindWindowA","��ȡ���ھ��"),
			ApiBreakPointInfo("","FindWindowW",""),
			ApiBreakPointInfo("","GetClipboardData","��ȡ����������"),
			ApiBreakPointInfo("","CoInitialize","��ʼ��COM��"),
			ApiBreakPointInfo("","CoCreateInstance","����COM����"),
			ApiBreakPointInfo("","LoadIconA","����ͼ����Դ"),
			ApiBreakPointInfo("","LoadIconW",""),
			ApiBreakPointInfo("","SetWindowLongA","���ô�������"),
			ApiBreakPointInfo("","SetWindowLongW",""),
			ApiBreakPointInfo("","SetWindowLongPtrA",""),
			ApiBreakPointInfo("","SetWindowLongPtrW",""),
			ApiBreakPointInfo("","ShowWindow","��ʾ����"),
			ApiBreakPointInfo("","UpdateWindow","���´���"),
			ApiBreakPointInfo("","CreateWindowExA","��������"),
			ApiBreakPointInfo("","CreateWindowExW",""),
			ApiBreakPointInfo("","CreateWindowA",""),
			ApiBreakPointInfo("","CreateWindowW",""),
			ApiBreakPointInfo("","DestroyWindow","���ٴ���"),
			ApiBreakPointInfo("","DialogBoxA","ģ̬�Ի���"),
			ApiBreakPointInfo("","DialogBoxW",""),
			ApiBreakPointInfo("","DialogBoxParamA",""),
			ApiBreakPointInfo("","DialogBoxParamW",""),
			ApiBreakPointInfo("","DialogBoxIndirectA",""),
			ApiBreakPointInfo("","DialogBoxIndirectW",""),
			ApiBreakPointInfo("","DialogBoxIndirectParamA",""),
			ApiBreakPointInfo("","DialogBoxIndirectParamW",""),
			ApiBreakPointInfo("","EndDialog","���ģ̬�Ի���"),
			ApiBreakPointInfo("","TranslateMessage","��Ϣ����"),
			ApiBreakPointInfo("","GetMessageA","ȡ��Ϣ����"),
			ApiBreakPointInfo("","GetMessageW",""),
			ApiBreakPointInfo("","PeekMessageA","����Ϣ����"),
			ApiBreakPointInfo("","PeekMessageW",""),
			ApiBreakPointInfo("","SetMenu","���˵�"),
			ApiBreakPointInfo("","DestroyMenu","ɾ���˵�"),
			ApiBreakPointInfo("","DeleteMenu","ɾ���˵���"),
			ApiBreakPointInfo("","EnableMenuItem","�˵����ޱ��"),
			ApiBreakPointInfo("","EnableWindow","��ֹ�����������"),
		}
	},
	{
		"�ļ�����",
		{
			ApiBreakPointInfo("","CreateFileA","��������ļ�"),
			ApiBreakPointInfo("","CreateFileW",""),
			ApiBreakPointInfo("","OpenFile","���ļ�"),
			ApiBreakPointInfo("","ReadFile","���ļ�"),
			ApiBreakPointInfo("","WriteFile","д�ļ�"),
			ApiBreakPointInfo("","GetFileSize","ȡ�ļ���С"),
			ApiBreakPointInfo("","FindFirstFileA","�����ļ�"),
			ApiBreakPointInfo("","FindFirstFileW",""),
			ApiBreakPointInfo("","GetModuleFileNameA","��ģ��·��"),
			ApiBreakPointInfo("","GetModuleFileNameW",""),
			ApiBreakPointInfo("","OpenFileMappingA","���ļ�ӳ�����"),
			ApiBreakPointInfo("","OpenFileMappingW",""),
			ApiBreakPointInfo("","LoadLibraryA","����DLL"),
			ApiBreakPointInfo("","LoadLibraryW",""),
			ApiBreakPointInfo("","LoadLibraryExA",""),
			ApiBreakPointInfo("","LoadLibraryExW",""),
			ApiBreakPointInfo("","GetModuleHandleA","����ģ��"),
			ApiBreakPointInfo("","GetModuleHandleW",""),
			ApiBreakPointInfo("","GetModuleHandleExA",""),
			ApiBreakPointInfo("","GetModuleHandleExW",""),			
			ApiBreakPointInfo("","CreateFileMappingA","�����ļ�����"),
			ApiBreakPointInfo("","CreateFileMappingW",""),
			ApiBreakPointInfo("","CopyFileA","�����ļ�"),
			ApiBreakPointInfo("","CopyFileW",""),
			ApiBreakPointInfo("","CopyFileExA",""),
			ApiBreakPointInfo("","CopyFileExW",""),
			ApiBreakPointInfo("","SetFilePointer","�����ļ���дλ��"),
			ApiBreakPointInfo("","MoveFileA","�ƶ��ļ�"),
			ApiBreakPointInfo("","MoveFileW",""),
			ApiBreakPointInfo("","MoveFileExA",""),
			ApiBreakPointInfo("","MoveFileExW",""),
			ApiBreakPointInfo("","DeleteFileA",""),
			ApiBreakPointInfo("","DeleteFileW","ɾ���ļ�"),
			ApiBreakPointInfo("","LoadCursorFromFileA","�����ļ����"),
			ApiBreakPointInfo("","LoadCursorFromFileW",""),
			ApiBreakPointInfo("","GetPrivateProfileStringA","INI������֤����"),
			ApiBreakPointInfo("","GetPrivateProfileStringW",""),
			ApiBreakPointInfo("","GetPrivateProfileIntA",""),
			ApiBreakPointInfo("","GetPrivateProfileIntW",""),
			ApiBreakPointInfo("","GetPrivateProfileStringA","ȡ�ַ���"),
			ApiBreakPointInfo("","GetPrivateProfileStringW",""),
			ApiBreakPointInfo("","WritePrivateProfileStringA","�����ַ���"),
			ApiBreakPointInfo("","WritePrivateProfileStringW",""),
		}
	},
	{
		"ע���",
		{
			ApiBreakPointInfo("","RegOpenKeyA","��ע�����"),
			ApiBreakPointInfo("","RegOpenKeyW",""),
			ApiBreakPointInfo("","RegOpenKeyExA","������֤����"),
			ApiBreakPointInfo("","RegOpenKeyExW",""),
			ApiBreakPointInfo("","RegCreateKeyExA",""),
			ApiBreakPointInfo("","RegCreateKeyExW",""),
			ApiBreakPointInfo("","RegQueryValueA","ȡע����ֵ"),
			ApiBreakPointInfo("","RegQueryValueW",""),
			ApiBreakPointInfo("","RegQueryValueExA",""),
			ApiBreakPointInfo("","RegQueryValueExW",""),
			ApiBreakPointInfo("","RegCreateKeyA","��������"),
			ApiBreakPointInfo("","RegCreateKeyW",""),
			ApiBreakPointInfo("","RegCloseKey","�ر�ע���"),
			ApiBreakPointInfo("","RegDeleteKeyA","ɾ����ֵ"),
			ApiBreakPointInfo("","RegDeleteKeyW",""),
			ApiBreakPointInfo("","RegEnumKeyExA","ö������"),
			ApiBreakPointInfo("","RegEnumKeyExW",""),
			ApiBreakPointInfo("","RegSetValueA","����Ĭ��ֵ"),
			ApiBreakPointInfo("","RegSetValueW",""),
			ApiBreakPointInfo("","RegSetValueExA","����ָ�����ֵ"),
			ApiBreakPointInfo("","RegSetValueExW",""),
		}
	},
	{
		"ʱ�䴦��",
		{
			ApiBreakPointInfo("","SetSystemTime","����ϵͳʱ��"),
			ApiBreakPointInfo("","TimerProc","�ص�����"),//what is this
			ApiBreakPointInfo("","SetLocalTime","���ñ���ʱ��"),
			ApiBreakPointInfo("","GetLocalTime","��ȡ����ʱ��"),
			ApiBreakPointInfo("","GetSystemTime","��ȡϵͳʱ��"),
			ApiBreakPointInfo("","GetCurrentTime","��ȡϵͳʱ��"),
			ApiBreakPointInfo("","GetFileTime","��ȡ�ļ�ʱ��"),
			ApiBreakPointInfo("","GetTickCount","ϵͳ�������������ĺ�����"),
			ApiBreakPointInfo("","CompareFileTime","�Ƚ��ļ�ʱ��"),
			ApiBreakPointInfo("","SetTimer","������ʱ��"),
			ApiBreakPointInfo("","KillTimer","�Ƴ���ʱ��"),
			ApiBreakPointInfo("","timeSetEvent","��ý�嶨ʱ��"),
		}
	},
	{
		"���̺���",
		{
			ApiBreakPointInfo("","CreateThread","�����߳�"),
			ApiBreakPointInfo("","CreateRemoteThread","����Զ���߳�"),
			ApiBreakPointInfo("","GetModuleHandleA","��ģ���ַ"),
			ApiBreakPointInfo("","GetModuleHandleW",""),
			ApiBreakPointInfo("","OpenMutexA","�򿪻�����"),
			ApiBreakPointInfo("","OpenMutexW",""),
			ApiBreakPointInfo("","WriteProcessMemory","д�ڴ�"),
			ApiBreakPointInfo("","ZwWriteVirtualMemory",""),
			ApiBreakPointInfo("","ReadProcessMemory","���ڴ�"),
			ApiBreakPointInfo("","ZwReadVirtualMemory",""),
			ApiBreakPointInfo("","CreateProcessA","��������"),
			ApiBreakPointInfo("","CreateProcessW",""),
			ApiBreakPointInfo("","OpenProcess","�򿪽���"),
			ApiBreakPointInfo("","ExitProcess","��������"),
			ApiBreakPointInfo("","ExitThread","������ǰ�߳�"),
			ApiBreakPointInfo("","TerminateProcess","��ֹ����"),
			ApiBreakPointInfo("","TerminateThread","��ֹ�߳�"),
			ApiBreakPointInfo("","CreateToolhelp32Snapshot","���̿���"),
			ApiBreakPointInfo("","Process32First","ȡ���̾��"),
			ApiBreakPointInfo("","Process32FirstW",""),
			ApiBreakPointInfo("","Process32Next",""),
			ApiBreakPointInfo("","Process32NextW",""),
			ApiBreakPointInfo("","Module32Next","ȡģ����"),
			ApiBreakPointInfo("","Module32NextW",""),
			ApiBreakPointInfo("","Module32First",""),
			ApiBreakPointInfo("","Module32FirstW",""),
			ApiBreakPointInfo("","Heap32ListFirst","ȡ�Ѿ��"),
			ApiBreakPointInfo("","Heap32ListNext","ȡ�Ѿ��"),
			ApiBreakPointInfo("","GetProcessHeap","ȡ�Ѿ��"),
			ApiBreakPointInfo("","Heap32First","ȡ���̶������Ϣ"),
			ApiBreakPointInfo("","Heap32Next","ȡ���̶������Ϣ"),
			ApiBreakPointInfo("","PostQuitMessage","��ֹ�߳�"),
			ApiBreakPointInfo("","IsDebuggerPresent","��������"),
			ApiBreakPointInfo("","OpenProcessToken","��ȡ���̷������ƾ��"),
			ApiBreakPointInfo("","OpenThreadToken",""),
			ApiBreakPointInfo("","ZwQueryInformationProcess",""),
		}
	},
	{
		"����",
		{
			ApiBreakPointInfo("","send",""),
			ApiBreakPointInfo("","sendto",""),
			ApiBreakPointInfo("","WSASend",""),
			ApiBreakPointInfo("","WSASendTo",""),
			ApiBreakPointInfo("","recv",""),
			ApiBreakPointInfo("","inet_addr",""),
			ApiBreakPointInfo("","connect",""),
			ApiBreakPointInfo("","UrlDownloadToFileA",""),
			ApiBreakPointInfo("","UrlDownloadToFileW",""),
		}
	},
	{
		"�ڴ�",
		{
			ApiBreakPointInfo("","FindWindow","ȡ���ھ��"),
			ApiBreakPointInfo("","GetWindowThreadProcessId","��ȡ���ڽ���ID"),
			ApiBreakPointInfo("","OpenProcess","�򿪽���"),
			ApiBreakPointInfo("","VirtualAllocEx","�����ڴ�"),
			ApiBreakPointInfo("","WriteProcessMemory","д�ڴ�"),
			ApiBreakPointInfo("","ReadProcessMemory","���ڴ�"),
			ApiBreakPointInfo("","CreateRemoteThread","����Զ���߳�"),
			ApiBreakPointInfo("","CreateMutexA","����������"),
			ApiBreakPointInfo("","CreateMutexW",""),
			ApiBreakPointInfo("","GetModuleHandleA","��ģ���ַ"),
			ApiBreakPointInfo("","GetModuleHandleW",""),
			ApiBreakPointInfo("","GetProcAddress","�麯����ַ"),
			ApiBreakPointInfo("","VirtualAlloc","�����ڴ�"),
			ApiBreakPointInfo("","HeapAlloc",""),
			ApiBreakPointInfo("","VirtualFree","�ͷ��ڴ�"),
			ApiBreakPointInfo("","HeapFree",""),
			ApiBreakPointInfo("","LoadLibraryA","����DLL"),
			ApiBreakPointInfo("","LoadLibraryW",""),
			ApiBreakPointInfo("","GetVersion","��ȡϵͳ�汾"),
			ApiBreakPointInfo("","ZwAllocateVirtualMemory",""),
			ApiBreakPointInfo("","ZwWriteVirtualMemory",""),
			ApiBreakPointInfo("","ZwReadVirtualMemory",""),
		}
	},
	{
		"����",
		{
			ApiBreakPointInfo("","GetDiskFreeSpaceA","��ȡ������Ϣ"),
			ApiBreakPointInfo("","GetDiskFreeSpaceExA",""),
			ApiBreakPointInfo("","GetDiskFreeSpaceExW",""),
			ApiBreakPointInfo("","GetDriveTypeA","�жϴ�������������"),
			ApiBreakPointInfo("","GetDriveTypeW",""),
			ApiBreakPointInfo("","GetLogicalDrives","ȡ��������ĸ"),
			ApiBreakPointInfo("","GetLogicalDriveStringsA","ȡ������·��"),
			ApiBreakPointInfo("","GetLogicalDriveStringsW",""),
		}
	},
	{
		"��������",
		{
			ApiBreakPointInfo("","CreateFileA",""),
			ApiBreakPointInfo("","CreateFileW",""),
			ApiBreakPointInfo("","LoadLibraryA",""),
			ApiBreakPointInfo("","LoadLibraryW",""),
			ApiBreakPointInfo("","LoadLibraryExA",""),
			ApiBreakPointInfo("","LoadLibraryExW",""),
			ApiBreakPointInfo("","CreateThread",""),
			ApiBreakPointInfo("","CreateProcessA",""),
			ApiBreakPointInfo("","CreateProcessW",""),
			ApiBreakPointInfo("","CreateRemoteThread",""),
			ApiBreakPointInfo("","WriteProcessMemory",""),
			ApiBreakPointInfo("","ReadProcessMemory",""),
			ApiBreakPointInfo("","OpenMutexA",""),
			ApiBreakPointInfo("","OpenMutexW",""),
			ApiBreakPointInfo("","CreateToolhelp32SnapShot",""),
			ApiBreakPointInfo("","Heap32ListFirst",""),
			ApiBreakPointInfo("","Heap32ListNext",""),
			ApiBreakPointInfo("","Heap32First",""),
			ApiBreakPointInfo("","Heap32Next",""),
			ApiBreakPointInfo("","Module32First",""),
			ApiBreakPointInfo("","Module32Next",""),
			ApiBreakPointInfo("","Module32FirstW",""),
			ApiBreakPointInfo("","Module32NextW",""),
			ApiBreakPointInfo("","Process32First",""),
			ApiBreakPointInfo("","Process32FirstW",""),
			ApiBreakPointInfo("","Process32Next",""),
			ApiBreakPointInfo("","Process32NextW",""),
			ApiBreakPointInfo("","PostQuitMessage",""),
			ApiBreakPointInfo("","Toolhelp32ReadProcessMemory",""),
			ApiBreakPointInfo("","ZwQueryInformationProcess",""),
			ApiBreakPointInfo("","SetTimer",""),
			ApiBreakPointInfo("","GetTempPathA",""),
			ApiBreakPointInfo("","GetTempPathW",""),
			ApiBreakPointInfo("","ReadFile",""),
			ApiBreakPointInfo("","WriteFile",""),
			ApiBreakPointInfo("","ShellExecuteA",""),
			ApiBreakPointInfo("","ShellExecuteW",""),
			ApiBreakPointInfo("","WinExec",""),
			ApiBreakPointInfo("","DeleteFileA",""),
			ApiBreakPointInfo("","DeleteFileW",""),
			ApiBreakPointInfo("","UrlDownloadToFileA",""),
			ApiBreakPointInfo("","UrlDownloadToFileW",""),
			ApiBreakPointInfo("","GetDesktopWindow",""),
		}
	},
	{
		"VB",
		{
			ApiBreakPointInfo("","FindResourceA","VBУ��"),
			ApiBreakPointInfo("","CreateFileA","VBУ��"),
			ApiBreakPointInfo("","GetVolumeInformation","���̾�"),
			ApiBreakPointInfo("","MultiByteToWideChar","AתU�ַ���"),
			ApiBreakPointInfo("","WideCharToMultiByte","UתA�ַ���"),
			ApiBreakPointInfo("","GetFileSize","��ȡ�ļ���С"),
			ApiBreakPointInfo("","VarCyFromStr","�ַ���ת����"),
			ApiBreakPointInfo("","arBstrFromI2","����ת�ַ���"),
			ApiBreakPointInfo("","rtcFileLen","VB��У��"),
			ApiBreakPointInfo("","rtcFileLenth",""),
			ApiBreakPointInfo("","rtcMsgBox","��ʾ�Ի���"),
			ApiBreakPointInfo("","rtcInputBox","�����"),
			ApiBreakPointInfo("","GetMemStr",""),
			ApiBreakPointInfo("","rtcR8ValFromBstr",""),
			ApiBreakPointInfo("","rtcGetPresendDate",""),
			ApiBreakPointInfo("","rtcBeep",""),
			ApiBreakPointInfo("","rtcTrimBstr","�ַ���ȥ���ո�"),
			ApiBreakPointInfo("","rtcMidCharVar","�ַ�����ȡ�ַ�"),
			ApiBreakPointInfo("","rtcLeftCharVar","�ַ������ȡ�ַ�"),
			ApiBreakPointInfo("","rtcRightCharVar","�ַ����ұ�ȡ�ַ�"),
			ApiBreakPointInfo("","StrConv","ת���ַ���"),
			ApiBreakPointInfo("","rtcT8ValFromBstr","�ַ���ת������"),
			ApiBreakPointInfo("","__vbaI2Str","�ַ�ת1�ֽ���ֵ"),
			ApiBreakPointInfo("","__vbaI4Str","�ַ�ת4�ֽ���ֵ"),
			ApiBreakPointInfo("","__vbar4Str","�ַ�ת4������"),
			ApiBreakPointInfo("","__vbar8Str","�ַ�ת8������"),
			ApiBreakPointInfo("","__vbavaradd","����ֵ���"),
			ApiBreakPointInfo("","__vbavarsub","����ֵ���"),
			ApiBreakPointInfo("","__vbavarmul","����ֵ���"),
			ApiBreakPointInfo("","__vbavaridiv","����ֵ���"),
			ApiBreakPointInfo("","__vbavarxor","����ֵ���"),
			ApiBreakPointInfo("","__vbavarcat","����ֵ����"),
			ApiBreakPointInfo("","__vbaStrCat","�ַ�������"),
			ApiBreakPointInfo("","__vbaVarCat","�����ִ�"),
			ApiBreakPointInfo("","__vbaStrCmp","�ַ����Ƚ�"),
			ApiBreakPointInfo("","__vbaStrComp","�ַ����Ƚ�"),
			ApiBreakPointInfo("","__vbaVarTstEq","�Ƚϱ���"),
			ApiBreakPointInfo("","__vbaFreeStr",""),
			ApiBreakPointInfo("","__vbaStrCopy",""),
			ApiBreakPointInfo("","__vbaLenBstr",""),
			ApiBreakPointInfo("","__vbavarfornext","ѭ���ṹ"),
			ApiBreakPointInfo("","__vbafreeobj","�ͷŶ���"),
		}
	},
	{
		"VC/MFC",
		{
			ApiBreakPointInfo("","lstrcmpA","�ַ����Ƚ�"),
			ApiBreakPointInfo("","DefWindowProcA","����Ĭ�ϴ��ڹ���"),
			ApiBreakPointInfo("","DefWindowProcW",""),
			ApiBreakPointInfo("","RegisterClassA","ע�ᴰ����"),
			ApiBreakPointInfo("","RegisterClassW",""),
			ApiBreakPointInfo("","RegisterClassExA",""),
			ApiBreakPointInfo("","RegisterClassExW",""),
			ApiBreakPointInfo("","FindResourceA","������Դ"),
			ApiBreakPointInfo("","FindResourceW",""),
			ApiBreakPointInfo("","LoadResource","������Դ"),
			ApiBreakPointInfo("","SetHandleCount","ȡ������ַ"),
			ApiBreakPointInfo("","IsWindowEnabled","�ɷ��������"),
		}
	},
	{
		"���ܹ�/��ɽ��",
		{
			ApiBreakPointInfo("","CreateThread","Ѱ��OEP"),
			ApiBreakPointInfo("","GetModuleHandleA","ħ����ת"),
			ApiBreakPointInfo("","OpenMutexA","1ת���������θ���"),
			ApiBreakPointInfo("","GetSystemTime","����KEY"),
			ApiBreakPointInfo("","VirtualProtect","2EAXΪ401000����"),
			ApiBreakPointInfo("","CreateFileMappingA","����"),
			ApiBreakPointInfo("","LoadLibraryA","����DLL"),
			ApiBreakPointInfo("","LoadLibraryW",""),
			ApiBreakPointInfo("","LoadLibraryExA",""),
			ApiBreakPointInfo("","LoadLibraryExW",""),
			ApiBreakPointInfo("","RefreshDeviceList","��˼3"),
			ApiBreakPointInfo("","DeviceIoControl","�����豸"),
			ApiBreakPointInfo("","Prestochangoselector",""),
			ApiBreakPointInfo("","FreeEnvironmentStringsA","�ͷŻ����ִ���"),
			ApiBreakPointInfo("","GetLogicalDriveStringsA","ȡ�б�"),
			ApiBreakPointInfo("","GetLogicalDrives","ȡ�������б�"),
			ApiBreakPointInfo("","GetDriveTypeA","�ж�����������"),
			ApiBreakPointInfo("","CreateFileA","��������"),
			ApiBreakPointInfo("","FindFirstFileA","�����ļ�"),
		}
	},
	{
		"����",
		{
		}
	},
	{
		"����2",
		{
		}
	},
};

const UINT IDC_CHECKS[CHECK_COUNT] =
{
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
	__COUNTER__ + 1500,
};

HWND hChecks[CHECK_COUNT];

HWND hTabControl;

HINSTANCE hInst;
HWND hMain;
WNDPROC DefTabControlProc;

int CurTab = 0;


DWORD WINAPI MsgLoopThread(LPVOID);
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

void DefBreakPointCallback() {}

//Initialize your plugin data here.
bool pluginInit(PLUG_INITSTRUCT* initStruct)
{
	//SetAPIBreakPoint("kernelbase.dll", "VirtualAlloc", UE_BREAKPOINT, UE_APIEND, DefBreakPointCallback);

	return true; //Return false to cancel loading the plugin.
}

//Deinitialize your plugin data here.
void pluginStop()
{
}

//Do GUI/Menu related things here.
void pluginSetup()
{
	_plugin_menuaddentry(hMenu, MENU_MAINWINDOW_POPUP, "Set Api Breakpoint");

	// automaticly show main window, for test
	//if (!bIsMainWindowShow)
	//{
	//	CloseHandle(CreateThread(0, 0, MsgLoopThread, 0, 0, 0));
	//	bIsMainWindowShow = true;
	//}
}

// doing msg loop like WinMain
DWORD WINAPI MsgLoopThread(LPVOID)
{
	MSG msg;
	WNDCLASSA wc;
	HWND hwnd;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = g_hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);

	wc.lpszMenuName = NULL;
	wc.lpszClassName = PLUGIN_NAME;

	RegisterClassA(&wc);

	hwnd = CreateWindowA(
		PLUGIN_NAME,
		"Standard Window",
		WS_OVERLAPPEDWINDOW,
		100,
		100,
		MAINWINDOW_WIDTH,
		MAINWINDOW_HEIGHT,
		NULL,
		NULL,
		g_hInstance,
		NULL
	);

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	bIsMainWindowShow = false;

	return (int)msg.wParam;
}

VOID CenterDialog(HWND hDlg)
{
	HWND hwndOwner = NULL;
	RECT rcOwner, rcDlg, rc;
	// Get the owner window and dialog box rectangles. 			
	if ((hwndOwner = GetParent(hDlg)) == NULL)
	{
		hwndOwner = GetDesktopWindow();
	}
	GetWindowRect(hwndOwner, &rcOwner);
	GetWindowRect(hDlg, &rcDlg);
	CopyRect(&rc, &rcOwner);

	// Offset the owner and dialog box rectangles so that right and bottom 
	// values represent the width and height, and then offset the owner again 
	// to discard space taken up by the dialog box. 

	OffsetRect(&rcDlg, -rcDlg.left, -rcDlg.top);
	OffsetRect(&rc, -rc.left, -rc.top);
	OffsetRect(&rc, -rcDlg.right, -rcDlg.bottom);

	// The new position is the sum of half the remaining space and the owner's 
	// original position. 

	SetWindowPos(hDlg,
		HWND_TOP,
		rcOwner.left + (rc.right / 2),
		rcOwner.top + (rc.bottom / 2),
		0, 0,          // Ignores size arguments. 
		SWP_NOSIZE);
}

// called when tab changed, update checkbox check(uncheck) and show(hide) state
void UpdateCheckBoxs()
{
	CurTab = TabCtrl_GetCurSel(hTabControl);
	size_t len = Groups[CurTab].apiList.size();
	for (size_t i = 0; i < CHECK_COUNT; i++)
	{
		if (i < len)
		{
			SetWindowTextA(hChecks[i], std::string(Groups[CurTab].apiList[i].apiName + " " + Groups[CurTab].apiList[i].description).c_str());
			if (Groups[CurTab].apiList[i].bWantToSetBp)
			{
				CheckDlgButton(hMain, IDC_CHECKS[i], BST_CHECKED);
			}
			else
			{
				CheckDlgButton(hMain, IDC_CHECKS[i], BST_UNCHECKED);
			}
			ShowWindow(hChecks[i], SW_SHOW);
		}
		else
		{
			ShowWindow(hChecks[i], SW_HIDE);
		}
	}
}

// initialize main window, register tab control and checkbox
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	TCITEMA ti;
	HFONT defaultFont;
	hMain = hwnd;

	switch (iMsg)
	{
	case WM_CREATE:
	{
		defaultFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

		InitCommonControls();

		hTabControl = CreateWindowA("SysTabControl32", "", WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
			0, 0, MAINWINDOW_WIDTH-20, 22, hwnd, (HMENU)IDC_TABCTRL, hInst, NULL);

		for (int i = 0; i < TAB_COUNT; i++)
		{
			ti.mask = TCIF_TEXT;
			ti.pszText = (LPSTR)Groups[i].groupName.c_str();
			TabCtrl_InsertItem(hTabControl, i, &ti);
		}

		for (int i = 0; i < CHECK_COUNT; i++)
		{
			hChecks[i] = CreateWindowExA(WS_EX_WINDOWEDGE, "Button", "CreateThread(some descrition here)",
				WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | WS_GROUP, 5 + (i / 25) * 250, 30 + 20 * (i % 25) + 5, 250, 20, hwnd, (HMENU)IDC_CHECKS[i], hInst, NULL);
			SendMessageA(hChecks[i], WM_SETFONT, (WPARAM)defaultFont, TRUE);
		}

		SendMessageA(hwnd, WM_SETFONT, (WPARAM)defaultFont, TRUE);
		SendMessageA(hTabControl, WM_SETFONT, (WPARAM)defaultFont, TRUE);

		TabCtrl_SetCurSel(hTabControl, 0);
		SetWindowTextA(hMain, PLUGIN_NAME);

		CenterDialog(hwnd);

		UpdateCheckBoxs();
	}
	return 0;
	case WM_NOTIFY:
	{
		switch (((LPNMHDR)lParam)->code)
		{

		case TCN_SELCHANGE:
		{
			UpdateCheckBoxs();

			return TRUE;
		}
		}
	}
	return 0;
	case WM_COMMAND:
		for (int i = 0; i < CHECK_COUNT; i++)
		{
			if (LOWORD(wParam) == IDC_CHECKS[i])
			{
				if (IsDlgButtonChecked(hwnd, IDC_CHECKS[i]))
				{
					// checked, means user want to set bp here, then we'll try to use bp instruction set one.
					Groups[CurTab].apiList[i].bWantToSetBp = true;
					std::string cmd = "bp " + Groups[CurTab].apiList[i].apiName;
					Cmd(cmd.c_str());
				}
				else
				{
					Groups[CurTab].apiList[i].bWantToSetBp = false;
					std::string cmd = "bc " + Groups[CurTab].apiList[i].apiName;
					Cmd(cmd.c_str());
				}
			}
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProcA(hwnd, iMsg, wParam, lParam);
}


// set delay breakpoint when dll loaded
EXTERN_C __declspec(dllexport) void _cdecl CBLOADDLL(
	CBTYPE bType, // event type, one of the `cbType` CB_* values listed above
	PLUG_CB_LOADDLL* callbackInfo // pointer to a structure of information
)
{
	// check if there are any breakpoint can be set
	for (size_t i = 0; i < TAB_COUNT; i++)
	{
		for (size_t j = 0; j < Groups[i].apiList.size(); j++)
		{
			if (Groups[i].apiList[j].bWantToSetBp)
			{
				std::string cmd = "bp " + Groups[i].apiList[j].apiName;
				Cmd(cmd.c_str());
			}
		}
	}
}

// register menu to popup main window
extern "C" __declspec(dllexport) void CBMENUENTRY(CBTYPE cbType, PLUG_CB_MENUENTRY* info)
{
	switch (info->hEntry)
	{
	case MENU_MAINWINDOW_POPUP:
		if (!bIsMainWindowShow && DbgIsDebugging())
		{
			CloseHandle(CreateThread(0, 0, MsgLoopThread, 0, 0, 0));
			bIsMainWindowShow = true;
		}

		break;
	}
}



