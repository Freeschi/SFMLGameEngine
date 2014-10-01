// ====================================================================================================
// Includes
// ====================================================================================================
#include "Includes.h"
#include "Lua.h"
#include "lua/GeneralFunctions.h"
#include "lua/ClassWrappers.h"

// ====================================================================================================
// GameState
// ====================================================================================================
GameState::GameState(StateStack& stack) : State(stack)
{

}

// ====================================================================================================
// BuildScene
// ====================================================================================================
void GameState::BuildScene()
{
	if (g_pPlayer != NULL)
		delete g_pPlayer;

	g_pPlayer = new Player();

	LuaClasses::BuildScene();
}

// ====================================================================================================
// Draw
// ====================================================================================================
void GameState::Draw()
{
	g_pWorld->Draw();
}

// ====================================================================================================
// Update
// ====================================================================================================
bool GameState::Update(sf::Time dt)
{
	if (g_pPlayer == NULL)
	{
		BuildScene();
	}

	g_pWorld->Update(dt, true);

	CommandQueue* commands = g_pWorld->GetCommandQueue();

	if (g_pPlayer != NULL)
		g_pPlayer->HandleRealtimeInput(commands);

	try
	{
		if (g_pWorld->IsEntityRegistered(0))
		{
			lua->GetEvent("Update");
			lua->PushNumber(dt.asMilliseconds());
			lua->ProtectedCall(2, 0);
		}
	}
	catch (...)
	{
		lua->PrintErrorMessage("Tried to call Update event, but something went wrong.", true);
	}

	return true;
}

// ====================================================================================================
// Handle Events
// ====================================================================================================
bool GameState::HandleEvent(const sf::Event& event)
{
	// Game input handling
	CommandQueue* commands = g_pWorld->GetCommandQueue();
	g_pPlayer->HandleEvent(event, commands);

	// Escape pressed, trigger the pause screen
	

	return true;
}