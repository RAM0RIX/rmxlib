#pragma once

#ifndef RMX_STACK_H_
#define RMX_STACK_H_

#include <rmx/String.h>

#define RMX_CHECK_OBJ_STACK_DYNAMIC_SIZE(_Stack)                                                                       \
    {RMX_CHECK_CLASS_MEMBER_NULLPTR("rmx::Stack<DYNAMIC_SIZE>", _Stack, bp, (_Stack).GetBP())                          \
         RMX_CHECK_CLASS_MEMBER_NULL("rmx::Stack<DYNAMIC_SIZE>", _Stack, size, (_Stack).GetSize())}

#define RMX_CHECK_OBJ_STACK_S(_Stack, S)                                                                               \
    {                                                                                                                  \
        RMX_CHECK_CLASS_MEMBER_NULLPTR("rmx::Stack<" #S ">", _Stack, bp, (_Stack).GetBP());                            \
        RMX_CHECK_CLASS_MEMBER_NULL("rmx::Stack<" #S ">", _Stack, size, (_Stack).GetSize());                           \
        if ((_Stack).GetBehavior() == rmx::STACK::BEHAVIOR::_GROW)                                                     \
            RMX_THROW("Member behavior of fixed-sized Stack<" #S "> \'" #_Stack                                        \
                      "\' is set to rmx::STACK::BEHAVIOR::_GROW !");                                                   \
    }

namespace rmx
{
namespace STACK
{
constexpr size__t DYNAMIC_SIZE = 0;
enum class BEHAVIOR
{
    _RESET,
    _CLEAR,
    _SHIFT_DOWN,
    // Available for Stack<T, STACK::DYNAMIC_SIZE> only, grows by half the size
    _GROW,
};
} // namespace STACK

// Stack class for one data type, allocated on the stack and thus non-resizable
template <size__t S> class Stack
{
  private:
    byte__t m_bp[S];
    size__t m_offset = 0;
    STACK::BEHAVIOR m_behavior;

  public:
    Stack() : m_offset(0), m_behavior(STACK::BEHAVIOR::_SHIFT_DOWN)
    {
        mem::clear(m_bp, S);
    }

  public:
    Stack(STACK::BEHAVIOR _Behavior) : m_offset(0)
    {
        SetBehavior(_Behavior);
        mem::clear(m_bp, S);
    }

  public:
    ~Stack()
    {
        Clear();
    }

  public:
    // Copy
    Stack(const Stack &_Other)
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_STACK_S(_Other, S);
#endif
        m_offset = _Other.m_offset;
        m_behavior = _Other.m_behavior;
        mem::copy(m_bp, _Other.m_bp, S);
    }

  public:
    // Copy operator
    Stack<S> &operator=(const Stack &_Other)
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_STACK_S(_Other, S);
#endif
        if (this != &_Other)
        {
            m_offset = _Other.m_offset;
            m_behavior = _Other.m_behavior;
            mem::copy(m_bp, _Other.m_bp, S);
        }
        return *this;
    }

  public:
    // Move
    Stack(Stack &&_Other)
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_STACK_S(_Other, S);
#endif
        m_offset = _Other.m_offset;
        m_behavior = _Other.m_behavior;
        mem::copy(m_bp, _Other.m_bp, S);

        _Other.Clear();
    }

  public:
    // Move operator
    Stack<S> &operator=(Stack &&_Other)
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_STACK_S(_Other, S);
#endif
        if (this != &_Other)
        {
            m_offset = _Other.m_offset;
            m_behavior = _Other.m_behavior;
            mem::copy(m_bp, _Other.m_bp, S);

            _Other.Clear();
        }
        return *this;
    }

  public:
    void Clear()
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_STACK_S(*this, S);
#endif
        mem::clear(m_bp, S);
        Reset();
    }

  public:
    void Reset()
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_STACK_S(*this, S);
#endif
        m_offset = 0;
    }

  public:
    void ShiftDown(size__t _Size)
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_STACK_S(*this, S);
        RMX_CHECK_PARAM_NULL(_Size);
#endif
        if (_Size >= S)
            Clear();
        else
        {
            if (m_offset < _Size)
                m_offset = 0;
            else
                m_offset -= _Size;
            mem::copy(m_bp, &m_bp[_Size], S - _Size);
            mem::clear(&m_bp[S - _Size], _Size);
        }
    }

  private:
    void Overflow(size__t _Size)
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_STACK_S(*this, S);
        if (_Size > S)
            RMX_THROW_2ARG("Trying to push an object with a size of %llu bytes on a fixed-sized Stack of size %llu !",
                           _Size, S);
