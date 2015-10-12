#include "SystemInclude.h"
#include "MessageQueue/MessageBlock.h"

class EventHandler;
/**********************class NotificationMessageBlock**********************/
//defined by liuhao.
class NotificationMessageBlock: public MessageBlock
{
public:
    NotificationMessageBlock(std::shared_ptr<EventHandler> handler, long mask);
    virtual ~NotificationMessageBlock();

public:
    std::shared_ptr<EventHandler> handler;
    long mask;
};