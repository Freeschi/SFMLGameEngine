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
	// SceneNode
	// ====================================================================================================
	lua_scenenode_wrapper::lua_scenenode_wrapper(SceneNode* pSceneNode) : m_pSceneNode(pSceneNode) {}

	// SetPosition
	void lua_scenenode_wrapper::SetPosition(sf::Vector2f pos)
	{
		m_pSceneNode->setPosition(pos);
	}

	// ====================================================================================================
	// Entity
	// ====================================================================================================
	lua_entity_wrapper::lua_entity_wrapper(Entity* pEntity) : m_pEntity(pEntity), lua_scenenode_wrapper((SceneNode*)pEntity) { };
	lua_entity_wrapper::~lua_entity_wrapper() { };

	// Valid-Check
	void lua_entity_wrapper::Invalidate()
	{
		m_pEntity = NULL;
	}
	void lua_entity_wrapper::Validate()
	{
		if (m_pEntity == NULL)
		{
			lua->PushString("Attempted to use NULL entity!");
			throw luabind::error(lua->State());
		}
	}

	// Activate
	void lua_entity_wrapper::Activate()
	{
		Validate();
		g_pWorld->GetSceneLayer(g_pWorld->Air)->AttachChild(m_pEntity);
	}

	// GetClassName
	std::string lua_entity_wrapper::GetClassName()
	{
		Validate();
		return m_pEntity->GetClassName();
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
		];

	

	luabind::module(lua->State()) [
		luabind::class_<LuaClasses::lua_scenenode_wrapper>("SceneNodeWrap")
		.def(luabind::constructor<SceneNode*>())
		.def("GetPosition", &LuaClasses::lua_scenenode_wrapper::GetWorldPosition)
		.def("SetPosition", &LuaClasses::lua_scenenode_wrapper::SetPosition)
	];

	// Entity
	luabind::module(lua->State())
	[
		luabind::class_<LuaClasses::lua_entity_wrapper, LuaClasses::lua_scenenode_wrapper>("EntityWrap")
		.def(luabind::constructor<Entity*>())
		.def("UpdateCurrent", &Entity::UpdateCurrent)
		.def("GetClassName", &LuaClasses::lua_entity_wrapper::GetClassName)
		.def("Activate", &LuaClasses::lua_entity_wrapper::Activate)
	];
}