// ====================================================================================================
// Includes
// ====================================================================================================
#pragma warning(disable: 4540)
#pragma warning(disable: 4584)
#include "../../Includes.h"
using namespace LuaFunctions;

// ====================================================================================================
// SceneNode Wrapper
// ====================================================================================================
class LuaWrapper_SceneNode : public SceneNode, public luabind::wrap_base
{
public:
	LuaWrapper_SceneNode() : SceneNode()
	{
		printf("SceneNode::SceneNode\n");
	}
};

// ====================================================================================================
// Entity Wrapper
// ====================================================================================================
class LuaWrapper_Entity : public Entity, public LuaWrapper_SceneNode, public luabind::wrap_base
{
public:
	LuaWrapper_Entity(std::string classname) : Entity(classname), LuaWrapper_SceneNode()
	{
		printf("Entity::Entity\n");
	}
	LuaWrapper_Entity() : Entity("lua_base_entity"), LuaWrapper_SceneNode()
	{
		printf("Entity::Entity\n");
	}

	virtual void UpdateCurrent(sf::Time df)
	{
		printf("Entity::Update\n");
		//call<void>("UpdateCurrent");
	}

	static void default_UpdateCurrent(Entity* ptr, sf::Time df)
	{
		printf("default\n");
		return ptr->Entity::UpdateCurrent(df);
	}
};

LuaWrapper_Entity* create_entity(std::string classname)
{
	LuaWrapper_Entity* pEntity = new LuaWrapper_Entity();

	SceneNode::Ptr ptr((Entity*) pEntity);
	g_pWorld->GetSceneLayer(g_pWorld->Air)->AttachChild(std::move(ptr));

	return pEntity;
}












class lua_entity_wrapper : public Entity, public luabind::wrap_base
{
public:
	lua_entity_wrapper(std::string ss) : Entity(ss) { };
	lua_entity_wrapper() : Entity("lua_base_entity") { };

	void Activate()
	{
		SceneNode::Ptr ptr((Entity*)this);
		g_pWorld->GetSceneLayer(g_pWorld->Air)->AttachChild(std::move(ptr));
	}
	
	virtual void UpdateCurrent(sf::Time dt)
	{
		try
		{
			call<void>("UpdateCurrent");
		}
		catch (...) { }
	}

	static void default_UpdateCurrent(Entity* ptr, sf::Time dt)
	{
		return ptr->Entity::UpdateCurrent(dt);
	}
};



void LuaFunctions::RegisterClassWrapper()
{
	

	luabind::module(lua->State())
	[
		luabind::class_<Entity, lua_entity_wrapper>("Entity")
			.def(luabind::constructor<std::string>())
			.def("UpdateCurrent", &Entity::UpdateCurrent, &lua_entity_wrapper::default_UpdateCurrent)
			.def("Activate", &lua_entity_wrapper::Activate)
	];

	/*// sf::Time
	luabind::module(lua->State()) [
	luabind::class_<sf::Time>("sfTime")
	.def(luabind::constructor<>())
	.def("asSeconds", &sf::Time::asSeconds)
	];

	// SceneNode
	luabind::module(lua->State()) [
	luabind::class_<SceneNode, LuaWrapper_SceneNode>("SceneNode")
	.def(luabind::constructor<>())
	];

	// Entity
	luabind::module(lua->State()) [
	luabind::class_<Entity, LuaWrapper_Entity, SceneNode>("Entity")
	.def(luabind::constructor<>())
	.def(luabind::constructor<std::string>())
	.def("GetClassName", &Entity::GetClassName)
	.def("UpdateCurrent", &Entity::UpdateCurrent, &LuaWrapper_Entity::default_UpdateCurrent)
	];

	// create entity
	luabind::module(lua->State()) [
	luabind::def("create_entity", create_entity)
	];*/
}