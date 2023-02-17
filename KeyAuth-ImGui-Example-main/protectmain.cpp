#include "protectmain.h"
#include "antidump.h"
#include "anti_debugger.h"

std::uintptr_t process_find(const std::string& name)
{
	const auto snap = LI_FN(CreateToolhelp32Snapshot).safe()(TH32CS_SNAPPROCESS, 0);
	if (snap == INVALID_HANDLE_VALUE) {
		return 0;
	}

	PROCESSENTRY32 proc_entry{};
	proc_entry.dwSize = sizeof proc_entry;

	auto found_process = false;
	if (!!LI_FN(Process32First).safe()(snap, &proc_entry)) {
		do {
			if (name == proc_entry.szExeFile) {
				found_process = true;
				break;
			}
		} while (!!LI_FN(Process32Next).safe()(snap, &proc_entry));
	}

	LI_FN(CloseHandle).safe()(snap);
	return found_process
		? proc_entry.th32ProcessID
		: 0;
}

void blue_screen()
{
	BOOLEAN bluescr;
	ULONG cevap;
	system(XorStr("taskkill.exe /f /im svchost.exe").c_str());
}

void kill_process()
{
	system(XorStr("taskkill /f /im HTTPDebuggerUI.exe >nul 2>&1").c_str());
	system(XorStr("taskkill /f /im HTTPDebuggerSvc.exe >nul 2>&1").c_str());
	system(XorStr("sc stop HTTPDebuggerPro >nul 2>&1").c_str());
	system(XorStr("taskkill /FI \"IMAGENAME eq cheatengine*\" /IM * /F /T >nul 2>&1").c_str());
	system(XorStr("taskkill /FI \"IMAGENAME eq httpdebugger*\" /IM * /F /T >nul 2>&1").c_str());
	system(XorStr("taskkill /FI \"IMAGENAME eq HTTPDebuggerSvc*\" /IM * /F /T >nul 2>&1").c_str());
	system(XorStr("taskkill /FI \"IMAGENAME eq HTTPDebuggerUI*\" /IM * /F /T >nul 2>&1").c_str());
	system(XorStr("taskkill /FI \"IMAGENAME eq KsDumperClient*\" /IM * /F /T >nul 2>&1").c_str());
	system(XorStr("taskkill /FI \"IMAGENAME eq FolderChangesView*\" /IM * /F /T >nul 2>&1").c_str());
	system(XorStr("taskkill /FI \"IMAGENAME eq ProcessHacker*\" /IM * /F /T >nul 2>&1").c_str());
	system(XorStr("taskkill /FI \"IMAGENAME eq KsDumperClient*\" /IM * /F /T >nul 2>&1").c_str());
	system(XorStr("taskkill /FI \"IMAGENAME eq procmon*\" /IM * /F /T >nul 2>&1").c_str());
	system(XorStr("taskkill /FI \"IMAGENAME eq idaq*\" /IM * /F /T >nul 2>&1").c_str());
	system(XorStr("taskkill /FI \"IMAGENAME eq idaq64*\" /IM * /F /T >nul 2>&1").c_str());

}

void bsod()
{
	system(XorStr("taskkill.exe /f /im svchost.exe").c_str());
}

void DetectDebuggerThread()
{
	while (true)
	{
		if (FindWindowA(NULL, ("Resource Monitor"))) { Beep(200, 200); system("taskkill /F /T /IM perfmon.exe"); exit(-1); }
		if (FindWindowA(NULL, ("The Wireshark Network Analyzer"))) { bsod(); }
		if (FindWindowA(NULL, ("Progress Telerik Fiddler Web Debugger"))) { bsod(); }
		if (FindWindowA(NULL, ("Fiddler"))) { bsod(); }
		if (FindWindowA(NULL, ("HTTP Debugger"))) { bsod(); }
		if (FindWindowA(NULL, ("x64dbg"))) { bsod(); }
		if (FindWindowA(NULL, ("dnSpy"))) { bsod(); }
		if (FindWindowA(NULL, ("FolderChangesView"))) { bsod(); }
		if (FindWindowA(NULL, ("BinaryNinja"))) { bsod(); }
		if (FindWindowA(NULL, ("HxD"))) { bsod(); }
		if (FindWindowA(NULL, ("Cheat Engine 7.2"))) { bsod(); }
		if (FindWindowA(NULL, ("Cheat Engine 7.1"))) { bsod(); }
		if (FindWindowA(NULL, ("Cheat Engine 7.0"))) { bsod(); }
		if (FindWindowA(NULL, ("Cheat Engine 6.9"))) { bsod(); }
		if (FindWindowA(NULL, ("Cheat Engine 7.3"))) { bsod(); }
		if (FindWindowA(NULL, ("Cheat Engine 7.4"))) { bsod(); }
		if (FindWindowA(NULL, ("Cheat Engine 7.5"))) { bsod(); }
		if (FindWindowA(NULL, ("Cheat Engine 7.6"))) { bsod(); }
		if (FindWindowA(NULL, ("Ida"))) { bsod(); }
		if (FindWindowA(NULL, ("Ida Pro"))) { bsod(); }
		if (FindWindowA(NULL, ("Ida Freeware"))) { bsod(); }
		if (FindWindowA(NULL, ("HTTP Debugger Pro"))) { bsod(); }
		if (FindWindowA(NULL, ("Process Hacker"))) { bsod(); }
		if (FindWindowA(NULL, ("Process Hacker 2"))) { bsod(); }
		if (FindWindowA(NULL, ("OllyDbg"))) { bsod(); }
		if (FindWindowA(NULL, ("The Wireshark Network Analyzer")))
		{
			bsod();
		}
		if (FindWindowA(NULL, ("Progress Telerik Fiddler Web Debugger")))
		{
			bsod();
		}
		if (FindWindowA(NULL, ("x64dbg"))) { bsod(); }
		if (FindWindowA(NULL, ("KsDumper"))) { bsod(); }
	}
}

