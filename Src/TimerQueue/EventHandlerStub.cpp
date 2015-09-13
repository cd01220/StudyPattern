// $Id: EventHandlerStub.cpp 94310 2011-07-09 19:10:06Z schmidt $
#include "SystemInclude.h"
#include "SystemError.h"

using namespace std;
#include "EventHandlerStub.h"

EventHandlerStub::EventHandlerStub () : count(0)
{
  cout << "EventHandlerStub::EventHandlerStub" << endl;
}

// Listing 1 code/ch20
error_code EventHandlerStub::HandleTimeOut(TimePoint, const void *arg)
{
  cout << "EventHandlerStub::handle_timeout" << endl;

  const int *val = static_cast<const int*> (arg);
  //assert(*val == timerID);

  if (count == 5)
  {
      // New interval is 10 ms.
      TimeInterval interval (1000L);
      //int status = Timer::instance ()->reset_interval(timerID_, interval);
      //ACE_ASSERT (status != -1);
  }

  if (count++ == 10)
  {
      //Timer::instance ()->cancel (this)) != 0;
  }

  return error_code();
}
// Listing 1

void EventHandlerStub::SetID(long timerID)
{
    cout << "EventHandlerStub::setID" << endl;
    this->timerID = timerID;
}

int EventHandlerStub::GetID(void)
{
    return timerID;
}

//int EventHandlerStub::handle_close (ACE_HANDLE, ACE_Reactor_Mask)
//{
//    ACE_TRACE ("EventHandlerStub::handle_close");
//    return 0;
//}


