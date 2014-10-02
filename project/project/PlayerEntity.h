// ====================================================================================================
// Player Entity
// ====================================================================================================
#ifndef H_PLAYER_ENTITY
#define H_PLAYER_ENTITY

class PlayerEntity : public BaseHuman
{
public:
	PlayerEntity();
	void UpdateCurrent(sf::Time dt);
	void CreateLuaObject();

	virtual bool IsHuman() const { return false; }
	virtual bool IsPlayer() const { return true; };
	virtual unsigned int GetCategory() const { return Category::Player; };
};

#endif