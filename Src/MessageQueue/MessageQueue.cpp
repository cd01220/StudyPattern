#include "SystemInclude.h"

#include "MessageQueue/MessageQueue.h"

using namespace std;

/**********************class MessageQueueBase**********************/
MessageQueueBase::MessageQueueBase()
{}

MessageQueueBase::~MessageQueueBase()
{}


/**********************class MessageQueueBase**********************/
MessageQueue::MessageQueue(std::shared_ptr<NotificationStrategy> ns)
{
    Open(ns);
}

MessageQueue::~MessageQueue()
{
    Close();
}

void MessageQueue::Close(void)
{
    std::lock_guard<mutex> lock(c11mutex);
    DeactivateImpl();
    while(!msgQueue.empty())
    {
        msgQueue.pop();
    }
}

void MessageQueue::Open(std::shared_ptr<NotificationStrategy> ns)
{
    notificationStrategy = ns;
}

std::shared_ptr<MessageBlock> MessageQueue::Pop(Duration duration)
{
    std::lock_guard<mutex> lock(c11mutex);
    return nullptr;
}

void MessageQueue::Push(std::shared_ptr<MessageBlock>, Duration duration)
{
    std::shared_ptr<NotificationStrategy> ns;
    std::unique_lock<std::mutex> lock(c11mutex);
    assert(state != Deactivated);
    if (!cv.wait_for(lock, duration, [this](){return msgQueue.size() == MaxQueueSize;}))
    {
        /* time out */
        cerr << "error, queue is full." << endl;
        return;
    }
    ns = notificationStrategy;
    lock.unlock(); 

    ns->Notify();
}

/**********************class MessageQueueBase**********************/
/* private member function */
void MessageQueue::DeactivateImpl(void)
{
}