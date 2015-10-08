#include "SystemInclude.h"
#include "Demo/Client.h"

using namespace std;

/**********************class Client**********************/
Client::Client()
{
    reactor = new Reactor;
    notificationStrategy = make_shared<ReactorNotificationStrategy>(reactor, shared_from_this(), EventHandler::WriteMask);
}

Client::~Client()
{}

std::error_code Client::HandleInput()
{
    return error_code();
}

// Called when output is possible.
std::error_code Client::HandleOutput()
{
    return error_code();
}

std::error_code Client::HandleTimeOut(TimePoint, const void *arg)
{
    return error_code();
}


std::error_code Client::Open(void *args)
{
    error_code errCode;
    errCode = MyBase::Open(args);
    if (errCode)
        return errCode;

    this->msgQueue->SetNotificationStrategy(notificationStrategy);
    
    return error_code();
}