#if !defined(_TimerQueue_h_)
#define _TimerQueue_h_

#include "CopyDisabled.h"
#include "TimerNode.h"
#include "AbstractTimerQueue.h"

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

/**********************class TimerQueueT**********************/
/* class ACE_Timer_Queue_T */
// T1: ACE_Event_Handler
// T2: ACE_Event_Handler_Handle_Timeout_Upcall
template <class T1>
class TimerQueueT: public AbstractTimerQueue<T1>,
                   private CopyDisabled
{
public:
    typedef typename TimerNodeT<T1> TimerNode;
    TimerQueueT();

    // Destructor - make virtual for proper destruction of inherited
    // classes.
    virtual ~TimerQueueT(void);

    // virtual ACE_Time_Value *ACE_Timer_Queue_T::calculate_timeout (ACE_Time_Value *max);
    virtual TimeInterval CalculateTimeout(TimePoint max);
    
    /**
    * Implement ACE_Abstract_Timer_Queue<TYPE>::expire() with the right
    * locking strategy.
    */
    virtual uint_t Expire(void);
    virtual uint_t Expire(TimePoint currentTime);
    
    /**
    * Implement ACE_Abstract_Timer_Queue<TYPE>::schedule() with the right
    * locking strategy.
    */
    virtual std::error_code Schedule(std::shared_ptr<T1> handler, 
        const void *arc, 
        TimePoint future, 
        TimeInterval interval);

protected:
    
private:
    std::mutex c11mutex;
    std::list<std::shared_ptr<TimerNode>> timers;
};

#endif