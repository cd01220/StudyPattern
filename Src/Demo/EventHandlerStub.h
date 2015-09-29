#ifndef _EventHandlerStub_h_
#define _EventHandlerStub_h_

#include "SystemInclude.h"
#include "Event/EventHandler.h"

/**********************class EventHandlerStub**********************/
class EventHandlerStub: public EventHandler
{
public:
    EventHandlerStub(Reactor *reactor = nullptr);
    
    std::error_code HandleClose();
    std::error_code HandleInput();
    std::error_code HandleOutput();
    std::error_code HandleTimeOut(TimePoint, const void *arg = 0);

    std::error_code Open();
};

/**********************class ClientService**********************/
class ClientService: public EventHandler
{
public:
    ClientService(Reactor *reactor = nullptr);
    ~ClientService();
    
    std::error_code HandleInput();
    std::error_code HandleTimeOut(TimePoint, const void *arg = 0);

    std::error_code Open();
};

#endif