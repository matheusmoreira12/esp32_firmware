#include "event.h"

namespace Firmware
{
    template <typename Targs>
    void Event<Targs>::invoke(Targs args)
    {
        for (EventHandler<Targs>& handler : this->handlers)
            handler(args);
    }

    template <typename Targs>
    Event<Targs> Event<Targs>::operator+=(EventHandler<Targs> handler)
    {
        this.attach(handler);
    }

    template <typename Targs>
    void Event<Targs>::attach(EventHandler<Targs> handler)
    {
        this->handlers.push_back(handler);
    }

    template <typename Targs>
    Event<Targs>::~Event()
    {
        this->handlers.clear();
        this->handlers.shrink_to_fit();
    }
}