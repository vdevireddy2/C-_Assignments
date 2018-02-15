#ifndef _PAYMENTSYSTEM_H
#define _PAYMENTSYSTEM_H
#include <assert.h>
#include <sys/time.h>
#include <csignal>
#include "statemachine.h"

// PaymentSystem finite sate machine class
class PaymentSystem : public StateMachine
{
public:
	PaymentSystem() : StateMachine(MAX_STATES) {}

	struct itimerval tout_val;

	// external events taken by this state machine
	void StartSystem();

	// setitimer related methods
	void SetTimer();
	void RegisterTimer();
	static void TimerEvent(void);
	static int transactionStatus;

private:

	// state map to define state function order

	enum E_states {
		IDLE_ST = 0,
		STARTUP_ST,
		PENDING_ST,
		TRANSACTING_ST,
		UNEXPECTED_ST,
		MAX_STATES,
	};

	// Define the state machine state functions as a templates
	void Idle_St();
	StateAction<PaymentSystem, &PaymentSystem::Idle_St> Idle;

	void Startup_St();
	StateAction<PaymentSystem, &PaymentSystem::Startup_St> Startup;

	void Pending_St();
	StateAction<PaymentSystem, &PaymentSystem::Pending_St> Pending;

	void Transacting_St();
	StateAction<PaymentSystem, &PaymentSystem::Transacting_St> Transacting;

	void Unexpected_St();
	StateAction<PaymentSystem, &PaymentSystem::Unexpected_St> Unexpected;


private:
	virtual const StateMapRow* GetStateMap() {
		static const StateMapRow STATE_MAP[] = {
			&Idle,
			&Startup,
			&Pending,
			&Transacting,
			&Unexpected
		};
		assert((sizeof(STATE_MAP) / sizeof(StateMapRow)) == MAX_STATES);
		return &STATE_MAP[0];
	}
};
#endif // _PAYMENTSYSTEM_H
