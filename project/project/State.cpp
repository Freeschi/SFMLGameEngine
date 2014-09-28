// ====================================================================================================
// Includes
// ====================================================================================================
#include "Includes.h"

// ====================================================================================================
// State
// ====================================================================================================
State::State(StateStack& stack) : mStack(&stack)
{

}
State::~State()
{

}

// ====================================================================================================
// Request
// ====================================================================================================
void State::RequestStackPush(States::ID stateID)
{
	mStack->PushState(stateID);
}

void State::RequestStackPop()
{
	mStack->PopState();
}

void State::RequestStateClear()
{
	mStack->ClearStates();
}