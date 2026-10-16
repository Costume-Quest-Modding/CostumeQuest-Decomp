#ifndef HPP_CQ_ALLOCATOR
#define HPP_CQ_ALLOCATOR

#include <cstdint>

enum AllocTag : uint32_t {
    ALLOCTAG_0,
    ALLOCTAG_1,
    ALLOCTAG_2,
    ALLOCTAG_3,
    ALLOCTAG_4,
    ALLOCTAG_5,
    ALLOCTAG_6,
    ALLOCTAG_7,
    ALLOCTAG_8,
    ALLOCTAG_9,
    ALLOCTAG_10,
    ALLOCTAG_11,
    ALLOCTAG_12,
    ALLOCTAG_13,
    ALLOCTAG_14,
    ALLOCTAG_15,
    ALLOCTAG_16,
    ALLOCTAG_17,
    ALLOCTAG_18,
    ALLOCTAG_19,
    ALLOCTAG_20,
    ALLOCTAG_21,
    ALLOCTAG_22,
    ALLOCTAG_23,
    ALLOCTAG_24,
    ALLOCTAG_25,
    ALLOCTAG_26,
    ALLOCTAG_27,
    ALLOCTAG_28,
    ALLOCTAG_29,
    ALLOCTAG_30,
    ALLOCTAG_31,
    ALLOCTAG_32,
    ALLOCTAG_33,
    ALLOCTAG_34,
    ALLOCTAG_35,
    ALLOCTAG_36,
    ALLOCTAG_37,
    ALLOCTAG_38,
    ALLOCTAG_39,
    ALLOCTAG_40,
    ALLOCTAG_41,
    ALLOCTAG_42,
    ALLOCTAG_43,
    ALLOCTAG_44,
    ALLOCTAG_45,
    ALLOCTAG_46,
    ALLOCTAG_47,
    ALLOCTAG_48,
    ALLOCTAG_49,
    ALLOCTAG_50,
    ALLOCTAG_51,
    ALLOCTAG_52,
    ALLOCTAG_53,
    ALLOCTAG_54,
    ALLOCTAG_55,
    ALLOCTAG_56,
    ALLOCTAG_57,
    ALLOCTAG_58,
    ALLOCTAG_59,
    ALLOCTAG_60,
    ALLOCTAG_61,
    ALLOCTAG_62,
    ALLOCTAG_63,

    ALLOCTAG_MAX
};

void* allocator_noop();

void* tracked_malloc(size_t size, size_t align, AllocTag tag);
void tracked_free(void* ptr);

void* tracked_virtual_alloc(size_t size, AllocTag tag);
void* tracked_virtual_alloc_top_down(size_t size, AllocTag tag);

void tracked_virtual_free(void* ptr, size_t size, AllocTag tag);

extern void (*G_alloc_failure_handler)();

void* operator new(size_t size, AllocTag tag) noexcept;

void operator delete(void* ptr) noexcept;

#endif