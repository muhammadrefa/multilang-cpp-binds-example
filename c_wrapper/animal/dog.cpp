#include <stdexcept>
#include <cstddef>
#include <cstring>

#include "animal.h"
#include "dog.hpp"
#include "dog.h"

static MyLibrary::Dog* GetObject(mylib_dog_t* handle)
{
    return reinterpret_cast<MyLibrary::Dog*>(handle);
}

mylib_dog_t* MyLib_Dog_Create()
{
    try
    {
        MyLibrary::Dog *dog = new MyLibrary::Dog();
        return reinterpret_cast<mylib_dog_t*>(dog);
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

mylib_dog_t* MyLib_Dog_Create_With_Name(char* name, int length)
{
    std::string name_str(name, length);

    try
    {
        MyLibrary::Dog *dog = new MyLibrary::Dog(name_str);
        return reinterpret_cast<mylib_dog_t*>(dog);
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

mylib_status_t MyLib_Dog_Destroy(mylib_dog_t* handle)
{
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;

    delete GetObject(handle);
    
    return MYLIB_STATUS_OK;
}

mylib_animal_t* MyLib_Dog_As_Animal(mylib_dog_t* handle)
{
    MyLibrary::Dog* dog = GetObject(handle);
    MyLibrary::Animal* animal = static_cast<MyLibrary::Animal*>(dog);
    return reinterpret_cast<mylib_animal_t*>(animal);
}

mylib_status_t MyLib_Dog_Fetch(mylib_dog_t* handle, int* success)
{
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;
    if (success == nullptr)
        return MYLIB_STATUS_INVALID_ARGUMENT;

    *success = GetObject(handle)->fetch();

    return MYLIB_STATUS_OK;
}

mylib_status_t MyLib_Dog_GetEnergy(mylib_dog_t* handle, int* energy)
{
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;
    if (energy == nullptr)
        return MYLIB_STATUS_INVALID_ARGUMENT;

    *energy = GetObject(handle)->getEnergy();

    return MYLIB_STATUS_OK;
}

mylib_status_t MyLib_Dog_Speak(mylib_dog_t* handle)
{
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;

    GetObject(handle)->speak();

    return MYLIB_STATUS_OK;
}

mylib_status_t MyLib_Dog_Speak_Multiple_Times(mylib_dog_t* handle, int times)
{
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;

    GetObject(handle)->speak(times);

    return MYLIB_STATUS_OK;
}

mylib_status_t MyLib_Dog_Sleep(mylib_dog_t* handle)
{
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;

    GetObject(handle)->sleep();

    return MYLIB_STATUS_OK;
}

mylib_status_t MyLib_Dog_Set_Name(mylib_dog_t* handle, char* name, int length)
{
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;

    GetObject(handle)->name = std::string(name, length);

    return MYLIB_STATUS_OK;
}

mylib_status_t MyLib_Dog_Get_Name(mylib_dog_t* handle, char* name, size_t buffer_size, int* length)
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
