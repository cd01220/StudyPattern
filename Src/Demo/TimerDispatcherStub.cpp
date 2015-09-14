#include "SystemInclude.h"

#include "Event/EventHandler.h"
#include "TimerQueue/TimeValue.h"
#include "TimerQueue/TimerQueue.h"
#include "Demo/TimerDispatcherStub.h"

using namespace std;
using namespace this_thread;

std::error_code TimerDispatcher::Cancel(uint_t timerId)
{
    return timerQueue->Cancel(timerId);
}

error_code TimerDispatcher::Schedule(std::shared_ptr<EventHandler> handler, 
        const void *act, 
        TimePoint future, 
        Duration  interval,
        uint_t    *timerId)
{
    error_code errCode = timerQueue->Schedule(handler, act, future, interval, timerId);
    return errCode;
}

void TimerDispatcher::Set(std::shared_ptr<TimerQueue> timerQueue)
{
    this->timerQueue = timerQueue;
}

void TimerDispatcher::WaitForEvent(void)
{
    while (true)
    {
        TimePoint maxTv = chrono::system_clock::now();
        Duration timeout = this->timerQueue->CalculateTimeout(maxTv);

        if (timeout != Duration::zero())
            this_thread::sleep_for(timeout);

        this->timerQueue->Expire();
    }
}
