#include "SystemInclude.h"
#include "Event/EventHandler.h"
#include "MessageQueue/MessageBlock.h"

/**********************class NotificationMessageBlock**********************/
//defined by liuhao.
class NotificationMessageBlock: public MessageBlock
{
public:
    NotificationMessageBlock(std::shared_ptr<EventHandler> handler, long mask);

public:
    std::shared_ptr<EventHandler> handler;
    long mask;
};