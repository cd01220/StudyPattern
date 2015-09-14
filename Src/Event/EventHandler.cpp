#include "SystemInclude.h"

#include "Reactor/Reactor.h"
#include "EventHandler.h"

using namespace std;

/**********************class EventHandler**********************/
EventHandler::~EventHandler()
{
}

std::error_code EventHandler::HandleTimeOut(TimePoint, const void *arg)
{
    return error_code();
}

/**********************class EventHandler**********************/
/* protected member function */
EventHandler::EventHandler(std::shared_ptr<Reactor> reactor, uint_t priority)
    : reactor(reactor), priority(priority)
{
}