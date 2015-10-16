#include "SystemInclude.h"
#include "SystemError.h" 

using namespace std;
const char* system_category_impl::name() const
{
    return "system error.";
}

string system_category_impl::message(int ev) const
{
    string ret;
    switch(ev)
    {
    case system_error_t::file_not_exists:
        ret = "file not exists";
        break;

    case system_error_t::bad_file_type:
        ret = "bad file type (supposed to be pcap format, 802.11 packet)";
        break;

    case system_error_t::wait_failed:
        ret = "wait failed";
        break;

    default:
        ret = "unknown error";
    }
    return ret;
}

error_condition system_category_impl::default_error_condition(int ev) const
{
    return error_condition(ev, *this);
}

const error_category& get_category_instance()
{
    static system_category_impl instance;
    return instance;
}

error_code make_error_code(system_error_t e)
{
    return error_code(static_cast<int>(e), get_category_instance());
}

error_condition make_error_condition(system_error_t e)
{
    return error_condition(static_cast<int>(e), get_category_instance());
}

