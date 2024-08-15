#include <rmx/mem.h>
namespace rmx::mem
{
    void* alloc(size__t _Size)
    {
    #ifdef RMX_DEBUG
        RMX_CHECK_PARAM_NULL(_Size);
    #endif
        void* ptr = malloc(_Size);
    #ifdef RMX_DEBUG
        if (!ptr)
            RMX_THROW_2ARG("malloc() returned nullptr with _Size(%llu), ERRNO is %s", _Size, strerror(errno));
    #endif
        return ptr;
    }
    void* allocarr(size__t _Count, size__t _Size)
    {
    #ifdef RMX_DEBUG
        RMX_CHECK_PARAM_NULL(_Count);
        RMX_CHECK_PARAM_NULL(_Size);
        if (math::isMultOverflow(_Count, _Size))
            RMX_THROW("Mult overflow !");
    #endif
        return alloc(_Count * _Size);
    }
    void* calloc_(size__t _Size)
    {
    #ifdef RMX_DEBUG
        RMX_CHECK_PARAM_NULL(_Size);
    #endif
        void* ptr = alloc(_Size);
        clear(ptr, _Size);
        return ptr;
    }
    void* callocarr(size__t _Count, size__t _Size)
    {
    #ifdef RMX_DEBUG
        RMX_CHECK_PARAM_NULL(_Count);
        RMX_CHECK_PARAM_NULL(_Size);
        if (math::isMultOverflow(_Count, _Size))
            RMX_THROW("Mult overflow !");
    #endif
        return calloc_(_Count * _Size);
    }

    void* realloc_(void* _Block, size__t _Size)
    {
    #ifdef RMX_DEBUG
        RMX_CHECK_PARAM_NULL(_Size);
    #endif
        void* ptr = realloc(_Block, _Size);
    #ifdef RMX_DEBUG
        if (!ptr)
            RMX_THROW_2ARG("relloc() returned nullptr with _Size(%llu), ERRNO is %s", _Size, strerror(errno));
    #endif
        return ptr;
    }
    void* reallocarr(void* _Block, size__t _Count, size__t _Size)
    {
    #ifdef RMX_DEBUG
        RMX_CHECK_PARAM_NULL(_Count);
        RMX_CHECK_PARAM_NULL(_Size);
        if (math::isMultOverflow(_Count, _Size))
            RMX_THROW("Mult overflow !");
    #endif
        return realloc_(_Block, _Count * _Size);
    }
    void* recalloc(void* _Block, size__t _Size)
    {
    #ifdef RMX_DEBUG
        RMX_CHECK_PARAM_NULL(_Size);
    #endif
        void* ptr = realloc_(_Block, _Size);
        clear(ptr, _Size);
        return ptr;
    }
    void* recallocarr(void* _Block, size__t _Count, size__t _Size)
    {
    #ifdef RMX_DEBUG
        RMX_CHECK_PARAM_NULL(_Count);
        RMX_CHECK_PARAM_NULL(_Size);
        if (math::isMultOverflow(_Count, _Size))
            RMX_THROW("Mult overflow !");
    #endif
        return recalloc(_Block, _Count * _Size);
    }

    void free_(void* _Block)
    {
        free(_Block);
    }

    void* clear(void* _Block, size__t _Size)
    {
    #ifdef RMX_DEBUG
        RMX_CHECK_PARAM_NULLPTR(_Block);
        RMX_CHECK_PARAM_NULL(_Size);
    #endif
        char* block = (char*)_Block;
        for (; _Size >= sizeof(uint64__t);)
        {
            *(uint64__t*)block = 0;
            _Size -= sizeof(uint64__t);
            block += sizeof(uint64__t);
        }
        if (_Size >= sizeof(uint32__t))
        {
            *(uint32__t*)block = 0;
            _Size -= sizeof(uint32__t);
            block += sizeof(uint32__t);
        }
        if (_Size >= sizeof(uint16__t))
        {
            *(uint16__t*)block = 0;
            _Size -= sizeof(uint16__t);
            block += sizeof(uint16__t);
        }
        if (_Size >= sizeof(uint8__t))
            *(uint8__t*)block = 0;
        return _Block;
    }

    void* copy(void* _Dest, const void* _Src, size__t _Size)
    {
    #ifdef RMX_DEBUG
        RMX_CHECK_PARAM_NULLPTR(_Dest);
        RMX_CHECK_PARAM_NULLPTR(_Src);
        RMX_CHECK_PARAM_NULL(_Size);
    #endif
        char* dest = (char*)_Dest;
        char* src = (char*)_Src;
        for (; _Size >= sizeof(uint64__t);)
        {
            *(uint64__t*)dest = *(uint64__t*)src;
            _Size -= sizeof(uint64__t);
            dest += sizeof(uint64__t);
        }
        if (_Size >= sizeof(uint32__t))
        {
            *(uint32__t*)dest = *(uint32__t*)src;
            _Size -= sizeof(uint32__t);
            dest += sizeof(uint32__t);
        }
        if (_Size >= sizeof(uint16__t))
        {
            *(uint16__t*)dest = *(uint16__t*)src;
            _Size -= sizeof(uint16__t);
            dest += sizeof(uint16__t);
        }
        if (_Size >= sizeof(uint8__t))
            *(uint8__t*)dest = *(uint8__t*)src;
        return _Dest;
    }



    template<> LogLevel* copyObj<LogLevel>(LogLevel* _Dest, const LogLevel* _Src, size__t _Size);
    template<> File* copyObj<File>(File* _Dest, const File* _Src, size__t _Size);

    template<> LogLevel* moveObj<LogLevel>(LogLevel* _Dest, LogLevel* _Src, size__t _Size);
    template<> File* moveObj<File>(File* _Dest, File* _Src, size__t _Size);

} // namespace rmx::mem
