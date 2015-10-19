#ifndef _Event_h_
#define _Event_h_

#include "CopyDisabled.h"
#include "TimeValue.h"

/**********************class Event**********************/
class Event: public CopyDisabled
{
public:
    virtual ~Event();

    bool Signal();
    bool Wait();
    bool Wait(Duration duration);

protected:
    Event();

protected:
    bool isReady;

private:
    std::mutex  theMutex;
    std::condition_variable theCv;
};

#endif