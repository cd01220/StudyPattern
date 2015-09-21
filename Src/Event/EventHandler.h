#if !defined(_EventHandler_h_)
#define _EventHandler_h_

#include "SystemInclude.h"
#include "TimerQueue/AbstractTimerQueue.h"

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
    enum
    {
        LowPriority = 0,
        HighPriority = 10,

        NullMask     = 0,
        ReadMask     = 1,
        WriteMask    = (1 << 1),
        ExceptMask   = (1 << 2),
        AcceptMask   = (1 << 3),
        ConnectMask  = (1 << 4),
        TimerMask    = (1 << 5),
        QosMask      = (1 << 6),
        GroupQosMask = (1 << 7),
        SignalMask   = (1 << 8),
        AllEventsMask = ReadMask | WriteMask | ExceptMask
                        | AcceptMask | ConnectMask | TimerMask 
                        | QosMask | GroupQosMask | SignalMask,
    };

    virtual ~EventHandler();
    
    virtual std::error_code HandleInput();
    virtual std::error_code HandleTimeOut(TimePoint, const void *arg = 0);

    virtual Handle GetEventHandle() const;
    virtual Reactor* GetReactor();
    virtual Handle GetIoHandle() const;
    virtual void SetReactor(Reactor *reactor);

protected:
    /// Force ACE_Event_Handler to be an abstract base class.
    EventHandler(Reactor *reactor = nullptr, uint_t priority = LowPriority);

private:
    Reactor *reactor;
    uint_t  priority;
};

#endif