// ====================================================================================================
// Includes
// ====================================================================================================
#include "Includes.h"

// ====================================================================================================
// Pause State
// ====================================================================================================
PauseState::PauseState(StateStack& stack) : State(stack)
{
	sf::Font& font = g_pWorld->GetFontHolder()->Get("Main");

	mPausedText.setFont(font);
	mPausedText.setString("PAUSED");
	UTIL::CenterOrigin(mPausedText);
	mPausedText.setPosition(g_pWorld->GetView()->getSize() / 2.f);

	lua->GetEvent("OnGamePaused");
	lua->ProtectedCall(1);
}

// ====================================================================================================
// Draw
// ====================================================================================================
void PauseState::Draw()
{
	sf::RenderWindow& window = g_pWorld->GetWindow();
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(sf::Vector2f(window.getSize()));

	window.draw(backgroundShape);
	window.draw(mPausedText);
}

// ====================================================================================================
// Event Handler
// ====================================================================================================
bool PauseState::HandleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	{
		g_pGame->SetPaused(false);

		lua->GetEvent("OnGameUnpaused");
		lua->ProtectedCall(1);

		RequestStackPop();
	}

	return true;
}

// ====================================================================================================
// Update
// ====================================================================================================
bool PauseState::Update(sf::Time dt)
{
	g_pGame->flLastPause = LuaFunctions::uptime();
	return true;
}