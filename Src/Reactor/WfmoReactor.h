#ifndef _WfmoReactor_h_
#define _WfmoReactor_h_

#include "Reactor/ReactorImpl.h"

/**********************class HandlerRepository**********************/
struct HandlerMaskTuple
{
    std::shared_ptr<EventHandler> handler;
    long                          mask;
};
/* Handle:          event handle
   HandlerMaskTuple: EventHandler and mask
*/
typedef std::map<Handle, HandlerMaskTuple> HandlerRepository;

/**********************class WfmoReactor**********************/
/* class ACE_WFMO_Reactor (WFMO: Wait For Multiple Objects) */
class WfmoReactor: public ReactorImpl
{
public:
    bool IsActived();

    /* int ACE_WFMO_Reactor::handle_events (ACE_Time_Value *how_long)*/
    virtual std::error_code HandleEvents(Duration duration);

    /* int ACE_WFMO_Reactor::register_handler (ACE_Event_Handler *event_handler, ACE_Reactor_Mask mask); */
    virtual std::error_code RegisterHandler(std::shared_ptr<EventHandler> handler, long mask);

protected:
    /* int ACE_WFMO_Reactor::event_handling (ACE_Time_Value *max_wait_time, int alertable)
    */
    std::error_code HandleEventsImpl(Duration duration);

    /* virtual int ACE_WFMO_Reactor::register_handler_i (ACE_HANDLE event_handle,
    ACE_HANDLE io_handle,
    ACE_Event_Handler *event_handler,
    ACE_Reactor_Mask mask);
    */
    std::error_code RegisterHandlerImpl(std::shared_ptr<EventHandler> handler, long mask);

    std::error_code WaitForMultipleEvents(Duration duration);


private:
    HandlerRepository repository;
    bool isActived;        
};

#endif