#include "SystemInclude.h"
#include "SystemError.h"
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

error_code WfmoReactorNotify::HandleSignal(int signalNum, SignalInfo SigInfor)
{
    return error_code();
}

bool WfmoReactorNotify::Notify(shared_ptr<EventHandler> handler, long mask)
{
    shared_ptr<MessageBlock> block = make_shared<NotificationMessageBlock>(NotificationMessageBlock(handler, mask));

    return msgQueue->Push(block, Duration::zero());
}

bool WfmoReactorNotify::Open(ReactorImpl *reactor, std::shared_ptr<TimerQueue> timerQueue)
{
    this->timerQueue = timerQueue;
    reactor->RegisterHandler(shared_from_this());
    return true;
}