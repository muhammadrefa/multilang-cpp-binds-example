#include <stdexcept>
#include <cstddef>
#include <cstring>

#include "animal.h"
#include "cat.hpp"
#include "cat.h"

static MyLibrary::Cat* GetObject(mylib_cat_t* handle)
{
    return reinterpret_cast<MyLibrary::Cat*>(handle);
}

mylib_cat_t* MyLib_Cat_Create()
{
    try
    {
        MyLibrary::Cat *cat = new MyLibrary::Cat();
        return reinterpret_cast<mylib_cat_t*>(cat);
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

mylib_cat_t* MyLib_Cat_Create_With_Name(char* name, int length)
{
    std::string name_str(name, length);

    try
    {
        MyLibrary::Cat *cat = new MyLibrary::Cat(name_str);
        return reinterpret_cast<mylib_cat_t*>(cat);
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

mylib_status_t MyLib_Cat_Destroy(mylib_cat_t* handle)
{
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;

    delete GetObject(handle);
    
    return MYLIB_STATUS_OK;
}

mylib_animal_t* MyLib_Cat_As_Animal(mylib_cat_t* handle)
{
    MyLibrary::Cat* cat = GetObject(handle);
    MyLibrary::Animal* animal = static_cast<MyLibrary::Animal*>(cat);
    return reinterpret_cast<mylib_animal_t*>(animal);
}

mylib_status_t MyLib_Cat_Fight(mylib_cat_t* handle, int bigger_cat, int* success)
{
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;
    if (success == nullptr)
        return MYLIB_STATUS_INVALID_ARGUMENT;

    *success = GetObject(handle)->fight(bigger_cat);

    return MYLIB_STATUS_OK;
}

mylib_status_t MyLib_Cat_StillAlive(mylib_cat_t* handle, int* is_alive)
{
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;
    if (is_alive == nullptr)
        return MYLIB_STATUS_INVALID_ARGUMENT;

    *is_alive = GetObject(handle)->stillAlive();

    return MYLIB_STATUS_OK;
}

mylib_status_t MyLib_Cat_Speak(mylib_cat_t* handle)
{
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;

    GetObject(handle)->speak();

    return MYLIB_STATUS_OK;
}

mylib_status_t MyLib_Cat_Speak_Multiple_Times(mylib_cat_t* handle, int times)
{
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;

    GetObject(handle)->speak(times);

    return MYLIB_STATUS_OK;
}

mylib_status_t MyLib_Cat_Sleep(mylib_cat_t* handle)
{
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;

    GetObject(handle)->sleep();

    return MYLIB_STATUS_OK;
}

mylib_status_t MyLib_Cat_Set_Name(mylib_cat_t* handle, char* name, int length)
{
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;

    GetObject(handle)->name = std::string(name, length);

    return MYLIB_STATUS_OK;
}

mylib_status_t MyLib_Cat_Get_Name(mylib_cat_t* handle, char* name, size_t buffer_size, int* length)
{
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;
    if (length == nullptr)
        return MYLIB_STATUS_INVALID_ARGUMENT;

    std::string _name = GetObject(handle)->name;
    *length = _name.length();

    if (buffer_size < *length)
        return MYLIB_STATUS_BUFFER_TOO_SMALL;

    // name can be null if only wants to get name length
    if (name == nullptr)
        return MYLIB_STATUS_INVALID_ARGUMENT;

    strcpy(name, _name.c_str());

    return MYLIB_STATUS_OK;
}
