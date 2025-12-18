#pragma once

#include "application.h"
#include "timer.h"
#include "ringbuffer.h"

constexpr int SAMPLE_RATE_HZ = 44100u;
constexpr int BUFFER_SIZE = SAMPLE_RATE_HZ * 1; // 1 second buffer

class MainApplication : public Firmware::Application
{
private:
    Firmware::Interrupts::Timer samplingTimer;
    Firmware::RingBuffer<BUFFER_SIZE, uint16_t> ringBuffer;
    void samplingTimer_callback();

public:
    MainApplication();
    void setup() override;
};