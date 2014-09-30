// ====================================================================================================
// Includes
// ====================================================================================================
#include "../../Includes.h"
#include "GeneralFunctions.h"
#include "ClassWrappers.h"
using namespace LuaFunctions;

// ====================================================================================================
// Class Definitions
// ====================================================================================================
namespace LuaClasses
{
	// ====================================================================================================
	// Base Class Wrapper
	// ====================================================================================================
	// Valid-Check
	void base_class_wrapper::CheckValid()
	{
		if (!IsValid())
		{
			char buf[350];
			sprintf(buf, "Attempted to use NULL %s!", m_sClassName.c_str());
			lua->PushString(buf);
			throw luabind::error(lua->State());
		}
	}

	// ====================================================================================================
	// SceneNode
	// ====================================================================================================
	lua_scenenode_wrapper::lua_scenenode_wrapper(SceneNode* pSceneNode) : m_pSceneNode(pSceneNode)
	{
		_base_class_wrapper_name("SceneNode");
	}

	// SetPosition
	void lua_scenenode_wrapper::SetPosition(sf::Vector2f pos)
	{
		m_pSceneNode->setPosition(pos);
	}

	// ====================================================================================================
	// Entity
	// ====================================================================================================
	lua_entity_wrapper::lua_entity_wrapper(Entity* pEntity) : m_pEntity(pEntity), lua_scenenode_wrapper((SceneNode*)pEntity)
	{ 
		_base_class_wrapper_name("Entity");
	};
	lua_entity_wrapper::~lua_entity_wrapper() { };

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
};

// ====================================================================================================
// Register Class Wrappers
// ====================================================================================================
void LuaClasses::RegisterClassWrappers()
{	
	// Vector2
	luabind::module(lua->State()) [
		luabind::class_<sf::Vector2f>("Vector2")
			.def(luabind::constructor<>())
			.def(luabind::constructor<float, float>())
			.property("x", &sf::Vector2f::x)
			.property("y", &sf::Vector2f::y)
	];

	// store info
	luabind::module(lua->State())[
		luabind::class_<LuaClasses::base_store_info>("base_store_info")
			.def("GetTable", &LuaClasses::base_store_info::GetTable),
		luabind::class_<LuaClasses::base_class_wrapper, LuaClasses::base_store_info>("base_class_wrapper")
			.def("IsValid", &LuaClasses::base_class_wrapper::IsValid)
	];

	// sf
	luabind::module(lua->State()) [
		luabind::class_<sf::Transformable>("sfTransformable")
	];
	luabind::module(lua->State())[
		luabind::class_<sf::Drawable>("sfDrawable")
	];
	luabind::module(lua->State())[
		luabind::class_<sf::NonCopyable>("NonCopyable")
	];

	luabind::module(lua->State()) [
		luabind::class_<LuaClasses::lua_scenenode_wrapper, LuaClasses::base_class_wrapper>("SceneNode")
		.def(luabind::constructor<SceneNode*>())
		.def("GetPosition", &LuaClasses::lua_scenenode_wrapper::GetWorldPosition)
		.def("SetPosition", &LuaClasses::lua_scenenode_wrapper::SetPosition)
	];

	// Entity
	luabind::module(lua->State())
	[
		luabind::class_<LuaClasses::lua_entity_wrapper, LuaClasses::lua_scenenode_wrapper>("Entity")
		.def(luabind::constructor<Entity*>())
		.def("UpdateCurrent", &Entity::UpdateCurrent)
		.def("GetClassName", &LuaClasses::lua_entity_wrapper::GetClassName)
		.def("Activate", &LuaClasses::lua_entity_wrapper::Activate)
		.def("Index", &LuaClasses::lua_entity_wrapper::Index)
	];


	/*// SceneNode
	luabind::module(lua->State())[
	luabind::class_<SceneNode>("SceneNode")
	.def(luabind::constructor<>())
	.def("GetPosition", &SceneNode::GetWorldPosition)
	];

	// Entity
	luabind::module(lua->State())
	[
	luabind::class_<Entity>("Entity")
	.def(luabind::constructor<>())
	.def("UpdateCurrent", &Entity::UpdateCurrent)
	.def("GetClassName", &Entity::GetClassName)
	];

	luabind::module(lua->State())
	[
	luabind::class_<Aircraft, Entity>("Aircraft")
	];*/
}