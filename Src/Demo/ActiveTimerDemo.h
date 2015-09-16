#ifndef _ActiveTimerDemo_h_
#define _ActiveTimerDemo_h_

#include "SystemInclude.h"
#include "SystemError.h"

#include "TimerQueue/TimerQueueAdapter.h"
#include "Demo/EventHandlerStub.h"

using namespace std;

inline int ActiveTimerMain(int argc, char *argv[])
{
    // Create an "active" timer and start its thread.
    ActiveTimer atimer;
    atimer.Activate();

    shared_ptr<EventHandlerStub> handler = make_shared<EventHandlerStub>();
    uint_t timerId;
    atimer.Schedule(handler, nullptr, chrono::system_clock::now() + Duration(1000), Duration(500), &timerId);

    SleepEx(3000, true);
    atimer.Deactivate();

    SleepEx(INFINITE, true);
    
    return 0;
}

#endif