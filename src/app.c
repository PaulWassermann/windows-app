#include "app.h"
#include "..\log.h"

LRESULT CALLBACK AppProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    AppData *data;
    HDC hDeviceContext;
    PAINTSTRUCT paintStruct;

    if (uMsg == WM_CREATE) {
        CREATESTRUCT *cStruct = (CREATESTRUCT *)lParam;
        data = (AppData *)cStruct->lpCreateParams;
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)data);
    } else {
        data = (AppData *)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    }

    switch(uMsg)
    {
        case WM_CLOSE:
        {
            DestroyWindow(hwnd);
            return 0;
        }
        case WM_COMMAND:
        {
            if (HIWORD(wParam) == BN_CLICKED) {                
                LOG_DEBUG("Button %d pushed !\n", LOWORD(wParam));
                LOG_DEBUG("App description: %s\n", data->desc);
                return 0;
            }
            return 0;
        }
        case WM_DESTROY:
        {   
            FreeConsole();
            PostQuitMessage(EXIT_SUCCESS);
            return 0;
        }
        case WM_PAINT:
        {
            RECT rect;
            hDeviceContext = BeginPaint(hwnd, &paintStruct);
            FillRect(hDeviceContext, &paintStruct.rcPaint, (HBRUSH) (COLOR_WINDOW + 1));
            GetClientRect(hwnd, &rect);
            DrawText(hDeviceContext, (LPCSTR) L"Welcome to GeoDataProcessing !", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
            EndPaint(hwnd, &paintStruct);
            return 0;
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

HWND CreateApp(HINSTANCE hInstance) {
    WNDCLASS wc = { 0 };

    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    wc.lpfnWndProc   = AppProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = (LPCWSTR) CLASS_NAME;

    RegisterClass(&wc);

    AppData data = { .desc = "Windows App"};

    HWND hwnd = CreateWindowExW(
        0,                              // Optional window styles.
        (LPCWSTR) CLASS_NAME,                     // Window class
        L"Learn to program Windows",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style
        // X, Y, W, H
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        &data       // Additional application data
    );

    if (hwnd == NULL) {
        printf("Hello, %lu\n", GetLastError());
        LOG_ERROR("Could not create window for App: %lu\n", GetLastError());
        exit(EXIT_FAILURE);
    }
    printf("Hello\n");

    return hwnd;
}