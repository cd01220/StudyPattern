#ifndef _EventHandlerStub_h_
#define _EventHandlerStub_h_

#include "SystemInclude.h"
#include "Event/EventHandler.h"

/**********************class EventHandlerStub**********************/
class EventHandlerStub: public EventHandler
{
public:
    EventHandlerStub(Reactor *reactor = nullptr);
    
    bool HandleClose();
    bool HandleInput();
    bool HandleOutput();
    bool HandleTimeOut(TimePoint, const void *arg = 0);

    bool Open();
};

/**********************class ClientService**********************/
class ClientService: public EventHandler
{
public:
    ClientService(Reactor *reactor = nullptr);
    ~ClientService();
    
    bool HandleInput();
    bool HandleTimeOut(TimePoint, const void *arg = 0);

    bool Open();
};

#endif