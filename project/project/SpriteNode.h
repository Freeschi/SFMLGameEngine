// ====================================================================================================
// SpriteNode Class
// ====================================================================================================
#ifndef H_SPRITENODE
#define H_SPRITENODE

class SpriteNode : public SceneNode
{
public:
	explicit SpriteNode(const sf::Texture& texture);
	SpriteNode(const sf::Texture& texture, const sf::IntRect& rect);
private:
	virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	sf::Sprite mSprite;
};

#endif