
#ifndef _Interface_h_
#define _Interface_h_

#include "SystemInclude.h"

class StateMachine;

/**********************class Interface**********************/
class Interface
{
public:
    Interface() {}
    virtual ~Interface() {}
    virtual Interface* Receive() = 0;
};

#endif