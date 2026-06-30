#include <stdexcept>
#include <cstddef>
#include <cstring>

#include "animal.h"
#include "cat.h"
#include "tiger.hpp"
#include "tiger.h"

static MyLibrary::Tiger* GetObject(mylib_tiger_t* handle)
{
    return reinterpret_cast<MyLibrary::Tiger*>(handle);
}

mylib_tiger_t* MyLib_Tiger_Create()
{
    try
    {
        MyLibrary::Tiger *tiger = new MyLibrary::Tiger();
        return reinterpret_cast<mylib_tiger_t*>(tiger);
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

mylib_tiger_t* MyLib_Tiger_Create_With_Name(char* name, int length)
{
    std::string name_str(name, length);

    try
    {
        MyLibrary::Tiger *tiger = new MyLibrary::Tiger(name_str);
        return reinterpret_cast<mylib_tiger_t*>(tiger);
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

mylib_status_t MyLib_Tiger_Destroy(mylib_tiger_t* handle)
{
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;

    delete GetObject(handle);
    
    return MYLIB_STATUS_OK;
}

mylib_cat_t* MyLib_Tiger_As_Cat(mylib_tiger_t* handle)
{
    MyLibrary::Tiger* tiger = GetObject(handle);
    MyLibrary::Cat* cat = static_cast<MyLibrary::Cat*>(tiger);
    return reinterpret_cast<mylib_cat_t*>(cat);
}

mylib_status_t MyLib_Tiger_Hunt(mylib_tiger_t* handle)
{
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;

    GetObject(handle)->hunt();

    return MYLIB_STATUS_OK;
}

mylib_status_t MyLib_Tiger_GetHunger(mylib_tiger_t* handle, int* hunger)
{
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;
    if (hunger == nullptr)
        return MYLIB_STATUS_INVALID_ARGUMENT;

    *hunger = GetObject(handle)->getHunger();

    return MYLIB_STATUS_OK;
}

mylib_status_t MyLib_Tiger_Fight(mylib_tiger_t* handle, int bigger_cat, int* success)
{
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;
    if (success == nullptr)
        return MYLIB_STATUS_INVALID_ARGUMENT;

    *success = GetObject(handle)->fight(bigger_cat);

    return MYLIB_STATUS_OK;
}

mylib_status_t MyLib_Tiger_StillAlive(mylib_tiger_t* handle, int* is_alive)
{
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;
    if (is_alive == nullptr)
        return MYLIB_STATUS_INVALID_ARGUMENT;

    *is_alive = GetObject(handle)->stillAlive();

    return MYLIB_STATUS_OK;
}

mylib_status_t MyLib_Tiger_Speak(mylib_tiger_t* handle)
{
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;

    GetObject(handle)->speak();

    return MYLIB_STATUS_OK;
}

mylib_status_t MyLib_Tiger_Speak_Multiple_Times(mylib_tiger_t* handle, int times)
{
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;

    GetObject(handle)->speak(times);

    return MYLIB_STATUS_OK;
}

mylib_status_t MyLib_Tiger_Sleep(mylib_tiger_t* handle)
{
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;

    GetObject(handle)->sleep();

    return MYLIB_STATUS_OK;
}

mylib_status_t MyLib_Tiger_Set_Name(mylib_tiger_t* handle, char* name, int length)
{
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;

    GetObject(handle)->name = std::string(name, length);

    return MYLIB_STATUS_OK;
}

mylib_status_t MyLib_Tiger_Get_Name(mylib_tiger_t* handle, char* name, size_t buffer_size, int* length)
{
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;
    if (name == nullptr)
        return MYLIB_STATUS_INVALID_ARGUMENT;
    if (length == nullptr)
        return MYLIB_STATUS_INVALID_ARGUMENT;

    std::string _name = GetObject(handle)->name;
    *length = _name.length();

    if (buffer_size < *length)
        return MYLIB_STATUS_BUFFER_TOO_SMALL;

    strcpy(name, _name.c_str());

    return MYLIB_STATUS_OK;
}
