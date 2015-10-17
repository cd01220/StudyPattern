#include "SystemInclude.h"

#include "MessageQueue/MessageBlock.h"
#include "MessageQueue/MessageQueue.h"

#include "Task/Task.h"
using namespace std;

/**********************class Task**********************/
Task::Task(Reactor *reactor)
    : TaskBase(reactor)
{
    msgQueue = make_shared<MessageQueue>();
}

Task::~Task()
{} 

bool Task::Push(std::shared_ptr<MessageBlock> msg, Duration duration)
{
    if (msgQueue->Push(msg, duration))
    {
        cerr << "Task::Push() failed" << endl;
        return false;
    }

    return true;
}