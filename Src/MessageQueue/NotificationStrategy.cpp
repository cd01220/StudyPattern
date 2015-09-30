#include "SystemInclude.h"

#include "MessageQueue/NotificationStrategy.h"
using namespace std;

/**********************class NotificationStrategy**********************/
NotificationStrategy::NotificationStrategy(shared_ptr<EventHandler> handler, long mask)
    : handler(handler), mask(mask)
{}

NotificationStrategy::~NotificationStrategy()
{}

/**********************class NotificationStrategy**********************/
ReactorNotificationStrategy::ReactorNotificationStrategy(Reactor *reactor, 
                                                         shared_ptr<EventHandler> handler, 
                                                         long mask)
    : NotificationStrategy(handler, mask), reactor(reactor)
{}

ReactorNotificationStrategy::~ReactorNotificationStrategy()
{}

error_code ReactorNotificationStrategy::Notify()
{
    return reactor->Notify(handler, mask);
}

error_code ReactorNotificationStrategy::Notify(shared_ptr<EventHandler> handler)
{
    return error_code();
}