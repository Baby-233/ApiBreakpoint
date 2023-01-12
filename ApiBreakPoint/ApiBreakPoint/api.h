//#pragma once
//#include <vector>
//#include <string>
//
//struct ApiBreakPointInfo
//{
//	std::string dllName;
//	std::string apiName;
//	std::string description;
//	bool bpSet;
//
//	ApiBreakPointInfo(std::string _dllName, std::string _apiName, std::string _description)
//		: dllName(_dllName), apiName(_apiName), description(_description), bpSet(false) {}
//};
//
//struct ApiGroup
//{
//	std::string groupName;
//	std::vector<ApiBreakPointInfo> apiList;
//};
//
///*
// * You can change display text language here if you want.
// * Dll name are not necessary so far cause we are using "bp" rather than SetBPX()
// * If the function name appears in multiple dlls, the behavior depends on the bp instruction
// */
//ApiGroup Groups[TAB_COUNT] =
//{
//	{
//		"���öϵ�",
//		{
//			ApiBreakPointInfo("expsrv.dll","rtcFileLen","VB��У��"),
//			ApiBreakPointInfo("Kernel32.dll","FindFirstFileA","�����ļ�"),
//			ApiBreakPointInfo("Kernel32.dll","ExitProcess","�����˳�"),
//			ApiBreakPointInfo("Kernel32.dll","GetStartupInfoA","��ȡ������Ϣ"),
//			ApiBreakPointInfo("Kernel32.dll","GetFileSize","��ȡ�ļ���С"),
//			ApiBreakPointInfo("Kernel32.dll","VirtualProtect","Vmp�ѿ�"),
//			ApiBreakPointInfo("User32.dll","ExitWindowsEx","�ػ��ϵ�"),
//			ApiBreakPointInfo("Kernel32.dll","CreateFileA","��У��"),
//			ApiBreakPointInfo("Kernel32.dll","GetVersion","�������ѿ�"),
//			ApiBreakPointInfo("Ws2_32.dll","send","���ͷ��"),
//			ApiBreakPointInfo("Ws2_32.dll","WSASend","���ͷ��"),
//			ApiBreakPointInfo("Ws2_32.dll","recv","���շ��"),
//			ApiBreakPointInfo("ntdll.dll","RtlAdjustPrivilege","�����Կ��ٹػ�"),
//			ApiBreakPointInfo("Shell32.dll","SHFormatDrive","����API"),
//			ApiBreakPointInfo("Kernel32.dll","RemoveDirectoryA","ɾ��Ŀ¼"),
//			ApiBreakPointInfo("Kernel32.dll","DeleteFileA","ɾ���ļ�"),
//		}
//	},
//	{
//		"�Ի���",
//		{
//			ApiBreakPointInfo("","MessageBoxA","���Ի���"),
//			ApiBreakPointInfo("","MessageBoxW",""),
//			ApiBreakPointInfo("","MessageBoxExA",""),
//			ApiBreakPointInfo("","MessageBoxExW",""),
//		}
//	},
//	{
//		"�ļ�����",
//		{
//			ApiBreakPointInfo("Kernel32.dll","CreateFileA","��������ļ�"),
//			ApiBreakPointInfo("Kernel32.dll","CreateFileW",""),
//		}
//	},
//	{
//		"Memory",
//		{
//			ApiBreakPointInfo("","",""),
//		}
//	},
//	{
//		"Reg",
//		{
//			ApiBreakPointInfo("","",""),
//		}
//	},
//	{
//		"Time",
//		{
//			ApiBreakPointInfo("","",""),
//		}
//	},
//	{
//		"Process",
//		{
//			ApiBreakPointInfo("","",""),
//		}
//	},
//	{
//		"Network",
//		{
//			ApiBreakPointInfo("","",""),
//		}
//	},
//	{
//		"Memory",
//		{
//			ApiBreakPointInfo("","",""),
//		}
//	},
//	{
//		"Disk",
//		{
//			ApiBreakPointInfo("","",""),
//		}
//	},
//	{
//		"Malware",
//		{
//			ApiBreakPointInfo("","",""),
//		}
//	},
//	{
//		"AntiDebug",
//		{
//			ApiBreakPointInfo("","",""),
//		}
//	},
//	{
//		"VB",
//		{
//			ApiBreakPointInfo("","",""),
//		}
//	},
//	{
//		"VC/MFC",
//		{
//			ApiBreakPointInfo("","",""),
//		}
//	},
//	{
//		"E-Lang",
//		{
//			ApiBreakPointInfo("","",""),
//		}
//	},
//};