#include "SystemInclude.h"

#include "StateMachine.h"

using namespace std;

/**********************class Task**********************/
Task::Task(): state(new InitState)
{
    myThread = thread(bind(&Task::ThreadMain, this));
}

State* Task::Receive()
{
    MsgType *msg = new MsgType(PacketMsg, nullptr);
    msgQueue.Add(msg);
    return nullptr;
}

void Task::ChangeState(State* newState)
{
    /*
        1 Send message to ThreadMain
     */
    MsgType *msg = new MsgType(StateChangeMsg, newState);
    msgQueue.Add(msg);
}

void Task::ThreadMain()
{
    while (true)
    {
        shared_ptr<MsgType> msg(msgQueue.Remove());
        State* newState;
        
        switch (msg->first)
        {
        case PacketMsg:
            while ((newState = state->Receive()) != nullptr)
            {
                state.reset(newState);
            }
            break;

        case StateChangeMsg:
            newState = (State*)msg->second;
            state.reset(newState);
            break;
        }
    }
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
