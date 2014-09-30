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
	m_pLuaObject = NULL;
	m_iEntityIndex = g_pWorld->RegisterEntity(this);
};
Entity::Entity()
{
	m_sClassName = "base_entity";
	m_pLuaObject = NULL;
	m_iEntityIndex = g_pWorld->RegisterEntity(this);
};
Entity::~Entity()
{
	if (m_pLuaObject != NULL)
		m_pLuaObject->Invalidate();
	g_pWorld->UnregisterEntity(this);
};

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