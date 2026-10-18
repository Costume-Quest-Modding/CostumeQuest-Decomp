#include "debug/trace.hpp"

#include <cstdio>
#include <cstdarg>

namespace debug {
    const char* trace_names[TRACE_MAX_DEPTH]; // 0x00a99fb0
    int trace_depth = 0; // 0x00a99fc0
    
    // TODO: Some kind of unused character array
    char trace_unk1_00a99fc4 = NULL; // 0x00a99fc4

    void TracePush(char buf[TRACE_MSG_BUFFER], const char* fmt, ...) {
        *buf = '\0';

        if (fmt != NULL) {
            va_list args;
            va_start(args, fmt);

            int written = _vsnprintf(buf, TRACE_MSG_BUFFER, fmt, args);
            if (written < 0) {
                buf[TRACE_MSG_BUFFER - 1] = '\0';
            }

            va_end(args);
        }

        if (trace_depth < 4) {
            trace_names[trace_depth] = buf;
            trace_depth++;
        }
    }
}