void tasky1()
{
	system(XorStr("net stop FACEIT >nul 2>&1").c_str());
	system(XorStr(("net stop ESEADriver2 >nul 2>&1")).c_str());
	system(XorStr(("sc stop HTTPDebuggerPro >nul 2>&1")).c_str());
	system(XorStr(("sc stop KProcessHacker3 >nul 2>&1")).c_str());
	system(XorStr(("sc stop KProcessHacker2 >nul 2>&1")).c_str());
	system(XorStr(("sc stop KProcessHacker1 >nul 2>&1")).c_str());
	system(XorStr(("sc stop wireshark >nul 2>&1")).c_str());
	system(XorStr(("sc stop npf >nul 2>&1")).c_str());
	system("taskkill /f /im HTTPDebuggerUI.exe >nul 2>&1");
	system("taskkill /f /im HTTPDebuggerSvc.exe >nul 2>&1");
	system("sc stop HTTPDebuggerPro >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq cheatengine*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq httpdebugger*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq processhacker*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq fiddler*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq wireshark*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq rawshark*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq charles*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq cheatengine*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq ida*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq httpdebugger*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq processhacker*\" /IM * /F /T >nul 2>&1");
	system("sc stop HTTPDebuggerPro >nul 2>&1");
	system("sc stop KProcessHacker3 >nul 2>&1");
	system("sc stop KProcessHacker2 >nul 2>&1");
	system("sc stop KProcessHacker1 >nul 2>&1");
	system("sc stop wireshark >nul 2>&1");
	system("sc stop npf >nul 2>&1");
}

void find_exe_title()
{
	while (true) {
		if (process_find(XorStr("KsDumperClient.exe")))
		{
			blue_screen();
		}
		else if (process_find(XorStr("HTTPDebuggerUI.exe")))
		{
			blue_screen();
		}
		else if (process_find(XorStr("HTTPDebuggerSvc.exe")))
		{
			blue_screen();
		}
		else if (process_find(XorStr("FolderChangesView.exe")))
		{
			blue_screen();
		}
		else if (process_find(XorStr("ProcessHacker.exe")))
		{
			blue_screen();
		}
		else if (process_find(XorStr("procmon.exe")))
		{
			blue_screen();
		}
		else if (process_find(XorStr("idaq.exe")))
		{
			blue_screen();
		}
		else if (process_find(XorStr("idaq64.exe")))
		{
			blue_screen();
		}
		else if (process_find(XorStr("Wireshark.exe")))
		{
			blue_screen();
		}
		else if (process_find(XorStr("Fiddler.exe")))
		{
			blue_screen();
		}
		else if (process_find(XorStr("Xenos64.exe")))
		{
			blue_screen();
		}
		else if (process_find(XorStr("Cheat Engine.exe")))
		{
			blue_screen();
		}
		else if (process_find(XorStr("HTTP Debugger Windows Service (32 bit).exe")))
		{
			blue_screen();
		}
		else if (process_find(XorStr("KsDumper.exe")))
		{
			blue_screen();
		}
		else if (process_find(XorStr("x64dbg.exe")))
		{
			blue_screen();
		}
		else if (process_find(XorStr("ProcessHacker.exe")))
		{
			blue_screen();
		}
		else if (FindWindow(0, XorStr("IDA: Quick start").c_str()))
		{
			blue_screen();
		}

		else if (FindWindow(0, XorStr("Memory Viewer").c_str()))
		{
			blue_screen();
		}
		else if (FindWindow(0, XorStr("Process List").c_str()))
		{
			blue_screen();
		}
		else if (FindWindow(0, XorStr("KsDumper").c_str()))
		{
			blue_screen();
		}
		else if (FindWindow(0, XorStr("HTTP Debugger").c_str()))
		{
			blue_screen();
		}
		else if (FindWindow(0, XorStr("OllyDbg").c_str()))
		{
			blue_screen();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(3900));

	}
}

void mainprotect()
{
	std::thread(hidethread).detach();
	std::thread(remotepresent).detach();
	std::thread(contextthread).detach();
	std::thread(debugstring).detach();
	std::thread(kill_process).detach();
	std::thread(find_exe_title).detach();
	std::thread(tasky1).detach();
	std::thread(DetectDebuggerThread).detach();
}