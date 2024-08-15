#pragma once

#ifndef _RMX_TYPES_H_
#define _RMX_TYPES_H_

namespace rmx
{
/* Basic defines for numbers */
typedef unsigned char byte__t;
typedef signed char int8__t;
typedef unsigned char uint8__t;
typedef unsigned char size8__t;

typedef unsigned short word__t;
typedef signed short int16__t;
typedef unsigned short uint16__t;
typedef unsigned short size16__t;
typedef unsigned short index__t;

typedef unsigned long dword__t;
typedef signed long int32__t;
typedef unsigned long uint32__t;
typedef unsigned long size32__t;

typedef unsigned long long qword__t;
typedef signed long long int64__t;
typedef unsigned long long uint64__t;
typedef unsigned long long size__t;

/* String types */

// String pointer types
typedef char *pstr__t, *lpstr__t;
typedef const char *pcstr__t, *lpcstr__t;

typedef wchar_t *pwstr__t, *lpwstr__t;
typedef const wchar_t *pcwstr__t, *lpcwstr__t;

// Macros to be able to switch between UNICODE and ANSI charsets
#ifdef UNICODE
typedef wchar_t char__t;

#define RMX_STR(string) L##string // Convert ASCII string to Unicode string if enabled
/* #define STRCPY rmx::str::wcopy */
/* #define STRLEN rmx::str::wlen */
#else
typedef char char__t;

#define RMX_STR(string) string // Default ASCII string
/* #define STRCPY rmx::str::copy */
/* #define STRLEN rmx::str::len */
#endif

enum RMX_STR_SIZE
{
    CHAR = 1,
    WCHAR = 2
};

typedef char__t *ptstr__t, *lptstr__t;
typedef const char__t *pctstr__t, *lpctstr__t;

// ErrorStacks typedefs
typedef uint16__t error__t;

// Colors typedefs
typedef uint32__t color__t;

#if !defined(_WINDOWS_) || defined(WIN32_LEAN_AND_MEAN) // Windows types (aren't declared if Windows.h was already
                                                        // included) Basic types typedefs
typedef byte__t BYTE;
typedef word__t WORD;
typedef dword__t DWORD;
typedef qword__t QWORD;

// Windows string pointer types
typedef char *PSTR, *LPSTR;
typedef const char *PCSTR, *LPCSTR;

typedef wchar_t *PWSTR, *LPWSTR;
typedef const wchar_t *PCWSTR, *LPCWSTR;

#ifdef UNICODE
typedef wchar_t TCHAR;
#else
typedef char TCHAR;
#endif

typedef TCHAR *PTSTR, *LPTSTR;
typedef const TCHAR *PCTSTR, *LPCTSTR;

#endif
} // namespace rmx

#endif /* _RMX_TYPES_H_ */
