#ifndef _Task_h_
#define _Task_h_

#include "Task/TaskBase.h"

class MessageQueue;
/**********************class Task**********************/
/* class ACE_Task */
class Task: public TaskBase
{
public:
    Task();
    virtual ~Task();

    MessageQueue& GetMessageQueue();

protected:
    std::shared_ptr<MessageQueue> msgQueue;
};

#endif