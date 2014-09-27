// ====================================================================================================
// Includes
// ====================================================================================================
#include "Includes.h"

// ====================================================================================================
// SpriteNode
// ====================================================================================================
SpriteNode::SpriteNode(const sf::Texture& texture): mSprite(texture)
{

}
SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect): mSprite(texture, textureRect)
{

}

// ====================================================================================================
// SpriteNode::drawCurrent
// ====================================================================================================
void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}