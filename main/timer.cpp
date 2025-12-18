#include "timer.h"

#include "esp_timer.h"

namespace Firmware::Interrupts
{
    long Timer::fromHz(unsigned hz)
    {
        return 1'000'000u / hz;
    }

    long Timer::fromKHz(unsigned khz)
    {
        return 1'000u / khz;
    }

    long Timer::fromMinutes(unsigned mins)
    {
        return mins * 60'000'000u;
    }

    long Timer::fromSeconds(unsigned secs)
    {
        return secs * 1'000'000u;
    }

    long Timer::fromMilliseconds(unsigned millis)
    {
        return millis * 1'000u;
    }

    Timer::Timer(std::function<void()> callback, unsigned long timeoutUs, bool isPeriodic)
        : _isEnabled(false),
          _isRunning(false),
          _callback(callback),
          _timeoutUs(timeoutUs),
          _isPeriodic(isPeriodic)
    {
        this->_setup();
    }

    void Timer::_setup()
    {
        esp_timer_create_args_t args = {
            .callback = Timer::espTimer_callback,
            .arg = this,
        };

        esp_timer_create(&args, &this->_espTimer_handle);
    }

    void Timer::_start()
    {
        if (this->_isRunning)
            return;

        if (this->_isPeriodic)
            ESP_ERROR_CHECK(esp_timer_start_periodic(this->_espTimer_handle, this->_timeoutUs));
        else
            ESP_ERROR_CHECK(esp_timer_start_once(this->_espTimer_handle, this->_timeoutUs));

        this->_isRunning = true;
    }

    void Timer::_stop()
    {
        if (!this->_isRunning)
            return;

        esp_timer_stop(this->_espTimer_handle);

        this->_isRunning = false;
    }

    void Timer::espTimer_callback(void *arg)
    {
        Timer *self = (Timer *)arg;

        self->_callback();

        if (!self->_isPeriodic)
        {
            self->_isEnabled = false;
            self->_isRunning = false;
        }
    }

    bool Timer::get_isEnabled()
    {
        return this->_isEnabled;
    }

    void Timer::set_isEnabled(bool value)
    {
        if (this->_isEnabled == value)
            return;

        if (value)
            _start();
        else
            _stop();

        this->_isEnabled = value;
    }

    void Timer::set_timeoutUs(unsigned long value)
    {
        this->_stop();

        this->_timeoutUs = value;

        if (this->_isEnabled)
            this->_start();
    }

    Timer::~Timer()
    {
        esp_timer_stop(this->_espTimer_handle);
        esp_timer_delete(this->_espTimer_handle);
    }
}