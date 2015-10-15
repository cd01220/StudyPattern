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
MessageQueue::MessageQueue(shared_ptr<NotificationStrategy> ns)
{
    Open(ns);
}

MessageQueue::~MessageQueue()
{
    Close();
}

void MessageQueue::Activate()
{
    lock_guard<mutex> lock(c11mutex);
    this->state = Actived;
}

void MessageQueue::Close(void)
{
    lock_guard<mutex> lock(c11mutex);
    DeactivateImpl();
    while(!msgQueue.empty())
    {
        msgQueue.pop();
    }
}

void MessageQueue::Deactivate(void)
{
    lock_guard<mutex> lock(c11mutex);
    this->state = Deactivated;
}

bool MessageQueue::IsEmpty()
{
    lock_guard<mutex> lock(c11mutex);
    return msgQueue.empty();
}

bool MessageQueue::IsFull()
{
    lock_guard<mutex> lock(c11mutex);
    return (msgQueue.size() == MaxQueueSize);
}

size_t MessageQueue::GetSize()
{
    lock_guard<mutex> lock(c11mutex);
    return msgQueue.size();
}

void MessageQueue::Open(shared_ptr<NotificationStrategy> ns)
{
    lock_guard<mutex> lock(c11mutex);
    notificationStrategy = ns;
    this->state = Actived;
}

void MessageQueue::SetNotificationStrategy(shared_ptr<NotificationStrategy> ns)
{
    lock_guard<mutex> lock(c11mutex);
    notificationStrategy = ns;
    this->state = Actived;
}

error_code MessageQueue::PeekTop(shared_ptr<MessageBlock> &msg, Duration duration)
{
    error_code errCode;
    TimePoint until = GetCurTime() + duration;

    unique_lock<mutex> lock(c11mutex);
    assert(state != Deactivated);
    while (msgQueue.size() == 0)
    {
        if (cv.wait_until(lock, until) == cv_status::timeout)
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
    
    if (notificationStrategy != nullptr)
        notificationStrategy->Notify();
    return errCode;
}

error_code MessageQueue::Pop(shared_ptr<MessageBlock> &msg, Duration duration)
{
    error_code errCode;
    TimePoint until = GetCurTime() + duration;

    unique_lock<mutex> lock(c11mutex);
    assert(state != Deactivated);
    while (msgQueue.size() == 0)
    {
        if (cv.wait_until(lock, until) == cv_status::timeout)
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
    
    if (notificationStrategy != nullptr)
        notificationStrategy->Notify();
    return errCode;
}

error_code MessageQueue::Push(shared_ptr<MessageBlock> msg, Duration duration)
{
    error_code errCode;
    TimePoint until = GetCurTime() + duration;

    unique_lock<mutex> lock(c11mutex);   
    assert(state != Deactivated); 
    while (msgQueue.size() == MaxQueueSize)
    {
        if (cv.wait_until(lock, until) == cv_status::timeout)
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

    if (notificationStrategy != nullptr)
        notificationStrategy->Notify();
    return errCode;
}

/**********************class MessageQueueBase**********************/
/* private member function */
void MessageQueue::DeactivateImpl(void)
{
}
