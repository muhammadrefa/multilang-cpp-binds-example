#include <stdio.h>
#include "cprocess_add3.h"

static void CProcess_Add3_process(mylib_number_processor_proxy_t* handle);
static void CProcess_Add3_PrintNumber(mylib_number_processor_proxy_t* handle);

static mylib_number_processor_proxy_cb_t callback = {
    .cb_process = CProcess_Add3_process,
    .cb_print_number = CProcess_Add3_PrintNumber
};

static void CProcess_Add3_process(mylib_number_processor_proxy_t* handle)
{
    int number;
    // get number
    MyLib_NumberProcessor_GetNumber(MyLib_NumberProcessorProxy_As_NumberProcessor(handle), &number);
    // add 3
    number += 3;
    // set number
    MyLib_NumberProcessor_SetNumber(MyLib_NumberProcessorProxy_As_NumberProcessor(handle), number);
}

static void CProcess_Add3_PrintNumber(mylib_number_processor_proxy_t* handle)
{
    printf("Cprocess print number -> ");
    MyLib_NumberProcessorProxy_CallBase_PrintNumber(handle);
}

mylib_cprocess_add3_t* MyLib_CProcessAdd3_Create()
{
    mylib_number_processor_proxy_t *proxy = MyLib_NumberProcessorProxy_Create();
    if (proxy == NULL)
        return NULL;
    MyLib_NumberProcessorProxy_SetCallback(proxy, &callback);
    return (mylib_cprocess_add3_t *)proxy;
}

mylib_status_t MyLib_CProcessAdd3_Destroy(mylib_cprocess_add3_t* handle)
{
    return MyLib_NumberProcessorProxy_Destroy((mylib_number_processor_proxy_t *)handle);
}

mylib_number_processor_t* MyLib_CProcessAdd3_As_NumberProcessor(mylib_cprocess_add3_t* handle)
{
    return MyLib_NumberProcessorProxy_As_NumberProcessor((mylib_number_processor_proxy_t *)handle);
}

// ----- C wrapper for the C++ class ----- //
