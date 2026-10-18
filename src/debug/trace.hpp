#ifndef HPP_CQ_DEBUG_TRACE
#define HPP_CQ_DEBUG_TRACE

#include <cstdint>

#define TRACE_MAX_DEPTH 4
#define TRACE_MSG_BUFFER 128

namespace debug {
    extern const char* trace_names[TRACE_MAX_DEPTH];
    extern int trace_depth;
    extern char trace_unk1_00a99fc4;

    void TracePush(char buf[TRACE_MSG_BUFFER], const char* fmt, ...);
    
    inline void TracePop() {
        if (trace_depth >= 0) {
            trace_depth--;
        }
    }
}

#endif