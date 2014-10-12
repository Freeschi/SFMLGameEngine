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

	lua->GetEvent("DrawHUD");
	lua->ProtectedCall(1);
	lua->Pop(2);
}

// ====================================================================================================
// Update
// ====================================================================================================
void stackDump(lua_State *L) {
	int i;
	int top = lua_gettop(L);
	printf("[Memory: %i kb] [Stack: %i] ", lua_gc(L, LUA_GCCOUNT, 0), top);
	for (i = 1; i <= top; i++) {  /* repeat for each level */
		int t = lua_type(L, i);
		switch (t) {

		case LUA_TSTRING:  /* strings */
			printf("`%s'", lua_tostring(L, i));
			break;

		case LUA_TBOOLEAN:  /* booleans */
			printf(lua_toboolean(L, i) ? "true" : "false");
			break;

		case LUA_TNUMBER:  /* numbers */
			printf("%g", lua_tonumber(L, i));
			break;

		default:  /* other values */
			printf("%s", lua_typename(L, t));
			break;

		}
		printf("  ");  /* put a separator */
	}
	printf("\n");  /* end the listing */
}

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


	if (!g_pGame->IsPaused())
	{
		//lua->GetEvent("Update");
		//lua->PushNumber(dt.asMilliseconds());
		//lua->ProtectedCall(1, 0);
	}

	char buf[256];
	sprintf(buf, "Lua Memory: %i kb - Stack Size: %i", lua_gc(lua->State(), LUA_GCCOUNT, 0), lua->Top());
	SetConsoleTitle(buf);

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