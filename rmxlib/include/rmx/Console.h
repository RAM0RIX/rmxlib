#pragma once

#ifndef _RMX_CONSOLE_H_
#define _RMX_CONSOLE_H_

namespace rmx
{
class Console
{
  private:
    void *cin;
    void *cout;

  public:
    Console() = delete;
    Console(void *_BufferIn, void *_BufferOut);
    ~Console();
};
} // namespace rmx

#endif /* _RMX_CONSOLE_H_ */
