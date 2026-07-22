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

            void process();
            void SetCallback(mylib_number_processor_proxy_t* handle, mylib_number_processor_proxy_cb_t* callback);
        
        private:
            mylib_number_processor_proxy_t* handle;
            mylib_number_processor_proxy_cb_t cb;
    };
}
