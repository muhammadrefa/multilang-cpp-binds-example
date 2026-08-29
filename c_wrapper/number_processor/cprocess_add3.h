#pragma once

#include <stddef.h>
#include "../mylib_export.h"
#include "../status_code.h"
#include "number_processor_proxy.h"

typedef struct mylib_CProcessAdd3 mylib_CProcessAdd3_t;

// Constructor and Destructor
MYLIB_API mylib_CProcessAdd3_t* MyLib_CProcessAdd3_Create();
MYLIB_API mylib_status_t MyLib_CProcessAdd3_Destroy(mylib_CProcessAdd3_t* handle);
MYLIB_API mylib_NumberProcessor_t* MyLib_CProcessAdd3_As_NumberProcessor(mylib_CProcessAdd3_t* handle);
MYLIB_API mylib_CProcessAdd3_t* MyLib_CProcessAdd3_From_NumberProcessor(mylib_NumberProcessor_t* handle);

// specific method
MYLIB_API mylib_status_t MyLib_CProcessAdd3_Hello(mylib_CProcessAdd3_t* handle);
