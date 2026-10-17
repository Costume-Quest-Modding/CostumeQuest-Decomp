#include "allocator.hpp"

#include <cstdlib>

#include <windows.h>

#include <tools/unimplemented.hpp>

struct AllocTagStats {
    size_t unk1_0x0;
    size_t alloc_count;
    size_t requested_size;
    size_t overhead_size;
    size_t unk5_0x10;
    size_t unk6_0x14;
};

struct AllocHeader {
    uint8_t align;
    uint8_t offset;
    uint8_t size;
    uint8_t tag;
};

static AllocTagStats alloc_tag_table[ALLOCTAG_MAX]; // 0x009f3e28

void (*G_alloc_failure_handler)() = NULL; // 0x00a8ff38

// 0x00711c20
void* allocator_noop() {
    static int object = 0;
    return &object;
}

// 0x00711a60
void* tracked_malloc(size_t size, size_t align, AllocTag tag) {
    size_t requested_size = size;

    if (align < 2) {
        align = 1;
    }
    
    size_t header_size = align + sizeof(AllocHeader);
    
    void* memory = malloc(header_size + size);
    if (memory == NULL) {
        return NULL;
    }

    void* aligned_ptr = (void*)(((uintptr_t)memory + align + 3) & ~(align - 1));
    AllocHeader* header = (AllocHeader*)((uintptr_t)aligned_ptr - sizeof(AllocHeader));
    header->align = (uint8_t)align;
    header->offset = (uint8_t)((uintptr_t)aligned_ptr - (uintptr_t)memory);
    header->size = (uint8_t)size;
    header->tag = (uint8_t)tag;

    *((uint8_t*)memory) = (uint8_t)align;

    AllocTagStats* stats = &alloc_tag_table[tag];
    InterlockedExchangeAdd(&stats->alloc_count, 1);
    InterlockedExchangeAdd(&stats->requested_size, requested_size);
    InterlockedExchangeAdd(&stats->overhead_size, header_size);

    return aligned_ptr;
}

// 0x00711b00
void tracked_free(void* ptr) {
    AllocHeader* header = (AllocHeader*)((uintptr_t)ptr - sizeof(AllocHeader));
    void* memory = (void*)((uintptr_t)ptr - header->offset);

    size_t total_size = _msize(memory);

    size_t overhead_size = total_size - header->size;
    size_t requested_size = header->size;
    
    AllocTagStats* stats = &alloc_tag_table[header->tag];

    InterlockedExchangeAdd(&stats->alloc_count, -1);
    InterlockedExchangeAdd(&stats->requested_size, -(LONG)requested_size);
    InterlockedExchangeAdd(&stats->overhead_size, -(LONG)overhead_size);

    free(memory);
}

// 0x00716e50
void* tracked_virtual_alloc(size_t size, AllocTag tag) {
    // TODO: Decompile
    UNIMPLEMENTED();
    return NULL;
}

// 0x00716ec0
void* tracked_virtual_alloc_top_down(size_t size, AllocTag tag) {
    // TODO: Decompile
    UNIMPLEMENTED();
    return NULL;
}

// 0x00716f30
void tracked_virtual_free(void* ptr, size_t size, AllocTag tag) {
    // TODO: Decompile
    UNIMPLEMENTED();
}

// 0x0070b020
void* operator new(size_t size, AllocTag tag) noexcept {
    allocator_noop();
    void* memory = tracked_malloc(size, 16, tag);
    
    if (memory == NULL && G_alloc_failure_handler != NULL) {
        G_alloc_failure_handler();
    }

    return memory;
}

// 0x0070b050
void operator delete(void* ptr) noexcept {
    allocator_noop();
    
    if (ptr != NULL) {
        tracked_free(ptr);
    }
}