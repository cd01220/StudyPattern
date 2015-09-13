#if !defined(_EventHandlerHandleTimeoutUpcall_h_)
#define _EventHandlerHandleTimeoutUpcall_h_

/* ACE define the class "ACE_Event_Handler_Handle_Timeout_Upcall", required by TimerQueue 
to call ACE_Event_Handler::handle_timeout(). The major function of this class is to process 
the reference counter of EventHandler. Now, with the C++11, we use shared_ptr to management
the reference counter, so we comment out relative .h and .cpp files.
*/

/* ACE_Event_Handler_Handle_Timeout_Upcall */
//class EventHandlerHandleTimeoutUpcall
//{
//public:
//    EventHandlerHandleTimeoutUpcall() {}
//    virtual ~EventHandlerHandleTimeoutUpcall() {}
//    
//    //called by ACE_Timer_Queue_T::schedule() function.
//    std::error_code Registration(TimerQueue& timerQueue, 
//        EventHandler *handler, const void *arg);
//
//    // This method is called before the timer expires.
//    std::error_code PreInvoke(TimerQueue &timerQueue,
//        EventHandler *handler,
//        const void   *arg,
//        bool         isRecurringTimer,
//        TimePoint    curTime,
//        const void   *upcallAct);
//
//    // This method is called when the timer expires.
//    std::error_code Timeout(TimerQueue &timerQueue,
//        EventHandler *handler,
//        const void   *arg,
//        bool         isRecurringTimer,
//        TimePoint    curTime);
//
//    // This method is called after the timer expires.
//    std::error_code PostInvoke(TimerQueue &timerQueue,
//        EventHandler *handler,
//        const void   *arg,
//        bool         isRecurringTimer,
//        TimePoint    curTime,
//        const void   *upcallAct);
//};

#endif