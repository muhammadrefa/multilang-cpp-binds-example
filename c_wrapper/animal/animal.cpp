#include <stdexcept>
#include <cstddef>
#include <cstring>

#include "animal.hpp"
#include "animal.h"

static MyLibrary::Animal* GetObject(mylib_animal_t* handle)
{
    return reinterpret_cast<MyLibrary::Animal*>(handle);
}

mylib_animal_t* MyLib_Animal_Create()
{
    try
    {
        MyLibrary::Animal *animal = new MyLibrary::Animal();
        return reinterpret_cast<mylib_animal_t*>(animal);
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

mylib_animal_t* MyLib_Animal_Create_With_Name(char* name, int length)
{
    std::string name_str(name, length);

    try
    {
        MyLibrary::Animal *animal = new MyLibrary::Animal(name_str);
        return reinterpret_cast<mylib_animal_t*>(animal);
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

mylib_status_t MyLib_Animal_Destroy(mylib_animal_t* handle)
{
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;

    delete GetObject(handle);
    
    return MYLIB_STATUS_OK;
}

mylib_status_t MyLib_Animal_Speak(mylib_animal_t* handle)
{
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;

    GetObject(handle)->speak();

    return MYLIB_STATUS_OK;
}

mylib_status_t MyLib_Animal_Speak_Multiple_Times(mylib_animal_t* handle, int times)
{
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;

    GetObject(handle)->speak(times);

    return MYLIB_STATUS_OK;
}

mylib_status_t MyLib_Animal_Sleep(mylib_animal_t* handle)
{
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;

    GetObject(handle)->sleep();

    return MYLIB_STATUS_OK;
}

mylib_status_t MyLib_Animal_Set_Name(mylib_animal_t* handle, char* name, int length)
{
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;

    GetObject(handle)->name = std::string(name, length);

    return MYLIB_STATUS_OK;
}

mylib_status_t MyLib_Animal_Get_Name(mylib_animal_t* handle, char* name, size_t buffer_size, int* length)
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
