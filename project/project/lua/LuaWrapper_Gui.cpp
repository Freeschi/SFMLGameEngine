// ====================================================================================================
// Includes
// ====================================================================================================
#include "../../Includes.h"
#include "GeneralFunctions.h"
#include "ClassWrappers.h"

namespace LuaClasses
{
	/*
	 * Register
	 */
	void RegisterGUI()
	{
		luabind::module(lua->State()) [
			luabind::class_<sf::Font>("sfFont")
		];

		luabind::module(lua->State()) [
			luabind::class_<sf::Text>("sfText")
				.def(luabind::constructor<>())
				.def(luabind::constructor<std::string, sf::Font>())
				.def(luabind::constructor<std::string, sf::Font, unsigned int>())
				.def("SetText", &sf::Text::setString)
				.def("GetText", &sf::Text::getString)
				.def("SetFont", &sf::Text::setFont)
				.def("GetFont", &sf::Text::getFont)
				.def("SetSize", &sf::Text::setCharacterSize)
				.def("GetSize", &sf::Text::getCharacterSize)
		];
	}
}