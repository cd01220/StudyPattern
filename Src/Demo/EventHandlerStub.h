#ifndef _EventHandlerStub_h_
#define _EventHandlerStub_h_

#include "SystemInclude.h"
#include "Event/EventHandler.h"

class EventHandlerStub: public EventHandler
{
public:
    EventHandlerStub();
    
    std::error_code HandleInput();
    std::error_code HandleTimeOut(TimePoint, const void *arg = 0);

private:
    uint_t timerId;
};

#endif