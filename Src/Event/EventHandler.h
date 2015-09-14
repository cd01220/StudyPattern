#if !defined(_EventHandler_h_)
#define _EventHandler_h_

#include "SystemInclude.h"
#include "TimerQueue/AbstractTimerQueue.h"

class Reactor;
/**********************class EventHandler**********************/
/* class ACE_Event_Handler */
class EventHandler
{
public:
    enum: uint_t
    {
        LoPriority = 0,
        HiPriority = 10,
        NullMask   = 0,
        ReadMask = (1 << 0),
        WriteMask = (1 << 1),
        ExceptMask = (1 << 2),
        AcceptMask = (1 << 3),
        ConnectMask = (1 << 4),
        TimerMask = (1 << 5),
        QosMask = (1 << 6),
        GroupQosMask = (1 << 7),
        SIGNAL_MASK = (1 << 8),
        AllEventsMask = (uint_t)-1,
        RweMask = ReadMask | WriteMask | ExceptMask,
    };

    virtual ~EventHandler();

    virtual std::error_code HandleTimeOut(TimePoint, const void *arg = 0);

protected:
    /// Force ACE_Event_Handler to be an abstract base class.
    EventHandler(std::shared_ptr<Reactor> reactor = nullptr, uint_t priority = LoPriority);

private:
    std::shared_ptr<Reactor> reactor;
    uint_t priority;
};

#endif