#include "SystemInclude.h"

#include "TimerQueue/TimerQueueAdapter.h"

using namespace std;
/**********************class ActiveTimer**********************/
/* Oringinal definition:
typedef ACE_Thread_Timer_Queue_Adapter<ACE_Timer_Heap> ActiveTimer; 

template <class TQ, class TYPE = ACE_Event_Handler*>
class ACE_Thread_Timer_Queue_Adapter : public ACE_Task_Base
*/
ActiveTimer::ActiveTimer()
{
    timerQueue = make_shared<TimerQueue>();
}

ActiveTimer::~ActiveTimer()
{}

bool ActiveTimer::Activate()
{
    std::lock_guard<mutex> lock(c11mutex);
    this->isActive = true;
    return TaskBase::Activate();
}

bool ActiveTimer::Cancel(uint_t timerId)
{
    if (!timerQueue->Cancel(timerId))
    {
        return false;
    }

    return true;
}

void ActiveTimer::Deactivate(void)
{
    std::lock_guard<mutex> lock(c11mutex);
    isActive = false;
    cv.notify_one();
}

bool ActiveTimer::Schedule(std::shared_ptr<EventHandler> handler, 
    const void *act, 
    TimePoint future, 
    Duration  interval,
    uint_t    *timerId)
{
    error_code errCode;

    std::lock_guard<mutex> lock(c11mutex);
    if (!timerQueue->Schedule(handler, act, future, interval, timerId))
    {
        return false;
    }

    cv.notify_one();
    return true;
}

bool ActiveTimer::ServiceRoutine()
{
    error_code errCode;

    while (isActive)
    {
        unique_lock<std::mutex> lock(c11mutex);
        while(timerQueue->IsEmpty())
        {
            cv.wait(lock);
        }

        Duration duration = timerQueue->CalculateTimeout();
        std::cv_status::cv_status status = cv.wait_for(lock, duration);
        if (status == cv_status::timeout)
        {
            timerQueue->Expire();
        }

        lock.unlock();
    }

    return errCode;
}