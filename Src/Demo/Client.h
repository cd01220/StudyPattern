#ifndef _Client_h_
#define _Client_h_

#include "SystemInclude.h"
#include "Task/Task.h"

class ReactorNotificationStrategy;
/**********************class Client**********************/
class Client: public Task
{
public:
    typedef Task MyBase;
    Client(Reactor *reactor);
    ~Client();
    
    virtual bool HandleInput();
    virtual bool HandleOutput();
    virtual bool HandleTimeOut(TimePoint, const void *arg = 0);
        
    virtual bool Open(void *args);
};


#endif