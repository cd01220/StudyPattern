
#ifndef _State_h_
#define _State_h_

#include "Public/SystemInclude.h"

template <typename StateInterface>
class StateMachine;

/**
 * Represents a particular state machines state base class.
 *
 * @tparam StateMachineImpl The state machine implementation type.
 * @tparam StateInterface Specifies the internal interface of state implementations for the state
 *                machine.
 */
template<class StateInterface>
class StateBase: public StateInterface
{
    friend class StateMachine<StateInterface>;

public:
    typedef StateBase<StateInterface> MyType;
    typedef StateMachine<StateInterface> MyContext;

    /**
     * Called by the containing StateMachine to finalize any sub state machines.
     * @param recursive If true further sub state machines should be finalized
     *                  recursively.
     */
    virtual void FinalizeSubStateMachines(bool recursive)
    {}

    /**
     * Called by the containing StateMachine to initialize any sub state machines.
     * @param recursive If true further sub state machines should be initialized
     *                  recursively.
     */
    virtual void InitSubStateMachines(bool recursive)
    {}

    /**
     * Called by the containing state machine when the state is entered.
     * @param context A pointer to the containing state machine.
     */
    virtual void Entry()
    {}

    /**
     * Called by the containing state machine when the state is left.
     * @param context A pointer to the containing state machine.
     */
    virtual void Exit()
    {}
    
    /**
     * Called by the containing state machine after the state was entered.
     * @param context A pointer to the containing state machine.
     */
    virtual void StartDo()
    {}

    /**
     * Called by the containing state machine before the state is left.
     * @param context A pointer to the containing state machine.
     */
    virtual void EndDo() 
    {}

    /**
     * Called by the containig state machine to pickup finished asynchronous doAction threads.
     * @param context A pointer to the containing state machine.
     */
    virtual void JoinDoAction()
    {}

protected:
    /**
     * Constructor for class StateBase.
     */
    StateBase()
    {}
    /**
     * Destructor for class StateBase.
     */
    virtual ~StateBase() {}
};


#endif