// ====================================================================================================
// Aircraft
// ====================================================================================================
#ifndef H_AIRCRAFT
#define H_AIRCRAFT

class Aircraft : public Entity
{
public:
	enum Type
	{
		Eagle,
		Raptor,
	};

public:
	explicit Aircraft(Type type, const TextureHolder& textures);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	Type mType;
	sf::Sprite mSprite;
};

// ====================================================================================================
// Aircraft Texture ID's
// ====================================================================================================
Textures::ID toTextureID(Aircraft::Type type);

#endif