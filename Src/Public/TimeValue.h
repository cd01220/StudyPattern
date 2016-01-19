#ifndef _TimeValue_h_
#define _TimeValue_h_

#include "SystemInclude.h"

/**********************class TimeValue**********************/
/* ACE_Time_Value */
typedef std::chrono::system_clock::time_point TimePoint;
typedef std::chrono::milliseconds Duration;

inline TimePoint GetCurTime()
{
    return std::chrono::system_clock::now();
}

class TimeCountDown
{
public:
    TimeCountDown(Duration duration)
        : duration(duration)
    {
        timePoint = GetCurTime();
    }

    ~TimeCountDown()
    {}

    Duration GetRemainingTime()
    {
        TimePoint nowTimePoint = GetCurTime();
        duration = duration - std::chrono::duration_cast<Duration>(nowTimePoint - timePoint);    
        if (duration < Duration::zero())
            duration = Duration::zero();
        timePoint = nowTimePoint;
        return duration;
    }

private:
    Duration duration;
    TimePoint timePoint;
};

#endif