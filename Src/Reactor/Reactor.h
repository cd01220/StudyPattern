#ifndef _Reactor_h_
#define _Reactor_h_

#include "SystemInclude.h"

/**********************class ReactorImpl**********************/
/* class ACE_Reactor_Impl */
class ReactorImpl
{
public:
    virtual int RunEventLoop() = 0;
};

/**********************class SelectReactorImpl**********************/
/* class ACE_Select_Reactor_Impl */
class SelectReactorImpl: public ReactorImpl
{
};

/**********************class Section**********************/
/* class ACE_Select_Reactor_T */
class SelectReactor: public SelectReactorImpl
{

};

#endif
