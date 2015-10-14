#ifndef _ReactorImpl_h_
#define _ReactorImpl_h_

#include "SystemInclude.h"
#include "TimerQueue/TimeValue.h"  //TimePoint, Duration

class EventHandler;

/**********************class ReactorImpl**********************/
/* class ACE_Reactor_Impl */
class ReactorImpl
{
public:
    virtual bool IsActived() = 0;

    /* int ACE_WFMO_Reactor::handle_events (ACE_Time_Value *how_long) */
    virtual std::error_code HandleEvents(Duration duration) = 0;    
    virtual std::error_code Notify(std::shared_ptr<EventHandler> handler, long mask) = 0;
    virtual std::error_code RegisterHandler(std::shared_ptr<EventHandler> handler) = 0;
    virtual std::error_code ScheduleTimer(std::shared_ptr<EventHandler> handler,
        const void *arg,
        TimePoint timePoint,
        Duration  interval) = 0;
};

/**********************class ReactorNotify**********************/
/* ACE_Reactor_Notify */
class ReactorNotify
{
public:
  //  // = Initialization and termination methods.
  //virtual int open (ReactorImpl *,
  //                  TimerQueue *timerQueue = 0,
  //                  int disableNotify = 0) = 0;

  //virtual int close (void) = 0;
    virtual std::error_code Notify(std::shared_ptr<EventHandler> handler, long mask) = 0;
};

#endif