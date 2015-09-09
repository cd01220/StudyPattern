#include "SystemInclude.h"

#include "TimeListT.h"
using namespace std;

template <class T1, class T2>
bool TimerListT<T1, T2>::IsEmpty(void) const
{
    return timers.size() == 0;
}

template <class T1, class T2>
std::error_code TimerListT<T1, T2>::ScheduleImpl(const T1 &type,
    const void *act,
    const TimePoint &futureTime,
    const TimeInterval &interval = TimeInterval(0))
{
}