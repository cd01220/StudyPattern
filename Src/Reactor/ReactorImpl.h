#ifndef _ReactorImpl_h_
#define _ReactorImpl_h_

#include "SystemInclude.h"

#include "Event/EventHandler.h"
#include "TimerQueue/AbstractTimerQueue.h"

/**********************class ReactorImpl**********************/
/* class ACE_Reactor_Impl */
class ReactorImpl
{
public:
    virtual bool IsActived() = 0;

    /* int ACE_WFMO_Reactor::handle_events (ACE_Time_Value *how_long) */
    virtual std::error_code HandleEvents(Duration duration) = 0;
    virtual std::error_code RegisterHandler(std::shared_ptr<EventHandler> handler, const Mask& mask) = 0;
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
};

/**********************class EventHandler**********************/
/* class ACE_Select_Reactor_Notify */
class SelectReactorNotify: public ReactorNotify
{
};

#endif