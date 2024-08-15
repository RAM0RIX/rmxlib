#pragma once

#ifndef _RMX_LOG_H_
#define _RMX_LOG_H_

#include <rmx/Array.h>

#define RMX_CHECK_OBJ_LOGLEVEL(_LogLevel) /* Does nothing lol */

namespace rmx
{

class Log
{
  public:
    // Or CONSOLEs together to output to multiple consoles at once
    enum CONSOLE : byte__t
    {
        _WINDOWS_SUBSYSTEM_CONSOLE = 0b00000001,
        _WINDOWS_DEBUG_CONSOLE = 0b00000010,
        _SEPARATE_WINDOW = 0b00000100,
        _CUSTOM_CONSOLE = 0b00001000
    };

  private:
    Array<LogLevel, ARRAY::DYNAMIC_SIZE> m_LogLevels;
    uint64__t m_defaultLogLevel;

    Array<File, ARRAY::DYNAMIC_SIZE> m_Files;

    byte__t m_consoles;

  public:
    Log();
    Log(byte__t _Consoles);
    Log(const Array<LogLevel, ARRAY::DYNAMIC_SIZE> &_llArray, const Array<File, ARRAY::DYNAMIC_SIZE> &_fArray,
        byte__t _Consoles);
    Log(const Array<LogLevel, ARRAY::DYNAMIC_SIZE> &_llArray, byte__t _Consoles);
    Log(const Array<File, ARRAY::DYNAMIC_SIZE> &_fArray, byte__t _Consoles);
    ~Log();

  public:
    const LogLevel &GetLogLevel(uint64__t _Index) const;

    LogLevel &SetLogLevel(uint64__t _Index, const LogLevel &_LogLevel);
    template <typename... Args> uint64__t CreateSetLogLevel(uint64__t _Index, Args &&..._Args);

    uint64__t AddLogLevel(const LogLevel &_LogLevel);
    template <typename... Args> uint64__t CreateAddLogLevel(Args &&..._Args);

    void SetDefaultLogLevel(uint64__t _Index);

    //
    const File &GetFile(uint64__t _Index) const;

    File &SetFile(uint64__t _Index, const File &_File);
    template <typename... Args> uint64__t CreateSetFile(uint64__t _Index, Args &&..._Args);

    uint64__t AddFile(const File &_File);
    template <typename... Args> uint64__t CreateAddFile(Args &&..._Args);

    byte__t GetConsoles() const;
    // Or consoles together from the CONSOLE enum to log on multiple consoles at once
    void SetConsoles(byte__t consoles);

  public:
    void log(uint64__t _llIndex, const char *_Msg, const wchar_t *_wMsg);
    void log(const char *_Msg, const wchar_t *_wMsg);
};

} // namespace rmx

#endif /* _RMX_LOG_H_ */
