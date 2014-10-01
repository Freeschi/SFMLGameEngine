// ====================================================================================================
// Includes
// ====================================================================================================
#include "../../Includes.h"
#include "GeneralFunctions.h"
#include "ClassWrappers.h"

// ====================================================================================================
// SceneNode
// ====================================================================================================
namespace LuaClasses
{
	lua_scenenode_wrapper::lua_scenenode_wrapper(SceneNode* pSceneNode) : m_pSceneNode(pSceneNode)
	{
		_base_init("SceneNode");
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
	void lua_scenenode_wrapper::AttachChild(lua_scenenode_wrapper* pWrapper)
	{
		CheckValid();
		pWrapper->CheckValid();

		m_pSceneNode->AttachChild(pWrapper->m_pSceneNode);
	}
	void lua_scenenode_wrapper::DetachChild(lua_scenenode_wrapper* pWrapper)
	{
		CheckValid();
		pWrapper->CheckValid();

		m_pSceneNode->DetachChild(pWrapper->m_pSceneNode);
	}
	luabind::object lua_scenenode_wrapper::GetParent()
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
	void lua_scenenode_wrapper::SetParent(lua_scenenode_wrapper* pParent)
	{
		CheckValid();

		m_pSceneNode->SetParent(pParent->m_pSceneNode);
	}

	/*
	 * Register
	 */
	void RegisterSceneNode()
	{
		// SceneNode
		luabind::module(lua->State()) [
			luabind::class_<LuaClasses::lua_scenenode_wrapper, LuaClasses::base_class_wrapper>("SceneNode")
				.def(luabind::constructor<SceneNode*>())
				.def("GetPosition", &LuaClasses::lua_scenenode_wrapper::GetPosition)
				.def("SetPosition", &LuaClasses::lua_scenenode_wrapper::SetPosition)
				.def("AttachChild", &LuaClasses::lua_scenenode_wrapper::AttachChild)
				.def("DetachChild", &LuaClasses::lua_scenenode_wrapper::DetachChild)
				.def("GetParent", &LuaClasses::lua_scenenode_wrapper::GetParent)
				.def("SetParent", &LuaClasses::lua_scenenode_wrapper::SetParent)
		];
	}
};