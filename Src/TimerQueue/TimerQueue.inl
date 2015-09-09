#include "SystemInclude.h"

using namespace std;

template<typename T1, typename T2>
T2& TimerQueueUpcallBase<T1, T2>::GetUpcallFunctor(void)
{
  return *this->upcallFunctor;
}

/**********************class TimerQueueT**********************/
template <class T1, class T2>
std::error_code TimerQueueT::Schedule<T1, T2>(const T1 &type,
        const void *act,
        const TimePoint &futureTime,
        const TimeInterval &interval = TimeInterval(0))
{
    ScheduleImpl(type, act, futureTime, interval);
}

template <class T1, class T2>
TimeInterval TimerQueueT::CalculateTimeout<T1, T2>(TimePoint max)
{
    if (IsEmpty())
        return TimeInterval(0);

    TimePoint curTime = chrono::system_clock::now();
    if (EarliestTime() > curTime)
    {
        // The earliest item on the Timer_Queue is still in the
        // future.  Therefore, use the smaller of (1) caller's wait
        // time or (2) the delta time between now and the earliest
        // time on the Timer_Queue.
        return chrono::duration_cast<chrono::TimeInterval>(EarliestTime() - max);
    }

    return TimeInterval(0);
}