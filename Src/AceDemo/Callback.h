/* -*- C++ -*- */
// $Id: CB.h 81978 2008-06-16 16:57:12Z sowayaa $

#ifndef _Callback_h_
#define _Callback_h_

#include "ace/Event_Handler.h"

#include "TimerDispatcher.h"

// Listing 1 code/ch20
class CB : public ACE_Event_Handler
{
public:
  CB ();

  // Set the timer id that is being handled by this instance.
  void setID (long timerID);

  // Get the timer id.
  long getID (void);

  // Handle the timeout.
  virtual int handle_timeout(const ACE_Time_Value &tv,
                             const void *arg = 0);

  virtual int handle_close (ACE_HANDLE handle,
                            ACE_Reactor_Mask close_mask);

private:
  long timerID_;
  int count_;
};
// Listing 1

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

#endif /*CB_H*/
