#ifndef _EventHandlerStub_h_
#define _EventHandlerStub_h_

#include "SystemInclude.h"
#include "Event/EventHandler.h"

/**********************class EventHandlerStub**********************/
class EventHandlerStub: public EventHandler
{
    typedef std::function<void(SOCKET sock)> AcceptHandler;

public:
    EventHandlerStub(AcceptHandler acceptHandler);
    
    bool HandleClose();
    bool HandleInput();
    bool HandleOutput();
    bool HandleTimeOut(TimePoint, const void *arg = 0);

    bool Open();

private:
    AcceptHandler acceptHandler;
};

/**********************class ClientService**********************/
class ClientService: public EventHandler
{
public:
    ClientService();
    ~ClientService();
    
    bool HandleInput();
    bool HandleTimeOut(TimePoint, const void *arg = 0);

    bool Open();
};

#endif