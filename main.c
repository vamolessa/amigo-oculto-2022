#define UNICODE
#define _UNICODE
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <mmsystem.h>

static void
error_dialog(const char* error_message) {
    MessageBoxA(NULL, error_message, "error", MB_ICONEXCLAMATION | MB_OK);
}

LRESULT CALLBACK
window_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HBITMAP avatar_bitmap = NULL;

    switch (uMsg) {
        case WM_CREATE: {
            avatar_bitmap = LoadBitmapA(GetModuleHandle(NULL), "AVATAR_BMP");
        } break;
        case WM_CLOSE: {
            DestroyWindow(hwnd);
        } break;
        case WM_DESTROY: {
            PostQuitMessage(0);
        } break;
        case WM_PAINT: {
            if (avatar_bitmap) {
                PAINTSTRUCT ps = {0};
                HDC hdc = BeginPaint(hwnd, &ps);

                HDC hdc_mem = CreateCompatibleDC(hdc);

                HBITMAP prev_bitmap_handle = SelectObject(hdc_mem, avatar_bitmap);
                BITMAP bitmap = {0};
                GetObject(avatar_bitmap, sizeof(bitmap), &bitmap);
                BitBlt(hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdc_mem, 0, 0, SRCCOPY);

                SelectObject(hdc_mem, prev_bitmap_handle);
                DeleteDC(hdc_mem);

                EndPaint(hwnd, &ps);
            }
        } break;
        default: return DefWindowProcW(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

int WINAPI
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    (void)hPrevInstance;
    (void)lpCmdLine;

    const wchar_t* window_class_name = L"main window class";

    HICON application_icon = LoadIconA(GetModuleHandle(NULL), "APP_ICON");
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

    PlaySoundA("THEME_WAV", GetModuleHandle(NULL), SND_ASYNC | SND_RESOURCE);

    MSG message = {0};
    while (GetMessageW(&message, NULL, 0, 0) > 0) {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    return 0;
}
