#include "SystemInclude.h"
#include "SystemError.h"

#include "Task/Task.h"
using namespace std;

/**********************class Task**********************/
Task::Task()
{
    msgQueue = make_shared<MessageQueue>();
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