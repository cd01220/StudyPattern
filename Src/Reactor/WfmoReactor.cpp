#include "SystemInclude.h"
#include "SystemError.h"

#include "Reactor/WfmoReactor.h"
using namespace std;

/**********************class WfmoReactor**********************/
bool WfmoReactor::IsActived()
{
    return true;
}

std::error_code WfmoReactor::HandleEvents(Duration duration)
{
    return HandleEventsImpl(duration);
}

error_code WfmoReactor::RegisterHandler(shared_ptr<EventHandler> handler, long mask)
{
    error_code errCode;
    errCode = RegisterHandlerImpl(handler, mask);
    return errCode;
}

/**********************class WfmoReactor**********************/
error_code WfmoReactor::HandleEventsImpl(Duration duration)
{
    error_code errCode;
    if (!isActived)
    {
        errCode = system_error_t::reactor_isnot_actived;
        return errCode;
    }

    while (!errCode)
    {
        errCode = this->WaitForMultipleEvents(duration);
    }

    return errCode;
}

/* private member function */
error_code WfmoReactor::RegisterHandlerImpl(shared_ptr<EventHandler> handler, long mask)
{
    error_code errCode;

    auto iter = repository.find(handler->GetIoHandle());
    assert(iter == repository.end());
    HandlerMaskTuple tuple = {handler, mask};
    repository.insert(make_pair(handler->GetIoHandle(), tuple));

    int result = ::WSAEventSelect((SOCKET)handler->GetIoHandle(),
        handler->GetEventHandle(), mask);

    return errCode;
}

error_code WfmoReactor::WaitForMultipleEvents(Duration duration)
{
    DWORD timeout = static_cast<DWORD>((duration == Duration::max()) ? INFINITE : duration.count());
    DWORD result = WAIT_TIMEOUT;
    HANDLE *handles = new HANDLE[repository.size()];

    HANDLE *ptr = handles;
    for (auto iter = repository.begin(); iter != repository.end(); ++iter)
    {
        *ptr++ = iter->second.handler->GetEventHandle();
    }

    result = ::WaitForMultipleObjectsEx (repository.size(),
        handles, FALSE, timeout, TRUE);

    /* int ACE_WFMO_Reactor::dispatch (DWORD wait_status)  */
    error_code errCode;
    switch(result)
    {
    case WAIT_TIMEOUT:
    case WAIT_FAILED:
        errCode = system_error_t::time_out;
        break;

    default:
        break;
    }

    if (errCode)
        return errCode;

    WSANETWORKEVENTS events;
    Handle handle = ptr[result - WAIT_OBJECT_0];
    auto iter = repository.find(handle);
    Handle event = iter->second.handler->GetEventHandle();
    if (::WSAEnumNetworkEvents ((SOCKET) handle, event,
                              &events) == SOCKET_ERROR)
    {
        errCode = system_error_t::unknown_error;
        return errCode;
    }

    long actualEvents = events.lNetworkEvents;
    if ((actualEvents | FD_WRITE) != 0)
    {
        iter->second.handler->HandleInput();
    }

    return errCode;
}