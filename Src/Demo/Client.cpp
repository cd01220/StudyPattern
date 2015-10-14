#include "SystemInclude.h"
#include "Debug.h"

#include "Reactor/Reactor.h"
#include "MessageQueue/MessageQueue.h"
#include "MessageQueue/NotificationStrategy.h"
#include "Demo/Client.h"

using namespace std;

/**********************class Client**********************/
Client::Client(Reactor *reactor)
    : Task(reactor)
{
    dbgstrm << "Start." << endl;
    eventHandle = CreateEvent(NULL, TRUE, FALSE, TEXT("ClientEvent")); 
}

Client::~Client()
{
    delete reactor;
}

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
    cout << "HandleTimeOut" << endl;
    shared_ptr<MessageBlock> msg = make_shared<MessageBlock>();
    this->msgQueue->Push(msg, Duration::zero());
    return error_code();
}

std::error_code Client::Open(void *args)
{
    error_code errCode;
    errCode = MyBase::Open(args);
    if (errCode)
        return errCode;
    
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

    notifer = make_shared<ReactorNotificationStrategy>(reactor, shared_from_this(), EventHandler::WriteMask);
    this->msgQueue->SetNotificationStrategy(this->notifer);
    
    errCode = reactor->ScheduleTimer(shared_from_this(), nullptr, GetCurTime() + Duration(1000), Duration(500));

    return errCode;
}

