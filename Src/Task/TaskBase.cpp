#include "SystemInclude.h"

#include "Task/TaskBase.h"
using namespace std;

/**********************class TaskBase**********************/
/* Origial definition: ACE_Task_Base */
TaskBase::TaskBase()
{}

TaskBase::~TaskBase()
{}

bool TaskBase::Activate()
{
    svcThread = std::thread(&TaskBase::ThreadRoutine, this);
    return true;
}

bool TaskBase::Close(uint_t flags)
{
    return true;
}

bool TaskBase::Open(void *args)
{
    return true;
}

bool TaskBase::ServiceRoutine()
{
    return true;
}

void TaskBase::Wait()
{
    if (svcThread.joinable())
        svcThread.join();
}

/**********************class TaskBase**********************/
/* private member function */
void TaskBase::ThreadRoutine()
{
    ServiceRoutine();
}