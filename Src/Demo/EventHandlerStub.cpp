#include "SystemInclude.h"
#include "SystemError.h"
#include "Debug.h"

#include "Reactor/Reactor.h"
#include "Demo/EventHandlerStub.h"
using namespace std;

/**********************class EventHandlerStub**********************/
EventHandlerStub::EventHandlerStub(Reactor *reactor)
    : EventHandler(reactor)
{
    dbgstrm << "Start." << endl;    
}

error_code EventHandlerStub::HandleClose()
{
    dbgstrm << "Start." << endl;
    return error_code();
}

error_code EventHandlerStub::HandleInput()
{
    dbgstrm << "Start." << endl;    
    SOCKET acceptSocket;
    acceptSocket = accept((SOCKET)ioHandle, NULL, NULL);
    if (acceptSocket == INVALID_SOCKET)
    {
        errstrm << "accept failed:" << WSAGetLastError() << endl;
        return system_error_t::unknown_error;
    }

    std::shared_ptr<ClientService> client = std::make_shared<ClientService>(this->reactor);
    client->SetIoHandle((Handle)acceptSocket);    
    client->SetMask(ReadMask);
    error_code errCode = client->Open();
    if (errCode)
        client->HandleClose();

    return errCode;
}

error_code EventHandlerStub::HandleOutput()
{
    dbgstrm << "Start." << endl;
    return error_code();
}

error_code EventHandlerStub::HandleTimeOut(TimePoint, const void *arg)
{
    dbgstrm << "Start." << endl;
    return error_code();
}

error_code EventHandlerStub::Open()
{
    SOCKET listenSocket;
    listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenSocket == INVALID_SOCKET) 
    {
        errstrm << "Error at socket(): " <<  WSAGetLastError() << endl;
        WSACleanup();
        return system_error_t::unknown_error;
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
        return system_error_t::unknown_error;
    }

    if (::listen(listenSocket, 1) == SOCKET_ERROR) 
    {
        errstrm << "Error listening on socket." << endl;
        closesocket(listenSocket);
        WSACleanup();
        return system_error_t::unknown_error;
    }

    this->SetIoHandle((Handle)listenSocket);
    this->SetMask(AcceptMask);
    error_code errCode = reactor->RegisterHandler(shared_from_this());
    if (errCode)
        errstrm << errCode.message();

    return errCode;
}

/**********************class ClientService**********************/
ClientService::ClientService(Reactor *reactor)
    : EventHandler(reactor)
{
    eventHandle = CreateEvent(NULL, TRUE, FALSE, TEXT("ClientServiceEvent"));
}

ClientService::~ClientService()
{
}

error_code ClientService::HandleInput()
{ 
    const size_t bufSize = 256;
    char buffer[bufSize];
    int result = recv((SOCKET)ioHandle, buffer, bufSize - 1, 0);
    if (result <= 0)
    {
        return system_error_t::unknown_error;
    }
    buffer[result] = '\0';
    prtstrm << buffer;
    send((SOCKET)ioHandle, buffer, result, 0);

    return error_code();
}

error_code ClientService::HandleTimeOut(TimePoint, const void *arg)
{
    return error_code();
}

error_code ClientService::Open()
{
    error_code errCode = reactor->RegisterHandler(shared_from_this());
    if (errCode)
        errstrm << errCode.message();

    return errCode;
}