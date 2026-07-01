#include <stdio.h>
#include <string.h>

#include "calculator.h"
#include "circular_buffer.h"
#include "status_code.h"

#include "animal/animal.h"
#include "animal/dog.h"
#include "animal/cat.h"
#include "animal/tiger.h"

void calculator_check()
{
    int val;
    mylib_status_t status;

    // initialise calculator
    mylib_calculator_t* calc = MyLib_Calculator_Create();

    // addition
    status = MyLib_Calculator_Add(calc, 1, 1, &val);
    printf("1 + 1 = %d\n", val);
    status = MyLib_Calculator_Add(calc, 2, 3, &val);
    printf("2 + 3 = %d\n", val);

    // check ops num
    status = MyLib_Calculator_CntOpsDone(calc, &val);
    printf("ops done %d\n", val);

    // error argument invalid
    status = MyLib_Calculator_Add(calc, 3, 4, NULL);
    printf("status=%d\n", status);

    // subtraction
    status = MyLib_Calculator_Sub(calc, 4, 3, &val);
    printf("4 - 3 = %d\n", val);
    status = MyLib_Calculator_Sub(calc, 1, 4, &val);
    printf("1 - 4 = %d\n", val);

    // check ops num
    status = MyLib_Calculator_CntOpsDone(calc, &val);
    printf("ops done %d\n", val);

    // reset
    status = MyLib_Calculator_ResetCounter(calc, &val);
    printf("counter resetted! last count %d\n", val);

    // check ops num
    status = MyLib_Calculator_CntOpsDone(calc, &val);
    printf("ops done %d\n", val);

    // 1 addition
    status = MyLib_Calculator_Add(calc, 100, 120, &val);
    printf("100 + 120 = %d\n", val);

    // check ops num
    status = MyLib_Calculator_CntOpsDone(calc, &val);
    printf("ops done %d\n", val);

    // destroy
    MyLib_Calculator_Destroy(calc);
}

void circbuff_check()
{
    mylib_status_t status;
    int len = 0;
    int len2 = 0;
    char arr[10];

    // initialise circbuff
    mylib_circular_buffer_t* buf = MyLib_CircularBuffer_Create(10);

    // insert 3
    status = MyLib_CircularBuffer_Put(buf, "abcd", 3, &len);
    status = MyLib_CircularBuffer_GetLength(buf, &len2);
    printf("put %d filled %d\n", len, len2);

    // insert 5
    status = MyLib_CircularBuffer_Put(buf, "12345", 5, &len);
    status = MyLib_CircularBuffer_GetLength(buf, &len2);
    printf("put %d filled %d\n", len, len2);

    // get 4
    status = MyLib_CircularBuffer_Get(buf, arr, 4, &len);
    arr[4] = 0;
    status = MyLib_CircularBuffer_GetLength(buf, &len2);
    printf("get %d filled %d data %s\n", len, len2, arr);

    // insert 5
    status = MyLib_CircularBuffer_Put(buf, "abcde", 5, &len);
    status = MyLib_CircularBuffer_GetLength(buf, &len2);
    printf("put %d filled %d\n", len, len2);

    // clean
    status = MyLib_CircularBuffer_Clean(buf, &len);
    status = MyLib_CircularBuffer_GetLength(buf, &len2);
    printf("cleaned %d! filled %d\n", len, len2);

    // argument is optional
    status = MyLib_CircularBuffer_Clean(buf, NULL);
    printf("status=%d\n", status);

    // destroy
    MyLib_CircularBuffer_Destroy(buf);
}

