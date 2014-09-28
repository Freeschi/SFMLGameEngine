// ====================================================================================================
// Includes
// ====================================================================================================
#include "Includes.h"

// ====================================================================================================
// Definitions
// ====================================================================================================
const float Game::PlayerSpeed = 100.f;
Game* g_pGame = NULL;

// ====================================================================================================
// Game::Game
// Constructor of the Game class
// ====================================================================================================
Game::Game() : mWindow(sf::VideoMode(640, 480), "SFML Application"), mPlayerSprite(), mTexture(), mIsMovingUp(false), mIsMovingDown(false), mIsMovingLeft(false), mIsMovingRight(false)
{
	mPlayerSprite.setPosition(100.f, 100.f);

	// Lua
	lua = new LuaManager();
	lua->Init();

	// main.lua
	if (!lua->IncludeFile("lua/main.lua"))
	{
		printf("\n[Lua] Proper startup not possible, because lua/main.lua was not found!\n");
		printf("[Game] Please make sure the lua environment is setup correctly!\n\n");
		return;
	}

	// call init function
	lua->GetGlobal("_main");
	if (!lua->ProtectedCall())
	{
		printf("\n[Lua] Unable to call _main()\n");
		printf("[Game] Please make sure the lua environment is setup correctly!\n\n");
		return;
	}

	// Init World
	g_pWorld = new World(mWindow);
	g_pWorld->LoadTextures();
	g_pWorld->BuildScene();

	REGISTER_ENTITY_CLASS(aircraft_eagle, Aircraft(Aircraft::Eagle));
	REGISTER_ENTITY_CLASS(aircraft_raptor, Aircraft(Aircraft::Raptor));

	// Done
	OnFullyInitialized();
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
	CommandQueue* commands = g_pWorld->GetCommandQueue();
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
// Game::OnFullyInitialized
// ====================================================================================================
void Game::OnFullyInitialized()
{
	// Lua event
	lua->GetEvent("OnGameInitialized");
	lua->ProtectedCall(1);
}

// ====================================================================================================
// Game::Update
// ====================================================================================================
void Game::Update(sf::Time deltaTime)
{
	g_pWorld->Update(deltaTime, HasFocus());
}

// ====================================================================================================
// Game::Render
// ====================================================================================================
void Game::Render()
{
	mWindow.clear();
	g_pWorld->Draw();

	mWindow.setView(mWindow.getDefaultView());
	mWindow.display();
}