#include <iostream>
#include <cstdio>

#include "calculator.hpp"
#include "circular_buffer.hpp"

void calculator_check()
{
    int val;
    // initialise calculator
    MyLibrary::Calculator *calc = new MyLibrary::Calculator();

    // addition
    val = calc->add(1, 1);
    printf("1 + 1 = %d\n", val);
    val = calc->add(2, 3);
    printf("2 + 3 = %d\n", val);

    // check ops num
    val = calc->cntOpsDone();
    printf("ops done %d\n", val);

    // subtraction
    val = calc->sub(4, 3);
    printf("4 - 3 = %d\n", val);
    val = calc->sub(1, 4);
    printf("1 - 4 = %d\n", val);

    // check ops num
    val = calc->cntOpsDone();
    printf("ops done %d\n", val);

    // reset
    val = calc->resetCounter();
    printf("counter resetted! last count %d\n", val);

    // check ops num
    val = calc->cntOpsDone();
    printf("ops done %d\n", val);

    // 1 addition
    val = calc->add(100, 120);
    printf("100 + 120 = %d\n", val);

    // check ops num
    val = calc->cntOpsDone();
    printf("ops done %d\n", val);\

    // destroy
    delete calc;
}

void circbuff_check()
{
    int len = 0;
    char arr[10];

    // initialise circbuff
    MyLibrary::CircularBuffer *buf = new MyLibrary::CircularBuffer(10);

    // insert 3
    len = buf->put("abcd", 3);
    printf("put %d filled %d\n", len, buf->getLength());

    // insert 5
    len = buf->put("12345", 5);
    printf("put %d filled %d\n", len, buf->getLength());

    // get 4
    len = buf->get(arr, 4);
    arr[4] = NULL;
    printf("get %d filled %d data %s\n", len, buf->getLength(), arr);

    // insert 5
    len = buf->put("abcde", 5);
    printf("put %d filled %d\n", len, buf->getLength());

    // clean
    len = buf->clean();
    printf("cleaned %d! filled %d\n", len, buf->getLength());

    // destroy
    delete buf;
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
