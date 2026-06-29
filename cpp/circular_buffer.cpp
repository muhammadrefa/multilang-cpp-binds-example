#include <cstdint>
#include <cstdlib>
#include <cstring>

#include <stdexcept>

#include "circular_buffer.hpp"


MyLibrary::CircularBuffer::CircularBuffer(int bufsize)
{
    _ptr_buffer = new char[bufsize+1];
    _size = bufsize;
}

MyLibrary::CircularBuffer::~CircularBuffer()
{
    delete[] _ptr_buffer;
}

int MyLibrary::CircularBuffer::getLength()
{
    return (_tail >= _head) ? (_tail - _head) : ((_size + 1) - _head + _tail);
}

int MyLibrary::CircularBuffer::put(char* data, int length)
{
    if (_ptr_buffer == NULL)
        throw std::logic_error("circular buffer not initialised!");

    if (getRemaining() < length)
        throw std::overflow_error("need more free space!");
    
    int tail_to_end = (_size + 1) - _tail;
    int towards_end = tail_to_end >= length ? length : tail_to_end;

    memcpy(_ptr_buffer+_tail, data, towards_end);        // store length or to the end
    memcpy(_ptr_buffer, data+towards_end, length-towards_end);  // store the rest (if any)
    
    _tail = (length > tail_to_end) ? (length - tail_to_end) : (_tail + length);

    return length;
}

int MyLibrary::CircularBuffer::get(char* dest, int length)
{
    if (_ptr_buffer == NULL)
        throw std::logic_error("circular buffer not initialised!");

    int available = getLength();
    int length_to_get = available < length ? available : length;

    if (length_to_get == 0)
        throw std::range_error("buffer empty!");

    uint16_t head_to_end = (_size + 1) - _head;
    uint16_t towards_end = head_to_end >= length_to_get ? length_to_get : head_to_end;
    memcpy(dest, _ptr_buffer+_head, towards_end);             // get length or to the end
    memcpy(dest+towards_end, _ptr_buffer, length_to_get - towards_end);     // get the rest (if any)

    _head = (_head + length_to_get > head_to_end) ? (length_to_get - towards_end) : (_head + length_to_get);

    return length_to_get;
}

int MyLibrary::CircularBuffer::clean()
{
    int last_length = getLength();
    _head = _tail;
    return last_length;
}

int MyLibrary::CircularBuffer::getRemaining()
{
    int remaining = ((_size - 1) - getLength());
    return remaining < 0 ? 0 : remaining;
}
