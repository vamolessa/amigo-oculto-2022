#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

LRESULT CALLBACK
window_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE: {
        } break;
        case WM_CLOSE: {
        } break;
        default: return DefWindowProcW(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

int WINAPI
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    (void)hPrevInstance;
    (void)lpCmdLine;
    (void)nCmdShow;

    const wchar_t* class_name = L"main window class";
    HICON application_icon = LoadIconA(NULL, IDI_APPLICATION);
    WNDCLASSEXW window_class = {
        .cbSize = sizeof(WNDCLASSEXW),
        .lpfnWndProc = window_proc,
        .hInstance = hInstance,
        .hIcon = application_icon,
        .hCursor = LoadCursor(NULL, IDC_ARROW),
        .hbrBackground = (HBRUSH)(COLOR_WINDOW + 1),
        .lpszClassName = class_name,
        .hIconSm = application_icon,
    };

    if (!RegisterClassExW(&window_class)) {
        MessageBoxA(NULL, "could not register window class", "error", MB_ICONEXCLAMATION | MB_OK);
        return 1;
    }

    return 0;
}
