#include "SystemInclude.h"

#include "Event/EventHandler.h"
#include "Reactor/Reactor.h"
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

bool ReactorNotificationStrategy::Notify()
{
    return reactor->Notify(handler, mask);
}

/**********************class NotificationStrategy**********************/
//private member function
error_code ReactorNotificationStrategy::Notify(shared_ptr<EventHandler> handler)
{
    return error_code();
}