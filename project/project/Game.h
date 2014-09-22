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

private:
	void ProcessEvents();
	void Update(sf::Time deltaTime);
	void Render();

	void HandlePlayerInput(sf::Keyboard::Key key, bool isPressed);

private:
	bool mIsMovingUp;
	bool mIsMovingDown;
	bool mIsMovingLeft;
	bool mIsMovingRight;
	float PlayerSpeed;

	sf::RenderWindow mWindow;
	sf::CircleShape mPlayer;
};

#endif