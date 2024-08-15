#include <rmx/GUI/box.h>

namespace rmx::box
{
void displayMessageOkA(LPCSTR title, LPCSTR text)
{
    MessageBoxA(nullptr, text, title, MB_OK);
}
void displayMessageOkW(LPCWSTR title, LPCWSTR text)
{
    MessageBoxW(nullptr, text, title, MB_OK);
}

void displayInfoA(LPCSTR lpInfo)
{
    displayMessageOkA(RMX_DISPLAYTITLE_INFOA, lpInfo);
}
void displayInfoW(LPCWSTR lpInfo)
{
    displayMessageOkW(RMX_DISPLAYTITLE_INFOW, lpInfo);
}

void displayErrorA(LPCSTR lpError)
{
    displayMessageOkA(RMX_DISPLAYTITLE_ERRORA, lpError);
}
void displayErrorW(LPCWSTR lpError)
{
    displayMessageOkW(RMX_DISPLAYTITLE_ERRORW, lpError);
}

void displayFatalErrorA(LPCSTR lpFatalError)
{
    displayMessageOkA(RMX_DISPLAYTITLE_FATAL_ERRORA, lpFatalError);
    abort();
}
void displayFatalErrorW(LPCWSTR lpFatalError)
{
    displayMessageOkW(RMX_DISPLAYTITLE_FATAL_ERRORW, lpFatalError);
    abort();
}

} // namespace rmx::box
