#pragma once

#ifndef _RMX_STR_H_
#define _RMX_STR_H_

#include <rmx/mem.h>

namespace rmx
{
namespace str
{
// Returns the length of _Str excluding the null-terminating character or _MaxCount if the string is larger than
// _MaxCount
size__t nlen(const char *_Str, size__t _MaxCount);
// Returns the length of _Str excluding the null-terminating character or _MaxCount if the string is larger than
// _MaxCount
size__t wnlen(const wchar_t *_Str, size__t _MaxCount);
// Returns the length of _Str excluding the null-terminating character
size__t len(const char *_Str);
// Returns the length of _Str excluding the null-terminating character
size__t wlen(const wchar_t *_Str);

// Returns a pointer to the null-terminating character of _Str, or &_Str[_MaxCount] is the string is larger than
// _MaxCount
const char *pnlen(const char *_Str, size__t _MaxCount);
// Returns a pointer to the null-terminating character of _Str, or &_Str[_MaxCount] is the string is larger than
// _MaxCount
const wchar_t *wpnlen(const wchar_t *_Str, size__t _MaxCount);
// Returns a pointer to the null-terminating character of _Str
const char *plen(const char *_Str);
// Returns a pointer to the null-terminating character of _Str
const wchar_t *wplen(const wchar_t *_Str);

// Copies _Count first ASCII characters of _Src in _Dest
// Adds a null character at the end of _Dest if none was find inside the first _Count ASCII characters of _Src
// MAKE SURE THAT _Dest IS AT LEAST 1 CHAR LARGER THAN _Src
char *ncopy(char *_Dest, const char *_Src, size__t _Count);
// Copies _Count first UNICODE characters of _Src in _Dest
// Adds a null character at the end of _Dest if none was find inside the first _Count UNICODE characters of _Src
// MAKE SURE THAT _Dest IS AT LEAST 1 WCHAR LARGER THAN _Src
wchar_t *wncopy(wchar_t *_Dest, const wchar_t *_Src, size__t _Count);

// Copies _Count first ASCII characters of _Src in a new string
// Allocates a string using rmx::mem::alloc(). You are responsible for freeing it using rmx::mem::free_()
// Adds a null character at the end of the new string if none was find inside the first _Count ASCII characters of _Src
char *ncopyalloc(const char *_Src, size__t _Count);
// Copies _Count first UNICODE characters of _Src in a new wstring
// Allocates a string using rmx::mem::alloc(). You are responsible for freeing it using rmx::mem::free_()
// Adds a null character at the end of the new wstring if none was find inside the first _Count UNICODE characters of
// _Src
wchar_t *wncopyalloc(const wchar_t *_Src, size__t _Count);

// Copies _Src in _Dest including null-terminating character
// MAKE SURE THAT YOUR _Src STRING IS NULL-TERMINATED
// MAKE SURE THAT _Dest IS AT LEAST 1 CHAR LARGER THAN _Str::len(_Src)
char *copy(char *_Dest, const char *_Src);
// Copies _Src in _Dest including null-terminating character
// MAKE SURE THAT YOUR _Src WSTRING IS NULL-TERMINATED
// MAKE SURE THAT _Dest IS AT LEAST 1 WCHAR LARGER THAN _Str::wlen(_Src)
wchar_t *wcopy(wchar_t *_Dest, const wchar_t *_Src);

// Copies _Count first ASCII characters of _Src in a new string
// Allocates a string using rmx::mem::alloc(). You are responsible for freeing it using rmx::mem::free_()
// Adds a null character at the end of the new string if none was find inside the first _Count ASCII characters of _Src
char *copyalloc(const char *_Src);
// Copies _Count first UNICODE characters of _Src in a new wstring
// Allocates a string using rmx::mem::alloc(). You are responsible for freeing it using rmx::mem::free_()
// Adds a null character at the end of the new wstring if none was find inside the first _Count UNICODE characters of
// _Src
wchar_t *wcopyalloc(const wchar_t *_Src);

// Converts n ASCII characters into UNICODE characters
wchar_t *natow(wchar_t *_Dest, const char *_Src, size__t _Count);
// Converts n UNICODE characters into ASCII characters
char *nwtoa(char *_Dest, const wchar_t *_Src, size__t _Count);
// Converts n ASCII characters into UNICODE characters
// Allocates a wstring using rmx::mem::alloc(). You are responsible for freeing it using rmx::mem::free_()
wchar_t *natowalloc(const char *_Str, size__t _Count);
// Converts n UNICODE characters into ASCII characters
// Allocates a string using rmx::mem::alloc(). You are responsible for freeing it using rmx::mem::free_()
char *nwtoaalloc(const wchar_t *_Str, size__t _Count);

// Converts n ASCII characters into UNICODE characters
// Includes the null-terminating character
wchar_t *atow(wchar_t *_Dest, const char *_Src);
// Converts n UNICODE characters into ASCII characters
// Includes the null-terminating character
char *wtoa(char *_Dest, const wchar_t *_Src);
// Converts n ASCII characters into UNICODE characters
// Allocates a wstring using rmx::mem::alloc(). You are responsible for freeing it using rmx::mem::free_()
// Includes the null-terminating character
wchar_t *atowalloc(const char *_Str);
// Converts n UNICODE characters into ASCII characters
// Allocates a string using rmx::mem::alloc(). You are responsible for freeing it using rmx::mem::free_()
// Includes the null-terminating character
char *wtoaalloc(const wchar_t *_Str);
}; // namespace str

} // namespace rmx

#endif /* _RMX_STR_H_ */
