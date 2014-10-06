// ====================================================================================================
// Includes
// ====================================================================================================
#include "../Includes.h"
#include "Lua.h"
#include "GeneralFunctions.h"
#include "ClassWrappers.h"

// ====================================================================================================
// include
// ====================================================================================================
void LuaFunctions::include(std::string file)
{
	char* currentpath = lua->DebugGetPath();
	luaL_checkstring(lua->State(), 1);

	char path[364];
	sprintf(path, "%s%s", currentpath, file.c_str());
	std::string filepath(path);
	UTIL::ParseFilePath(filepath);

	char* sPath = const_cast<char*>(filepath.c_str());
	lua->IncludeFile(sPath);

	if (!lua->IsOnFileList(sPath))
		lua->AddToFileList(sPath);

	LuaFunctions::Autorefresh::AddDirectory(filepath);
}

// ====================================================================================================
// LocalPlayer
// ====================================================================================================
LuaClasses::lua_player_wrapper* LocalPlayer()
{
	return (LuaClasses::lua_player_wrapper*) g_pPlayer->GetEntity()->GetLuaObject();
}

// ====================================================================================================
// world-Module
// ====================================================================================================
namespace LuaFunctions
{
	sf::Clock cl;
	float uptime()
	{
		return (float)(cl.getElapsedTime().asMilliseconds()) / 1000;
	}

	namespace Module_World
	{
		// Probabbly broken
		// Untested!
		luabind::object GetSceneLayer(int iLayer)
		{
			if (iLayer >= g_pWorld->LAYER_COUNT)
			{
				lua->PushString("Invalid SceneLayer ID passed!");
				throw luabind::error(lua->State());
			}

			SceneNode* pNode = g_pWorld->GetSceneLayer((World::Layer) iLayer);
			return pNode->GetLuaObject()->LuaBindObject();
		}

		// Create Entity
		luabind::object CreateEntity(std::string classname)
		{
			Entity* pEntity = g_pWorld->CreateEntityByClassName(classname);
			if (pEntity == NULL) return lua_nil;
			return pEntity->GetLuaObject()->LuaBindObject();
		}

		// World Bounds
		sf::FloatRect GetBounds() { return g_pWorld->GetBounds(); }
		void SetBounds(sf::FloatRect b) { g_pWorld->SetBounds(b); }
	};
};


// ====================================================================================================
// game-Module
// ====================================================================================================
namespace LuaFunctions
{
	namespace Module_Game
	{
		// HasFocus
		bool HasFocus() { return g_pGame->HasFocus(); }

		// Mouse Position
		sf::Vector2i GetMousePosition()
		{
			return sf::Mouse::getPosition();
		}

		// Texture
		bool LoadTexture(std::string alias, std::string filename)
		{
			return g_pWorld->GetTextureHolder()->Load(alias, filename);
		}

		// Font
		bool LoadFont(std::string alias, std::string filename)
		{
			return g_pWorld->GetFontHolder()->Load(alias, filename);
		}
		luabind::object GetFont(std::string id)
		{
			try
			{
				luabind::object obj(lua->State(), g_pWorld->GetFontHolder()->Get(id));
				return obj;
			}
			catch (...)
			{
				return lua_nil;
			}
		}

		// GetFPS
		int GetFPS()
		{
			return g_pGame->GetFPS();
		}
	}
};


// ====================================================================================================
// draw-Module
// ====================================================================================================
namespace LuaFunctions
{
	namespace Module_Draw
	{
		void Rectangle(int x, int y, int w, int h, sf::Color color)
		{
			sf::RectangleShape rectangle;
			rectangle.setSize(sf::Vector2f(w, h));
			rectangle.setFillColor(color);
			rectangle.setPosition(sf::Vector2f(x, y));

			g_pWorld->GetWindow().draw(rectangle);
		}
	}
}

// ====================================================================================================
// Register Functions
// ====================================================================================================
void LuaFunctions::RegisterLuaFunctions()
{
	cl.restart();

	// General
	luabind::module(lua->State()) [
		luabind::def("include", &LuaFunctions::include),
		luabind::def("uptime", &LuaFunctions::uptime),
		luabind::def("LocalPlayer", &LocalPlayer)
	];

	// world Module
	luabind::module(lua->State(), "world") [
		luabind::def("GetSceneLayer", &LuaFunctions::Module_World::GetSceneLayer),
		luabind::def("CreateEntity", &LuaFunctions::Module_World::CreateEntity),
		luabind::def("GetBounds", &LuaFunctions::Module_World::GetBounds),
		luabind::def("SetBounds", &LuaFunctions::Module_World::SetBounds)
	];

	// game Module
	luabind::module(lua->State(), "game") [
		luabind::def("HasFocus", &LuaFunctions::Module_Game::HasFocus),
		luabind::def("LoadTexture", &LuaFunctions::Module_Game::LoadTexture),
		luabind::def("LoadFont", &LuaFunctions::Module_Game::LoadFont),
		luabind::def("GetFont", &LuaFunctions::Module_Game::GetFont),
		luabind::def("GetFPS", &LuaFunctions::Module_Game::GetFPS),
		luabind::def("GetMousePosition", &LuaFunctions::Module_Game::GetMousePosition)
	];

	// game Module
	luabind::module(lua->State(), "draw") [
		luabind::def("Rectangle", &LuaFunctions::Module_Draw::Rectangle)
	];
}