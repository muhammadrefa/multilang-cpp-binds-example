#include <stdio.h>
#include "cprocess_add3.h"

static void CProcess_Add3_process(mylib_NumberProcessorProxy_t* handle);
static void CProcess_Add3_PrintNumber(mylib_NumberProcessorProxy_t* handle);

static mylib_NumberProcessorProxy_cb_t callback = {
    .cb_process = CProcess_Add3_process,
    .cb_print_number = CProcess_Add3_PrintNumber
};

static void CProcess_Add3_process(mylib_NumberProcessorProxy_t* handle)
{
    int number;
    // get number
    MyLib_NumberProcessor_GetNumber(MyLib_NumberProcessorProxy_As_NumberProcessor(handle), &number);
    // add 3
    number += 3;
    // set number
    MyLib_NumberProcessor_SetNumber(MyLib_NumberProcessorProxy_As_NumberProcessor(handle), number);
}

static void CProcess_Add3_PrintNumber(mylib_NumberProcessorProxy_t* handle)
{
    printf("Cprocess print number -> ");
    MyLib_NumberProcessorProxy_CallBase_PrintNumber(handle);
}

mylib_CProcessAdd3_t* MyLib_CProcessAdd3_Create()
{
    mylib_NumberProcessorProxy_t *proxy = MyLib_NumberProcessorProxy_Create(&callback);
    if (proxy == NULL)
        return NULL;
    return (mylib_CProcessAdd3_t *)proxy;
}

mylib_status_t MyLib_CProcessAdd3_Destroy(mylib_CProcessAdd3_t* handle)
{
    return MyLib_NumberProcessorProxy_Destroy((mylib_NumberProcessorProxy_t *)handle);
}

mylib_NumberProcessor_t* MyLib_CProcessAdd3_As_NumberProcessor(mylib_CProcessAdd3_t* handle)
{
    return MyLib_NumberProcessorProxy_As_NumberProcessor((mylib_NumberProcessorProxy_t *)handle);
}

mylib_CProcessAdd3_t* MyLib_CProcessAdd3_From_NumberProcessor(mylib_NumberProcessor_t* handle)
{
    return (mylib_CProcessAdd3_t *)MyLib_NumberProcessorProxy_From_NumberProcessor(handle);
}

mylib_status_t MyLib_CProcessAdd3_Hello(mylib_CProcessAdd3_t* handle)
{
    printf("Hello from C!\n");
    return MYLIB_STATUS_OK;
}

// ----- C wrapper for the C++ class ----- //
