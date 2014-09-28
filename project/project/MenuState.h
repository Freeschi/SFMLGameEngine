#ifndef H_MENU_STATE
#define H_MENU_STATE

class MenuState : public State
{
public:
	MenuState(StateStack& stack);

	virtual void Draw();
	virtual bool Update(sf::Time dt);
	virtual bool HandleEvent(const sf::Event& event);

	void UpdateOptionText();

private:
	enum OptionNames
	{
		Play,
		Exit,
	};
	std::vector<sf::Text> mOptions;
	std::size_t mOptionIndex;
	sf::Sprite mBackgroundSprite;
};

#endif