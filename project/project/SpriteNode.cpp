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
void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);	
} 