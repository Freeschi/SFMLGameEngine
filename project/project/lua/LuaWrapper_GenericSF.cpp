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
};