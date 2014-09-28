// ====================================================================================================
// Includes
// ====================================================================================================
#include "Includes.h"

// ====================================================================================================
// Menu State
// ====================================================================================================
MenuState::MenuState(StateStack& stack) : State(stack)
{
	sf::Texture& texture = g_pWorld->GetTextureHolder()->Get(Textures::TitleScreen);
	sf::Font& font = g_pWorld->GetFontHolder()->Get(Fonts::Main);

	mBackgroundSprite.setTexture(texture);

	// A simple menu demonstration
	sf::Text playOption;
	playOption.setFont(font);
	playOption.setString("Play");
	UTIL::CenterOrigin(playOption);
	playOption.setPosition(g_pWorld->GetView()->getSize() / 2.f);
	mOptions.push_back(playOption);

	sf::Text exitOption;
	exitOption.setFont(font);
	exitOption.setString("Exit");
	UTIL::CenterOrigin(exitOption);
	exitOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 30.f));
	mOptions.push_back(exitOption);
}

// ====================================================================================================
// Option Text
// ====================================================================================================
void MenuState::UpdateOptionText()
{
	if (mOptions.empty())
		return;

	FOREACH(sf::Text& text, mOptions)
		text.setColor(sf::Color::White);

	if (mOptionIndex < 0 || mOptionIndex > mOptions.size())
		mOptionIndex = mOptions.size();
	mOptions[mOptionIndex].setColor(sf::Color::Red);
}


void MenuState::Draw()
{
	sf::RenderWindow& window = g_pGame->GetWindow();

	window.setView(window.getDefaultView());
	window.draw(mBackgroundSprite);

	FOREACH(const sf::Text& text, mOptions)
		window.draw(text);
}

bool MenuState::Update(sf::Time)
{
	return true;
}

bool MenuState::HandleEvent(const sf::Event& event)
{
	// The demonstration menu logic
	if (event.type != sf::Event::KeyPressed)
		return false;

	if (event.key.code == sf::Keyboard::Return)
	{
		if (mOptionIndex == Play)
		{
			RequestStackPop();
			RequestStackPush(States::Game);
		}
		else if (mOptionIndex == Exit)
		{
			RequestStackPop();
		}
	}

	else if (event.key.code == sf::Keyboard::Up)
	{
		if (mOptionIndex > 0)
			mOptionIndex--;
		else
			mOptionIndex = mOptions.size() - 1;

		UpdateOptionText();
	}

	else if (event.key.code == sf::Keyboard::Down)
	{
		if (mOptionIndex < mOptions.size() - 1)
			mOptionIndex++;
		else
			mOptionIndex = 0;

		UpdateOptionText();
	}

	return true;
}