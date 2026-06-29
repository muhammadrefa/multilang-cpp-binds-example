#include <stdio.h>

#include "calculator.h"
#include "circular_buffer.h"
#include "status_code.h"

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

int main()
{
    printf("--- calculator check ---\n");
    calculator_check();
    printf("\n");

    printf("--- circbuff check ---\n");
    circbuff_check();
    printf("\n");

    return 0;
}
