#pragma once

#include "esp_timer.h"
#include <functional>

namespace Firmware::Interrupts
{
    class ITimer
    {
    public:
        virtual bool get_isEnabled() = 0;
        virtual void set_isEnabled(bool value) = 0;
        virtual void set_timeoutUs(unsigned long value) = 0;
    };

    class Timer final : public ITimer
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
        static long fromHz(unsigned int hz);
        static long fromKHz(unsigned int khz);
        static long fromMinutes(unsigned int mins);
        static long fromSeconds(unsigned int secs);
        static long fromMilliseconds(unsigned int ms);

        Timer(std::function<void()> callback, unsigned long timeoutUs, bool isPeriodic);

        bool get_isEnabled() override;
        void set_isEnabled(bool value) override;
        void set_timeoutUs(unsigned long value);

        ~Timer();
    };
}