#include "SystemInclude.h"
#include "Debug.h"

#include "Reactor/Reactor.h"
#include "MessageQueue/MessageQueue.h"
#include "MessageQueue/NotificationStrategy.h"
#include "Demo/EventHandlerStub.h"  //EventHandlerStub
#include "Demo/Client.h"            //Client
#include "Demo/ReactorDemo.h"
using namespace std;

Reactor reactor;

void HandleAccept(SOCKET sock)
{   
    std::shared_ptr<ClientService> client = std::make_shared<ClientService>();
    client->SetIoHandle((Handle)sock);    
    client->SetMask(EventHandler::ReadMask);
    if (!client->Open())
    {
        client->HandleClose();
        return;
    }

    reactor.RegisterHandler(client);
}

void ReactorMain1(int argc, char *argv[])
{
    std::shared_ptr<EventHandlerStub> handler = std::make_shared<EventHandlerStub>(HandleAccept);
    handler->Open();

    if (!reactor.RegisterHandler(handler))
    {
        errstrm << "reactor.RegisterHandler() failed" << endl;
        return;
    }
    reactor.RunEventLoop();
}

void ReactorMain2(int argc, char *argv[])
{
    std::shared_ptr<Client> client = std::make_shared<Client>();

    if (!client->Open(nullptr))
    {
        errstrm << "client->Open() failed" << endl;
        return;
    }

    /* Note:
       Set messge queue notification stratege, mask "EventHandler::WriteMask" means 
       a msgQueue->Push() call will cause this->HandleOutput() to be called.
    */
    auto notifer = make_shared<ReactorNotificationStrategy>(&reactor, 
        client, EventHandler::WriteMask);
    MessageQueue& msgQueue = client->GetMessageQueue();
    msgQueue.SetNotificationStrategy(notifer);

    if (!reactor.RegisterHandler(client))
    {
        errstrm << "reactor.RegisterHandler() failed" << endl;
        return;
    }

    if (!reactor.ScheduleTimer(client, nullptr, GetCurTime() + Duration(1000), Duration(2000)))
    {
        errstrm << "reactor.ScheduleTimer() failed" << endl;
        return;
    }

    reactor.RunEventLoop();
}