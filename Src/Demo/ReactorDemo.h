#ifndef _ReactorDemo_h_
#define _ReactorDemo_h_

#include "Demo/EventHandlerStub.h"
#include "Reactor/Reactor.h"

inline void ReactorMain1(int argc, char *argv[])
{
    Reactor *reactor = new Reactor;

    std::shared_ptr<EventHandlerStub> handler = std::make_shared<EventHandlerStub>(reactor);
    handler->Open();
    reactor->RunEventLoop();
}

#endif