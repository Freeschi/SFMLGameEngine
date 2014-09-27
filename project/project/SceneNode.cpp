// ====================================================================================================
// Includes
// ====================================================================================================
#include "Includes.h"

SceneNode::SceneNode() : mParent(NULL)
{
}

// ====================================================================================================
// SceneNode::AttachChild
// ====================================================================================================
void SceneNode::AttachChild(Ptr child)
{
	child->mParent = this;
	mChildren.push_back(std::move(child));

	printf("SceneNode::AttachChild\n");
}

// ====================================================================================================
// SceneNode::DetachChild
// ====================================================================================================
SceneNode::Ptr SceneNode::DetachChild(const SceneNode& node)
{
	auto found = std::find_if(mChildren.begin(), mChildren.end(),
		[&](Ptr& p) -> bool { return p.get() == &node; });

	if (found == mChildren.end()) return NULL;

	Ptr result = std::move(*found);
	result->mParent = nullptr;
	mChildren.erase(found);
	return result;
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
	if (GetCategory() & Category::PlayerAircraft)
	{
		printf("Aircraft::onCommand\n");
	}
	printf("SceneNode::onCommand => Category = %i => mChildren = %i\n", (int)GetCategory(), (int)mChildren.size());
	if (command.category & GetCategory())
		command.action(*this, dt);

	for (Ptr& child : mChildren)
		child->onCommand(command, dt);
}

// ====================================================================================================
// SceneNode::GetCategory()
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
	UpdateCurrent(dt);
	UpdateChildren(dt);
}
void SceneNode::UpdateChildren(sf::Time dt)
{
	for(Ptr& child : mChildren)
		child->Update(dt);
}