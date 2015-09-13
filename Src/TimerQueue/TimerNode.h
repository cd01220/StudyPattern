#if !defined(_TimerQueueIterator_h_)
#define _TimerQueueIterator_h_

#include "TimeValue.h"

/**********************class TimerNode**********************/
/* ACE_Timer_Node_Dispatch_Info_T */
// T: ACE_Event_Handler
//template <typename T>
//class TimerNodeDispatchInfoT
//{
//public:
//    T     value;
//    void  *arc;
//    bool  isRecurringTimer;
//};

/**********************class TimerNodeT**********************/
/* ACE_Timer_Node_T */
// T: ACE_Event_Handler
template <typename T>
class TimerNodeT
{
public:
    TimerNodeT(std::shared_ptr<T> value, const void *act, TimePoint timePoint, TimeInterval interval)
    {
        this->value = value;
        this->timePoint = timePoint;
        this->interval = interval;
        this->arc = act;
    }

public:
    // Type of object stored in the Queue
    std::shared_ptr<T> value;
    TimePoint    timePoint;
    TimeInterval interval;
    // arc: Asynchronous completion token associated with the timer.
    // the act will pass to EventHandler as a parameter.
    // For more detail, refer to 
    // "Asynchronous_Completion_Token_an_Object_Behavioral_Pattern_for_Efficient_Asynchronous_Event.pdf"
    const void *arc;
};

#endif