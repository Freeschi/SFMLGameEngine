// ====================================================================================================
// Includes
// ====================================================================================================
#include "../../Includes.h"
#include "Lua.h"
#include "GeneralFunctions.h"
#include "ClassWrappers.h"

// ====================================================================================================
// Sorite Node
// ====================================================================================================
namespace LuaClasses
{
	lua_spritenode_wrapper::lua_spritenode_wrapper(SpriteNode* pEntity) : lua_entity_wrapper((Entity*)pEntity)
	{
		m_pSprite = pEntity;
		_base_init("SpriteNode");
	};

	luabind::object lua_spritenode_wrapper::SetupLuaObject()
	{
		return luabind::object(lua->State(), this);
	}

	// Set Texture
	void lua_spritenode_wrapper::SetTexture(std::string texturename)
	{
		CheckValid();

		try
		{
			sf::Texture& texture = g_pWorld->GetTextureHolder()->Get(texturename);
			m_pSprite->SetTexture(texture);
		}
		catch (...)
		{
			lua->PushString("Invalid/Unloaded Texture specified!");
			throw luabind::error(lua->State());
		}
	}

	/*
	 * Register
	 */
	void RegisterSpriteNode()
	{
		luabind::module(lua->State()) [
			luabind::class_<LuaClasses::lua_spritenode_wrapper, LuaClasses::lua_entity_wrapper>("SpriteNode")
				.def("SetTexture", &LuaClasses::lua_spritenode_wrapper::SetTexture)
		];
	}
}