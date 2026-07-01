#include <iostream>
#include "tiger.hpp"

void MyLibrary::Tiger::speak()
{
    Animal::speak("\"MEOW\"");
}

void MyLibrary::Tiger::hunt()
{
    if (hunger < 10)
        std::cout << name << " is full" << std::endl;
    else
        hunger -= 10;
}

void MyLibrary::Tiger::sleep()
{
    hunger += 10;
}

int MyLibrary::Tiger::getHunger() const
{
    return hunger;
}
