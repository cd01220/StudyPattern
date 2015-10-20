#ifndef _WfmoReactorNotify_h_
#define _WfmoReactorNotify_h_

#include "Reactor/ReactorNotify.h"     //ReactorNotify: base class

class MessageQueue;
class ReactorImpl;
class TimerQueue;

/**********************class WfmoReactorNotify**********************/
/* class ACE_WFMO_Reactor_Notify */
class WfmoReactorNotify: public ReactorNotify
{
public:
    WfmoReactorNotify();
    virtual ~WfmoReactorNotify();
    /**
    * Called when the notification event waited on by
    * <ACE_WFMO_Reactor> is signaled.  This dequeues all pending
    * ACE_Event_Handlers and dispatches them.
    */
    /* int ACE_WFMO_Reactor_Notify::handle_signal() */
    bool HandleSignal();
    /* int ACE_WFMO_Reactor_Notify::notify (ACE_Event_Handler *event_handler,
                                 ACE_Reactor_Mask mask,
                                 ACE_Time_Value *timeout)
    */
    bool Notify(std::shared_ptr<EventHandler> handler, long mask);

    //int ACE_WFMO_Reactor_Notify::open (ACE_Reactor_Impl *wfmo_reactor,
    //                           ACE_Timer_Queue *timer_queue,
    //                           int ignore_notify)
    bool Open(ReactorImpl *reactor, std::shared_ptr<TimerQueue>);

private:
    std::shared_ptr<MessageQueue> msgQueue;
    /* shared timer queue with WfmoReactor */
    std::shared_ptr<TimerQueue> timerQueue;  
};

#endif