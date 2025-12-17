#pragma once

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