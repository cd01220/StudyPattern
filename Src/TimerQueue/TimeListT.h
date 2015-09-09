#if !defined(_TimeListT_h_)
#define _TimeListT_h_

#include "TimerQueue.h"

/**********************class TimerListT**********************/
/* class ACE_Timer_List_T */
// T1: ACE_Event_Handler
// T2: ACE_Event_Handler_Handle_Timeout_Upcall
template <class T1, class T2>
class TimerListT: public TimerQueueT<T1, T2>
{
public:
    // True if queue is empty, else false.
    virtual bool IsEmpty(void) const;

protected:
    std::error_code ScheduleImpl(const T1 &type,
        const void *act,
        const TimePoint &futureTime,
        const TimeInterval &interval = TimeInterval(0));

private:
    std::list<void *> timers;
};
#endif