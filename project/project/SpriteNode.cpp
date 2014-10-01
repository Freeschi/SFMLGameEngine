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
void SpriteNode::SetRect(sf::IntRect rect)
{
	mSprite.setTextureRect(rect);
}

// ====================================================================================================
// Draw
// ====================================================================================================
void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
} 