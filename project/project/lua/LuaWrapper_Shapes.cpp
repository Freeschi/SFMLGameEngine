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
	void RegisterSFShapes()
	{
		luabind::module(lua->State())[
			luabind::class_<sf::Transformable>("sfTransformable")
		];

		// Shape
		luabind::module(lua->State()) [
			luabind::class_<sf::Shape>("sfShape")
				.def("SetTexture", &sf::Shape::setTexture)
				.def("SetTextureRect", &sf::Shape::setTextureRect)
				.def("SetFillColor", &sf::Shape::setFillColor)
				.def("SetOutlineColor", &sf::Shape::setOutlineColor)
				.def("SetOutlineThickness", &sf::Shape::setOutlineThickness)
				.def("GetPoint", &sf::Shape::getPoint)
				.def("GetPointCount", &sf::Shape::getPointCount)
				// sf::Transformable
				.def("GetPosition", &sf::Shape::getPosition)
				.def("SetPosition", (void (sf::Shape::*)(float, float))		   &sf::Shape::setPosition)
				.def("SetPosition", (void (sf::Shape::*)(const sf::Vector2f&)) &sf::Shape::setPosition)
		];

		// Recangle Shape
		luabind::module(lua->State()) [
			luabind::class_<sf::RectangleShape, sf::Shape>("sfRectangleShape")
				.def(luabind::constructor<>())
				.def(luabind::constructor<sf::Vector2f>())
				.def("SetSize", &sf::RectangleShape::setSize)
				.def("GetSize", &sf::RectangleShape::getSize)
		];

		// Circle Shape
		luabind::module(lua->State()) [
			luabind::class_<sf::CircleShape, sf::Shape>("sfCircleShape")
				.def(luabind::constructor<>())
				.def(luabind::constructor<float>())
				.def(luabind::constructor<float, int>())
				.def("SetRadius", &sf::CircleShape::setRadius)
				.def("GetRadius", &sf::CircleShape::getRadius)
				.def("SetPointCount", &sf::CircleShape::setPointCount)
		];
	}
}