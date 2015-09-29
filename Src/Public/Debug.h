#ifndef _Debug_h_
#define _Debug_h_

#ifdef WIN32
#   define __func__ __FUNCTION__
#endif

std::ostream& DbgClearStream(char const*, uint32_t);
std::ostream& DbgOStream(char const*, uint32_t);
std::ostream& ErrOStream(char const*, uint32_t);

#define dbgcstrm DbgClearStream(__func__, __LINE__)
#define dbgstrm DbgOStream(__func__, __LINE__)
#define prtstrm ErrOStream(__func__, __LINE__)
#define errstrm ErrOStream(__func__, __LINE__)

/*Example:  
    char a = 10;  
    cout <<  DbgExpandVar(a, int);
    out put:  a = 10
*/
#define DbgExpandVar(v, type) #v << " = " << (type)v

class DebugFlag
{
public:
    DebugFlag();

    bool GetState(std::string const& funcName);
    void SetState(std::string const& funcName, bool doDebug);

private:
    static std::map<std::string, bool> flags;
};

#define Printf(...) \
{   const char* func = __func__; int line = __LINE__; \
    DebugFlag flag;                     \
    if (flag.GetState(func))            \
    {                                   \
        printf("%s, %d> ", func, line); \
        printf(__VA_ARGS__);            \
    }                                   \
}

#endif /* _Debug_h_ */
