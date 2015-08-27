
#ifndef _Demo_h_
#define _Demo_h_

#include "StateMachineLib/State.h"
#include "StateMachineLib/StateMachine.h"

/* Example:
#include "StateMachine/Demo.h"
using namespace std;

int main()
{   
    Task task;
    task.Receive();

	return 0;
}
*/

/**********************class Task**********************/
class Task: public StateMachine
{
public:
    Task();
    State* Receive();
};

/**********************class InitState**********************/
class InitState: public State
{
public:
    InitState();
    State* Receive();
};

/**********************class CapturingState**********************/
class CapturingState: public ActiveState
{
public:
    CapturingState();
    State* Receive();
    void ThreadRoutine();
};

#endif