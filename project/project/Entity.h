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

	ACCESSOR_FUNC(ClassName, std::string, m_sClassName);
	ACCESSOR_FUNC(LuaObject, LuaClasses::lua_entity_wrapper*, m_pLuaObject);

	void SetVelocity(sf::Vector2f velocity);
	void SetVelocity(float vx, float vy);
	sf::Vector2f GetVelocity() const;

	void Accelerate(sf::Vector2f velocity);
	void Accelerate(float vx, float vy);

	virtual void UpdateCurrent(sf::Time dt);

private:
	sf::Vector2f mVelocity;
	std::string m_sClassName;
	LuaClasses::lua_entity_wrapper* m_pLuaObject;
	int m_iEntityIndex;
}; 


#endif