#if !defined(_EventHandler_h_)
#define _EventHandler_h_

#include "SystemInclude.h"
#include "TimerQueue/AbstractTimerQueue.h"

#define MaxMaskNum 32
typedef void* Handle;
#define InvalidHandleValue (Handle)(-1);

class Reactor;
/**********************class EventHandler**********************/
/* class ACE_Event_Handler */
class EventHandler
{
public:
    enum: uint32_t
    {
        LowPriority = 0,
        HighPriority = 10,
        NullMask   = 0,
        ReadMask = (1 << 0),
        WriteMask = (1 << 1),
        ExceptMask = (1 << 2),
        AcceptMask = (1 << 3),
        ConnectMask = (1 << 4),
        TimerMask = (1 << 5),
        QosMask = (1 << 6),
        GroupQosMask = (1 << 7),
        SignalMask = (1 << 8),
        AllEventsMask = (uint32_t)-1,
        RweMask = ReadMask | WriteMask | ExceptMask,
    };

    virtual ~EventHandler();
    
    virtual std::error_code HandleTimeOut(TimePoint, const void *arg = 0);
    virtual Reactor* GetReactor();
    virtual Handle GetHandle();
    virtual void SetReactor(Reactor *reactor);

protected:
    /// Force ACE_Event_Handler to be an abstract base class.
    EventHandler(Reactor *reactor = nullptr, uint_t priority = LowPriority);

private:
    Reactor *reactor;
    uint_t  priority;
};

#endif