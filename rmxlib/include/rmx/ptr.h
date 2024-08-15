#pragma once
#ifndef _RMX_PTR_H_
#define _RMX_PTR_H_

#include <rmx/mem.h>

namespace rmx
{
template <typename T> class ptr
{
  public:
    T *m_ptr;
    size__t m_size;

  public:
    ptr() : m_ptr(nullptr), m_size(0)
    {
    }
    ptr(void *_Address, size__t _Size) : m_ptr(_Address), m_size(_Size)
    {
    }
    ~ptr()
    {
        mem::free_(m_ptr);
    }

    ptr(const ptr &_Other) = delete;
    ptr &operator=(const ptr &_Other) = delete;

    ptr(ptr &&_Other) : m_ptr(_Other.m_ptr), m_size(_Other.m_size)
    {
        _Other.m_ptr = nullptr;
        _Other.m_size = 0;
    }
    ptr &operator=(ptr &&_Other)
    {
        if (this != &_Other)
        {
            m_ptr = _Other.m_ptr;
            m_size = _Other.m_size;

            _Other.m_ptr = nullptr;
            _Other.m_size = 0;
        }
        return *this;
    }

  public:
    operator T *()
    {
        return m_ptr;
    }
    T operator->()
    {
        return *m_ptr;
    }
    T *operator++()
    {
        return m_ptr++;
    }
    T *operator--()
    {
        return m_ptr--;
    }
};
} // namespace rmx

#endif /* _RMX_PTR_H_ */
