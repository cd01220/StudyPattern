#include "SystemInclude.h"
#include "SystemError.h"

using namespace std;
using namespace this_thread;

#include "ace/Timer_Queue.h"
#include "ace/Timer_Heap.h"
#include "ace/Timer_Wheel.h"
#include "ace/Timer_Hash.h"
#include "ace/Timer_List.h"

#include "AceDemo/Callback.h"
#include "AceDemo/TimerDispatcher.h"

#include "TimerQueue/EventHandlerStub.h"
#include "TimerQueue/TimerQueue.h"
#include "TimerQueue/TimerQueue.inl"

int main (int, ACE_TCHAR *[])
{    
    TimerQueueT<EventHandlerStub> timerQueue;

    timerQueue.Schedule(make_shared<EventHandlerStub>(), nullptr, chrono::system_clock::now() + TimeInterval(5000), TimeInterval::zero());
    while(true)
    {
        timerQueue.Expire();
        SleepEx(1000, true);
    }

    ACE_Timer_Queue *timer_queue = new ACE_Timer_List;
    // setup the timer queue 
    Timer::instance()->set(timer_queue);

    CB cb[10];
    long args[10];
    for (long i = 0; i < 10 ; i++)
    {
        ACE_Time_Value const timeout(i);
        long timerID = Timer::instance()->schedule(&cb[i],
            &args[i],
            timer_queue->gettimeofday() + ACE_Time_Value(5),
            timeout);

        // Set the timerID state variable of the handler.
        cb[i].setID (timerID);

        // Implicitly send the handler it's timer id.
        args[i] = timerID;
    }

    // "run" the timer.
    Timer::instance()->wait_for_event ();
    return 0;
}
