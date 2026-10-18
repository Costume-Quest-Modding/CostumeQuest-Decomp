#ifndef HPP_CQ_DFAPP
#define HPP_CQ_DFAPP

#include <windows.h>

#include <cstdint>

// TODO: Swap out byte[n] for undefined individual bytes as the DFApp padding.

// TODO: Rename all unknown fields to unk{n}_{offset} in ghidra.

struct WindowStruct {
    HWND hwnd;
    HINSTANCE hinstance;
    HICON hicon;
    uint32_t unk4_0xc;
    uint32_t unk5_0x10;
    uint32_t unk6_0x14;
};

class DFApp {
public:
    uint32_t unk1_0x4;
    bool unk2_0x8;
    const char* title;
    WindowStruct* window;
    uint32_t unk5_0x14;
    uint64_t unk6_0x18;
    uint32_t win_width;
    uint32_t win_height;
    bool unk8_0x28;
    bool unk9_0x29;
    float unk10_0x2c;
    uint32_t width_2;           // NOTE: I think these may be something like render surface
    uint32_t height_2;
    uint32_t unk13_0x38;
    uint32_t display_flags;

    DFApp(uint32_t param_2, uint32_t width, uint32_t height);
    virtual ~DFApp();

    virtual uint32_t FUN_04() = 0;
    virtual void FUN_08() = 0;
    virtual void FUN_0C(uint32_t param_2) = 0;

    virtual bool FUN_10(uint32_t param_2);
    virtual void FUN_14();
    virtual void FUN_18();
    virtual void FUN_1C();
    virtual void FUN_20();
    virtual void FUN_24();
    virtual void FUN_28();
    virtual void CloseWindow();
    virtual bool FUN_30(uint32_t param_2, uint32_t param_3, uint32_t param_4, uint32_t param_5, uint32_t param_6, uint32_t param_7);
    virtual void ParseCommandLine();
};

#endif