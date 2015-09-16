#include "SystemInclude.h"
#include "SystemError.h"

#include "ServiceObject.h"
using namespace std;

/**********************class ServiceObject**********************/
/* Origial definition: ACE_Service_Object */
ServiceObject::ServiceObject(Reactor *reactor)
    : EventHandler(reactor)
{
}

/// Destructor.
ServiceObject::~ServiceObject (void)
{
}

/// Temporarily disable a service without removing it completely.
error_code ServiceObject::Suspend (void)
{
    return error_code();
}

/// Re-enable a previously suspended service.
error_code ServiceObject::Resume (void)
{
    return error_code();
}