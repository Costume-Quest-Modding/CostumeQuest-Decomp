#ifndef HPP_CQ_STRING
#define HPP_CQ_STRING

#include <cstdint>

#include "allocator.hpp"

// TODO: Revisit this

class String {
public:
    uint32_t tag : 6;
    uint32_t length : 26;
    uint32_t capacity : 30;
    uint32_t unk_bit : 1;
    uint32_t not_owned : 1;
    char* data;

    // Might be other constructors
    String(AllocTag tag);
    
    ~String();

    void Assign(char* source, int size = -1);

    void FUN_0050be00(uint32_t new_size, bool force_realloc);
    void FUN_004332b0(uint32_t new_cap);
};

#endif