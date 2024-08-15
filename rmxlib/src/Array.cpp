#include <rmx/Array.h>

#include <rmx/File.h>
#include <rmx/LogLevel.h>

namespace rmx
{
template<> class Array<LogLevel, ARRAY::DYNAMIC_SIZE>;
template<> class Array<File, ARRAY::DYNAMIC_SIZE>;
} // namespace rmx
