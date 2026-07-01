#pragma once

#include <stddef.h>
#include "../mylib_export.h"
#include "../status_code.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct mylib_animal mylib_animal_t;

// Constructor and destructor
MYLIB_API mylib_animal_t* MyLib_Animal_Create();
MYLIB_API mylib_animal_t* MyLib_Animal_Create_With_Name(char* name, int length);
MYLIB_API mylib_status_t MyLib_Animal_Destroy(mylib_animal_t* handle);

// Animal methods
MYLIB_API mylib_status_t MyLib_Animal_Speak(mylib_animal_t* handle);
MYLIB_API mylib_status_t MyLib_Animal_Speak_Multiple_Times(mylib_animal_t* handle, int times);
MYLIB_API mylib_status_t MyLib_Animal_Sleep(mylib_animal_t* handle);

// Animal public data member
MYLIB_API mylib_status_t MyLib_Animal_Set_Name(mylib_animal_t* handle, char* name, int length);
MYLIB_API mylib_status_t MyLib_Animal_Get_Name(mylib_animal_t* handle, char* name, size_t buffer_size, int* length);

#ifdef __cplusplus
}
#endif
