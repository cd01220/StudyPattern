#include "SystemInclude.h"
#include "SystemError.h"
#include "Debug.h"

#include "MessageQueue/NotificationStrategy.h" //NotificationStrategy
#include "Reactor/NotificationMessageBlock.h"
#include "Reactor/WfmoReactorNotify.h"
using namespace std;

/**********************class WfmoReactorNotify**********************/
WfmoReactorNotify::WfmoReactorNotify(shared_ptr<NotificationStrategy> msgQueueNs)
    : msgQueue(msgQueueNs)
{
}

WfmoReactorNotify::~WfmoReactorNotify()
{
}

error_code WfmoReactorNotify::HandleSignal(int signalNum, SignalInfo SigInfor)
{
    return error_code();
}

error_code WfmoReactorNotify::Notify(shared_ptr<EventHandler> handler, long mask)
{
    shared_ptr<MessageBlock> block = make_shared<NotificationMessageBlock>(NotificationMessageBlock(handler, mask));

    return msgQueue.Push(block, Duration::zero());
}