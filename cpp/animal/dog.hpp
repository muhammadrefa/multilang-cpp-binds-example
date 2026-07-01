#pragma once

#include <string>
#include "animal.hpp"

namespace MyLibrary
{
    class Dog : public Animal {
        public:
            using Animal::Animal;
            using Animal::speak;

            void speak() override;
            void sleep() override;

            bool fetch();
            int getEnergy() const;

        private:        
            int energy = 50;
            bool haveEnergy();
            void decreaseEnergy();
    };
}
