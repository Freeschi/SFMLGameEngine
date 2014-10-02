// ====================================================================================================
// Includes
// ====================================================================================================
#include "Includes.h"

// ====================================================================================================
// Title State
// ====================================================================================================
TitleState::TitleState(StateStack& stack) : State(stack), mStateTime(sf::Time::Zero)
{
	mBackgroundSprite.setTexture(g_pWorld->GetTextureHolder()->Get("FreschiLogo_Big"));
}

// ====================================================================================================
// Handle Event
// ====================================================================================================
bool TitleState::HandleEvent(const sf::Event& event)
{
	return true;
}

// ====================================================================================================
// Draw
// ====================================================================================================
void TitleState::Draw()
{
	sf::RenderWindow& window = g_pGame->GetWindow();
	window.setView(window.getDefaultView());
	sf::Vector2u ss = mBackgroundSprite.getTexture()->getSize();
	sf::Vector2u ws = window.getSize();
	mBackgroundSprite.setPosition(sf::Vector2f(ws.x / 2 - ss.x / 2, ws.y / 2 - ss.y / 2));
	window.draw(mBackgroundSprite);
}

// ====================================================================================================
// Update
// ====================================================================================================
bool TitleState::Update(sf::Time dt)
{
	mStateTime += dt;
	if (mStateTime >= sf::seconds(2.0f))
	{
		RequestStackPop();
		RequestStackPush(States::Menu);
		
	}
	return true;
}