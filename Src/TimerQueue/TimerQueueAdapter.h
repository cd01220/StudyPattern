#if !defined(_TimerQueueAdapter_h_)
#define _TimerQueueAdapter_h_

/* Oringinal definition:
typedef ACE_Thread_Timer_Queue_Adapter<ACE_Timer_Heap> ActiveTimer; 

template <class TQ, class TYPE = ACE_Event_Handler*>
class ACE_Thread_Timer_Queue_Adapter : public ACE_Task_Base
*/

/**********************class TimerQueueT**********************/
/* class ACE_Timer_Queue_T */
// T1: TimerQueue
template<typename T1>
class ThreadTimerQueueAdapter: public TaskBase
{
};

#endif