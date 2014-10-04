// ====================================================================================================
// Includes
// ====================================================================================================
#include "Includes.h"
#include "lua/GeneralFunctions.h"

// ====================================================================================================
// Definitions
// ====================================================================================================
Player* g_pPlayer = NULL;

// ====================================================================================================
// Player Mover
// ====================================================================================================
struct PlayerMover
{
	PlayerMover(Movement eMove) : m_eMove(eMove) { }

	void operator() (PlayerEntity& playerent, sf::Time dt) const
	{
		playerent.CreateMovement(m_eMove, dt);
	}

	Movement m_eMove;
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
	m_pPlayer = (PlayerEntity*) g_pWorld->CreateEntityByClassName("player");
	g_pWorld->GetSceneLayer(g_pWorld->LAYER_GENERAL)->AttachChild(m_pPlayer);

	mKeyBinding[sf::Keyboard::Left] = MoveLeft;
	mKeyBinding[sf::Keyboard::Right] = MoveRight;
	mKeyBinding[sf::Keyboard::Up] = MoveUp;
	mKeyBinding[sf::Keyboard::Down] = MoveDown;


	InitializeActions();
	FOREACH(auto& pair, mActionBinding)
		pair.second.category = Category::Player;
}

// ====================================================================================================
// Player::InitializeActions
// ====================================================================================================
void Player::InitializeActions()
{
	mActionBinding[MoveLeft].action = derivedAction<PlayerEntity>(PlayerMover(MOVEMENT_WALK_LEFT));
	mActionBinding[MoveRight].action = derivedAction<PlayerEntity>(PlayerMover(MOVEMENT_WALK_RIGHT));
	mActionBinding[MoveUp].action = derivedAction<PlayerEntity>(PlayerMover(MOVEMENT_WALK_UP));
	mActionBinding[MoveDown].action = derivedAction<PlayerEntity>(PlayerMover(MOVEMENT_WALK_DOWN));
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
		{
			if(!g_pGame->IsPaused())
				commands->push(mActionBinding[pair.second]);
		}
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
	case MoveUp:
	case MoveDown:
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
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	{
		if ((g_pGame->flLastPause+0.05f) <= LuaFunctions::uptime())
		{
			g_pGame->SetPaused(true);
			g_pGame->flLastPause = LuaFunctions::uptime();
			g_pGame->GetStateStack()->PushState(States::Pause);
		}
	}
}