#endif
        switch (m_behavior)
        {
        case STACK::BEHAVIOR::_RESET:
            Reset();
            break;

        case STACK::BEHAVIOR::_CLEAR:
            Clear();
            break;

        case STACK::BEHAVIOR::_SHIFT_DOWN:
            ShiftDown(_Size + m_offset - S);
            break;
        }
    }

  public:
    STACK::BEHAVIOR GetBehavior() const
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
    void SetBehavior(STACK::BEHAVIOR _Behavior)
    {
#ifdef RMX_DEBUG
        if (_Behavior == STACK::BEHAVIOR::_GROW)
            RMX_THROW("Can't set a fixed-size Stack's behavior to rmx::STACK::BEHAVIOR::_GROW !");
#endif
        m_behavior = _Behavior;
    }

  public:
    void SetOffset(uint64__t _Offset)
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_STACK_S(*this, S);
        if (_Offset >= S)
            RMX_THROW_2ARG("Out of Bounds Access ! Trying to set offset to  %llu "
                           "but size is %llu",
                           _Offset, S);
#endif
        m_offset = _Offset;
    }

  public:
    template <typename T> T &Push(const T &_Item)
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_STACK_S(*this, S);
#endif
        if (sizeof(T) > S - m_offset)
            Overflow(sizeof(T));

        *reinterpret_cast<T *>(&m_bp[m_offset]) = _Item;
        m_offset += sizeof(T);
        return *reinterpret_cast<T *>(&m_bp[m_offset - sizeof(T)]);
    }

  public:
    template <typename T> T &Push(T &&_Item)
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_STACK_S(*this, S);
#endif
        if (sizeof(T) > S - m_offset)
            Overflow(sizeof(T));

        *reinterpret_cast<T *>(&m_bp[m_offset]) = std::move(_Item);
        m_offset += sizeof(T);
        return *reinterpret_cast<T *>(&m_bp[m_offset - sizeof(T)]);
    }

  public:
    template <typename T, typename... Args> T &PushCreate(Args &&..._Args)
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_STACK_S(*this, S);
#endif
        if (sizeof(T) > S - m_offset)
            Overflow(sizeof(T));

        new (*reinterpret_cast<T *>(&m_bp[m_offset])) T(std::forward<Args>(_Args)...);
        m_offset += sizeof(T);
        return *reinterpret_cast<T *>(&m_bp[m_offset - sizeof(T)]);
    }

  public:
    template <typename T> const T &Peak() const
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_STACK_S(*this, S);
        if (m_offset < sizeof(T))
            RMX_THROW_2ARG("Trying to Peak an object of size %llu when offset is %llu !", sizeof(T), m_offset);
#endif
        return *reinterpret_cast<T *>(&m_bp[m_offset - sizeof(T)]);
    }

  public:
    template <typename T> T &&Pop()
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_STACK_S(*this, S);
        if (m_offset < sizeof(T))
            RMX_THROW_2ARG("Trying to Pop an object of size %llu when offset is %llu !", sizeof(T), m_offset);
#endif
        m_offset -= sizeof(T);
        return std::move(*reinterpret_cast<T *>(&m_bp[m_offset]));
    }

  public:
    template <typename T> void PopDestroy()
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_STACK_S(*this, S);
        if (m_offset < sizeof(T))
            RMX_THROW_2ARG("Trying to Pop and Destroy an object of size %llu when offset is %llu !", sizeof(T),
                           m_offset);
#endif
        m_offset -= sizeof(T);
        reinterpret_cast<T *>(&m_bp[m_offset])->~T();
        mem::clear(&m_bp[m_offset], sizeof(T));
    }
};

// Stack<rmx::STACK::DYNAMIC_SIZE> specialization
// Stack class for one data type, allocated on the heap and thus resizable
template <> class Stack<STACK::DYNAMIC_SIZE>
{
  private:
    byte__t *m_bp = nullptr;
    size__t m_size;
    size__t m_offset = 0;
    STACK::BEHAVIOR m_behavior;

  public:
    Stack() = delete;
    // public:
    Stack(size__t _Size)
    {
        Stack(_Size, STACK::BEHAVIOR::_GROW);
    }

  public:
    Stack(size__t _Size, STACK::BEHAVIOR _Behavior) : m_behavior(_Behavior)
    {
        SetSize(_Size);
    }

  public:
    ~Stack()
    {
        Clear();
        mem::free_(m_bp);
    }

  public:
    // Copy
    Stack(const Stack &_Other)
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_STACK_DYNAMIC_SIZE(_Other);
#endif
        m_offset = _Other.m_offset;
        m_behavior = _Other.m_behavior;
        SetSize(_Other.m_size);

        if (m_offset)
            mem::copy(m_bp, _Other.m_bp, m_offset);
    }

  public:
    Stack<STACK::DYNAMIC_SIZE> &operator=(const Stack &_Other)
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_STACK_DYNAMIC_SIZE(_Other);
#endif
        if (this != &_Other)
        {
            m_offset = _Other.m_offset;
            m_behavior = _Other.m_behavior;
            SetSize(_Other.m_size);

            if (m_offset)
                mem::copy(m_bp, _Other.m_bp, m_offset);
        }
        return *this;
    }

  public:
    // Move
    Stack(Stack &&_Other)
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_STACK_DYNAMIC_SIZE(_Other);
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
    Stack<STACK::DYNAMIC_SIZE> &operator=(Stack &&_Other)
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_STACK_DYNAMIC_SIZE(_Other);
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
    void Clear()
    {
        if (m_offset)
            mem::clear(m_bp, m_size);
        m_offset = 0;
    }

  public:
    void Reset()
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_STACK_DYNAMIC_SIZE(*this);
#endif
        m_offset = 0;
    }

  public:
    void ShiftDown(size__t _Size)
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_STACK_DYNAMIC_SIZE(*this);
        RMX_CHECK_PARAM_NULL(_Size);
