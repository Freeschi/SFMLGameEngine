// ====================================================================================================
// Includes
// ====================================================================================================
#include "Includes.h"
#include "Lua.h"
#include "lua/GeneralFunctions.h"
#include "lua/ClassWrappers.h"

// ====================================================================================================
// Definitions
// ====================================================================================================
Game* g_pGame = NULL;

// ====================================================================================================
// Game::Game
// Constructor of the Game class
// ====================================================================================================
Game::Game() : mWindow(sf::VideoMode(1280, 720), "Freeschi"), mStateStack(NULL), m_iFPS(0)
{
	// Config
	g_pConfig = new Config();

	// Lua
	lua = new LuaManager();
	lua->Init();

	// Functions
	LuaFunctions::RegisterLuaFunctions();

	// Classes
	LuaClasses::RegisterClassWrappers();

	// AutoRefresh
	LuaFunctions::Autorefresh::Init();

	// main.lua
	if (!lua->IncludeFile("lua/main.lua"))
	{
		printf("\n[Lua] Proper startup not possible, because lua/main.lua was not found or failed to load!\n");
		printf("[Game] Please make sure the lua environment is setup correctly!\n\n");

		throw std::string("Scripting errors");
		return;
	}
	lua->AddToFileList("lua/main.lua");

	// call init function
	lua->GetGlobal("_main");
	if (!lua->ProtectedCall())
	{
		printf("\n[Lua] Unable to call _main()\n");
		printf("[Game] Please make sure the lua environment is setup correctly!\n\n");

		throw std::string("Scripting errors");
		return;
	}

	// Init World
	g_pWorld = new World(mWindow);
	g_pWorld->LoadTextures();

	// Registered Entity Classes
	REGISTER_ENTITY_CLASS(sprite_node, SpriteNode());
	REGISTER_ENTITY_CLASS(player, PlayerEntity());

	// Pause
	flLastPause = 0.0f;
	m_bIsPaused = false;

	// States
	mStateStack = new StateStack();
	RegisterStates();
	mStateStack->PushState(States::Menu);

	// Build Scene
	g_pWorld->BuildScene();

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
		timeSinceLastUpdate += clock.restart();

		ProcessEvents();
		
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			
			ProcessEvents();
			Update(TimePerFrame);
			mStateStack->Update(TimePerFrame);
		}
		 
		UpdateStats(timeSinceLastUpdate);
		
		Render();

		Sleep(1); // this needs to be better
	}
}

// ====================================================================================================
// Game::Exit
// ====================================================================================================
void Game::Exit()
{
	printf("----------------------------------------------------\n");
	printf("[Game] Exiting..\n");

	lua->GetEvent("OnShutdown");
	lua->ProtectedCall(1, 0);

	mWindow.close();

	LuaFunctions::Autorefresh::Destroy();
	lua->Destroy();
}

// ====================================================================================================
// FPS Counter
// ====================================================================================================
int mStatisticsNumFrames = 1000;
sf::Clock framecounter;
void Game::UpdateStats(sf::Time dt)
{
	mStatisticsNumFrames += 1;
	if (framecounter.getElapsedTime().asSeconds() >= 1.0f)
	{
		framecounter.restart();
		m_iFPS = mStatisticsNumFrames;
		mStatisticsNumFrames = 0;
	}
}
int Game::GetFPS() { return m_iFPS; }

// ====================================================================================================
// Game::ProcessEvents
// ====================================================================================================
void Game::ProcessEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		mStateStack->HandleEvent(event);

		switch (event.type)
		{
			case sf::Event::Closed:
				Exit();
				break;
			case sf::Event::GainedFocus:
				m_bHasFocus = true;
				lua->GetEvent("OnWindowLostFocus");
				lua->ProtectedCall(1, 0);
				break;
			case sf::Event::LostFocus:
				m_bHasFocus = false;
				lua->GetEvent("OnWindowGainedFocus");
				lua->ProtectedCall(1, 0);
				break;
		};
	}
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
// Game::RegisterStates
// ====================================================================================================
void Game::RegisterStates()
{
	mStateStack->RegisterState<TitleState>(States::Title);
	mStateStack->RegisterState<MenuState>(States::Menu);
	mStateStack->RegisterState<LoadingState>(States::Loading);
	mStateStack->RegisterState<GameState>(States::Game);
	mStateStack->RegisterState<PauseState>(States::Pause);
}

// ====================================================================================================
// Game::Update
// ====================================================================================================
void Game::Update(sf::Time deltaTime)
{
	g_pWorld->Update(deltaTime, HasFocus());
	LuaFunctions::Autorefresh::Update();
}

// ====================================================================================================
// Game::Render
// ====================================================================================================
void Game::Render()
{
	mWindow.clear();
	g_pWorld->Draw();
	mStateStack->Draw();

	mWindow.setView(mWindow.getDefaultView());
	mWindow.display();
}


