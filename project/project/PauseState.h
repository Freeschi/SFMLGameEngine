#ifndef H_PAUSESTATE
#define H_PAUSESTATE

class PauseState : public State
{
public:
	PauseState(StateStack& stack);

	virtual void Draw();
	virtual bool Update(sf::Time dt);
	virtual bool HandleEvent(const sf::Event& event);
	sf::Text mPausedText;
};

#endif