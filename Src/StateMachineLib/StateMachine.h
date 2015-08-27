
#ifndef _StateMachine_h_
#define _StateMachine_h_

#include "SystemInclude.h"

#include "State.h"

/**********************class StateMachine**********************/
class StateMachine: public Interface
{
public:
    StateMachine(State *state);
    ~StateMachine();

    void ChangeState(State* newState);
    void SetState(State* newState);
    void EnterNewState();
    void ExitCurrentState();

protected:
    std::shared_ptr<State> state;
};

#endif