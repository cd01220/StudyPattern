/* -*- C++ -*- */
// $Id: TimerDispatcher.h 80826 2008-03-04 14:51:23Z wotte $

/* 
#include "TimerQueue/TimerQueue.h"
#include "Demo/EventHandlerStub.h"
#include "Demo/TimerDispatcherStub.h"

int main(int, char *[])
{   
    TimerDispatcher &dispatcher = TimerDispatcher::GetInstance();
    dispatcher.Set(make_shared<TimerQueue>());

    shared_ptr<EventHandlerStub> handler = make_shared<EventHandlerStub>();

    uint_t timerId;
    dispatcher.Schedule(handler, nullptr, chrono::system_clock::now() + Duration(2000), Duration(500), &timerId);
    handler->SetTimerId(timerId);

    dispatcher.WaitForEvent();

    return 0;
}
*/

#ifndef _TimerDispatcher_h_
#define _TimerDispatcher_h_

#include "SystemInclude.h"

#include "Event/EventHandler.h"
#include "TimerQueue/TimeValue.h"
#include "TimerQueue/TimerQueue.h"

class TimerDispatcher
{
public:
    std::error_code Cancel(uint_t timerId);

    std::error_code Schedule(std::shared_ptr<EventHandler> handler, 
        const void *arc, 
        TimePoint future, 
        Duration  interval,
        uint_t    *timerId);

    void Set(std::shared_ptr<TimerQueue> timerQueue);
    void WaitForEvent (void);

    static TimerDispatcher& GetInstance()
    {
        static TimerDispatcher instance;
        return instance;
    }

private:
    TimerDispatcher() {}

private:
    std::shared_ptr<TimerQueue> timerQueue;
};

#endif /*TIMER_DISPATCHER_H*/

