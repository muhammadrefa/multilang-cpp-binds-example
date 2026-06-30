#pragma once

#include "../mylib_export.h"
#include "../status_code.h"

#include "animal.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct mylib_cat mylib_cat_t;

// Constructor and destructor
MYLIB_API mylib_cat_t* MyLib_Cat_Create();
MYLIB_API mylib_cat_t* MyLib_Cat_Create_With_Name(char* name, int length);
MYLIB_API mylib_status_t MyLib_Cat_Destroy(mylib_cat_t* handle);

// Upcast Cat to Animal
// This allows Animal functions to be used through the Animal interface
// Useful when accessing functionality provided by Animal API
MYLIB_API mylib_animal_t* MyLib_Cat_As_Animal(mylib_cat_t* handle);

// Specific Cat methods
MYLIB_API mylib_status_t MyLib_Cat_Fight(mylib_cat_t* handle, int bigger_cat, int* success);
MYLIB_API mylib_status_t MyLib_Cat_StillAlive(mylib_cat_t* handle, int* is_alive);

// Wrapper for inherited Animal methods
// Consumers do not need to think about inheritance or upcasting
MYLIB_API mylib_status_t MyLib_Cat_Speak(mylib_cat_t* handle);
MYLIB_API mylib_status_t MyLib_Cat_Speak_Multiple_Times(mylib_cat_t* handle, int times);
MYLIB_API mylib_status_t MyLib_Cat_Sleep(mylib_cat_t* handle);

#ifdef __cplusplus
}
#endif
