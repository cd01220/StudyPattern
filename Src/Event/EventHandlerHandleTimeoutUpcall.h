#if !defined(_EventHandlerHandleTimeoutUpcall_h_)
#define _EventHandlerHandleTimeoutUpcall_h_

#include "SystemInclude.h"
#include "TimerQueue/AbstractTimerQueue.h"

/* ACE_Event_Handler_Handle_Timeout_Upcall */
class EventHandlerHandleTimeoutUpcall
{
public:
    EventHandlerHandleTimeoutUpcall() {}
    virtual ~EventHandlerHandleTimeoutUpcall() {}
    
    std::error_code Registration(TimerQueue& timerQueue, 
        EventHandler *handler, const void *arg);

    // This method is called before the timer expires.
    std::error_code PreInvoke (TimerQueue &timerQueue,
        EventHandler *handler,
        const void *arg,
        TimeInterval interval,
        const TimePoint &curTime,
        const void *&upcallAct);

    // This method is called when the timer expires.
    std::error_code Timeout (TimerQueue &timerQueue,
        EventHandler *handler,
        const void *arg,
        TimeInterval interval,
        const TimePoint &curTime);

    // This method is called after the timer expires.
    std::error_code PostInvoke (TimerQueue &timerQueue,
        EventHandler *handler,
        const void *arg,
        TimeInterval interval,
        const TimePoint &curTime,
        const void *upcallAct);
};

#endif