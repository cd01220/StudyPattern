#ifndef _Reactor_h_
#define _Reactor_h_

#include "TimeValue.h"  //TimePoint, Duration

class EventHandler;
class ReactorImpl;
/**********************class Reactor**********************/
/* class ACE_Reactor */
class Reactor
{
public:
    typedef std::function<bool(Reactor&)> ReactorEventHook;

    Reactor();
    virtual ~Reactor();

    bool Notify(std::shared_ptr<EventHandler> handler, long mask);

    /* int register_handler (ACE_Event_Handler *event_handler, ACE_Reactor_Mask mask); */
    bool RegisterHandler(std::shared_ptr<EventHandler> handler);
    
    /* static int ACE_Reactor::run_event_loop (void) */
    virtual bool RunEventLoop();

    /* int ACE_Reactor::run_reactor_event_loop (REACTOR_EVENT_HOOK eh) */
    virtual bool RunReactorEventLoop(ReactorEventHook hook);

    bool ScheduleTimer(std::shared_ptr<EventHandler> handler,
        const void *arg,
        TimePoint timePoint,
        Duration  interval);

private:
    std::shared_ptr<ReactorImpl> implementation;
};


#endif
