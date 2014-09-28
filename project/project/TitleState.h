#ifndef H_TITLE_STATE
#define H_TITLE_STATE

class TitleState : public State
{
public:
	TitleState(StateStack& stack);

	virtual void Draw();
	virtual bool Update(sf::Time dt);
	virtual bool HandleEvent(const sf::Event& event);

private:
	sf::Sprite mBackgroundSprite;
	sf::Text mText;
	bool mShowText;
	sf::Time mTextEffectTime;
};

#endif