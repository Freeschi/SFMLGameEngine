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
		// Some random sf stuff needed
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

		// FloatRect
		luabind::module(lua->State()) [
			luabind::class_<sf::FloatRect>("FloatRect")
				.def(luabind::constructor<>())
				.def(luabind::constructor<float, float, float, float>())
				.property("left", &sf::FloatRect::left)
				.property("top", &sf::FloatRect::top)
				.property("width", &sf::FloatRect::width)
				.property("height", &sf::FloatRect::height)
		];

		// Vector2
		luabind::module(lua->State())[
			luabind::class_<sf::Vector2f>("Vector2")
				.def(luabind::constructor<>())
				.def(luabind::constructor<float, float>())
				.property("x", &sf::Vector2f::x)
				.property("y", &sf::Vector2f::y)
		];
	}
};