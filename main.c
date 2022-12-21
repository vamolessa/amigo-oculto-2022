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

static void
error_dialog(const char* error_message) {
    MessageBoxA(NULL, error_message, "error", MB_ICONEXCLAMATION | MB_OK);
}

int WINAPI
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    (void)hPrevInstance;
    (void)lpCmdLine;

    const wchar_t* window_class_name = L"main window class";

    HICON application_icon = LoadIconA(NULL, IDI_APPLICATION);
    WNDCLASSEXW window_class = {
        .cbSize = sizeof(WNDCLASSEXW),
        .lpfnWndProc = window_proc,
        .hInstance = hInstance,
        .hIcon = application_icon,
        .hCursor = LoadCursor(NULL, IDC_ARROW),
        .hbrBackground = (HBRUSH)(COLOR_WINDOW + 1),
        .lpszClassName = window_class_name,
        .hIconSm = application_icon,
    };

    if (!RegisterClassExW(&window_class)) {
        error_dialog("could not register window class");
        return 1;
    }

    HWND window_handle = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        window_class_name,
        L"Amigo Oculto",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        800,
        600,
        NULL,
        NULL,
        hInstance,
        NULL
    );
    if (!window_handle) {
        error_dialog("could not create window");
        return 1;
    }

    ShowWindow(window_handle, nCmdShow);
    UpdateWindow(window_handle);

    MSG message = {0};
    while (GetMessageW(&message, NULL, 0, 0) > 0) {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    return 0;
}
