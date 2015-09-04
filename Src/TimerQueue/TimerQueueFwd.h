#ifndef _TimerQueueFwd_h_
#define _TimerQueueFwd_h_


template<typename T>
class AbstractTimerQueue
{
};

class EventHandler;

typedef AbstractTimerQueue<EventHandler> TimerQueue;

#endif