// ====================================================================================================
// Includes
// ====================================================================================================
#include "../../Includes.h"
#include "GeneralFunctions.h"
#include "ClassWrappers.h"

// ====================================================================================================
// Entity
// ====================================================================================================
namespace LuaClasses
{
	lua_entity_wrapper::lua_entity_wrapper(Entity* pEntity) : lua_scenenode_wrapper((SceneNode*)pEntity)
	{ 
		m_pEntity = pEntity;
		_base_class_wrapper_name("Entity");
	};
	lua_entity_wrapper::~lua_entity_wrapper() { };

	// OnInvalidated
	void lua_entity_wrapper::OnInvalidated()
	{
		if (m_pEntity != NULL)
		{
			// Call OnEntityRemoved event
			try
			{
				luabind::object eventcall = luabind::globals(lua->State())["event"]["Call"];
				luabind::call_function<void>(eventcall, "OnEntityRemoved", this);
			}
			catch (...)
			{
				lua->PrintErrorMessage("Tried to call OnEntityRemoved event, but something went wrong.");
			}
		}

		m_pEntity = NULL;
	}

	// Activate
	void lua_entity_wrapper::Activate()
	{
		CheckValid();
		g_pWorld->GetSceneLayer(g_pWorld->Air)->AttachChild(m_pEntity);
	}

	// GetClassName
	std::string lua_entity_wrapper::GetClassName()
	{
		CheckValid();
		return m_pEntity->GetClassName();
	}

	// Index
	int lua_entity_wrapper::Index()
	{
		CheckValid();
		return g_pWorld->GetEntityIndex(m_pEntity);
	}

	/*
	 * Register
	 */
	void RegisterEntity()
	{
		luabind::module(lua->State()) [
			luabind::class_<LuaClasses::lua_entity_wrapper, LuaClasses::lua_scenenode_wrapper>("Entity")
			.def(luabind::constructor<Entity*>())
			.def("UpdateCurrent", &Entity::UpdateCurrent)
			.def("GetClassName", &LuaClasses::lua_entity_wrapper::GetClassName)
			.def("Activate", &LuaClasses::lua_entity_wrapper::Activate)
			.def("Index", &LuaClasses::lua_entity_wrapper::Index)
		];
	}
};