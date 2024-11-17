#ifndef UNICODE
#define UNICODE
#endif
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>

#include "log.h"
#include "src\app.h"

void init_console();

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE HPrevHinstance, PWSTR pCmdLine, int nCmdShow) {
    init_console();

    printf("Hello\n");
    HWND hwndApp = CreateApp(hInstance);

    HWND button_hwnd = CreateWindowEx(
        0,
        L"BUTTON",
        L"Print debug message",
        WS_VISIBLE | WS_CHILD | BS_MULTILINE | BS_PUSHBUTTON,
        10, 10, 100, 100,
        hwndApp,
        NULL,
        (HINSTANCE) GetWindowLongPtr(hwndApp, GWLP_HINSTANCE),
        NULL
    );

    if (button_hwnd == 0) {
        exit(EXIT_FAILURE);
    }
    printf("Hello\n");

    ShowWindow(hwndApp, nCmdShow);

    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return EXIT_SUCCESS;
}

void init_console() {
    BOOL attach_result = AttachConsole(ATTACH_PARENT_PROCESS);

    if (attach_result == FALSE) {
        DWORD err = GetLastError();
        
        if (err == ERROR_ACCESS_DENIED) {
            LOG_ERROR("Current process already has a console attached to it.\n", NULL);
        } else if (err == ERROR_INVALID_HANDLE) {
            LOG_ERROR("Parent process does not have a console attached to it.\n", NULL);
            AllocConsole();
        }
    }

    freopen("CON", "a", stdout);
    freopen("CON", "a", stderr);
}