#endif
        if (_Size >= m_offset)
            Clear();
        else
        {
            m_offset -= _Size;
            mem::copy(m_bp, &m_bp[_Size], m_offset);
            mem::clear(&m_bp[m_offset], _Size);
        }
    }

  private:
    void Overflow(size__t _Size)
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_STACK_DYNAMIC_SIZE(*this);
        if (_Size > m_size && m_behavior != STACK::BEHAVIOR::_GROW)
            RMX_THROW_2ARG("Trying to push an object with a size of %llu bytes on a Stack of size %llu and a behavior "
                           "different than GROW !",
                           _Size, m_size);
#endif
        switch (m_behavior)
        {
        case STACK::BEHAVIOR::_RESET:
            Reset();
            break;

        case STACK::BEHAVIOR::_CLEAR:
            Clear();
            break;

        case STACK::BEHAVIOR::_SHIFT_DOWN:
            ShiftDown(_Size + m_offset - m_size);
            break;

        case STACK::BEHAVIOR::_GROW:
            SetSize((m_size + _Size) * 3 / 2);
            break;
        }
    }

  public:
    STACK::BEHAVIOR GetBehavior() const
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
    void SetBehavior(STACK::BEHAVIOR _Behavior)
    {
        m_behavior = _Behavior;
    }

  private:
    void SetSize(size__t _Size)
    {
#ifdef RMX_DEBUG
        RMX_CHECK_PARAM_NULL(_Size);
#endif
        byte__t *newBP = (byte__t *)mem::alloc(_Size);
        if (m_bp)
        {
            mem::copy(newBP, m_bp, _Size);
            mem::free_(m_bp);
        }
        m_bp = newBP;
        m_size = _Size;
        if (m_offset > m_size)
            m_offset = m_size;
    }

  public:
    template <typename T> T &Push(const T &_Item)
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_STACK_DYNAMIC_SIZE(*this);
#endif
        if (sizeof(T) > m_size - m_offset)
            Overflow(sizeof(T));

        *reinterpret_cast<T *>(&m_bp[m_offset]) = _Item;
        m_offset += sizeof(T);
        return *reinterpret_cast<T *>(&m_bp[m_offset - sizeof(T)]);
    }

  public:
    template <typename T> T &Push(T &&_Item)
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_STACK_DYNAMIC_SIZE(*this);
#endif
        if (sizeof(T) > m_size - m_offset)
            Overflow(sizeof(T));

        *reinterpret_cast<T *>(&m_bp[m_offset]) = std::move(_Item);
        m_offset += sizeof(T);
        return *reinterpret_cast<T *>(&m_bp[m_offset - sizeof(T)]);
    }

  public:
    template <typename T, typename... Args> T &PushCreate(Args &&..._Args)
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_STACK_DYNAMIC_SIZE(*this);
#endif
        if (sizeof(T) > m_size - m_offset)
            Overflow(sizeof(T));

        new (*reinterpret_cast<T *>(&m_bp[m_offset])) T(std::forward<Args>(_Args)...);
        m_offset += sizeof(T);
        return *reinterpret_cast<T *>(&m_bp[m_offset - sizeof(T)]);
    }

  public:
    template <typename T> const T &Peak() const
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_STACK_DYNAMIC_SIZE(*this);
        if (m_offset < sizeof(T))
            RMX_THROW_2ARG("Trying to Peak an object of size %llu when offset is %llu !", sizeof(T), m_offset);
#endif
        return *reinterpret_cast<T *>(&m_bp[m_offset - sizeof(T)]);
    }

  public:
    template <typename T> T &&Pop()
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_STACK_DYNAMIC_SIZE(*this);
        if (m_offset < sizeof(T))
            RMX_THROW_2ARG("Trying to Pop an object of size %llu when offset is %llu !", sizeof(T), m_offset);
#endif
        m_offset -= sizeof(T);
        return std::move(*reinterpret_cast<T *>(&m_bp[m_offset]));
    }

  public:
    template <typename T> void PopDestroy()
    {
#ifdef RMX_DEBUG
        RMX_CHECK_OBJ_STACK_DYNAMIC_SIZE(*this);
        if (m_offset < sizeof(T))
            RMX_THROW_2ARG("Trying to Pop and Destroy an object of size %llu when offset is %llu !", sizeof(T),
                           m_offset);
#endif
        m_offset -= sizeof(T);
        reinterpret_cast<T *>(&m_bp[m_offset])->~T();
        mem::clear(&m_bp[m_offset], sizeof(T));
    }
};
} // namespace rmx
#endif /* RMX_STACK_H_ */
