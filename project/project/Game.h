// ====================================================================================================
// Game
// ====================================================================================================
#ifndef H_GAME
#define H_GAME

class Game
{
public:
	Game();
	void Run();
	void Exit();

	void OnFullyInitialized();

	bool HasFocus() { return m_bHasFocus;  }
	sf::RenderWindow& GetWindow() { return mWindow; }

private:
	void RegisterStates();

	void ProcessEvents();
	void Update(sf::Time deltaTime);
	void Render();

	void ProcessInput();

	sf::RenderWindow mWindow;
	StateStack* mStateStack;
	Player mPlayer;
	CommandQueue commands;
	bool m_bHasFocus;
};

extern Game* g_pGame;

#endif