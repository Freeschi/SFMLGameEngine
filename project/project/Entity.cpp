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
// Velocity
// ====================================================================================================
void Entity::SetVelocity(sf::Vector2f velocity)
{
	mVelocity = velocity;
}
void Entity::SetVelocity(float vx, float vy)
{
	mVelocity.x = vx;
	mVelocity.y = vy;
}
sf::Vector2f Entity::GetVelocity() const
{
	return mVelocity;
}

// ====================================================================================================
// Update
// ====================================================================================================
void Entity::UpdateCurrent(sf::Time dt)
{
	move(mVelocity * dt.asSeconds());
}

// ====================================================================================================
// Accelerate
// ====================================================================================================
void Entity::Accelerate(sf::Vector2f velocity)
{
	mVelocity += velocity;
}
void Entity::Accelerate(float vx, float vy)
{
	mVelocity.x += vx;
	mVelocity.y += vy;
}