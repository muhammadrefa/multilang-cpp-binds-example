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

            void SetCallback(mylib_NumberProcessorProxy_t* handle, mylib_NumberProcessorProxy_cb_t* callback);

            void process();
            void PrintNumber() override;
        
        private:
            mylib_NumberProcessorProxy_t* handle;
            mylib_NumberProcessorProxy_cb_t cb;
    };
}
