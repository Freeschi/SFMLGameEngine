// ====================================================================================================
// Game Class
// ====================================================================================================
#ifndef H_GAME
#define H_GAME

class Game
{
public:
	Game();
	void Run();

	static const float PlayerSpeed;

	bool HasFocus() { return m_bHasFocus;  }

private:
	void ProcessEvents();
	void Update(sf::Time deltaTime);
	void Render();

	void HandlePlayerInput(sf::Keyboard::Key key, bool isPressed);

	bool mIsMovingUp;
	bool mIsMovingDown;
	bool mIsMovingLeft;
	bool mIsMovingRight;

	sf::RenderWindow mWindow;
	sf::Texture mTexture;
	sf::Sprite mPlayer;
	World mWorld;
	bool m_bHasFocus;
};

#endif