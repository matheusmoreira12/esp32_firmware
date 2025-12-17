#pragma once

#include "freertos/task.h"

namespace Firmware
{
    class Application
    {
    public:
        virtual void setup();
        virtual void main();
        virtual void finalize();
    };
}