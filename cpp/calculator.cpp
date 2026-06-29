#include <cstdint>
#include <cstdlib>
#include <cstring>

#include <stdexcept>

#include "calculator.hpp"


MyLibrary::Calculator::Calculator()
{

}

MyLibrary::Calculator::~Calculator()
{

}

int MyLibrary::Calculator::add(int a, int b)
{
    ++counter;
    return a + b;
}

int MyLibrary::Calculator::sub(int a, int b)
{
    ++counter;
    return a - b;
}

int MyLibrary::Calculator::cntOpsDone()
{
    return counter;
}

int MyLibrary::Calculator::resetCounter()
{
    int last_counter = counter;
    counter = 0;
    return last_counter;
}
