#ifndef _ActiveTimerDemo_h_
#define _ActiveTimerDemo_h_

#include "SystemInclude.h"
#include "SystemError.h"

#include "Demo/EventHandlerStub.h"
#include "TimerQueue/TimerQueueAdapter.h"

inline void ActiveTimerMain(int argc, char *argv[])
{
    // Create an "active" timer and start its thread.
    ActiveTimer activeTimer;
    activeTimer.Activate();

    std::shared_ptr<EventHandlerStub> handler = std::make_shared<EventHandlerStub>();
    uint_t timerId;
    activeTimer.Schedule(handler, nullptr, GetCurTime() + Duration(1000), Duration(500), &timerId);

    activeTimer.Wait();
}

#endif