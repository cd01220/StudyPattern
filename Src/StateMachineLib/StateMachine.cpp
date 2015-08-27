#include "SystemInclude.h"

#include "StateMachine.h"

/**********************class StateMachine**********************/
StateMachine::StateMachine(State *state): state(state)
{  }

StateMachine::~StateMachine()
{
    ExitCurrentState();
}

void StateMachine::ChangeState(State* newState)
{
    ExitCurrentState();
    SetState(newState);
    EnterNewState();
}

void StateMachine::SetState(State* newState)
{
    state.reset(newState);
}

void StateMachine::EnterNewState()
{
    state->Start();
}

void StateMachine::ExitCurrentState()
{
    state->End();
}