#include <rmx/LogLevel.h>

namespace rmx
{

LogLevel::LogLevel(const char *_Str, size__t _Count, const wchar_t *_wStr, size__t _wCount, LogLevel::COLOR _Color)
    : m_color(_Color), m_header(nullptr), m_headerSize(0), m_wheader(nullptr), m_wheaderSize(0)
{
    if (_Str && _Count)
        SetHeader(_Str, _Count);
    if (_wStr && _wCount)
        SetWHeader(_wStr, _wCount);
}
LogLevel::~LogLevel()
{
    mem::free_(m_header);
    mem::free_(m_wheader);
}

LogLevel::LogLevel(const LogLevel &_Other)
{
    mem::free_(m_header);
    m_header = str::ncopyalloc(_Other.m_header, _Other.m_headerSize);
    m_headerSize = _Other.m_headerSize;

    mem::free_(m_wheader);
    m_wheader = str::wncopyalloc(_Other.m_wheader, _Other.m_wheaderSize);
    m_wheaderSize = _Other.m_wheaderSize;

    m_color = _Other.m_color;
}
LogLevel &LogLevel::operator=(const LogLevel &_Other)
{
    if (this != &_Other)
    {
        mem::free_(m_header);
        m_header = str::ncopyalloc(_Other.m_header, _Other.m_headerSize);
        m_headerSize = _Other.m_headerSize;

        mem::free_(m_wheader);
        m_wheader = str::wncopyalloc(_Other.m_wheader, _Other.m_wheaderSize);
        m_wheaderSize = _Other.m_wheaderSize;

        m_color = _Other.m_color;
    }
    return *this;
}

LogLevel::LogLevel(LogLevel &&_Other) noexcept
{
    mem::free_(m_header);
    mem::free_(m_wheader);

    m_header = _Other.m_header;
    m_headerSize = _Other.m_headerSize;
    m_wheader = _Other.m_wheader;
    m_wheaderSize = _Other.m_wheaderSize;
    m_color = _Other.m_color;

    _Other.m_header = nullptr;
    _Other.m_headerSize = 0;
    _Other.m_wheader = nullptr;
    _Other.m_wheaderSize = 0;
    _Other.m_color = COLOR::BLACK;
}
LogLevel &LogLevel::operator=(LogLevel &&_Other) noexcept
{
    if (this != &_Other)
    {
        mem::free_(m_header);
        mem::free_(m_wheader);

        m_header = _Other.m_header;
        m_headerSize = _Other.m_headerSize;
        m_wheader = _Other.m_wheader;
        m_wheaderSize = _Other.m_wheaderSize;
        m_color = _Other.m_color;

        _Other.m_header = nullptr;
        _Other.m_headerSize = 0;
        _Other.m_wheader = nullptr;
        _Other.m_wheaderSize = 0;
        _Other.m_color = COLOR::BLACK;
    }
    return *this;
}

const char *const &LogLevel::GetHeader() const
{
    return m_header;
}

const wchar_t *const &LogLevel::GetWHeader() const
{
    return m_wheader;
}

size__t LogLevel::GetHeaderSize() const
{
    return m_headerSize;
}
size__t LogLevel::GetWHeaderSize() const
{
    return m_wheaderSize;
}

void LogLevel::SetHeader(const char *_Str, size__t _Count)
{
#ifdef RMX_DEBUG
    RMX_CHECK_PARAM_NULLPTR(_Str);
    RMX_CHECK_PARAM_NULL(_Count);
#endif
    if (m_header)
        mem::free_(m_header);
    m_header = str::ncopyalloc(_Str, _Count);
}

void LogLevel::SetWHeader(const wchar_t *_wStr, size__t _wCount)
{
#ifdef RMX_DEBUG
    RMX_CHECK_PARAM_NULLPTR(_wStr);
    RMX_CHECK_PARAM_NULL(_wCount);
#endif
    if (m_wheader)
        mem::free_(m_wheader);
    m_wheader = str::wncopyalloc(_wStr, _wCount);
}

LogLevel::COLOR LogLevel::GetColor() const
{
    return m_color;
}

void LogLevel::SetColor(COLOR _Color)
{
    m_color = _Color;
}

} // namespace rmx
