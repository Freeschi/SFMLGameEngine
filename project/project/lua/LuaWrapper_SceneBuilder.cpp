// ====================================================================================================
// Includes
// ====================================================================================================
#include "../../Includes.h"
#include "Lua.h"
#include "GeneralFunctions.h"
#include "ClassWrappers.h"

// ====================================================================================================
// Scene Builder
// ====================================================================================================
namespace LuaClasses
{
	class SceneBuilder
	{
	public:
		SceneBuilder();

		void SetBackgroundTexture(std::string texture);
		void Add(sf::Vector2f, std::string texture);
	};

	SceneBuilder::SceneBuilder()
	{
		//
	}

	void SceneBuilder::SetBackgroundTexture(std::string texturename)
	{
		try
		{
			sf::Texture& texture = g_pWorld->GetTextureHolder()->Get(texturename);
			texture.setRepeated(true);

			SpriteNode* pSprite = (SpriteNode*)g_pWorld->CreateEntityByClassName("sprite_node");
			pSprite->SetTexture(texture);
			sf::FloatRect wb = g_pWorld->GetBounds();
			pSprite->SetBoundingRect(sf::IntRect(wb));

			g_pWorld->GetSceneLayer(g_pWorld->LAYER_BACKGROUND)->AttachChild((SceneNode*)pSprite);
		}
		catch (...)
		{
			lua->PushString("Invalid/Unloaded Texture specified!");
			throw luabind::error(lua->State());
		}
	}

	void SceneBuilder::Add(sf::Vector2f pos, std::string texturename)
	{
		try
		{
			sf::Texture& texture = g_pWorld->GetTextureHolder()->Get(texturename);

			SpriteNode* pSprite = (SpriteNode*)g_pWorld->CreateEntityByClassName("sprite_node");
			pSprite->SetTexture(texture);
			pSprite->setPosition(pos);

			g_pWorld->GetSceneLayer(g_pWorld->LAYER_MAP)->AttachChild((SceneNode*)pSprite);
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
	void RegisterSceneBuilder()
	{
		luabind::module(lua->State()) [
			luabind::class_<SceneBuilder>("SceneBuilder")
				.def("SetBackgroundTexture", &SceneBuilder::SetBackgroundTexture)
				.def("Add", &SceneBuilder::Add)
		];
	}

	void BuildScene()
	{
		// Let Lua build the scene
		SceneBuilder sb;
		luabind::object lua_sb(lua->State(), sb);

		lua->GetEvent("BuildScene");
		lua_sb.push(lua->State());
		g_pPlayer->GetEntity()->GetLuaObject()->Push();
		lua->ProtectedCall(3);
	}
};