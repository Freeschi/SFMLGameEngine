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
	explicit Aircraft(Type type);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	void UpdateCurrent(sf::Time dt);

	virtual unsigned int GetCategory() const { return 0; };

private:
	Type mType;
	sf::Sprite mSprite;
};

#endif