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

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	std::vector<Ptr> mChildren;
	SceneNode* mParent;
};

#endif