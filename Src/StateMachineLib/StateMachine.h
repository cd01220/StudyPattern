
#ifndef _StateMachine_h_
#define _StateMachine_h_

#include "Public/SystemInclude.h"

#include "State.h"

template <typename StateInterface>
class StateMachine: public StateInterface
{
public:
    typedef StateBase<StateInterface> StateType;
    typedef std::shared_ptr<StateType> StateTypeSharedPtr;

    StateMachine(const StateTypeSharedPtr& state): state(state)
    { }

    ~StateMachine()
    {
    }

    void ChangeState(StateTypeSharedPtr& newState)
    {
        ExitCurrentState();
        SetState(newState);
        EnterNewState();
    }

    void SetState(StateTypeSharedPtr& newState)
    {
        state = newState;
    }

    void EnterNewState()
    {
        state->Entry();
        state->StartDo();
    }

    void ExitCurrentState()
    {
        if (state != nullptr)
        {
            state->EndDo();
            state->Exit();
        }
    }

    virtual StateTypeSharedPtr GetInitialState() = 0;

protected:
    StateTypeSharedPtr state;
};

#endif