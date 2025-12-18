#include "ringbuffer.h"

#include <algorithm>
#include <cstring>

namespace Firmware
{
    template <unsigned Length, typename Tdata>
    RingBuffer<Length, Tdata>::RingBuffer(unsigned initialPosition)
        : _data((Tdata *)std::malloc(Length * sizeof(Tdata))),
          _position(initialPosition)
    {
    }

    template <unsigned Length, typename Tdata>
    int RingBuffer<Length, Tdata>::write(Tdata value)
    {
        *(this->_data + this->_position) = value;

        return this->seekRelative(1);
    }

    template <unsigned Length, typename Tdata>
    int RingBuffer<Length, Tdata>::copyFrom(Tdata *source, unsigned length, unsigned sourceOffset)
    {
        unsigned copyToEndCount = std::min(length, Length - this->_position);
        std::memcpy(this->_data + this->_position, source + sourceOffset, copyToEndCount * sizeof(Tdata));

        unsigned copyFromStartCount = std::min(length - copyToEndCount, this->_position);
        std::memcpy(this->_data, source + sourceOffset + copyToEndCount, copyFromStartCount * sizeof(Tdata));

        return copyToEndCount + copyFromStartCount;
    }

    template <unsigned Length, typename Tdata>
    int RingBuffer<Length, Tdata>::copyTo(Tdata *dest, unsigned length, unsigned destOffset)
    {
        int copyToEndCount = std::min(length, Length - this->_position);
        std::memcpy(dest + destOffset, this->_data + this->_position, copyToEndCount * sizeof(Tdata));

        int copyFromStartCount = std::min(length - copyToEndCount, this->_position);
        std::memcpy(dest + destOffset + copyToEndCount, this->_data, copyFromStartCount * sizeof(Tdata));

        return copyToEndCount + copyFromStartCount;
    }

    template <unsigned Length, typename Tdata>
    void RingBuffer<Length, Tdata>::seekAbsolute(unsigned position)
    {
        this->_position = position;
    }

    template <unsigned Length, typename Tdata>
    unsigned RingBuffer<Length, Tdata>::seekRelative(int offset)
    {
        this->_position = (this->_position + offset) % Length;
        return this->_position;
    }

    template <unsigned Length, typename Tdata>
    unsigned RingBuffer<Length, Tdata>::get_position()
    {
        return this->_position;
    }

    template <unsigned Length, typename Tdata>
    RingBuffer<Length, Tdata>::~RingBuffer()
    {
        std::free(this->_data);
    }
}
