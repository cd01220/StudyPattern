#ifndef _MessageQueue_h_
#define _MessageQueue_h_

#include "SystemInclude.h"

#include "TimerQueue/TimeValue.h"
#include "MessageQueue/MessageBlock.h"
#include "MessageQueue/NotificationStrategy.h"

/**********************class MessageQueueBase**********************/
/* ACE_Message_Queue_Base */
class MessageQueueBase
{
public:
    enum: uint_t
    {
        MaxQueueSize = 1024,

        /// Message queue is active and processing normally
        Actived     = 1,
        /// Queue is deactivated; no enqueue or dequeue operations allowed.
        Deactivated, 
        /// Message queue was pulsed; enqueue and dequeue may proceed normally.
        Pulsed
    };
    MessageQueueBase();
    virtual ~MessageQueueBase();
        
    virtual void Activate() = 0;
    // Close down the message queue and release all resources.
    virtual void Close(void) = 0;
    // Inform the dispatching thread that it should terminate.
    virtual void Deactivate (void) = 0;

    virtual bool IsEmpty() = 0;
    virtual bool IsFull() = 0;

    virtual size_t GetSize() = 0;

    /**
    * Retrieve the first ACE_Message_Block without removing it.  Note
    * that @a timeout uses <{absolute}> time rather than <{relative}>
    * time.  If the @a timeout elapses without receiving a message -1 is
    * returned and @c errno is set to @c EWOULDBLOCK.  If the queue is
    * deactivated -1 is returned and @c errno is set to @c ESHUTDOWN.
    * Otherwise, returns -1 on failure, else the number of items still
    * on the queue.
    * original definition: peek_dequeue_head()
    */
    virtual std::error_code PeekTop(std::shared_ptr<MessageBlock> &msg, Duration duration) = 0;

    virtual std::error_code Pop(std::shared_ptr<MessageBlock> &msg, Duration duration) = 0;
    virtual std::error_code Push(std::shared_ptr<MessageBlock> msg, Duration duration) = 0;

protected:
    uint_t state;
};

/**********************class MessageQueue**********************/
/* class class ACE_Message_Queue */
class MessageQueue: public MessageQueueBase
{
public:
    MessageQueue(std::shared_ptr<NotificationStrategy> ns);
    virtual ~MessageQueue();    
    
    virtual void Activate();
    // Close down the message queue and release all resources.
    virtual void Close(void);
    // Inform the dispatching thread that it should terminate.
    virtual void Deactivate(void);

    virtual bool IsEmpty();
    virtual bool IsFull();

    virtual size_t GetSize();
    virtual void Open(std::shared_ptr<NotificationStrategy> ns = nullptr);
    /* ACE_Message_Queue::notification_strategy(ACE_Notification_Strategy *s) */
    virtual void SetNotificationStrategy(std::shared_ptr<NotificationStrategy> ns);

    /**
    * Retrieve the first ACE_Message_Block without removing it.  Note
    * that @a timeout uses <{absolute}> time rather than <{relative}>
    * time.  If the @a timeout elapses without receiving a message -1 is
    * returned and @c errno is set to @c EWOULDBLOCK.  If the queue is
    * deactivated -1 is returned and @c errno is set to @c ESHUTDOWN.
    * Otherwise, returns -1 on failure, else the number of items still
    * on the queue.
    * original definition: peek_dequeue_head()
    */
    virtual std::error_code PeekTop(std::shared_ptr<MessageBlock> &msg, Duration duration);

    virtual std::error_code Pop(std::shared_ptr<MessageBlock> &msg, Duration duration);
    /* Enqueue an ACE_Message_Block into the queue in accordance with
     * the ACE_Message_Block's priority (0 is lowest priority).  FIFO
     * order is maintained when messages of the same priority are
     * inserted consecutively.
    ACE_Message_Queue::enqueue_prio (ACE_Message_Block *new_item, ACE_Time_Value *timeout)
    */
    virtual std::error_code Push(std::shared_ptr<MessageBlock> msg, Duration duration);

private:
    void DeactivateImpl(void);

private:
    std::priority_queue<std::shared_ptr<MessageBlock>> msgQueue;
    std::shared_ptr<NotificationStrategy> notificationStrategy;

    std::mutex  c11mutex;
    std::condition_variable cv;
};

#endif
