// ====================================================================================================
// Entity
// ====================================================================================================
#ifndef H_ENTITY
#define H_ENTITY

class Entity : public SceneNode
{
public:
	Entity(std::string classname);
	Entity();
	~Entity();

	bool IsEntity() { return true; }

	ACCESSOR_FUNC(ClassName, std::string, m_sClassName);
	virtual void CreateLuaObject();

	void SetVelocity(sf::Vector2f velocity);
	void SetVelocity(float vx, float vy);
	sf::Vector2f GetVelocity() const;

	void Accelerate(sf::Vector2f velocity);
	void Accelerate(float vx, float vy);

	virtual void UpdateCurrent(sf::Time dt);

private:
	sf::Vector2f mVelocity;
	std::string m_sClassName;
	int m_iEntityIndex;
}; 


#endif