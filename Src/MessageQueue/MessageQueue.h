#ifndef _MessageQueue_h_
#define _MessageQueue_h_

#include "SystemInclude.h"

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
