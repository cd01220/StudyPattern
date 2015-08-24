#include "Public/SystemInclude.h"

#include "StateMachine/DemoStateMachine.h"
#include "StateMachine/CmdInterpreter.h"

using namespace std;


int main()
{   
    Application::DemoStateMachine demoStateMachine;
	Application::CmdInterpreter cmdInterpreter(cin,demoStateMachine);

	return cmdInterpreter.run();
}
