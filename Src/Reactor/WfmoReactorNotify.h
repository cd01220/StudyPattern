#ifndef _WfmoReactorNotify_h_
#define _WfmoReactorNotify_h_

#include "Event/EventHandler.h" //Handle
#include "Reactor/ReactorNotify.h"
#include "MessageQueue/MessageQueue.h" //MessageQueue

struct SignalInfo
{
    SignalInfo (Handle handle);

    /// Win32 HANDLE that has become signaled.
    Handle handle;
};

class NotificationStrategy;  //for parameter of MessageQueue's construct function
/**********************class WfmoReactorNotify**********************/
/* class ACE_WFMO_Reactor_Notify */
class WfmoReactorNotify: public ReactorNotify
{
public:
    WfmoReactorNotify(std::shared_ptr<NotificationStrategy> msgQueueNs);
    virtual ~WfmoReactorNotify();
    /**
    * Called when the notification event waited on by
    * <ACE_WFMO_Reactor> is signaled.  This dequeues all pending
    * ACE_Event_Handlers and dispatches them.
    */
    /* int ACE_WFMO_Reactor_Notify::handle_signal() */
    std::error_code HandleSignal(int signalNum, SignalInfo SigInfor);
    /* int ACE_WFMO_Reactor_Notify::notify (ACE_Event_Handler *event_handler,
                                 ACE_Reactor_Mask mask,
                                 ACE_Time_Value *timeout)
    */
    std::error_code Notify(std::shared_ptr<EventHandler> handler, long mask);

private:
    MessageQueue msgQueue;
};

#endif