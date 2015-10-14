#ifndef _NotificationStrategy_h_
#define _NotificationStrategy_h_

#include "SystemInclude.h"

class Reactor;
class EventHandler;
/**********************class NotificationStrategy**********************/
/**
 * @class ACE_Notification_Strategy
 *
 * @brief Abstract class used for notifying an interested party
 *
 * A vehicle for extending the behavior of ACE_Message_Queue wrt
 * notification *without subclassing*.  Thus, it's an example of
 * the Bridge/Strategy patterns.
 */
/* ACE_Notification_Strategy */ 
class NotificationStrategy
{
public:
    NotificationStrategy(std::shared_ptr<EventHandler> handler, long mask);
    virtual ~NotificationStrategy();

    virtual std::error_code Notify() = 0;

protected:
    std::shared_ptr<EventHandler> handler;
    long mask;
};

/**********************class ReactorNotificationStrategy**********************/
class ReactorNotificationStrategy: public NotificationStrategy
{
public:    
    ReactorNotificationStrategy(Reactor *reactor, std::shared_ptr<EventHandler> handler, long mask);
    virtual ~ReactorNotificationStrategy();

    virtual std::error_code Notify();

private:
    virtual std::error_code Notify(std::shared_ptr<EventHandler> handler);

private:
    Reactor *reactor;
};

#endif