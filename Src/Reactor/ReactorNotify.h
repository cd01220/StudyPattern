#ifndef _ReactorNotify_h_
#define _ReactorNotify_h_

#include "Event/EventHandler.h"   //EventHandler,  base class

class ReactorImpl;
class TimerQueue;

/**********************class ReactorNotify**********************/
/* ACE_Reactor_Notify */
class ReactorNotify: public EventHandler
{
public:
    ReactorNotify() {}
    virtual ~ReactorNotify() {}
    //  // = Initialization and termination methods.
    //virtual int open (ReactorImpl *,
    //                  TimerQueue *timerQueue = 0,
    //                  int disableNotify = 0) = 0;

    //virtual int close (void) = 0;
    virtual bool Notify(std::shared_ptr<EventHandler> handler, long mask) = 0;
    virtual bool Open(ReactorImpl *reactor, std::shared_ptr<TimerQueue>) = 0;
};

#endif