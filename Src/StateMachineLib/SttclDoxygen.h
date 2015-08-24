/**
 * @file SttclDoxygen.h
 *
 * Copyright (c) 2012, Guenther Makulik All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that
 * the following conditions are met:
 *
 * 1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
 *    disclaimer.
 * 2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided with the distribution.
 * 3) Neither the name STTCL nor the names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef STTCLDOXYGEN_HPP_
#define STTCLDOXYGEN_HPP_

/*! \mainpage STTCL state machine template class framework
 *
 * Content:\n
 * \ref intro_sec "1 Introduction"\n
 * \ref usage_sec "2 Usage of the STTCL state machine template class framework"\n
 * \ref usage_sec_1 "2.1 Declare a StateMachine implementation"\n
 * \ref usage_sec_2 "2.2 Declare State implementations"\n
 * \ref usage_sec_3 "2.3 Implement the state machine interfaces"\n
 * \ref usage_sec_4 "2.4 STTCL 'implementation hooks'"\n
 * \ref usage_sec_5 "2.5 Implement state actions and transitions"\n
 * \ref usage_sec_6 "2.6 Composite states"\n
 * \ref usage_sec_7 "2.7 Composite state regions, forks/joins"\n
 * \ref uml2gof_sec "3 Mapping of the UML state diagram notation elements to the GoF State pattern"\n
 * \ref sttcl_config_sec "4 Configuring the STTCL library for a specific OS/build environment"\n
 * \ref sttcl_config_sec_1 "4.1 Configuring STTCL builtin concurrency implementations"\n
 * \ref sttcl_config_sec_2 "4.2 Providing custom implementations for concurrency"\n
 *
 * \section intro_sec 1 Introduction
 *
 * The STTCL state machine template class framework provides a number of template classes to
 * implement UML 2.2 state machine specification compliant state machines. The template classes
 * are intended to be used as public base class of the implementation of state machine and state
 * classes. The basic function principle is based on the <A HREF="http://en.wikipedia.org/wiki/State_pattern" >GoF State Pattern</A>.
 *
 * You start with a given UML 2.2 state diagram that defines your applications behavior:
 * \image html StateMachine_Implementation_SD.png "State machine diagram"
 *
 * The GoF state pattern proposes to use a class design like shown in the following class diagram.
 * \image html StateMachine_Implementation_CD.png "State machine implementation class diagram"
 *
 * The overall class design using STTCL will look like the following detailed class diagram:
 * \image html Application_Design_CD.png "STTCL state machine application design class diagram"
 */

