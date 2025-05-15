#include <windows.h>
extern "C" int count = 0;
CRITICAL_SECTION cs;

BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID lpReserved) {
    switch (dwReason) {
    case DLL_PROCESS_ATTACH:
        InitializeCriticalSection(&cs);
        break;
    case DLL_PROCESS_DETACH:
        DeleteCriticalSection(&cs);
        break;
    }
    return TRUE;
}

extern "C" int Add(int n) {
    EnterCriticalSection(&cs);
    count += n;
    int result = count;
    LeaveCriticalSection(&cs);
    return result;
}

extern "C" int Sub(int n) {
    EnterCriticalSection(&cs);
    count -= n;
    int result = count;
    LeaveCriticalSection(&cs);
    return result;
}