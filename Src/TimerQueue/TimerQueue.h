#ifndef _TimerQueue_h_
#define _TimerQueue_h_

#include "CopyDisabled.h"                   //base class
#include "TimerQueue/AbstractTimerQueue.h"  //base class

class EventHandler;
template<typename T> class TimerNodeT; 

/**********************class TimerQueueUpcallBase**********************/
/* ACE define the class "ACE_Event_Handler_Handle_Timeout_Upcall", required by TimerQueue 
to call ACE_Event_Handler::handle_timeout(). The major function of this class is to process 
the reference counter of EventHandler. Now, with the C++11, we use shared_ptr to management
the reference counter, so we comment out class AbstractTimerQueue.
*/

/* ACE_Timer_Queue_Upcall_Base */
// T1: ACE_Event_Handler
// T2: ACE_Event_Handler_Handle_Timeout_Upcall
//template<typename T1, typename T2>
//class TimerQueueUpcallBase: public AbstractTimerQueue<T1>,
//                            private CopyDisabled
//{
//public:
//    explicit TimerQueueUpcallBase(std::shared_ptr<T2> upcallFunctor = nullptr);
//    virtual ~TimerQueueUpcallBase (void);
//
//    // Accessor to the upcall functor
//    T2& GetUpcallFunctor(void);
//
//protected:
//    std::shared_ptr<T2> upcallFunctor;
//};

/**********************class TimerQueue**********************/
/* class ACE_Timer_Queue_T */
// T1: ACE_Event_Handler
// T2: ACE_Event_Handler_Handle_Timeout_Upcall
class TimerQueue: public AbstractTimerQueue<EventHandler>,
                  private CopyDisabled
{
public:
    typedef TimerNodeT<EventHandler> TimerNode;
    enum: uint_t { MaxNodeNumber = 65535 };
    TimerQueue();

    // Destructor - make virtual for proper destruction of inherited
    // classes.
    virtual ~TimerQueue();

    // virtual ACE_Time_Value *ACE_Timer_Queue_T::calculate_timeout (ACE_Time_Value *max);
    virtual Duration CalculateTimeout();
    /**
    * Cancel all timer associated with @a type.  If
    * @a dont_call_handle_close is 0 then the <functor> will be invoked,
    * which typically invokes the <handle_close> hook.  Returns number
    * of timers cancelled.
    */
    virtual std::error_code Cancel(uint_t timerId);

    /**
    * Implement ACE_Abstract_Timer_Queue<TYPE>::expire() with the right
    * locking strategy.
    */
    virtual uint_t Expire(void);
    virtual uint_t Expire(TimePoint currentTime);
    
    virtual bool IsEmpty();

    /**
    * Implement ACE_Abstract_Timer_Queue<TYPE>::schedule() with the right
    * locking strategy.
    */
    virtual std::error_code Schedule(std::shared_ptr<EventHandler> handler, 
        const void *act, 
        TimePoint future, 
        Duration  interval,
        uint_t    *timerId);

private:
    uint_t AllocTimerId();
    void CancelTimerId(uint_t timerId);
    /**
    * interally implement of Expire(TimePoint currentTime) without lock.
    */
    uint_t ExpireImpl(TimePoint currentTime);

    void FreeTimerId(uint_t timerId);
    
private:
    std::mutex c11mutex;
    std::priority_queue<std::shared_ptr<TimerNode>> timers;
    std::list<uint_t> freeId; 
    std::bitset<MaxNodeNumber> canceledId;
};

#endif