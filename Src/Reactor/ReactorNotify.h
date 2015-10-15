#ifndef _ReactorNotify_h_
#define _ReactorNotify_h_

/**********************class ReactorNotify**********************/
/* ACE_Reactor_Notify */
class ReactorNotify
{
public:
    ReactorNotify() {}
    virtual ~ReactorNotify() {}
  //  // = Initialization and termination methods.
  //virtual int open (ReactorImpl *,
  //                  TimerQueue *timerQueue = 0,
  //                  int disableNotify = 0) = 0;

  //virtual int close (void) = 0;
    virtual std::error_code Notify(std::shared_ptr<EventHandler> handler, long mask) = 0;
};

#endif