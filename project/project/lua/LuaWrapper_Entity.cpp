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
	lua_scenenode_wrapper() {}
};

class lua_entity_wrapper : public Entity, public lua_scenenode_wrapper, public luabind::wrap_base
{
public:
	typedef std::unique_ptr<Entity> Ptr;
	Ptr m_pEntity;
	lua_entity_wrapper(Entity* pEntity) : m_pEntity(pEntity) { };

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



/*Entity* Create() createfunc \*/

void LuaFunctions::RegisterClassWrapper()
{
	/*class RegisteredEntity_Aircraft : public RegisteredEntity
	{
	public:
		RegisteredEntity_Aircraft() : RegisteredEntity("aircraft_eagle") {}

		Entity* Create() { return new Aircraft(Aircraft::Eagle); }
	};
	RegisterEntityClass(new RegisteredEntity_Aircraft());
	*/
	
	// SceneNode
	luabind::module(lua->State())[
		luabind::class_<lua_scenenode_wrapper>("SceneNode")
			.def(luabind::constructor<>())
	];

	luabind::module(lua->State())
	[
		luabind::class_<lua_entity_wrapper, lua_scenenode_wrapper>("Entity")
			.def(luabind::constructor<Entity*>())
			.def("UpdateCurrent", &Entity::UpdateCurrent)
			.def("GetClassName", &lua_entity_wrapper::GetClassName)
			.def("Activate", &lua_entity_wrapper::Activate)
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