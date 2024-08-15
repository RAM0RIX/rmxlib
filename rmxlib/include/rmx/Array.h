#pragma once

#ifndef _RMX_ARRAY_H_
#define _RMX_ARRAY_H_

#include <rmx/Stack.h>

#include <rmx/File.h>
#include <rmx/LogLevel.h>

#define RMX_CHECK_OBJ_ARRAY_T_DYNAMIC_SIZE(_Array, T)                                                                  \
    {RMX_CHECK_CLASS_MEMBER_NULLPTR("rmx::Array<" #T ", DYNAMIC_SIZE>", _Array, bp, (_Array).GetBP())                  \
         RMX_CHECK_CLASS_MEMBER_NULL("rmx::Array<" #T ", DYNAMIC_SIZE>", _Array, size, (_Array).GetSize())}

#define RMX_CHECK_OBJ_ARRAY_T_S(_Array, T, S)                                                                          \
    {                                                                                                                  \
        RMX_CHECK_CLASS_MEMBER_NULLPTR("rmx::Array<" #T ", " #S ">", _Array, bp, (_Array).GetBP());                    \
        RMX_CHECK_CLASS_MEMBER_NULL("rmx::Array<" #T ", " #S ">", _Array, size, (_Array).GetSize());                   \
        if ((_Array).GetBehavior() == rmx::ARRAY::BEHAVIOR::_GROW)                                                     \
            RMX_THROW("Member behavior of fixed-sized Array<" #T ", " #S "> \'" #_Array                                \
                      "\' is set to rmx::ARRAY::BEHAVIOR::_GROW !");                                                   \
    }

namespace rmx
{
namespace ARRAY
{
constexpr size__t DYNAMIC_SIZE = 0;
enum class BEHAVIOR
{
    _RESET,
    _CLEAR,
    _SHIFT_DOWN,
    // Available for Array<T, ARRAY::DYNAMIC_SIZE> only, grows by half the size
    _GROW,
};
} // namespace ARRAY

// Array class for one data type, allocated on the stack and thus non-resizable
template <typename T, size__t S> class Array
{
  private:
    T m_bp[S];
    size__t m_offset = 0;
    ARRAY::BEHAVIOR m_behavior;

  public:
    Array() : m_offset(0), m_behavior(ARRAY::BEHAVIOR::_SHIFT_DOWN)
    {
        mem::clear(m_bp, S * sizeof(T));
    }

  public:
    Array(ARRAY::BEHAVIOR _Behavior) : m_offset(0)
    {
        SetBehavior(_Behavior);
        mem::clear(m_bp, S * sizeof(T));
    }

  public:
    ~Array()
    {
        Clear();
    }

  public:
    // Copy
    Array(const Array &_Other)
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_ARRAY_T_S(_Other, T, S);
#endif
        m_offset = _Other.m_offset;
        m_behavior = _Other.m_behavior;
        mem::copyObj<T>(m_bp, _Other.m_bp, S);
    }

  public:
    // Copy operator
    Array<T, S> &operator=(const Array &_Other)
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_ARRAY_T_S(_Other, T, S);
#endif
        if (this != &_Other)
        {
            m_offset = _Other.m_offset;
            m_behavior = _Other.m_behavior;
            mem::copyObj<T>(m_bp, _Other.m_bp, S);
        }
        return *this;
    }

  public:
    // Move
    Array(Array &&_Other)
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_ARRAY_T_S(_Other, T, S);
#endif
        m_offset = _Other.m_offset;
        m_behavior = _Other.m_behavior;
        mem::moveObj<T>(m_bp, _Other.m_bp, S);

        _Other.m_offset = 0;
        mem::clear(_Other.m_bp, S);
    }

  public:
    // Move operator
    Array<T, S> &operator=(Array &&_Other)
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_ARRAY_T_S(_Other, T, S);
#endif
        if (this != &_Other)
        {
            m_offset = _Other.m_offset;
            m_behavior = _Other.m_behavior;
            mem::moveObj<T>(m_bp, _Other.m_bp, S);

            _Other.m_offset = 0;
            mem::clear(_Other.m_bp, S);
        }
        return *this;
    }

  public:
    T &operator[](uint64__t _Index)
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_ARRAY_T_S(*this, T, S);
        if (_Index >= S)
            RMX_THROW_2ARG("Out of Bounds Access ! Trying to access index %llu of bp "
                           "but size is %llu",
                           _Index, S);
#endif
        return m_bp[_Index];
    }

  public:
    void Clear()
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_ARRAY_T_S(*this, T, S);
#endif
        for (uint64__t i = 0; i < S; i++)
        {
            m_bp[i].~T();
        }
        mem::clear(m_bp, sizeof(T) * S);
        m_offset = 0;
    }

  public:
    void Reset()
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_ARRAY_T_S(*this, T, S);
#endif
        m_offset = 0;
    }

  public:
    void ShiftDown(size__t _nElem)
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_ARRAY_T_S(*this, T, S);
        RMX_CHECK_PARAM_NULL(_nElem);
