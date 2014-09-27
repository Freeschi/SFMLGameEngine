// ====================================================================================================
// Includes
// ====================================================================================================
#include "Includes.h"

struct AircraftMover
{
	AircraftMover(float vx, float vy) : velocity(vx, vy)
	{

	}

	void operator() (Aircraft& aircraft, sf::Time) const
	{
		aircraft.Accelerate(velocity);
		printf("accelerate you piece of shit\n");
	}

	sf::Vector2f velocity;
};

template <typename GameObject, typename Function>
std::function<void(SceneNode&, sf::Time)>
derivedAction(Function fn)
{
	return [=](SceneNode& node, sf::Time dt)
	{
		// Check if cast is safe
		assert(dynamic_cast<GameObject*>(&node) != nullptr);
		// Downcast node and invoke function on it
		fn(static_cast<GameObject&>(node), dt);
	};
}

void Player::HandleRealtimeInput(CommandQueue& commands)
{
	const float PlayerSpeed = 31.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		Command moveLeft;
		moveLeft.category = Category::PlayerAircraft;
		moveLeft.action = derivedAction<Aircraft>(AircraftMover(-PlayerSpeed, 0.f));
		commands.push(moveLeft);
	}
}

void Player::HandleEvent(const sf::Event& event,
	CommandQueue& commands)
{
	if (event.type == sf::Event::KeyPressed
		&& event.key.code == sf::Keyboard::P)
	{
		Command output;
		output.category = Category::PlayerAircraft;
		output.action = [] (SceneNode& s, sf::Time)
		{
			std::cout << s.getPosition().x << ","
				<< s.getPosition().y << "\n";
		};
		commands.push(output);
	}
}