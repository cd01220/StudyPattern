#ifndef _Reactor_h_
#define _Reactor_h_

#include "SystemInclude.h"
#include "Event/EventHandler.h"

/**********************class ReactorImpl**********************/
/* class ACE_Reactor_Impl */
class ReactorImpl
{
public:
    virtual std::error_code RegisterHandler(std::shared_ptr<EventHandler> handler, uint32_t mask) = 0;

    virtual std::error_code RunEventLoop() = 0;
};

/**********************class SelectReactorImpl**********************/
/* class ACE_Select_Reactor_Impl */
class SelectReactorImpl: public ReactorImpl
{
public:
};

/**********************class Section**********************/
/* class ACE_Select_Reactor_T */
class SelectReactor: public SelectReactorImpl
{
public:
    /* ACE_Select_Reactor_T::register_handler(ACE_Event_Handler *eh, ACE_Reactor_Mask mask); */
    virtual std::error_code RegisterHandler(std::shared_ptr<EventHandler> handler, uint32_t mask);

private:
    std::map<Handle, std::pair<std::shared_ptr<EventHandler>, uint32_t>> handles;
};

/**********************class Reactor**********************/
/* class ACE_Reactor */
class Reactor
{
public:
    std::error_code RegisterHandler(std::shared_ptr<EventHandler> handler, uint32_t mask);

private:
    std::shared_ptr<ReactorImpl> implementation;
};


#endif