#endif
        if (_nElem >= S)
            Clear();
        else
        {
            if (m_offset < _nElem)
                m_offset = 0;
            else
                m_offset -= _nElem;
            for (size__t i = 0; i < _nElem; i++)
                m_bp[i].~T();
            mem::moveObj<T>(m_bp, &m_bp[_nElem], S - _nElem);
            mem::clear(&m_bp[S - _nElem], _nElem * sizeof(T));
        }
    }

  private:
    void Overflow()
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_ARRAY_T_S(*this, T, S);
#endif
        switch (m_behavior)
        {
        case ARRAY::BEHAVIOR::_RESET:
            Reset();
            break;

        case ARRAY::BEHAVIOR::_CLEAR:
            Clear();
            break;

        case ARRAY::BEHAVIOR::_SHIFT_DOWN:
            ShiftDown(1);
            break;
        }
    }

  public:
    ARRAY::BEHAVIOR GetBehavior() const
    {
        return m_behavior;
    }

  public:
    const void *const GetBP() const
    {
        return m_bp;
    }

  public:
    size__t GetOffset() const
    {
        return m_offset;
    }

  public:
    void SetBehavior(ARRAY::BEHAVIOR _Behavior)
    {
#ifdef RMX_DEBUG
        if (_Behavior == ARRAY::BEHAVIOR::_GROW)
            RMX_THROW("Can't set a fixed-size Array's behavior to rmx::ARRAY::BEHAVIOR::_GROW !");
#endif
        m_behavior = _Behavior;
    }

  public:
    void SetOffset(uint64__t _Offset)
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_ARRAY_T_S(*this, T, S);
        if (_Offset >= S)
            RMX_THROW_2ARG("Out of Bounds Access ! Trying to set offset to %llu "
                           "but size is %llu",
                           _Offset, S);
#endif
        m_offset = _Offset;
    }

  public:
    const T &CopyFrom(uint64__t _Index) const
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_ARRAY_T_S(*this, T, S);
        if (_Index >= S)
            RMX_THROW_2ARG("Out of Bounds Access ! Trying to access index %llu of bp "
                           "but size is %llu",
                           _Index, S);
#endif
        return m_bp[_Index];
    }

  public:
    T &&MoveFrom(uint64__t _Index)
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_ARRAY_T_S(*this, T, S);
        if (_Index >= S)
            RMX_THROW_2ARG("Out of Bounds Access ! Trying to access index %llu of bp "
                           "but size is %llu",
                           _Index, S);
#endif
        return std::move(m_bp[_Index]);
    }

  public:
    T &CopyTo(uint64__t _Index, const T &obj)
    {

#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_ARRAY_T_S(*this, T, S);
        if (_Index >= S)
            RMX_THROW_2ARG("Out of Bounds Access ! Trying to access index %llu of bp "
                           "but size is %llu",
                           _Index, S);
#endif
        m_bp[_Index] = obj;
        return m_bp[_Index];
    }

  public:
    T &MoveTo(uint64__t _Index, T &&obj)
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_ARRAY_T_S(*this, T, S);
        if (_Index >= S)
            RMX_THROW_2ARG("Out of Bounds Access ! Trying to access index %llu of bp "
                           "but size is %llu",
                           _Index, S);
