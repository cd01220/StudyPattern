#include "SystemInclude.h"
#include "SystemError.h"

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

void MessageQueue::Activate()
{
    std::lock_guard<mutex> lock(c11mutex);
    this->state = Actived;
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

void MessageQueue::Deactivate(void)
{
    std::lock_guard<mutex> lock(c11mutex);
    this->state = Deactivated;
}

bool MessageQueue::IsEmpty()
{
    std::lock_guard<mutex> lock(c11mutex);
    return msgQueue.empty();
}

bool MessageQueue::IsFull()
{
    std::lock_guard<mutex> lock(c11mutex);
    return (msgQueue.size() == MaxQueueSize);
}

size_t MessageQueue::GetSize()
{
    std::lock_guard<mutex> lock(c11mutex);
    return msgQueue.size();
}

void MessageQueue::Open(std::shared_ptr<NotificationStrategy> ns)
{
    std::lock_guard<mutex> lock(c11mutex);
    notificationStrategy = ns;
    this->state = Actived;
}

error_code MessageQueue::PeekTop(std::shared_ptr<MessageBlock> &msg, Duration duration)
{
    error_code errCode;
    TimePoint until = GetCurTime() + duration;

    std::unique_lock<mutex> lock(c11mutex);
    assert(state != Deactivated);
    while (msgQueue.size() == 0)
    {
        if (cv.wait_until(lock, until) == std::cv_status::timeout)
        {
            lock.unlock();
            /* time out */
            cerr << "error, queue is empty." << endl;
            errCode = system_error_t::queue_is_empty;
            return errCode;
        }
    }

    msg = msgQueue.top();
    cv.notify_all();
    lock.unlock();

    notificationStrategy->Notify();
    return errCode;
}

error_code MessageQueue::Pop(shared_ptr<MessageBlock> &msg, Duration duration)
{
    error_code errCode;
    TimePoint until = GetCurTime() + duration;

    std::unique_lock<mutex> lock(c11mutex);
    assert(state != Deactivated);
    while (msgQueue.size() == 0)
    {
        if (cv.wait_until(lock, until) == std::cv_status::timeout)
        {
            lock.unlock();
            /* time out */
            cerr << "error, queue is empty." << endl;
            errCode = system_error_t::queue_is_empty;
            return errCode;
        }
    }

    msg = msgQueue.top();
    msgQueue.pop();
    cv.notify_all();
    lock.unlock();

    notificationStrategy->Notify();
    return errCode;
}

error_code MessageQueue::Push(shared_ptr<MessageBlock> msg, Duration duration)
{
    error_code errCode;
    TimePoint until = GetCurTime() + duration;

    std::unique_lock<std::mutex> lock(c11mutex);   
    assert(state != Deactivated); 
    while (msgQueue.size() == MaxQueueSize)
    {
        if (cv.wait_until(lock, until) == std::cv_status::timeout)
        {
            lock.unlock();
            /* time out */
            cerr << "error, queue is full." << endl;
            errCode = system_error_t::queue_is_full;
            return errCode;
        }
    }

    msgQueue.push(msg);
    cv.notify_all();
    lock.unlock(); 

    notificationStrategy->Notify();
    return errCode;
}

/**********************class MessageQueueBase**********************/
/* private member function */
void MessageQueue::DeactivateImpl(void)
{
}
