#ifndef _TimerQueueAdapter_h_
#define _TimerQueueAdapter_h_

#include "Task/TaskBase.h"
#include "TimerQueue/TimerQueue.h"

/**********************class ActiveTimer**********************/
/* Oringinal definition:
typedef ACE_Thread_Timer_Queue_Adapter<ACE_Timer_Heap> ActiveTimer; 

template <class TQ, class TYPE = ACE_Event_Handler*>
class ACE_Thread_Timer_Queue_Adapter : public ACE_Task_Base
*/
// T1: TimerQueue
// T2: EventHandler 
class ActiveTimer: public TaskBase
{
public:
    ActiveTimer();
    virtual ~ActiveTimer();
    
    std::error_code Activate();

    /// Cancel the @a timer_id and pass back the @a act if an address is
    /// passed in.
    std::error_code Cancel(uint_t timerId);

    // Inform the dispatching thread that it should terminate.
    void Deactivate (void);

    std::error_code Schedule(std::shared_ptr<EventHandler> handler, 
        const void *act, 
        TimePoint future, 
        Duration  interval,
        uint_t    *timerId);

    // ACE_Thread_Timer_Queue_Adapter::svc()
    // overwrite virtual function of TaskBase::ServiceRoutine
    virtual std::error_code ServiceRoutine();

private:
    std::shared_ptr<TimerQueue> timerQueue;
    bool isActive;

    std::mutex  c11mutex;
    std::condition_variable cv;
};


#endif