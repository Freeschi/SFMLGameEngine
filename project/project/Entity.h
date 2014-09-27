// ====================================================================================================
// Entity
// ====================================================================================================
#ifndef H_ENTITY
#define H_ENTITY

class Entity : public SceneNode
{
public:
	void SetVelocity(sf::Vector2f velocity);
	void SetVelocity(float vx, float vy);
	sf::Vector2f GetVelocity() const;

	void Accelerate(sf::Vector2f velocity);
	void Accelerate(float vx, float vy);

	virtual void UpdateCurrent(sf::Time dt);

private:
	sf::Vector2f mVelocity;
};

#endif