#include <rmx/Error.h>

namespace rmx
{
// Class 'ObjError'
template <class C, typename EC> ObjError<C, EC>::ObjError() : m_lastError(0)
{
}
template <class C, typename EC> ObjError<C, EC>::~ObjError()
{
}

template <class C, typename EC> EC ObjError<C, EC>::GetLastError() const
{
    return m_lastError;
}

// Class 'ClassError'
template <class C, typename EC> EC ClassError<C, EC>::sm_lastError = 0;

template <class C, typename EC> EC ClassError<C, EC>::getLastError()
{
    return sm_lastError;
}

} // namespace rmx
