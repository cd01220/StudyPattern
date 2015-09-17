#include "SystemInclude.h"
#include "SystemError.h"

#include "Reactor/Reactor.h"
#include "Task/TaskBase.h"
using namespace std;

/**********************class TaskBase**********************/
/* Origial definition: ACE_Task_Base */
TaskBase::TaskBase()
{}

TaskBase::~TaskBase()
{}

error_code TaskBase::Activate()
{
    error_code errCode;
    svcThread = std::thread(&TaskBase::ThreadRoutine, this);
    return errCode;
}

error_code TaskBase::Close(uint_t flags)
{
    return error_code();
}

error_code TaskBase::Open(void *args)
{
    return error_code();
}

error_code TaskBase::ServiceRoutine()
{
    return error_code();
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