
#ifndef _Demo_h_
#define _Demo_h_

#include "StateMachineLib/StateMachine.h"
#include "StateMachineLib/State.h"

class InitState;
class CapturingState;
class Task;

class IState
{
public:
    virtual std::shared_ptr<IState> HandleReceive() = 0;
};

class Task: public StateMachine<IState>
{
public:
    typedef StateMachine<IState> MyBase;
    Task(): MyBase(GetInitialState())
    {        
    }

    std::shared_ptr<StateBase<IState>> GetInitialState()
    {
        auto state = std::make_shared<InitState>();
        return std::dynamic_pointer_cast<StateBase<IState>>(state);
    }

    std::shared_ptr<IState> HandleReceive()
    {
        std::shared_ptr<IState> ret;
        while ((ret = state->HandleReceive()) != nullptr)
        {
            ChangeState(std::dynamic_pointer_cast<StateBase<IState>>(ret));
            
        }
        return nullptr;
    }
};

class InitState: public StateBase<IState>
{
public:
    typedef StateBase<IState> MyBase;
    typedef StateMachine<IState> MyContext;

    InitState()
    {}

    std::shared_ptr<IState> HandleReceive()
    {
        return std::dynamic_pointer_cast<MyBase>(std::make_shared<CapturingState>());
    }
};

class CapturingState: public StateBase<IState>
{
public:
    typedef StateBase<IState> MyBase;
    typedef StateMachine<IState> MyContext;

    CapturingState()
    {}

    std::shared_ptr<IState> HandleReceive()
    {
        return nullptr;
    }
};

#endif