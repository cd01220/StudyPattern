#if !defined(_TimeList_h_)
#define _TimeList_h_

#include "TimeListT.h"

/**********************class TimeList**********************/
/* class ACE_Timer_List_T */
typedef TimerListT<EventHandler, EventHandlerHandleTimeoutUpcall> TimeList;

#endif