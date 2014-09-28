// ====================================================================================================
// Includes
// ====================================================================================================
#include "Includes.h"

// ====================================================================================================
// State Stack
// ====================================================================================================
StateStack::StateStack()
{

}

// ====================================================================================================
// Create State
// ====================================================================================================
State::Ptr StateStack::CreateState(States::ID stateID)
{
	auto found = mFactories.find(stateID);
	if (found == mFactories.end())
	{
		// Invalid State
		printf("[StateStack] Called CreateStack with invalid State (%i)!\n", stateID);
		throw std::string("StateStack::CreateState called with invalid State!");
	}
	return found->second();
}

// ====================================================================================================
// State: Handle Event
// ====================================================================================================
void StateStack::HandleEvent(const sf::Event& event)
{
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		if (!(*itr)->HandleEvent(event))
			return;
	}

	ApplyPendingChanges();
}

// ====================================================================================================
// State: Update
// ====================================================================================================
void StateStack::Update(sf::Time dt)
{
	// Iterate from top to bottom, stop as soon as update() returns false
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		if (!(*itr)->Update(dt))
			break;
	}

	ApplyPendingChanges();
}

// ====================================================================================================
// State: Apply Pending Changes
// ====================================================================================================
void StateStack::ApplyPendingChanges()
{
	FOREACH(PendingChange change, mPendingList)
	{
		switch (change.action)
		{
		case Push:
			mStack.push_back(CreateState(change.stateID));
			break;
		case Pop:
			mStack.pop_back();
			break;
		case Clear:
			mStack.clear();
			break;
		}
	}
	mPendingList.clear();
}

// ====================================================================================================
// State: Draw
// ====================================================================================================
void StateStack::Draw()
{
	// Draw all active states from bottom to top
	FOREACH(State::Ptr& state, mStack)
		state->Draw();
}

// ====================================================================================================
// State Operations
// ====================================================================================================
void StateStack::PushState(States::ID stateID)
{
	mPendingList.push_back(PendingChange(Push, stateID));
}
void StateStack::PopState()
{
	mPendingList.push_back(PendingChange(Pop));
}
void StateStack::ClearStates()
{
	mPendingList.push_back(PendingChange(Clear));
}
bool StateStack::IsEmpty() const
{
	return mStack.empty();
}