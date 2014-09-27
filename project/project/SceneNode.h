// ====================================================================================================
// Scene Nodes
// ====================================================================================================
#ifndef H_SCENE_NODE
#define H_SCENE_NODE

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
	typedef std::unique_ptr<SceneNode> Ptr;

public:
	SceneNode();

	void AttachChild(Ptr child);
	Ptr DetachChild(const SceneNode& node);

	void Update(sf::Time dt);

	sf::Transform GetWorldTransform() const;
	sf::Vector2f GetWorldPosition() const;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {};
	virtual void UpdateCurrent(sf::Time dt) {};
	void UpdateChildren(sf::Time dt);
	void onCommand(const Command& command, sf::Time dt);

	std::vector<Ptr> mChildren;
	SceneNode* mParent;
};

#endif