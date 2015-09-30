#include "SystemInclude.h"
#include "SystemError.h"

#include "MessageQueue/MessageBlock.h"
#include "Reactor/WfmoReactor.h"
using namespace std;

/**********************class WfmoReactorHandlerRepository**********************/
WfmoReactorHandlerRepository::WfmoReactorHandlerRepository()
{}

WfmoReactorHandlerRepository::~WfmoReactorHandlerRepository()
{}

WfmoReactorHandlerRepository::iterator WfmoReactorHandlerRepository::begin()
{
    return repository.begin();
}

WfmoReactorHandlerRepository::iterator WfmoReactorHandlerRepository::end()
{
    return repository.end();
}

shared_ptr<EventHandler> WfmoReactorHandlerRepository::Find(Handle handle)
{
    auto iter = repository.find(handle);
    if (iter == repository.end())
        return nullptr;

    return iter->second;
}

std::shared_ptr<EventHandler> WfmoReactorHandlerRepository::Find(size_t index)
{
    assert(index < MAXIMUM_WAIT_OBJECTS);
    Handle handle = handles[index];
    auto iter = repository.find(handle);
    if (iter == repository.end())
        return nullptr;

    return iter->second;
}

Handle* WfmoReactorHandlerRepository::GetEventHandles()
{
    return handles;
}

size_t WfmoReactorHandlerRepository::GetSize()
{
    return repository.size();
}

void WfmoReactorHandlerRepository::Insert(std::shared_ptr<EventHandler> handler)
{
    assert(repository.find(handler->GetEventHandle()) == repository.end());
    auto ret = repository.insert(make_pair(handler->GetEventHandle(), handler));
    assert(ret.second);

    handles[repository.size() - 1] = handler->GetEventHandle();
}

/**********************class WfmoReactorNotify**********************/
//???????????????????
error_code WfmoReactorNotify::Notify(std::shared_ptr<EventHandler> handler, long mask)
{
    shared_ptr<MessageBlock> block = make_shared<MessageBlock>(MessageBlock(sizeof(NotificationBuffer)));
    NotificationBuffer *buffer = (NotificationBuffer*)block->GetPtr();
    buffer->handler = handler;
    buffer->mask = mask;

    Duration duration;
    error_code errCode = msgQueue.Push(block, duration);
    return errCode;
}

/**********************class WfmoReactor**********************/
bool WfmoReactor::IsActived()
{
    return true;
}

error_code WfmoReactor::HandleEvents(Duration duration)
{
    return HandleEventsImpl(duration);
}

error_code WfmoReactor::Notify(std::shared_ptr<EventHandler> handler,
                               long mask)
{
    return error_code();
}

error_code WfmoReactor::RegisterHandler(shared_ptr<EventHandler> handler)
{
    error_code errCode;
    errCode = RegisterHandlerImpl(handler);
    return errCode;
}

/**********************class WfmoReactor**********************/
/* protected member function */
error_code WfmoReactor::DeregisterHandlerImpl(std::shared_ptr<EventHandler> handler, 
                                              long mask)
{
    long newMask = handler->GetMask() & (~mask);
    handler->SetMask(newMask);

    int result = ::WSAEventSelect((SOCKET)handler->GetIoHandle(),
        handler->GetEventHandle(), handler->GetMask());
    if (result != 0)
    {
        int err = WSAGetLastError();
        /* */
        return system_error_t::unknown_error;
    }

    return error_code();
}

error_code WfmoReactor::Dispatch(DWORD waitStatus)
{
    DWORD index;
    
    if (waitStatus <= WAIT_OBJECT_0 + repository.GetSize())
        index = waitStatus - WAIT_OBJECT_0;
    else
        index = waitStatus - WAIT_ABANDONED_0;
    
    return DispatchHandles(index);
}

error_code WfmoReactor::DispatchHandles (size_t index)
{
    WSANETWORKEVENTS events;
    auto handler = repository.Find(index);

    if (::WSAEnumNetworkEvents((SOCKET)handler->GetIoHandle(), handler->GetEventHandle(),
                              &events) == SOCKET_ERROR)
    {
        return system_error_t::unknown_error;
    }

    long problems = UpCall(events.lNetworkEvents, handler);
    if (problems != EventHandler::NullMask)
    {
        this->DeregisterHandlerImpl(handler, problems);
    }

    /* we don't return handler error code to my caller, the handler should take care it's own error 
    *  status.
    */
    return error_code();
}

error_code WfmoReactor::HandleEventsImpl(Duration duration)
{
    if (!isActived)
    {
        return system_error_t::reactor_isnot_actived;
    }
    
    error_code errCode;
    while (!errCode)
    {
        errCode = this->WaitForMultipleEvents(duration);
        if (errCode)
            cout << errCode.message() << endl;
    }

    return errCode;
}

error_code WfmoReactor::RegisterHandlerImpl(shared_ptr<EventHandler> handler)
{
    error_code errCode;

    repository.Insert(handler);
    int result = ::WSAEventSelect((SOCKET)handler->GetIoHandle(),
        handler->GetEventHandle(), handler->GetMask());

    if (result == SOCKET_ERROR)
        return system_error_t::unknown_error;

    return errCode;
}

long WfmoReactor::UpCall(long events, shared_ptr<EventHandler> handler)
{
    long problems = EventHandler::NullMask;

    if ((events & FD_WRITE) != 0)
    {
        if (handler->HandleOutput())
            problems = problems | FD_WRITE;
    }

    if ((events & FD_CONNECT) != 0)
    {
        if (handler->HandleInput())
            problems = problems | FD_CONNECT;
    }

    if ((events & FD_OOB) != 0)
    {
        if (handler->HandleException())
            problems = problems | FD_OOB;
    }

    if ((events & FD_READ) != 0)
    {
        if (handler->HandleInput())
            problems = problems | FD_READ;
    }

    if ((events & FD_CLOSE) != 0)
    {
        if (handler->HandleInput())
            problems = problems | FD_CLOSE;
    }
    
    if ((events & FD_ACCEPT) != 0)
    {
        if (handler->HandleInput())
            problems = problems | FD_ACCEPT;
    }

    if ((events & FD_QOS) != 0)
    {
        if (handler->HandleQos())
            problems = problems | FD_QOS;
    }
    
    if ((events & FD_GROUP_QOS) != 0)
    {
        if (handler->HandleGroupQos())
            problems = problems | FD_GROUP_QOS;
    }

    return problems;
}

error_code WfmoReactor::WaitForMultipleEvents(Duration duration)
{
    DWORD timeout = static_cast<DWORD>((duration == Duration::max()) ? INFINITE : duration.count());

    error_code errCode;
    while (!errCode)
    {        
        DWORD result = ::WaitForMultipleObjectsEx(repository.GetSize(), repository.GetEventHandles(),
            FALSE, timeout, TRUE);        

        switch (result)
        {
        case WAIT_TIMEOUT:            
            if (timeout != 0)
                return system_error_t::time_out;
            return errCode;

        case WAIT_FAILED:
            return system_error_t::unknown_error;

        case WAIT_IO_COMPLETION:
            return errCode;

        default:
            errCode = Dispatch(result);
            break;
        }

        timeout = 0;
    }

    return errCode;
}