// ====================================================================================================
// Includes
// ====================================================================================================
#include "Includes.h"
#include "lua/ClassWrappers.h"

// ====================================================================================================
// SceneNode
// ====================================================================================================
SceneNode::SceneNode() : mParent(NULL)
{
	m_bFlaggedForRemoval = false;
	m_pLuaObject = NULL;

	CreateLuaObject();
}
SceneNode::~SceneNode()
{
	if (m_pLuaObject != NULL)
		m_pLuaObject->Invalidate();
}

// ====================================================================================================
// Lua
// ====================================================================================================
void SceneNode::CreateLuaObject()
{
	if (m_pLuaObject != NULL)
		delete m_pLuaObject;

	m_pLuaObject = (LuaClasses::base_class_wrapper*) new LuaClasses::lua_scenenode_wrapper(this);
}

// ====================================================================================================
// SceneNode::AttachChild
// ====================================================================================================
void SceneNode::AttachChild(SceneNode* child)
{
	child->SetParent(this);
	mChildren.push_back(child);
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
// Velocity
// ====================================================================================================
void SceneNode::SetVelocity(sf::Vector2f velocity)
{
	mVelocity = velocity;
}
void SceneNode::SetVelocity(float vx, float vy)
{
	mVelocity.x = vx;
	mVelocity.y = vy;
}
sf::Vector2f SceneNode::GetVelocity() const
{
	return mVelocity;
}

// ====================================================================================================
// Accelerate
// ====================================================================================================
void SceneNode::Accelerate(sf::Vector2f velocity)
{
	mVelocity += velocity;
}
void SceneNode::Accelerate(float vx, float vy)
{
	mVelocity.x += vx;
	mVelocity.y += vy;
}

bool _has_vector(std::vector<SceneNode*> vec, SceneNode* el)
{
	for (std::vector<SceneNode*>::iterator it2 = vec.begin(); it2 != vec.end(); ++it2)
	{
		SceneNode* pAlreadyAddedChild = *it2;
		if (pAlreadyAddedChild == el)
			return true;
	}

	return false;
}
std::vector<SceneNode*> SceneNode::GetAllChildren()
{
	std::vector<SceneNode*> pChildren;
	
	for (std::vector<SceneNode*>::iterator it = mChildren.begin(); it != mChildren.end(); ++it)
	{
		SceneNode* pChild = *it;
		pChildren.push_back(pChild);

		// childrens children
		std::vector<SceneNode*> pChildrensChildren = pChild->GetAllChildren();
		for (std::vector<SceneNode*>::iterator it2 = pChildrensChildren.begin(); it2 != pChildrensChildren.end(); ++it2)
		{
			SceneNode* pChildrenChild = *it2;
			if (!_has_vector(pChildren, pChildrenChild))
			{
				pChildren.push_back(pChildrenChild);
			}
		}
	}

	return pChildren;
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
		// General Updating
		move(mVelocity * dt.asSeconds()); // Velocity

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
		}
	}
}

// ====================================================================================================
// Collisions
// ====================================================================================================
sf::FloatRect SceneNode::GetBoundingRect() const
{
	return sf::FloatRect();
}
bool SceneNode::CollidesWith(SceneNode* pOther) const
{
	return pOther->GetBoundingRect().intersects(GetBoundingRect());
}

// ====================================================================================================
// Data
// ====================================================================================================
void SceneNode::SetValue(std::string key, int value)
{
	GetLuaObject()->LuaBindObject()[key] = value;
}
void SceneNode::SetValue(std::string key, float value)
{
	GetLuaObject()->LuaBindObject()[key] = value;
}
void SceneNode::SetValue(std::string key, double value)
{
	GetLuaObject()->LuaBindObject()[key] = value;
}
void SceneNode::SetValue(std::string key, std::string value)
{
	GetLuaObject()->LuaBindObject()[key] = value;
}
int SceneNode::GetIntValue(std::string key)
{
	return luabind::object_cast<int>(GetLuaObject()->LuaBindObject()[key]);
}
float SceneNode::GetFloatValue(std::string key)
{
	return luabind::object_cast<float>(GetLuaObject()->LuaBindObject()[key]);
}
double SceneNode::GetDoubleValue(std::string key)
{
	return luabind::object_cast<double>(GetLuaObject()->LuaBindObject()[key]);
}
std::string SceneNode::GetStringValue(std::string key)
{
	return luabind::object_cast<std::string>(GetLuaObject()->LuaBindObject()[key]);
}