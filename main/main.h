#pragma once

#include "application.h"
#include "timer.h"

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