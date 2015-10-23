#ifndef _ServiceObject_h_
#define _ServiceObject_h_

#include "Event/EventHandler.h"  //EventHandler

class Reactor;
/**********************class ServiceObject**********************/
/* Origial definition: ACE_Service_Object */
class ServiceObject: public EventHandler
{
public:
    // = Initialization and termination methods.
    /// Constructor.
    ServiceObject (Reactor *reactor);

    /// Destructor.
    virtual ~ServiceObject (void);

    /// Temporarily disable a service without removing it completely.
    virtual bool Suspend (void);

    /// Re-enable a previously suspended service.
    virtual bool Resume (void);
};

#endif