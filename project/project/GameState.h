#ifndef H_GAME_STATE
#define H_GAME_STATE

class GameState : public State
{
public:
	GameState(StateStack& stack);

	virtual void Draw();
	virtual bool Update(sf::Time dt);
	virtual bool HandleEvent(const sf::Event& event);

	void BuildScene();
private:
	
};

#endif