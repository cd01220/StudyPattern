#if !defined(_EventHandler_h_)
#define _EventHandler_h_

#include "SystemInclude.h"
#include "TimerQueue/AbstractTimerQueue.h"

/**********************class EventHandler**********************/
/* class ACE_Event_Handler */
class EventHandler
{
public:
    virtual std::error_code HandleTimeOut(TimePoint, const void *arg = 0);
};

#endif