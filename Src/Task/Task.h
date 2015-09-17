#ifndef _Task_h_
#define _Task_h_

#include "MessageQueue/MessageBlock.h"
#include "MessageQueue/MessageQueue.h"

#include "Task/TaskBase.h"
/**********************class Task**********************/
/* class ACE_Task */
class Task: public TaskBase
{
public:
    Task();
    virtual ~Task();

    std::error_code Push(std::shared_ptr<MessageBlock> msg, Duration duration);

protected:
    std::shared_ptr<MessageQueue> msgQueue;
};

#endif