// ====================================================================================================
// Includes
// ====================================================================================================
#include "Includes.h"
#include "Lua.h"

SceneNode::SceneNode() : mParent(NULL)
{
	m_bFlaggedForRemoval = false;
}

// ====================================================================================================
// SceneNode::AttachChild
// ====================================================================================================
void SceneNode::AttachChild(SceneNode* child)
{
	child->mParent = this;
	mChildren.push_back(std::move(child));
}

// ====================================================================================================
// SceneNode::DetachChild
// ====================================================================================================
SceneNode* SceneNode::DetachChild(SceneNode* node)
{
	auto found = std::find_if(mChildren.begin(), mChildren.end(),
		[&](SceneNode* p) -> bool { return p == node; });

	if (found == mChildren.end()) return NULL;

	node->mParent = nullptr;
	mChildren.erase(found);
	return node;
}

// ====================================================================================================
// SceneNode::Draw
// ====================================================================================================
void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	drawCurrent(target, states);

	for (auto itr = mChildren.begin();
		itr != mChildren.end(); ++itr)
	{
		if ((*itr)->IsValid())
			(*itr)->draw(target, states);
	}
}

// ====================================================================================================
// SceneNode::GetWorldPosition
// ====================================================================================================
sf::Transform SceneNode::GetWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;
	for (const SceneNode* node = this; node != nullptr; node = node->mParent)
		transform = node->getTransform() * transform;

	return transform;
}
sf::Vector2f SceneNode::GetWorldPosition() const
{
	return GetWorldTransform() * sf::Vector2f();
}

// ====================================================================================================
// SceneNode::OnCommand
// ====================================================================================================
void SceneNode::onCommand(const Command& command, sf::Time dt)
{
	if (command.category & GetCategory())
		command.action(*this, dt);

	for (SceneNode* child : mChildren)
		child->onCommand(command, dt);
}

// ====================================================================================================
// SceneNode::GetCategory
// ====================================================================================================
unsigned int SceneNode::GetCategory() const
{
	return Category::Scene;
}

// ====================================================================================================
// SceneNode::Update
// ====================================================================================================
void SceneNode::Update(sf::Time dt)
{
	if (IsValid())
	{
		UpdateCurrent(dt);
		UpdateChildren(dt);
	}
}
void SceneNode::UpdateChildren(sf::Time dt)
{
	for (SceneNode* child : mChildren)
	{
		child->Update(dt);

		if (!child->IsValid())
		{
			DetachChild(child);
			delete child;

			lua->GetEvent("OnSceneNodeDeleted");
			lua->ProtectedCall(1);

			printf("Call to OnSceneNode already placed\n");
		}
	}
}