// ====================================================================================================
// Includes
// ====================================================================================================
#pragma warning(disable: 4540)
#pragma warning(disable: 4584)
#include "../../Includes.h"
using namespace LuaFunctions;

class lua_scenenode_wrapper : public SceneNode, public luabind::wrap_base
{
public:
	typedef std::unique_ptr<SceneNode> Ptr;
	Ptr m_pSceneNode;
	lua_scenenode_wrapper(SceneNode* pSceneNode) : m_pSceneNode(pSceneNode) {}
};

class lua_entity_wrapper : public Entity, public lua_scenenode_wrapper, public luabind::wrap_base
{
public:
	typedef std::unique_ptr<Entity> Ptr;
	Ptr m_pEntity;
	lua_entity_wrapper(Entity* pEntity) : m_pEntity(pEntity), lua_scenenode_wrapper((SceneNode*) pEntity) { };

	void Activate()
	{
		Ptr mSelf(this);
		g_pWorld->GetSceneLayer(g_pWorld->Air)->AttachChild(std::move(mSelf));
	}

	std::string GetClassName() { return m_pEntity->GetClassName(); }
};

lua_entity_wrapper* create_entity(std::string classname)
{
	lua_entity_wrapper* ent = new lua_entity_wrapper(g_pWorld->CreateEntityByClassName(classname));
	return ent;
}

namespace LuaFunctions
{
	namespace Module_World
	{
		lua_scenenode_wrapper* GetSceneLayer(int iLayer)
		{
			if (iLayer >= g_pWorld->LayerCount)
			{
				return NULL;
			}

			SceneNode* pNode = g_pWorld->GetSceneLayer((World::Layer) iLayer);
			printf("pNode = %i\n", pNode);
			lua_scenenode_wrapper* pWrapper = new lua_scenenode_wrapper(pNode);
			printf("pWrapper = %i\n", pWrapper);

			return pWrapper;
		}
	}
}


void LuaFunctions::RegisterClassWrapper()
{	
	// Vector2
	luabind::module(lua->State()) [
		luabind::class_<sf::Vector2f>("Vector2")
			.def(luabind::constructor<>())
			.def(luabind::constructor<float, float>())
			.property("x", &sf::Vector2f::x)
			.property("y", &sf::Vector2f::y)
	];

	// SceneNode
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
		luabind::class_<lua_scenenode_wrapper>("SceneNode")
			.def(luabind::constructor<SceneNode*>())
			.def("GetPosition", &lua_scenenode_wrapper::GetWorldPosition)
	];

	// Entity
	luabind::module(lua->State())
	[
		luabind::class_<lua_entity_wrapper, lua_scenenode_wrapper>("Entity")
			.def(luabind::constructor<Entity*>())
			.def("UpdateCurrent", &Entity::UpdateCurrent)
			.def("GetClassName", &lua_entity_wrapper::GetClassName)
			.def("Activate", &lua_entity_wrapper::Activate)
	];

	// world Module
	luabind::module(lua->State(), "world")[
		luabind::def("GetSceneLayer", &LuaFunctions::Module_World::GetSceneLayer)
	];

	/*// sf::Time
	luabind::module(lua->State()) [
	luabind::class_<sf::Time>("sfTime")
	.def(luabind::constructor<>())
	.def("asSeconds", &sf::Time::asSeconds)
	];

	

	// Entity
	luabind::module(lua->State()) [
	luabind::class_<Entity, LuaWrapper_Entity, SceneNode>("Entity")
	.def(luabind::constructor<>())
	.def(luabind::constructor<std::string>())
	.def("GetClassName", &Entity::GetClassName)
	.def("UpdateCurrent", &Entity::UpdateCurrent, &LuaWrapper_Entity::default_UpdateCurrent)
	];*/

	// create entity
	luabind::module(lua->State()) [
		luabind::def("create_entity", create_entity)
	];
}