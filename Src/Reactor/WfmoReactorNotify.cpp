#include "SystemInclude.h"
#include "Debug.h"

#include "TimerQueue/TimerQueue.h"  //TimerQueue
#include "MessageQueue/NotificationStrategy.h" //NotificationStrategy
#include "MessageQueue/MessageQueue.h" //MessageQueue
#include "Reactor/ReactorImpl.h"               //
#include "Reactor/NotificationMessageBlock.h"

#include "Reactor/WfmoReactorNotify.h"
using namespace std;

/**********************class WfmoReactorNotify**********************/
WfmoReactorNotify::WfmoReactorNotify()
{
    msgQueue = make_shared<MessageQueue>();
}

WfmoReactorNotify::~WfmoReactorNotify()
{
}

bool WfmoReactorNotify::HandleSignal()
{
    dbgstrm << "Start" << endl;

    bool result = true;
    shared_ptr<MessageBlock> block;
    while (msgQueue->Pop(block, Duration::zero()))
    {
        shared_ptr<NotificationMessageBlock> msg = dynamic_pointer_cast<NotificationMessageBlock>(block);
        switch(msg->mask)
        {
            case ReadMask:
            case AcceptMask:
                result = msg->handler->HandleInput();
                break;
            case WriteMask:
                result = msg->handler->HandleOutput();
                break;
            case ExceptMask:
                result = msg->handler->HandleException();
                break;
            case QosMask:
                result = msg->handler->HandleQos();
                break;
            case GroupQosMask:
                result = msg->handler->HandleGroupQos();
                break;
        }
    }

    return result;
}

bool WfmoReactorNotify::Notify(shared_ptr<EventHandler> handler, long mask)
{
    shared_ptr<MessageBlock> block = make_shared<NotificationMessageBlock>(NotificationMessageBlock(handler, mask));

    if (!msgQueue->Push(block, Duration::zero()))
        return false;

    if (!SetEvent(this->eventHandle))
    {
        errstrm << "SetEvent() failed. " << endl;
        return false;
    }

    return true;
}

bool WfmoReactorNotify::Open(ReactorImpl *reactor, std::shared_ptr<TimerQueue> timerQueue)
{
    this->timerQueue = timerQueue;
    return reactor->RegisterHandler(shared_from_this());
}