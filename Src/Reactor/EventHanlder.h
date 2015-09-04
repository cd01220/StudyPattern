#ifndef _EventHanlder_h_
#define _EventHanlder_h_

#include "SystemInclude.h"
#include "TimerQueue/TimerQueueFwd.h"

class ReactorImpl;
/**********************class EventHandler**********************/
/* class ACE_Event_Handler */
class EventHandler
{
public:
    virtual int HandleTimeOut(std::chrono::milliseconds, const void *arg = 0);
};

/**********************class ReactorNotify**********************/
/* ACE_Reactor_Notify */
class ReactorNotify
{
public:
    // = Initialization and termination methods.
  virtual int open (ReactorImpl *,
                    TimerQueue *timerQueue = 0,
                    int disableNotify = 0) = 0;

  virtual int close (void) = 0;
};

/**********************class EventHandler**********************/
/* class ACE_Select_Reactor_Notify */
class SelectReactorNotify: public ReactorNotify
{
};

#endif