#endif
        m_bp[_Index] = std::move(obj);
        return m_bp[_Index];
    }

  public:
    template <typename... Args> T &CreateTo(uint64__t _Index, Args &&..._Args)
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_ARRAY_T_S(*this, T, S);
        if (_Index >= S)
            RMX_THROW_2ARG("Out of Bounds Access ! Trying to access index %llu of bp "
                           "but size is %llu",
                           _Index, S);
#endif
        new (&m_bp[_Index]) T(std::forward<Args>(_Args)...);
        return m_bp[_Index];
    }

  public:
    void DestroyTo(uint64__t _Index)
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_ARRAY_T_S(*this, T, S);
        if (_Index >= S)
            RMX_THROW_2ARG("Out of Bounds Access ! Trying to access index %llu of bp "
                           "but size is %llu",
                           _Index, S);
#endif
        m_bp[_Index].~T();
        mem::clear(&m_bp[_Index], sizeof(T));
    }

  public:
    T &Push(const T &_Item)
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_ARRAY_T_S(*this, T, S);
#endif
        if (m_offset == S)
            Overflow();

        m_bp[m_offset] = _Item;
        return m_bp[m_offset++];
    }

  public:
    T &Push(T &&_Item)
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_ARRAY_T_S(*this, T, S);
#endif
        if (m_offset == S)
            Overflow();

        m_bp[m_offset] = std::move(_Item);
        return m_bp[m_offset++];
    }

  public:
    template <typename... Args> T &PushCreate(Args &&..._Args)
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_ARRAY_T_S(*this, T, S);
#endif
        if (m_offset == S)
            Overflow();

        new (&m_bp[m_offset]) T(std::forward<Args>(_Args)...);
        return m_bp[m_offset++];
    }

  public:
    const T &Peak() const
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_ARRAY_T_S(*this, T, S);
        if (!m_offset)
            RMX_THROW("Trying to Peak when offset is 0 !");
#endif
        return m_bp[m_offset - 1];
    }

  public:
    T &&Pop()
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_ARRAY_T_S(*this, T, S);
        if (!m_offset)
            RMX_THROW("Trying to Pop when offset is 0 !");
#endif
        return std::move(m_bp[--m_offset]);
    }

  public:
    void PopDestroy()
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_ARRAY_T_S(*this, T, S);
        if (!m_offset)
            RMX_THROW("Trying to Pop and Destroy when offset is 0 !");
#endif
        m_bp[--m_offset].~T();
        mem::clear(&m_bp[m_offset], sizeof(T));
    }
};

// Array class for one data type, allocated on the heap and thus resizable
template <typename T> class Array<T, ARRAY::DYNAMIC_SIZE>
{
  private:
    T *m_bp = nullptr;
    size__t m_size;
    size__t m_offset = 0;
    ARRAY::BEHAVIOR m_behavior;

  public:
    // Array<T, rmx::ARRAY::DYNAMIC_SIZE> specialization
    Array() = delete;
    Array(size__t _nElem) : m_behavior(ARRAY::BEHAVIOR::_GROW)
    {
        SetSize(_nElem);
    }

  public:
    Array(size__t _nElem, ARRAY::BEHAVIOR _Behavior) : m_behavior(_Behavior)
    {
        SetSize(_nElem);
    }

  public:
    ~Array()
    {
        Clear();
        mem::free_(m_bp);
    }

  public:
    // Copy
    Array(const Array &_Other)
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_ARRAY_T_DYNAMIC_SIZE(_Other, T);
#endif
        m_offset = _Other.m_offset;
        m_behavior = _Other.m_behavior;
        SetSize(_Other.m_size);

        if (m_offset)
            mem::copyObj<T>(m_bp, _Other.m_bp, m_offset);
    }

  public:
    Array<T, ARRAY::DYNAMIC_SIZE> &operator=(const Array &_Other)
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_ARRAY_T_DYNAMIC_SIZE(_Other, T);
#endif
        if (this != &_Other)
        {
            m_offset = _Other.m_offset;
            m_behavior = _Other.m_behavior;
            SetSize(_Other.m_size);

            if (m_offset)
                mem::copyObj<T>(m_bp, _Other.m_bp, m_offset);
        }
        return *this;
    }

  public:
    // Move
    Array(Array &&_Other)
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_ARRAY_T_DYNAMIC_SIZE(_Other, T);
#endif
        mem::free_(m_bp);
        m_bp = _Other.m_bp;
        m_size = _Other.m_size;
        m_offset = _Other.m_offset;
        m_behavior = _Other.m_behavior;

        _Other.m_bp = nullptr;
        _Other.m_size = 0;
        _Other.m_offset = 0;
    }

  public:
    Array<T, ARRAY::DYNAMIC_SIZE> &operator=(Array &&_Other)
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_ARRAY_T_DYNAMIC_SIZE(_Other, T);
#endif
        if (this != &_Other)
        {
            mem::free_(m_bp);
            m_bp = _Other.m_bp;
            m_size = _Other.m_size;
            m_offset = _Other.m_offset;
            m_behavior = _Other.m_behavior;

            _Other.m_bp = nullptr;
            _Other.m_size = 0;
            _Other.m_offset = 0;
        }
        return *this;
    }

  public:
    T &operator[](uint64__t _Index)
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_ARRAY_T_DYNAMIC_SIZE(*this, T);
        if (_Index >= m_offset)
            RMX_THROW_2ARG("Out of Bounds Access ! Trying to access index %llu of bp "
                           "but offset is %llu",
                           _Index, m_offset);
