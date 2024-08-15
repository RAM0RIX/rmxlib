#include <rmx/math.h>

namespace rmx
{
math::EXCEPTION math::m_except = math::EXCEPTION::_NO_EXCEPT;
math::EXCEPTION math::GetExcept()
{
    return m_except;
}

int64__t math::pow(int64__t base, int64__t exp)
{
    if (!base)
        return 0;
    if (base == 1)
        return 1;
    if (!exp)
        return 1;
    if (exp == 1)
        return base;
    int64__t result = 1;
    for (; exp; exp--)
    {
        if (isMultOverflow<int64__t>(result, base))
            return 0;
        result *= base;
    }
    return result;
}
uint64__t math::pow(uint64__t base, uint64__t exp)
{
    if (!base)
        return 0;
    if (base == 1)
        return 1;
    if (!exp)
        return 1;
    if (exp == 1)
        return base;
    uint64__t result = 1;
    for (; exp; exp--)
    {
        if (isMultOverflow<uint64__t>(result, base))
            return 0;
        result *= base;
    }
    return result;
}
} // namespace rmx
