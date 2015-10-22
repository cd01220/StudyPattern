#ifndef _EventHandler_h_
#define _EventHandler_h_

#include "SystemInclude.h"
#include "TimeValue.h"  //TimePoint, Duration

#include "Event/Handle.h"

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
    
    virtual void SetIoHandle(Handle handle);
    virtual void SetMask(long mask);

protected:
    /// Force ACE_Event_Handler to be an abstract base class.
    EventHandler();

protected:
    Handle  eventHandle;
    Handle  ioHandle;
    long    mask;
    uint_t  priority;
};


#endif