#include "SystemInclude.h"

#include "Reactor/Reactor.h"
#include "EventHandler.h"

using namespace std;

/**********************class EventHandler**********************/
EventHandler::~EventHandler()
{
}

error_code EventHandler::HandleTimeOut(TimePoint, const void *arg)
{
    return error_code();
}

Reactor* EventHandler::GetReactor()
{
    return reactor;
}

Handle EventHandler::GetHandle()
{
    return InvalidHandleValue;
}

void EventHandler::SetReactor(Reactor *reactor)
{
    this->reactor = reactor;
}

/**********************class EventHandler**********************/
/* protected member function */
EventHandler::EventHandler(Reactor *reactor, uint_t priority)
    : reactor(reactor), priority(priority)
{
}