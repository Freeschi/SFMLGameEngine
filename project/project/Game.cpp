// ====================================================================================================
// Includes
// ====================================================================================================
#include "Includes.h"

// ====================================================================================================
// Definitions
// ====================================================================================================
const float Game::PlayerSpeed = 100.f;
TextureHolder textures;

// ====================================================================================================
// Game::Game
// Constructor of the Game class
// ====================================================================================================
Game::Game() : mWindow(sf::VideoMode(640, 480), "SFML Application"), mPlayerSprite(), mTexture(), mIsMovingUp(false), mIsMovingDown(false), mIsMovingLeft(false), mIsMovingRight(false), mWorld(mWindow)
{
	mPlayerSprite.setPosition(100.f, 100.f);
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
			ProcessInput();
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
// Game::ProcessInput
// ====================================================================================================
void Game::ProcessInput()
{
	CommandQueue& commands = mWorld.GetCommandQueue();
	sf::Event event;

	while (mWindow.pollEvent(event))
	{
		mPlayer.HandleEvent(event, commands);
		if (event.type == sf::Event::Closed)
			mWindow.close();
	}

	mPlayer.HandleRealtimeInput(commands);
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