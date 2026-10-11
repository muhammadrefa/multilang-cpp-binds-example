#pragma once

#include <string>
#include "number_processor_proxy.h"
#include "number_processor.hpp"

namespace MyLibrary
{
    class NumberProcessorProxy : public NumberProcessor {
        public:
            NumberProcessorProxy();
            NumberProcessorProxy(mylib_NumberProcessor_t* base_handle);
            ~NumberProcessorProxy();

            void SetCallback(mylib_NumberProcessorProxy_cb_t* callback);
            mylib_NumberProcessor_t* GetBaseHandle();

            void process();
            void PrintNumber() override;
        
        private:
            mylib_NumberProcessorProxy_cb_t cb;
            mylib_NumberProcessor_t* base_handle;
            mylib_NumberProcessorProxy_t* GetSelfHandle();
    };
}
