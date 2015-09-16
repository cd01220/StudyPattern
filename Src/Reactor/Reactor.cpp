#include "SystemInclude.h"

#include "Reactor/Reactor.h"
using namespace std;

/**********************class ReactorImpl**********************/
/* class ACE_Reactor_Impl */

/**********************class Section**********************/
/* class ACE_Select_Reactor_T */
error_code SelectReactor::RegisterHandler(shared_ptr<EventHandler> handler, uint32_t mask)
{
    error_code errCode;

    return errCode;
}

/**********************class Reactor**********************/
error_code Reactor::RegisterHandler(shared_ptr<EventHandler> handler, uint32_t mask)
{
    error_code errCode;
    Reactor *reactor = handler->GetReactor();
    handler->SetReactor(this);

    errCode = implementation->RegisterHandler(handler, mask);
    if (errCode)
    {
        handler->SetReactor(reactor);
    }

    return errCode;
}