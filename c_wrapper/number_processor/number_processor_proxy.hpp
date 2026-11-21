#pragma once

#include <string>
#include "number_processor_proxy.h"
#include "number_processor.hpp"

namespace MyLibrary
{
    class NumberProcessorProxy : public NumberProcessor {
        public:
            NumberProcessorProxy();
            ~NumberProcessorProxy();

            void SetCallback(mylib_NumberProcessorProxy_cb_t* callback);

            void process() override;
            void PrintNumber() override;
        
        private:
            mylib_NumberProcessorProxy_cb_t cb;
            mylib_NumberProcessorProxy_t* GetSelfHandle();
    };
}
