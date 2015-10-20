#include "SystemInclude.h"
#include "Debug.h"

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
