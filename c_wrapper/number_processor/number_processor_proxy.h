#pragma once

#include <stddef.h>
#include "../mylib_export.h"
#include "../status_code.h"
#include "number_processor.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct mylib_NumberProcessorProxy mylib_NumberProcessorProxy_t;

typedef struct
{
    void (*cb_process)(mylib_NumberProcessorProxy_t*) = nullptr;
    void (*cb_print_number)(mylib_NumberProcessorProxy_t*) = nullptr;
} mylib_NumberProcessorProxy_cb_t;


// Constructor and Destructor
MYLIB_API mylib_NumberProcessorProxy_t* MyLib_NumberProcessorProxy_Create(mylib_NumberProcessorProxy_cb_t* callback);
MYLIB_API mylib_status_t MyLib_NumberProcessorProxy_Destroy(mylib_NumberProcessorProxy_t* handle);
MYLIB_API mylib_NumberProcessor_t* MyLib_NumberProcessorProxy_As_NumberProcessor(mylib_NumberProcessorProxy_t* handle);
MYLIB_API mylib_NumberProcessorProxy_t* MyLib_NumberProcessorProxy_From_NumberProcessor(mylib_NumberProcessor_t* handle);
MYLIB_API mylib_NumberProcessorProxy_t* MyLib_NumberProcessorProxy_From_NumberProcessor2(mylib_NumberProcessor_t* handle, mylib_NumberProcessorProxy_cb_t* callback);

MYLIB_API mylib_NumberProcessorProxy_t* MyLib_NumberProcessorProxy_Attach_NumberProcessor(mylib_NumberProcessor_t* handle);
MYLIB_API mylib_status_t* MyLib_NumberProcessorProxy_Detach_NumberProcessor(mylib_NumberProcessorProxy_t* handle);

// calls base method
MYLIB_API mylib_status_t MyLib_NumberProcessorProxy_CallBase_PrintNumber(mylib_NumberProcessorProxy_t* handle);

#ifdef __cplusplus
}
#endif