#endif
        return m_bp[_Index];
    }

  public:
    void Clear()
    {
        if (m_offset)
        {
            for (uint64__t i = 0; i < m_offset; i++)
            {
                m_bp[i].~T();
            }
            mem::clear(m_bp, sizeof(T) * m_offset);
        }
        m_offset = 0;
    }

  public:
    void Reset()
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_ARRAY_T_DYNAMIC_SIZE(*this, T);
#endif
        m_offset = 0;
    }

  public:
    void ShiftDown(size__t _nElem)
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_ARRAY_T_DYNAMIC_SIZE(*this, T);
        RMX_CHECK_PARAM_NULL(_nElem);
#endif
        if (_nElem >= m_offset)
            Clear();
        else
        {
            m_offset -= _nElem;
            for (size__t i = 0; i < _nElem; i++)
                m_bp[i].~T();
            mem::moveObj<T>(m_bp, &m_bp[_nElem], m_offset);
            mem::clear(&m_bp[m_offset - _nElem], _nElem * sizeof(T));
        }
    }

  private:
    void Overflow()
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_ARRAY_T_DYNAMIC_SIZE(*this, T);
#endif
        switch (m_behavior)
        {
        case ARRAY::BEHAVIOR::_RESET:
            Reset();
            break;

        case ARRAY::BEHAVIOR::_CLEAR:
            Clear();
            break;

        case ARRAY::BEHAVIOR::_SHIFT_DOWN:
            ShiftDown(1);
            break;

        case ARRAY::BEHAVIOR::_GROW:
            SetSize((m_size + 1) * 3 / 2);
            break;
        }
    }

  public:
    ARRAY::BEHAVIOR GetBehavior() const
    {
        return m_behavior;
    }

  public:
    const void *const GetBP() const
    {
        return m_bp;
    }

  public:
    size__t GetSize() const
    {
        return m_size;
    }

  public:
    size__t GetOffset() const
    {
        return m_offset;
    }

  public:
    void SetBehavior(ARRAY::BEHAVIOR _Behavior)
    {
        m_behavior = _Behavior;
    }

  private:
    void SetSize(size__t _nElem)
    {
#ifdef RMX_DEBUG
        RMX_CHECK_PARAM_NULL(_nElem);
#endif
        T *newBP = (T *)mem::allocarr(_nElem, sizeof(T));
        if (m_bp)
        {
            mem::moveObj<T>(newBP, m_bp, _nElem);
            mem::free_(m_bp);
        }
        m_bp = newBP;
        m_size = _nElem;
        if (m_offset > m_size)
            m_offset = m_size;
    }

  public:
    const T &CopyFrom(uint64__t _Index) const
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_ARRAY_T_DYNAMIC_SIZE(*this, T);
        if (_Index > m_offset)
            RMX_THROW_2ARG("Out of Bounds Access ! Trying to access index %llu of bp "
                           "but offset is %llu",
                           _Index, m_offset);