/**
 * \page usage_page Usage of the STTCL state machine template class framework
 * \section usage_sec 2 Usage of the STTCL state machine template class framework
 * \ref usage_sec_1 "2.1 Declare a StateMachine implementation"\n
 * \ref usage_sec_2 "2.2 Declare State implementations"\n
 * \ref usage_sec_3 "2.3 Implement the state machine interfaces"\n
 * \ref usage_sec_4 "2.4 STTCL 'implementation hooks'"\n
 * \ref usage_sec_5 "2.5 Implement state actions and transitions"\n
 * \ref usage_sec_6 "2.6 Composite states"\n
 * \ref usage_sec_7 "2.7 Composite state regions, forks/joins"\n
 *
 * \subsection usage_sec_1 2.1 Declare a StateMachine implementation
 *
 * Analyze your UML 2.2 state diagram and declare all necessary variables and event (trigger
 * methods) needed for the state machine. Declare an appropriate instance of \c sttcl::StateMachine
 * as base class for your state machine class.
 *
 * \code
class MyStateMachine;

class IStateEventHandlers
{
public:
	virtual handleEvent1(MyStateMachine* context) = 0;
	virtual handleEvent2(MyStateMachine* context) = 0;
};

class MyStateMachine : public sttcl::StateMachine<MyStateMachine,IStateEventHandlers>
{
public:
	void event1();
	void event2();

	int getX() const;
	const std::string& getY();

	// ...
};
\endcode
 *
 * According to the GoF state pattern implementation variants you can decide where to hold the
 * necessary state instances and make their sibling states accessible for them, so they can
 * realize event triggered transitions.
 * As a rule of thumb the state implementation classes can be instantiated as singletons (see
 * <A HREF="http://en.wikipedia.org/wiki/Singleton_Pattern">GoF Singleton pattern</A>) if they
 * have no member variables other than application scope configurations. Otherwise the available
 * states should be embedded members of the state machine implementation class and are accessible
 * from the state machine context for state implementation classes.
 *
 * \note State implementation classes inheriting from the sttcl::ActiveState
 * or sttcl::CompositeState template classes implicitly have embedded members in the base
 * classes.
 *
 * \subsection usage_sec_2 2.2 Declare State implementations
 * Implement a state class for each state in your UML 2.2 state machine diagram. Declare the
 * appropriate instance of the sttcl::State template class as base class for all state classes.
 * \code
class MyStateMachine;

class MyState1 : public sttcl::State<MyState1,MyStateMachine,IStateEventHandlers>
{
	// ...
};
\endcode
 *
 * \subsection usage_sec_3 2.3 Implement state machine interface
 *
 * The event1() and event2() method implementations of MyStateMachine can just delegate to the
 * matching call to the IStateEventHandlers interface of the current state
 * \code
void MyStateMachine::event1()
{
	IStateEventHandlers* currentState = getState();
	if(currentState)
	{
		currentState->handleEvent1(this);
	}
}
\endcode
 *
 * \subsection usage_sec_4 2.4 STTCL 'implementation hooks'
 *
 * The STTCL template base classes provide so called 'implementation hooks' to enable an implementation class to
 * override certain methods of the base class implementation. As soon the implementation class provides an implementation
 * hook method it will be called without using the vtable. The implementing class should always call the base classes
 * implementation of the implementation hook method to ensure the correct behavior of the state machine, unless you
 * want to reimplement the basic behavior yourself.
 *
 * \code
void MyState::entryImpl(MyStateMachine* context)
{
	// Provide state specific entry actions
	// ...

	// Call the base class implementation
	State<MyState,MyStateMachine,IState>::entryImpl(context);
}
\endcode
 *
 * \subsection usage_sec_5 2.5 Implement state actions and transitions
 *
 * Transition actions are implemented within the event handler methods of the state classes.
 * See the table in \ref uml2gof_sec "3 Mapping of the UML state diagram notation elements to the GoF State pattern"
 * for more details how UML2.2 state diagram elements can be implemented using the GoF state pattern and STTCL.
 *
 * State entry and exit actions can be implemented using the implementation hooks entryImpl() and exitImpl() in the
 * state implementation class.
 *
 * State do actions can be implemented in a method of the state implementation class, that is passed to the base class
 * constructor. The sttcl::ActiveState base class supports asynchronous execution of the state do action. It implements
 * a thread function loop, that calls the do action method until the state is exited.
 *
 * Direct state transitions (i.e. transitions between states without a triggering event method) are a special case.
 * You can handle these by overriding the checkDirectTransitionImpl() implementation hook in the state implementation
 * class.
 *
 * \subsection usage_sec_6 2.6 Composite states
 *
 * To implement composite states you can use the sttcl::CompositeState template base class. This class inherits both,
 * the sttcl::State and the sttcl::StateMachine template base classes. The first is used to specify a valid state
 * signature to embed the composite state implementation in an outer state machine implementation. The second specifies
 * the sub state machine of the composite state and specifies the signature for any inner states of the composite state
 * implementation.
 *
 * To use a history pseudo state within the composite state diagram you may optionally specify the \em HistoryType
 * template parameter. The state history behavior will automatically appear on any entry of the composite state
 * implementation until it is (re-)initialized.
 *
 * \subsection usage_sec_7 2.7 Composite state regions, forks/joins
 *
 * If you need orthogonal state machine regions or transition paths that go out a fork pseudo state you can use the
 * sttcl::ConcurrentCompositeState and sttcl::Region template base classes. The sttcl::ConcurrentCompositeState
 * base class needs to be initialized with a fixed array of pointers to sttcl::Region implementation instances in
 * the constructor. The overall number of regions contained in the sttcl::ConcurrentCompositeState implementation
 * is specified using the \em NumOfRegions template parameter.
 * To broadcast events to the contained regions the state interface methods used for the sttcl::ConcurrentCompositeState
 * implementation need to have a special signature as follows:
 * \code
typedef void (StateInterface::*OuterEventHandler)(StateMachineImpl*);
\endcode
 *
 * Each of the sttcl::Region implementations runs its own internal thread, where state transitions of the contained
 * states (including initialization, finalization and history behavior) are performed.
 * That event method calls to the sttcl::ConcurrentCompositeState \em IInnerState interface methods can be dispatched to these region threads, all
 * of the inner state interfaces methods need to have a special signature as follows:
 * \code
typedef void (InnerState::*InnerEventHandler)(StateMachineImpl*,RegionBase<StateMachineImpl,StateInterface,IInnerState>*);
\endcode
 *
 * You can also specify a type or class to pass additional event arguments to the dispatched event methods. These event
 * arguments need to be managed using a thread safe smart pointer that is provided with the sttcl::RefCountPtr template
 * class. If you specify the \em EventArgs template parameter to the sttcl::ConcurrentCompositeState and matching
 * sttcl::Region classes, the outer and inner state interface method signatures must look like this:
 * \code
typedef void (StateInterface::*OuterEventHandler)(StateMachineImpl*,RefCountPtr<EventArgs>);
typedef void (InnerState::*InnerEventHandler)(StateMachineImpl*,RegionBase<StateMachineImpl,StateInterface,IInnerState>*,RefCountPtr<EventArgs>);
\endcode
 *
 * Its your responsibility to create an appropriate hierarchy of event argument classes and to decode these for particular
 * event methods if necessary. The RefCountPtr template needs to be instantiated with a common base class in this case.
 *
 * Fork pseudo states can be represented by a sttcl::ConcurrentCompositeState implementation providing a region for
 * each of the forks outgoing transitions. A join pseudo state equivalents the finalized state of the sttcl::ConcurrentCompositeState
 * class.
 */

