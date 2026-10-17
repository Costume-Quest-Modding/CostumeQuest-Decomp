// SPDX-License-Identifier: BSD-2-Clause
// Copyright (c) 2026 Costume-Quest-Modding

#ifndef HPP_TOOLS_UNIMPLEMENTED
#define HPP_TOOLS_UNIMPLEMENTED

#include <cstdio>
#include <intrin.h>

#define UNIMPLEMENTED() \
    do { \
        std::fprintf(stderr, "%s UNIMPLEMENTED (%s:%d)\n", __FUNCTION__, __FILE__, __LINE__); \
        __debugbreak(); \
    } while(0)

#endif