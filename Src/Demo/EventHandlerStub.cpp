#include "SystemInclude.h"
#include "SystemError.h"

#include "Demo/EventHandlerStub.h"
using namespace std;

EventHandlerStub::EventHandlerStub()
{
    cout << "EventHandlerStub::EventHandlerStub" << endl;
}

error_code EventHandlerStub::HandleInput()
{
    cout << "EventHandlerStub::HandleInput()" << endl;    
    return std::error_code();
}

error_code EventHandlerStub::HandleTimeOut(TimePoint, const void *arg)
{
    cout << "EventHandlerStub::HandleTimeOut()" << endl;
    return std::error_code();
}
