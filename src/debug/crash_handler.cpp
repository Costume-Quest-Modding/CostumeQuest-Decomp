#include "debug/crash_handler.hpp"
#include "debug/trace.hpp"

#include <cstdio>

#include <DbgHelp.h>

typedef BOOL (WINAPI *PFN_MiniDumpWriteDump)(
    HANDLE, DWORD, HANDLE, MINIDUMP_TYPE,
    CONST PMINIDUMP_EXCEPTION_INFORMATION,
    CONST PMINIDUMP_USER_STREAM_INFORMATION,
    CONST PMINIDUMP_CALLBACK_INFORMATION);

namespace debug {
    int (*pfn_messagebox)(void* handle, const char* msg, const char* title, uint32_t type) = NULL; // 0x00a99f84
    
    // 0x00719e80
    LONG WINAPI CrashHandler(EXCEPTION_POINTERS* exceptionInfo) { 
        MEMORYSTATUS mem_status;
        GlobalMemoryStatus(&mem_status);

        char module_path[264];
        char crash_name[256];
        char file_name[512];

        sprintf(crash_name, "Crash: 0x%08x", (int)exceptionInfo->ExceptionRecord->ExceptionCode);

        if (trace_depth < 4) {
            trace_names[trace_depth] = crash_name;
            trace_depth++;
        }

        HMODULE dbghelp = NULL;
        WORD result = GetModuleFileNameA(NULL, module_path, sizeof(module_path) - 4);

        if (result == 0) {
        fallback:
            dbghelp = LoadLibraryA("DBGHELP.DLL");
            if (dbghelp == NULL) goto end;
        }
        else {
            char* last_slash = strrchr(module_path, '\\');
            if (last_slash == NULL) goto fallback;

            strncpy(last_slash + 1, "DBGHELP.DLL", sizeof("DBGHELP.DLL"));
            dbghelp = LoadLibraryA(module_path);

            if (dbghelp == NULL) goto end;
        }

        PFN_MiniDumpWriteDump pfn_MiniDumpWriteDump = (PFN_MiniDumpWriteDump)GetProcAddress(dbghelp, "MiniDumpWriteDump");
        if (pfn_MiniDumpWriteDump != 0) {
            snprintf(file_name, sizeof(file_name) - 1, "DFDump%c%d-%d.dmp", 'R', 1, 0x7ff53);

            HANDLE dump_file = CreateFileA(file_name, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
            if (dump_file != INVALID_HANDLE_VALUE) {
                HANDLE proc = GetCurrentProcess();
                DWORD proc_id = GetCurrentProcessId();

                MINIDUMP_EXCEPTION_INFORMATION mdei;
                mdei.ThreadId = GetCurrentThreadId();
                mdei.ExceptionPointers = exceptionInfo;
                mdei.ClientPointers = 1;

                pfn_MiniDumpWriteDump(proc, proc_id, dump_file, MiniDumpNormal, &mdei, NULL, NULL);

                CloseHandle(dump_file);
            }
        }

    end:

        if (pfn_messagebox != NULL) {
            pfn_messagebox(0, &trace_unk1_00a99fc4, "Callstack", 1);
        }
        TracePop();

        Sleep(250);
        return EXCEPTION_EXECUTE_HANDLER;
    }
}