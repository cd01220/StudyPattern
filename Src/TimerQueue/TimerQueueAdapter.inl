#include "SystemInclude.h"

#include "TimerQueue/TimerQueueAdapter.h"

using namespace std;
/**********************class ThreadTimerQueueAdapter**********************/
/* Oringinal definition:
typedef ACE_Thread_Timer_Queue_Adapter<ACE_Timer_Heap> ActiveTimer; 

template <class TQ, class TYPE = ACE_Event_Handler*>
class ACE_Thread_Timer_Queue_Adapter : public ACE_Task_Base
*/
template <typename T1, typename T2>
ThreadTimerQueueAdapter<T1, T2>::ThreadTimerQueueAdapter()
{
    timerQueue = make_shared<T1>();
}

template <typename T1, typename T2>
ThreadTimerQueueAdapter<T1, T2>::~ThreadTimerQueueAdapter()
{}

template <typename T1, typename T2>
error_code ThreadTimerQueueAdapter<T1, T2>::Activate()
{
    std::lock_guard<mutex> lock(c11mutex);
    this->isActive = true;
    return TaskBase::Activate();
}

template <typename T1, typename T2>
error_code ThreadTimerQueueAdapter<T1, T2>::Cancel(uint_t timerId)
{
    error_code errCode;

    errCode = timerQueue->Cancel(timerId);
    if (errCode)
    {
        std::cerr << errCode.message() << std::endl;
    }

    return errCode;
}

template <typename T1, typename T2>
void ThreadTimerQueueAdapter<T1, T2>::Deactivate(void)
{
    std::lock_guard<mutex> lock(c11mutex);
    isActive = false;
    cv.notify_one();
}

template <typename T1, typename T2>
error_code ThreadTimerQueueAdapter<T1, T2>::Schedule(std::shared_ptr<T2> handler, 
    const void *act, 
    TimePoint future, 
    Duration  interval,
    uint_t    *timerId)
{
    error_code errCode;

    std::lock_guard<mutex> lock(c11mutex);
    errCode = timerQueue->Schedule(handler, act, future, interval, timerId);
    if (errCode)
    {
        cerr << errCode.message() << std::endl;
        return errCode;
    }

    cv.notify_one();
    return errCode;
}

template <typename T1, typename T2>
error_code ThreadTimerQueueAdapter<T1, T2>::ServiceRoutine()
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