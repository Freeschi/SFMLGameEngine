// ====================================================================================================
// Includes
// ====================================================================================================
#include "Includes.h"

// ====================================================================================================
// Aircraft Mover
// ====================================================================================================
struct AircraftMover
{
	AircraftMover(float vx, float vy) : velocity(vx, vy)
	{

	}

	void operator() (Aircraft& aircraft, sf::Time) const
	{
		aircraft.Accelerate(velocity);
	}

	sf::Vector2f velocity;
};

// ====================================================================================================
// Utility Function
// ====================================================================================================
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

// ====================================================================================================
// Realtime Input
// ====================================================================================================
void Player::HandleRealtimeInput(CommandQueue& commands)
{
	const float PlayerSpeed = 10.0f;

	// TO-DO: Make this work
	// Move Left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		Command moveLeft;
		moveLeft.category = Category::PlayerAircraft;
		moveLeft.action = derivedAction<Aircraft>(AircraftMover(-PlayerSpeed, 0.f));
		commands.push(moveLeft);
	}
}

// ====================================================================================================
// Event Handling
// TO-DO: This functions is never called!
// ====================================================================================================
void Player::HandleEvent(const sf::Event& event, CommandQueue& commands)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
	{
		Command output;
		output.category = Category::PlayerAircraft;
		output.action = [] (SceneNode& s, sf::Time)
		{
			std::cout << s.getPosition().x << "," << s.getPosition().y << "\n";
		};
		commands.push(output);
	}
}