#include "AceDemo/ClientAcceptor.h"
#include "AceDemo/ClientService.h"

// Listing 11 code/ch07
inline int HaStatusDemo (int, ACE_TCHAR *[])
{
    ACE_INET_Addr port_to_listen ("HAStatus");
    cout << port_to_listen.get_host_addr() << ", " << port_to_listen.get_port_number() << endl;

    ClientAcceptor acceptor;
    acceptor.reactor (ACE_Reactor::instance ());
    if (acceptor.open (port_to_listen) == -1)
        return 1;

    ACE_Reactor::instance ()->run_reactor_event_loop ();

    return (0);
}
// Listing 11
