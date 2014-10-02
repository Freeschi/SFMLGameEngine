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

	bool IsEntity() const { return true; }

	ACCESSOR_FUNC(ClassName, std::string, m_sClassName);
	virtual void CreateLuaObject();

	virtual void UpdateCurrent(sf::Time dt);

private:
	std::string m_sClassName;
	int m_iEntityIndex;
}; 


#endif