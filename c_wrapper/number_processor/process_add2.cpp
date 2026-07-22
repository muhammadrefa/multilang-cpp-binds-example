#include <stdexcept>

#include "number_processor.h"
#include "process_add2.hpp"
#include "process_add2.h"

static MyLibrary::ProcessAdd2* GetObject(mylib_process_add2_t* handle)
{
    return reinterpret_cast<MyLibrary::ProcessAdd2*>(handle);
}

mylib_process_add2_t* MyLib_ProcessAdd2_Create()
{
    try
    {
        MyLibrary::ProcessAdd2 *add2 = new MyLibrary::ProcessAdd2();
        return reinterpret_cast<mylib_process_add2_t*>(add2);
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

mylib_status_t MyLib_ProcessAdd2_Destroy(mylib_process_add2_t* handle)
{
    if (handle == nullptr)
        return MYLIB_STATUS_INVALID_HANDLE;

    delete GetObject(handle);
    
    return MYLIB_STATUS_OK;
}

mylib_number_processor_t* MyLib_ProcessAdd2_As_NumberProcessor(mylib_process_add2_t* handle)
{
    MyLibrary::ProcessAdd2* add2 = GetObject(handle);
    MyLibrary::NumberProcessor* np = static_cast<MyLibrary::NumberProcessor*>(add2);
    return reinterpret_cast<mylib_number_processor_t*>(np);
}
