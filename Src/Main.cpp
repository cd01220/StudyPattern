#include "SystemInclude.h"
#include "SystemError.h"

using namespace std;
using namespace this_thread;

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
