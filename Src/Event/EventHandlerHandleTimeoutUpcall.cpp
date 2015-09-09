#include "SystemInclude.h"

#include "EventHandler.h"
#include "EventHandlerHandleTimeoutUpcall.h"

using namespace std;

std::error_code EventHandlerHandleTimeoutUpcall::Registration(TimerQueue& timerQueue, 
    EventHandler *handler, const void *arg)
{
    error_code errCode;

    return errCode;
}

std::error_code EventHandlerHandleTimeoutUpcall::PreInvoke(TimerQueue &timerQueue,
    EventHandler *handler,
    const void *arg,
    TimeInterval interval,
    const TimePoint &curTime,
    const void *&upcallAct)
{
    return error_code();
}

std::error_code EventHandlerHandleTimeoutUpcall::Timeout(TimerQueue &timerQueue,
    EventHandler *handler,
    const void *arg,
    TimeInterval interval,
    const TimePoint &curTime)
{
    if (handler->HandleTimeOut(curTime, arg))
    {
        /* HandleTimeOut() failed, cancel timer queue */
        timerQueue.Cancel(*handler, true); // 0 means "call handle_close()".
    }

    return error_code();
}

std::error_code EventHandlerHandleTimeoutUpcall::PostInvoke(TimerQueue &timerQueue,
    EventHandler *handler,
    const void *arg,
    TimeInterval interval,
    const TimePoint &curTime,
    const void *upcallAct)
{
    return error_code();
}