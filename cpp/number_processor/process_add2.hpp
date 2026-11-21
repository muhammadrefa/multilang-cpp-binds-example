#pragma once

#include <string>
#include "number_processor.hpp"

namespace MyLibrary
{
    class ProcessAdd2 : public NumberProcessor {
        public:
            ProcessAdd2();
            ~ProcessAdd2();

            void process();
    };
}
