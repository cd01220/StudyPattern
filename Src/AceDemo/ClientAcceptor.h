#ifndef _ClientAcceptor_h_
#define _ClientAcceptor_h_

// Listing 1 code/ch07
#include "ace/Auto_Ptr.h"
#include "ace/Log_Msg.h"
#include "ace/INET_Addr.h"
#include "ace/SOCK_Acceptor.h"
#include "ace/Reactor.h"

class ClientAcceptor : public ACE_Event_Handler
{
public:
    virtual ~ClientAcceptor ();

    //FUZZ: disable check_for_lack_ACE_OS
    int open (const ACE_INET_Addr &listen_addr);
    //FUZZ: enable check_for_lack_ACE_OS

    // Get this handler's I/O handle.
    virtual ACE_HANDLE get_handle (void) const
    { return this->acceptor_.get_handle (); }

    // Called when a connection is ready to accept.
    virtual int handle_input (ACE_HANDLE fd = ACE_INVALID_HANDLE);

    // Called when this handler is removed from the ACE_Reactor.
    virtual int handle_close (ACE_HANDLE handle,
        ACE_Reactor_Mask close_mask);

protected:
    ACE_SOCK_Acceptor acceptor_;
};
// Listing 1



#endif