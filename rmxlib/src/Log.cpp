#include <rmx/Log.h>
namespace rmx
{
    // Log class constructors

    Log::Log() : m_LogLevels(5), m_defaultLogLevel(0), m_Files(5), m_consoles(0)
    {}
    Log::Log(byte__t _Consoles) : m_LogLevels(5), m_defaultLogLevel(0), m_Files(5), m_consoles(_Consoles)
    {}
    Log::Log(const Array<LogLevel, ARRAY::DYNAMIC_SIZE>& _llArray, const Array<File, ARRAY::DYNAMIC_SIZE>& _fArray,
             byte__t _Consoles)
        : m_LogLevels(_llArray), m_defaultLogLevel(0), m_Files(_fArray), m_consoles(_Consoles)
    {}
    Log::Log(const Array<LogLevel, ARRAY::DYNAMIC_SIZE>& _llArray, byte__t _Consoles)
        : m_LogLevels(_llArray), m_defaultLogLevel(0), m_Files(5), m_consoles(_Consoles)
    {}
    Log::Log(const Array<File, ARRAY::DYNAMIC_SIZE>& _fArray, byte__t _Consoles)
        : m_LogLevels(5), m_defaultLogLevel(0), m_Files(_fArray), m_consoles(_Consoles)
    {}

    Log::~Log()
    {
        m_LogLevels.~Array();
        m_Files.~Array();
    }

    const LogLevel& Log::GetLogLevel(uint64__t _Index) const
    {
        return m_LogLevels.CopyFrom(_Index);
    }

    LogLevel& Log::SetLogLevel(uint64__t _Index, const LogLevel& _LogLevel)
    {
        return m_LogLevels.CopyTo(_Index, _LogLevel);
    }
    template <typename... Args> uint64__t Log::CreateSetLogLevel(uint64__t _Index, Args &&..._Args)
    {
        return m_LogLevels.CreateTo(_Index, _Args...);
    }

    uint64__t Log::AddLogLevel(const LogLevel& _LogLevel)
    {
        m_LogLevels.Push(_LogLevel);
        return m_LogLevels.GetOffset() - 1;
    }
    void Log::SetDefaultLogLevel(uint64__t _Index)
    {
    #ifdef RMX_DEBUG
        if (_Index >= m_LogLevels.GetSize()) RMX_THROW_2ARG("_Index(%llu bytes) for the default LogLevel is larger than the size of m_LogLevels(%llu bytes)!", _Index, m_LogLevels.GetSize());
    #endif
        m_defaultLogLevel = _Index;
    }
    template <typename... Args> uint64__t Log::CreateAddLogLevel(Args &&..._Args)
    {
        m_LogLevels.PushCreate(_Args...);
        return m_LogLevels.GetOffset() - 1;
    }


    const File& Log::GetFile(uint64__t _Index) const
    {
        return m_Files.CopyFrom(_Index);
    }

    File& Log::SetFile(uint64__t _Index, const File& _File)
    {
        return m_Files.CopyTo(_Index, _File);
    }
    template <typename... Args> uint64__t Log::CreateSetFile(uint64__t _Index, Args &&..._Args)
    {
        return m_Files.CreateTo(_Index, _Args...);
    }

    uint64__t Log::AddFile(const File& _File)
    {
        m_Files.Push(_File);
        return m_Files.GetOffset() - 1;
    }
    template <typename... Args> uint64__t Log::CreateAddFile(Args &&..._Args)
    {
        m_Files.PushCreate(_Args...);
        return m_Files.GetOffset() - 1;
    }

    byte__t Log::GetConsoles() const
    {
        return m_consoles;
    }

    void Log::SetConsoles(byte__t consoles)
    {
        if (consoles & CONSOLE::_WINDOWS_SUBSYSTEM_CONSOLE)
            m_consoles |= CONSOLE::_WINDOWS_SUBSYSTEM_CONSOLE;
        if (consoles & CONSOLE::_WINDOWS_DEBUG_CONSOLE)
            m_consoles |= CONSOLE::_WINDOWS_DEBUG_CONSOLE;
        if (consoles & CONSOLE::_SEPARATE_WINDOW)
            m_consoles |= CONSOLE::_SEPARATE_WINDOW;
        if (consoles & CONSOLE::_CUSTOM_CONSOLE)
            m_consoles |= CONSOLE::_CUSTOM_CONSOLE;
    }

    void Log::log(uint64__t _llIndex, const char* _Msg, const wchar_t* _wMsg)
    {
        // Create the string to output
        // Log to consoles
        if (m_consoles & CONSOLE::_WINDOWS_SUBSYSTEM_CONSOLE)
        {
             if (_wMsg) 
             { 
                 std::wcout.imbue(std::locale("")); 

                 switch (m_LogLevels.CopyFrom(_llIndex).GetColor()) 
                 { 
                 case LogLevel::COLOR::BLACK: 
                     std::wcout << L"\033[30m"; 
                     break; 
                 case LogLevel::COLOR::RED: 
                     std::wcout << L"\033[31m"; 
                     break; 
                 case LogLevel::COLOR::GREEN: 
                     std::wcout << L"\033[32m"; 
                     break; 
                 case LogLevel::COLOR::YELLOW: 
                     std::wcout << L"\033[33m"; 
                     break; 
                 case LogLevel::COLOR::BLUE: 
                     std::wcout << L"\033[34m"; 
                     break; 
                 case LogLevel::COLOR::MAGENTA: 
                     std::wcout << L"\033[35m"; 
                     break; 
                 case LogLevel::COLOR::CYAN: 
                     std::wcout << L"\033[36m"; 
                     break; 
                 case LogLevel::COLOR::WHITE: 
                     std::wcout << L"\033[37m"; 
                     break; 
                 } 
                 if (m_LogLevels.CopyFrom(_llIndex).GetWHeaderSize()) 
                     std::wcout << m_LogLevels.CopyFrom(_llIndex).GetWHeader(); 
                 if (_wMsg) 
                     std::wcout << _wMsg; 
                 std::wcout << L"\n" << L"\033[0m"; 
             } 
             else 
            {
                switch (m_LogLevels.CopyFrom(_llIndex).GetColor())
                {
                case LogLevel::COLOR::BLACK:
                    std::cout << "\033[30m";
                    break;
                case LogLevel::COLOR::RED:
                    std::cout << "\033[31m";
                    break;
                case LogLevel::COLOR::GREEN:
                    std::cout << "\033[32m";
                    break;
                case LogLevel::COLOR::YELLOW:
                    std::cout << "\033[33m";
                    break;
                case LogLevel::COLOR::BLUE:
                    std::cout << "\033[34m";
                    break;
                case LogLevel::COLOR::MAGENTA:
                    std::cout << "\033[35m";
                    break;
                case LogLevel::COLOR::CYAN:
                    std::cout << "\033[36m";
                    break;
                case LogLevel::COLOR::WHITE:
                    std::cout << "\033[37m";
                    break;
                }
                if (m_LogLevels.CopyFrom(_llIndex).GetHeaderSize())
                    std::cout << m_LogLevels.CopyFrom(_llIndex).GetHeader();
                else if (_Msg)
                    std::cout << _Msg;
                std::cout << "\n" << "\033[0m";
            }
        }
    }
    void Log::log(const char* _Msg, const wchar_t* _wMsg)
    {
        log(m_defaultLogLevel, _Msg, _wMsg);
    }
} // namespace rmx
