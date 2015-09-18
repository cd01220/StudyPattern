#if !defined(_EventHandler_h_)
#define _EventHandler_h_

#include "SystemInclude.h"
#include "TimerQueue/AbstractTimerQueue.h"

#define MaxMaskNum 64
typedef std::bitset<MaxMaskNum> Mask;

#ifdef _WIN32
    typedef HANDLE Handle;
    #define InvalidHandleValue INVALID_HANDLE_VALUE
#else
#endif

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
        ReadMask,
        WriteMask,
        ExceptMask,
        AcceptMask,
        ConnectMask,
        TimerMask,
        QosMask,
        GroupQosMask,
        SignalMask,
    };

    virtual ~EventHandler();
    
    virtual std::error_code HandleTimeOut(TimePoint, const void *arg = 0);
    virtual Reactor* GetReactor();
    virtual Handle GetHandle() const;
    virtual void SetReactor(Reactor *reactor);

protected:
    /// Force ACE_Event_Handler to be an abstract base class.
    EventHandler(Reactor *reactor = nullptr, uint_t priority = LowPriority);

private:
    Reactor *reactor;
    uint_t  priority;
};

#endif