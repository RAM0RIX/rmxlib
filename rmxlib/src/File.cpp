#include <rmx/File.h>

namespace rmx
{
File::File(const char *_FilePath, const char _Mode[4])
{
    m_FilePath = str::copyalloc(_FilePath);
    mem::copy(m_mode, _Mode, 4);

#ifdef RMX_DEBUG
    fopen_s(&m_FileHandle, m_FilePath, m_mode);
    if (errno != ERROR_SUCCESS)
        RMX_THROW_3ARG("Couldn't open file %s with mode %s ! Errno returned: %s", m_FilePath, m_mode, strerror(errno));
#else
    m_FileHandle = fopen(m_FilePath, m_mode);
#endif
}

File::~File()
{
    fclose(m_FileHandle);
}

File::File(const File &_Other)
{
    m_FilePath = str::copyalloc(_Other.m_FilePath);
    mem::copy(m_mode, _Other.m_mode, 4);

#ifdef RMX_DEBUG
    fopen_s(&m_FileHandle, m_FilePath, m_mode);
    if (errno != ERROR_SUCCESS)
        RMX_THROW_3ARG("Couldn't open file %s with mode %s ! Errno returned: %s", m_FilePath, m_mode, strerror(errno));
#else
    m_FileHandle = fopen(m_FilePath, m_mode);
#endif
}

File &File::operator=(const File &_Other)
{
    if (this != &_Other)
    {
        m_FilePath = str::copyalloc(_Other.m_FilePath);
        mem::copy(m_mode, _Other.m_mode, 4);

#ifdef RMX_DEBUG
        fopen_s(&m_FileHandle, m_FilePath, m_mode);
        if (errno != ERROR_SUCCESS)
            RMX_THROW_3ARG("Couldn't open file %s with mode %s ! Errno returned: %s", m_FilePath, m_mode,
                           strerror(errno));
#else
        m_FileHandle = fopen(m_FilePath, m_mode);
#endif
    }
    return *this;
}

File::File(File &&_Other)
{
    m_FileHandle = _Other.m_FileHandle;
    m_FilePath = _Other.m_FilePath;
    mem::copy(m_mode, _Other.m_mode, 4);

    _Other.m_FileHandle = nullptr;
    _Other.m_FilePath = nullptr;
    mem::clear(_Other.m_mode, 4);
}

File &File::operator=(File &&_Other)
{
    if (this != &_Other)
    {
        m_FileHandle = _Other.m_FileHandle;
        m_FilePath = _Other.m_FilePath;
        mem::copy(m_mode, _Other.m_mode, 4);

        _Other.m_FileHandle = nullptr;
        _Other.m_FilePath = nullptr;
        mem::clear(_Other.m_mode, 4);
    }
    return *this;
}

const FILE *const File::GetHandle() const
{
    return m_FileHandle;
}
} // namespace rmx
