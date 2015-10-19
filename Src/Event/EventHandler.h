#if !defined(_EventHandler_h_)
#define _EventHandler_h_

#include "SystemInclude.h"
#include "TimeValue.h"  //TimePoint, Duration

#ifdef _WIN32
    typedef HANDLE Handle;
    #define InvalidHandleValue INVALID_HANDLE_VALUE
        
    struct SignalInfo
    {
        SignalInfo (Handle handle);

        /// Win32 HANDLE that has become signaled.
        Handle handle;
    };
#else
#endif

class Reactor;
/**********************class EventHandler**********************/
/* class ACE_Event_Handler */
class EventHandler: public std::enable_shared_from_this<EventHandler>
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
    
    virtual bool HandleClose();
    virtual bool HandleException();
    virtual bool HandleGroupQos();
    virtual bool HandleInput();
    virtual bool HandleOutput();
    virtual bool HandleQos();
    virtual bool HandleSignal();
    virtual bool HandleTimeOut(TimePoint, const void *arg = 0);

    virtual Handle GetEventHandle() const;
    virtual Handle GetIoHandle() const;
    virtual long GetMask() const;
    virtual Reactor* GetReactor();
    
    virtual void SetIoHandle(Handle handle);
    virtual void SetMask(long mask);
    virtual void SetReactor(Reactor *reactor);

protected:
    /// Force ACE_Event_Handler to be an abstract base class.
    EventHandler(Reactor *reactor = nullptr, uint_t priority = LowPriority);

protected:
    Handle  eventHandle;
    Handle  ioHandle;
    long    mask;
    uint_t  priority;
    Reactor *reactor;
};


#endif