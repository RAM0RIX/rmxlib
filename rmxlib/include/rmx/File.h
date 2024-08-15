#pragma once
#ifndef _RMX_FILE_H_
#define _RMX_FILE_H_


#include <rmxdef.h>
#include <rmx/str.h>

namespace rmx
{
class File
{
  private:
    FILE *m_FileHandle;
    char *m_FilePath;
    char m_mode[4];

  public:
    File() = delete;
    File(const char *_FilePath, const char _Mode[4]);
    ~File();

    // Copy
    File(const File &_Other);
    File &operator=(const File &_Other);

    // Move
    File(File &&_Other);
    File &operator=(File &&_Other);

  public:
    // DO NOT CLOSE _pFile !!!
    const FILE *const GetHandle() const;
};
} // namespace rmx

#endif /* _RMX_FILE_H_ */
