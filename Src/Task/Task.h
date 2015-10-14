#ifndef _Task_h_
#define _Task_h_

#include "Task/TaskBase.h"

class MessageBlock;
class MessageQueue;
/**********************class Task**********************/
/* class ACE_Task */
class Task: public TaskBase
{
public:
    Task(Reactor *reactor);
    virtual ~Task();

    std::error_code Push(std::shared_ptr<MessageBlock> msg, Duration duration);

protected:
    std::shared_ptr<MessageQueue> msgQueue;
};

#endif