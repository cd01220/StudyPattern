#if !defined(_TaskBase_h_)
#define _TaskBase_h_

#include "Task/ServiceObject.h"

/**********************class TaskBase**********************/
/* Origial definition: ACE_Task_Base */
class TaskBase: public ServiceObject
{
public:
    TaskBase();
    ~TaskBase();
    
    std::error_code Activate();

    /**
    * Hook called from ACE_Thread_Exit when during thread exit and from
    * the default implementation of @c module_closed().  In general, this
    * method shouldn't be called directly by an application,
    * particularly if the Task is running as an Active Object.
    * Instead, a special message should be passed into the Task via
    * the put() method defined below, and the svc() method should
    * interpret this as a flag to shut down the Task.
    */
    virtual std::error_code Close(uint_t flags = 0);

    // Inform the dispatching thread that it should terminate.
    virtual void Deactivate (void);

    /// Hook called to initialize a task and prepare it for execution.
    /// @a args can be used to pass arbitrary information into <open>.
    virtual std::error_code Open(void *args = nullptr);

    // service thread routine
    // original definition: virtual int ACE_Task_Base::svc (void);
    virtual std::error_code ServiceRoutine();

private:
    // Routine that runs the service routine as a daemon thread.
    // static ACE_THR_FUNC_RETURN svc_run (void *);
    void ThreadRoutine();

protected:
    std::thread svcThread;  //service thread
};

#endif