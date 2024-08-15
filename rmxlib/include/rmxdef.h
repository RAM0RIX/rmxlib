#pragma once

#ifndef _RMXDEF_H_
#define _RMXDEF_H_

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include <rmx/Windows/winHeader.h>

#define RMX_REMOVE_CONSTRUCTORS(_Class)                                                                                \
  private:                                                                                                             \
    _Class() = delete;                                                                                                 \
    ~_Class() = delete;                                                                                                \
    _Class(_Class &other) = delete;                                                                                    \
    _Class &operator=(_Class &other) = delete;                                                                         \
    _Class(_Class &&other) = delete;                                                                                   \
    _Class &operator=(_Class &&other) = delete;

#define RMX_PRIVATE_CONSTRUCTORS(_Class)                                                                               \
  private:                                                                                                             \
    _Class();                                                                                                          \
    ~_Class();                                                                                                         \
    _Class(_Class &other);                                                                                             \
    _Class &operator=(_Class &other);                                                                                  \
    _Class(_Class &&other);                                                                                            \
    _Class &operator=(_Class &&other);

namespace rmx
{
class Log;
class LogLevel;
} // namespace rmx

#include <rmx/debug.h>

#include <rmx/types.h>

#include <rmx/limits.h>

#endif /* _RMXDEF_H_ */
