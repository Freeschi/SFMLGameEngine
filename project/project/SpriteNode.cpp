// ====================================================================================================
// Includes
// ====================================================================================================
#include "Includes.h"
#include "lua/ClassWrappers.h"

// ====================================================================================================
// SpriteNode
// ====================================================================================================
SpriteNode::SpriteNode() : Entity("sprite_node")
{
	CreateLuaObject();
}
SpriteNode::SpriteNode(const sf::Texture& texture) : Entity("sprite_node"), mSprite(texture)
{

}
SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect) : Entity("sprite_node"), mSprite(texture, textureRect)
{

}

// ====================================================================================================
// Lua
// ====================================================================================================
void SpriteNode::CreateLuaObject()
{
	if (GetLuaObject() != NULL)
		delete GetLuaObject();

	SetLuaObject((LuaClasses::base_class_wrapper*) new LuaClasses::lua_spritenode_wrapper(this));
}

// ====================================================================================================
// Texture
// ====================================================================================================
void SpriteNode::SetTexture(sf::Texture& texture)
{
	mSprite.setTexture(texture);
}
const sf::Texture* SpriteNode::GetTexture() const
{
	return mSprite.getTexture();
}

void SpriteNode::SetBoundingRect(sf::IntRect rect)
{
	mSprite.setTextureRect(rect);
}
void SpriteNode::SetBoundingRect(sf::FloatRect rect)
{
	mSprite.setTextureRect(sf::IntRect(rect));
}
sf::FloatRect SpriteNode::GetBoundingRect() const
{
	return GetWorldTransform().transformRect(mSprite.getGlobalBounds());
}

// ====================================================================================================
// Draw
// ====================================================================================================
void ds(sf::RenderTarget& target, sf::Vector2f pos, sf::Color col)
{
	sf::RectangleShape shape;
	shape.setPosition(pos);
	shape.setSize(sf::Vector2f(64.0f, 64.0f));
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(col);
	shape.setOutlineThickness(1.0f);
	target.draw(shape);
}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);

	sf::FloatRect rect = GetBoundingRect();

	

	if (IsPlayer())
	{
		std::vector<SceneNode*> pIntersects = g_pWorld->GetPhysics()->GetObjectsIntersecting((SceneNode*) this);
		for (std::vector<SceneNode*>::iterator it = pIntersects.begin(); it != pIntersects.end(); ++it)
		{
			SceneNode* pOther = *it;
			if (pOther->GetWorldPosition() == sf::Vector2f(0.0f, 0.0f))
			{
				SpriteNode* pSprite = dynamic_cast<SpriteNode*>(pOther);
				printf("%i\n", pSprite->GetTexture()->isRepeated());
			}
			ds(target, pOther->GetWorldPosition(), sf::Color::Red);
		}

		ds(target, GetWorldPosition(), sf::Color::Green);
	}
	if (!IsPlayer())
	{
		if (CollidesWith(g_pPlayer->GetEntity()))
			ds(target, sf::Vector2f(rect.left, rect.top), sf::Color::Blue);
	}
	
} 