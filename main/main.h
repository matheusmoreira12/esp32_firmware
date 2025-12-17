#pragma once

#include "application.h"
#include "timer.h"

class MainApplication : public Firmware::Application
{
private:
    Firmware::Interrupts::ITimer* samplingTimer;
    void samplingTimer_callback();

public:
    MainApplication();
    void setup() override;
};