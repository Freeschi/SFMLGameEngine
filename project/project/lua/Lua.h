// ====================================================================================================
// Lua Includes
// ====================================================================================================
#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"
#include "luabind/luabind.hpp"

// ====================================================================================================
// Lua Libs
// ====================================================================================================
#pragma comment(lib, "lua/lib/luabind.lib")
#pragma comment(lib, "lua/lib/lua.lib")

// ====================================================================================================
// Lua Manager
// ====================================================================================================
#include <exception>
#include "luamanager/LuaManager.h"