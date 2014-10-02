// ====================================================================================================
// Includes
// ====================================================================================================
#include "Includes.h"

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
// Includes
// ====================================================================================================
std::vector<SceneNode*> Physics::GetObjectsIntersecting(sf::FloatRect rect)
{
	return std::vector<SceneNode*>();
}

std::vector<SceneNode*> Physics::GetObjectsIntersecting(SceneNode* pSceneNode)
{
	std::vector<SceneNode*> pObjects;
	std::vector<SceneNode*> pAllSceneNodes = GetAllSceneNodes();
	sf::FloatRect frMine = pSceneNode->GetBoundingRect();

	for (std::vector<SceneNode*>::iterator it = pAllSceneNodes.begin(); it != pAllSceneNodes.end(); ++it)
	{
		SceneNode* pOther = *it;
		sf::FloatRect frOther = pOther->GetBoundingRect();
		if (pOther != pSceneNode && frOther.intersects(frMine))
		{
			pObjects.push_back(pOther);
		}
	}

	return pObjects;
}