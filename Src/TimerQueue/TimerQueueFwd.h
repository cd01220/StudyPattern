#ifndef _TimerQueueFwd_h_
#define _TimerQueueFwd_h_

#include "SystemInclude.h"

/**********************class TimeValue**********************/
/* ACE_Time_Value */
typedef std::chrono::milliseconds TimeValue;

/**********************class AbstractTimerQueue**********************/
/* ACE_Abstract_Timer_Queue */
template<typename Handler>
class AbstractTimerQueue
{
public:
    virtual ~AbstractTimerQueue() = 0;

    // Returns the time of the earlier node in the Timer_Queue.  Must
    // be called on a non-empty queue.
    virtual TimeValue EarliestTime(void) const = 0; 

    // Determine the next event to timeout.  Returns @a max if there are
    // no pending timers or if all pending timers are longer than max.
    // This method acquires a lock internally since it modifies internal state.
    virtual TimeValue* CalculateTimeout(TimeValue *max) = 0;

    virtual std::system_error Schedule(const Handler& handler, void *act, const TimeValue& time);
    virtual int Expir() = 0;

    virtual void Close(void) = 0;
};

class EventHandler;

typedef AbstractTimerQueue<EventHandler> TimerQueue;

#endif