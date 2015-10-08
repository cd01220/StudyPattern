#ifndef _Reactor_h_
#define _Reactor_h_

#include "SystemInclude.h"
#include "Event/EventHandler.h"
#include "Reactor/ReactorImpl.h"

/**********************class Reactor**********************/
/* class ACE_Reactor */
class Reactor
{
public:
    typedef std::function<std::error_code(Reactor&)> ReactorEventHook;

    Reactor();
    virtual ~Reactor();

    std::error_code Notify(std::shared_ptr<EventHandler> handler, long mask);

    /* int register_handler (ACE_Event_Handler *event_handler, ACE_Reactor_Mask mask); */
    std::error_code RegisterHandler(std::shared_ptr<EventHandler> handler);
    
    /* int ACE_Reactor::run_event_loop (void) */
    virtual std::error_code RunEventLoop();

    /* int ACE_Reactor::run_reactor_event_loop (REACTOR_EVENT_HOOK eh) */
    virtual std::error_code RunReactorEventLoop(ReactorEventHook hook);

    std::error_code ScheduleTimer(std::shared_ptr<EventHandler> handler,
        const void *arg,
        TimePoint timePoint,
        Duration  interval);

private:
    std::shared_ptr<ReactorImpl> implementation;
};


#endif
