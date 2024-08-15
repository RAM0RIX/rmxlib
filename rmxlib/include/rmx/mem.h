#pragma once

#ifndef _RMX_MEMORY_H_
#define _RMX_MEMORY_H_

#include <malloc.h>
#include <utility> // For std::move()

#include <rmxdef.h>
#include <rmx/math.h>
#include <rmx/File.h>

namespace rmx
{
    namespace mem
    {
        inline auto move = [](auto&& x) -> decltype(auto) { return std::move(x); };
        // Calls stdlib malloc()
        void* alloc(size__t _Size);
        void* allocarr(size__t _Count, size__t _Size);

        // Calls mem::alloc(), not stdlib calloc()
        void* calloc_(size__t _Size);
        void* callocarr(size__t _Count, size__t _Size);

        // Calls stdlib realloc()
        void* realloc_(void* _Block, size__t _Size);
        void* reallocarr(void* _Block, size__t _Count, size__t _Size);
        void* recalloc(void* _Block, size__t _Size);
        void* recallocarr(void* _Block, size__t _Count, size__t _Size);

        // Calls stdlib free()
        void free_(void* _Block);

        void* clear(void* _Block, size__t _Size);

        // Much faster than copy<T>()
        void* copy(void* _Dest, const void* _Src, size__t _Size);

        template <typename T> T* copyObj(T* _Dest, const T* _Src, size__t _Count)
        {
        #ifdef RMX_DEBUG
            RMX_CHECK_PARAM_NULLPTR(_Dest);
            RMX_CHECK_PARAM_NULLPTR_T(_Src, T);
            RMX_CHECK_PARAM_NULL(_Count);
        #endif
            for (uint64__t i = 0; i < _Count; i++)
                _Dest[i] = _Src[i];
            return _Dest;
        }

        template <typename T> T* moveObj(T* _Dest, T* _Src, size__t _Count)
        {
        #ifdef RMX_DEBUG
            RMX_CHECK_PARAM_NULLPTR(_Dest);
            RMX_CHECK_PARAM_NULLPTR_T(_Src, T);
            RMX_CHECK_PARAM_NULL(_Count);
        #endif
            for (uint64__t i = 0; i < _Count; i++)
                _Dest[i] = std::move(_Src[i]);
            return _Dest;
        }

    }; // namespace mem

} // namespace rmx

#endif /* _RMX_MEMORY_H_ */
