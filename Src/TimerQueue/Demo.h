#ifndef _Demo_h_
#define _Demo_h_

#include "SystemInclude.h"

using std::chrono::system_clock;

#include "Reactor/EventHanlder.h"
#include "TimerQueueFwd.h"

class Timer_Dispatcher
{
public:
  void WaitForEvent(void)
  {
      while (true)
      {
          system_clock::time_point maxTv = system_clock::now();
      }
  }

  long Schedule (EventHandler *handler,
                 void *arg,
                 const std::chrono::milliseconds &absTime,
                 const std::chrono::milliseconds &interval);

  void Set (TimerQueue *timerQueue);

private:
  TimerQueue *timerQueue;
};

#endif