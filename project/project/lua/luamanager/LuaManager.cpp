// ====================================================================================================
// Includes
// ====================================================================================================
#include "Lua.h"

void DumpStack()
{
	lua_State* L = lua->State();
	int amount = lua->Top();
	printf("[LUA] Stack Dump: Currently %i item(s) in stack!\n", amount);

	for (int i = 1; i <= amount; i++)
	{
		printf("%i:\t%s\n", i, lua_typename(L, i));
	}
}

// ====================================================================================================
// Global Instance
// ====================================================================================================
LuaManager* lua = NULL;

// ====================================================================================================
// LuaManager
// ====================================================================================================
LuaManager::LuaManager() : m_pState(NULL), m_bSuccess(true) {}
void LuaManager::Init()
{
	// Create lua_State
	m_pState = luaL_newstate();
	if (m_pState == NULL)
	{
		m_bSuccess = false;
		printf("[LuaManager] luaL_newstate Failed: NULL pointer\n");
		return;
	}

	// Default Functions, Libs
	luaL_openlibs(m_pState);

	// Error Handling
	lua_atpanic(m_pState, LuaPanicHandler);

	// LuaBind
	luabind::open(m_pState);

	// Done
	printf("[LuaManager] Initialized Lua successfully\n");
	m_bSuccess = true;
}

// ====================================================================================================
// Call
// ====================================================================================================
void LuaManager::Call(int narg, int nresults)
{
	lua_State* L = State();

	// Traceback
	GetGlobal("debug");
	GetField("traceback");
	Remove(-2);
	int errindex = -narg - 2;
	lua_insert(L, errindex);

	// Call
	int status = lua_pcall(L, narg, nresults, errindex);
	m_bSuccess = (status == 0);

	if (!m_bSuccess)
	{
		char* err = GetString();
		if (err == NULL)
			err = "(unknown error)";
		throw LuaException(err);
	}
}
bool LuaManager::ProtectedCall(int narg, int nresults)
{
	try
	{
		Call(narg, nresults);
	}
	catch (LuaException& e)
	{
		PrintErrorMessage(const_cast<char*>(e.what()), true, true);
	}

	return m_bSuccess;
}

// ====================================================================================================
// Include File
// ====================================================================================================
bool LuaManager::IncludeFile(char* sPath)
{
	lua_State* L = State();

	// Load File
	int status = luaL_loadfile(L, sPath);
	m_bSuccess = (status == 0);

	// Check for errors
	if (!Success())
	{
		// Traceback
		lua->GetGlobal("debug");
		lua->GetField("traceback");
		lua->ProtectedCall(0, 1);
		lua->Remove(-3);
		lua->Remove(-2);

		// Error Message
		char eMsg[364];
		sprintf(eMsg, "%s\n%s", lua->GetString(-2), lua->GetString(-1));
		PrintErrorMessage(eMsg, true, true);

		lua->Pop(2);		
		return false;
	}

	// Execute File
	return ProtectedCall(0, LUA_MULTRET);
}

// ====================================================================================================
// Error Handling
// ====================================================================================================
int LuaPanicHandler(lua_State* L)
{
	// Message
	char* msg = const_cast<char*>(lua_tostring(L, -1));
	if (msg == NULL)
		msg = "(error object invalid)";

	// Trace
	lua->GetGlobal("debug");
	lua->GetField("traceback");
	lua->ProtectedCall(0, 1);
	lua->Remove(-3);
	lua->Remove(-2);

	std::string msgs = msg;
	throw LuaException(msgs);

	return 0;
}
void LuaManager::CheckForLuaErrors(int iErrorIndex)
{
	lua_State* L = State();
	if (lua_isstring(L, -1))
	{
		// Message
		char* msg = const_cast<char*>(lua_tostring(L, -1));
		if (msg == NULL)
			msg = "(error object invalid)";

		lua->GetGlobal("debug");
		lua->GetField("traceback");
		lua->ProtectedCall(0, 1);
		lua->Remove(-3);
		lua->Remove(-2);

		throw LuaException(msg, lua->GetString());
	}
}

// ====================================================================================================
// Error Handling
// ====================================================================================================
bool LuaManager::Success()
{
	return m_bSuccess;
}
void LuaManager::PrintErrorMessage(char* sErrorMsg, bool bDoNotTriggerLuaError, bool bDoNotCreateTraceback)
{
	lua_State* L = State();

	if (!bDoNotTriggerLuaError)
		luaL_error(L, sErrorMsg);
	else
		printf("[LUA] %s\n", sErrorMsg);

	if (!bDoNotCreateTraceback)
	{
		GetGlobal("debug");
		GetField("traceback");
		ProtectedCall(0, 1);
		Remove(-3);
		Remove(-2);

		printf("%s\n", lua_tostring(L, -1));
	}
}