#ifndef _Demo_h_
#define _Demo_h_

#if 0
#include "MessageQueue/MessageQueue.h"

/* Example:
#include "StateMachine/Demo.h"
using namespace std;

int main()
{   
    Task task;
    task.Receive();

    while (true)
    {
        Sleep(100);
    }

	return 0;
}
*/

class State 
{
public:
    virtual State* Receive() = 0;
};

/**********************class Task**********************/
class Task
{
    enum: uint32_t  { PacketMsg, StateChangeMsg };
    typedef std::pair<uint32_t, void*> MsgType;

public:
    Task();
    void ChangeState(State* newState);
    State* Receive();     

private:
    void ThreadMain();

private:
    std::thread myThread;
    std::shared_ptr<State> state;
    MessageQueue<MsgType> msgQueue;
};

/**********************class InitState**********************/
class InitState: public State
{
public:
    InitState();

    State* Receive();
};

/**********************class CapturingState**********************/
class CapturingState: public State
{
public:
    CapturingState();
    
    State* Receive();

private:
    int dictionary;
};

#endif
#endif