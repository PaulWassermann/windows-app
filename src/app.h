#ifndef APP_H
#define APP_H

#include <windows.h>

typedef struct AppData {
    char *desc;
} AppData;

LRESULT CALLBACK AppProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HWND CreateApp(HINSTANCE hInstance);

#endif