#ifndef H_PLAYER
#define H_PLAYER

class Player
{
public:
	Player();

	enum Action
	{
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown
	};

	void InitializeActions();
	void AssignKey(Action action, sf::Keyboard::Key key);
	sf::Keyboard::Key GetAssignedKey(Action action) const;

	PlayerEntity* GetEntity() {
		return m_pPlayer;
	};

public:
	void HandleEvent(const sf::Event& event, CommandQueue* commands);
	void HandleRealtimeInput(CommandQueue* commands);

private:
	static bool isRealtimeAction(Action action);

	std::map<sf::Keyboard::Key, Action> mKeyBinding;
	std::map<Action, Command> mActionBinding;

	PlayerEntity* m_pPlayer;
};

extern Player* g_pPlayer;

#endif
