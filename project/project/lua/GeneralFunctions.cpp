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
		LuaClasses::lua_scenenode_wrapper* GetSceneLayer(int iLayer)
		{
			if (iLayer >= g_pWorld->LayerCount)
			{
				return NULL;
			}

			SceneNode* pNode = g_pWorld->GetSceneLayer((World::Layer) iLayer);
			LuaClasses::lua_scenenode_wrapper* pWrapper = new LuaClasses::lua_scenenode_wrapper(pNode);

			return pWrapper;
		}

		// Create Entity
		LuaClasses::lua_entity_wrapper* CreateEntity(std::string classname)
		{
			Entity* pEntity = g_pWorld->CreateEntityByClassName(classname);

			LuaClasses::lua_entity_wrapper* pWrapper = new LuaClasses::lua_entity_wrapper(pEntity);
			pEntity->SetLuaObject(pWrapper);
			return pWrapper;
		}
	}
}

// ====================================================================================================
// Register Functions
// ====================================================================================================
void LuaFunctions::RegisterLuaFunctions()
{
	// General
	luabind::module(lua->State())
		[
			luabind::def("include", &LuaFunctions::include)
		];

	// world Module
	luabind::module(lua->State(), "world") [
		luabind::def("GetSceneLayer", &LuaFunctions::Module_World::GetSceneLayer),
		luabind::def("CreateEntity", &LuaFunctions::Module_World::CreateEntity)
	];
}