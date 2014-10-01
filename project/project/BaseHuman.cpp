// ====================================================================================================
// Includes
// ====================================================================================================
#include "Includes.h"
#include "lua/ClassWrappers.h" 

// ====================================================================================================
// BaseHuman
// ====================================================================================================
BaseHuman::BaseHuman() : Entity("base_human")
{
	mSprite = new SpriteNode();
	mSprite->SetParent(this);
	this->AttachChild(mSprite);
}

SpriteNode* BaseHuman::GetSprite() { return mSprite;  }

// ====================================================================================================
// Lua
// ====================================================================================================
void BaseHuman::CreateLuaObject()
{
	if (GetLuaObject() != NULL)
		delete GetLuaObject();

	SetLuaObject((LuaClasses::base_class_wrapper*) new LuaClasses::lua_human_wrapper(this));
}

bool BaseHuman::CreateMovement(sf::Vector2f direction)
{
	sf::Vector2f vNewPos = GetWorldPosition() + direction;
	sf::FloatRect vPlayerBounds(vNewPos.x, vNewPos.y, 64.0f, 64.0f);
	vNewPos.x += vPlayerBounds.width;
	vNewPos.y += vPlayerBounds.height;
	sf::FloatRect wb = g_pWorld->GetBounds();
	if (!wb.intersects(vPlayerBounds))
		return false;
	if (vNewPos.x < wb.left && vNewPos.y < wb.top)
		return false;

	move(direction);
	return true;
}

// ====================================================================================================
// Update
// ====================================================================================================
void BaseHuman::UpdateCurrent(sf::Time dt)
{

}