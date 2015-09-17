#ifndef _TimerQueueIterator_h_
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
    TimerNodeT(std::shared_ptr<T> handler, const void *act, 
        TimePoint timePoint, Duration interval, uint_t timerId)
    {
        this->handler = handler;
        this->timePoint = timePoint;
        this->interval = interval;
        this->act = act;
        this->timerId = timerId;
    }

public:
    // Type of object stored in the Queue
    std::shared_ptr<T> handler;
    TimePoint          timePoint;
    Duration           interval;
    // arc: Asynchronous completion token associated with the timer.
    // the act will pass to EventHandler as a parameter.
    // For more detail, refer to 
    // "Asynchronous_Completion_Token_an_Object_Behavioral_Pattern_for_Efficient_Asynchronous_Event.pdf"
    const void *act;

    /// Id of this timer (used to cancel timers before they expire).
    uint_t timerId;
};

template <typename T>
class TimeNodeTCompasion: public std::binary_function<T, T, bool>
{
public:
    TimeNodeTCompasion()
    { }

    bool operator() (const first_argument_type &lhs, 
        const second_argument_type &rhs) const
    {
        return lhs.timePoint > rhs.timePoint;
    }

    bool operator() (const std::shared_ptr<first_argument_type> &lhs, 
        const std::shared_ptr<second_argument_type> &rhs) const
    {
        return lhs->timePoint > rhs->timePoint;
    }
};

#endif