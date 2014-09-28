// ====================================================================================================
// Includes
// ====================================================================================================
#include "Includes.h"

// ====================================================================================================
// Definitions
// ====================================================================================================
Player* g_pPlayer = NULL;

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
// Player::Player
// ====================================================================================================

Player::Player()
{
	mKeyBinding[sf::Keyboard::Left] = MoveLeft;
	mKeyBinding[sf::Keyboard::Right] = MoveRight;
	mKeyBinding[sf::Keyboard::Up] = MoveUp;
	mKeyBinding[sf::Keyboard::Down] = MoveDown;

	InitializeActions();
	FOREACH(auto& pair, mActionBinding)
		pair.second.category = Category::PlayerAircraft;
}

// ====================================================================================================
// Player::InitializeActions
// ====================================================================================================
void Player::InitializeActions()
{
	const float playerSpeed = 200.f;

	mActionBinding[MoveLeft].action = derivedAction<Aircraft>(AircraftMover(-playerSpeed, 0.f));
	mActionBinding[MoveRight].action = derivedAction<Aircraft>(AircraftMover(+playerSpeed, 0.f));
	mActionBinding[MoveUp].action = derivedAction<Aircraft>(AircraftMover(0.f, -playerSpeed));
	mActionBinding[MoveDown].action = derivedAction<Aircraft>(AircraftMover(0.f, +playerSpeed));
}

// ====================================================================================================
// Player::AssignKey
// ====================================================================================================
void Player::AssignKey(Action action, sf::Keyboard::Key key)
{
	// Remove all keys that already map to action
	for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end();)
	{
		if (itr->second == action)
			mKeyBinding.erase(itr++);
		else
			++itr;
	}

	// Insert new binding
	mKeyBinding[key] = action;
}

// ====================================================================================================
// Player::GetAssignedKey
// ====================================================================================================
sf::Keyboard::Key Player::GetAssignedKey(Action action) const
{
	FOREACH(auto pair, mKeyBinding)
	{
		if (pair.second == action)
			return pair.first;
	}

	return sf::Keyboard::Unknown;
}
// ====================================================================================================
// Realtime Input
// ====================================================================================================
void Player::HandleRealtimeInput(CommandQueue* commands)
{
	FOREACH(auto pair, mKeyBinding)
	{
		if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
			commands->push(mActionBinding[pair.second]);
	}
}

// ====================================================================================================
// isRealtimeAction
// ====================================================================================================
bool Player::isRealtimeAction(Action action)
{
	switch (action)
	{
	case MoveLeft:
	case MoveRight:

		return true;

	default:
		return false;
	}
}


// ====================================================================================================
// Event Handling
// ====================================================================================================
void Player::HandleEvent(const sf::Event& event, CommandQueue* commands)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
	{
		Command output;
		output.category = Category::PlayerAircraft;
		output.action = [] (SceneNode& s, sf::Time)
		{
			std::cout << s.getPosition().x << "," << s.getPosition().y << "\n";
		};
		commands->push(output);
	}
}