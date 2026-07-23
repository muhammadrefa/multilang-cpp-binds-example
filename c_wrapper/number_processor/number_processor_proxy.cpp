#include <iostream>
#include "number_processor_proxy.hpp"
#include "number_processor_proxy.h"

// ----- Implementation of abstract C++ class ----- //

MyLibrary::NumberProcessorProxy::NumberProcessorProxy()
{

}

MyLibrary::NumberProcessorProxy::~NumberProcessorProxy()
{

}

void MyLibrary::NumberProcessorProxy::SetCallback(mylib_NumberProcessorProxy_t* handle, mylib_NumberProcessorProxy_cb_t* callback)
{
    this->handle = handle;
    cb = *callback;
}

void MyLibrary::NumberProcessorProxy::process()
{
    if (cb.cb_process != nullptr)
        cb.cb_process(handle);
}

void MyLibrary::NumberProcessorProxy::PrintNumber()
{
    if (cb.cb_print_number != nullptr)
        return cb.cb_print_number(handle);
    return MyLibrary::NumberProcessor::PrintNumber();
}

// ----- Implementation of abstract C++ class ----- //

// ----- C wrapper for the C++ class ----- //

static MyLibrary::NumberProcessorProxy* GetObject(mylib_NumberProcessorProxy_t* handle)
{
    return reinterpret_cast<MyLibrary::NumberProcessorProxy*>(handle);
}

mylib_NumberProcessorProxy_t* MyLib_NumberProcessorProxy_Create()
{
    try
    {
        MyLibrary::NumberProcessorProxy *proxy = new MyLibrary::NumberProcessorProxy();
        return reinterpret_cast<mylib_NumberProcessorProxy_t*>(proxy);
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

mylib_status_t MyLib_NumberProcessorProxy_Destroy(mylib_NumberProcessorProxy_t* handle)
{
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;

    delete GetObject(handle);
    
    return MYLIB_STATUS_OK;
}

mylib_NumberProcessor_t* MyLib_NumberProcessorProxy_As_NumberProcessor(mylib_NumberProcessorProxy_t* handle)
{
    MyLibrary::NumberProcessorProxy* proxy = GetObject(handle);
    MyLibrary::NumberProcessor* np = static_cast<MyLibrary::NumberProcessor*>(proxy);
    return reinterpret_cast<mylib_NumberProcessor_t*>(np);
}

void MyLib_NumberProcessorProxy_SetCallback(mylib_NumberProcessorProxy_t* handle, mylib_NumberProcessorProxy_cb_t* callback)
{
    GetObject(handle)->SetCallback(handle, callback);
}

mylib_status_t MyLib_NumberProcessorProxy_CallBase_PrintNumber(mylib_NumberProcessorProxy_t* handle)
{
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;

    GetObject(handle)->MyLibrary::NumberProcessor::PrintNumber();

    return MYLIB_STATUS_OK;
}

// ----- C wrapper for the C++ class ----- //
