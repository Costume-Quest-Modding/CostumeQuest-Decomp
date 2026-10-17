#include "string.hpp"

#include <cstring>

// NOTE: Not sure if the function belongs here.
// I haven't checked its usage elsewhere.
// 0x0070c2f0
void* ArrayResize(AllocTag tag, bool free_old, void* data, size_t element_size, size_t old_cap, size_t new_cap) {
    void* new_data = NULL;

    if (new_cap != 0) {
        allocator_noop();
        new_data = tracked_malloc(element_size * new_cap, 0x10, tag);
        
        if (new_data == NULL && G_alloc_failure_handler != NULL) {
            G_alloc_failure_handler();
        }
        
        if (old_cap <= new_cap) {
            new_cap = old_cap;
        }

        memcpy(new_data, data, new_cap * element_size);
    }

    if (free_old && data != NULL) {
        allocator_noop();
        tracked_free(data);
    }

    return new_data;
}

// UNSURE: Inferred from DFApp::ParseCommandLine's inlined constructor of String.
// NOTE: No known address.
String::String(AllocTag tag)
    : tag(tag), length(0), capacity(0), unk_bit(0), not_owned(0), data(nullptr)
{

}

// UNSURE: Inferred from DFApp::ParseCommandLine's inlined destructor of String.
// NOTE: No known address.
String::~String() {
    this->FUN_004332b0(0);
}

// 0x0070b8d0
void String::Assign(char* source, int size) {
    if (source != NULL && *source != '\0') {
        if (size < 0) {
            char* tmp = source;
            char character = '\0';

            do {
                character = *tmp;
                tmp++;
            } while(character != '\0');

            size = (int)((size_t)tmp - (size_t)(source + 1));
        }

        int new_size = size + 1;
        if (capacity < new_size || (capacity < new_size && !this->not_owned)) {
            this->FUN_0050be00(new_size, capacity < new_size);
        }
        else {
            this->length = new_size;
        }

        strncpy(this->data, source, size);
        this->data[size] = '\0';
        return;
    }
    this->FUN_004332b0(0);
}

// 0x0050be00
void String::FUN_0050be00(uint32_t new_size, bool force_realloc) {
    uint32_t new_cap = new_size;

    if (!force_realloc) {
        if (new_size <= this->capacity) {
            this->length = new_size;
            return;
        }

        if (new_size < 0x20) {
            // TODO: Decompile function
            // new_cap = FUN_006bf500(new_size);
        }
        else {
            new_cap = (new_size * 3 >> 3) + 0x10 + new_size;
        }
    }

    this->FUN_004332b0(new_cap);

    this->length = new_size;
    return;
}

// 0x004332b0
void String::FUN_004332b0(uint32_t new_cap) {
    uint32_t cap = this->capacity;

    if (cap != new_cap) {
        if (this->not_owned && new_cap <= cap) {
            cap = this->length;
            if (new_cap < cap) {
                cap = new_cap;
            }

            this->length = cap;
            return;
        }

        void* new_data = ArrayResize((AllocTag)this->tag, !this->not_owned, this->data, sizeof(char), this->length, new_cap);
        this->capacity = new_cap;
        this->not_owned = 0;
        
        cap = this->length;
        if (new_cap < cap) {
            cap = new_cap;
        }
        this->length = cap;
        this->data = (char*)new_data;
    }
}