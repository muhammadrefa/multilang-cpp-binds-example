#pragma once

#include <string>
#include "animal.hpp"

namespace MyLibrary
{
    class Dog : public Animal {
        public:
            using Animal::Animal;
            using Animal::speak;

            void speak();
            void sleep();

            bool fetch();
            int getEnergy();

        private:        
            int energy = 50;
            bool haveEnergy();
            void decreaseEnergy();
    };
}
