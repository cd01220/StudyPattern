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
    no_id_space = 1,
    queue_is_full,
    queue_is_empty,
    time_out,
    unknown_error, 
};

class system_category_impl : public std::error_category
{
public:
    virtual const char* name() const;
    virtual std::string message(int ev) const;
    virtual std::error_condition default_error_condition(int ev) const;
};

const std::error_category& router_category();
std::error_code make_error_code(system_error_t e);
std::error_condition make_error_condition(system_error_t e);

namespace std
{
    template <>
    struct is_error_code_enum<system_error_t> : public true_type
    {};
}

#endif /* _SystemError_h_ */