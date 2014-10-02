// ====================================================================================================
// Includes
// ====================================================================================================
#include "Includes.h"

// ====================================================================================================
// LoadingState
// ====================================================================================================
LoadingState::LoadingState(StateStack& stack) : State(stack)
{
	mText.setFont(g_pWorld->GetFontHolder()->Get("Main"));
	SetStatusText("Loading..");

	m_pLoadingTask = new LoadingTask();
	m_pLoadingTask->Execute(this);
}
LoadingState::~LoadingState()
{
	delete m_pLoadingTask;
}

// ====================================================================================================
// Update
// ====================================================================================================
bool LoadingState::Update(sf::Time dt)
{
	if (m_pLoadingTask->IsFinished())
	{
		printf("LoadingState::Update is finished\n");

		RequestStackPop();
		RequestStackPush(States::Game);
	}

	return true;
}
void LoadingState::SetStatusText(std::string text)
{
	mText.setString(text);
	UTIL::CenterOrigin(mText);
	mText.setPosition(g_pWorld->GetView()->getSize() / 2.f);
}

// ====================================================================================================
// Update
// ====================================================================================================
void LoadingState::Draw()
{
	sf::RenderWindow& window = g_pGame->GetWindow();
	window.draw(mText);
}

// ====================================================================================================
// Handle Event
// ====================================================================================================
bool LoadingState::HandleEvent(const sf::Event& event)
{
	return true;
}