// ====================================================================================================
// Includes
// ====================================================================================================
#include "../../Includes.h"
#include "Lua.h"
#include "GeneralFunctions.h"
#include "ClassWrappers.h"

// ====================================================================================================
// Human & Player
// ====================================================================================================
namespace LuaClasses
{
	// ====================================================================================================
	// Human
	// ====================================================================================================
	// Human Wrapper
	lua_human_wrapper::lua_human_wrapper(BaseHuman* pEntity) : lua_spritenode_wrapper((SpriteNode*)pEntity)
	{
		m_pHuman = pEntity;
		_base_init("Human");
	};

	luabind::object lua_human_wrapper::SetupLuaObject()
	{
		return luabind::object(lua->State(), this);
	}

	// ====================================================================================================
	// Player
	// ====================================================================================================
	// Player Wrapper
	lua_player_wrapper::lua_player_wrapper(PlayerEntity* pEntity) : lua_human_wrapper((BaseHuman*)pEntity)
	{
		m_pPlayer = pEntity;
		_base_init("Player");
	};

	luabind::object lua_player_wrapper::SetupLuaObject()
	{
		return luabind::object(lua->State(), this);
	}

	/*
	 * Register
	 */
	void RegisterHuman()
	{
		luabind::module(lua->State())[
			luabind::class_<LuaClasses::lua_human_wrapper, LuaClasses::lua_spritenode_wrapper>("Human")
		];

		luabind::module(lua->State())[
			luabind::class_<LuaClasses::lua_player_wrapper, LuaClasses::lua_human_wrapper>("Player")
		];
	}
}