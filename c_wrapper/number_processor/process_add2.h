#pragma once

#include <stddef.h>
#include "../mylib_export.h"
#include "../status_code.h"
#include "number_processor.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct mylib_ProcessAdd2 mylib_ProcessAdd2_t;

// Constructor and Destructor
MYLIB_API mylib_ProcessAdd2_t* MyLib_ProcessAdd2_Create();
MYLIB_API mylib_status_t MyLib_ProcessAdd2_Destroy(mylib_ProcessAdd2_t* handle);
MYLIB_API mylib_NumberProcessor_t* MyLib_ProcessAdd2_As_NumberProcessor(mylib_ProcessAdd2_t* handle);
MYLIB_API mylib_ProcessAdd2_t* MyLib_ProcessAdd2_From_NumberProcessor(mylib_NumberProcessor_t* handle);

#ifdef __cplusplus
}
#endif
