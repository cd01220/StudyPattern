#ifndef _AbstractTimerQueue_h_
#define _AbstractTimerQueue_h_

#include "SystemInclude.h"
#include "TimerNode.h"

/**********************class AbstractTimerQueue**********************/
/* ACE_Abstract_Timer_Queue */
// T: ACE_Event_Handler
template<typename T>
class AbstractTimerQueue
{
public:
    AbstractTimerQueue() {}
    virtual ~AbstractTimerQueue() {}
    
    virtual std::error_code Schedule(std::shared_ptr<T> handler, 
        const void *arc, 
        TimePoint future, 
        TimeInterval interval) = 0;

    /**
    * Run the <functor> for all timers whose values are <= @a current_time.
    * This does not account for <timer_skew>.  Returns the number of
    * timers canceled.
    */
    virtual uint_t Expire(TimePoint currentTime) = 0;
    virtual uint_t Expire() = 0;

    /**
    * Cancel all timer associated with @a type.  If
    * @a dont_call_handle_close is 0 then the <functor> will be invoked,
    * which typically invokes the <handle_close> hook.  Returns number
    * of timers cancelled.
    */
    //virtual std::error_code Cancel(const T&, bool doCallHandleClose) = 0;

    /**
    * Close timer queue. Cancels all timers.
    */
    //virtual void Close(void) = 0;

    // Determine the next event to timeout.  Returns @a max if there are
    // no pending timers or if all pending timers are longer than max.
    // This method acquires a lock internally since it modifies internal state.
    /* Example:
    TimePoint maxTv = chrono::system_clock::now();
    TimePoint *thisTimeOut = this->timer_queue_->CalculateTimeout (&maxTv);
    if (*this_timeout == TimePoint::Zero)
    this->timer_queue_->expire();
    */
    //virtual TimeInterval CalculateTimeout(TimePoint max) = 0;
};

#endif