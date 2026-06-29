#pragma once

#include <cstdint>
#include <cstddef>

namespace MyLibrary
{
    class CircularBuffer
    {
        public:
            CircularBuffer(int bufsize);
            ~CircularBuffer();

            int getLength();
            int put(char* data, int length);
            int get(char* dest, int length);
            int clean();

        protected:
            int _size = 0;
            int _head = 0;
            int _tail = 0;
            char* _ptr_buffer = NULL;

            int getRemaining();

        private:

    };
}
