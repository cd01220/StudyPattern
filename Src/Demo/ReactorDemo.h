#ifndef _ReactorDemo_h_
#define _ReactorDemo_h_

#include "Reactor/Reactor.h"
#include "Demo/EventHandlerStub.h"
#include "Demo/Client.h"

inline void ReactorMain1(int argc, char *argv[])
{
    Reactor *reactor = new Reactor;

    std::shared_ptr<EventHandlerStub> handler = std::make_shared<EventHandlerStub>(reactor);
    handler->Open();
    reactor->RunEventLoop();
}

inline void ReactorMain2(int argc, char *argv[])
{
    Reactor *reactor = new Reactor;
    std::shared_ptr<Client> client = std::make_shared<Client>(reactor);

    client->Open(nullptr);
    client->Activate();

    reactor->RunEventLoop();
}

#endif