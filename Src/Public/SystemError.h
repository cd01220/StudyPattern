#ifndef _SystemError_h_
#define _SystemError_h_

/* 
Example1:
    error_code errCode = system_error_t::file_not_exists;
    if (errCode == system_error_t::file_not_exists)
    {
        cout << errCode.message() << endl;
    }
Example 2:
    to raise an exception:
    void Func()
    {
        throw system_error(system_error_t::bad_file_type);
    }

    to catch an exception:
    try
    {
        Func()
    }
    catch (system_error& error)
    {
        cout << error.what() << endl;
    }
*/
enum class system_error_t
{
    invalid_parameter = 1,
    no_free_timer_id,
    reactor_isnot_actived, 
    time_out,
    queue_is_full,
    queue_is_empty,
	file_not_exists,
	bad_file_type,
    unknown_error, 
    wait_failed,
};

class system_category_impl : public std::error_category
{
public:
    virtual const char* name() const;
    virtual std::string message(int ev) const;
    virtual std::error_condition default_error_condition(int ev) const;
};

std::error_code make_error_code(system_error_t e);
std::error_condition make_error_condition(system_error_t e);

namespace std
{
    template <>
    struct is_error_code_enum<system_error_t> : public true_type
    {};
}

#endif /* _SystemError_h_ */