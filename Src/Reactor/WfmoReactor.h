#ifndef _WfmoReactor_h_
#define _WfmoReactor_h_

#include "Reactor/ReactorImpl.h"  //class WfmoReactor: public ReactorImpl

class TimerQueue;

/**********************class WfmoReactorHandlerRepository**********************/
/* ACE_WFMO_Reactor_Handler_Repository */
class WfmoReactorHandlerRepository
{
public:
    typedef std::map<Handle, std::shared_ptr<EventHandler>>::iterator iterator;
    WfmoReactorHandlerRepository();
    ~WfmoReactorHandlerRepository();

    iterator begin();
    iterator end();

    std::shared_ptr<EventHandler> Find(Handle handle);
    Handle* GetEventHandles();
    size_t GetSize();

    void Insert(std::shared_ptr<EventHandler>);

private:
    Handle handles[MAXIMUM_WAIT_OBJECTS];
    std::map<Handle, std::shared_ptr<EventHandler>> repository;
};

class WfmoReactorNotify;
/**********************class WfmoReactor**********************/
/* class ACE_WFMO_Reactor (WFMO: Wait For Multiple Objects) */
class WfmoReactor: public ReactorImpl
{
public:
    WfmoReactor();
    WfmoReactor(std::shared_ptr<WfmoReactorNotify> notifyHandler, 
                std::shared_ptr<TimerQueue> timerQueue);
    ~WfmoReactor();

    bool IsActived();

    /* int ACE_WFMO_Reactor::handle_events (ACE_Time_Value *how_long)*/
    virtual bool HandleEvents(Duration duration);
        
    virtual bool Notify(std::shared_ptr<EventHandler> handler, long mask);

    virtual bool Open();

    /* int ACE_WFMO_Reactor::register_handler (ACE_Event_Handler *event_handler, ACE_Reactor_Mask mask); */
    virtual bool RegisterHandler(std::shared_ptr<EventHandler> handler);

    virtual bool ScheduleTimer(std::shared_ptr<EventHandler> handler,
        const void *arg,
        TimePoint timePoint,
        Duration  interval);

protected:
    Duration CalculateTimeout(Duration maxWaitTime);
    /* int ACE_WFMO_Reactor_Handler_Repository::unbind_i(ACE_HANDLE handle,
                                                         ACE_Reactor_Mask mask,
                                                         bool &changes_required)
    */
    bool DeregisterHandlerImpl(std::shared_ptr<EventHandler> handler, long mask);

    /* int ACE_WFMO_Reactor::dispatch (DWORD wait_status) */
    //bool Dispatch(DWORD waitStatus);
    /* int ACE_WFMO_Reactor::dispatch_handles (DWORD wait_status) */
    bool Dispatch (std::shared_ptr<EventHandler> handler);
    uint_t ExpireTimers();

    /* int ACE_WFMO_Reactor::event_handling (ACE_Time_Value *max_wait_time, int alertable)
    */
    bool HandleEventsImpl(Duration duration);

    /* virtual int ACE_WFMO_Reactor::register_handler_i (ACE_HANDLE event_handle,
    ACE_HANDLE io_handle,
    ACE_Event_Handler *event_handler,
    ACE_Reactor_Mask mask);
    */
    bool RegisterHandlerImpl(std::shared_ptr<EventHandler> handler);

    /* Up call when handler->GetIoHandle() == InvalidHandleValue */
    bool UpCall(std::shared_ptr<EventHandler> handler);
    /*
    ACE_Reactor_Mask ACE_WFMO_Reactor::upcall (ACE_Event_Handler *event_handler,
        ACE_HANDLE io_handle,
        WSANETWORKEVENTS &events)
    */
    long UpCall(long events, std::shared_ptr<EventHandler> handler);
    bool WaitForMultipleEvents(Duration duration);
    
private:
    bool isActived;
    //ACE_WFMO_Reactor::notify_handler_, object type is WfmoReactorNotify
    std::shared_ptr<WfmoReactorNotify> notifyHandler; 
    WfmoReactorHandlerRepository repository;
    std::shared_ptr<TimerQueue> timerQueue;
};

#endif