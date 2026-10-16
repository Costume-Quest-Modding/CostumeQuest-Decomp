#include "dfapp.hpp"

#include <cassert>

enum DisplayFlags : uint32_t {
    DISPLAY_SYNCFRAMERATE   = (1 << 0),
    DISPLAY_BIT1            = (1 << 1),
    DISPLAY_FULLSCREEN      = (1 << 2),
    DISPLAY_BIT3            = (1 << 3),
    DISPLAY_SSAA2x          = (1 << 7),
    DISPLAY_SSAA4x          = (1 << 8),
};

DFApp::DFApp(uint32_t param_2, uint32_t width, uint32_t height) {
    this->unk5_0x14 = 0;
    this->unk6_0x18 = 0;
    this->unk2_0x8 = false;
    this->title = "CostumeQuest";
    this->windows = NULL;
    this->win_width = width;
    this->win_height = height;
    this->unk8_0x28 = true;
    this->unk9_0x29 = true;
    this->unk10_0x2c = 0.05f;
    this->width_2 = width;
    this->height_2 = height;
    this->unk13_0x38 = param_2;
    this->display_flags = DISPLAY_FULLSCREEN | DISPLAY_SYNCFRAMERATE;

    if ((param_2 & 8) != 0) {
        this->display_flags = DISPLAY_BIT3 | DISPLAY_FULLSCREEN | DISPLAY_BIT1 | DISPLAY_SYNCFRAMERATE;
    }
}

DFApp::~DFApp() {

}

uint32_t DFApp::FUN_10() {
    assert(false && "DFApp::FUN_10 UNIMPLEMENTED");
    return 0;
}

void DFApp::FUN_14() {
    assert(false && "DFApp::FUN_14 UNIMPLEMENTED");
}

void DFApp::FUN_18() {
    assert(false && "DFApp::FUN_18 UNIMPLEMENTED");
}

void DFApp::FUN_1C() {
    assert(false && "DFApp::FUN_1C UNIMPLEMENTED");
}

void DFApp::FUN_20() {
    assert(false && "DFApp::FUN_20 UNIMPLEMENTED");
}

void DFApp::FUN_24() {
    assert(false && "DFApp::FUN_24 UNIMPLEMENTED");
}

void DFApp::FUN_28() {
    assert(false && "DFApp::FUN_28 UNIMPLEMENTED");
}

void DFApp::CloseWindow() {
    assert(false && "DFApp::CloseWindow UNIMPLEMENTED");
}

uint32_t DFApp::FUN_30() {
    assert(false && "DFApp::FUN_30 UNIMPLEMENTED");
    return 0;
}

void DFApp::ParseCommandLine() {
    assert(false && "DFApp::ParseCommandLine UNIMPLEMENTED");
}