#include "Reactor/ReactorMessageBlock.h"

/**********************class NotifyMessageBlock**********************/
NotificationMessageBlock::NotificationMessageBlock(std::shared_ptr<EventHandler> handler, long mask)
    : handler(handler), mask(mask)
{
}