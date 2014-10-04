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
	void lua_renderwindow::Draw(sf::Shape& draw)
	{
		m_pWindow.draw((sf::Drawable&) draw);
	}
	void lua_renderwindow::Draw(sf::Text& draw)
	{
		m_pWindow.draw((sf::Drawable&) draw);
	}

	/*
	 * Register
	 */
	void RegisterGenericSF()
	{
		// Some random sf stuff needed
		luabind::module(lua->State()) [
			luabind::class_<sf::NonCopyable>("NonCopyable"),

			luabind::class_<sf::Time>("sfTime")
				.def("asSeconds", &sf::Time::asSeconds)
				.def("asMilliseconds", &sf::Time::asMilliseconds),

			luabind::class_<sf::Drawable>("sfDrawable"),

			luabind::class_<lua_renderwindow>("RenderWindow")
				.def("Draw",  (void (lua_renderwindow::*)(sf::Shape&)) &lua_renderwindow::Draw)
				.def("Draw",  (void (lua_renderwindow::*)(sf::Text&))  &lua_renderwindow::Draw),

			luabind::class_<sf::RenderTarget>("RenderTarget"),

			luabind::class_<sf::String>("sfString")
				.def(luabind::constructor<std::string>())
		];

		// Color
		luabind::module(lua->State()) [
			luabind::class_<sf::Color>("Color")
				.def(luabind::constructor<>())
				.def(luabind::constructor<sf::Uint8, sf::Uint8, sf::Uint8>())
				.def(luabind::constructor<sf::Uint8, sf::Uint8, sf::Uint8, sf::Uint8>())
				.property("r", &sf::Color::r)
				.property("g", &sf::Color::g)
				.property("b", &sf::Color::b)
				.property("a", &sf::Color::a)
		];

		// Rect<>
		luabind::module(lua->State()) [
			luabind::class_<sf::FloatRect>("FloatRect")
				.def(luabind::constructor<>())
				.def(luabind::constructor<float, float, float, float>())
				.property("left", &sf::FloatRect::left)
				.property("top", &sf::FloatRect::top)
				.property("width", &sf::FloatRect::width)
				.property("height", &sf::FloatRect::height)
		];
		luabind::module(lua->State())[
			luabind::class_<sf::IntRect>("IntRect")
				.def(luabind::constructor<>())
				.def(luabind::constructor<int, int, int, int>())
				.property("left", &sf::IntRect::left)
				.property("top", &sf::IntRect::top)
				.property("width", &sf::IntRect::width)
				.property("height", &sf::IntRect::height)
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