//======================================
// Thanks to tmp64 for crash handler code from his BugfixedHL-Rebased.
// https://github.com/tmp64/BugfixedHL-Rebased
// https://github.com/tmp64/BugfixedHL-Rebased/blob/master/src/game/client/engine_patches_windows.cpp#L749-L1225
//======================================

#include "includes.h"
#include "StackWalker.h"

//---------------------------------------------------------------
// Vectored Exceptions Handler
//---------------------------------------------------------------
static LONG NTAPI CrashHandlerCaller(PEXCEPTION_POINTERS pExceptionInfo);

class CWindowsCrashHandler
{
public:
	void OnDLLAttach()
	{
		if (!m_hHandler)
		{
			m_hHandler = AddVectoredExceptionHandler(TRUE, CrashHandlerCaller);
		}
	}

	void OnDLLDetach()
	{
		m_bIsDetaching = true;

		if (m_hHandler)
		{
			RemoveVectoredExceptionHandler(m_hHandler);
			m_hHandler = nullptr;
		}
	}

	LONG VectoredExceptionsHandler(PEXCEPTION_POINTERS pExceptionInfo) noexcept
	{
		DWORD exceptionCode = pExceptionInfo->ExceptionRecord->ExceptionCode;
		DWORD exceptionAddress = (long)pExceptionInfo->ExceptionRecord->ExceptionAddress;

		if (exceptionCode == 0xE06D7363u) // SEH
			return EXCEPTION_CONTINUE_SEARCH;

		// We will handle all fatal unexpected exceptions, like STATUS_ACCESS_VIOLATION
		// But skip DLL Not Found exception, which happen on old non-steam when steam is running
		// Also skip while detach is in process, cos we can't write files (not sure about message boxes, but anyway...)
		if ((exceptionCode & 0xF0000000L) == 0xC0000000L && exceptionCode != 0xC0000139 && !m_bIsDetaching)
		{
			time_t timestamp = time(nullptr);
			localtime_s(&m_CrashTime, &timestamp);
			strftime(m_szCrashFileName, sizeof(m_szCrashFileName), "crash-%Y-%m-%d-%H-%M-%S", &m_CrashTime);

			CreateCrashReport(pExceptionInfo);
			CreateMiniDump(pExceptionInfo);
			ShowCrashDialog(pExceptionInfo);

			// Application will die anyway, so futher exceptions are not interesting to us
			RemoveVectoredExceptionHandler(m_hHandler);
			m_hHandler = nullptr;
		}

		return EXCEPTION_CONTINUE_SEARCH;
	}

	void CreateCrashReport(PEXCEPTION_POINTERS pExceptionInfo) noexcept
	{
		char filename[MAX_PATH];
		snprintf(filename, sizeof(filename), "chaos_%s.txt", m_szCrashFileName);

		FILE* file = fopen(filename, "w");

		if (file)
		{
			DWORD exceptionCode = pExceptionInfo->ExceptionRecord->ExceptionCode;
			DWORD exceptionAddress = (DWORD)pExceptionInfo->ExceptionRecord->ExceptionAddress;

			fprintf(file, "GSChaos Crash Log\n");
			fprintf(file, "  Exception %s (0x%08X) at address 0x%08X (%s).\n",
				ExceptionCodeString(exceptionCode),
				exceptionCode,
				exceptionAddress,
				GetModuleNameForAddress(exceptionAddress));
			fprintf(file, "\n");

			fprintf(file, "Please post contents of this log file and file chaos_%s.dmp on\n", m_szCrashFileName);
			fprintf(file, "https://github.com/ScriptedSnark/GSChaos/issues\n");
			fprintf(file, "\n\n\n\n\n");
			fprintf(file, "-------------------------------------------------------------------------\n");
			fprintf(file, "Technical information\n");
			fprintf(file, "\n");

			PrintGameInfo(file);
			PrintStackTrace(file, pExceptionInfo);
			PrintModuleList(file, pExceptionInfo);

			fclose(file);

			ShellExecuteA(NULL, "open", "notepad.exe", filename, NULL, SW_SHOWNORMAL);
		}
	}

