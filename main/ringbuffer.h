#pragma once

#include <type_traits>

namespace Firmware
{
    template <unsigned Length, typename Tdata>
    class RingBuffer final
    {
        static_assert(std::is_arithmetic<Tdata>::value, "Tdata must be a arithmetic type");

    private:
        Tdata *_data;
        unsigned _position;

    public:
        RingBuffer(unsigned initialPosition = 0);
        int write(Tdata value);
        int copyFrom(Tdata *source, unsigned length, unsigned sourceOffset = 0);
        int copyTo(Tdata *dest, unsigned length, unsigned destOffset = 0);
        void seekAbsolute(unsigned position);
        unsigned seekRelative(int offset);
        unsigned get_position();
        ~RingBuffer();
    };
}

#include "ringbuffer.inl"