#pragma once

#include <stddef.h>
#include "../mylib_export.h"
#include "../status_code.h"
#include "number_processor_proxy.h"

typedef struct mylib_cprocess_add3 mylib_cprocess_add3_t;

// Constructor and Destructor
MYLIB_API mylib_cprocess_add3_t* MyLib_CProcessAdd3_Create();
MYLIB_API mylib_status_t MyLib_CProcessAdd3_Destroy(mylib_cprocess_add3_t* handle);
MYLIB_API mylib_number_processor_t* MyLib_CProcessAdd3_As_NumberProcessor(mylib_cprocess_add3_t* handle);