	void PrintGameInfo(FILE* file) noexcept
	{
		fprintf(file, "Version: " __TIMESTAMP__ "\n");

		// do some engine analyzing
		fprintf(file, UTIL_VarArgs("Encrypted engine?: %s\n", g_bEncrypted ? "true" : "false"));
		fprintf(file, UTIL_VarArgs("Pre-Steampipe?: %s\n", g_bPreSteamPipe ? "true" : "false"));
		fprintf(file, UTIL_VarArgs("HL25?: %s\n", g_bHL25 ? "true" : "false"));

		char buffer[128];
		strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &m_CrashTime);
		fprintf(file, "Local time: %s\n", buffer);

		// OS version
		fprintf(file, "OS version: ");
		{
			DWORD handle;
			DWORD size = GetFileVersionInfoSizeA("kernel32.dll", &handle);

			if (size != 0)
			{
				char* verBuf = (char*)malloc(size);

				if (verBuf)
				{
					if (GetFileVersionInfoA("kernel32.dll", 0, size, verBuf))
					{
						VS_FIXEDFILEINFO* info = nullptr;
						UINT infoSize;

						if (VerQueryValueA(verBuf, "\\", (LPVOID*)&info, &infoSize))
						{

							if (infoSize != 0)
							{
								fprintf(file, "%u.%u.%u.%u\n",
									HIWORD(info->dwFileVersionMS),
									LOWORD(info->dwFileVersionMS),
									HIWORD(info->dwFileVersionLS),
									LOWORD(info->dwFileVersionLS));
							}
							else
							{
								fprintf(file, "infoSize = 0\n");
							}
						}
						else
						{
							fprintf(file, "VerQueryValueA failed\n");
						}
					}
					else
					{
						fprintf(file, "GetFileVersionInfoA failed\n");
					}
				}
				else
				{
					fprintf(file, "malloc(%u) failed\n", size);
				}
			}
			else
			{
				fprintf(file, "GetFileVersionInfoSizeA failed\n");
			}
		}

