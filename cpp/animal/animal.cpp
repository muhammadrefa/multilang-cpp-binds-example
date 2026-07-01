#include <iostream>
#include "animal.hpp"

MyLibrary::Animal::Animal()
{
    
}

MyLibrary::Animal::Animal(std::string name)
{
    this->name = name;
}

MyLibrary::Animal::~Animal()
{
    std::cout << name << " really thankful for all the time spent together" << std::endl;
}

void MyLibrary::Animal::speak()
{
    speak("... (inaudible)");
}

void MyLibrary::Animal::speak(int times)
{
    for (int i=0; i<times; ++i)
        speak();
}

void MyLibrary::Animal::speak(std::string sentence)
{
    std::cout << name << ": " << sentence << std::endl;
}

void MyLibrary::Animal::sleep()
{
    
}