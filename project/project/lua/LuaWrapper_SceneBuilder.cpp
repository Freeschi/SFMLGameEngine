// ====================================================================================================
// Includes
// ====================================================================================================
#include "../../Includes.h"
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

	void SceneBuilder::SetBackgroundTexture(std::string texture)
	{
		//
	}

	void SceneBuilder::Add(sf::Vector2f, std::string add)
	{
		//
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
		lua->Call(2);
	}
};