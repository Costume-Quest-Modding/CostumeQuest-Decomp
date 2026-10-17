#ifndef HPP_CQ_UNIMPLEMENTED
#define HPP_CQ_UNIMPLEMENTED

// NOTE: This is not part of the decomp code.
// This header exists to abort on a function
// that does not have an implementation.

#include <cstdio>
#include <intrin.h>

#define UNIMPLEMENTED() \
    do { \
        std::fprintf(stderr, "%s UNIMPLEMENTED (%s:%d)\n", __FUNCTION__, __FILE__, __LINE__); \
        __debugbreak(); \
    } while(0)

#endif