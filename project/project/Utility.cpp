// ====================================================================================================
// Includes
// ====================================================================================================
#include "Includes.h"

// ====================================================================================================
// Center
// ====================================================================================================
namespace UTIL
{
	void CenterOrigin(sf::Sprite& sprite)
	{
		sf::FloatRect bounds = sprite.getLocalBounds();
		sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	}

	void CenterOrigin(sf::Text& text)
	{
		sf::FloatRect bounds = text.getLocalBounds();
		text.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	}
}