#pragma once

#include <string>
#include "animal.hpp"

namespace MyLibrary
{
    class Cat : public Animal {
        public:
            using Animal::Animal;
            using Animal::speak;

            void speak() override;

            bool fight(bool bigger_cat);
            bool stillAlive() const;

        protected:
            int lives = 9;
    };
}
