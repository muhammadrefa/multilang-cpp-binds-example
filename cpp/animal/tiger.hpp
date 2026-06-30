#pragma once

#include <string>
#include "cat.hpp"

namespace MyLibrary
{
    class Tiger : public Cat {
        public:
            using Cat::Cat;
            using Cat::speak;

            void speak() override;
            void sleep() override;

            void hunt();
            int getHunger() const;

        private:
            int hunger = 50;
    };
}
