#include "SystemInclude.h"
#include "Debug.h"

#include "Reactor/Reactor.h"
#include "Demo/EventHandlerStub.h"
using namespace std;

/**********************class EventHandlerStub**********************/
EventHandlerStub::EventHandlerStub(AcceptHandler acceptHandler)
    : acceptHandler(acceptHandler)
{
    dbgstrm << "Start." << endl;    
}

bool EventHandlerStub::HandleClose()
{
    dbgstrm << "Start." << endl;
    return error_code();
}

bool EventHandlerStub::HandleInput()
{
    dbgstrm << "Start." << endl;
    SOCKET acceptSocket;
    acceptSocket = accept((SOCKET)ioHandle, NULL, NULL);
    if (acceptSocket == INVALID_SOCKET)
    {
        errstrm << "accept failed:" << WSAGetLastError() << endl;
        return false;
    }

    acceptHandler(acceptSocket);
    return true;
}

bool EventHandlerStub::HandleOutput()
{
    dbgstrm << "Start." << endl;
    return true;
}

bool EventHandlerStub::HandleTimeOut(TimePoint, const void *arg)
{
    dbgstrm << "Start." << endl;
    return true;
}

bool EventHandlerStub::Open()
{
    SOCKET listenSocket;
    listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenSocket == INVALID_SOCKET) 
    {
        errstrm << "Error at socket(): " <<  WSAGetLastError() << endl;
        WSACleanup();
        return false;
    }

    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr("127.0.0.1");
    service.sin_port = htons(5000);

    if (::bind(listenSocket, (SOCKADDR*) &service, sizeof(service)) == SOCKET_ERROR) 
    {
        errstrm << "bind() failed." << endl;
        closesocket(listenSocket);
        WSACleanup();
        return false;
    }

    if (::listen(listenSocket, 1) == SOCKET_ERROR) 
    {
        errstrm << "Error listening on socket." << endl;
        closesocket(listenSocket);
        WSACleanup();
        return false;
    }

    this->ioHandle = (Handle)listenSocket;
    this->mask = AcceptMask;

    //if (!reactor->RegisterHandler(shared_from_this()))
    //{
    //    errstrm << "reactor->RegisterHandler() failed" << endl;
    //    return false;
    //}

    return true;
}

/**********************class ClientService**********************/
ClientService::ClientService()
{}

ClientService::~ClientService()
{
}

bool ClientService::HandleInput()
{ 
    const size_t bufSize = 256;
    char buffer[bufSize];
    int result = recv((SOCKET)ioHandle, buffer, bufSize - 1, 0);
    if (result <= 0)
    {
        return false;
    }
    buffer[result] = '\0';
    prtstrm << buffer;
    send((SOCKET)ioHandle, buffer, result, 0);

    return true;
}

bool ClientService::HandleTimeOut(TimePoint, const void *arg)
{
    return true;
}

bool ClientService::Open()
{
    //return reactor->RegisterHandler(shared_from_this());
    return true;
}