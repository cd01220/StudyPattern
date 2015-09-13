#if !defined(_TimeValue_h_)
#define _TimeValue_h_

#include "SystemInclude.h"

/**********************class TimeValue**********************/
/* ACE_Time_Value */
typedef std::chrono::system_clock::time_point TimePoint;
typedef std::chrono::milliseconds TimeInterval;

#endif