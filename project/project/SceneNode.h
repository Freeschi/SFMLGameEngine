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

	void AttachChild(SceneNode* child);
	SceneNode* DetachChild(SceneNode* node);

	ACCESSOR_FUNC(LuaObject, LuaClasses::base_class_wrapper*, m_pLuaObject);
	virtual void CreateLuaObject();

	const void RemoveNextUpdate() { m_bFlaggedForRemoval = true; };
	bool IsValid() { return !m_bFlaggedForRemoval; }

	virtual void Update(sf::Time dt);
	virtual void UpdateCurrent(sf::Time dt) {};
	virtual void onCommand(const Command& command, sf::Time dt);

	sf::Transform GetWorldTransform() const;
	sf::Vector2f GetWorldPosition() const;

	std::vector<SceneNode*> mChildren;

	virtual unsigned int SceneNode::GetCategory() const;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {};

	SceneNode* GetParent() {
		return mParent;
	};

	/*void SetParent(SceneNode* parent) { mParent = parent; }
	SceneNode* GetParent() { return mParent;  }*/

private:
	bool m_bFlaggedForRemoval;
	void UpdateChildren(sf::Time dt);
	LuaClasses::base_class_wrapper* m_pLuaObject;
	
	SceneNode* mParent;
};

#endif