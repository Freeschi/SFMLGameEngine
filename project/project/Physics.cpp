// ====================================================================================================
// Includes
// ====================================================================================================
#include "Includes.h"

// ====================================================================================================
// Get All Scene Nodes
// ====================================================================================================
std::vector<SceneNode*> Physics::GetAllSceneNodes()
{
	std::vector<SceneNode*> pObjects;

	for (std::size_t i = g_pWorld->LAYER_MAP; i < g_pWorld->LAYER_COUNT; ++i)
	{
		SceneNode* layer = g_pWorld->GetSceneLayer((World::Layer) i);
		std::vector<SceneNode*> pChildren = layer->GetAllChildren();

		for (std::vector<SceneNode*>::iterator it = pChildren.begin(); it != pChildren.end(); ++it)
		{
			pObjects.push_back(*it);
		}
	}

	return pObjects;
}

// ====================================================================================================
// Get Objects Intersecting
// ====================================================================================================
std::vector<SceneNode*> Physics::GetObjectsIntersecting(sf::FloatRect frMine, SceneNode* pIgnoreScene)
{
	std::vector<SceneNode*> pObjects;
	std::vector<SceneNode*> pAllSceneNodes = GetAllSceneNodes();

	for (std::vector<SceneNode*>::iterator it = pAllSceneNodes.begin(); it != pAllSceneNodes.end(); ++it)
	{
		SceneNode* pOther = *it;
		sf::FloatRect frOther = pOther->GetBoundingRect();
		if (pOther != NULL && pOther->IsValid() && pIgnoreScene != pOther && frOther.intersects(frMine))
		{
			pObjects.push_back(pOther);
		}
	}

	return pObjects;
}
std::vector<SceneNode*> Physics::GetObjectsIntersecting(SceneNode* pSceneNode)
{
	sf::FloatRect frMine = pSceneNode->GetBoundingRect();
	std::vector<SceneNode*> pObjects = GetObjectsIntersecting(frMine, pSceneNode);
	return pObjects;
}