// ====================================================================================================
// Includes
// ====================================================================================================
#include "Includes.h"

// ====================================================================================================
// Title State
// ====================================================================================================
TitleState::TitleState(StateStack& stack) : State(stack), mShowText(true), mTextEffectTime(sf::Time::Zero)
{
	mBackgroundSprite.setTexture(g_pWorld->GetTextureHolder()->Get("TitleScreen"));

	mText.setFont(g_pWorld->GetFontHolder()->Get("Main"));
	mText.setString("Press any key to start");
	UTIL::CenterOrigin(mText);
	mText.setPosition(g_pWorld->GetView()->getSize() / 2.f);
}

// ====================================================================================================
// Handle Event
// ====================================================================================================
bool TitleState::HandleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		RequestStackPop();
		RequestStackPush(States::Menu);
	}

	return true;
}

// ====================================================================================================
// Draw
// ====================================================================================================
void TitleState::Draw()
{
	sf::RenderWindow& window = g_pGame->GetWindow();
	window.setView(window.getDefaultView());
	window.draw(mBackgroundSprite);

	if (mShowText)
		window.draw(mText);
}

// ====================================================================================================
// Update
// ====================================================================================================
bool TitleState::Update(sf::Time dt)
{
	mTextEffectTime += dt;
	if (mTextEffectTime >= sf::seconds(0.5f))
	{
		mShowText = !mShowText;
		mTextEffectTime = sf::Time::Zero;
	}
	return true;
}