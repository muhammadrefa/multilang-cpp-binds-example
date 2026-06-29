#pragma once

#include <cstdint>

namespace MyLibrary
{
    class Calculator
    {
        public:
            Calculator();
            ~Calculator();

            int add(int a, int b);
            int sub(int a, int b);
            
            int cntOpsDone();
            int resetCounter();

        protected:
            int counter = 0;

        private:

    };
}
