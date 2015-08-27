
#ifndef _State_h_
#define _State_h_

#include "SystemInclude.h"
#include "Interface.h"

class StateMachine;

/**
 * Represents a particular state machines state base class.
 *
 * @tparam StateMachineImpl The state machine implementation type.
 * @tparam Interface Specifies the internal interface of state implementations for the state
 *                machine.
 */
class State: public Interface
{
public:    
    /**
     * Constructor for class State.
     */
    State()
    {}
    /**
     * Destructor for class State.
     */
    virtual ~State() {}
    
    /**
     * Called by the containing state machine after the state was entered.
     * @param context A pointer to the containing state machine.
     */
    virtual void Start()
    {}

    /**
     * Called by the containing state machine before the state is left.
     * @param context A pointer to the containing state machine.
     */
    virtual void End() 
    {}
};

class ActiveState: public State
{
public:
    ActiveState();
    virtual ~ActiveState();

    virtual void Start();
    virtual void End();

    virtual void ThreadRoutine() = 0;

protected:
    bool isExiting;

private:
    std::thread myThread;
    std::mutex  myMutext;
    std::condition_variable myCv;
    bool isReady;

    void ThreadMain();
};

#endif