#include "SystemInclude.h"

#include "EventHandler.h"

using namespace std;

std::error_code EventHandler::HandleTimeOut(const TimePoint&, const void *arg)
{
    return error_code();
}