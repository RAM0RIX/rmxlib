#pragma once

#ifndef _RMX_BOX_H_
#define _RMX_BOX_H_

#include <rmxdef.h>

const LPCSTR RMX_DISPLAYTITLE_INFOA = "INFO";
const LPCWSTR RMX_DISPLAYTITLE_INFOW = L"INFO";

const LPCSTR RMX_DISPLAYTITLE_ERRORA = "ERROR";
const LPCWSTR RMX_DISPLAYTITLE_ERRORW = L"ERROR";

const LPCSTR RMX_DISPLAYTITLE_FATAL_ERRORA = "FATAL ERROR";
const LPCWSTR RMX_DISPLAYTITLE_FATAL_ERRORW = L"FATAL ERROR \uF480";

namespace rmx
{
namespace box
{
#ifdef UNICODE
#define RMXdisplayMessageOk displayMessageOkW
#else
#define RMXdisplayMessageOk displayMessageOkA
#endif
void displayMessageOkA(LPCSTR title, LPCSTR text);
void displayMessageOkW(LPCWSTR title, LPCWSTR text);

#ifdef UNICODE
#define RMXdisplayInfo displayInfoW
#else
#define RMXdisplayInfo displayInfoA
#endif
void displayInfoA(LPCSTR lpInfo);
void displayInfoW(LPCWSTR lpInfo);

#ifdef UNICODE
#define RMXdisplayError displayErrorW
#else
#define RMXdisplayError displayErrorA
#endif
void displayErrorA(LPCSTR lpError);
void displayErrorW(LPCWSTR lpError);

#ifdef UNICODE
#define RMXdisplayFatalError displayFatalErrorW
#else
#define RMXdisplayFatalError displayFatalErrorA
#endif
void displayFatalErrorA(LPCSTR lpFatalError);
void displayFatalErrorW(LPCWSTR lpFatalError);
}; // namespace box
} // namespace rmx

#endif /* _RMX_BOX_H_ */
