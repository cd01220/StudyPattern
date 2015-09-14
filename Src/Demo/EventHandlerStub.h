/* -*- C++ -*- */
// $Id: EventHandlerStub.h 81978 2008-06-16 16:57:12Z sowayaa $

#ifndef _EventHandlerStub_h_
#define _EventHandlerStub_h_

#include "SystemInclude.h"
#include "Event/EventHandler.h"

// Listing 1 code/ch20
class EventHandlerStub: public EventHandler
{
public:
    EventHandlerStub ();

    // Handle the timeout.
    std::error_code HandleTimeOut(TimePoint, const void *arg = 0);
    uint_t GetTimerId();
    void SetTimerId(uint_t timerId);

private:
    int count;
    uint_t timerId;
};

#endif /*CB_H*/
