#pragma once

#ifndef _RMX_LIMITS_H_
#define _RMX_LIMITS_H_

#include <limits>

#include <rmx/types.h>

namespace rmx
{
namespace limits
{
/* Min values */

constexpr int8__t INT8__T_MIN = -128;
constexpr uint8__t UINT8__T_MIN = 0;

constexpr int16__t INT16__T_MIN = -32767;
constexpr uint16__t UINT16__T_MIN = 0;

constexpr int32__t INT32__T_MIN = -2147483647;
constexpr uint32__t UINT32__T_MIN = 0;

constexpr int64__t INT64__T_MIN = -9223372036854775807 - 1;
constexpr uint64__t UINT64__T_MIN = 0;

/* Max values */

constexpr int8__t INT8__T_MAX = 127;
constexpr uint8__t UINT8__T_MAX = 255;

constexpr int16__t INT16__T_MAX = 32767;
constexpr uint16__t UINT16__T_MAX = 65535;

constexpr int32__t INT32__T_MAX = 2147483647;
constexpr uint32__t UINT32__T_MAX = 4294967295;

constexpr int64__t INT64__T_MAX = 9223372036854775807;
constexpr uint64__t UINT64__T_MAX = 18446744073709551615ULL;

// Calls std::numeric_limits<T>::min()
template <typename T> T minVal();
template <> int8__t minVal<int8__t>();
template <> uint8__t minVal<uint8__t>();
template <> int16__t minVal<int16__t>();
template <> uint16__t minVal<uint16__t>();
template <> int32__t minVal<int32__t>();
template <> uint32__t minVal<uint32__t>();
template <> int64__t minVal<int64__t>();
template <> uint64__t minVal<uint64__t>();

// Calls std::numeric_limits<T>::max()
template <typename T> T maxVal();
template <> int8__t maxVal<int8__t>();
template <> uint8__t maxVal<uint8__t>();
template <> int16__t maxVal<int16__t>();
template <> uint16__t maxVal<uint16__t>();
template <> int32__t maxVal<int32__t>();
template <> uint32__t maxVal<uint32__t>();
template <> int64__t maxVal<int64__t>();
template <> uint64__t maxVal<uint64__t>();

} // namespace limits
} // namespace rmx

#endif /* _RMX_LIMITS_H_ */
