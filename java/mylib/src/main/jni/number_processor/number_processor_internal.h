#pragma once

#include "number_processor/number_processor.h"

#ifdef __cplusplus
extern "C" {
#endif

mylib_NumberProcessor_t* NumberProcessor_Internal_NumberProcessor_get_handle(jlong handle);

#ifdef __cplusplus
}
#endif