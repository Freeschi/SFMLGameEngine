// ====================================================================================================
// Includes
// ====================================================================================================
#include "../../Includes.h"
#include "GeneralFunctions.h"
#include "ClassWrappers.h"

// ====================================================================================================
// Enums
// ====================================================================================================
namespace LuaClasses
{
	void RegisterEnums()
	{
		luabind::object g = luabind::globals(lua->State());

		// Scene LAYER_
		g["LAYER_COUNT"] = g_pWorld->LAYER_COUNT;
		g["LAYER_MAP"] = g_pWorld->LAYER_MAP;
		g["LAYER_GENERAL"] = g_pWorld->LAYER_GENERAL;
		g["LAYER_FOREGROUND"] = g_pWorld->LAYER_FOREGROUND;
		g["LAYER_HUD"] = g_pWorld->LAYER_HUD;

		// Move MOVEMENT_
		g["MOVEMENT_WALK_RIGHT"] = MOVEMENT_WALK_RIGHT;
		g["MOVEMENT_WALK_LEFT"] = MOVEMENT_WALK_LEFT;
		g["MOVEMENT_WALK_UP"] = MOVEMENT_WALK_UP;
		g["MOVEMENT_WALK_DOWN"] = MOVEMENT_WALK_DOWN;
	}
}