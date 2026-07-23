#pragma once

#include <string>

namespace MyLibrary
{
    class NumberProcessor
    {
        public:
            NumberProcessor() = default;
            virtual ~NumberProcessor() = 0;
            
            virtual void process() = 0;
            void SetNumber(int number);
            int GetNumber();
            virtual void PrintNumber();
        
        protected:
            int number;
    };
}
