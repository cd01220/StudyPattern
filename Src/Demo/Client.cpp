#include "SystemInclude.h"
#include "Debug.h"

#include "Reactor/Reactor.h"
#include "MessageQueue/MessageBlock.h"
#include "MessageQueue/NotificationStrategy.h"
#include "MessageQueue/MessageQueue.h"

#include "Demo/Client.h"

using namespace std;

/**********************class Client**********************/
Client::Client(Reactor *reactor)
    : Task(reactor)
{
    dbgstrm << "Start." << endl;
}

Client::~Client()
{}

bool Client::HandleInput()
{
    return true;
}

// Called when output is possible.
bool Client::HandleOutput()
{
    return true;
}

bool Client::HandleTimeOut(TimePoint, const void *arg)
{
    cout << "HandleTimeOut" << endl;
    
    std::shared_ptr<MessageBlock> msg = std::make_shared<MessageBlock>();

    return Push(msg, Duration::zero());
}

bool Client::Open(void *args)
{
    if (!MyBase::Open(args))
        return false;
    
    //SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    //sockaddr_in clientService; 
    //clientService.sin_family = AF_INET;
    //clientService.sin_addr.s_addr = inet_addr("127.0.0.1");
    //clientService.sin_port = htons(5000);

    //this->SetIoHandle((Handle)sock);
    //this->SetMask(NullMask);
    //errCode = reactor->RegisterHandler(shared_from_this());
    //if (errCode)
    //    errstrm << errCode.message();

    auto notifer = make_shared<ReactorNotificationStrategy>(reactor, 
        shared_from_this(), EventHandler::WriteMask);
    this->msgQueue->SetNotificationStrategy(notifer);
    
    return reactor->ScheduleTimer(shared_from_this(), 
        nullptr, GetCurTime() + Duration(1000), Duration(1000));
}

