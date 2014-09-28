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

	static const float PlayerSpeed;

	void OnFullyInitialized();

	bool HasFocus() { return m_bHasFocus;  }
	sf::RenderWindow& GetWindow() { return mWindow; }

private:
	void RegisterStates();

	void ProcessEvents();
	void Update(sf::Time deltaTime);
	void Render();

	void ProcessInput();

	bool mIsMovingUp;
	bool mIsMovingDown;
	bool mIsMovingLeft;
	bool mIsMovingRight;

	sf::RenderWindow mWindow;
	sf::Texture mTexture;
	sf::Sprite mPlayerSprite;
	StateStack* mStateStack;
	Player mPlayer;
	CommandQueue commands;
	bool m_bHasFocus;
};

extern Game* g_pGame;

#endif