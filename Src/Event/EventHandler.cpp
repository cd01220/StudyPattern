#include "SystemInclude.h"

#include "Reactor/Reactor.h"
#include "Event/EventHandler.h"

using namespace std;

/**********************class EventHandler**********************/
EventHandler::~EventHandler()
{
}

bool EventHandler::HandleClose()
{
    return true;
}

bool EventHandler::HandleException()
{
    return true;
}

bool EventHandler::HandleGroupQos()
{
    return true;
}

bool EventHandler::HandleInput()
{
    return true;
}

bool EventHandler::HandleOutput()
{
    return true;
}

bool EventHandler::HandleQos()
{
    return true;
}

bool EventHandler::HandleSignal()
{
    return true;
}

bool EventHandler::HandleTimeOut(TimePoint, const void *arg)
{
    return true;
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
    static uint_t index = 0;
    wostringstream os;
    os << TEXT("EventHandler") << index++;
    eventHandle = CreateEvent(NULL, TRUE, FALSE, os.str().c_str());
    ioHandle = InvalidHandleValue;
}
