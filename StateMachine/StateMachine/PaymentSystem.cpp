#include <assert.h>
#include "paymentsystem.h"
#include <iostream>
#include <csignal>
#include <chrono>
#include <thread>

/*
** These classes are POSIX compatible and tested on Linux Ubuntu
** Should be compiled as g++ -std=c++11 statemachine.h statemachine.cpp paymentsystem.h paymentsystem.cpp main.cpp
** This code is not ported to Windows, we can port by replacing the signal methods with Events and WaitForSingleObject
** and WaitForMultipleObjects methods in Windows API
*/
using namespace std;
int PaymentSystem::transactionStatus = 0;

void PaymentSystem::StartSystem(void)
{
	static const unsigned char TRANSITIONMATRIX[] = {
		// Next State                          Current State
		// -----------					       ----------------	
		STARTUP_ST,                      		// IDLE_ST
		PENDING_ST,                      		// STARTUP_ST
		STARTUP_ST,                      		// PENDING_ST
		PENDING_ST,                      		// TRANSACTING_ST
	};
	ExternalEvent(TRANSITIONMATRIX[GetCurrentState()]);  // GetCurrentState is initialized with IDLE_ST at starting
	assert((sizeof(TRANSITIONMATRIX) / sizeof(unsigned char)) == MAX_STATES);
}

void PaymentSystem::Idle_St()
{
	cout << "PaymentSystem::Idle_St" << endl;
}

void PaymentSystem::Startup_St()
{
	cout << endl;
	cout << "PaymentSystem::Starup_St: Systemonline" << endl;
	cout << "	Logging online event ... Done" << endl;

	InternalEvent(PENDING_ST);
}

void PaymentSystem::Pending_St()
{
	cout << "PaymentSystem::Pending_St: New transaction received" << endl;
	cout << "	Sending transaction event to the server ... Done" << endl;
	cout << "	Logging transaction event ... Done" << endl;

	SetTimer();
	RegisterTimer();
	InternalEvent(TRANSACTING_ST);
}

void PaymentSystem::Unexpected_St()
{
	cout << "PaymentSystem::Unexpected_St <<<<<<<<<" << endl;
}

void PaymentSystem::Transacting_St()
{
	char insertDelay[2];
	// Reset the transactionStatus
	PaymentSystem::transactionStatus = 0;

	std::cout << "Do you want to introduce 30 sec. delay in PaymentSystem::Transacting_St y/n ?(n) ";
	std::cin.getline(insertDelay, 2);
	std::cout << endl;
	std::cout << "PaymentSystem::Transacting_St Processing..." << endl;
	if (insertDelay[0] == 'y')
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(30000));
	}
	if (PaymentSystem::transactionStatus == 0)
	{
		cout << endl;
		cout << "PaymentSystem::Transacting_St completed **SUCCESSFULLY**" << endl;

		tout_val.it_interval.tv_sec = 0;
		tout_val.it_interval.tv_usec = 0;
		tout_val.it_value.tv_sec = 0;    // Reset the timer if any 
		tout_val.it_value.tv_usec = 0;
		InternalEvent(PENDING_ST);
	}
	else
	{
		cout << "PaymentSystem::Transacting_St failed **SYSTEM ERROR**" << endl;
		InternalEvent(STARTUP_ST);
	}
}

#define INTERVAL 30
void PaymentSystem::SetTimer()
{

	tout_val.it_interval.tv_sec = 0;
	tout_val.it_interval.tv_usec = 0;
	tout_val.it_value.tv_sec = INTERVAL;
	tout_val.it_value.tv_usec = 0;

	setitimer(ITIMER_REAL, &tout_val, 0);
}

void PaymentSystem::TimerEvent()
{
	cout << endl;
	cout << "PaymentSytem::Transaction_St: Transaction timedout" << endl;
	transactionStatus = 1;
}

void PaymentSystem::RegisterTimer()
{
	typedef void(*pTimerEvent)(void);
	pTimerEvent ptTimerEvent = &TimerEvent;
	signal(SIGALRM, (void(*)(int))ptTimerEvent); /* set the Alarm signal capture */
}
