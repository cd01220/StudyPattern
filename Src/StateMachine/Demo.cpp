#include "SystemInclude.h"

#include "Demo.h"

using namespace std;

/**********************class Task**********************/
Task::Task(): StateMachine(new InitState)
{}

State* Task::Receive()
{
    State* newState;
    while ((newState = dynamic_cast<State*>(state->Receive())) != nullptr)
    {        
        ChangeState(newState);            
    }
    return nullptr;
}

/**********************class InitState**********************/
InitState::InitState()
{}

State* InitState::Receive()
{
    return (new CapturingState);
}

/**********************class CapturingState**********************/
CapturingState::CapturingState()
{}

State* CapturingState::Receive()
{
    return nullptr;
}

void CapturingState::ThreadRoutine()
{
    cout << "do nothing" << endl;
}