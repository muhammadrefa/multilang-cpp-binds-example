#include <iostream>
#include "cat.hpp"

void MyLibrary::Cat::speak()
{
    Animal::speak("\"meow\"");
}

bool MyLibrary::Cat::fight(bool bigger_cat)
{
    if (!stillAlive())
    {
        std::cout << name << " already died..." << std::endl;
        return false;
    }

    if (bigger_cat)
    {
        std::cout << name << " loses fight!" << std::endl;
        --lives;
        return false;
    }
    else
    {
        std::cout << name << " wins fight!" << std::endl;
        return true;
    }
}

bool MyLibrary::Cat::stillAlive()
{
    return (lives > 0);
}
