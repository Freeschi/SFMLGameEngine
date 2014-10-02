#ifndef H_LOADING_STATE
#define H_LOADING_STATE

class LoadingState : public State
{
public:
	LoadingState(StateStack& stack);
	~LoadingState();

	virtual void Draw();
	virtual bool Update(sf::Time dt);
	virtual bool HandleEvent(const sf::Event& event);

	void SetStatusText(std::string text);

private:
	sf::Text mText;
	LoadingTask* m_pLoadingTask;
};

#endif