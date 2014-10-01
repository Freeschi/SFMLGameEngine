// ====================================================================================================
// SpriteNode Class
// ====================================================================================================
#ifndef H_SPRITENODE
#define H_SPRITENODE

class SpriteNode : public Entity
{
public:
	SpriteNode();
	explicit SpriteNode(const sf::Texture& texture);
	SpriteNode(const sf::Texture& texture, const sf::IntRect& rect);
	void CreateLuaObject();

	void SetTexture(sf::Texture& texture);
	void SetRect(sf::IntRect rect);

private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Sprite mSprite;
};

#endif