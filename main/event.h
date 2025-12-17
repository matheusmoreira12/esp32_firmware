#pragma once

#include <vector>

namespace Firmware
{
    class EventArgs
    {
    };

    template <typename Targs>
    using EventHandler = void (*)(Targs eventArgs);

    template <typename Targs>
    class IEvent
    {
    public:
        virtual void invoke(Targs) = 0;
        virtual void attach(EventHandler<Targs>) = 0;
    };

    template <typename Targs>
    class Event final : public IEvent<Targs>
    {
        static_assert(std::is_base_of<EventArgs, Targs>::value, "TArgs must inherit IEventArgs");

    private:
        std::vector<EventHandler<Targs>> handlers;
        bool isDisposed = false;

    public:
        void invoke(Targs args);
        void attach(EventHandler<Targs> handler);
        Event operator+=(EventHandler<Targs> handler);
        ~Event();
    };
}

#include "event.inl"