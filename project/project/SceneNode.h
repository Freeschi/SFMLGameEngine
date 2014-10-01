// ====================================================================================================
// Scene Nodes
// ====================================================================================================
#ifndef H_SCENE_NODE
#define H_SCENE_NODE

#include "Command.h"

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
	SceneNode();
	~SceneNode();

	// Is-Functions
	virtual bool IsEntity() { return false; };
	virtual bool IsPlayer() { return false; }

	// Parents & Childs
	ACCESSOR_FUNC(Parent, SceneNode*, mParent);
	std::vector<SceneNode*> mChildren;
	void AttachChild(SceneNode* child);
	SceneNode* DetachChild(SceneNode* node);

	// Lua Object
	ACCESSOR_FUNC(LuaObject, LuaClasses::base_class_wrapper*, m_pLuaObject);
	virtual void CreateLuaObject();

	// General
	const void RemoveNextUpdate() { m_bFlaggedForRemoval = true; };
	bool IsValid() { return !m_bFlaggedForRemoval; };
	sf::Transform GetWorldTransform() const;
	sf::Vector2f GetWorldPosition() const;
	virtual unsigned int SceneNode::GetCategory() const;

	// Data
	void SetValue(std::string key, std::string value);
	void SetValue(std::string key, int value);
	void SetValue(std::string key, float value);
	void SetValue(std::string key, double value);
	int GetIntValue(std::string key);
	std::string GetStringValue(std::string key);
	float GetFloatValue(std::string key);
	double GetDoubleValue(std::string key);

	// Update
	virtual void Update(sf::Time dt);
	virtual void UpdateCurrent(sf::Time dt) {};
	virtual void onCommand(const Command& command, sf::Time dt);

	// Draw
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {};

private:
	bool m_bFlaggedForRemoval;
	void UpdateChildren(sf::Time dt);
	LuaClasses::base_class_wrapper* m_pLuaObject;
	
	SceneNode* mParent;
};

#endif