#if !defined(_ServiceObject_h_)
#define _ServiceObject_h_

#include "Event/EventHandler.h"

class ServiceObject: public EventHandler
{
public:
  // = Initialization and termination methods.
  /// Constructor.
  ServiceObject (Reactor *reactor = nullptr);

  /// Destructor.
  virtual ~ServiceObject (void);

  /// Temporarily disable a service without removing it completely.
  virtual int Suspend (void);

  /// Re-enable a previously suspended service.
  virtual int Resume (void);
};

#endif