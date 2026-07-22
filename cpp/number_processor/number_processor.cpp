#include <iostream>
#include "number_processor.hpp"

MyLibrary::NumberProcessor::~NumberProcessor()
{

}

void MyLibrary::NumberProcessor::SetNumber(int number)
{
    this->number = number;
}

int MyLibrary::NumberProcessor::GetNumber()
{
    return number;
}

void MyLibrary::NumberProcessor::PrintNumber()
{
    std::cout << "Number: " << std::to_string(number) << std::endl;
}
