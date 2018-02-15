#include <assert.h>
#include "statemachine.h"

StateMachine::StateMachine(unsigned char maxStates) :
	_maxStates(maxStates),
	m_currentState(0),
	_eventGenerated(false)
{
}

// generates an external event. Called from PaymentSystem::StartupSystem()
void StateMachine::ExternalEvent(unsigned char newState)
{
	InternalEvent(newState);
	StateEngine();
}

// generates an internal event. called from within a state
// function to transition to a new state
void StateMachine::InternalEvent(unsigned char newState)
{
	_eventGenerated = true;
	m_newState = newState;
}

// the state engine executes the state machine states
void StateMachine::StateEngine(void)
{
	const StateMapRow* pStateMap = GetStateMap();
	if (pStateMap != NULL)
	{
		// while events are being generated keep executing states
		while (_eventGenerated) {
			_eventGenerated = false;
			// Get the pointer from the state map
			const StateBase* state = pStateMap[m_newState].State;
			// Switch to the new current state
			SetCurrentState(m_newState);
			state->InvokeStateAction(this);
		}

	}
}
