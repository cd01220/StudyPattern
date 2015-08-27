#include "SystemInclude.h"

#include "State.h"

using namespace std;

ActiveState::ActiveState()
    : myThread(std::thread(bind(&ActiveState::ThreadMain, this))),
      isReady(false), isExiting(false)
{
}

ActiveState::~ActiveState()
{
}

void ActiveState::Start()
{
    // send message to the worker thread
    {
    lock_guard<mutex> lock(myMutext);
    isReady = true;
    }
    myCv.notify_one();
}

void ActiveState::End()
{
    isExiting = true;
    myThread.join();
}

void ActiveState::ThreadMain()
{
    unique_lock<std::mutex> lock(myMutext);
    while(!isReady)
    {
        myCv.wait(lock);
    }
    lock.unlock();

    ThreadRoutine();
}