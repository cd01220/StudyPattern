#include "SystemInclude.h"

#include "Event/Event.h"
using namespace std;

/**********************class Event**********************/
Event::~Event()
{
}

bool Event::Signal()
{
    lock_guard<mutex> lock(theMutex);
    isReady = true;
    theCv.notify_one();

    return false;
}

bool Event::Wait()
{
    unique_lock<mutex> lock(theMutex);
    while(!isReady)
    {
        theCv.wait(lock);
    }
    isReady = false;
    lock.unlock();

    return true;
}

bool Event::Wait(Duration duration)
{
    unique_lock<mutex> lock(theMutex);
    while(!isReady)
    {
        if (theCv.wait_for(lock, duration) == cv_status::timeout)
        {
            lock.unlock();
            return false;
        }
    }
    isReady = false;
    lock.unlock();

    return true;
}

/**********************class Event**********************/
//protected member function
Event::Event()
{
    isReady = false;
}