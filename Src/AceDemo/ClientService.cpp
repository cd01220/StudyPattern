// $Id: HAStatus.cpp 91626 2010-09-07 10:59:20Z johnnyw $

#include "ace/OS_NS_sys_time.h"
#include "ace/os_include/os_netdb.h"

#include "AceDemo/ClientAcceptor.h"
#include "AceDemo/ClientService.h"

// Listing 7 code/ch07
int ClientService::open (void)
{
    ACE_TCHAR peer_name[MAXHOSTNAMELEN];
    ACE_INET_Addr peer_addr;
    if (this->sock_.get_remote_addr (peer_addr) == 0 &&
        peer_addr.addr_to_string (peer_name, MAXHOSTNAMELEN) == 0)
        ACE_DEBUG ((LM_DEBUG,
        ACE_TEXT ("(%P|%t) Connection from %s\n"),
        peer_name));
    return this->reactor ()->register_handler
        (this, ACE_Event_Handler::READ_MASK);
}
// Listing 7

// Listing 8 code/ch07
int ClientService::handle_input (ACE_HANDLE)
{
    const size_t INPUT_SIZE = 4096;
    char buffer[INPUT_SIZE];
    ssize_t recv_cnt, send_cnt;

    if ((recv_cnt = this->sock_.recv (buffer, sizeof(buffer))) <= 0)
    {
        ACE_DEBUG ((LM_DEBUG,
            ACE_TEXT ("(%P|%t) Connection closed\n")));
        return -1;
    }

    send_cnt =
        this->sock_.send (buffer, static_cast<size_t> (recv_cnt));
    if (send_cnt == recv_cnt)
        return 0;
    if (send_cnt == -1 && ACE_OS::last_error () != EWOULDBLOCK)
        ACE_ERROR_RETURN ((LM_ERROR,
        ACE_TEXT ("(%P|%t) %p\n"),
        ACE_TEXT ("send")),
        0);
    if (send_cnt == -1)
        send_cnt = 0;
    ACE_Message_Block *mb = 0;
    size_t remaining =
        static_cast<size_t> ((recv_cnt - send_cnt));
    ACE_NEW_RETURN (mb, ACE_Message_Block (remaining), -1);
    mb->copy (&buffer[send_cnt], remaining);
    int output_off = this->output_queue_.is_empty ();
    ACE_Time_Value nowait (ACE_OS::gettimeofday ());
    if (this->output_queue_.enqueue_tail (mb, &nowait) == -1)
    {
        ACE_ERROR ((LM_ERROR,
            ACE_TEXT ("(%P|%t) %p; discarding data\n"),
            ACE_TEXT ("enqueue failed")));
        mb->release ();
        return 0;
    }
    if (output_off)
        return this->reactor ()->register_handler
        (this, ACE_Event_Handler::WRITE_MASK);
    return 0;
}
// Listing 8

// Listing 9 code/ch07
int ClientService::handle_output (ACE_HANDLE)
{
    ACE_Message_Block *mb = 0;
    ACE_Time_Value nowait (ACE_OS::gettimeofday ());
    while (0 <= this->output_queue_.dequeue_head
        (mb, &nowait))
    {
        ssize_t send_cnt =
            this->sock_.send (mb->rd_ptr (), mb->length ());
        if (send_cnt == -1)
            ACE_ERROR ((LM_ERROR,
            ACE_TEXT ("(%P|%t) %p\n"),
            ACE_TEXT ("send")));
        else
            mb->rd_ptr (static_cast<size_t> (send_cnt));
        if (mb->length () > 0)
        {
            this->output_queue_.enqueue_head (mb);
            break;
        }
        mb->release ();
    }
    return (this->output_queue_.is_empty ()) ? -1 : 0;
}
// Listing 9

// Listing 10 code/ch07
int ClientService::handle_close (ACE_HANDLE, ACE_Reactor_Mask mask)
{
    if (mask == ACE_Event_Handler::WRITE_MASK)
        return 0;
    mask = ACE_Event_Handler::ALL_EVENTS_MASK |
        ACE_Event_Handler::DONT_CALL;
    this->reactor ()->remove_handler (this, mask);
    this->sock_.close ();
    this->output_queue_.flush ();
    delete this;
    return 0;
}
// Listing 10

// Listing 12 code/ch07
class LoopStopper : public ACE_Event_Handler
{
public:
    LoopStopper (int signum = SIGINT);

    // Called when object is signaled by OS.
    virtual int handle_signal (int signum,
        siginfo_t * = 0,
        ucontext_t * = 0);
};

LoopStopper::LoopStopper (int signum)
{
    ACE_Reactor::instance ()->register_handler (signum, this);
}

int LoopStopper::handle_signal (int, siginfo_t *, ucontext_t *)
{
    ACE_Reactor::instance ()->end_reactor_event_loop ();
    return 0;
}
// Listing 12

// Listing 13 code/ch07
#include "ace/Signal.h"

class LogSwitcher : public ACE_Event_Handler
{
public:
    LogSwitcher (int on_sig, int off_sig);

    // Called when object is signaled by OS.
    virtual int handle_signal (int signum,
        siginfo_t * = 0,
        ucontext_t * = 0);

    // Called when an exceptional event occurs.
    virtual int handle_exception (ACE_HANDLE fd = ACE_INVALID_HANDLE);

private:
    LogSwitcher () {}

    int on_sig_;       // Signal to turn logging on
    int off_sig_;      // Signal to turn logging off
    int on_off_;       // 1 == turn on, 0 == turn off
};

LogSwitcher::LogSwitcher (int on_sig, int off_sig)
    : on_sig_ (on_sig), off_sig_ (off_sig)
{
    ACE_Sig_Set sigs;
    sigs.sig_add (on_sig);
    sigs.sig_add (off_sig);
    ACE_Reactor::instance ()->register_handler (sigs, this);
}
// Listing 13

// Listing 14 code/ch07
int LogSwitcher::handle_signal (int signum, siginfo_t *, ucontext_t *)
{
    if (signum == this->on_sig_ || signum == this->off_sig_)
    {
        this->on_off_ = signum == this->on_sig_;
        ACE_Reactor::instance ()->notify (this);
    }
    return 0;
}
// Listing 14

// Listing 15 code/ch07
int LogSwitcher::handle_exception (ACE_HANDLE)
{
    if (this->on_off_)
        ACE_LOG_MSG->clr_flags (ACE_Log_Msg::SILENT);
    else
        ACE_LOG_MSG->set_flags (ACE_Log_Msg::SILENT);
    return 0;
}
// Listing 15

