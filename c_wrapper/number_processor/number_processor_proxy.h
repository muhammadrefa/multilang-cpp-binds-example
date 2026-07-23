#pragma once

#include <stddef.h>
#include "../mylib_export.h"
#include "../status_code.h"
#include "number_processor.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct mylib_number_processor_proxy mylib_number_processor_proxy_t;

typedef struct
{
    void (*cb_process)(mylib_number_processor_proxy_t*);
    void (*cb_print_number)(mylib_number_processor_proxy_t*);
} mylib_number_processor_proxy_cb_t;


// Constructor and Destructor
MYLIB_API mylib_number_processor_proxy_t* MyLib_NumberProcessorProxy_Create();
MYLIB_API mylib_status_t MyLib_NumberProcessorProxy_Destroy(mylib_number_processor_proxy_t* handle);
MYLIB_API mylib_number_processor_t* MyLib_NumberProcessorProxy_As_NumberProcessor(mylib_number_processor_proxy_t* handle);

// set callback
MYLIB_API void MyLib_NumberProcessorProxy_SetCallback(mylib_number_processor_proxy_t* handle, mylib_number_processor_proxy_cb_t* callback);

// calls base method
MYLIB_API mylib_status_t MyLib_NumberProcessorProxy_CallBase_PrintNumber(mylib_number_processor_proxy_t* handle);

#ifdef __cplusplus
}
#endif
