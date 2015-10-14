#include "SystemInclude.h"
#include "SystemError.h"

#include "MessageQueue/MessageQueue.h"

#include "Task/Task.h"
using namespace std;

/**********************class Task**********************/
Task::Task(Reactor *reactor)
    : TaskBase(reactor)
{
    msgQueue = make_shared<MessageQueue>(nullptr);
}

Task::~Task()
{}

error_code Task::Push(std::shared_ptr<MessageBlock> msg, Duration duration)
{
    error_code errCode;
    errCode = msgQueue->Push(msg, duration);
    if (errCode)
        cerr << "Task::Push() failed" << endl;

    return errCode;
}