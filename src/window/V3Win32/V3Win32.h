#pragma once

#include <stdint.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include "../V3Window.h"

typedef struct win32_window Win32Window;

struct win32_window {
    V3Window parent;

    /** PRIVATE **/

    HINSTANCE hInstance;
    HWND hWnd;

    /** ------- **/
};

#define WM_RESHAPE (WM_USER + 0)
#define WM_ACTIVE  (WM_USER + 1)

// From : https://github.com/renelindsay/Vulkan-WSIWindow
// Convert native Win32 keyboard scancode to cross-platform USB HID code.
static const unsigned char WIN32_TO_HID[256] = {
      0,  0,  0,  0,  0,  0,  0,  0, 42, 43,  0,  0,  0, 40,  0,  0,    // 16
    225,224,226, 72, 57,  0,  0,  0,  0,  0,  0, 41,  0,  0,  0,  0,    // 32
     44, 75, 78, 77, 74, 80, 82, 79, 81,  0,  0,  0, 70, 73, 76,  0,    // 48
     39, 30, 31, 32, 33, 34, 35, 36, 37, 38,  0,  0,  0,  0,  0,  0,    // 64
      0,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18,    // 80
     19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29,  0,  0,  0,  0,  0,    // 96
     98, 89, 90, 91, 92, 93, 94, 95, 96, 97, 85, 87,  0, 86, 99, 84,    //112
     58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69,104,105,106,107,    //128
    108,109,110,111,112,113,114,115,  0,  0,  0,  0,  0,  0,  0,  0,    //144
     83, 71,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,    //160
    225,229,224,228,226,230,  0,  0,  0,  0,  0,  0,  0,127,128,129,    //176    L/R shift/ctrl/alt  mute/vol+/vol-
      0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 51, 46, 54, 45, 55, 56,    //192
     53,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,    //208
      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 47, 49, 48, 52,  0,    //224
      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,    //240
      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0     //256
};

int Win32Window_create(Win32Window *self, char const *name, unsigned int width, unsigned int height);
int Win32Window_destroy(Win32Window *self);
void Win32Window_pollEvent(Win32Window *self, V3Event *v3_event);