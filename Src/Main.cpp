#include "SystemInclude.h"
#include "SystemError.h"

#if 1
#   include "AceDemo/HAStatusDemo.h"
#   include "AceDemo/MessageReceiver.h"
#else
#   include "Demo/ActiveTimerDemo.h"
#endif
using namespace std;

int main(int argc, char *argv[])
{
    HaStatusDemo(argc, argv);
    return 0;
}
