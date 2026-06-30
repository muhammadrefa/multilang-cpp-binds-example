#pragma once

#include <string>
#include "cat.hpp"

namespace MyLibrary
{
    class Tiger : public Cat {
        public:
            using Cat::Cat;
            using Cat::speak;

            void speak();
            void hunt();
            void sleep();
            int getHunger();

        private:
            int hunger = 50;
    };
}
