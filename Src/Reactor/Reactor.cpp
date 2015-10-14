#include "SystemInclude.h"
#include "SystemError.h"

#include "Event/EventHandler.h" //EventHandler
#include "Reactor/ReactorImpl.h" //ReactorImpl
#include "Reactor/WfmoReactor.h"
#include "Reactor/Reactor.h"
using namespace std;

/**********************class Reactor**********************/
Reactor::Reactor()
{
#ifdef _WIN32
    implementation = make_shared<WfmoReactor>(nullptr);
#endif
}

Reactor::~Reactor()
{
}

error_code Reactor::Notify(std::shared_ptr<EventHandler> handler, long mask)
{
    if (handler != nullptr && handler->GetReactor() == nullptr)
        handler->SetReactor(this);

    return implementation->Notify(handler, mask);
}

error_code Reactor::RegisterHandler(shared_ptr<EventHandler> handler)
{
    error_code errCode;
    Reactor *reactor = handler->GetReactor();
    handler->SetReactor(this);

    errCode = implementation->RegisterHandler(handler);
    if (errCode)
    {
        handler->SetReactor(reactor);
    }

    return errCode;
}

error_code Reactor::RunEventLoop()
{
    return RunReactorEventLoop(nullptr);
}

error_code Reactor::RunReactorEventLoop(ReactorEventHook hook)
{
    if (!implementation->IsActived())
    {
        return error_code(system_error_t::unknown_error);
    }

    error_code errCode;
    while (true)
    {
        errCode = implementation->HandleEvents(Duration::max());
        if (errCode)
        { 
            break; 
        }

        if (hook != nullptr)
        {
            hook(*this);
        }
    }

    return errCode;
}

error_code Reactor::ScheduleTimer(std::shared_ptr<EventHandler> handler,
        const void *arg,
        TimePoint timePoint,
        Duration  interval)
{
    // Remember the old reactor.
    Reactor *oldReactor = handler->GetReactor();
    handler->SetReactor(this);

    error_code errCode = this->implementation->ScheduleTimer(handler, arg, timePoint, interval);
    if (errCode)
    {
        // Reset the old reactor in case of failures.
        handler->SetReactor(oldReactor);
    }

    return errCode;
}