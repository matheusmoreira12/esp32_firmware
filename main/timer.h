#pragma once

#include "esp_timer.h"
#include <functional>

namespace Firmware::Interrupts
{
    class Timer final
    {
    private:
        bool _isEnabled;
        bool _isRunning;
        esp_timer_handle_t _espTimer_handle;
        std::function<void()> _callback;
        int _timeoutUs;
        bool _isPeriodic;

        void _setup();
        void _start();
        void _stop();

    protected:
        static void espTimer_callback(void *arg);

    public:
        static long fromHz(unsigned hz);
        static long fromKHz(unsigned khz);
        static long fromMinutes(unsigned mins);
        static long fromSeconds(unsigned secs);
        static long fromMilliseconds(unsigned ms);

        Timer(std::function<void()> callback, unsigned long timeoutUs, bool isPeriodic = false);

        bool get_isEnabled();
        void set_isEnabled(bool value);
        void set_timeoutUs(unsigned long value);

        ~Timer();
    };
}