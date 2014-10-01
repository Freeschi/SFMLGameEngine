// ====================================================================================================
// Includes
// ====================================================================================================
#include "Includes.h"
#include "lua/ClassWrappers.h" 

// ====================================================================================================
// Entity
// ====================================================================================================
Entity::Entity(std::string classname)
{
	m_sClassName = classname;
	m_iEntityIndex = g_pWorld->RegisterEntity(this);

	CreateLuaObject();
};
Entity::Entity()
{
	m_sClassName = "base_entity";
	m_iEntityIndex = g_pWorld->RegisterEntity(this);

	CreateLuaObject();
};
Entity::~Entity()
{
	g_pWorld->UnregisterEntity(this);
};

// ====================================================================================================
// Lua
// ====================================================================================================
void Entity::CreateLuaObject()
{
	if (GetLuaObject() != NULL)
		delete GetLuaObject();

	SetLuaObject((LuaClasses::base_class_wrapper*) new LuaClasses::lua_entity_wrapper(this));
}

// ====================================================================================================
// Update
// ====================================================================================================
void Entity::UpdateCurrent(sf::Time dt)
{
	
}