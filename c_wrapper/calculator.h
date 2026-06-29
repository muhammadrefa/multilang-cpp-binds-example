#pragma once

#include "mylib_export.h"
#include "status_code.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct mylib_calculator mylib_calculator_t;

MYLIB_API mylib_calculator_t* MyLib_Calculator_Create();
MYLIB_API mylib_status_t MyLib_Calculator_Destroy(mylib_calculator_t* handle);
MYLIB_API mylib_status_t MyLib_Calculator_Add(mylib_calculator_t* handle, int a, int b, int* retval);
MYLIB_API mylib_status_t MyLib_Calculator_Sub(mylib_calculator_t* handle, int a, int b, int* retval);
MYLIB_API mylib_status_t MyLib_Calculator_CntOpsDone(mylib_calculator_t* handle, int* retval);
MYLIB_API mylib_status_t MyLib_Calculator_ResetCounter(mylib_calculator_t* handle, int* retval);

#ifdef __cplusplus
}
#endif