		fprintf(file, "\n");
	}

	void PrintStackTrace(FILE* file, PEXCEPTION_POINTERS pExceptionInfo) noexcept
	{
		fprintf(file, "Stack trace (may be incorrect since no engine PDBs are available):\n");

		int options = StackWalker::RetrieveSymbol | StackWalker::RetrieveLine | StackWalker::SymAll;
		StackWalkerToFile sw(file, StackWalker::OptionsAll, nullptr, GetCurrentProcessId(), GetCurrentProcess());
		sw.ShowCallstack(GetCurrentThread(), pExceptionInfo->ContextRecord);

		fprintf(file, "\n");
	}

	void PrintModuleList(FILE* file, PEXCEPTION_POINTERS pExceptionInfo) noexcept
	{
		DWORD exceptionCode = pExceptionInfo->ExceptionRecord->ExceptionCode;
		DWORD exceptionAddress = (DWORD)pExceptionInfo->ExceptionRecord->ExceptionAddress;

		// Get modules info
		HMODULE hMods[1024];
		HANDLE hProcess = GetCurrentProcess();
		MODULEINFO moduleInfo;
		DWORD cbNeeded;
		EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded);
		int count = cbNeeded / sizeof(HMODULE);

		fprintf(file, "Modules:\n");
		fprintf(file, "  Base     Size     Path (Exception Offset)\n");
		for (int i = 0; i < count; i++)
		{
			GetModuleInformation(hProcess, hMods[i], &moduleInfo, sizeof(moduleInfo));
			DWORD moduleBase = (DWORD)moduleInfo.lpBaseOfDll;
			DWORD moduleSize = (DWORD)moduleInfo.SizeOfImage;

			// Get the full path to the module's file.
			TCHAR szModName[MAX_PATH];
			if (GetModuleFileNameEx(hProcess, hMods[i], szModName, sizeof(szModName) / sizeof(TCHAR)))
			{
				if (moduleBase <= exceptionAddress && exceptionAddress <= (moduleBase + moduleSize))
					fprintf(file, "=>%08X %08X %s  <==  %08X\n", moduleBase, moduleSize, szModName, exceptionAddress - moduleBase);
				else
					fprintf(file, "  %08X %08X %s\n", moduleBase, moduleSize, szModName);
			}
			else
			{
				if (moduleBase <= exceptionAddress && exceptionAddress <= (moduleBase + moduleSize))
					fprintf(file, "=>%08X %08X  <==  %08X\n", moduleBase, moduleSize, exceptionAddress - moduleBase);
				else
					fprintf(file, "  %08X %08X\n", moduleBase, moduleSize);
			}
		}

		fprintf(file, "\n");
	}

	void CreateMiniDump(PEXCEPTION_POINTERS pExceptionInfo)
	{
		char filename[MAX_PATH];
		snprintf(filename, sizeof(filename), "chaos_%s.dmp", m_szCrashFileName);
		HANDLE hProcess = GetCurrentProcess();
		HANDLE hMiniDumpFile = CreateFile(filename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_WRITE_THROUGH, NULL);

		if (hMiniDumpFile != INVALID_HANDLE_VALUE)
		{
			MINIDUMP_EXCEPTION_INFORMATION eInfo;
			eInfo.ThreadId = GetCurrentThreadId();
			eInfo.ExceptionPointers = pExceptionInfo;
			eInfo.ClientPointers = FALSE;
			MiniDumpWriteDump(hProcess, GetCurrentProcessId(), hMiniDumpFile, MiniDumpNormal, &eInfo, NULL, NULL);
			CloseHandle(hMiniDumpFile);
		}
	}

	void ShowCrashDialog(PEXCEPTION_POINTERS pExceptionInfo)
	{
		char buf[1024];
		snprintf(buf, sizeof(buf),
			"Seems like Chaos Mod was too chaotic for GoldSrc :xdd:\n"
			"Game has crashed (%s).\n"
			"\n"
			"A crash log file was opened in Notepad.\n"
			"Please report its contents as well as file named chaos_%s.dmp on GitHub.\n"
			"\n" "https://github.com/ScriptedSnark/GSChaos/issues",
			ExceptionCodeString(pExceptionInfo->ExceptionRecord->ExceptionCode),
			m_szCrashFileName);

		MessageBoxA(g_hWndOfGame ? g_hWndOfGame : NULL, buf, "GSChaos", MB_OK | MB_ICONEXCLAMATION | MB_SETFOREGROUND | MB_TOPMOST);
	}

	const char* ExceptionCodeString(DWORD exceptionCode)
	{
		switch (exceptionCode)
		{
		case STATUS_ACCESS_VIOLATION:
			return "EXCEPTION_ACCESS_VIOLATION";
		case STATUS_ARRAY_BOUNDS_EXCEEDED:
			return "EXCEPTION_ARRAY_BOUNDS_EXCEEDED";
		case STATUS_BREAKPOINT:
			return "EXCEPTION_BREAKPOINT";
		case STATUS_DATATYPE_MISALIGNMENT:
			return "EXCEPTION_DATATYPE_MISALIGNMENT";
		case STATUS_FLOAT_DENORMAL_OPERAND:
			return "EXCEPTION_FLT_DENORMAL_OPERAND";
		case STATUS_FLOAT_DIVIDE_BY_ZERO:
			return "EXCEPTION_FLT_DIVIDE_BY_ZERO";
		case STATUS_FLOAT_INEXACT_RESULT:
			return "EXCEPTION_FLT_INEXACT_RESULT";
		case STATUS_FLOAT_INVALID_OPERATION:
			return "EXCEPTION_FLT_INVALID_OPERATION";
		case STATUS_FLOAT_OVERFLOW:
			return "EXCEPTION_FLT_OVERFLOW";
		case STATUS_FLOAT_STACK_CHECK:
			return "EXCEPTION_FLT_STACK_CHECK";
		case STATUS_FLOAT_UNDERFLOW:
			return "EXCEPTION_FLT_UNDERFLOW";
		case EXCEPTION_ILLEGAL_INSTRUCTION:
			return "STATUS_ILLEGAL_INSTRUCTION";
		case STATUS_IN_PAGE_ERROR:
			return "EXCEPTION_IN_PAGE_ERROR";
		case STATUS_INTEGER_DIVIDE_BY_ZERO:
			return "EXCEPTION_INT_DIVIDE_BY_ZERO";
		case STATUS_INTEGER_OVERFLOW:
			return "EXCEPTION_INT_OVERFLOW";
		case STATUS_INVALID_DISPOSITION:
			return "EXCEPTION_INVALID_DISPOSITION";
		case STATUS_INVALID_HANDLE:
			return "EXCEPTION_INVALID_HANDLE";
		case STATUS_NONCONTINUABLE_EXCEPTION:
			return "EXCEPTION_NONCONTINUABLE_EXCEPTION";
		case STATUS_PRIVILEGED_INSTRUCTION:
			return "EXCEPTION_PRIV_INSTRUCTION";
		case STATUS_SINGLE_STEP:
			return "EXCEPTION_SINGLE_STEP";
		case STATUS_STACK_OVERFLOW:
			return "EXCEPTION_STACK_OVERFLOW";
		case STATUS_UNWIND_CONSOLIDATE:
			return "STATUS_UNWIND_CONSOLIDATE";
		default:
			return "< unknown >";
		}
	}

	bool PATHSEPARATOR(char c)
	{
		return c == '\\' || c == '/';
	}

	const char* V_UnqualifiedFileName(const char* in)
	{
		// back up until the character after the first path separator we find,
		// or the beginning of the string
		const char* out = in + strlen(in) - 1;
		while ((out > in) && (!PATHSEPARATOR(*(out - 1))))
			out--;
		return out;
	}

	const char* GetModuleNameForAddress(DWORD address)
	{
		// Get modules info
		HMODULE hMods[1024];
		HANDLE hProcess = GetCurrentProcess();
		MODULEINFO moduleInfo;
		DWORD cbNeeded;
		EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded);
		int count = cbNeeded / sizeof(HMODULE);

		static char outbuf[MAX_PATH];

		for (int i = 0; i < count; i++)
		{
			GetModuleInformation(hProcess, hMods[i], &moduleInfo, sizeof(moduleInfo));
			DWORD moduleBase = (DWORD)moduleInfo.lpBaseOfDll;
			DWORD moduleSize = (DWORD)moduleInfo.SizeOfImage;

			if (moduleBase <= address && address < (moduleBase + moduleSize))
			{
				// Get the full path to the module's file.
				if (GetModuleFileNameEx(hProcess, hMods[i], outbuf, sizeof(outbuf)))
				{
					return V_UnqualifiedFileName(outbuf);
				}
				else
				{
					return "< unknown module name >";
				}
			}
		}

		return "< module not found >";
	}

