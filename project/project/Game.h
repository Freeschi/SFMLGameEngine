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

	void UpdateStats(sf::Time dt);
	int GetFPS();

	StateStack* GetStateStack() { return mStateStack; }
	float flLastPause;
	ACCESSOR_FUNC_BOOL(Paused, m_bIsPaused);

private:
	void RegisterStates();
	void ProcessEvents();
	void Update(sf::Time deltaTime);
	void Render();

	int m_iFPS;
	sf::Time mStatisticsUpdateTime;

	sf::RenderWindow mWindow;
	StateStack* mStateStack;
	CommandQueue commands;

	bool m_bHasFocus;
	bool m_bIsPaused;
};

extern Game* g_pGame;

#endif