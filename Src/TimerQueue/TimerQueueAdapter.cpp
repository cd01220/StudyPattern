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
    lock_guard<mutex> lock(theMutex);
    isActive = true;
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
    lock_guard<mutex> lock(theMutex);
    isActive = false;
    theCv.notify_one();
}

bool ActiveTimer::Schedule(shared_ptr<EventHandler> handler, 
    const void *act, 
    TimePoint future, 
    Duration  interval,
    uint_t    *timerId)
{
    error_code errCode;

    lock_guard<mutex> lock(theMutex);
    if (!timerQueue->Schedule(handler, act, future, interval, timerId))
    {
        return false;
    }

    theCv.notify_one();
    return true;
}

bool ActiveTimer::ServiceRoutine()
{
    error_code errCode;

    while (isActive)
    {
        unique_lock<mutex> lock(theMutex);
        while(timerQueue->IsEmpty())
        {
            theCv.wait(lock);
        }

        Duration duration = timerQueue->CalculateTimeout();
        cv_status::cv_status status = theCv.wait_for(lock, duration);
        if (status == cv_status::timeout)
        {
            timerQueue->Expire();
        }

        lock.unlock();
    }

    return errCode;
}