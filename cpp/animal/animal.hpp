#pragma once

#include <string>

namespace MyLibrary
{
    class Animal
    {
        public:
            std::string name;

            Animal();
            Animal(std::string name);
            virtual ~Animal();
            
            virtual void speak();
            void speak(int times);
            virtual void sleep();
        
        protected:
            void speak(std::string sentence);
    };
}
