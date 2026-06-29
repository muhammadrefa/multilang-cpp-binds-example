#include <stdexcept>

#include "calculator.hpp"
#include "calculator.h"

static MyLibrary::Calculator* GetObject(mylib_calculator_t* handle)
{
    return reinterpret_cast<MyLibrary::Calculator*>(handle);
}

mylib_calculator_t* MyLib_Calculator_Create()
{
    try
    {
        MyLibrary::Calculator *calculator = new MyLibrary::Calculator();
        return reinterpret_cast<mylib_calculator_t*>(calculator);
    }
    catch (const std::bad_alloc& e)
    {
        return nullptr;
    }
    catch (...)
    {
        return nullptr;
    }
}

mylib_status_t MyLib_Calculator_Destroy(mylib_calculator_t* handle)
{
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;

    delete GetObject(handle);
    
    return MYLIB_STATUS_OK;
}

mylib_status_t MyLib_Calculator_Add(mylib_calculator_t* handle, int a, int b, int* retval)
{
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;
    if (retval == nullptr)
        return MYLIB_STATUS_INVALID_ARGUMENT;

    *retval = GetObject(handle)->add(a, b);

    return MYLIB_STATUS_OK;
}

mylib_status_t MyLib_Calculator_Sub(mylib_calculator_t* handle, int a, int b, int* retval)
{
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;
    if (retval == nullptr)
        return MYLIB_STATUS_INVALID_ARGUMENT;

    *retval = GetObject(handle)->sub(a, b);

    return MYLIB_STATUS_OK;
}

mylib_status_t MyLib_Calculator_CntOpsDone(mylib_calculator_t* handle, int* retval)
{
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;
    if (retval == nullptr)
        return MYLIB_STATUS_INVALID_ARGUMENT;

    *retval = GetObject(handle)->cntOpsDone();

    return MYLIB_STATUS_OK;
}

mylib_status_t MyLib_Calculator_ResetCounter(mylib_calculator_t* handle, int* retval)
{
    int ret;
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;
    if (retval == nullptr)
        return MYLIB_STATUS_INVALID_ARGUMENT;

    ret = GetObject(handle)->resetCounter();
    if (retval != nullptr)
        *retval = ret;

    return MYLIB_STATUS_OK;
}
