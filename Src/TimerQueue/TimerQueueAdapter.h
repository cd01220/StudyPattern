#if !defined(_TimerQueueAdapter_h_)
#define _TimerQueueAdapter_h_

#include "Task/TaskBase.h"
#include "TimerQueue/TimerQueue.h"

/**********************class ThreadTimerQueueAdapter**********************/
/* Oringinal definition:
typedef ACE_Thread_Timer_Queue_Adapter<ACE_Timer_Heap> ActiveTimer; 

template <class TQ, class TYPE = ACE_Event_Handler*>
class ACE_Thread_Timer_Queue_Adapter : public ACE_Task_Base
*/
// T1: TimerQueue
// T2: EventHandler
template<typename T1, typename T2>
class ThreadTimerQueueAdapter: public TaskBase
{
public:
    ThreadTimerQueueAdapter();
    virtual ~ThreadTimerQueueAdapter();
    
    std::error_code Activate();

    /// Cancel the @a timer_id and pass back the @a act if an address is
    /// passed in.
    std::error_code Cancel(uint_t timerId);

    // Inform the dispatching thread that it should terminate.
    void Deactivate (void);

    std::error_code Schedule(std::shared_ptr<T2> handler, 
        const void *act, 
        TimePoint future, 
        Duration  interval,
        uint_t    *timerId);

    // overwrite virtual function of TaskBase::ServiceRoutine
    virtual std::error_code ServiceRoutine();

private:
    std::shared_ptr<T1> timerQueue;
    bool isActive;

    std::mutex  c11mutex;
    std::condition_variable cv;
};

typedef ThreadTimerQueueAdapter<TimerQueueT<EventHandler>, EventHandler> ActiveTimer; 

#endif