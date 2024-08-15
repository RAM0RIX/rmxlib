#pragma once

#ifndef _RMX_MATH_H_
#define _RMX_MATH_H_

#include <rmxdef.h>

#define RMX_SIZE_T_MUL_OVERFLOW(a, b) (((b) != 0) && ((a) > (0xffffffffffffffff / (b))))

// Undefine C standard library defines
#undef CHAR_MIN
#undef LONG_MIN

#undef CHAR_MAX
#undef UCHAR_MAX

#undef LONG_MAX
#undef ULONG_MAX

namespace rmx
{

class math
{
  public:
    enum class EXCEPTION : error__t
    {
        _MULT_OVERFLOW,
        _NO_EXCEPT,
    };

  private:
    static EXCEPTION m_except;

  public:
    static EXCEPTION GetExcept();

  public:
    template <typename T> static bool isMultOverflow(T var1, T var2)
    {
        m_except = EXCEPTION::_NO_EXCEPT;
        if (!var1 || !var2)
        {
            return false;
        }
        if (var1 == 1 || var2 == 1)
        {
            return false;
        }
        if (!(var1 > (limits::maxVal<T>() / var2)))
        {
            return false;
        }
        m_except = EXCEPTION::_MULT_OVERFLOW;
        return true;
    }

    // Exceptions: _MULT_OVERFLOW
    static int64__t pow(int64__t base, int64__t exp);
    // Exceptions: _MULT_OVERFLOW
    static uint64__t pow(uint64__t base, uint64__t exp);
}; // namespace math

} // namespace rmx

#endif /* _RMX_MATH_H_ */
