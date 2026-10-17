#include "dfapp.hpp"

#include <cassert>

#include "string.hpp"

enum DisplayFlags : uint32_t {
    DISPLAY_SYNCFRAMERATE   = (1 << 0),
    DISPLAY_BIT1            = (1 << 1),
    DISPLAY_FULLSCREEN      = (1 << 2),
    DISPLAY_BIT3            = (1 << 3),
    DISPLAY_SSAA2x          = (1 << 7),
    DISPLAY_SSAA4x          = (1 << 8),
};

// 0x007192a0
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

// 0x0098a940
DFApp::~DFApp() {

}

bool DFApp::FUN_10(uint32_t param_2) {
    return false;
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

// 0x0071aad0
void DFApp::CloseWindow() {
    SendMessageA(this->windows[0].hwnd, WM_CLOSE, 0, 0);
}

uint32_t DFApp::FUN_30() {
    assert(false && "DFApp::FUN_30 UNIMPLEMENTED");
    return 0;
}

// 0x00719380
void DFApp::ParseCommandLine() {
    char delimiter[2] = { ' ', '\0' };
    LPSTR cmdline = GetCommandLineA();

    // TODO: Not 100% on the string implementation
    // but everything else is fine. Come back after
    // having another look at string.
    String string(ALLOCTAG_46);
    string.Assign(cmdline);

    char* token;
    char buffer[1024];

    uint32_t length = string.length;
    if (length == 0 || (int)(length - 1) < 1) {
        token = (char*)"";
    }
    else {
        token = string.data;
        if (string.data == NULL) {
            return;
        }
    }

    strncpy(buffer, token, 1024);
    token = strtok(buffer, delimiter);

    while (token != NULL) {
        if (strcmp(token, "-width") == 0) {
            token = strtok(NULL, delimiter);
            if (token != NULL) {
                this->win_width = atoi(token);
            }
        }
        else if (strcmp(token, "-height") == 0) {
            if (token != NULL) {
                token = strtok(NULL, delimiter);
                this->win_height = atoi(token);
            }
        }
        else if (strcmp(token, "-fullscreen") == 0) {
            this->display_flags |= DISPLAY_FULLSCREEN;
        }
        else if (strcmp(token, "-window") == 0) {
            this->display_flags &= ~DISPLAY_FULLSCREEN;
        }
        else if (strcmp(token, "-syncframerate") == 0) {
            this->display_flags |= DISPLAY_SYNCFRAMERATE;
        }
        else if (strcmp(token, "-novsync") == 0) {
            this->display_flags &= ~DISPLAY_SYNCFRAMERATE;
        }
        else if (strcmp(token, "-ssaa2x") == 0) {
            this->display_flags |= DISPLAY_SSAA2x;
        }
        else if (strcmp(token, "-ssaa4x") == 0) {
            this->display_flags |= DISPLAY_SSAA4x;
        }

        token = strtok(NULL, delimiter);
    }
}