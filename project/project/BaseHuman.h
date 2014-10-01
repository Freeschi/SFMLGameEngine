// ====================================================================================================
// Base Human
// ====================================================================================================
#ifndef H_BASE_HUMAN
#define H_BASE_HUMAN

class BaseHuman : public Entity
{
public:
	BaseHuman();
	void UpdateCurrent(sf::Time dt);
	void CreateLuaObject();

	SpriteNode* GetSprite();

	bool CreateMovement(sf::Vector2f direction);

	virtual unsigned int GetCategory() const { return Category::Human; };

private:
	SpriteNode* mSprite;
};

#endif