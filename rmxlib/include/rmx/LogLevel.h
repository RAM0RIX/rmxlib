#pragma once
#ifndef _RMX_LOGLEVEL_H_
#define _RMX_LOGLEVEL_H_

#include <rmx/String.h>

namespace rmx
{

class LogLevel
{
  public:
    enum class COLOR : rmx::color__t
    {
        BLACK,
        RED,
        GREEN,
        YELLOW,
        BLUE,
        MAGENTA,
        CYAN,
        WHITE,
    };

    /*public:*/
    /*  mutable Array<RMX_ERROR, 8> m_errorStack;*/

  private:
    char *m_header;
    size__t m_headerSize;

    wchar_t *m_wheader;
    size__t m_wheaderSize;

    COLOR m_color;

  public:
    LogLevel() = delete;
    // Copies _Str into m_header and _wStr into m_wheader
    LogLevel(const char *_Str, size__t _Count, const wchar_t *_wStr, size__t _wCount, LogLevel::COLOR _Color);

    // Copy
    LogLevel(const LogLevel &_Other);
    LogLevel &operator=(const LogLevel &_Other);

    // Move
    LogLevel(LogLevel &&_Other) noexcept;
    LogLevel &operator=(LogLevel &&_Other) noexcept;

    ~LogLevel();

  public:
    const char *const &GetHeader() const;

    const wchar_t *const &GetWHeader() const;

    // Returns the size allocated for m_header, thus including the null-terminating character, returns 0 if m_header
    // is not allocated
    size__t GetHeaderSize() const;
    // Returns the size allocated for m_wheader, thus including the null-terminating character, returns 0 if
    // m_wheader is not allocated
    size__t GetWHeaderSize() const;

    // Allocates space for m_header and copies in the first _Count characters of_Str
    void SetHeader(const char *_Str, size__t _Count);

    // Allocates space for m_wheader and copies in the first _Count characters of_wStr
    void SetWHeader(const wchar_t *_wStr, size__t _wCount);

    COLOR GetColor() const;
    void SetColor(COLOR _Color);
};

} // namespace rmx

#endif /* _RMX_LOGLEVEL_H_ */
