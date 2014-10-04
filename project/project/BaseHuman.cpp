// ====================================================================================================
// Includes
// ====================================================================================================
#include "Includes.h"
#include "lua/ClassWrappers.h" 

// ====================================================================================================
// BaseHuman
// ====================================================================================================
BaseHuman::BaseHuman()
{
	SetClassName("base_human"); 
	SetWalkSpeed(200.0f);
}

// ====================================================================================================
// Lua
// ====================================================================================================
void BaseHuman::CreateLuaObject()
{
	if (GetLuaObject() != NULL)
		delete GetLuaObject();

	SetLuaObject((LuaClasses::base_class_wrapper*) new LuaClasses::lua_human_wrapper(this));
}

// ====================================================================================================
// Movement
// ====================================================================================================
bool BaseHuman::CreateMovement(Movement eMove, sf::Time dt)
{
	lua->GetEvent("CreateMovement");
	lua->PushNumber((double)eMove);
	luabind::object dtime(lua->State(), dt);
	dtime.push(lua->State());
	lua->ProtectedCall(3, 1);

	bool bOverwrite = false;
	if (!lua->IsNil() && lua->IsBool())
		bOverwrite = lua->GetBool();
	if (bOverwrite)
		return true;

	// Offset Vector
	sf::Vector2f vOffset;
	switch (eMove)
	{
	case MOVEMENT_WALK_LEFT:
		vOffset = sf::Vector2f(-GetWalkSpeed(), 0.0f);
		break;
	case MOVEMENT_WALK_RIGHT:
		vOffset = sf::Vector2f(GetWalkSpeed(), 0.0f);
		break;
	case MOVEMENT_WALK_DOWN:
		vOffset = sf::Vector2f(0.0f, GetWalkSpeed());
		break;
	case MOVEMENT_WALK_UP:
		vOffset = sf::Vector2f(0.0f, -GetWalkSpeed());
		break;
	default:
		return false;
	}

	// Check Collision with our new position
	sf::Vector2f vNewPosition = GetWorldPosition() + vOffset * dt.asSeconds();
	sf::FloatRect vBoundingRect = GetBoundingRect();
	sf::FloatRect vNewPosRect(vNewPosition.x, vNewPosition.y, vBoundingRect.width, vBoundingRect.height);
	std::vector<SceneNode*> inters = g_pWorld->GetPhysics()->GetObjectsIntersecting(vNewPosRect, this);
	if (inters.size() > 0)
		return false;

	move(vOffset * dt.asSeconds());

	return true;
}

// ====================================================================================================
// Update
// ====================================================================================================
void BaseHuman::UpdateCurrent(sf::Time dt)
{

}