// ====================================================================================================
// Scene Nodes
// ====================================================================================================
#ifndef H_SCENE_NODE
#define H_SCENE_NODE

#include "Command.h"



class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
	typedef std::unique_ptr<SceneNode> Ptr;

public:
	SceneNode();

	void AttachChild(Ptr child);
	Ptr DetachChild(const SceneNode& node);

	virtual void Update(sf::Time dt);
	virtual void UpdateCurrent(sf::Time dt) {};
	virtual void onCommand(const Command& command, sf::Time dt);

	sf::Transform GetWorldTransform() const;
	sf::Vector2f GetWorldPosition() const;

	std::vector<Ptr> mChildren;

	virtual unsigned int SceneNode::GetCategory() const;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {};

	/*void SetParent(SceneNode* parent) { mParent = parent; }
	SceneNode* GetParent() { return mParent;  }*/

private:
	void UpdateChildren(sf::Time dt);
	
	SceneNode* mParent;
};

#endif