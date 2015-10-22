#include "SystemInclude.h"

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

void EventHandler::SetIoHandle(Handle handle)
{
    ioHandle = handle;
}

void EventHandler::SetMask(long mask)
{
    this->mask = mask;
}

/**********************class EventHandler**********************/
/* protected member function */
EventHandler::EventHandler()
{
    this->eventHandle = CreateEvent(NULL, TRUE, FALSE, nullptr);
    this->ioHandle = InvalidHandleValue;
    this->mask = NullMask;
    this->priority = LowPriority;
}
