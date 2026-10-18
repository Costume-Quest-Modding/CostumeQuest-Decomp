#include "dfapp.hpp"

#include "string.hpp"

#include <tools/unimplemented.hpp>

// TODO: Check display_flags and unk13_0x38 because
// they both seem to be flags, both display related.
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
    this->window = NULL;
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

// 0x00496870
bool DFApp::FUN_10(uint32_t param_2) {
    return false;
}

// NOTE: FUN_14 to FUN_28 are all no-ops.
// The compiler folded them into a single
// function at 0x004ea700. They have no
// addresses of their own.

void DFApp::FUN_14() {

}

void DFApp::FUN_18() {

}

void DFApp::FUN_1C() {

}

void DFApp::FUN_20() {

}

void DFApp::FUN_24() {

}

void DFApp::FUN_28() {

}

// 0x0071aad0
void DFApp::CloseWindow() {
    SendMessageA(this->window->hwnd, WM_CLOSE, 0, 0);
}

// 0x0055f540
bool DFApp::FUN_30(uint32_t param_2, uint32_t param_3, uint32_t param_4, uint32_t param_5, uint32_t param_6, uint32_t param_7) {
    // TODO: Decompile
    UNIMPLEMENTED();
    return 0;
}

// 0x00719380
void DFApp::ParseCommandLine() {
    char delimiter[2] = { ' ', '\0' };
    LPSTR cmdline = GetCommandLineA();

    // UNSURE: Not 100% on the string implementation
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

DFApp* G_dfapp = NULL; // 0x00a8ff44
WindowStruct* G_window = NULL; // 0x00a8ff34

LONG WINAPI CrashHandler(EXCEPTION_POINTERS* exceptionInfo);

// 0x0071a030
bool DFApp::FUN_0071a030() {
    G_dfapp = this;

    // TODO: Define and implement this function
    SetUnhandledExceptionFilter(CrashHandler);

    HRESULT result = CoInitialize(NULL);
    if (-1 < result) {
        HINSTANCE hinstance = GetModuleHandleA(NULL);
        HICON icon = (HICON)LoadImageA(hinstance, "IDI_MAIN_ICON", IMAGE_ICON, 0, 0, 0);
        
        if (icon == NULL) {
            char filename[264];
            GetModuleFileNameA(NULL, filename, 260);
            icon = ExtractIconA(hinstance, filename, 0);
        }

        // TODO: Implement WindowProc function
        WNDCLASSA wc = {};
        wc.style = 8;
        // wc.lpfnWndProc = WindowProc;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = hinstance;
        wc.hIcon = icon;
        wc.hCursor = LoadCursorA(NULL, NULL); // 0x7f89
        wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
        wc.lpszMenuName = NULL;
        wc.lpszClassName = "DFAppClass";

        if (RegisterClassA(&wc) != 0) {
            DWORD win_style = WS_OVERLAPPEDWINDOW;
            if ((this->unk13_0x38 & 0x100) != 0) {
                win_style = WS_POPUP;
            }

            RECT win_rect;
            SetRect(&win_rect, 0, 0, this->win_width, this->win_height);
            AdjustWindowRect(&win_rect, win_style, 0);


            RECT desktop_rect;
            HWND hwnd = GetDesktopWindow();
            GetWindowRect(hwnd, &desktop_rect);

            int desktop_width = desktop_rect.right - desktop_rect.left;
            int desktop_height = desktop_rect.bottom - desktop_rect.top;

            int x = (desktop_width + (desktop_width >> 0x1f & 7U)) >> 3;
            int y = (desktop_height + (desktop_height >> 0x1f & 7U)) >> 3;

            if ((this->unk13_0x38 & 0x100) != 0) {
                x = 0;
                y = 0;
            }

            hwnd = CreateWindowExA(
                WS_EX_APPWINDOW,
                "DFAppClass", this->title,
                win_style,
                x, y,
                (int)(desktop_width * 6 + (desktop_width * 6 >> 0x1f & 7U)) >> 3,
                (int)(desktop_height * 6 + (desktop_height * 6 >> 0x1f & 7U)) >> 3,
                NULL,
                NULL,
                hinstance,
                NULL
            );

            if (hwnd != NULL) {
                WindowStruct* _window = new(ALLOCTAG_4) WindowStruct();
                if (_window != NULL) {
                    G_window = _window;

                    _window->hwnd = hwnd;
                    _window->hinstance = hinstance;
                    _window->icon = icon;
                    _window->unk4_0xc = 0;
                    _window->unk5_0x10 = 0;
                    _window->unk6_0x14 = 0;
                }

                this->window = _window;
                ShowWindow(hwnd, 5);
                ShowCursor(0);

                return true;
            }
        }

        GetLastError();
    }

    return false;
}


// UNSURE: This may want to go in another file.

#include <DbgHelp.h>

typedef BOOL (WINAPI *PFN_MiniDumpWriteDump)(
    HANDLE, DWORD, HANDLE, MINIDUMP_TYPE,
    CONST PMINIDUMP_EXCEPTION_INFORMATION,
    CONST PMINIDUMP_USER_STREAM_INFORMATION,
    CONST PMINIDUMP_CALLBACK_INFORMATION);

// 0x00719e80
LONG WINAPI CrashHandler(EXCEPTION_POINTERS* exceptionInfo) {    
    MEMORYSTATUS mem_status;
    GlobalMemoryStatus(&mem_status);

    char module_path[264];
    char crash_name[256];
    char file_name[512];

    sprintf(crash_name, "Crash: 0x%08x", (int)exceptionInfo->ExceptionRecord->ExceptionCode);

    // TODO: Looks like some object
    // if ((int)DAT_00a99fc0 < 4) {
    //     *(char **)(&DAT_00a99fb0 + DAT_00a99fc0 * 4) = crash_name;
    //     DAT_00a99fc0 = DAT_00a99fc0 + 1;
    // }

    HMODULE dbghelp = NULL;
    WORD result = GetModuleFileNameA(NULL, module_path, sizeof(module_path) - 4);

    if (result == 0) {
        dbghelp = LoadLibraryA("DBGHELP.DLL");
        if (dbghelp == NULL) goto end;
    }
    else {
        char* last_slash = strchr(module_path, '\\');
        if (last_slash == NULL) goto end;

        strncpy(last_slash + 1, "DBGHELP.DLL", sizeof("DBGHELP.DLL"));
        dbghelp = LoadLibraryA(module_path);

        if (dbghelp == NULL) goto end;
    }

    PFN_MiniDumpWriteDump pfn_MiniDumpWriteDump = (PFN_MiniDumpWriteDump)GetProcAddress(dbghelp, "MiniDumpWriteDump");
    if (pfn_MiniDumpWriteDump != 0) {
        snprintf(file_name, sizeof(file_name) - 1, "DFDump%c%d-%d.tdmp", 'R', 1, 0x7ff53);

        HANDLE dump_file = CreateFileA(file_name, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (dump_file != INVALID_HANDLE_VALUE) {
            HANDLE proc = GetCurrentProcess();
            DWORD proc_id = GetCurrentProcessId();

            MINIDUMP_EXCEPTION_INFORMATION mdei;
            mdei.ThreadId = GetCurrentThreadId();
            mdei.ExceptionPointers = exceptionInfo;
            mdei.ClientPointers = 1;

            pfn_MiniDumpWriteDump(proc, proc_id, dump_file, MiniDumpNormal, &mdei, NULL, NULL);
        }
    }

    end:
    // TODO: Some object or something
    // if (DAT_00a99f84 != (code *)0x0) {
    //     (*DAT_00a99f84)(0,&DAT_00a99fc4,"Callstack",1);
    // }
    // DAT_00a99fc0 = ((int)(DAT_00a99fc0 - 1) < 0) - 1 & DAT_00a99fc0 - 1;
    Sleep(250);
    return EXCEPTION_EXECUTE_HANDLER;
}