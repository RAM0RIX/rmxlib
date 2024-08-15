#include <rmx/str.h>

namespace rmx::str
{
size__t nlen(const char *_Str, size__t _MaxCount)
{
#ifdef RMX_DEBUG
    RMX_CHECK_PARAM_NULLPTR(_Str);
    RMX_CHECK_PARAM_NULL(_MaxCount);
#endif
    size__t i = 0;
    for (; _Str[i] != 0 && i < _MaxCount; i++)
        ;
    return i;
}
size__t wnlen(const wchar_t *_Str, size__t _MaxCount)
{
#ifdef RMX_DEBUG
    RMX_CHECK_PARAM_NULLPTR(_Str);
    RMX_CHECK_PARAM_NULL(_MaxCount);
#endif
    size__t i = 0;
    for (; _Str[i] != 0 && i < _MaxCount; i++)
        ;
    return i;
}

size__t len(const char *_Str)
{
#ifdef RMX_DEBUG
    RMX_CHECK_PARAM_NULLPTR(_Str);
#endif
    return nlen(_Str, limits::maxVal<size__t>());
}
size__t wlen(const wchar_t *_Str)
{
#ifdef RMX_DEBUG
    RMX_CHECK_PARAM_NULLPTR(_Str);
#endif
    return wnlen(_Str, limits::maxVal<size__t>());
}

const char *pnlen(const char *_Str, size__t _MaxCount)
{
#ifdef RMX_DEBUG
    RMX_CHECK_PARAM_NULLPTR(_Str);
    RMX_CHECK_PARAM_NULL(_MaxCount);
#endif
    return &_Str[nlen(_Str, _MaxCount)];
}
const wchar_t *wpnlen(const wchar_t *_Str, size__t _MaxCount)
{
#ifdef RMX_DEBUG
    RMX_CHECK_PARAM_NULLPTR(_Str);
    RMX_CHECK_PARAM_NULL(_MaxCount);
#endif
    return &_Str[wnlen(_Str, _MaxCount)];
}
const char *plen(const char *_Str)
{
#ifdef RMX_DEBUG
    RMX_CHECK_PARAM_NULLPTR(_Str);
#endif
    return pnlen(_Str, limits::maxVal<size__t>());
}
const wchar_t *wplen(const wchar_t *_Str)
{
#ifdef RMX_DEBUG
    RMX_CHECK_PARAM_NULLPTR(_Str);
#endif
    return wpnlen(_Str, limits::maxVal<size__t>());
}

char *ncopy(char *_Dest, const char *_Src, size__t _Count)
{
#ifdef RMX_DEBUG
    RMX_CHECK_PARAM_NULLPTR(_Dest);
    RMX_CHECK_PARAM_NULLPTR(_Src);
    RMX_CHECK_PARAM_NULL(_Count);
#endif
    bool nullChar = false;
    for (uint64__t i = 0; i < _Count; i++)
    {
        _Dest[i] = _Src[i];
        if (!_Src[i])
            nullChar = true;
    }
    if (!nullChar)
        _Dest[_Count] = 0;
    return _Dest;
}
wchar_t *wncopy(wchar_t *_Dest, const wchar_t *_Src, size__t _Count)
{
#ifdef RMX_DEBUG
    RMX_CHECK_PARAM_NULLPTR(_Dest);
    RMX_CHECK_PARAM_NULLPTR(_Src);
    RMX_CHECK_PARAM_NULL(_Count);
#endif
    bool nullChar = false;
    for (uint64__t i = 0; i < _Count; i++)
    {
        _Dest[i] = _Src[i];
        if (!_Src[i])
            nullChar = true;
    }
    if (!nullChar)
        _Dest[_Count] = 0;
    return _Dest;
}

char *ncopyalloc(const char *_Src, size__t _Count)
{
#ifdef RMX_DEBUG
    RMX_CHECK_PARAM_NULLPTR(_Src);
    RMX_CHECK_PARAM_NULL(_Count);
#endif
    return ncopy((char *)mem::allocarr(nlen(_Src, _Count) + 1, sizeof(char)), _Src, nlen(_Src, _Count));
}

wchar_t *wncopyalloc(const wchar_t *_Src, size__t _Count)
{
#ifdef RMX_DEBUG
    RMX_CHECK_PARAM_NULLPTR(_Src);
    RMX_CHECK_PARAM_NULL(_Count);
#endif
    return wncopy((wchar_t *)mem::allocarr(wnlen(_Src, _Count), sizeof(wchar_t)), _Src, wnlen(_Src, _Count));
}

char *copy(char *_Dest, const char *_Src)
{
#ifdef RMX_DEBUG
    RMX_CHECK_PARAM_NULLPTR(_Dest);
    RMX_CHECK_PARAM_NULLPTR(_Src);
#endif
    size__t length = len(_Src);
#ifdef RMX_DEBUG
    RMX_CHECK_NULL(length);
#endif
    return ncopy(_Dest, _Src, length);
}
wchar_t *wcopy(wchar_t *_Dest, const wchar_t *_Src)
{
#ifdef RMX_DEBUG
    RMX_CHECK_PARAM_NULLPTR(_Dest);
    RMX_CHECK_PARAM_NULLPTR(_Src);
#endif
    size__t length = wlen(_Src);
#ifdef RMX_DEBUG
    RMX_CHECK_NULL(length);
#endif
    return wncopy(_Dest, _Src, length);
}

char *copyalloc(const char *_Str)
{
#ifdef RMX_DEBUG
    RMX_CHECK_PARAM_NULL(_Str);
#endif
    size__t length = len(_Str);
#ifdef RMX_DEBUG
    RMX_CHECK_NULL(length);
#endif
    return ncopyalloc(_Str, length);
}

wchar_t *wcopyalloc(const wchar_t *_Str)
{
#ifdef RMX_DEBUG
    RMX_CHECK_PARAM_NULL(_Str);
#endif
    size__t length = wlen(_Str);
#ifdef RMX_DEBUG
    RMX_CHECK_NULL(length);
#endif
    return wncopyalloc(_Str, length);
}

wchar_t *natow(wchar_t *_Dest, const char *_Src, size__t _Count)
{
#ifdef RMX_DEBUG
    RMX_CHECK_PARAM_NULLPTR(_Dest);
    RMX_CHECK_PARAM_NULLPTR(_Src);
    RMX_CHECK_PARAM_NULL(_Count);
#endif
    // Code coming soon
    return nullptr;
}
char *nwtoa(char *_Dest, const wchar_t *_Src, size__t _Count)
{
#ifdef RMX_DEBUG
    RMX_CHECK_PARAM_NULLPTR(_Dest);
    RMX_CHECK_PARAM_NULLPTR(_Src);
    RMX_CHECK_PARAM_NULL(_Count);
#endif
    // Code coming soon
    return nullptr;
}

wchar_t *natowalloc(const char *_Str, size__t _Count)
{
#ifdef RMX_DEBUG
    RMX_CHECK_PARAM_NULLPTR(_Str);
    RMX_CHECK_PARAM_NULL(_Count);
#endif
    return natow((wchar_t *)mem::allocarr(_Count + 1, sizeof(wchar_t)), _Str, _Count);
}
char *nwtoaalloc(const wchar_t *_Str, size__t _Count)
{
#ifdef RMX_DEBUG
    RMX_CHECK_PARAM_NULLPTR(_Str);
    RMX_CHECK_PARAM_NULL(_Count);
#endif
    return nwtoa((char *)mem::allocarr(_Count + 1, sizeof(char)), _Str, _Count);
}

wchar_t *atow(wchar_t *_Dest, const char *_Src)
{
#ifdef RMX_DEBUG
    RMX_CHECK_PARAM_NULLPTR(_Dest);
    RMX_CHECK_PARAM_NULLPTR(_Src);
#endif
    size__t length = len(_Src);
#ifdef RMX_DEBUG
    RMX_CHECK_NULL(length);
#endif
    return natow(_Dest, _Src, length);
}
char *wtoa(char *_Dest, const wchar_t *_Src)
{
#ifdef RMX_DEBUG
    RMX_CHECK_PARAM_NULLPTR(_Dest);
    RMX_CHECK_PARAM_NULLPTR(_Src);
#endif
    size__t length = wlen(_Src);
#ifdef RMX_DEBUG
    RMX_CHECK_NULL(length);
#endif
    return nwtoa(_Dest, _Src, length);
}

wchar_t *atowalloc(const char *_Str)
{
#ifdef RMX_DEBUG
    RMX_CHECK_PARAM_NULLPTR(_Str);
#endif
    size__t length = len(_Str);
#ifdef RMX_DEBUG
    RMX_CHECK_NULL(length);
#endif
    return natowalloc(_Str, length);
}
char *wtoaalloc(const wchar_t *_Str)
{
#ifdef RMX_DEBUG
    RMX_CHECK_PARAM_NULLPTR(_Str);
#endif
    size__t length = wlen(_Str);
#ifdef RMX_DEBUG
    RMX_CHECK_NULL(length);
#endif
    return nwtoaalloc(_Str, length);
}

} // namespace rmx::str
