#ifndef _MessageQueue_h_
#define _MessageQueue_h_

#include "SystemInclude.h"

#include "TimerQueue/TimeValue.h"
#include "MessageQueue/MessageBlock.h"

/**********************class NotificationStrategy**********************/
/**
 * @class ACE_Notification_Strategy
 *
 * @brief Abstract class used for notifying an interested party
 *
 * A vehicle for extending the behavior of ACE_Message_Queue wrt
 * notification *without subclassing*.  Thus, it's an example of
 * the Bridge/Strategy patterns.
 */
/* ACE_Notification_Strategy */ 
class NotificationStrategy
{
public:
    virtual std::error_code Notify() = 0;
};

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
    MessageQueue(std::shared_ptr<NotificationStrategy> ns = nullptr);
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

#if 0
template<typename MsgType>
class MessageQueue
{        
public:
   void Add(MsgType *pMsg)
   {
      // Insert the element at the end of the queue
      std::lock_guard<mutex> lock(myMutext);
      msgQueue.push(pMsg);
      myCv.notify_one();
   }

   MsgType *Remove()
   {
      MsgType *msg = nullptr;
      
      std::unique_lock<std::mutex> lock(myMutext);
      // Check if the message queue is not empty
      while(msgQueue.empty())
      {
          myCv.wait(lock);
      }
      // std::queue is thread safety, so we unlock befor queue operation.
      lock.unlock();  

      // Queue is not empty so get a pointer to the
      // first message in the queue
      msg = msgQueue.front();

      // Now remove the pointer from the message queue
      msgQueue.pop();
      
      return msg;
   }
   
   int GetLength() const
   {
      return msgQueue.size();
   }

private:
    typedef std::queue<MsgType *, std::list<MsgType *> > MsgQueType;  
    MsgQueType msgQueue;

    std::mutex  myMutext;
    std::condition_variable myCv;
};
#endif

/* Example:
void ThreadMain(MessageQueue<int> *msgQueue)
{
    while (true)
    {
        int* msg;
        
        msg = msgQueue->Remove();
        cout << *msg << endl;
    }
}

int main()
{   
    MessageQueue<int> msgQueue;

    thread thread(bind(ThreadMain, &msgQueue)); 

    int a = 10;
    
    while (true)
    {
        msgQueue.Add(&a);
        Sleep(100);
    }
	return 0;
}

*/

#endif
