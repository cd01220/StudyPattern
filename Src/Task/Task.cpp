#include "SystemInclude.h"
#include "Debug.h"

#include "MessageQueue/MessageQueue.h"

#include "Task/Task.h"
using namespace std;

/**********************class Task**********************/
Task::Task()
{
    msgQueue = make_shared<MessageQueue>();
}

Task::~Task()
{} 

MessageQueue& Task::GetMessageQueue()
{
    return *msgQueue;
}
