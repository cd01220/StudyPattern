#ifndef _TimerQueueFwd_h_
#define _TimerQueueFwd_h_

#include "SystemInclude.h"

/**********************class TimeValue**********************/
/* ACE_Time_Value */
typedef std::chrono::system_clock::time_point TimePoint;
typedef std::chrono::milliseconds TimeInterval;

/**********************class AbstractTimerQueue**********************/
/* ACE_Abstract_Timer_Queue */
template<typename EventHandlerType>
class AbstractTimerQueue
{
public:
    virtual ~AbstractTimerQueue() {};

    virtual bool IsEmpty (void) const = 0;

    // Returns the time of the earlier node in the Timer_Queue.  Must
    // be called on a non-empty queue.
    virtual TimePoint EarliestTime(void) const = 0; 

    // Determine the next event to timeout.  Returns @a max if there are
    // no pending timers or if all pending timers are longer than max.
    // This method acquires a lock internally since it modifies internal state.
    /* Example:
        TimePoint maxTv = chrono::system_clock::now();
        TimePoint *thisTimeOut = this->timer_queue_->CalculateTimeout (&maxTv);
        if (*this_timeout == TimePoint::Zero)
            this->timer_queue_->expire();
    */
    virtual TimeInterval CalculateTimeout(TimePoint max) = 0;

    virtual std::system_error Schedule(const EventHandlerType &handler, void *arg, 
                                       const TimePoint &time, const TimeInterval &interval);
    virtual std::error_code Expir() = 0;
    virtual std::error_code Cancel(const EventHandlerType&, bool) = 0;
    virtual void Close(void) = 0;
};

class EventHandler;

typedef AbstractTimerQueue<EventHandler> TimerQueue;

#endif