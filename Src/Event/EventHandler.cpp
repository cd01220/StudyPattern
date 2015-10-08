#include "SystemInclude.h"

#include "Reactor/Reactor.h"
#include "Event/EventHandler.h"

using namespace std;

/**********************class EventHandler**********************/
EventHandler::~EventHandler()
{
}

error_code EventHandler::HandleClose()
{
    return error_code();
}

error_code EventHandler::HandleException()
{
    return error_code();
}

error_code EventHandler::HandleGroupQos()
{
    return error_code();
}

error_code EventHandler::HandleInput()
{
    return error_code();
}

error_code EventHandler::HandleOutput()
{
    return error_code();
}

error_code EventHandler::HandleQos()
{
    return error_code();
}

error_code EventHandler::HandleTimeOut(TimePoint, const void *arg)
{
    return error_code();
}

Handle EventHandler::GetEventHandle() const
{
    return eventHandle;
}

Handle EventHandler::GetIoHandle() const
{
    return ioHandle;
}

long EventHandler::GetMask() const
{
    return mask;
}

Reactor* EventHandler::GetReactor()
{
    return reactor;
}

void EventHandler::SetIoHandle(Handle handle)
{
    ioHandle = handle;
}

void EventHandler::SetMask(long mask)
{
    this->mask = mask;
}

void EventHandler::SetReactor(Reactor *reactor)
{
    if (this->reactor != reactor)
        this->reactor = reactor;
}

/**********************class EventHandler**********************/
/* protected member function */
EventHandler::EventHandler(Reactor *reactor, uint_t priority)
    : reactor(reactor), priority(priority)
{
}
