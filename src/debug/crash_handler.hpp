#ifndef HPP_CQ_DEBUG_CRASH_HANDLER
#define HPP_CQ_DEBUG_CRASH_HANDLER

#include <windows.h>

#include <cstdint>

namespace debug {
    extern int (*pfn_messagebox)(void* handle, const char* msg, const char* title, uint32_t type);

    LONG WINAPI CrashHandler(EXCEPTION_POINTERS* exceptionInfo);
}

#endif