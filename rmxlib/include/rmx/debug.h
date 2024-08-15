#pragma once
#ifndef _RMX_DEBUG_H_
#define _RMX_DEBUG_H_

#include <stdexcept>

#include <rmx/GUI/box.h>

static char msg[1024];

#define RMX_TO_STR(_Arg) #_Arg

#define RMX_THROW(_Msg)                                                                                                \
    {                                                                                                                  \
        sprintf(msg, "Error in file \'%s\' at line %d in function \'%s\': " _Msg, __FILE__, __LINE__, __func__);       \
        rmx::box::displayFatalErrorA(msg);                                                                             \
    }

#define RMX_THROW_ARG(_Msg, _Arg)                                                                                      \
    {                                                                                                                  \
        sprintf(msg, "Error in file \'%s\' at line %d in function \'%s\': " _Msg, __FILE__, __LINE__, __func__, _Arg); \
        rmx::box::displayFatalErrorA(msg);                                                                             \
    }
#define RMX_THROW_2ARG(_Msg, _Arg1, _Arg2)                                                                             \
    {                                                                                                                  \
        sprintf(msg, "Error in file \'%s\' at line %d in function \'%s\': " _Msg, __FILE__, __LINE__, __func__, _Arg1, \
                _Arg2);                                                                                                \
        rmx::box::displayFatalErrorA(msg);                                                                             \
    }
#define RMX_THROW_3ARG(_Msg, _Arg1, _Arg2, _Arg3)                                                                      \
    {                                                                                                                  \
        sprintf(msg, "Error in file \'%s\' at line %d in function \'%s\': " _Msg, __FILE__, __LINE__, __func__, _Arg1, \
                _Arg2, _Arg3);                                                                                         \
        rmx::box::displayFatalErrorA(msg);                                                                             \
    }
#define RMX_THROW_4ARG(_Msg, _Arg1, _Arg2, _Arg3, _Arg4)                                                               \
    {                                                                                                                  \
        sprintf(msg, "Error in file \'%s\' at line %d in function \'%s\': " _Msg, __FILE__, __LINE__, __func__, _Arg1, \
                _Arg2, _Arg2, _Arg4);                                                                                  \
        rmx::box::displayFatalErrorA(msg);                                                                             \
    }

#define RMX_CHECK_NULL(_Var)                                                                                           \
    {                                                                                                                  \
        if (!_Var)                                                                                                     \
            RMX_THROW("\'" #_Var "\' is NULL !")                                                                       \
    }
#define RMX_CHECK_NULLPTR(_Ptr)                                                                                        \
    {                                                                                                                  \
        if (!_Ptr)                                                                                                     \
            RMX_THROW("Pointer \'" #_Ptr "\' is nullptr !")                                                            \
    }

#define RMX_CHECK_PARAM_NULL(_Var)                                                                                     \
    {                                                                                                                  \
        if (!_Var)                                                                                                     \
            RMX_THROW("Parmeter \'" #_Var "\' is NULL!")                                                               \
    }
#define RMX_CHECK_PARAM_NULLPTR(_Ptr)                                                                                  \
    {                                                                                                                  \
        if (!_Ptr)                                                                                                     \
            RMX_THROW("PointerParmeter \'" #_Ptr "\' is nullptr !")                                                    \
    }
#define RMX_CHECK_PARAM_NULL_T(_Var, T)                                                                                \
    {                                                                                                                  \
        if (!_Var)                                                                                                     \
            RMX_THROW("Parmeter \'" #_Var "\' of type " #T " is NULL!")                                                \
    }
#define RMX_CHECK_PARAM_NULLPTR_T(_Ptr, T)                                                                             \
    {                                                                                                                  \
        if (!_Ptr)                                                                                                     \
            RMX_THROW("PointerParmeter \'" #_Ptr "\' of type " #T " is nullptr !")                                     \
    }

#define RMX_CHECK_CLASS_MEMBER_NULL(Class, _Object, _Member, _MemberValue)                                             \
    {                                                                                                                  \
        if (!_MemberValue)                                                                                             \
            RMX_THROW_ARG("Member \'" #_Member "\' of \'" #_Object "\' : " #Class "(%llu bytes) is NULL !",            \
                          sizeof(_Object))                                                                             \
    }
#define RMX_CHECK_CLASS_MEMBER_NULLPTR(Class, _Object, _Pointer, _PointerValue)                                        \
    {                                                                                                                  \
        if (!_PointerValue)                                                                                            \
            RMX_THROW_ARG("PointerMember \'" #_Pointer "\' of \'" #_Object "\' : " #Class "(%llu bytes) is nullptr !", \
                          sizeof(_Object))                                                                             \
    }

#endif /* _RMX_DEBUG_H_ */
