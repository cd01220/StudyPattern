#ifndef _Handle_h_
#define _Handle_h_

#include "SystemInclude.h"

#ifdef _WIN32
    typedef HANDLE Handle;
    #define InvalidHandleValue INVALID_HANDLE_VALUE
        
    struct SignalInfo
    {
        SignalInfo (Handle handle);

        /// Win32 HANDLE that has become signaled.
        Handle handle;
    };
#else
#endif

#endif