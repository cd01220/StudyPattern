#include "SystemInclude.h"
#include "Debug.h"

#include "MessageQueue/MessageBlock.h"
#include "MessageQueue/NotificationStrategy.h"
#include "MessageQueue/MessageQueue.h"

#include "Demo/Client.h"

using namespace std;

/**********************class Client**********************/
Client::Client()
{
    dbgstrm << "Start." << endl;
}

Client::~Client()
{}

bool Client::HandleInput()
{
    char buf[64];    
    int result = recv((SOCKET)this->ioHandle, buf, 64, 0);
    if (result != SOCKET_ERROR)
        cout << buf << endl;

    return true;
}

// Called when output is possible.
bool Client::HandleOutput()
{
    shared_ptr<MessageBlock> msg;
    while (msgQueue->Pop(msg, Duration::zero()))
    {
        char buf[] = "hello";
        int result = send((SOCKET)this->ioHandle, buf, sizeof(buf), 0);
        if (result == SOCKET_ERROR)
        {
            errstrm << "send() failed" << endl;
        }
    }

    return true;
}

bool Client::HandleTimeOut(TimePoint, const void *arg)
{
    dbgstrm << "Start" << endl;

    shared_ptr<MessageBlock> msg = make_shared<MessageBlock>();
    bool result = msgQueue->Push(msg, Duration::zero());
    if (!result)
    {
        errstrm << "Push() failed. " << endl;
        return false;
    }

    return true;
}

bool Client::Open(void *args)
{
    if (!MyBase::Open(args))
    {
        return false;
    }
    
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in clientService; 
    clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr("127.0.0.1");
    clientService.sin_port = htons(5000);

    int result = connect(sock, (SOCKADDR*)&clientService, sizeof(sockaddr_in));
    if (result == SOCKET_ERROR)
    {
        errstrm << "connect() failed" << endl;
        return false;
    }

    this->ioHandle = (Handle)sock;
    this->mask = EventHandler::ReadMask;
    
    //if (!reactor->RegisterHandler(shared_from_this()))
    //{
    //    errstrm << "RegisterHandler() failed" << endl;
    //    return false;
    //}

    /* Note:
       Set messge queue notification stratege, mask "EventHandler::WriteMask" means 
       a msgQueue->Push() call will cause this->HandleOutput() to be called.
    */
    //auto notifer = make_shared<ReactorNotificationStrategy>(reactor, 
    //    shared_from_this(), EventHandler::WriteMask);
    //msgQueue->SetNotificationStrategy(notifer);
    
    //return reactor->ScheduleTimer(shared_from_this(), 
    //    nullptr, GetCurTime() + Duration(1000), Duration(2000));
    return true;
}

