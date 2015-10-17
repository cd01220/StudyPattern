#ifndef _ReactorImpl_h_
#define _ReactorImpl_h_

#include "SystemInclude.h"
#include "TimeValue.h"     //TimePoint, Duration

class EventHandler;

/**********************class ReactorImpl**********************/
/* class ACE_Reactor_Impl */
class ReactorImpl
{
public:
    virtual bool IsActived() = 0;

    /* int ACE_WFMO_Reactor::handle_events (ACE_Time_Value *how_long) */
    virtual bool HandleEvents(Duration duration) = 0;    
    virtual bool Notify(std::shared_ptr<EventHandler> handler, long mask) = 0;
    virtual bool RegisterHandler(std::shared_ptr<EventHandler> handler) = 0;

    virtual bool ScheduleTimer(std::shared_ptr<EventHandler> handler,
        const void *arg,
        TimePoint timePoint,
        Duration  interval) = 0;
};

#endif