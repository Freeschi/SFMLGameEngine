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

class BaseHuman : public SpriteNode
{
public:
	BaseHuman();
	void UpdateCurrent(sf::Time dt);
	void CreateLuaObject();

	ACCESSOR_FUNC(WalkSpeed, float, m_fWalkSpeed);
	bool CreateMovement(Movement move);

	virtual unsigned int GetCategory() const { return Category::Human; };

private:
	float m_fWalkSpeed;
};

#endif