#ifndef _TimerQueue_h_
#define _TimerQueue_h_

#include "AbstractTimerQueue.h"

/**********************class AbstractTimerQueue**********************/
/* ACE_Timer_Queue_Upcall_Base */
// T1: ACE_Event_Handler
// T2: ACE_Event_Handler_Handle_Timeout_Upcall
template<typename T1, typename T2>
class TimerQueueUpcallBase: public AbstractTimerQueue<T1>
{
public:
    explicit TimerQueueUpcallBase(T2 *upcallFunctor = 0);
    virtual ~TimerQueueUpcallBase (void);

    /// Accessor to the upcall functor
    T2& GetUpcallFunctor(void);

protected:
    T2 *upcallFunctor;
};

/**********************class TimerQueueT**********************/
/* class ACE_Timer_Queue_T */
// T1: ACE_Event_Handler
// T2: ACE_Event_Handler_Handle_Timeout_Upcall
template <class T1, class T2>
class TimerQueueT: public TimerQueueUpcallBase<T1, T2>
{
public:
    TimerQueueT (T2 *upcallFunctor = 0,
        std::list<void*> *freelist = 0);

    /// Destructor - make virtual for proper destruction of inherited
    /// classes.
    virtual ~TimerQueueT (void);

    virtual TimePoint EarliestTime(void) const = 0; 
    virtual TimeInterval CalculateTimeout(TimePoint max);

    /**
    * Implement ACE_Abstract_Timer_Queue<TYPE>::schedule () with the right
    * locking strategy.
    */
    virtual std::error_code Schedule(const T1 &type,
        const void *act,
        const TimePoint &futureTime,
        const TimeInterval &interval = TimeInterval(0));

protected:
    virtual std::error_code ScheduleImpl(const T1 &type,
        const void *act,
        const TimePoint &futureTime,
        const TimeInterval &interval = TimeInterval(0)) = 0;
};

#endif