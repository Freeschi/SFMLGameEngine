// ====================================================================================================
// Physics
// ====================================================================================================
#ifndef H_PHYSICS
#define H_PHYSICS

class Physics
{
public:
	std::vector<SceneNode*> GetObjectsIntersecting(sf::FloatRect rect);
	std::vector<SceneNode*> GetObjectsIntersecting(SceneNode* pSceneNode);

private:
	std::vector<SceneNode*> GetAllSceneNodes();
};

#endif