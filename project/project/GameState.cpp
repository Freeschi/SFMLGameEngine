// ====================================================================================================
// Includes
// ====================================================================================================
#include "Includes.h"

// ====================================================================================================
// GameState
// ====================================================================================================
GameState::GameState(StateStack& stack) : State(stack)
{
	BuildScene();
}

// ====================================================================================================
// BuildScene
// ====================================================================================================
void GameState::BuildScene()
{
	if (g_pPlayer != NULL)
		delete g_pPlayer;
	g_pPlayer = new Player();
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
	g_pWorld->Update(dt, true);

	CommandQueue* commands = g_pWorld->GetCommandQueue();
	g_pPlayer->HandleRealtimeInput(commands);

	try
	{
		luabind::object eventcall = luabind::globals(lua->State())["event"]["Call"];
		luabind::call_function<void>(eventcall, "Update", dt);
	}
	catch (...)
	{
		lua->PrintErrorMessage("Tried to call Update event, but something went wrong.");
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