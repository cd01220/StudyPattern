#include "SystemInclude.h"

#include "TimeValue.h"
#include "TimerQueue.h"

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
{}

template <class T1>
TimerQueueT<T1>::~TimerQueueT(void)
{}


template <class T1>
TimeInterval TimerQueueT<T1>::CalculateTimeout(TimePoint currentTime)
{
    lock_guard<std::mutex> lock(c11mutex);

    if (timers.size() == 0)
    {
        return TimeInterval::max();
    }

    TimePoint earliestTime  = timers.front()->timePoint;
    if (earliestTime > currentTime)
    {
        // The earliest item on the Timer_Queue is still in the
        // future.  Therefore, use the smaller of (1) caller's wait
        // time or (2) the delta time between now and the earliest
        // time on the Timer_Queue.
        return chrono::duration_cast<TimeInterval>(earliestTime - currentTime);
    }

    return TimeInterval::zero();
}

template <class T1>
uint_t TimerQueueT<T1>::Expire(void)
{
    if (this->timers.size() == 0)
        return 0;
        
    TimePoint currentTime = chrono::system_clock::now();
    return this->Expire(currentTime);
}

template <class T1>
uint_t TimerQueueT<T1>::Expire(TimePoint currentTime)
{
    lock_guard<std::mutex> lock(c11mutex);

    uint_t numberOfExpiredTimer = 0;
    for (auto iter = timers.begin(); iter != timers.end(); ++iter)
    {
        if ((*iter)->timePoint > currentTime)
        {            
            break;
        }

        (*iter)->value->HandleTimeOut(currentTime, (*iter)->arc);
        ++numberOfExpiredTimer;
    }

    return numberOfExpiredTimer;
}

template <class T1>
std::error_code TimerQueueT<T1>::Schedule(std::shared_ptr<T1> handler, 
    const void *arc, 
    TimePoint future, 
    TimeInterval interval)
{
    auto node = make_shared<TimerNode>(handler, arc, future, interval);
    timers.push_back(node);

    return error_code();
}


