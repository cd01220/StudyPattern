#if !defined(_ReactorImpl_h_)
#define _ReactorImpl_h_

#include "SystemInclude.h"
#include "TimerQueue/AbstractTimerQueue.h"

class ReactorImpl;

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