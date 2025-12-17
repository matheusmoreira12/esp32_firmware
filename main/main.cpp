#include "main.h"

#include "application.h"

#include <iostream>
#include <functional>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

using Timer = Firmware::Interrupts::Timer;

MainApplication::MainApplication()
    : samplingTimer(new Timer(std::bind(&MainApplication::samplingTimer_callback, this), Timer::fromHz(44100), true))
{
}

void MainApplication::samplingTimer_callback()
{
}

void MainApplication::setup()
{
    this->samplingTimer->set_isEnabled(true);
}

extern "C" void app_main(void)
{
    MainApplication app;

    app.setup();
    app.main();
    app.finalize();
}