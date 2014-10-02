// ====================================================================================================
// State
// ====================================================================================================
#ifndef H_STATE
#define H_STATE

#include "StateIdentifiers.h"

class State
{
public:
	typedef std::unique_ptr<State> Ptr;

public:
	State(StateStack& stack);
	virtual ~State();
	virtual void Draw() = 0;
	virtual bool Update(sf::Time dt) = 0;
	virtual bool HandleEvent(const sf::Event& event) = 0;

protected:
	void RequestStackPush(States::ID stateID);
	void RequestStackPop();
	void RequestStateClear();

private:
	StateStack* mStack;
};

#include "StateStack.h"
#include "GameState.h"
#include "TitleState.h"
#include "MenuState.h"
#include "LoadingState.h"
#include "LoadingTask.h"

#endif