#endif
        return m_bp[_Index];
    }

  public:
    T &&MoveFrom(uint64__t _Index)
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_ARRAY_T_DYNAMIC_SIZE(*this, T);
        if (_Index > m_offset)
            RMX_THROW_2ARG("Out of Bounds Access ! Trying to access index %llu of bp "
                           "but offset is %llu",
                           _Index, m_offset);
#endif
        return std::move(m_bp[_Index]);
    }

  public:
    T &CopyTo(uint64__t _Index, const T &obj)
    {

#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_ARRAY_T_DYNAMIC_SIZE(*this, T);
        if (_Index > m_offset)
            RMX_THROW_2ARG("Out of Bounds Access ! Trying to access index %llu of bp "
                           "but offset is %llu",
                           _Index, m_offset);
#endif
        m_bp[_Index] = obj;
        return m_bp[_Index];
    }

  public:
    T &MoveTo(uint64__t _Index, T &&obj)
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_ARRAY_T_DYNAMIC_SIZE(*this, T);
        if (_Index > m_offset)
            RMX_THROW_2ARG("Out of Bounds Access ! Trying to access index %llu of bp "
                           "but offset is %llu",
                           _Index, m_offset);
#endif
        m_bp[_Index] = std::move(obj);
        return m_bp[_Index];
    }

  public:
    template <typename... Args> T &CreateTo(uint64__t _Index, Args &&..._Args)
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_ARRAY_T_DYNAMIC_SIZE(*this, T);
        if (_Index > m_offset)
            RMX_THROW_2ARG("Out of Bounds Access ! Trying to access index %llu of bp "
                           "but offset is %llu",
                           _Index, m_offset);
#endif
        new (&m_bp[_Index]) T(std::forward<Args>(_Args)...);
        return m_bp[_Index];
    }

  public:
    void DestroyTo(uint64__t _Index)
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_ARRAY_T_DYNAMIC_SIZE(*this, T);
        if (_Index >= m_offset)
            RMX_THROW_2ARG("Out of Bounds Access ! Trying to access index %llu of bp "
                           "but offset is %llu",
                           _Index, m_offset);
#endif
        m_bp[_Index].~T();
        mem::clear(&m_bp[_Index], sizeof(T));
    }

  public:
    T &Push(const T &_Item)
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_ARRAY_T_DYNAMIC_SIZE(*this, T);
#endif
        if (m_offset == m_size)
            Overflow();

        m_bp[m_offset] = _Item;
        return m_bp[m_offset++];
    }

  public:
    T &Push(T &&_Item)
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_ARRAY_T_DYNAMIC_SIZE(*this, T);
#endif
        if (m_offset == m_size)
            Overflow();

        m_bp[m_offset] = std::move(_Item);
        return m_bp[m_offset++];
    }

  public:
    template <typename... Args> T &PushCreate(Args &&..._Args)
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_ARRAY_T_DYNAMIC_SIZE(*this, T);
#endif
        if (m_offset == m_size)
            Overflow();

        new (&m_bp[m_offset]) T(std::forward<Args>(_Args)...);
        return m_bp[m_offset++];
    }

  public:
    const T &Peak() const
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_ARRAY_T_DYNAMIC_SIZE(*this, T);
        if (!m_offset)
            RMX_THROW("Trying to Peak when offset is 0 !");
#endif
        return m_bp[m_offset - 1];
    }

  public:
    T &&Pop()
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_ARRAY_T_DYNAMIC_SIZE(*this, T);
        if (!m_offset)
            RMX_THROW("Trying to Pop when offset is 0 !");
#endif
        return std::move(m_bp[--m_offset]);
    }

  public:
    void PopDestroy()
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_ARRAY_T_DYNAMIC_SIZE(*this, T);
        if (!m_offset)
            RMX_THROW("Trying to Pop and Destroy when offset is 0 !");
#endif
        m_bp[--m_offset].~T();
        mem::clear(&m_bp[m_offset], sizeof(T));
    }
};

} // namespace rmx
#endif /* _RMX_ARRAY_H_ */
