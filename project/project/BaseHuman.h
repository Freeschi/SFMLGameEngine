// ====================================================================================================
// Base Human
// ====================================================================================================
#ifndef H_BASE_HUMAN
#define H_BASE_HUMAN

enum Movement
{
	MOVEMENT_WALK_LEFT,
	MOVEMENT_WALK_RIGHT,
	MOVEMENT_WALK_UP,
	MOVEMENT_WALK_DOWN
	// In future we can add RUN movements, or jump / climb
	// speed is specified by Human SetWalkSpeed
};
enum MoveType
{
	MOVETYPE_NORMAL,
	MOVETYPE_GRID
};

class BaseHuman : public SpriteNode
{
public:
	BaseHuman();
	void UpdateCurrent(sf::Time dt);
	void CreateLuaObject();

	ACCESSOR_FUNC(WalkSpeed, float, m_fWalkSpeed);
	ACCESSOR_FUNC(MoveType, MoveType, m_eMoveType);
	bool CreateMovement(Movement move, sf::Time dt);

	virtual bool IsHuman() const { return true; }
	virtual unsigned int GetCategory() const { return Category::Human; };

private:
	MoveType m_eMoveType;
	float m_fWalkSpeed;
};

#endif