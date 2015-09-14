#include "SystemInclude.h"
#include "SystemError.h"

#include "TimerQueue/TimeValue.h"
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

/**********************class TimerQueueT**********************/
template <class T1>
TimerQueueT<T1>::TimerQueueT() 
{
    for (uint_t i = 0; i < MaxNodeNumber; ++i)
    {
        freeId.push_back(i);
    }
}

template <class T1>
TimerQueueT<T1>::~TimerQueueT(void)
{}


template <class T1>
Duration TimerQueueT<T1>::CalculateTimeout(TimePoint currentTime)
{
    lock_guard<std::mutex> lock(c11mutex);

    if (timers.empty())
    {
        return Duration::max();
    }

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

template <class T1>
std::error_code TimerQueueT<T1>::Cancel(uint_t timerId)
{
    //caller may call this function in the Expire() context, this will cause
    //re-lock().
    //lock_guard<std::mutex> lock(c11mutex);
    CancelTimerId(timerId);
    return error_code();
}

template <class T1>
uint_t TimerQueueT<T1>::Expire(void)
{
    lock_guard<std::mutex> lock(c11mutex);
    if (timers.empty())
        return 0;

    TimePoint currentTime = chrono::system_clock::now();
    return this->ExpireImpl(currentTime);
}

template <class T1>
uint_t TimerQueueT<T1>::Expire(TimePoint currentTime)
{
    lock_guard<std::mutex> lock(c11mutex);
    return this->ExpireImpl(currentTime);
}

template <class T1>
std::error_code TimerQueueT<T1>::Schedule(std::shared_ptr<T1> handler, 
    const void *act, TimePoint future, Duration interval, uint_t *timerId)
{
    lock_guard<std::mutex> lock(c11mutex);

    error_code errCode;
    if (freeId.empty())
    {
        errCode = system_error_t::no_id_space;
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

/**********************class EventHandler**********************/
/* private member function */
template <class T1>
uint_t TimerQueueT<T1>::AllocTimerId()
{
    assert(!freeId.empty());

    uint_t id = freeId.front();
    freeId.pop_front();
    return id;
}

template <class T1>
void TimerQueueT<T1>::CancelTimerId(uint_t timerId)
{
    canceledId.set(timerId);
}

template <class T1>
uint_t TimerQueueT<T1>::ExpireImpl(TimePoint currentTime)
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

template <class T1>
void TimerQueueT<T1>::FreeTimerId(uint_t timerId)
{    
    canceledId.reset(timerId);
    freeId.push_back(timerId);
}

