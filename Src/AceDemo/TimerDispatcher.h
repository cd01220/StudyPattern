/* -*- C++ -*- */
// $Id: TimerDispatcher.h 80826 2008-03-04 14:51:23Z wotte $

/* Example:
#include "ace/Timer_Queue.h"
#include "ace/Timer_Heap.h"
#include "ace/Timer_Wheel.h"
#include "ace/Timer_Hash.h"
#include "ace/Timer_List.h"

#include "AceDemo/Callback.h"
#include "AceDemo/TimerDispatcher.h"
int main (int, ACE_TCHAR *[])
{
    ACE_Timer_Queue *timer_queue;

    ACE_NEW_RETURN(timer_queue, ACE_Timer_List, -1);

    // setup the timer queue
    Timer::instance ()->set (timer_queue);

    CB cb[10];
    long args[10];
    for (long i = 0; i < 10 ; i++)
    {
        ACE_Time_Value const timeout (i);
        long timerID = Timer::instance ()->schedule(&cb[i],
            &args[i],
            timer_queue->gettimeofday () + ACE_Time_Value(5),
            timeout);

        // Set the timerID state variable of the handler.
        cb[i].setID (timerID);

        // Implicitly send the handler it's timer id.
        args[i] = timerID;
    }

    // "run" the timer.
    Timer::instance ()->wait_for_event ();
}
*/

#ifndef _TimerDispatcher_h_
#define _TimerDispatcher_h_

#include "ace/Event_Handler.h"
#include "ace/Singleton.h"
#include "ace/Synch.h"  // needed for ACE_Event
#include "ace/Timer_Queue.h"

// Listing 1 code/ch20
class Timer_Dispatcher
{
public:
  void wait_for_event (void);

  long schedule (ACE_Event_Handler *cb,
                 void *arg,
                 const ACE_Time_Value &abs_time,
                 const ACE_Time_Value &interval);

  int cancel (ACE_Event_Handler *cb,
              int dont_call_handle_close = 1);

  int reset_interval (long timer_id,
                      const ACE_Time_Value &interval);

  void set (ACE_Timer_Queue *timer_queue);

private:
  ACE_Timer_Queue *timer_queue_;
  ACE_Event timer_;
};

typedef ACE_Singleton<Timer_Dispatcher, ACE_Null_Mutex> Timer;
// Listing 1

#endif /*TIMER_DISPATCHER_H*/

