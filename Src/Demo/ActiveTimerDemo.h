#ifndef _ActiveTimerDemo_h_
#define _ActiveTimerDemo_h_

#include "SystemInclude.h"
#include "SystemError.h"

#include "TimerQueue/TimerQueueAdapter.h"

using namespace std;

// Listing 1 code/ch20
class EventHandlerStub: public EventHandler
{
public:
    EventHandlerStub (): count(0)
    {
        cout << "EventHandlerStub::EventHandlerStub" << endl;
    }

    // Handle the timeout.
    std::error_code HandleTimeOut(TimePoint, const void *arg = 0)
    {
        cout << "EventHandlerStub::handle_timeout" << endl;
        count++;
        return error_code();
    }

    uint_t GetTimerId()
    {
        return timerId;
    }

    void SetTimerId(uint_t timerId)
    {
        this->timerId = timerId;
    }

private:
    int count;
    uint_t timerId;
};

inline int ActiveTimerMain(int argc, char *argv[])
{
    // Create an "active" timer and start its thread.
    ActiveTimer activeTimer;
    activeTimer.Activate();

    shared_ptr<EventHandlerStub> handler = make_shared<EventHandlerStub>();
    uint_t timerId;
    activeTimer.Schedule(handler, nullptr, GetCurTime() + Duration(1000), Duration(500), &timerId);

    activeTimer.Wait();
    
    return 0;
}

#endif