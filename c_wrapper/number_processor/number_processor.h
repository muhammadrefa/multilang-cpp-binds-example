#pragma once

#include <stddef.h>
#include "../mylib_export.h"
#include "../status_code.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct mylib_number_processor mylib_number_processor_t;

// Destructor
// (abstract class does not have any constructor)
MYLIB_API mylib_status_t MyLib_NumberProcessor_Destroy(mylib_number_processor_t* handle);

// Virtual methods
MYLIB_API mylib_status_t MyLib_NumberProcessor_Process(mylib_number_processor_t* handle);

// Implemented methods
MYLIB_API mylib_status_t MyLib_NumberProcessor_GetNumber(mylib_number_processor_t* handle, int* number);
MYLIB_API mylib_status_t MyLib_NumberProcessor_SetNumber(mylib_number_processor_t* handle, int  number);
MYLIB_API mylib_status_t MyLib_NumberProcessor_PrintNumber(mylib_number_processor_t* handle);

#ifdef __cplusplus
}
#endif
