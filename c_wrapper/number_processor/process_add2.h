#pragma once

#include <stddef.h>
#include "../mylib_export.h"
#include "../status_code.h"
#include "number_processor.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct mylib_process_add2 mylib_process_add2_t;

// Constructor and Destructor
MYLIB_API mylib_process_add2_t* MyLib_ProcessAdd2_Create();
MYLIB_API mylib_status_t MyLib_ProcessAdd2_Destroy(mylib_process_add2_t* handle);
MYLIB_API mylib_number_processor_t* MyLib_ProcessAdd2_As_NumberProcessor(mylib_process_add2_t* handle);

#ifdef __cplusplus
}
#endif
