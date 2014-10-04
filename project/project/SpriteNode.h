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
	const sf::Texture* GetTexture() const;
	void SetBoundingRect(sf::IntRect rect);
	void SetBoundingRect(sf::FloatRect rect);
	virtual sf::FloatRect GetBoundingRect() const;

private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Sprite mSprite;
};

#endif