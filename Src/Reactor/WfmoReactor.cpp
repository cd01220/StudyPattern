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

std::error_code WfmoReactor::HandleEventsImpl(Duration duration)
{
    error_code errCode;
    if (!isActived)
    {
        errCode = system_error_t::unknown_error;
        return errCode;
    }

    while (true)
    {
        errCode = this->WaitForMultipleObjects(duration);
        if (errCode)
            break;
    }

    return errCode;
}

std::error_code WfmoReactor::WaitForMultipleObjects(Duration duration)
{
    DWORD timeout = static_cast<DWORD>((duration == Duration::max()) ? INFINITE : duration.count());
    DWORD result = WAIT_IO_COMPLETION;
    while (result == WAIT_IO_COMPLETION)
    {
        //result = ::WaitForMultipleObjectsEx(AtomicWaitArray, atomicWaitArray, TRUE, timeout, TRUE);
    }

    error_code errCode;
    switch(result)
    {
    case WAIT_TIMEOUT:
        errCode = system_error_t::time_out;
        break;
    case WAIT_FAILED:
    case WAIT_ABANDONED_0:
        errCode = system_error_t::time_out;
        break;
    default:
        break;
    }

    return errCode;
}

std::error_code WfmoReactor::WaitForMultipleEvents(Duration duration)
{
    DWORD timeout = static_cast<DWORD>((duration == Duration::max()) ? INFINITE : duration.count());
    DWORD result = WAIT_TIMEOUT;
    //result = ::WaitForMultipleObjectsEx (this->handler_rep_.max_handlep1 (),
    //                                 this->handler_rep_.handles (),
    //                                 FALSE,
    //                                 timeout,
    //                                 alertable);
    error_code errCode;
    switch(result)
    {
    case WAIT_TIMEOUT:
        errCode = system_error_t::time_out;
        break;
    case WAIT_FAILED:
    case WAIT_ABANDONED_0:
        errCode = system_error_t::time_out;
        break;
    default:
        break;
    }
    return errCode;
}