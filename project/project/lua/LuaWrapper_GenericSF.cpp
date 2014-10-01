// ====================================================================================================
// Includes
// ====================================================================================================
#include "../../Includes.h"
#include "GeneralFunctions.h"
#include "ClassWrappers.h"

// ====================================================================================================
// Base
// ====================================================================================================
namespace LuaClasses
{
	/*
	 * Register
	 */
	void RegisterGenericSF()
	{
		// sf
		luabind::module(lua->State()) [
			luabind::class_<sf::Transformable>("sfTransformable")
		];
		luabind::module(lua->State()) [
			luabind::class_<sf::Drawable>("sfDrawable")
		];
		luabind::module(lua->State()) [
			luabind::class_<sf::NonCopyable>("NonCopyable")
		];
		luabind::module(lua->State()) [
			luabind::class_<sf::Time>("sfTime")
				.def("asMilliseconds", &sf::Time::asMilliseconds)
		];
		luabind::module(lua->State()) [
			luabind::class_<sf::FloatRect>("FloatRect")
				.def(luabind::constructor<>())
				.def(luabind::constructor<float, float, float, float>())
				.property("left", &sf::FloatRect::left)
				.property("top", &sf::FloatRect::top)
				.property("width", &sf::FloatRect::width)
				.property("height", &sf::FloatRect::height)
		];
	}
	void RegisterVector2()
	{
		// Vector2
		luabind::module(lua->State()) [
			luabind::class_<sf::Vector2f>("Vector2")
				.def(luabind::constructor<>())
				.def(luabind::constructor<float, float>())
				.property("x", &sf::Vector2f::x)
				.property("y", &sf::Vector2f::y)
		];
	}
	void RegisterEnums()
	{
		luabind::object g = luabind::globals(lua->State());

		// Scene LAYER_
		g["LAYER_COUNT"]			 = g_pWorld->LAYER_COUNT;
		g["LAYER_MAP"]				 = g_pWorld->LAYER_MAP;
		g["LAYER_GENERAL"]			 = g_pWorld->LAYER_GENERAL;
		g["LAYER_FOREGROUND"]		 = g_pWorld->LAYER_FOREGROUND;
		g["LAYER_HUD"]				 = g_pWorld->LAYER_HUD;
	}
};