void animal_check()
{
    mylib_status_t status;

    // create animal1
    mylib_animal_t *animal1 = MyLib_Animal_Create();
    status = MyLib_Animal_Set_Name(animal1, "specimen1", strlen("specimen1"));
    status = MyLib_Animal_Speak(animal1);

    // create animal2
    mylib_animal_t *animal2 = MyLib_Animal_Create_With_Name("specimen2", strlen("specimen2"));
    status = MyLib_Animal_Speak_Multiple_Times(animal2, 3);

    // adopt a dog
    mylib_dog_t *dog = MyLib_Dog_Create_With_Name("Pluto", strlen("Pluto"));
    status = MyLib_Dog_Speak(dog);
    char dog_name[10];
    int dog_name_len = 0;
    status = MyLib_Dog_Get_Name(dog, dog_name, sizeof(dog_name), &dog_name_len);
    int fetch_result = 0;
    for (int i=0; i<7; ++i)
    {
        status = MyLib_Dog_Fetch(dog, &fetch_result);
        if (fetch_result)
            printf("%s fetched the stick!\n", dog_name);
        else
            printf("%s did not fetch the stick!\n", dog_name);
    }
    int dog_energy = 0;
    status = MyLib_Dog_GetEnergy(dog, &dog_energy);
    printf("%s energy: %d\n", dog_name, dog_energy);
    status = MyLib_Dog_Sleep(dog);
    status = MyLib_Dog_Fetch(dog, &fetch_result);
    if (fetch_result)
        printf("%s fetched the stick!\n", dog_name);
    
    // adopt a cat
    mylib_cat_t *cat = MyLib_Cat_Create_With_Name("Pretty", strlen("Pretty"));
    status = MyLib_Cat_Speak_Multiple_Times(cat, 2);
    char cat_name[10];
    int cat_name_len = 0;
    int cat_fight_success;
    status = MyLib_Cat_Get_Name(cat, cat_name, sizeof(cat_name), &cat_name_len);
    status = MyLib_Cat_Fight(cat, 0, &cat_fight_success);
    status = MyLib_Cat_Fight(cat, 1, &cat_fight_success);
    status = MyLib_Cat_Fight(cat, 1, &cat_fight_success);
    status = MyLib_Cat_Fight(cat, 0, &cat_fight_success);
    int is_cat_alive;
    status = MyLib_Cat_StillAlive(cat, &is_cat_alive);
    if (is_cat_alive)
        printf("%s still alive\n", cat_name);
    else
        printf("%s died\n", cat_name);
    for (int i=0; i<9; ++i)
        status = MyLib_Cat_Fight(cat, 1, &cat_fight_success);
    status = MyLib_Cat_StillAlive(cat, &is_cat_alive);
    if (is_cat_alive)
        printf("%s still alive\n", cat_name);
    else
        printf("%s died\n", cat_name);

    // adopt a tiger (?)
    mylib_tiger_t *tiger = MyLib_Tiger_Create_With_Name("Tigris", strlen("Tigris"));
    status = MyLib_Tiger_Speak_Multiple_Times(tiger, 3);
    char tiger_name[10];
    int tiger_name_len = 0;
    int tiger_fight_success;
    status = MyLib_Tiger_Get_Name(tiger, tiger_name, sizeof(tiger_name), &tiger_name_len);
    
    status = MyLib_Tiger_Fight(tiger, 0, &tiger_fight_success);
    status = MyLib_Tiger_Fight(tiger, 1, &tiger_fight_success);

    // call fight using cat
    status = MyLib_Cat_Fight(MyLib_Tiger_As_Cat(tiger), 1, &tiger_fight_success);
    status = MyLib_Cat_Fight(MyLib_Tiger_As_Cat(tiger), 0, &tiger_fight_success);

    int is_tiger_alive;
    status = MyLib_Tiger_StillAlive(tiger, &is_tiger_alive);
    if (is_tiger_alive)
        printf("%s still alive\n", tiger_name);
    else
        printf("%s died\n", tiger_name);
    int tiger_hunger;
    status = MyLib_Tiger_GetHunger(tiger, &tiger_hunger);
    printf("%s hunger level: %d\n", tiger_name, tiger_hunger);
    status = MyLib_Tiger_Hunt(tiger);
    status = MyLib_Tiger_Hunt(tiger);
    status = MyLib_Tiger_GetHunger(tiger, &tiger_hunger);
    printf("%s hunger level: %d\n", tiger_name, tiger_hunger);
    status = MyLib_Tiger_Sleep(tiger);
    status = MyLib_Tiger_GetHunger(tiger, &tiger_hunger);
    printf("%s hunger level: %d\n", tiger_name, tiger_hunger);
    
    // kill them :(
    MyLib_Animal_Destroy(animal1);
    MyLib_Animal_Destroy(animal2);
    MyLib_Dog_Destroy(dog);
    MyLib_Cat_Destroy(cat);
    MyLib_Tiger_Destroy(tiger);
}

int main()
{
    printf("--- calculator check ---\n");
    calculator_check();
    printf("\n");

    printf("--- circbuff check ---\n");
    circbuff_check();
    printf("\n");

    printf("--- animal check ---\n");
    animal_check();
    printf("\n");

    return 0;
}
