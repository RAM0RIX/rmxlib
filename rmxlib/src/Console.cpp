#include <rmx/Console.h>

namespace rmx
{

Console::Console(void *_BufferIn, void *_BufferOut) : cout(_BufferOut), cin(_BufferIn)
{
}
Console::~Console()
{
}

} // namespace rmx
