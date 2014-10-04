// ====================================================================================================
// Includes
// ====================================================================================================
#include "Includes.h"

PauseState::PauseState(StateStack& stack) : State(stack)
{
	sf::Font& font = g_pWorld->GetFontHolder()->Get("Main");

	sf::Text mPausedText;
	mPausedText.setFont(font);
	mPausedText.setString("PAUSED");
	UTIL::CenterOrigin(mPausedText);
	mPausedText.setPosition(g_pWorld->GetView()->getSize() / 2.f);
}


// ====================================================================================================
// Draw
// ====================================================================================================
void PauseState::Draw()
{

		sf::RenderWindow& window = g_pWorld->GetWindow();
		window.setView(* g_pWorld->GetView());

		sf::RectangleShape backgroundShape;
		backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
		backgroundShape.setSize(sf::Vector2f(window.getSize()));

		window.draw(backgroundShape);
		window.draw(mPausedText);

}

bool PauseState::HandleEvent(const sf::Event& event)
{
	if (event.key.code == sf::Keyboard::BackSpace)
	{
		
	}

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	{
			std::cout << "Game was unpaused!\n";
			RequestStackPop();
	}

	return true;
}

bool PauseState::Update(sf::Time dt)
{
	g_pGame->flLastPause = LuaFunctions::uptime();
	return true;
}