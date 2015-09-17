#include "SystemInclude.h"

#include "AceDemo/ClientAcceptor.h"
#include "AceDemo/ClientService.h"

using namespace std;

/* time out call stack
1  inline int HaStatusDemo(int, ACE_TCHAR *[])
2  int ACE_Reactor::run_reactor_event_loop (REACTOR_EVENT_HOOK eh)
3  ACE_INLINE int ACE_WFMO_Reactor::handle_events (ACE_Time_Value *how_long);
4  ACE_WFMO_Reactor::event_handling (ACE_Time_Value *max_wait_time,int alertable)
5  ACE_INLINE int ACE_WFMO_Reactor::safe_dispatch (DWORD wait_status)
6  int ACE_WFMO_Reactor::dispatch (DWORD wait_status)
7  int ACE_WFMO_Reactor::expire_timers (void)
8  ACE_Timer_Queue_T<TYPE, FUNCTOR, ACE_LOCK, TIME_POLICY>::expire (void)
9  ACE_Timer_Queue_T<TYPE, FUNCTOR, ACE_LOCK, TIME_POLICY>::expire (const ACE_Time_Value &cur_time)
10 ACE_Timer_Queue_T<TYPE, FUNCTOR, ACE_LOCK, TIME_POLICY>::upcall (ACE_Timer_Node_Dispatch_Info_T<TYPE> &info,
                                                    const ACE_Time_Value &cur_time)
11 int ACE_Event_Handler_Handle_Timeout_Upcall::timeout()
12 int ClientAcceptor::handle_timeout(const ACE_Time_Value &tv, const void *arg)
*/

#include "ace/SOCK_Connector.h"
static int ClientMain(u_short port)
{
    ACE_INET_Addr srvr (port, ACE_LOCALHOST);

    ACE_SOCK_Connector connector;
    ACE_SOCK_Stream peer;

    if (-1 == connector.connect (peer, srvr))
    {
        ACE_ERROR_RETURN ((LM_ERROR,
            ACE_TEXT ("%p\n"),
            ACE_TEXT ("connect")), 1);
    }

    int bc;
    char buf[64];
    strcpy(buf, "abcdef");
    
    peer.send_n (buf, strlen(buf) + 1);
    bc = peer.recv (buf, strlen(buf) + 1);
    buf[bc] = '\0';
    std::cout << buf << std::endl;
    peer.close ();
    return 0;
}

// Listing 11 code/ch07
inline int HaStatusDemo(int, ACE_TCHAR *[])
{
    ACE_INET_Addr port_to_listen (5000, ACE_LOCALHOST);
    cout << port_to_listen.get_host_addr() << ", " << port_to_listen.get_port_number() << endl;

    ClientAcceptor acceptor;
    acceptor.reactor(ACE_Reactor::instance());
    if (acceptor.open(port_to_listen) == -1)
        return 1;

    std::thread thd(ClientMain, 5000);
    ACE_Reactor::instance()->run_reactor_event_loop();

    return (0);
}
// Listing 11