/**
 * \page uml2gof_page Mapping of the state diagram notation elements
 * \section uml2gof_sec 3 Mapping of the UML state diagram notation elements to the GoF State pattern
 * \htmlinclude UMLStateGoFStateMapping.html
 *
 */

/**
 * \page sttcl_config_page Configuring the STTCL library for a specific OS/build environment
 * \section sttcl_config_sec 4 Configuring the STTCL library for a specific OS/build environment
 * \ref sttcl_config_sec_1 "4.1 Configuring STTCL builtin concurrency implementations"\n
 * \ref sttcl_config_sec_2 "4.2 Providing custom implementations for concurrency"\n
 *
 * STTCL uses wrapper classes (adapters) for the environment specific implementations of the above mentioned capabilities:
 * \li \link sttcl::internal::SttclThread\endlink as thread adapter
 * \li \link sttcl::internal::SttclMutex\endlink as mutex abstraction (needs timed/unblocking try_lock() implementation)
 * \li \link sttcl::internal::SttclSemaphore\endlink as semaphore abstraction (needs timed/unblocking try_wait() implementation)
 * \li \link sttcl::TimeDuration\endlink as abstraction for a &quot;real&quot;-time duration
 *
 * \subsection sttcl_config_sec_1 4.1 Configuring STTCL builtin concurrency implementations
 *
 * To use the builtin implementations you need to build the STTCL source files using one of the following defines
 * (add -D\<config\> to your compiler flags):
 * \li \c STTCL_BOOST_IMPL to select the boost implementation as default
 * \li \c STTCL_POSIX_IMPL to select the POSIX implementation as default
 * \li \c STTCL_CX11_IMPL to select the C++ 11 standard implementation as default
 *
 * \subsection sttcl_config_sec_2 4.2 Providing custom implementations for concurrency
 * You may implement your own abstractions for threads, mutexes, semaphores and time duration representation. Provide the following defines to set your custom implementation as defaults (these must be seen by the STTCL header files):
 *
 * \code
#define STTCL_DEFAULT_THREADIMPL MyThreadImpl
#define STTCL_DEFAULT_MUTEXDIMPL MyMutexImpl
#define STTCL_DEFAULT_SEMAPHOREIMPL MySemaphoreImpl
#define STTCL_DEFAULT_TIMEDURATIONIMPL MyTimeDurationImpl
\endcode
 *
 * Alternatively you can provide your implementations directly as template parameters of the STTCL template base classes.
 */

/**
 * @namespace sttcl
 * @brief Provides base classes to build state machines.
 */
namespace sttcl
{

/**
 * @namespace sttcl::internal
 * @brief Classes used internally by the STTCL implementation
 */
namespace internal
{

/**
 * @namespace sttcl::internal::boost_impl
 * @brief Contains boost based implementation classes for STTCL.
 */
namespace boost_impl
{
}

/**
 * @namespace sttcl::internal::posix_impl
 * @brief Contains posix based implementation classes for STTCL.
 */
namespace posix_impl
{
}

/**
 * @namespace sttcl::internal::cx11_impl
 * @brief Contains C++ 11 standard based implementation classes for STTCL.
 */
namespace cx11_impl
{
}
}
}

#endif /* STTCLDOXYGEN_HPP_ */
