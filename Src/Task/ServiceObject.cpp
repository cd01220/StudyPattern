#include "SystemInclude.h"

#include "ServiceObject.h"
using namespace std;

/**********************class ServiceObject**********************/
/* Origial definition: ACE_Service_Object */
ServiceObject::ServiceObject()
{}

/// Destructor.
ServiceObject::~ServiceObject (void)
{
}

/// Temporarily disable a service without removing it completely.
bool ServiceObject::Suspend (void)
{
    return true;
}

/// Re-enable a previously suspended service.
bool ServiceObject::Resume (void)
{
    return true;
}