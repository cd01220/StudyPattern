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
        ReadMask     = FD_READ,
        WriteMask    = FD_WRITE,
        ExceptMask   = FD_OOB,
        AcceptMask   = FD_ACCEPT,
        ConnectMask  = FD_CONNECT,
        TimerMask    = FD_CLOSE,
        QosMask      = FD_QOS,
        GroupQosMask = FD_GROUP_QOS,
        AllEventsMask = ReadMask | WriteMask | ExceptMask
                        | AcceptMask | ConnectMask | TimerMask 
                        | QosMask | GroupQosMask,
    };

    virtual ~EventHandler();
    
    virtual std::error_code HandleException();
    virtual std::error_code HandleGroupQos();
    virtual std::error_code HandleInput();
    virtual std::error_code HandleOutput();
    virtual std::error_code HandleQos();
    virtual std::error_code HandleTimeOut(TimePoint, const void *arg = 0);

    virtual Handle GetEventHandle() const;
    virtual Reactor* GetReactor();
    virtual Handle GetIoHandle() const;
    virtual long GetMask() const;

    virtual void SetReactor(Reactor *reactor);
    virtual void SetMask(long mask);

protected:
    /// Force ACE_Event_Handler to be an abstract base class.
    EventHandler(Reactor *reactor = nullptr, uint_t priority = LowPriority);

private:
    Reactor *reactor;
    uint_t  priority;
    long    mask;
};

#endif