#include <rmx/limits.h>

namespace rmx
{
namespace limits
{
template <typename T> T minVal()
{
    return std::numeric_limits<T>::min();
}

template <> int8__t minVal<int8__t>()
{
    return INT8__T_MIN;
}
template <> uint8__t minVal<uint8__t>()
{
    return UINT8__T_MIN;
}
template <> int16__t minVal<int16__t>()
{
    return INT16__T_MIN;
}
template <> uint16__t minVal<uint16__t>()
{
    return UINT16__T_MIN;
}
template <> int32__t minVal<int32__t>()
{
    return INT32__T_MIN;
}
template <> uint32__t minVal<uint32__t>()
{
    return UINT32__T_MIN;
}
template <> int64__t minVal<int64__t>()
{
    return INT64__T_MIN;
}
template <> uint64__t minVal<uint64__t>()
{
    return UINT64__T_MIN;
}

template <typename T> T maxVal()
{
    return std::numeric_limits<T>::max();
}

template <> int8__t maxVal<int8__t>()
{
    return INT8__T_MAX;
}
template <> uint8__t maxVal<uint8__t>()
{
    return UINT8__T_MAX;
}
template <> int16__t maxVal<int16__t>()
{
    return INT16__T_MAX;
}
template <> uint16__t maxVal<uint16__t>()
{
    return UINT16__T_MAX;
}
template <> int32__t maxVal<int32__t>()
{
    return INT32__T_MAX;
}
template <> uint32__t maxVal<uint32__t>()
{
    return UINT32__T_MAX;
}
template <> int64__t maxVal<int64__t>()
{
    return INT64__T_MAX;
}
template <> uint64__t maxVal<uint64__t>()
{
    return UINT64__T_MAX;
}

}; // namespace limits
} // namespace rmx
