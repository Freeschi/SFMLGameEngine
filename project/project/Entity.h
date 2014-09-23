// ====================================================================================================
// Entity
// ====================================================================================================
#ifndef H_ENTITY
#define H_ENTITY

class Entity
{
public:
	void SetVelocity(sf::Vector2f velocity);
	void SetVelocity(float vx, float vy);
	sf::Vector2f GetVelocity() const;

private:
	sf::Vector2f mVelocity;
};

#endif