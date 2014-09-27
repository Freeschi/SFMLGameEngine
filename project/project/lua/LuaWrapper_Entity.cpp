// ====================================================================================================
// Includes
// ====================================================================================================
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

	void Update(sf::Time df)
	{
		printf("SceneNode::Update\n");
	}
};

// ====================================================================================================
// Entity Wrapper
// ====================================================================================================
class LuaWrapper_Entity : public Entity, public LuaWrapper_SceneNode, public luabind::wrap_base
{
public:
	LuaWrapper_Entity() : Entity("lua_base_entity"), LuaWrapper_SceneNode()
	{
		printf("Entity::Entity\n");
	}


};

void LuaFunctions::RegisterClassWrapper()
{
	// sf::Time
	luabind::module(lua->State())[
		luabind::class_<sf::Time>("sfTime")
			.def(luabind::constructor<>())
			.def("asSeconds", &sf::Time::asSeconds)
	];

	// SceneNode
	luabind::module(lua->State()) [
		luabind::class_<SceneNode, LuaWrapper_SceneNode>("SceneNode")
			.def(luabind::constructor<>())
			.def("Update", &SceneNode::Update)
	];

	// Entity
	luabind::module(lua->State()) [
		luabind::class_<Entity, SceneNode, LuaWrapper_Entity>("Entity")
			.def(luabind::constructor<>())
			.def("GetClassName", &Entity::GetClassName)
	];
}