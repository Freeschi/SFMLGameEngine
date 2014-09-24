// ====================================================================================================
// Includes
// ====================================================================================================
#include "Includes.h"

const float Game::PlayerSpeed = 100.f;

// ====================================================================================================
// Game::Game
// Constructor of the Game class
// ====================================================================================================
TextureHolder textures;
Game::Game() : mWindow(sf::VideoMode(640, 480), "SFML Application"), mPlayer(), mTexture(), mIsMovingUp(false), mIsMovingDown(false), mIsMovingLeft(false), mIsMovingRight(false), mWorld(mWindow)
{
	mPlayer.setPosition(100.f, 100.f);
}

// ====================================================================================================
// Game::Run
// ====================================================================================================
void Game::Run()
{
	sf::Clock clock;
	sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		ProcessEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			ProcessEvents();
			Update(TimePerFrame);
		}
		Render();
	}
}

// ====================================================================================================
// Game::ProcessEvents
// ====================================================================================================
void Game::ProcessEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				mWindow.close();
				break;
			case sf::Event::KeyPressed:
				HandlePlayerInput(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				HandlePlayerInput(event.key.code, false);
				break;
			case sf::Event::GainedFocus:
				m_bHasFocus = true;
				printf("[Game] Gained focus\n");
				break;
			case sf::Event::LostFocus:
				m_bHasFocus = false;
				printf("[Game] Lost focus\n");
				break;
		};
	}
}

// ====================================================================================================
// Game::HandlePlayerInput
// ====================================================================================================
void Game::HandlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W)
		mIsMovingUp = isPressed;
	else if (key == sf::Keyboard::S)
		mIsMovingDown = isPressed;
	else if (key == sf::Keyboard::A)
		mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		mIsMovingRight = isPressed;
}

// ====================================================================================================
// Game::Update
// ====================================================================================================
void Game::Update(sf::Time deltaTime)
{
	mWorld.Update(deltaTime, HasFocus());
}

// ====================================================================================================
// Game::Render
// ====================================================================================================
void Game::Render()
{
	mWindow.clear();
	mWorld.Draw();

	mWindow.setView(mWindow.getDefaultView());
	mWindow.display();
}