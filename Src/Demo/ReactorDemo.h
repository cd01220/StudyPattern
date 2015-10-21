#ifndef _ReactorDemo_h_
#define _ReactorDemo_h_

#include "MessageQueue/MessageQueue.h"
#include "Reactor/Reactor.h"
#include "Demo/EventHandlerStub.h"
#include "Demo/Client.h"

Reactor reactor;

inline void ReactorMain1(int argc, char *argv[])
{
    std::shared_ptr<EventHandlerStub> handler = std::make_shared<EventHandlerStub>(&reactor);
    handler->Open();
    reactor.RunEventLoop();
}

inline void ReactorMain2(int argc, char *argv[])
{
    std::shared_ptr<Client> client = std::make_shared<Client>(&reactor);

    if (!client->Open(nullptr))
    {
        return;
    }

    reactor.RunEventLoop();
}

#endif