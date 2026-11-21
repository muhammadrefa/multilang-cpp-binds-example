#include <iostream>
#include "process_add2.hpp"

MyLibrary::ProcessAdd2::ProcessAdd2()
{

}

MyLibrary::ProcessAdd2::~ProcessAdd2()
{

}

void MyLibrary::ProcessAdd2::process()
{
    this->number += 2;
}
