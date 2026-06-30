#pragma once

#include <stddef.h>
#include "../mylib_export.h"
#include "../status_code.h"

#include "animal.h"
#include "cat.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct mylib_tiger mylib_tiger_t;

// Constructor and destructor
MYLIB_API mylib_tiger_t* MyLib_Tiger_Create();
MYLIB_API mylib_tiger_t* MyLib_Tiger_Create_With_Name(char* name, int length);
MYLIB_API mylib_status_t MyLib_Tiger_Destroy(mylib_tiger_t* handle);

// Upcast Tiger to Cat
// This allows Cat functions to be used through the Cat interface
// Useful when accessing functionality provided by Cat API
MYLIB_API mylib_cat_t* MyLib_Tiger_As_Cat(mylib_tiger_t* handle);

// Specific Tiger methods
MYLIB_API mylib_status_t MyLib_Tiger_Hunt(mylib_tiger_t* handle);
MYLIB_API mylib_status_t MyLib_Tiger_GetHunger(mylib_tiger_t* handle, int* hunger);

// Wrapper for inherited Cat methods
// Consumers do not need to think about inheritance or upcasting
MYLIB_API mylib_status_t MyLib_Tiger_Fight(mylib_tiger_t* handle, int bigger_cat, int* success);
MYLIB_API mylib_status_t MyLib_Tiger_StillAlive(mylib_tiger_t* handle, int* is_alive);

// Wrapper for inherited Animal methods
// Consumers do not need to think about inheritance or upcasting
MYLIB_API mylib_status_t MyLib_Tiger_Speak(mylib_tiger_t* handle);
MYLIB_API mylib_status_t MyLib_Tiger_Speak_Multiple_Times(mylib_tiger_t* handle, int times);
MYLIB_API mylib_status_t MyLib_Tiger_Sleep(mylib_tiger_t* handle);

// Animal public data member
MYLIB_API mylib_status_t MyLib_Tiger_Set_Name(mylib_tiger_t* handle, char* name, int length);
MYLIB_API mylib_status_t MyLib_Tiger_Get_Name(mylib_tiger_t* handle, char* name, size_t buffer_size, int* length);

#ifdef __cplusplus
}
#endif
