#include "SystemInclude.h"

#include "ace/OS_NS_sys_time.h"
#include "ace/os_include/os_netdb.h"
#include "ace/Timer_List.h"

#include "AceDemo/ClientService.h"
#include "AceDemo/ClientAcceptor.h"

ClientAcceptor::ClientAcceptor()
{
}

// Listing 5 code/ch07
ClientAcceptor::~ClientAcceptor ()
{
    this->handle_close (ACE_INVALID_HANDLE, 0);
}
// Listing 5

// Listing 2 code/ch07
int ClientAcceptor::open(const ACE_INET_Addr &listen_addr)
{
    if (this->acceptor_.open (listen_addr, 1) == -1)
        ACE_ERROR_RETURN ((LM_ERROR,
        ACE_TEXT ("%p\n"),
        ACE_TEXT ("acceptor.open")),
        -1);
    
    ACE_Timer_Queue *timer_queue;
    ACE_NEW_NORETURN(timer_queue, ACE_Timer_List);
    this->reactor()->timer_queue(timer_queue);

    const ACE_Time_Value curr_tv = ACE_OS::gettimeofday() + ACE_Time_Value (1L);
    ACE_Time_Value interval = ACE_Time_Value (1, 500);
    int ret = this->reactor()->schedule_timer(this, nullptr, interval,  interval);
    if (ret != 0)
        std::cout << "error" << std::endl;

    return this->reactor()->register_handler(this, ACE_Event_Handler::ACCEPT_MASK | ACE_Event_Handler::TIMER_MASK);
}
// Listing 2

// Listing 3 code/ch07
int ClientAcceptor::handle_input (ACE_HANDLE)
{
    ClientService *client;
    ACE_NEW_RETURN (client, ClientService, -1);
    auto_ptr<ClientService> p (client);

    if (this->acceptor_.accept (client->peer()) == -1)
    {
        ACE_ERROR_RETURN((LM_ERROR,
            ACE_TEXT ("(%P|%t) %p\n"),
            ACE_TEXT ("Failed to accept ")
            ACE_TEXT ("client connection")),
            -1);
    }
    p.release ();
    client->reactor (this->reactor ());
    if (client->open () == -1)
        client->handle_close (ACE_INVALID_HANDLE, 0);
    return 0;
}
// Listing 3

// Listing 4 code/ch07
int ClientAcceptor::handle_close (ACE_HANDLE, ACE_Reactor_Mask)
{
    if (this->acceptor_.get_handle () != ACE_INVALID_HANDLE)
    {
        ACE_Reactor_Mask m = ACE_Event_Handler::ACCEPT_MASK |
            ACE_Event_Handler::DONT_CALL;
        this->reactor ()->remove_handler (this, m);
        this->acceptor_.close ();
    }
    return 0;
}
// Listing 4

int ClientAcceptor::handle_timeout(const ACE_Time_Value &tv,
                            const void *arg)
{
    std::cout << "ClientAcceptor::handle_timeout" << std::endl;
    return 0;
}