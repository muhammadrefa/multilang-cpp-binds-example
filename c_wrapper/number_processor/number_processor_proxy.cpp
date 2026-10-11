#include <iostream>

#include "number_processor_internal.hpp"
#include "number_processor_proxy.hpp"
#include "number_processor_proxy.h"

// ----- Implementation of abstract C++ class ----- //

MyLibrary::NumberProcessorProxy::NumberProcessorProxy()
{
    // upcast and store the base handle for base class operation
    MyLibrary::NumberProcessorProxy* proxy = this;
    MyLibrary::NumberProcessor* np = static_cast<MyLibrary::NumberProcessor*>(proxy);
    this->base_handle = reinterpret_cast<mylib_NumberProcessor_t*>(np);
}

MyLibrary::NumberProcessorProxy::NumberProcessorProxy(mylib_NumberProcessor_t* base_handle)
{
    // use the supplied base handle for base class operation
    this->base_handle = base_handle;
}

MyLibrary::NumberProcessorProxy::~NumberProcessorProxy()
{

}

mylib_NumberProcessorProxy_t* MyLibrary::NumberProcessorProxy::GetSelfHandle()
{
    NumberProcessorProxy* handle = this;
    return reinterpret_cast<mylib_NumberProcessorProxy_t*>(handle);
}

void MyLibrary::NumberProcessorProxy::SetCallback(mylib_NumberProcessorProxy_cb_t* callback)
{    
    // store the struct values instead of only storing the pointer to the struct
    // by doing this way, the lifetime of the struct passed to this function can be ignored
    if (callback != nullptr)
        cb = *callback;
}

void MyLibrary::NumberProcessorProxy::process()
{
    if (cb.cb_process != nullptr)
        cb.cb_process(GetSelfHandle());
}

void MyLibrary::NumberProcessorProxy::PrintNumber()
{
    if (cb.cb_print_number != nullptr)
        return cb.cb_print_number(GetSelfHandle());
    return MyLibrary::NumberProcessor::PrintNumber();
}

// ----- Implementation of abstract C++ class ----- //

// ----- C wrapper for the C++ class ----- //

static MyLibrary::NumberProcessorProxy* GetObject(mylib_NumberProcessorProxy_t* handle)
{
    return reinterpret_cast<MyLibrary::NumberProcessorProxy*>(handle);
}

mylib_NumberProcessorProxy_t* MyLib_NumberProcessorProxy_Create(mylib_NumberProcessorProxy_cb_t* callback)
{
    try
    {
        MyLibrary::NumberProcessorProxy *_proxy = new MyLibrary::NumberProcessorProxy();
        mylib_NumberProcessorProxy_t* proxy = reinterpret_cast<mylib_NumberProcessorProxy_t*>(_proxy);
        _proxy->SetCallback(callback);
        return proxy;
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
    return GetObject(handle)->GetBaseHandle();
}

mylib_NumberProcessorProxy_t* MyLib_NumberProcessorProxy_From_NumberProcessor(mylib_NumberProcessor_t* handle)
{
    MyLibrary::NumberProcessor* np = MyLib_NumberProcessor_Internal_GetObject(handle);
    MyLibrary::NumberProcessorProxy* proxy = static_cast<MyLibrary::NumberProcessorProxy*>(np);

    mylib_NumberProcessorProxy_t* _proxy = reinterpret_cast<mylib_NumberProcessorProxy_t*>(proxy);
    
    return _proxy;
}

mylib_NumberProcessorProxy_t* MyLib_NumberProcessorProxy_Attach_NumberProcessor(mylib_NumberProcessor_t* handle, mylib_NumberProcessorProxy_cb_t* callback)
{
    try
    {
        // Create NPP
        MyLibrary::NumberProcessorProxy *_proxy = new MyLibrary::NumberProcessorProxy();
        mylib_NumberProcessorProxy_t* proxy = reinterpret_cast<mylib_NumberProcessorProxy_t*>(_proxy);

        // Cast NP handle to NPP handle for callback
        MyLibrary::NumberProcessor* np_handle = MyLib_NumberProcessor_Internal_GetObject(handle);
        MyLibrary::NumberProcessorProxy* casted_handle = static_cast<MyLibrary::NumberProcessorProxy*>(np_handle);
        mylib_NumberProcessorProxy_t* _casted_handle = reinterpret_cast<mylib_NumberProcessorProxy_t*>(casted_handle);

        // Use casted handle for callback
        _proxy->SetCallback(_casted_handle, callback);
        return proxy;
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

mylib_status_t MyLib_NumberProcessorProxy_CallBase_PrintNumber(mylib_NumberProcessorProxy_t* handle)
{
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;

    GetObject(handle)->MyLibrary::NumberProcessor::PrintNumber();

    return MYLIB_STATUS_OK;
}

// ----- C wrapper for the C++ class ----- //
