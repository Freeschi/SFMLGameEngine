// ====================================================================================================
// Includes
// ====================================================================================================
#include "Includes.h"

// ====================================================================================================
// SpriteNode
// ====================================================================================================
SpriteNode::SpriteNode() : Entity("sprite_node")
{

}
SpriteNode::SpriteNode(const sf::Texture& texture) : Entity("sprite_node"), mSprite(texture)
{

}
SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect) : Entity("sprite_node"), mSprite(texture, textureRect)
{

}

void SpriteNode::SetTexture(sf::Texture& texture)
{
	mSprite.setTexture(texture);
}
void SpriteNode::SetRect(sf::IntRect rect)
{
	mSprite.setTextureRect(rect);
}

// ====================================================================================================
// SpriteNode::drawCurrent
// ====================================================================================================
void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}