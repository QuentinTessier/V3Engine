#include "V3Win32.h"

static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
        case WM_CLOSE:
            PostMessage(hWnd, WM_CLOSE, 0, 0);  // for OnCloseEvent
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_PAINT:
            // printf("WM_PAINT\n");
            return 0;
        case WM_GETMINMAXINFO:  // set window's minimum size
            // ((MINMAXINFO*)lParam)->ptMinTrackSize = demo.minsize;
            return 0;
        case WM_EXITSIZEMOVE : { PostMessage(hWnd, WM_RESHAPE, 0, 0);          break; }
        case WM_ACTIVATE     : { PostMessage(hWnd, WM_ACTIVE, wParam, lParam); break; }
        default: break;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int Win32Window_create(Win32Window *self, char const *name, u32 width, u32 height)
{
    self->hInstance = GetModuleHandle(0);

    WNDCLASSEX win_class;
    win_class.cbSize        = sizeof(WNDCLASSEX);
    win_class.style         = CS_HREDRAW | CS_VREDRAW;
    win_class.lpfnWndProc   = WndProc;
    win_class.cbClsExtra    = 0;
    win_class.cbWndExtra    = 0;
    win_class.hInstance     = self->hInstance;
    win_class.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    win_class.hCursor       = LoadCursor(NULL, IDC_ARROW);
    win_class.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    win_class.lpszMenuName  = NULL;
    win_class.lpszClassName = name;
    win_class.hIconSm       = LoadIcon(NULL, IDI_WINLOGO);

    ATOM atom = RegisterClassEx(&win_class);
    if (atom == 0)
        return 0;

    RECT wr = {0, 0, (LONG)width, (LONG)height};
    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);
    self->hWnd = CreateWindowEx(0,
                                name,
                                name,
                                WS_VISIBLE | WS_SYSMENU | WS_OVERLAPPEDWINDOW,
                                100, 100,
                                wr.right - wr.left,
                                wr.bottom - wr.top,
                                NULL,
                                NULL,
                                self->hInstance,
                                NULL);
    if (self->hWnd == 0)
        return 0;
    return 1;
}

int Win32Window_destroy(Win32Window *self)
{
    DestroyWindow(self->hWnd);
    return 1;
}

static void Win32Window_convertEvent(Win32Window *self, MSG msg, V3Event *v3_event)
{
    int16_t x = GET_X_LPARAM(msg.lParam);
    int16_t y = GET_Y_LPARAM(msg.lParam);

    if (msg.message == WM_KEYDOWN || msg.message == WM_KEYUP) {
        if (msg.wParam == VK_CONTROL) msg.wParam = (msg.lParam & (1 << 24)) ? VK_RCONTROL : VK_LCONTROL;
        if (msg.wParam == VK_SHIFT) {
            //if (!!(GetKeyState(VK_LSHIFT) & 128) != KeyState(KEY_LeftShift)) PostMessage(hWnd, msg.message, VK_LSHIFT, 0);
            //if (!!(GetKeyState(VK_RSHIFT) & 128) != KeyState(KEY_RightShift)) PostMessage(hWnd, msg.message, VK_RSHIFT, 0);
            v3_event->type = V3EVENT_NONE;
            return;
        }
    } else if (msg.message == WM_SYSKEYDOWN || msg.message == WM_SYSKEYUP) {
        if (msg.wParam == VK_MENU) msg.wParam = (msg.lParam & (1 << 24)) ? VK_RMENU : VK_LMENU;
    }
    switch (msg.message) {
        case WM_MOUSEMOVE:
            v3_event->type = V3EVENT_MOUSE_MOVE;
            v3_event->vec[0] = x;
            v3_event->vec[1] = y;
            return;
        case WM_LBUTTONDOWN:
            v3_event->type = V3EVENT_MOUSE_BUTTON_PRESSED;
            v3_event->mouseButton.id = 1;
            v3_event->mouseButton.pos[0] = x;
            v3_event->mouseButton.pos[1] = y;
            return;
        case WM_MBUTTONDOWN:
            v3_event->type = V3EVENT_MOUSE_BUTTON_PRESSED;
            v3_event->mouseButton.id = 2;
            v3_event->mouseButton.pos[0] = x;
            v3_event->mouseButton.pos[1] = y;
            return;
        case WM_RBUTTONDOWN:
            v3_event->type = V3EVENT_MOUSE_BUTTON_PRESSED;
            v3_event->mouseButton.id = 3;
            v3_event->mouseButton.pos[0] = x;
            v3_event->mouseButton.pos[1] = y;
            return;
        case WM_LBUTTONUP  :
            v3_event->type = V3EVENT_MOUSE_BUTTON_RELEASED;
            v3_event->mouseButton.id = 1;
            v3_event->mouseButton.pos[0] = x;
            v3_event->mouseButton.pos[1] = y;
            return;
        case WM_MBUTTONUP  :
            v3_event->type = V3EVENT_MOUSE_BUTTON_RELEASED;
            v3_event->mouseButton.id = 2;
            v3_event->mouseButton.pos[0] = x;
            v3_event->mouseButton.pos[1] = y;
            return;
        case WM_RBUTTONUP  :
            v3_event->type = V3EVENT_MOUSE_BUTTON_RELEASED;
            v3_event->mouseButton.id = 3;
            v3_event->mouseButton.pos[0] = x;
            v3_event->mouseButton.pos[1] = y;
            return;
        case WM_KEYDOWN   :
            v3_event->type = V3EVENT_KEY_PRESSED;
            v3_event->key = WIN32_TO_HID[msg.wParam];
            return;
        case WM_KEYUP     :
            v3_event->type = V3EVENT_KEY_RELEASED;
            v3_event->key = WIN32_TO_HID[msg.wParam];
            return;
        case WM_SYSKEYDOWN: {
                MSG discard; GetMessage(&discard, NULL, 0, 0);
                v3_event->type = V3EVENT_KEY_PRESSED;
                v3_event->key = WIN32_TO_HID[msg.wParam];
            }
            return;
        case WM_SYSKEYUP:
            v3_event->type = V3EVENT_KEY_RELEASED;
            v3_event->key = WIN32_TO_HID[msg.wParam];
            return;
        case WM_ACTIVE:
            v3_event->type = V3EVENT_FOCUS;
            v3_event->asFocus = msg.wParam != WA_INACTIVE;
            return;
        case WM_CLOSE:
            v3_event->type = V3EVENT_CLOSE;
            return;
    }
    return;
}

void Win32Window_pollEvent(Win32Window *self, V3Event *v3_event)
{
    MSG msg = {};

    if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE) > 0) {
        TranslateMessage(&msg);
        Win32Window_convertEvent(self, msg, v3_event);
        DispatchMessage(&msg);
        return;
    }
    v3_event->type = V3EVENT_NONE;
    return;
}

