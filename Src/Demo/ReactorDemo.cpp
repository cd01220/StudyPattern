#include "SystemInclude.h"
#include "Debug.h"

#include "Reactor/Reactor.h"
#include "Demo/EventHandlerStub.h"  //EventHandlerStub
#include "Demo/Client.h"            //Client
#include "Demo/ReactorDemo.h"
using namespace std;

Reactor reactor;

void ReactorMain1(int argc, char *argv[])
{
    std::shared_ptr<EventHandlerStub> handler = std::make_shared<EventHandlerStub>(&reactor);
    handler->Open();
    reactor.RunEventLoop();
}

void ReactorMain2(int argc, char *argv[])
{
    std::shared_ptr<Client> client = std::make_shared<Client>(&reactor);

    if (!client->Open(nullptr))
    {
        return;
    }

    reactor.RunEventLoop();
}