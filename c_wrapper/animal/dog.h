#pragma once

#include <stddef.h>
#include "../mylib_export.h"
#include "../status_code.h"

#include "animal.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct mylib_dog mylib_dog_t;

// Constructor and destructor
MYLIB_API mylib_dog_t* MyLib_Dog_Create();
MYLIB_API mylib_dog_t* MyLib_Dog_Create_With_Name(char* name, int length);
MYLIB_API mylib_status_t MyLib_Dog_Destroy(mylib_dog_t* handle);

// Upcast Dog to Animal
// This allows Animal functions to be used through the Animal interface
// Useful when accessing functionality provided by Animal API
MYLIB_API mylib_animal_t* MyLib_Dog_As_Animal(mylib_dog_t* handle);

// Specific Dog methods
MYLIB_API mylib_status_t MyLib_Dog_Fetch(mylib_dog_t* handle, int* success);
MYLIB_API mylib_status_t MyLib_Dog_GetEnergy(mylib_dog_t* handle, int* energy);

// Overridden Animal methods
MYLIB_API mylib_status_t MyLib_Dog_Speak(mylib_dog_t* handle);
MYLIB_API mylib_status_t MyLib_Dog_Sleep(mylib_dog_t* handle);

// Wrapper for inherited Animal methods
// Consumers do not need to think about inheritance or upcasting
MYLIB_API mylib_status_t MyLib_Dog_Speak_Multiple_Times(mylib_dog_t* handle, int times);

// Animal public data member
MYLIB_API mylib_status_t MyLib_Dog_Set_Name(mylib_dog_t* handle, char* name, int length);
MYLIB_API mylib_status_t MyLib_Dog_Get_Name(mylib_dog_t* handle, char* name, size_t buffer_size, int* length);


#ifdef __cplusplus
}
#endif
