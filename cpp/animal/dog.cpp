#include <iostream>
#include "dog.hpp"

void MyLibrary::Dog::speak()
{
    Animal::speak("\"woof woof!\"");
}

void MyLibrary::Dog::sleep()
{
    energy += 20;
    if (energy >= 200)
    {
        energy = 200;
        Animal::speak("\"WOOF!\" (i'm full of energy!)");
    }
}

bool MyLibrary::Dog::fetch()
{
    if (!haveEnergy())
    {
        Animal::speak("\"woof...\" (i'm tired...)");
        return false;
    }
        
    decreaseEnergy();
    return true;
}

int MyLibrary::Dog::getEnergy()
{
    return energy;
}

bool MyLibrary::Dog::haveEnergy()
{
    return (energy > 10);
}

void MyLibrary::Dog::decreaseEnergy()
{
    energy -= 10;
    if (energy < 0)
        energy = 0;
}
