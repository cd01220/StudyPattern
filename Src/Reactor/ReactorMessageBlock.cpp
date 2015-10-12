#include "SystemInclude.h"
#include "Event/EventHandler.h"
#include "Reactor/ReactorMessageBlock.h"

using namespace std;

/**********************class NotifyMessageBlock**********************/
NotificationMessageBlock::NotificationMessageBlock(std::shared_ptr<EventHandler> handler, long mask)
    : handler(handler), mask(mask)
{
}

NotificationMessageBlock::~NotificationMessageBlock()
{
}