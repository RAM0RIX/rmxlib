#pragma once
#ifndef _RMX_ERROR_H_
#define _RMX_ERROR_H_

#include <rmx/types.h>
#include <rmxdef.h>

namespace rmx
{
// Provides an error handling system to all its subclasses
// Made for non-static classes
// Inherit it from the superclass like this: class superClassName: public ObjError<errType>
template <class C, typename EC> class ObjError
{
    friend C;

  private:
    mutable EC m_lastError;

  protected:
    ObjError();
    ~ObjError();

  public:
    EC GetLastError() const;

  protected:
    inline EC SetLastError(EC error) const
    {
        m_lastError = error;
        return error;
    }
};

// Provides an error handling system to all its subclasses
// Made for static classes
// Instantiate it with class className: public StaticError<className, errType>
template <class C, typename EC> class ClassError
{
    friend C;
    RMX_PRIVATE_CONSTRUCTORS(ClassError)
  private:
    static EC sm_lastError;

  public:
    static EC getLastError();

  private:
    inline static EC setLastError(EC error)
    {
        sm_lastError = error;
        return error;
    }
};

} // namespace rmx

#endif /* _RMX_ERROR_H_ */
