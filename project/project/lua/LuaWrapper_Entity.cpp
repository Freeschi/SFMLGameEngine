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

	// GetPosition
	sf::Vector2f lua_scenenode_wrapper::GetPosition()
	{
		CheckValid();
		return m_pSceneNode->getPosition();
	}

	// SetPosition
	void lua_scenenode_wrapper::SetPosition(sf::Vector2f pos)
	{
		CheckValid();
		m_pSceneNode->setPosition(pos);
	}

	// Childs & Parents
	void lua_scenenode_wrapper::lua_AttachChild(lua_scenenode_wrapper* pWrapper)
	{
		CheckValid();
		pWrapper->CheckValid();

		m_pSceneNode->AttachChild(pWrapper->m_pSceneNode);
	}
	void lua_scenenode_wrapper::lua_DetachChild(lua_scenenode_wrapper* pWrapper)
	{
		CheckValid();
		pWrapper->CheckValid();

		m_pSceneNode->DetachChild(pWrapper->m_pSceneNode);
	}
	

	// ====================================================================================================
	// Entity
	// ====================================================================================================
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
	
	// Parent
	luabind::object lua_scenenode_wrapper::lua_GetParent()
	{
		CheckValid();

		SceneNode* pParent = m_pSceneNode->GetParent();
		if (pParent != NULL)
		{
			LuaClasses::base_class_wrapper* wrapper = pParent->GetLuaObject();

			if (pParent->IsEntity())
				return luabind::object(lua->State(), (LuaClasses::lua_entity_wrapper*) wrapper);

			// hopefully this actually is a scenenode
			// check if its a scene layer
			// scene layers tend to crash TO-DO: figure out why
			for (int i = 0; i < g_pWorld->LayerCount; i++)
			{
				if (pParent == g_pWorld->GetSceneLayer((World::Layer) i))
					return lua_nil;
			}
			return luabind::object(lua->State(), (LuaClasses::lua_scenenode_wrapper*) wrapper);
		}

		return lua_nil;
	}
	void lua_scenenode_wrapper::lua_SetParent(lua_scenenode_wrapper* pParent)
	{
		CheckValid();

		m_pSceneNode->SetParent(pParent->m_pSceneNode);
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

	// SceneNode
	luabind::module(lua->State()) [
		luabind::class_<LuaClasses::lua_scenenode_wrapper, LuaClasses::base_class_wrapper>("SceneNode")
		.def(luabind::constructor<SceneNode*>())
		.def("GetPosition", &LuaClasses::lua_scenenode_wrapper::GetPosition)
		.def("SetPosition", &LuaClasses::lua_scenenode_wrapper::SetPosition)
		.def("AttachChild", &LuaClasses::lua_scenenode_wrapper::lua_AttachChild)
		.def("DetachChild", &LuaClasses::lua_scenenode_wrapper::lua_DetachChild)
		.def("GetParent", &LuaClasses::lua_scenenode_wrapper::lua_GetParent)
		.def("SetParent", &LuaClasses::lua_scenenode_wrapper::lua_SetParent)
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
}