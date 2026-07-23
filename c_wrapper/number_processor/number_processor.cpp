#include <stdexcept>

#include "number_processor.hpp"
#include "number_processor.h"

static MyLibrary::NumberProcessor* GetObject(mylib_NumberProcessor_t* handle)
{
    return reinterpret_cast<MyLibrary::NumberProcessor*>(handle);
}

mylib_status_t MyLib_NumberProcessor_Destroy(mylib_NumberProcessor_t* handle)
{
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;

    delete GetObject(handle);
    
    return MYLIB_STATUS_OK;
}

mylib_status_t MyLib_NumberProcessor_Process(mylib_NumberProcessor_t* handle)
{
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;

    GetObject(handle)->process();

    return MYLIB_STATUS_OK;
}

mylib_status_t MyLib_NumberProcessor_GetNumber(mylib_NumberProcessor_t* handle, int* number)
{
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;
    if (number == nullptr)
        return MYLIB_STATUS_INVALID_ARGUMENT;

    *number = GetObject(handle)->GetNumber();

    return MYLIB_STATUS_OK;
}

mylib_status_t MyLib_NumberProcessor_SetNumber(mylib_NumberProcessor_t* handle, int  number)
{
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;

    GetObject(handle)->SetNumber(number);

    return MYLIB_STATUS_OK;
}

mylib_status_t MyLib_NumberProcessor_PrintNumber(mylib_NumberProcessor_t* handle)
{
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;

    GetObject(handle)->PrintNumber();

    return MYLIB_STATUS_OK;
}
