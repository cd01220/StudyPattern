// $Id: EventHandlerStub.cpp 94310 2011-07-09 19:10:06Z schmidt $
#include "SystemInclude.h"
#include "SystemError.h"

#include "Demo/TimerDispatcherStub.h"
#include "EventHandlerStub.h"

using namespace std;

EventHandlerStub::EventHandlerStub () : count(0)
{
    cout << "EventHandlerStub::EventHandlerStub" << endl;
}

error_code EventHandlerStub::HandleTimeOut(TimePoint, const void *arg)
{
    cout << "EventHandlerStub::handle_timeout" << endl;
    count++;
    return error_code();
}

uint_t EventHandlerStub::GetTimerId()
{
    return timerId;
}

void EventHandlerStub::SetTimerId(uint_t timerId)
{
    this->timerId = timerId;
}

