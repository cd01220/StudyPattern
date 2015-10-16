#include "SystemInclude.h"
#include "SystemError.h"

#include "TimeValue.h"  //TimePoint, Duration

#include "Event/EventHandler.h"
#include "TimerQueue/TimerNode.h"
#include "TimerQueue/TimerQueue.h"

#if defined(max)
#undef max
#endif

using namespace std;

/**********************class TimerQueueUpcallBase**********************/
//template<typename T1, typename T2>
//TimerQueueUpcallBase<T1, T2>::TimerQueueUpcallBase(std::shared_ptr<T2> upcallFunctor)
//{
//    if (upcallFunctor == nullptr)
//        this->upcallFunctor = make_shared<T2>();
//    else
//        this->upcallFunctor = upcallFunctor;
//}
//
//template<typename T1, typename T2>
//TimerQueueUpcallBase<T1, T2>::~TimerQueueUpcallBase (void)
//{
//}
//
//template<typename T1, typename T2>
//T2& TimerQueueUpcallBase<T1, T2>::GetUpcallFunctor(void)
//{
//  return *this->upcallFunctor;
//}

/**********************class TimerQueue**********************/
TimerQueue::TimerQueue() 
{
    for (uint_t i = 0; i < MaxNodeNumber; ++i)
    {
        freeId.push_back(i);
    }
}


TimerQueue::~TimerQueue()
{}


Duration TimerQueue::CalculateTimeout()
{    
    lock_guard<std::mutex> lock(c11mutex);

    if (timers.empty())
    {
        return Duration::max();
    }

    TimePoint currentTime = std::chrono::system_clock::now();
    TimePoint earliestTime  = timers.top()->timePoint;
    if (earliestTime > currentTime)
    {
        // The earliest item on the Timer_Queue is still in the
        // future.  Therefore, use the smaller of (1) caller's wait
        // time or (2) the delta time between now and the earliest
        // time on the Timer_Queue.
        return chrono::duration_cast<Duration>(earliestTime - currentTime);
    }

    return Duration::zero();
}

std::error_code TimerQueue::Cancel(uint_t timerId)
{
    lock_guard<std::mutex> lock(c11mutex);
    CancelTimerId(timerId);
    return error_code();
}


uint_t TimerQueue::Expire(void)
{
    lock_guard<std::mutex> lock(c11mutex);
    if (timers.empty())
        return 0;

    TimePoint currentTime = chrono::system_clock::now();
    return this->ExpireImpl(currentTime);
}

uint_t TimerQueue::Expire(TimePoint currentTime)
{
    lock_guard<std::mutex> lock(c11mutex);
    return this->ExpireImpl(currentTime);
}

bool TimerQueue::IsEmpty()
{
    lock_guard<std::mutex> lock(c11mutex);
    return timers.empty();
}

std::error_code TimerQueue::Schedule(std::shared_ptr<EventHandler> handler, 
    const void *act, TimePoint future, Duration interval, uint_t *timerId)
{
    lock_guard<std::mutex> lock(c11mutex);

    error_code errCode;
    if (freeId.empty())
    {
        errCode = system_error_t::no_free_timer_id;
        return errCode;
    }
    uint_t id = AllocTimerId();
    if (timerId != nullptr)
    {
        *timerId = id;
    }

    timers.push(make_shared<TimerNode>(handler, act, future, interval, id));

    return errCode;
}

/**********************class TimerQueue**********************/
/* private member function */

uint_t TimerQueue::AllocTimerId()
{
    assert(!freeId.empty());

    uint_t id = freeId.front();
    freeId.pop_front();
    return id;
}


void TimerQueue::CancelTimerId(uint_t timerId)
{
    canceledId.set(timerId);
}


uint_t TimerQueue::ExpireImpl(TimePoint currentTime)
{
    uint_t numberOfExpiredTimer = 0;
    while(!timers.empty())
    {
        std::shared_ptr<TimerNode> node = timers.top();
        if (node->timePoint > currentTime)
            break;

        timers.pop();
        if (canceledId.test(node->timerId))
        {
            FreeTimerId(node->timerId);            
            continue;
        }

        node->handler->HandleTimeOut(currentTime, node->act);
        if (node->interval != Duration::zero())
        {
            node->timePoint = currentTime + node->interval;
            timers.push(node);
        }
        ++numberOfExpiredTimer;
    }

    return numberOfExpiredTimer;
}


void TimerQueue::FreeTimerId(uint_t timerId)
{    
    canceledId.reset(timerId);
    freeId.push_back(timerId);
}

