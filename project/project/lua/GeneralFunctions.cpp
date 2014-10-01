// ====================================================================================================
// Includes
// ====================================================================================================
#include "../Includes.h"
#include "GeneralFunctions.h"
#include "ClassWrappers.h"

// ====================================================================================================
// include
// ====================================================================================================
void LuaFunctions::include(std::string file)
{
	char* currentpath = lua->DebugGetPath();
	luaL_checkstring(lua->State(), 1);

	char path[364];
	sprintf(path, "%s%s", currentpath, file.c_str());
	lua->IncludeFile(path);
}

// ====================================================================================================
// world-Module
// ====================================================================================================
namespace LuaFunctions
{
	namespace Module_World
	{
		// Probabbly broken
		// Untested!
		luabind::object GetSceneLayer(int iLayer)
		{
			if (iLayer >= g_pWorld->LAYER_COUNT)
			{
				lua->PushString("Invalid SceneLayer ID passed!");
				throw luabind::error(lua->State());
			}

			SceneNode* pNode = g_pWorld->GetSceneLayer((World::Layer) iLayer);
			return pNode->GetLuaObject()->LuaBindObject();
		}

		// Create Entity
		luabind::object CreateEntity(std::string classname)
		{
			Entity* pEntity = g_pWorld->CreateEntityByClassName(classname);
			return pEntity->GetLuaObject()->LuaBindObject();
		}
		
		// World Bounds
		sf::FloatRect GetBounds() { return g_pWorld->GetBounds(); }
		void SetBounds(sf::FloatRect b) { g_pWorld->SetBounds(b); }
	};

	namespace Module_Game
	{
		// HasFocus
		bool HasFocus()
		{
			return g_pGame->HasFocus();
		}
	}
}

// ====================================================================================================
// Register Functions
// ====================================================================================================
void LuaFunctions::RegisterLuaFunctions()
{
	// General
	luabind::module(lua->State()) [
		luabind::def("include", &LuaFunctions::include)
	];

	// world Module
	luabind::module(lua->State(), "world") [
		luabind::def("GetSceneLayer", &LuaFunctions::Module_World::GetSceneLayer),
		luabind::def("CreateEntity", &LuaFunctions::Module_World::CreateEntity),
		luabind::def("GetBounds", &LuaFunctions::Module_World::GetBounds),
		luabind::def("SetBounds", &LuaFunctions::Module_World::SetBounds)
	];

	// game Module
	luabind::module(lua->State(), "game")[
		luabind::def("HasFocus", &LuaFunctions::Module_Game::HasFocus)
	];
}