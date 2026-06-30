#pragma once

#include <string>
#include "animal.hpp"

namespace MyLibrary
{
    class Cat : public Animal {
        public:
            using Animal::Animal;
            using Animal::speak;

            void speak();
            bool fight(bool bigger_cat);
            bool stillAlive();

        protected:
            int lives = 9;
    };
}