private:
	class StackWalkerToFile : public StackWalker
	{
	public:
		StackWalkerToFile(FILE* pFile, int options = OptionsAll,
			LPCSTR szSymPath = NULL,
			DWORD dwProcessId = GetCurrentProcessId(),
			HANDLE hProcess = GetCurrentProcess())
			: StackWalker(options, szSymPath, dwProcessId, hProcess)
		{
			m_pFile = pFile;
		}

		virtual void OnOutput(LPCSTR szText) override
		{
			fputs("  ", m_pFile);
			fputs(szText, m_pFile);
		}

		virtual void OnLoadModule(LPCSTR img,
			LPCSTR mod,
			DWORD64 baseAddr,
			DWORD size,
			DWORD result,
			LPCSTR symType,
			LPCSTR pdbName,
			ULONGLONG fileVersion) override
		{
		}

		virtual void OnDbgHelpErr(LPCSTR szFuncName, DWORD gle, DWORD64 addr) override
		{
			// Silence symbol errors (PDBs for engine modules are not available)
			if (!strcmp(szFuncName, "SymGetSymFromAddr64") || !strcmp(szFuncName, "SymGetLineFromAddr64"))
				return;
			StackWalker::OnDbgHelpErr(szFuncName, gle, addr);
		}

		virtual void OnSymInit(LPCSTR szSearchPath, DWORD symOptions, LPCSTR szUserName) override
		{
		}

	private:
		FILE* m_pFile = nullptr;
	};

	bool m_bIsDetaching = false;
	PVOID m_hHandler = nullptr;
	tm m_CrashTime;
	char m_szCrashFileName[MAX_PATH]; // Name of crash log and dump without extention
};

static CWindowsCrashHandler s_CrashHandler;

static LONG NTAPI CrashHandlerCaller(PEXCEPTION_POINTERS pExceptionInfo)
{
	return s_CrashHandler.VectoredExceptionsHandler(pExceptionInfo);
}

//-------------------------------------------------------------------
// DLL Entry Point
//-------------------------------------------------------------------
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hinstDLL); // said to increase performance?
		s_CrashHandler.OnDLLAttach();
	}
	else if (fdwReason == DLL_PROCESS_DETACH)
	{
		s_CrashHandler.OnDLLDetach();
	}

	return TRUE;
}