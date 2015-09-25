#include "SystemInclude.h"

#include "Reactor/Reactor.h"
#include "EventHandler.h"

using namespace std;

/**********************class EventHandler**********************/
EventHandler::~EventHandler()
{
}

std::error_code EventHandler::HandleException()
{
    return error_code();
}

std::error_code EventHandler::HandleGroupQos()
{
    return error_code();
}

std::error_code EventHandler::HandleInput()
{
    return error_code();
}

std::error_code EventHandler::HandleOutput()
{
    return error_code();
}

std::error_code EventHandler::HandleQos()
{
    return error_code();
}

error_code EventHandler::HandleTimeOut(TimePoint, const void *arg)
{
    return error_code();
}

Handle EventHandler::GetEventHandle() const
{
    return InvalidHandleValue;
}

Reactor* EventHandler::GetReactor()
{
    return reactor;
}

Handle EventHandler::GetIoHandle() const
{
    return InvalidHandleValue;
}

long EventHandler::GetMask() const
{
    return mask;
}

void EventHandler::SetReactor(Reactor *reactor)
{
    this->reactor = reactor;
}

void EventHandler::SetMask(long mask)
{
    this->mask = mask;
}

/**********************class EventHandler**********************/
/* protected member function */
EventHandler::EventHandler(Reactor *reactor, uint_t priority)
    : reactor(reactor), priority(priority)
{
}