// ====================================================================================================
// Includes
// ====================================================================================================
#include "../../Includes.h"
#include "GeneralFunctions.h"
#include "ClassWrappers.h"

namespace LuaClasses
{
	void sfTextWrap::lua_SetText(std::string t)
	{
		setString(t);
	}
	std::string sfTextWrap::lua_GetText()
	{
		return getString();
	}

	/*
	 * Register
	 */
	void RegisterGUI()
	{
		luabind::module(lua->State()) [
			luabind::class_<sf::Font>("sfFont")
		];

		luabind::module(lua->State()) [
			luabind::class_<sfTextWrap>("sfText")
				.def(luabind::constructor<>())
				.def(luabind::constructor<std::string, sf::Font>())
				.def(luabind::constructor<std::string, sf::Font, unsigned int>())
				.def("SetText", &sfTextWrap::lua_SetText)
				.def("GetText", &sfTextWrap::lua_GetText)
				.def("SetFont", &sfTextWrap::setFont)
				.def("GetFont", &sfTextWrap::getFont)
				.def("SetSize", &sfTextWrap::setCharacterSize)
				.def("GetSize", &sfTextWrap::getCharacterSize)
				.def("SetColor", &sfTextWrap::setColor)
				.def("GetColor", &sfTextWrap::getColor)
				.def("SetPosition", (void (sf::Text::*)(float, float)) &sfTextWrap::setPosition)
				.def("SetPosition", (void (sf::Text::*)(const sf::Vector2f& pos)) &sfTextWrap::setPosition)
				.def("GetPosition", &sfTextWrap::getPosition)
		];
	}
}