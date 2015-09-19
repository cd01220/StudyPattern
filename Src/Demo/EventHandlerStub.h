#ifndef _EventHandlerStub_h_
#define _EventHandlerStub_h_

#include "SystemInclude.h"
#include "Event/EventHandler.h"

class EventHandlerStub: public EventHandler
{
public:
    EventHandlerStub()
    {
        std::cout << "EventHandlerStub::EventHandlerStub" << std::endl;
    }

    // Handle the timeout.
    std::error_code HandleTimeOut(TimePoint, const void *arg = 0)
    {
        std::cout << "EventHandlerStub::handle_timeout" << std::endl;
        return std::error_code();
    }

private:
    uint_t timerId;
};

#endif