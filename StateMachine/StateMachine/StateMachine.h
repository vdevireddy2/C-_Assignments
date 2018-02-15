#ifndef _STATE_MACHINE_H
#define _STATE_MACHINE_H
#include <stdio.h>

/*
** These classes are POSIX compatible and tested on Linux Ubuntu
** Should be compiled as g++ -std=c++11 statemachine.h statemachine.cpp paymentsystem.h paymentsystem.cpp main.cpp
** This code is not ported to Windows becuase of time constraint, we can port by replacing the signal methods 
** with Events and WaitForSingleObject and WaitForMultipleObjects methods in Windows API
*/

// Forward declaration
class StateMachine;

class StateBase
{
public:
	/// Called by the state machine engine to execute a state action
	/// @param[in] sm - A state machine instance.
	virtual void InvokeStateAction(StateMachine* sm) const = 0;
};

/// StateAction class takes two template arguments: A state machine class,
/// state machine member function pointer.
template <class SM, void (SM::*Func)()>
class StateAction : public StateBase
{
public:
	virtual void InvokeStateAction(StateMachine* sm) const
	{
		// Here SM is of type PaymentSystem
		// Downcast the state machine to the PaymentSystem type
		SM* derivedSM = static_cast<SM*>(sm);

		// Call the state function
		(derivedSM->*Func)();
	}
};

// A structure to hold a single row within the state map.
struct StateMapRow
{
	const StateBase* const State;
};

// base class for state machines
class StateMachine
{
public:
	StateMachine(unsigned char maxStates);
	// virtual ~StateMachine() {}
	unsigned char GetCurrentState() { return m_currentState; }
	void SetCurrentState(unsigned char newState) { m_currentState = newState; }
protected:
	enum { EVENT_IGNORED = 0xFE, CANNOT_HAPPEN };
	unsigned char m_currentState;
	unsigned char m_newState;

	// Externalevent such as StartySystem, StopSystem
	void ExternalEvent(unsigned char);
	void InternalEvent(unsigned char);
	virtual const StateMapRow* GetStateMap() = 0;
private:
	const unsigned char _maxStates;
	bool _eventGenerated;
	void StateEngine(void);
};

#endif //_STATE_MACHINE_H
