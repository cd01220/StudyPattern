#ifndef _WfmoReactor_h_
#define _WfmoReactor_h_

#include "Reactor/ReactorImpl.h"

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
    std::shared_ptr<EventHandler> Find(size_t index);
    Handle* GetEventHandles();
    size_t GetSize();

    void Insert(std::shared_ptr<EventHandler>);

private:
    Handle handles[MAXIMUM_WAIT_OBJECTS];
    std::map<Handle, std::shared_ptr<EventHandler>> repository;
};

/**********************class WfmoReactor**********************/
/* class ACE_WFMO_Reactor (WFMO: Wait For Multiple Objects) */
class WfmoReactor: public ReactorImpl
{
public:
    bool IsActived();

    /* int ACE_WFMO_Reactor::handle_events (ACE_Time_Value *how_long)*/
    virtual std::error_code HandleEvents(Duration duration);

    /* int ACE_WFMO_Reactor::register_handler (ACE_Event_Handler *event_handler, ACE_Reactor_Mask mask); */
    virtual std::error_code RegisterHandler(std::shared_ptr<EventHandler> handler);

protected:
    /* int ACE_WFMO_Reactor::dispatch (DWORD wait_status) */
    std::error_code Dispatch(DWORD waitStatus);
    /* int ACE_WFMO_Reactor::dispatch_handles (DWORD wait_status) */
    std::error_code DispatchHandles (size_t index);

    /* int ACE_WFMO_Reactor::event_handling (ACE_Time_Value *max_wait_time, int alertable)
    */
    std::error_code HandleEventsImpl(Duration duration);

    /* virtual int ACE_WFMO_Reactor::register_handler_i (ACE_HANDLE event_handle,
    ACE_HANDLE io_handle,
    ACE_Event_Handler *event_handler,
    ACE_Reactor_Mask mask);
    */
    std::error_code RegisterHandlerImpl(std::shared_ptr<EventHandler> handler);
    /*
    ACE_Reactor_Mask ACE_WFMO_Reactor::upcall (ACE_Event_Handler *event_handler,
        ACE_HANDLE io_handle,
        WSANETWORKEVENTS &events)
    */
    long UpCall(long events, std::shared_ptr<EventHandler> handler);
    std::error_code WaitForMultipleEvents(Duration duration);
    
private:
    bool isActived;     
    WfmoReactorHandlerRepository repository;
};

#endif