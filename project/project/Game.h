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
};

#endif