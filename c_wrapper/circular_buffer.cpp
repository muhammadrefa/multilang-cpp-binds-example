#include <stdexcept>

#include "circular_buffer.hpp"
#include "circular_buffer.h"

static MyLibrary::CircularBuffer* GetObject(mylib_circular_buffer_t* handle)
{
    return reinterpret_cast<MyLibrary::CircularBuffer *>(handle);
}

mylib_circular_buffer_t* MyLib_CircularBuffer_Create(int bufsize)
{
    try
    {
        MyLibrary::CircularBuffer *circ_buff = new MyLibrary::CircularBuffer(bufsize);
        return reinterpret_cast<mylib_circular_buffer_t*>(circ_buff);
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

mylib_status_t MyLib_CircularBuffer_Destroy(mylib_circular_buffer_t* handle)
{
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;
    
    delete GetObject(handle);

    return MYLIB_STATUS_OK;
}

mylib_status_t MyLib_CircularBuffer_GetLength(mylib_circular_buffer_t* handle, int* returned_value)
{
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;
    if (returned_value == nullptr)
        return MYLIB_STATUS_INVALID_ARGUMENT;

    *returned_value = GetObject(handle)->getLength();

    return MYLIB_STATUS_OK;
}

mylib_status_t MyLib_CircularBuffer_Put(mylib_circular_buffer_t* handle, char* data, int length, int* returned_length)
{
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;

    int ret;
    try
    {
        ret = GetObject(handle)->put(data, length);
    }
    catch (const std::logic_error& e)
    {
        return MYLIB_STATUS_LOGIC_ERROR;
    }
    catch (const std::overflow_error& e)
    {
        return MYLIB_STATUS_OVERFLOW_ERROR;
    }
    
    if (returned_length != nullptr)
        *returned_length = ret;
        
    return MYLIB_STATUS_OK;
}

mylib_status_t MyLib_CircularBuffer_Get(mylib_circular_buffer_t* handle, char* dest, int length, int* returned_length)
{
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;
        
    int ret;
    try
    {
        ret = GetObject(handle)->get(dest, length);
    }
    catch (const std::logic_error& e)
    {
        return MYLIB_STATUS_LOGIC_ERROR;
    }
    catch (const std::range_error& e)
    {
        return MYLIB_STATUS_RANGE_ERROR;
    }
    
    if (returned_length != nullptr)
        *returned_length = ret;
        
    return MYLIB_STATUS_OK;
}

mylib_status_t MyLib_CircularBuffer_Clean(mylib_circular_buffer_t* handle, int* returned_length)
{
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;

    int ret = GetObject(handle)->clean();
    
    if (returned_length != nullptr)
        *returned_length = ret;
        
    return MYLIB_STATUS_OK;
}
